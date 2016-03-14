#include "ofApp.h"

using namespace ofxAsio;

//--------------------------------------------------------------
void ofApp::setup(){
	mSender = std::make_shared<UdpSender>();
	mSender->addOnSendFn([](std::shared_ptr<Datagram> datagram) {
		std::printf("Sent message!");
	});
}

//--------------------------------------------------------------
void ofApp::update(){
	std::shared_ptr<Datagram> datagram = std::make_shared<Datagram>("Hello world", "192.168.0.115", 8080);
	mSender->send(datagram);
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
