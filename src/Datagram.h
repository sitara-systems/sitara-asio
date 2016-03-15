#pragma once

#include "asio.hpp"
#include "Endpoint.h"
#include <string>

namespace ofxAsio {
	class Datagram {
	public:
		Datagram() {
			mEndpoint = Endpoint();
		}

		Datagram(Endpoint endpoint) {
			mEndpoint = endpoint;
		}

		Datagram(std::string ipAddress, int port) {
			mEndpoint = Endpoint(ipAddress, port);
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

		virtual asio::const_buffer getDataBuffer() = 0;
		virtual std::size_t getDataLength() = 0;

	protected:
		Endpoint mEndpoint;
	};

	class Message : public Datagram {
	public:
		Message() : Datagram() {
			mMessage = "";
		}

		Message(std::string msg, Endpoint endpoint) : Datagram(endpoint) {
			mMessage = msg;
		}

		Message(std::string msg, std::string ipAddress, int port) : Datagram(ipAddress, port) {
			mMessage = msg;
		}

		void setMessage(std::string msg) {
			mMessage = msg;
		}

		std::string getMessage() {
			return mMessage;
		}

		asio::const_buffer getDataBuffer() {
			return asio::buffer(mMessage.data(), mMessage.length());
		}

		std::size_t getDataLength() {
			return mMessage.length();
		}

	protected:
		std::string mMessage;
	};

	class Packet : public Datagram {
	public:
		Packet() : Datagram() {
			mPacket.clear();
		}

		Packet(std::vector<unsigned char> data, Endpoint endpoint) : Datagram(endpoint) {
			mPacket = data;
		}

		Packet(std::vector<unsigned char> data, std::string ipAddress, int port) : Datagram(ipAddress, port) {
			mPacket = data;
		}

		void setPacket(std::vector<unsigned char> data) {
			mPacket = data;
		}

		std::vector<unsigned char> getPacket() {
			return mPacket;
		}

		asio::const_buffer getDataBuffer() {
			return asio::buffer(mPacket.data(), mPacket.size());
		}

		std::size_t getDataLength() {
			return mPacket.size();
		}

	protected:
		std::vector<unsigned char> mPacket;
	};

}
