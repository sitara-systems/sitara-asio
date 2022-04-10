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

#include "Tcp.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class exampleTcpAppApp : public App {
   public:
    void setup() override;
    void mouseDown(MouseEvent event) override;
    void update() override;
    void draw() override;

    std::shared_ptr<sitara::tcp::TcpServer> mServer;
    std::shared_ptr<sitara::tcp::TcpClient> mClient;
};

void exampleTcpAppApp::setup() {
    mServer = sitara::tcp::TcpServer::make(7331);
    mServer->start();

    mClient = sitara::tcp::TcpClient::make();
    mClient->connect("127.0.0.1", 7331);
}

void exampleTcpAppApp::mouseDown(MouseEvent event) {}

void exampleTcpAppApp::update() {
    if (ci::app::getElapsedFrames() % 60 == 0) {
        mClient->send("Hello world");
    }
}

void exampleTcpAppApp::draw() {
    gl::clear(Color(0, 0, 0));
}

CINDER_APP(exampleTcpAppApp, RendererGl, [=](cinder::app::App::Settings* settings) {
    settings->setConsoleWindowEnabled();
})
