# CFLAGS
CC:= gcc
CROSS_COMPILE:=
CFLAGS:= -Wall

# Source files and target name
SRC = writer.c
TARGET = writer

# Default target
default: $(TARGET)

# Build the writer application
$(TARGET): $(SRC)
	$(CROSS_COMPILE)$(CC) -o $@ $^ $(CFLAGS) 

# Clean target
clean:
	rm -f $(TARGET) *.o

.PHONY: default clean