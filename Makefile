NAME=app
BUILD_PATH=./build
SRC_PATH=./src
CC=gcc
CFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf

all:
	if [ ! -d "$(BUILD_PATH)" ]; then mkdir $(BUILD_PATH); fi
	$(CC) -o $(BUILD_PATH)/$(NAME) $(SRC_PATH)/*.c $(CFLAGS)

run:
	$(BUILD_PATH)/$(NAME)

hotreload:
	if [ ! -d "$(BUILD_PATH)" ]; then mkdir $(BUILD_PATH); fi
	$(CC) -o $(BUILD_PATH)/$(NAME) $(SRC_PATH)/*.c $(CFLAGS)
	$(BUILD_PATH)/$(NAME)

clean:
	rm -rf $(BUILD_PATH)
