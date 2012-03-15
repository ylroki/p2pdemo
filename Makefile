INCLUDE = ./include
CLIENT_DIR = client
SERVER_DIR = server
CLIENT_CPP = $(CLIENT_DIR)/*.cpp
SERVER_CPP = $(SERVER_DIR)/*.cpp
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

p2p_server:
	g++ -g -I$(INCLUDE) $(SERVER_CPP) $(SHARE_CPP) -o ./bin/server

test_file_system:
	g++ -g -I$(INCLUDE) -I$(CLIENT_DIR) \
	client/file_system.cpp client/config.cpp $(SHARE_CPP) \
	test/test_file_system.cpp -o ./bin/test_file_system -lpthread -lsqlite3
