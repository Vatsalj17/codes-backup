import tkinter as tk
from tkinter import font as tkfont
import random
import time

class TypingSpeedTest:
    def __init__(self, root):
        self.root = root
        self.root.title("Typing Speed Test")
        self.root.geometry("900x700")
        self.root.resizable(False, False)
        
        self.sample_texts = [
            "The quick brown fox jumps over the lazy dog near the riverbank.",
            "Programming is the art of telling another human what one wants the computer to do.",
            "Practice makes perfect when it comes to improving your typing speed and accuracy.",
            "Technology has changed the way we communicate and interact with the world.",
            "Every great developer you know got there by solving problems they were unqualified to solve.",
            "The only way to learn a new programming language is by writing programs in it.",
            "Good code is its own best documentation as you are about to add a comment.",
        ]
        
        self.current_text = ""
        self.start_time = None
        self.is_running = False
        
        self.setup_ui()
        self.reset_test()
        
    def setup_ui(self):
        bg_color = "#0f0f1e"
        self.root.configure(bg=bg_color)
        
        main_frame = tk.Frame(self.root, bg=bg_color)
        main_frame.pack(expand=True, fill="both", padx=40, pady=40)
        
        title_font = tkfont.Font(family="Helvetica", size=36, weight="bold")
        title = tk.Label(main_frame, text="Typing Speed Test", 
                        font=title_font, fg="#00d4ff", bg=bg_color)
        title.pack(pady=(0, 10))
        
        subtitle_font = tkfont.Font(family="Helvetica", size=12)
        subtitle = tk.Label(main_frame, text="Test your typing speed and accuracy", 
                           font=subtitle_font, fg="#8b8b9f", bg=bg_color)
        subtitle.pack(pady=(0, 30))
        
        stats_frame = tk.Frame(main_frame, bg=bg_color)
        stats_frame.pack(pady=(0, 30))
        
        self.wpm_label = self.create_stat_card(stats_frame, "WPM", "0", 0)
        self.accuracy_label = self.create_stat_card(stats_frame, "Accuracy", "100%", 1)
        self.time_label = self.create_stat_card(stats_frame, "Time", "0s", 2)
        
        text_container = tk.Frame(main_frame, bg="#1a1a2e", highlightbackground="#00d4ff", highlightthickness=2, bd=0)
        text_container.pack(pady=(0, 20), fill="x")
        
        inner_frame = tk.Frame(text_container, bg="#1a1a2e")
        inner_frame.pack(padx=3, pady=3, fill="both", expand=True)
        
        text_font = tkfont.Font(family="Consolas", size=16)
        self.sample_label = tk.Label(inner_frame, text="", font=text_font, fg="#e0e0e0", bg="#1a1a2e", wraplength=780, justify="left", pady=20, padx=20)
        self.sample_label.pack()
        
        input_container = tk.Frame(main_frame, bg="#1a1a2e", highlightbackground="#00d4ff", highlightthickness=2, bd=0)
        input_container.pack(pady=(0, 20), fill="x")
        
        input_font = tkfont.Font(family="Consolas", size=16)
        self.input_text = tk.Text(input_container, height=4, font=input_font, bg="#1a1a2e", fg="#ffffff", insertbackground="#00d4ff", relief="flat", padx=20, pady=20, wrap="word", selectbackground="#00d4ff", selectforeground="#0f0f1e")
        self.input_text.pack(padx=3, pady=3)
        self.input_text.bind("<KeyRelease>", self.on_key_release)
        
        button_frame = tk.Frame(main_frame, bg=bg_color)
        button_frame.pack()
        
        self.reset_btn = tk.Button(button_frame, text="🔄 New Test", 
                                   command=self.reset_test,
                                   font=("Helvetica", 14, "bold"),
                                   bg="#00d4ff", fg="#0f0f1e",
                                   activebackground="#00b8e6",
                                   activeforeground="#0f0f1e",
                                   relief="flat", padx=30, pady=12,
                                   cursor="hand2", bd=0)
        self.reset_btn.pack(side="left", padx=10)
        
        result_font = tkfont.Font(family="Helvetica", size=14, weight="bold")
        self.result_label = tk.Label(main_frame, text="", font=result_font, 
                                     fg="#00ff88", bg=bg_color)
        self.result_label.pack(pady=(20, 0))
        
    def create_stat_card(self, parent, title, value, column):
        card = tk.Frame(parent, bg="#1a1a2e", highlightbackground="#2a2a3e", 
                       highlightthickness=2, bd=0)
        card.grid(row=0, column=column, padx=15)
        
        inner = tk.Frame(card, bg="#1a1a2e")
        inner.pack(padx=25, pady=20)
        
        title_label = tk.Label(inner, text=title, font=("Helvetica", 12), 
                              fg="#8b8b9f", bg="#1a1a2e")
        title_label.pack()
        
        value_label = tk.Label(inner, text=value, font=("Helvetica", 28, "bold"), 
                              fg="#00d4ff", bg="#1a1a2e")
        value_label.pack()
        
        return value_label
        
    def reset_test(self):
        self.current_text = random.choice(self.sample_texts)
        self.sample_label.config(text=self.current_text)
        self.input_text.delete("1.0", "end")
        self.start_time = None
        self.is_running = False
        self.wpm_label.config(text="0")
        self.accuracy_label.config(text="100%")
        self.time_label.config(text="0s")
        self.result_label.config(text="")
        self.input_text.focus()
        
    def on_key_release(self, _):
        if not self.is_running and self.input_text.get("1.0", "end-1c"):
            self.start_time = time.time()
            self.is_running = True
            
        if self.is_running:
            self.update_stats()
            
    def update_stats(self):
        typed_text = self.input_text.get("1.0", "end-1c")
        
        if not typed_text or self.start_time is None:
            return
            
        elapsed_time = time.time() - self.start_time
        self.time_label.config(text=f"{int(elapsed_time)}s")
        
        words_typed = len(typed_text.split())
        minutes = elapsed_time / 60
        wpm = int(words_typed / minutes) if minutes > 0 else 0
        self.wpm_label.config(text=str(wpm))
        
        correct_chars = 0
        for i, char in enumerate(typed_text):
            if i < len(self.current_text) and char == self.current_text[i]:
                correct_chars += 1
                
        accuracy = int((correct_chars / len(typed_text)) * 100) if typed_text else 100
        self.accuracy_label.config(text=f"{accuracy}%")
        
        if typed_text == self.current_text:
            self.is_running = False
            self.result_label.config(
                text=f"✓ Complete! {wpm} WPM with {accuracy}% accuracy in {int(elapsed_time)}s"
            )

if __name__ == "__main__":
    root = tk.Tk()
    app = TypingSpeedTest(root)
    root.mainloop()
