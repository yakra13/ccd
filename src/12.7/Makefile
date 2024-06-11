CC=gcc
OUT_CLIENT=client
OUT_SERVER=server
CLIENT=client.c
SERVER=networking.c

make: $(SERVER) $(CLIENT)
	$(CC) -Wall -Wfatal-errors -o $(OUT_CLIENT) $(CLIENT)
	$(CC) -Wall -Wfatal-errors -o $(OUT_SERVER) $(SERVER)