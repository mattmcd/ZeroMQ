// ==============================================================
// 
//       Filename:  echo_client.cpp
// 
//    Description:  0MQ echo client 
// 
//        Version:  1.0
//        Created:  17/03/13 08:58:46
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Matt McDonnell (MMcD), matt@matt-mcdonnell.com
//        Company:  
// 
// ==============================================================

#include <zmq.hpp>
#include <iostream>
#include <sstream>
#include <string>

int main (int argc, char *argv[]) 
{
  zmq::context_t context(1);
  zmq::socket_t socket ( context, ZMQ_REQ );
  if ( argc > 1) {
    // Attach to a list of sockets
    for (int i=1; i<argc; i++ ){
      std::string port(argv[i]);
      std::string socket_str = "tcp://127.0.0.1:" + port;
      socket.connect( socket_str.c_str() );
    }
  } else {
    socket.connect( "tcp://127.0.0.1:5000");
  }

  for( int i=0; i<10; i++ ) {
    std::stringstream ss;
    ss << "Message " << i;
    std::string test = ss.str();

    zmq::message_t msg( test.length() ); 
    memcpy( (void *) msg.data(), test.c_str(), test.length());
    
    socket.send( msg );
    std::cout << "Sending " << test << std::endl;
    
    socket.recv( &msg );
  }

  return 0;
}
