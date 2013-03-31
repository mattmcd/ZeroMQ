// ==============================================================
// 
//       Filename:  echo_client.cpp
// 
//    Description:  0MQ echo client 
// 
//        Version:  1.0
//        Created:  17/03/13 08:58:46
//       Revision:  none
//       Compiler:  clang++
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

  std::vector<std::string> args(argc);
  args.assign( argv + 1, argv+argc);
  if ( argc > 1) {

    // Attach to a list of sockets
    for ( auto port : args ){
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
