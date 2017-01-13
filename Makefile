all:
	gcc spyfall_client.c -o spyfall_client
	gcc spyfall_server.c -o spyfall_server
	gcc spyfall_networking.c -o spyfall_networking

clean:
	rm *~
