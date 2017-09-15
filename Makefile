CC = gcc
OBJS = scanner.c lex.yy.c
FLEX = flex.l
OUT = scan

compile: $(OBJS)
	$(CC) -o $(OUT) $(OBJS) 

flex: $(FLEX)
	lex $(FLEX)

debug: $(OBJS)
	$(CC) -g -o $(OUT) $(OBJS)
	gdb $(OUT)

run:
	./$(OUT)
