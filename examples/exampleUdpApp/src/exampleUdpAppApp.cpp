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

#include "Udp.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class exampleUdpAppApp : public App {
   public:
    void setup() override;
    void mouseDown(MouseEvent event) override;
    void update() override;
    void draw() override;

    std::shared_ptr<sitara::udp::UdpSender> mSender;
    std::shared_ptr<sitara::udp::UdpReceiver> mReceiver;
};

void exampleUdpAppApp::setup() {
    mSender = sitara::udp::UdpSender::make();
    mSender->addOnSendFn([](std::shared_ptr<sitara::Datagram> datagram) {
        std::printf("Sent message '%s' to %s:%d!\n", datagram->getDataAsString().c_str(),
                    datagram->getIpAddress().c_str(), datagram->getPort());
    });

    mReceiver =
        sitara::udp::UdpReceiver::make("127.0.0.1", 7331);  // or UdpReceiver("192.168.0.17", 8080) to specify interface
    mReceiver->addOnReceiveFn([](std::shared_ptr<sitara::Datagram> datagram) {
        std::printf("Asio callback -- received %d bytes from %s:%d\n", datagram->getDataLength(),
                    datagram->getIpAddress().c_str(), datagram->getPort());
    });
    mReceiver->start();
}

void exampleUdpAppApp::mouseDown(MouseEvent event) {}

void exampleUdpAppApp::update() {
    if (ci::app::getElapsedFrames() % 300 == 0) {
        std::shared_ptr<sitara::Datagram> datagram =
            std::make_shared<sitara::Datagram>("Hello world", "127.0.0.1", 7331);
        mSender->send(datagram);
    }

    if (ci::app::getElapsedFrames() % 120 == 0) {
        std::printf("Application updating!  Work is still happening while we wait for a received message.\n");
    }
}

void exampleUdpAppApp::draw() {
    gl::clear(Color(0, 0, 0));
}

CINDER_APP(exampleUdpAppApp, RendererGl, [=](cinder::app::App::Settings* settings) {
    settings->setConsoleWindowEnabled();
})
