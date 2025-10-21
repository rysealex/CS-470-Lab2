# C compiler
CC=gcc

# compile-time flags
CFLAGS=-Wall -g

# target exe name
TARGET=process_man_sim

# build the exe
all:$(TARGET)

# link file into the exe
$(TARGET): $(TARGET).c
		$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c 