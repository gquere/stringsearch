CC	= gcc
CFLAGS	= -fPIC -O2
LDFLAGS	= -shared

TARGET = libstrstr.so
SOURCES = $(shell echo *.c)
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

clean:
	rm *.o *.so
