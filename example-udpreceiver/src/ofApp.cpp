#include "ofApp.h"

using namespace midnight::sockets;

//--------------------------------------------------------------
void ofApp::setup(){
	mReceiver = UdpReceiver::make("0.0.0.0", 7331); // or UdpReceiver("192.168.0.17", 8080) to specify interface
	mReceiver->addOnReceiveFn([](std::shared_ptr<Datagram> datagram) {
		std::printf("Asio callback -- received %d bytes from %s:%d\n", datagram->getDataLength(), datagram->getIpAddress().c_str(), datagram->getPort());
	});
	mReceiver->start();
}

//--------------------------------------------------------------
void ofApp::update(){
	if (ofGetFrameNum() % 30 == 0) {
		std::printf("Application updating!  Work is still happening while we wait for a received message.\n");
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