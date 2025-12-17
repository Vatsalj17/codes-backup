import json
import os

def load_data():
    try:
        with open('youtube.txt', 'r') as file:
            test = json.load(file)
            # print(type(test))
            return test
    except FileNotFoundError:
        return []

def save_data_helper(videos):
    with open('youtube.txt', 'w') as file:
        json.dump(videos, file)

def list_all_videos(videos):
    width = os.get_terminal_size().columns
    print('*' * width)
    for index, video in enumerate(videos, start = 1):
        print(f"{index}. {video['name']}, Duration: {video['duration']}")
    print()
    print('*' * width)

def add_video(videos):
    name = input("Enter video name: ")
    duration = input("Enter video duration: ")
    videos.append({'name': name, 'duration': duration})
    save_data_helper(videos)

def update_video(videos):
    list_all_videos(videos)
    index = int(input("Enter the video number to update: "))
    if 1 <= index <= len(videos):
        name = input("Enter the video name: ")
        duration = input("Enter the video duration: ")
        videos[index - 1] = {'name': name, 'duration': duration}
        save_data_helper(videos)
    else:
        print("Invalid index selected")

def delete_video(videos):
    list_all_videos(videos)
    index = int(input("Enter the video number to delete: "))
    if 1 <= index <= len(videos):
        del videos[index - 1]
        save_data_helper(videos)
    else:
        print("Invalid index selected")

def main():
    videos = load_data()
    while True:
        print("\nYoutube Manager | choose an option ")
        print("1. List all youtube videos")
        print("2. Add a youtube video")
        print("3. Update a youtube video detail")
        print("4. Delete a youtube video")
        print("5. Exit the app")
        choice = input("Enter your choice: ")
        # print(videos)

        match choice:
            case "1":
                list_all_videos(videos)
            case "2":
                add_video(videos)
            case "3":
                update_video(videos)
            case "4":
                delete_video(videos)
            case "5":
                break
            case _:
                print("Invalid Input!\nTry again :(")

if __name__ == "__main__":
    main()
