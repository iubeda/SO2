# This is the makefile that generates the executable

#CFLAGS = -Wall -Werror -g
CFLAGS = -g
LFLAGS = -lm

FILES_C = main.c file-parser.c file-list.c linked-string-list.h

TARGET = practica2

# There is no need to change the instructions below this
# line

FILES_O = $(subst .c,.o,$(FILES_C))

$(TARGET): $(FILES_O) Makefile
	gcc $(FILES_O) -o $(TARGET) $(LFLAGS) 

%.o: %.c Makefile 
	gcc $(CFLAGS) -c $<

all: $(TARGET) 

clean:
	/bin/rm $(FILES_O) $(TARGET) 
