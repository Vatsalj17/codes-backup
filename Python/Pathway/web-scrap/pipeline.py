import pathway as pw
import threading
import os
from scraper import UniversalScraper

# -------------------------------------------------------------
# PART 1: THE DATA PRODUCER
# -------------------------------------------------------------
def live_scraper_daemon(urls: list[str], output_file: str):
    if os.path.exists(output_file):
        os.remove(output_file)

    for url in urls:
        try:
            scraper = UniversalScraper(url, js=True)
            scraper.scrape()
            scraper.save_to_stream(output_file)
            print(f"[Daemon] Scraped {url} -> Appended to stream.")
        except Exception as e:
            print(f"[Daemon] Error scraping {url}: {e}")
        
    # Keep thread alive to simulate a long-running background service
    import time
    while True:
        time.sleep(10)

# -------------------------------------------------------------
# PART 2: THE PATHWAY PIPELINE
# -------------------------------------------------------------
class ScraperSchema(pw.Schema):
    url: str
    full_text: str
    page_title: str
    timestamp: float

def run_pipeline():
    data_file = "stream_data.jsonl"
    
    target_urls = [
        "https://news.ycombinator.com",
        "https://archlinux.org",
        "https://kernel.org",
        "https://github.com/vatsalj17",
        "https://python.org",
        "https://rust-lang.org",
        "https://djangoproject.com",
        "https://flask.palletsprojects.com",
        "https://fastapi.tiangolo.com",
        "https://djangoproject.com/download/",
        "https://wikipedia.org",
        "https://leetcode.com",
        "https://geeksforgeeks.org",
        "https://linkedin.com/in/vatsal17",
    ]

    # FIX 2: Correct argument is 'daemon', not 'target_daemon'
    # 'daemon=True' ensures this thread dies when the main program exits.
    t = threading.Thread(daemon=True, target=live_scraper_daemon, args=(target_urls, data_file))
    t.start()

    # Define Input Stream
    t_raw = pw.io.jsonlines.read(
        data_file,
        schema=ScraperSchema,
        mode="streaming"
    )

    # FIX 3: Pathway 0.27.0 doesn't use flat_map in pw.apply.
    # Instead, we split the string into a LIST, then use .flatten() on the TABLE.
    
    # Step A: Split text into a list of words (returns a column of lists)
    # We use pw.apply to run the Python split() function on every row.
    tokenized = t_raw.select(
        word_list=pw.apply(lambda x: x.split(), t_raw.full_text)
    )

    # Step B: Flatten the list column (Explode/Unnest)
    # This transforms 1 row with [a, b, c] into 3 rows: [a], [b], [c]
    words = tokenized.flatten(tokenized.word_list)

    # Step C: Select and rename the flattened column for grouping
    words = words.select(word=words.word_list)

    # Count occurrences (Map-Reduce style)
    word_counts = words.groupby(words.word).reduce(
        count=pw.reducers.count()
    )

    # Filter for interesting words
    top_words = word_counts.filter(word_counts.count > 3)

    # Output
    pw.io.csv.write(top_words, "output_analytics.csv")
    
    print("[Pathway] Pipeline started. Watching for data...")
    pw.run()

if __name__ == "__main__":
    run_pipeline()
