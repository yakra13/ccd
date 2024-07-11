# gcc -pthread -c threadpool.c
# gcc -pthread -o thread_pool_example concurrency.c threadpool.o

CC=gcc
OUT=run_example
LIB_TP=threadpool.c
OBJ_TP=threadpool.o
MAIN=concurrency.c

make: $(LIB_TP) $(MAIN)
	$(CC) -Wall -Wfatal-errors -pthread -c $(LIB_TP)
	$(CC) -Wall -Wfatal-errors -pthread -o $(OUT) $(MAIN) $(OBJ_TP)
