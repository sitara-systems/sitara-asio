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
#include "Endpoint.h"
#include <string>
#include <functional>

namespace sitara {
	class Datagram {
	public:
		Datagram() {
			mEndpoint = Endpoint();
			init();
		}

		Datagram(Endpoint endpoint) {
			mEndpoint = endpoint;
			init();
		}

		Datagram(std::string ipAddress, int port) {
			mEndpoint = Endpoint(ipAddress, port);
			init();
		}

		Datagram(std::string message, std::string ipAddress, int port) {
			mEndpoint = Endpoint(ipAddress, port);
			setData(message);
		}

		Datagram(std::vector<unsigned char> data, std::string ipAddress, int port) {
			mEndpoint = Endpoint(ipAddress, port);
			setData(data);
		}

		void init() {
			mData.reserve(512);
			mData.clear();
		}

		Endpoint getEndpoint() {
			return mEndpoint;
		}

		std::string getIpAddress() {
			return mEndpoint.getIpAddress();
		}

		int getPort() {
			return mEndpoint.getPort();
		}

		void setEndpoint(Endpoint endpoint) {
			mEndpoint = endpoint;
		}

		void setEndpoint(std::string ipAddress, int port) {
			mEndpoint = Endpoint(ipAddress, port);
		}

		void setData(char* data, std::size_t length) {
			mData = std::vector<char>(data, data + length);
		}

		void setData(std::string message) {
			mData.resize(message.size());
			std::copy(message.begin(), message.end(), mData.data());
		}

		void setData(std::vector<unsigned char> data) {
			mData.resize(data.size());
			std::copy(data.begin(), data.end(), mData.begin());
		}

		asio::const_buffer getDataBuffer() {
			return asio::buffer(mData, mData.size());
		}

		const char* getData() {
			return mData.data();
		}

		std::string getDataAsString() {
			std::string msg = std::string(mData.data(), mData.size());
			return msg;
		}

		std::vector<unsigned char> getDataAsVector() {
			return std::vector<unsigned char>(reinterpret_cast<unsigned char>(mData.data()), mData.size());
		}

		std::size_t getDataLength() {
			return mData.size();
		}

		void clear() {
			mData.clear();
		}

		bool empty() {
			return mData.empty();
		}

		void push_back(char data) {
			mData.push_back(data);
		}

		void push_back(unsigned char data) {
			mData.push_back(data);
		}

		std::vector<char>::iterator begin() {
			return mData.begin();
		}

		std::vector<char>::iterator end() {
			return mData.end();
		}

	protected:
		Endpoint mEndpoint;
		std::vector<char> mData;
	};

}
