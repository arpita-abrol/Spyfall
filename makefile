all: server client

server: spyfall_server.o networking.o
	gcc -o server spyfall_server.o networking.o

client: spyfall_client.o networking.o
	gcc -o client spyfall_client.o networking.o

server.o: spyfall_server.c networking.h
	gcc -c spyfall_Server.c

client.o: spyfall_client.c networking.h
	gcc -c spyfall_client.c

networking.o: networking.c networking.h
	gcc -c networking.c

clean:
	rm *.o
	rm *~