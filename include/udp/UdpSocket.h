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

#include "asio/asio.hpp"
#include "../Endpoint.h"
#include "../Datagram.h"
#include <memory>
#include <thread>
#include <array>
#include <string>

namespace sitara {
	namespace udp {
		class UdpSocket {
		public:
			UdpSocket();
			UdpSocket(int port);
			UdpSocket(std::string localAddress, int port);
			~UdpSocket();
			void setIncomingBufferSize(std::size_t buffer_size);
			void addOnReceiveFn(std::function<void(std::shared_ptr<Datagram> msg)> response);
			void addOnSendFn(std::function<void(std::shared_ptr<Datagram> msg)> response);
		protected:
			void init();
			void sendDatagram(std::shared_ptr<Datagram> msg);
			void receive();
			void onReceive(const asio::error_code &error, std::size_t bytes_received);
			asio::io_service mService;
			std::thread mServiceThread;
			asio::io_service::work mWork;
			asio::ip::udp::socket mSocket;
			Endpoint mLocalEndpoint;
			std::size_t mMaxBufferSize;
			std::shared_ptr<Datagram> mIncomingDatagram;
			asio::ip::udp::endpoint mIncomingEndpoint;
			std::vector<unsigned char> mIncomingMessage;
			std::vector<std::function<void(std::shared_ptr<Datagram> msg)> > mOnReceiveFns;
			std::vector<std::function<void(std::shared_ptr<Datagram> msg)> > mOnSendFns;
		};

	}
}
