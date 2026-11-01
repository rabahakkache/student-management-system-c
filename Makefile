CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Iinclude
TARGET = student_manager
SOURCES = src/main.c src/student.c src/storage.c

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SOURCES) include/student.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe students.dat
