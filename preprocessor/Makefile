CC = gcc
OBJS = preprocessor.c
FLEX = ../flex.l
OUT = prepro

compile: $(OBJS)
	$(CC) -o $(OUT) $(OBJS) 

flex: $(FLEX)
	rm -f lex.yy.c
	lex $(FLEX)

debug: $(OBJS)
	$(CC) -g -o $(OUT) $(OBJS)
	gdb $(OUT)

all:
	rm -f lex.yy.c
	lex $(FLEX)
	$(CC) -o $(OUT) $(OBJS) 

run:
	./$(OUT)
