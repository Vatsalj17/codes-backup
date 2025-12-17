import requests
from bs4 import BeautifulSoup, Tag
from urllib.parse import urljoin
from playwright.sync_api import sync_playwright
import re
import time
from typing import Optional, List, Dict, Any
from playwright_stealth import stealth

class UniversalScraper:
    def __init__(self, url: str, js: bool = False, timeout: int = 15000) -> None:
        self.url: str = url
        self.js: bool = js
        self.timeout: int = timeout
        # Explicitly tell the type checker these can be None initially
        self.html: Optional[str] = None
        self.soup: Optional[BeautifulSoup] = None
        self.result: Dict[str, Any] = {}

    # -------------------------------------------------------------
    # STEP 1: FETCH HTML (PATCHED)
    # -------------------------------------------------------------
    def fetch_html(self) -> None:
        if not self.js:
            print("[+] Fetching with requests...")
            r = requests.get(self.url, headers={
                "User-Agent": "Mozilla/5.0 (X11; Linux x86_64)"
            }, timeout=20)
            r.raise_for_status()
            self.html = r.text
            return

        print("[+] Fetching full JS-rendered HTML using Playwright...")
        with sync_playwright() as p:
            # Launch with a real viewport to look less like a bot
            browser = p.chromium.launch(headless=True) 
            
            context = browser.new_context(
                user_agent="Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36",
                viewport={'width': 1920, 'height': 1080}
            )

            # --- CRITICAL: INJECT COOKIE HERE ---
            # Replace 'YOUR_LI_AT_VALUE_HERE' with the actual string from your browser
            context.add_cookies([{
                'name': 'li_at', 
                'value': 'YOUR_LI_AT_VALUE_HERE',  # <--- PASTE COOKIE HERE
                'domain': '.linkedin.com', 
                'path': '/'
            }])
            # ------------------------------------

            page = context.new_page()
            
            # Optional: Try to mask automation (ignore linter errors here)

            print(f"[+] Navigating to {self.url}...")
            page.goto(self.url, timeout=self.timeout)

            # FIX FOR THE CRASH:
            # Instead of sleep(2), wait for the network to be idle (no traffic for 500ms)
            # This ensures redirects are finished before we grab content.
            try:
                page.wait_for_load_state("networkidle", timeout=10000)
            except Exception as e:
                print(f"[-] Warning: Network idle timeout ({e}), proceeding anyway...")

            # Scroll down to trigger lazy-loaded elements (common on LinkedIn)
            page.evaluate("window.scrollTo(0, document.body.scrollHeight)")
            time.sleep(1) 

            self.html = page.content()
            browser.close()

    # -------------------------------------------------------------
    # STEP 2: PARSE DOM
    # -------------------------------------------------------------
    def parse(self) -> None:
        # GUARD CLAUSE: Ensure html exists before passing to BeautifulSoup
        if self.html is None:
            raise ValueError("HTML content is empty. Call fetch_html() first.")
        
        self.soup = BeautifulSoup(self.html, "lxml")

    # -------------------------------------------------------------
    # STEP 3: EXTRACT FULL TEXT (CLEANED)
    # -------------------------------------------------------------
    def extract_text(self) -> None:
        # GUARD CLAUSE: Ensure soup exists
        if self.soup is None:
            return 

        text = self.soup.get_text(separator="\n")
        cleaned = re.sub(r"\n\s*\n", "\n", text).strip()
        self.result["full_text"] = cleaned

    # -------------------------------------------------------------
    # STEP 4: EXTRACT HEADINGS
    # -------------------------------------------------------------
    def extract_headings(self) -> None:
        if self.soup is None:
            return

        headings: Dict[str, List[str]] = {}
        for level in range(1, 7):
            tag = f"h{level}"
            # BS4 find_all returns a ResultSet, we iterate and get text
            headings[tag] = [h.get_text(strip=True) for h in self.soup.find_all(tag)]
        self.result["headings"] = headings

    # -------------------------------------------------------------
    # STEP 5: EXTRACT ALL LINKS
    # -------------------------------------------------------------
    def extract_links(self) -> None:
        if self.soup is None:
            return

        base = self.url
        links: List[str] = []
        
        # Explicitly typing 'a' helps, but strict checking requires valid hrefs
        for a in self.soup.find_all("a", href=True):
            # BeautifulSoup attributes can be str, list, or None. We strictly cast to str.
            href = a.get("href")
            if isinstance(href, (str, list)):
                # Handle cases where href might be a list (rare, but valid in BS4 types)
                clean_href = href[0] if isinstance(href, list) else href
                links.append(urljoin(base, clean_href))
                
        self.result["links"] = list(set(links))

    # -------------------------------------------------------------
    # STEP 6: IMAGES, SCRIPTS, CSS (FIXED)
    # -------------------------------------------------------------
    def extract_assets(self) -> None:
        if self.soup is None:
            return

        base = self.url

        # Helper function to safely extract and join URLs
        def get_asset_urls(tag_name: str, attr_name: str) -> List[str]:
            if self.soup is None: return [] # Redundant but satisfies analyzer
            urls = []
            # This tells the type checker explicitly that we are passing attributes,
            # not trying to pass a boolean to 'limit' or 'recursive'.
            for item in self.soup.find_all(tag_name, attrs={attr_name: True}):
                # find_all can theoretically return NavigableString (text nodes),
                # which would crash .get() at runtime or error in strict typing.
                if isinstance(item, Tag):
                    val = item.get(attr_name)
                    # Handle the Union[str, List[str]] return type of .get()
                    if isinstance(val, (str, list)):
                        clean_val = val[0] if isinstance(val, list) else val
                        urls.append(urljoin(base, clean_val))
            return urls

        self.result["images"] = get_asset_urls("img", "src")
        self.result["scripts"] = get_asset_urls("script", "src")
        self.result["stylesheets"] = get_asset_urls("link", "href")

    # -------------------------------------------------------------
    # STEP 7: METADATA
    # -------------------------------------------------------------
    def extract_metadata(self) -> None:
        if self.soup is None:
            return

        meta_data: Dict[str, str] = {}

        for m in self.soup.find_all("meta"):
            # Type narrowing for attribute retrieval
            name = m.get("name")
            prop = m.get("property")
            content = m.get("content", "")

            # Ensure content is a string (BS4 can return lists for some attrs)
            content_str = str(content[0]) if isinstance(content, list) else str(content)

            if isinstance(name, str):
                meta_data[name] = content_str
            if isinstance(prop, str):
                meta_data[prop] = content_str

        # Handle Title Safely
        title_tag = self.soup.title
        title = title_tag.string if title_tag and title_tag.string else ""
        meta_data["title"] = str(title)

        self.result["meta"] = meta_data

    # -------------------------------------------------------------
    # RUN EVERYTHING
    # -------------------------------------------------------------
    def scrape(self) -> Dict[str, Any]:
        self.fetch_html()
        self.parse()
        self.extract_text()
        self.extract_headings()
        self.extract_links()
        self.extract_assets()
        self.extract_metadata()
        return self.result

# -------------------------------------------------------------
# Example Usage
# -------------------------------------------------------------
if __name__ == "__main__":
    url_input = input("Enter URL to scrape → ")
    if not url_input.startswith("http"):
        url_input = "https://" + url_input

    scraper = UniversalScraper(url_input, js=True)
    result = scraper.scrape()

    print("\n==================== SCRAPED CONTENT ====================\n")
    for key, value in result.items():
        print(f"\n### {key.upper()} ###")
        if isinstance(value, list):
            for item in value[:15]:
                print("-", item)
            print("... (truncated)")
        elif isinstance(value, dict):
            for k, v in value.items():
                print(f"{k}: {str(v)[:150]}")
        else:
            print(str(value)[:5000])
