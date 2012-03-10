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

test_upload_file:
	g++ -g -I$(INCLUDE) -I$(CLIENT_DIR) \
	client/upload_file.cpp client/config.cpp $(SHARE_CPP) \
	test/test_upload.cpp -o ./bin/test_upload -lpthread
