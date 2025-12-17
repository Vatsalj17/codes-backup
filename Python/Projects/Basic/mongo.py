from pymongo import MongoClient

client = MongoClient("mongodb+srv://vatsaljaiswal17_db_user:efviqBNDspNAJqD6@clustertest.wlkxiiy.mongodb.net/?retryWrites=true&w=majority&appName=ClusterTest")
db = client["ytmanger"]
video_collection = db["videos"]
print(video_collection)
