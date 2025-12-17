import tkinter as tk
from tkinter import messagebox

class MyGUI:
    def __init__(self) -> None:
        self.root = tk.Tk()

        self.menubar = tk.Menu(self.root)
        self.filemenu = tk.Menu(self.menubar, tearoff=0)
        self.filemenu.add_command(label="Close", command=self.on_closing)
        self.filemenu.add_command(label="Force Close", command=exit)

        self.actionmenu = tk.Menu(self.menubar, tearoff=0)
        self.actionmenu.add_command(label="Show Message", command=self.show_message)
        self.actionmenu.add_command(label="Clear", command=self.clear)

        self.menubar.add_cascade(menu=self.filemenu, label="File")
        self.menubar.add_cascade(menu=self.actionmenu, label="Action")
        self.root.config(menu=self.menubar)

        self.label = tk.Label(self.root, text="Hello", font=('Ariel', 18))
        self.label.pack(padx=10, pady=10)

        self.textbox = tk.Text(self.root, height=5, font=('Ariel', 16))
        self.textbox.bind("<KeyPress>", self.shortcut)
        self.textbox.pack(padx=10, pady=10)

        self.check_state = tk.IntVar()

        self.check = tk.Checkbutton(self.root, text="Show Messagebox", font=('Ariel', 16), variable=self.check_state)
        self.check.pack(padx=10, pady=10)

        self.button = tk.Button(self.root, text="Show Message", font=('Ariel', 16), command=self.show_message)
        self.button.pack(padx=10, pady=10)

        self.clearbtn = tk.Button(self.root, text="Clear", font=('Ariel', 16), command=self.clear)
        self.clearbtn.pack(padx=10, pady=10)

        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)
        self.root.mainloop()

    def show_message(self) -> None:
        if self.check_state.get():
            messagebox.showinfo(title="Message", message=self.textbox.get("1.0", tk.END))
        else:
            print(self.textbox.get("1.0", tk.END), end="")

    def shortcut(self, event):
        if event.state == 4 and event.keysym == "Return":
            self.show_message()

    def on_closing(self):
        if messagebox.askyesno(title="Quit?", message="Kya tum sahi mein jaana chahte ho?"):
            self.root.destroy()

    def clear(self):
        self.textbox.delete('1.0', tk.END)

if __name__ == "__main__":
    app = MyGUI()
