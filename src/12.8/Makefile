CC=gcc
OUT_CLIENT=sendrecv_client
OUT_SERVER=sendrecv_server
CLIENT=client.c
SERVER=sendrecv.c

make: $(SERVER) $(CLIENT)
	$(CC) -Wall -Wfatal-errors -o $(OUT_CLIENT) $(CLIENT)
	$(CC) -Wall -Wfatal-errors -o $(OUT_SERVER) $(SERVER)