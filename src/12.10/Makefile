CC=gcc
OPOLL=poll
OSELECT=select
POLL=poll.c
SELECT=select.c

make: $(SERVER) $(CLIENT)
	$(CC) -Wall -Wfatal-errors -o $(OPOLL) $(POLL)
	$(CC) -Wall -Wfatal-errors -o $(OSELECT) $(SELECT)