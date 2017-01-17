all:
	gcc spyfall_client.c -o spyfall_client
	gcc spyfall_server.c -o spyfall_server
	gcc networking.c -o networking

clean:
	rm *~
