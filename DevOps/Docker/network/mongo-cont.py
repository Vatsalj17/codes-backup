import os
from pymongo import MongoClient

try:
    client = MongoClient("mongodb://mongod:27017/", serverSelectionTimeoutMS=5000)
    client.admin.command('ping')
except Exception as e:
    print(f"Couldn't connect: {e}")
    client = None

if client:
    print("Connected to mongodb")
    db = client["ytmanger"]
    video_collection = db["videos"]

def list_all_videos():
    width = os.get_terminal_size().columns
    print("\nVideo List:")
    print('-' * width)
    for video in video_collection.find():
        print(f"{video['serial']}. Name: \"{video['name']}\" and Duration: {video['duration']}")
    print('-' * width)

def add_video():
    name = input("Enter video name: ")
    duration = input("Enter video duration: ")
    serial_num = video_collection.estimated_document_count() + 1
    video_collection.insert_one({"serial": serial_num, "name": name, "duration": duration})

def update_video():
    list_all_videos()
    index = int(input("Enter the video number to update: "))
    row_count = video_collection.estimated_document_count()
    if 1 <= index <= row_count:
        name = input("Enter the video name: ")
        duration = input("Enter the video duration: ")
        video_collection.update_one(
            {'serial': index},
            {"$set": {"name": name, "duration": duration}}
        )
    else:
        print("Invalid index selected")

def delete_video():
    list_all_videos()
    index = int(input("Enter the video number to delete: "))
    row_count = video_collection.estimated_document_count()
    if 1 <= index <= row_count:
        video_collection.delete_one({"serial": index})
    else:
        print("Invalid index selected")

def main():
    while True:
        print("\nYoutube Manager | choose an option ")
        print("1. List all youtube videos")
        print("2. Add a youtube video")
        print("3. Update a youtube video detail")
        print("4. Delete a youtube video")
        print("5. Exit the app")
        choice = input("Enter your choice: ")

        match choice:
            case "1":
                list_all_videos()
            case "2":
                add_video()
            case "3":
                update_video()
            case "4":
                delete_video()
            case "5":
                break
            case _:
                print("Invalid Input!\nTry again :(")

if __name__ == "__main__":
    if client:
        main()
        client.close()
