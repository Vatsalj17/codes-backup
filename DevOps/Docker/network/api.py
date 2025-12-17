import requests
import json

def fetch_random_cat_fact():
    url = "https://meowfacts.herokuapp.com/"
    try:
        response = requests.get(url)
        response.raise_for_status()
        fact = response.text
        return fact
    except requests.exceptions.RequestException as e:
        print(f"An error occurred: {e}")
    return None

def main():
    fact = fetch_random_cat_fact()
    if fact:
        print(json.dumps(json.loads(fact), indent=1))
    else:
        print("Failed to fetch a cat fact.")

if __name__ == "__main__":
    main()
