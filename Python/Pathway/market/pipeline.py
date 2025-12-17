import warnings
warnings.filterwarnings("ignore", category=UserWarning, module='pkg_resources')

import pathway as pw
import threading
import time
import os
from textblob import TextBlob
from typing import Any
from scraper import UniversalScraper

def live_scraper_daemon(urls: list[str], output_file: str):
    if os.path.exists(output_file):
        os.remove(output_file)

    # Infinite loop to keep generating live data for the demo
    while True:
        for url in urls:
            try:
                scraper = UniversalScraper(url, js=True) # JS mode for robust scraping
                scraper.scrape()
                scraper.save_to_stream(output_file)
                print(f"[Daemon] Scraped {url}")
            except Exception as e:
                print(f"[Error] {url}: {e}")
            time.sleep(5) # Wait 5s between sites

class NewsSchema(pw.Schema):
    url: str
    full_text: str
    page_title: str
    timestamp: float

# -------------------------------------------------------------
# THE FIX: Use @pw.udf instead of pw.apply
# -------------------------------------------------------------
@pw.udf
def get_sentiment_score(text: str) -> float:
    # We cast to Any to satisfy Pyright, but the -> float above
    # tells Pathway's Rust engine exactly what memory to allocate.
    blob: Any = TextBlob(text)
    try:
        return float(blob.sentiment[0])
    except Exception:
        return 0.0

def run_pipeline():
    data_file = "stream_data.jsonl"
    
    # ... [Keep thread starting logic EXACTLY as before] ...
    
    # We target high-velocity news sites for this demo
    targets = [
        "https://techcrunch.com",
        "https://www.theverge.com",
        "https://news.ycombinator.com",
    ]

    # Start the Scraper in background
    t = threading.Thread(daemon=True, target=live_scraper_daemon, args=(targets, data_file))
    t.start()

    # 1. Read Stream
    t_raw = pw.io.jsonlines.read(
        data_file,
        schema=NewsSchema,
        mode="streaming"
    )

    # 1. Read Stream
    t_raw = pw.io.jsonlines.read(
        data_file,
        schema=NewsSchema,
        mode="streaming"
    )

    # 2. High-Level Logic: Apply the UDF
    # Notice we call the function directly! The @pw.udf decorator 
    # intercepts this call and inserts it into the dataflow graph.
    processed = t_raw.select(
        url=t_raw.url,
        title=t_raw.page_title,
        timestamp=t_raw.timestamp,
        sentiment_score=get_sentiment_score(t_raw.full_text)
    )

    # 3. Aggregation (Now works because sentiment_score is strictly float)
    significant_news = processed.filter(processed.sentiment_score != 0.0)

    pw.io.csv.write(significant_news, "dashboard_feed.csv")
    print("--- TrendPulse Engine Running ---")
    pw.run()

if __name__ == "__main__":
    run_pipeline()
