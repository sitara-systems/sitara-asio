#pragma once

#include "asio.hpp"
#include "Endpoint.h"
#include <string>

namespace ofxAsio {
  class Datagram {
  public:
    Datagram() {
      mMessage = "";
	  mEndpoint = Endpoint();
    }

    Datagram(std::string msg, std::string ipAddress, int port) {
      mMessage = msg;
      mEndpoint = Endpoint(ipAddress, port);
    }

    Datagram(std::string msg, Endpoint endpoint) {
      mMessage = msg;
      mEndpoint = endpoint;
    }

    std::string getMessage() {
      return mMessage;
    }

    Endpoint getEndpoint() {
      return mEndpoint;
    }

    void setMessage(std::string msg) {
      mMessage = msg;
    }

    void setEndpoint(Endpoint endpoint) {
      mEndpoint = endpoint;
    }

    void setEndpoint(std::string ipAddress, int port) {
      mEndpoint = Endpoint(ipAddress, port);
    }
    
 protected:   
    std::string mMessage;
    Endpoint mEndpoint;
    
  };
}
