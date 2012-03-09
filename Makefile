INCLUDE = ./include
CLIENT_DIR = client
CLIENT_CPP = $(CLIENT_DIR)/*.cpp
SHARE_CPP = $(INCLUDE)/*.cpp
p2p_client:
	g++ -g -I$(INCLUDE)  $(CLIENT_CPP) $(SHARE_CPP) -o ./bin/clientc -lpthread
	g++ -g -I$(INCLUDE) -D__CLIENT_DAEMON__  $(CLIENT_CPP) $(SHARE_CPP) -o ./bin/clientd -lpthread
p2p_client_debug:
	g++ -g -I$(INCLUDE) -D__DEBUG__  $(CLIENT_CPP) $(SHARE_CPP) -o ./bin/clientc -lpthread
	g++ -g -I$(INCLUDE) -D__DEBUG__  -D__CLIENT_DAEMON__ $(CLIENT_CPP) $(SHARE_CPP) -o ./bin/clientd -lpthread
