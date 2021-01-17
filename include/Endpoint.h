#pragma once

#include "asio/asio.hpp"
#include <iostream>
#include <string>

namespace sitara {
	class Endpoint {
	public:
		Endpoint() {
			mEndpoint = asio::ip::udp::endpoint(asio::ip::udp::v4(), 0);
		}

		Endpoint(asio::ip::udp::endpoint endpoint) {
			mEndpoint = endpoint;
		}

		Endpoint(std::string ipAddress, int port) {
			setEndpoint(ipAddress, port);
		}

		asio::ip::udp::endpoint getAsioEndpoint() {
			return mEndpoint;
		}

		std::string getIpAddress() {
			return mEndpoint.address().to_string();
		}

		int getPort() {
			return mEndpoint.port();
		}

		void setEndpoint(asio::ip::udp::endpoint endpoint) {
			mEndpoint = endpoint;
		}

		void setEndpoint(std::string ipAddress, int port) {
			asio::error_code error;
			auto address = asio::ip::address::from_string(ipAddress, error);
			if (!error) {
				mEndpoint = asio::ip::udp::endpoint(address, port);
			}
			else {
				std::cout << "sitara::Endpoint::setEndpoint -- Error setting new address : " << error.message() << std::endl;
			}
		}


	protected:
		asio::ip::udp::endpoint mEndpoint;
	};

}
