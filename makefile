CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# List of source files
SRCS = main.c StrList.c

# List of object files
OBJS = $(SRCS:.c=.o)

# Executable name
EXEC = StrList

# Target for building the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Rule for building object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Target to clean up the project (remove object files and executable)
clean:
	rm -f $(OBJS) $(EXEC)
