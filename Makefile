CC = gcc
OBJS = scanner.c lex.yy.c
OUT = scan

compile: $(OBJS)
	$(CC) -o $(OUT) $(OBJS) 



debug: $(OBJS)
	$(CC) -g -o $(OUT) $(OBJS)
	gdb $(OUT)

run:
	./$(OUT)
