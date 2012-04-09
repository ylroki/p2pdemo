SHARE_CPP = include/*.cpp
SERVER_CPP = server/*.cpp
P2P_CLASS_CPP = p2p_class/*.cpp
SSL_DIR = /usr/local/ssl
SSL_INCLUDE = $(SSL_DIR)/include
SSL_LIB = $(SSL_DIR)/lib

p2p_clientc:	
	g++ -g -Iinclude -Ip2p_class -I$(SSL_INCLUDE) -L$(SSL_LIB) -D__DEBUG__ \
		p2p_class/command.cpp p2p_class/config.cpp $(SHARE_CPP) client/clientc.cpp\
		-o bin/clientc -lpthread -lcrypto -lsqlite3
	
p2p_clientd_debug:
	g++ -g -Iinclude -Ip2p_class -I$(SSL_INCLUDE) -L$(SSL_LIB) -D__DEBUG__ \
		$(P2P_CLASS_CPP) $(SHARE_CPP) client/clientd.cpp \
		-o bin/clientd -lpthread -lcrypto -lsqlite3

p2p_client_debug:
	make p2p_clientc
	make p2p_clientd_debug

test_upload_file:
	g++ -g -Iinclude -Ip2p_class -I$(SSL_INCLUDE) -L$(SSL_LIB)\
		p2p_class/upload_file.cpp p2p_class/config.cpp $(SHARE_CPP) test/test_upload.cpp \
		-o bin/test_upload -lpthread -lcrypto -lsqlite3

p2p_server:
	g++ -g -Iinclude -I$(SSL_INCLUDE) -L$(SSL_LIB) \
		$(SERVER_CPP) $(SHARE_CPP) \
		-o bin/server -lcrypto -lsqlite3

p2p_server_debug:
	g++ -g -Iinclude -I$(SSL_INCLUDE) -L$(SSL_LIB) -D__DEBUG__\
		$(SERVER_CPP) $(SHARE_CPP) \
		-o bin/server -lcrypto -lsqlite3

test_file_system:
	g++ -g -Iinclude -Ip2p_class -I$(SSL_INCLUDE) -L$(SSL_LIB) \
		p2p_class/file_system.cpp p2p_class/config.cpp $(SHARE_CPP) test/test_file_system.cpp \
		-o bin/test_file_system -lpthread -lsqlite3 -lcrypto

test_md5:
	g++ -g -Iinclude -I$(SSL_INCLUDE) -L$(SSL_LIB) \
		test/test_md5.cpp $(SHARE_CPP) \
		-o bin/test_md5 -lcrypto -lpthread -lsqlite3

test_advanced_file:
	g++ -g -Iinclude -Ip2p_class -I$(SSL_INCLUDE) -L$(SSL_LIB)\
		test/test_advanced_file.cpp $(SHARE_CPP) p2p_class/advanced_file.cpp \
		-o bin/test_advanced_file -lpthread -lsqlite3 -lcrypto

test_kad:
	g++ -g -Iinclude -Ip2p_class -Ikad -I$(SSL_INCLUDE) -L$(SSL_LIB)\
		test/test_kad.cpp $(SHARE_CPP) kad/kad.cpp \
		-o bin/test_kad -lpthread -lsqlite3 -lcrypto

doc_test:
	xsltproc \
	-o docs/test.html \
	/home/ylroki/project/docbook/xsl/html/docbook.xsl \
	docs/test.xml

doc_kad:
	xsltproc \
	-o docs/kad.html \
	/home/ylroki/project/docbook/xsl/html/docbook.xsl \
	docs/kad.xml


