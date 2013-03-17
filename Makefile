all: echo_server echo_client queue

echo_server: echo_server.cpp
	clang++ -std=c++0x -o echo_server echo_server.cpp -lzmq 

echo_client: echo_client.cpp
	clang++ -std=c++0x -o echo_client echo_client.cpp -lzmq 

queue: queue.cpp
	clang++ -std=c++0x -o queue queue.cpp -lzmq 
