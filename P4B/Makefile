# This is the makefile that generates the executable

#CFLAGS = -Wall -Werror -g
#CFLAGS = -Wall -g 
CFLAGS = -Wall -g -DDEBUG=0 -DDEBUGPTH=1
LFLAGS = -lm -lpthread

FILES_C = main.c view.c file-parser.c file-list.c linked-list.c hash-list.c red-black-tree.c processer.c indexer.c

TARGET = practica4

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
