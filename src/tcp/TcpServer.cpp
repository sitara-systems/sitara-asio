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

#include "tcp/TcpServer.h"

using namespace sitara;
using namespace sitara::tcp;

std::shared_ptr<TcpServer> TcpServer::make(int port) {
	std::shared_ptr<TcpServer> Server(new TcpServer(port));
	return Server;
}

TcpServer::TcpServer(int port) : mService(), mSocket(mService), mWork(mService), mAcceptor(mService) {
	init(port);
}

TcpServer::~TcpServer() {
	mSocket.cancel();
	mService.stop();
	if (mServiceThread.joinable()) {
		mServiceThread.join();
	}
}

void TcpServer::start() {
	createSession();
}

void TcpServer::init(int port) {
	mLocalEndpoint = asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port);

	std::printf("sitara::sockets::TcpServer -- Creating endpoint %s:%d ...\n", mLocalEndpoint.address().to_string().c_str(), mLocalEndpoint.port());

	mAcceptor.open(mLocalEndpoint.protocol());
	mAcceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
	mAcceptor.bind(mLocalEndpoint);
	mAcceptor.listen();

	mServiceThread = std::thread([&] {
		mService.run();
	});

}

void TcpServer::onConnect(std::vector<std::shared_ptr<TcpSession>>::iterator session_iter, const asio::error_code& error) {
	if (!error) {
		std::printf("sitara::sockets::TcpServer -- Connection from %s received!\n", (*session_iter)->getSocket().remote_endpoint().address().to_string().c_str());

		(*session_iter)->start();
		createSession();
	}
	else {
		std::printf("sitara::sockets::TcpServer::onConnect -- Error receiving data. %s\n", error.message().c_str());
		mSessions.erase(session_iter);
	}
}

void TcpServer::createSession() {
	std::shared_ptr<TcpSession> newSession = TcpSession::make(mService);
	std::vector<std::shared_ptr<TcpSession>>::iterator iterator = mSessions.insert(mSessions.end(), newSession);

	mAcceptor.async_accept(newSession->getSocket(),
		[this, iterator](const asio::error_code &error) {
		onConnect(iterator, error);
	});
}
