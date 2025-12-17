import os
import sqlite3


conn = sqlite3.connect('youtube_videos.db')
cursor = conn.cursor()
cursor.execute('''
    CREATE TABLE IF NOT EXISTS videos (
        id INTEGER PRIMARY KEY,
        name TEXT NOT NULL,
        duration TEXT NOT NULL
    )
''')

def list_all_videos():
    width = os.get_terminal_size().columns
    print('*' * width)
    cursor.execute("SELECT * FROM videos")
    for row in cursor.fetchall():
        print(row)
    print()
    print('*' * width)

def add_video():
    name = input("Enter video name: ")
    duration = input("Enter video duration: ")
    cursor.execute("INSERT INTO videos (name, duration) VALUES (?, ?)", (name, duration))
    conn.commit()

def update_video():
    list_all_videos()
    index = int(input("Enter the video number to update: "))
    cursor.execute("SELECT COUNT(*) FROM videos")
    row_count = cursor.fetchone()[0]
    if 1 <= index <= row_count:
        name = input("Enter the video name: ")
        duration = input("Enter the video duration: ")
        cursor.execute("UPDATE videos SET name = ?, duration = ? WHERE id = ?", (name, duration, index))
        conn.commit()
    else:
        print("Invalid index selected")

def delete_video():
    list_all_videos()
    index = int(input("Enter the video number to delete: "))
    cursor.execute("SELECT COUNT(*) FROM videos")
    row_count = cursor.fetchone()[0]
    if 1 <= index <= row_count:
        cursor.execute("DELETE FROM videos where id = ?", (index,))
        conn.commit()
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

    conn.close()

if __name__ == "__main__":
    main()
