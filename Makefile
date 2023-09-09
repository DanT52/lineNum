# Compiler
CC = gcc

# Source files and object files
SRCS = lineNum.c main.c
OBJS = $(SRCS:.c=.o)

# Target binary name
TARGET = lineNum

# Default target: all
all: $(TARGET)

# Linking the object files to produce the target
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

# Compiling the source files
%.o: %.c
	$(CC) -c $< -o $@

# Phony targets
.PHONY: clean run

# Clean target
clean:
	rm -f $(OBJS) $(TARGET)

# Run target
run: $(TARGET)
	./$(TARGET) little webster_16 16
