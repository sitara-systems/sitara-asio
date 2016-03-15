#pragma once

#include "asio.hpp"
#include "Endpoint.h"
#include <string>

namespace ofxAsio {
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
			mDataLength = 0;
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
			mDataLength = length;
		}

		void setData(std::string message) {
			mData.resize(message.size());
			std::copy(message.begin(), message.end(), mData.data());
			mData.push_back('\0');
			mDataLength = message.size();
		}

		void setData(std::vector<unsigned char> data) {
			mData.resize(data.size());
			std::copy(data.begin(), data.end(), mData.begin());
			mDataLength = data.size();
		}

		asio::const_buffer getDataBuffer() {
			return asio::buffer(mData, mDataLength);
		}

		const char* getData() {
			return mData.data();
		}

		std::string getDataAsString() {
			std::string msg = std::string(mData.data(), mDataLength);
			return msg;
		}

		std::vector<unsigned char> getDataAsVector() {
			return std::vector<unsigned char>(reinterpret_cast<unsigned char>(mData.data()), mDataLength);
		}

		std::size_t getDataLength() {
			return mDataLength;
		}

	protected:
		Endpoint mEndpoint;
		std::vector<char> mData;
		std::size_t mDataLength;
	};
}
