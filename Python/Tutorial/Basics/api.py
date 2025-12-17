import requests, json

url = "https://api.freeapi.app/api/v1/public/randomjokes"
querystring = {"limit":"2","query":"science","inc":"categories%2Cid%2Ccontent","page":"1"}
headers = {"accept": "application/json"}

response = requests.get(url, headers=headers, params=querystring)
data = response.json()

json_data = json.dumps(data, indent=4)
# print(json_data)

if data["success"] and "data" in data:
    real_data = data["data"]
    joke = real_data["data"][1]["content"]
    print(f"joke: {joke}")
else:
    raise Exception("Failed to fetch user data")
