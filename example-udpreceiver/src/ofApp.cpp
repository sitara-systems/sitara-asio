#include "ofApp.h"

using namespace ofxAsio;

//--------------------------------------------------------------
void ofApp::setup(){
	mReceiver = std::make_shared<UdpReceiver>("0.0.0.0", 7331); // or UdpReceiver("192.168.0.17", 8080) to specify interface
	mReceiver->addOnReceiveFn([](std::shared_ptr<Datagram> datagram) {
		std::printf("ofxAsio callback -- received %d bytes from %s:%d\n", datagram->getMessage().length(), datagram->getIpAddress().c_str(), datagram->getPort());
	});
	mReceiver->start();
}

//--------------------------------------------------------------
void ofApp::update(){

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
