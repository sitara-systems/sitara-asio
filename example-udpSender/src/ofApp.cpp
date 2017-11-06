#include "ofApp.h"

using namespace midnight::sockets;

//--------------------------------------------------------------
void ofApp::setup(){
	mSender = UdpSender::make();
	mSender->addOnSendFn([](std::shared_ptr<Datagram> datagram) {
		std::printf("Sent message '%s' to %s:%d!\n", datagram->getDataAsString().c_str(), datagram->getIpAddress().c_str(), datagram->getPort());
	});
}

//--------------------------------------------------------------
void ofApp::update(){
	if (ofGetFrameNum() % 60 == 0) {
		std::shared_ptr<Datagram> datagram = std::make_shared<Datagram>("Hello world", "192.168.0.115", 8080);
		mSender->send(datagram);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
