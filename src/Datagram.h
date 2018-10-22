#pragma once

#include "asio/asio.hpp"
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
			mData.push_back('\0');
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
			std::vector<unsigned char> dataVector;
			dataVector.reserve(mData.size());
			for (auto c : mData)
			{
				dataVector.push_back((unsigned char)c);
			}
			return dataVector;
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
