# ChadSh Makefile - Building sigma energy since day 1
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = chadsh
SRCDIR = src
SOURCES = $(SRCDIR)/main.c $(SRCDIR)/parser.c $(SRCDIR)/builtins.c $(SRCDIR)/executor.c
OBJECTS = $(SOURCES:.c=.o)
INSTALL_DIR = /usr/local/bin

# Colors for that extra drip
GREEN = \033[0;32m
BLUE = \033[0;34m
RESET = \033[0m

.PHONY: all clean install uninstall help

# Default target (the sigma build)
all: $(TARGET)
	@echo "$(GREEN)✅ ChadSh built successfully! Ready to drop bars 🔥$(RESET)"

# Build the shell (where magic happens)
$(TARGET): $(OBJECTS)
	@echo "$(BLUE)🔗 Linking the sigma energy...$(RESET)"
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile source files
%.o: %.c $(SRCDIR)/memes.h
	@echo "$(BLUE)⚡ Compiling $< (no cap)...$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

# Install to system (become the main character)
install: $(TARGET)
	@echo "$(GREEN)📦 Installing ChadSh to $(INSTALL_DIR)...$(RESET)"
	sudo cp $(TARGET) $(INSTALL_DIR)/
	sudo chmod +x $(INSTALL_DIR)/$(TARGET)
	@echo "$(GREEN)🎉 ChadSh installed! Type 'chadsh' to start the grind$(RESET)"

# Remove from system (sad but necessary)
uninstall:
	@echo "Removing ChadSh from $(INSTALL_DIR)..."
	sudo rm -f $(INSTALL_DIR)/$(TARGET)
	@echo "ChadSh uninstalled (we'll miss you king) 😢"

# Clean build files (spring cleaning)
clean:
	@echo "🧹 Cleaning up build files..."
	rm -f $(OBJECTS) $(TARGET)
	@echo "Build cleaned (fresh start energy)"

# Debug build (for when things get sus)
debug: CFLAGS += -g -DDEBUG
debug: $(TARGET)
	@echo "$(GREEN)🐛 Debug build ready (time to investigate)$(RESET)"

# Help menu (getting that assistance)
help:
	@echo "$(BLUE)🔥 ChadSh Build Commands 🔥$(RESET)"
	@echo "  make          - Build ChadSh (default)"
	@echo "  make install  - Install to system (requires sudo)"
	@echo "  make clean    - Remove build files"
	@echo "  make debug    - Build with debug symbols"
	@echo "  make uninstall- Remove from system"
	@echo "  make help     - Show this menu"
	@echo ""
	@echo "$(GREEN)Pro tip: Run 'make && sudo make install' for one-shot setup$(RESET)"
