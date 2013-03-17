// ==============================================================
// 
//       Filename:  echo_server.cpp
// 
//    Description:  0MQ echo server 
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
#include <string>

int main (int argc, char *argv[]) 
{
  zmq::context_t context(1);
  zmq::socket_t socket ( context, ZMQ_REP );
  // Take port binding from first argument
  if ( argc > 1 ) {
    std::string port( argv[1] );
    std::string sock_str = "tcp://127.0.0.1:" + port;
    socket.connect( sock_str.c_str() );
  } else {
    socket.connect( "tcp://127.0.0.1:5001");
  }

  while ( true ) {
    zmq::message_t msg; 
    socket.recv( &msg );
    std::string text = (char *) msg.data() ;
    std::cout << "Got " << text << std::endl;
    socket.send( msg );
  }

  return 0;
}
