# ofxAsio

A wrapper to simplify using the Asio library for asynchronous networking in openFrameworks.  I created this addon because I was frustrated with the limitations of `ofxUdpManager` and wanted something a bit more robust.  In addition, I wanted to create something that was cross-platform and even framework agnostic.  You'll find that this addon doesn't use any openFrameworks-specific classes, and can be dropped into any C++ project with minimal tweaking.

## Requirements

### Windows
To use this add-on, use the projector generator.  The one trick is that you'll then manually have to *remove* the `libs` folder from the project, so that your compiler doesn't try to compile the headers.  Once you've created a project, use the `asio.props` property sheet in `config/` to set up your compiler properly.

This library has been tested with Visual Studio 2015 and openFrameworks v0.9.1

### OSX
This project is currently not configured for Xcode in OSX.  If anyone wants to take this on, I'd be glad to help.  Otherwise you'll have to wait until I have a reason to need it on my Mac :)

## Usage
`ofxAsio` is a a relatively minimal wrapper around the Asio library to try to make networking easier.  There are two main classes, one for sending UDP messages (`UdpSender`) and one for receiving UDP messages (`UdpReceiver`).

Both should be created as such:

     std::shared_ptr<ofxAsio::UdpSender> mUdpSender = std::make_shared<ofxAsio::UdpSender>();
     std::shared_ptr<ofxAsio::UdpReceiver> mUdpReceiver = std::make_shared<ofxAsio::UdpReceiver>("0.0.0.0", 8080);
     
For both classes, you'll need to familiarize yourself with the `Datagram` class.  A datagram is the combination of a udp message and an endpoint; in `ofxAsio` we've encapsulated the endpoint as an `Endpoint` class that contains an IP address and a port number.  The message itself lives in the `Datagram` class, represented as a `std::vector`.

The `Datagram` class is meant to be versatile to meet most possible needs, which means that it should be able to accept strings as the message, but it should also be able to accept data packets (which would typically be buffers of `unsigned char`, or bytes).  As such, `Datagram` has several ways to set the message:

    void setData(char* data, std::size_t length);
    void setData(std::string message);
    void setData(std::vector<unsigned char> data);

All three accepted data types (`char*`, `std::vector<unsigned char>`, and `std::string`) are also accepted in the constructor.

In addition, just like a normal `std::vector`, you can `push_back()` into the `Datagram`, as well as get an iterator with `begin()` and `end()`.

Both `UdpSender` and `UdpReceiver` send and receive asynchronously, so the preferred way to deal with the results is to use callbacks.  With both classes you can attach a function callback that accepts a `std::shared_ptr<Datagram>` via the functions `addOnReceiveFn()` and `addOnSendFn()`.  If you're not sure what I'm talking about, check out the examples.

## Examples
* `example-udpSender` shows how to send messages repeatedly.
* `example-udpReceiver` shows how to asynchronously wait for and print messages.

## Contributing
This project uses the [Git Flow](http://nvie.com/posts/a-successful-git-branching-model/) paradigm.  Before contributing, please make your own feature branch with your changes.

## More Information
* [Asio Homepage](http://think-async.com/)