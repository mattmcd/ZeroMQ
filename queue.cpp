// ==============================================================
// 
//       Filename:  queue.cpp
// 
//    Description:  0MQ queue device 
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
#include <string>

int main (int argc, char *argv[]) 
{
  zmq::context_t context(1);
  zmq::socket_t frontend ( context, ZMQ_ROUTER );
  frontend.bind( "tcp://127.0.0.1:5000");
  
  zmq::socket_t backend ( context, ZMQ_DEALER );
  backend.bind( "tcp://127.0.0.1:5001");

  zmq_device( ZMQ_QUEUE, frontend, backend );

  return 0;
}
