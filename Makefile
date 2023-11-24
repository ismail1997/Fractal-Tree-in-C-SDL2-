
CC = gcc
CFLAGS = -Wall -Wextra -I C:\devtools\SDL2\include
LDFLAGS = -L C:\devtools\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows

SRC_DIR = src
BIN_DIR = bin
ASSETS_DIR = assets

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))
ASSETS = $(wildcard $(ASSETS_DIR)/*)

# The main target
all: $(BIN_DIR)/prog

# Rule to build the executable
$(BIN_DIR)/prog: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule to copy assets to bin directory
$(BIN_DIR)/%: $(ASSETS_DIR)/%
	cp $< $@

# Phony target to clean the project
.PHONY: clean
clean:
	del /Q $(BIN_DIR)\*.o $(BIN_DIR)\*.exe

# Phony target to run the program
.PHONY: run
run: all
	./$(BIN_DIR)/prog


