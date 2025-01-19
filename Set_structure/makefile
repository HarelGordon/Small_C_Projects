# Compiler
CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
LIBS = $(wildcard *.h)
# Executable
TARGET = myset

# Default target
all: $(TARGET)

# Compile source files into object files
%.o: %.c $(LIBS)
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJS) $(TARGET)

