CC = gcc
OBJS = scanner.c lex.yy.c
FLEX = flex.l
OUT = scan

compile: $(OBJS)
	$(CC) -o $(OUT) $(OBJS) 

flex: $(FLEX)
	rm -f lex.yy.c
	lex $(FLEX)

debug: $(OBJS)
	$(CC) -g -o $(OUT) $(OBJS)
	gdb $(OUT)

run:
	./$(OUT)
