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

#include <thread>
#include "asio/asio.hpp"
#include "TcpSession.h"
#include "../Datagram.h"

namespace sitara {
	namespace tcp {
		class TcpServer {
		public:
			static std::shared_ptr<TcpServer> make(int port);
			~TcpServer();
			void start();
		protected:
			TcpServer(int port);
			void init(int port);
			void createSession();
			void onConnect(std::vector<std::shared_ptr<TcpSession>>::iterator session_iter, const asio::error_code& error);
			asio::io_service mService;
			asio::io_service::work mWork;
			std::thread mServiceThread;
			asio::ip::tcp::acceptor mAcceptor;
			asio::ip::tcp::socket mSocket;
			asio::ip::tcp::endpoint mLocalEndpoint;
			std::vector < std::shared_ptr<TcpSession>> mSessions;
		};

	}
}
