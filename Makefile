p2p_client:
	g++ -g -I./include client/client.cpp -o ./bin/clientc
	g++ -g -I./include -D__CLIENT_DAEMON__ client/client.cpp -o ./bin/clientd
