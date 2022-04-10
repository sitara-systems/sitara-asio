// Copyright (c) 2022 Nathan S Lachenmyer
//
// MIT License
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <iostream>
#include <string>

#include "asio/asio.hpp"

namespace sitara {
class Endpoint {
   public:
    Endpoint() { mEndpoint = asio::ip::udp::endpoint(asio::ip::udp::v4(), 0); }

    Endpoint(asio::ip::udp::endpoint endpoint) { mEndpoint = endpoint; }

    Endpoint(std::string ipAddress, int port) { setEndpoint(ipAddress, port); }

    asio::ip::udp::endpoint getAsioEndpoint() { return mEndpoint; }

    std::string getIpAddress() { return mEndpoint.address().to_string(); }

    int getPort() { return mEndpoint.port(); }

    void setEndpoint(asio::ip::udp::endpoint endpoint) { mEndpoint = endpoint; }

    void setEndpoint(std::string ipAddress, int port) {
        asio::error_code error;
        auto address = asio::ip::address::from_string(ipAddress, error);
        if (!error) {
            mEndpoint = asio::ip::udp::endpoint(address, port);
        } else {
            std::cout << "sitara::Endpoint::setEndpoint -- Error setting new address : " << error.message()
                      << std::endl;
        }
    }

   protected:
    asio::ip::udp::endpoint mEndpoint;
};

}  // namespace sitara
