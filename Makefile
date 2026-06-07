CC = gcc

CFLAGS = -Wall -Wextra -Iinclude

LIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

BUILD_DIR = build

TARGET = main

SRC = \
	src/main.c \
	src/game.c \
	src/map.c \
	src/player.c \
	src/render.c

OBJ = \
	$(BUILD_DIR)/main.o \
	$(BUILD_DIR)/game.o \
	$(BUILD_DIR)/map.o \
	$(BUILD_DIR)/player.o \
	$(BUILD_DIR)/render.o

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: src/main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/game.o: src/game.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/map.o: src/map.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/player.o: src/player.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/render.o: src/render.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

level1: $(TARGET)
	./$(TARGET) map/level1.txt

level2: $(TARGET)
	./$(TARGET) map/level2.txt

level3: $(TARGET)
	./$(TARGET) map/level3.txt


clean:
	rm -rf $(BUILD_DIR)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re level1 level2 level3 level4 level5 valgrind