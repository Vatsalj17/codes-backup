import streamlit as st
import pandas as pd
import time
import altair as alt

st.set_page_config(page_title="TrendPulse AI", layout="wide")

# Title and Hero Section
st.title("⚡ TrendPulse: Real-Time Sentiment Intelligence")
st.markdown("""
This system monitors tech news sources in real-time, uses **NLP** to calculate sentiment, 
and visualizes the 'Mood of the Web' as data streams in.
""")

# Placeholders for live data
col1, col2 = st.columns(2)
with col1:
    metric_ph = st.empty() # Placeholder for big number
with col2:
    status_ph = st.empty() # Placeholder for status text

chart_ph = st.empty()
dataframe_ph = st.empty()

csv_file = "dashboard_feed.csv"

def load_data():
    try:
        df = pd.read_csv(csv_file, names=["url", "title", "timestamp", "sentiment"], header=None)
        return df
    except Exception:
        # ERROR FIX: Explicitly create a pd.Index object to satisfy strict typing
        return pd.DataFrame(columns=pd.Index(["url", "title", "timestamp", "sentiment"]))

# The "Game Loop" - Reruns every 2 seconds
while True:
    df = load_data()
    
    if not df.empty:
        # Clean up data
        df["sentiment"] = pd.to_numeric(df["sentiment"], errors='coerce')
        df = df.dropna()
        
        # Calculate recent average
        avg_sentiment = df["sentiment"].tail(10).mean()
        
        # 1. Update Metrics
        with metric_ph.container():
            delta_color = "normal"
            if avg_sentiment > 0.1: delta_color = "normal" # Greenish default
            elif avg_sentiment < -0.1: delta_color = "inverse" # Red
            
            st.metric(
                label="Current Market Mood (Live Window)", 
                value=f"{avg_sentiment:.4f}",
                delta="Positivity Index" if avg_sentiment > 0 else "Negativity Spike"
            )

        # 2. Update Chart
        chart_data = df.tail(50).reset_index()
        
        chart = alt.Chart(chart_data).mark_line(point=True).encode(
            # FIX: Change 'index' to 'index:Q'
            # This tells Altair: "Trust me, this is a Number, not a string or category."
            x=alt.X('index:Q', title='Event Sequence'),
            
            y=alt.Y('sentiment', scale=alt.Scale(domain=[-1, 1]), title='Sentiment Score'),
            tooltip=['title', 'sentiment', 'url'],
            color=alt.condition(
                alt.datum.sentiment > 0,
                alt.value("green"),
                alt.value("red")
            )
        ).properties(
            height=400,
            title="Live Sentiment Stream"
        ).interactive()
        
        chart_ph.altair_chart(chart, use_container_width=True)

        # 3. Update Data Table (Recent News)
        with dataframe_ph.container():
            st.subheader("Recent Signals")
            # Show just title and score, make URL clickable if we had more logic
            st.dataframe(
                df.tail(10)[["title", "sentiment", "url"]].sort_index(ascending=False),
                use_container_width=True
            )
            
    else:
        status_ph.warning("Waiting for data stream...")

    time.sleep(2)
