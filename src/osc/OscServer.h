/*
 * OscServer.h
 *
 * An implementation of Cinder's native Osc Receiver classes, built up with the ofxAsio framework.
 */

#pragma once

#include "cinder/osc/osc.h"
#include "cinder/Log.h"

namespace ofxAsio {
	namespace osc {
		class OscServer : public cinder::osc::ReceiverUdp {
		public:
			static std::shared_ptr<OscServer> make(int port);
			static std::shared_ptr<OscServer> make(std::string localAddress, int port);
			~OscServer();
			void start();
		protected:
			OscServer(int port);
			OscServer(std::string localAddress, int port);
			void init();
			asio::io_service mService;
			std::thread mServiceThread;
			asio::io_service::work mWork;
		};
	}
}