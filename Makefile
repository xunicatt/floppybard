TARGET:=floppybard
CC:=gcc
CSTD:=-std=c99

CFLAGS:= \
	-Wall \
	-Werror \
	-Wextra \
	-Iinclude \
	-O3 \

LDFLAGS:= \

# sdl2
SDL2_CFLAGS:=$(shell pkg-config --cflags sdl2)
SDL2_LDFLAGS:=$(shell pkg-config --libs sdl2)

# sdl2_ttf
SDL2_TTF_CFLAGS:=$(shell pkg-config --cflags SDL2_ttf)
SDL2_TTF_LDFLAGS:=$(shell pkg-config --libs SDL2_ttf)

# sdl2_image
SDL2_IMAGE_CFLAGS:=$(shell pkg-config --cflags SDL2_image)
SDL2_IMAGE_LDFLAGS:=$(shell pkg-config --libs SDL2_image)

# source files
SRCS:= \
	main.c \
	src/loaders.c \
	src/pipepair.c \
	src/base.c \
	src/bird.c \
	src/game.c \

# objs generated from source files
OBJS:=$(SRCS:.c=.o)
# deps generated from source files
DEPS:=$(SRCS:.c=.d)

CFLAGS:= \
	$(CFLAGS) \
	$(SDL2_CFLAGS) \
	$(SDL2_TTF_CFLAGS) \
	$(SDL2_IMAGE_CFLAGS) \
	$(CSTD) \

LDFLAGS:= \
	$(LDFLAGS) \
	$(SDL2_LDFLAGS) \
	$(SDL2_TTF_LDFLAGS) \
	$(SDL2_IMAGE_LDFLAGS) \

.PHONY: all run clean

%.o: %.c
	@echo "Compiling: $< ->$@"
	@$(CC) $(CFLAGS) -c -o $@ $< -MD

$(TARGET): $(OBJS)
	@echo "Linking: $@"
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -MD

all: $(TARGET)

run: $(TARGET)
	@./$(TARGET)

clean:
	@rm -f $(TARGET) $(OBJS) $(DEPS)
	@echo "Cleaned"

-include $(DEPS)

