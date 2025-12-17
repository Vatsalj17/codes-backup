import pathway as pw
import datetime

# ==========================================
# 1. THE SCHEMA (Data Typing)
# ==========================================
# In low-level systems, you define memory structures. 
# Here, we define the structure of our incoming log stream.
class LogSchema(pw.Schema):
    timestamp: int          # Unix timestamp
    service_name: str       # e.g., "auth-service", "payment-api"
    status_code: int        # HTTP Status: 200, 404, 500
    latency_ms: int         # Request duration

# ==========================================
# 2. THE INPUT (The Connector)
# ==========================================
# We use a JSON line connector. In a real production env, 
# you would swap this for 'pw.io.kafka.read' or 'pw.io.fs.read' (tail -f equivalent).
# "mode='streaming'" tells the Rust engine to keep the pipe open.
log_stream = pw.io.jsonlines.read(
    "./logs/",
    schema=LogSchema,
    mode="streaming"
)

# ==========================================
# 3. THE LOGIC (The Dataflow)
# ==========================================

# Step A: Filter, Cast, and Convert
enriched_logs = log_stream.with_columns(
    # FIX: Explicitly cast the Boolean comparison to an Integer.
    # True -> 1, False -> 0.
    # Now 'pw.reducers.sum' will see a column of Integers, which it loves.
    is_error=pw.cast(pw.this.status_code >= 500, int),
    
    event_time=pw.this.timestamp.dt.from_timestamp(unit="s")
)

# Step B: The Sliding Window (Remains the same as previous fix)
windowed_stats = enriched_logs.windowby(
    pw.this.event_time,
    window=pw.temporal.sliding(
        hop=datetime.timedelta(seconds=1), 
        duration=datetime.timedelta(seconds=10)
    ),
    behavior=pw.temporal.common_behavior(keep_results=True),
    instance=pw.this.service_name
).reduce(
    service_name=pw.reducers.max(pw.this.service_name),
    total_requests=pw.reducers.count(),
    # Now valid: Summing a column of Integers (0s and 1s)
    error_count=pw.reducers.sum(pw.this.is_error)
)

# ==========================================
# 4. THE OUTPUT (The Sink)
# ==========================================
# In production, this would be `pw.io.http.write` to hit a Slack Webhook.
# Here, we dump it to a CSV so you can see the updates live.
pw.io.csv.write(alerts, "alerts_output.csv")

# ==========================================
# 5. EXECUTION (The Engine)
# ==========================================
# This starts the Rust backend. It blocks the main thread.
pw.run()
