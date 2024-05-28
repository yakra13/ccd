CC=gcc
OUT_CLIENT=sendrecv_client
OUT_SERVER=sendrecv_server
CLIENT=client.c
SERVER=server.c
LIB_MESSAGE=message.c
OBJ_MESSAGE=message.o

make: $(LIB_MESSAGE) $(SERVER) $(CLIENT)
	$(CC) -Wall -Wfatal-errors -c $(LIB_MESSAGE)
	$(CC) -Wall -Wfatal-errors -o $(OUT_CLIENT) $(CLIENT) $(OBJ_MESSAGE)
	$(CC) -Wall -Wfatal-errors -o $(OUT_SERVER) $(SERVER) $(OBJ_MESSAGE)