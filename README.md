# sitara-asio

A wrapper to simplify using the Asio library for asynchronous networking in openFrameworks and Cinder. I created this addon because I was frustrated with the limitations of `ofxUdpManager` and wanted something a bit more robust. In addition, I wanted to create something that was cross-platform and even framework agnostic. You'll find that this addon doesn't use any openFrameworks-specific classes, and can be dropped into any C++ project with minimal tweaking.

As of 2019, I'm only maintaining this library for Cinder. As it doesn't use any openFrameworks-specific classes, this doesn't mean it won't work -- but I won't be creating or supporting examples in openFrameworks, as I've moved my practice entirely to cinder at this point.

## Requirements

This library currently runs off of asio 1.11; it runs off of the version included in cinder, but can be easily adaptered for newer version by using the `vcpkg.json` file.

The included `vcpkg.json` should automatically download and build the dependencies for all examples in here. This block also requires cinder to be in an adjacent folder for the cinder dependencies to be found automatically:

    parentFolder/
        sitara-asio/
        cinder/

Use the included `vcpkg.json` as a jumping off point for adding this block into other projects!

## Usage

`sitara-asio` is a a relatively minimal wrapper around the Asio library to try to make networking easier. There are two main classes, one for sending UDP messages (`UdpSender`) and one for receiving UDP messages (`UdpReceiver`).

Both should be created as such:

     std::shared_ptr<sitara::udp::UdpSender> mUdpSender = std::make_shared<sitara::udpUdpSender>();
     std::shared_ptr<sitara::udpUdpReceiver> mUdpReceiver = std::make_shared<sitara::udpUdpReceiver>("0.0.0.0", 8080);

For both classes, you'll need to familiarize yourself with the `Datagram` class. A datagram is the combination of a udp message and an endpoint; in `ofxAsio` we've encapsulated the endpoint as an `Endpoint` class that contains an IP address and a port number. The message itself lives in the `Datagram` class, represented as a `std::vector`.

The `Datagram` class is meant to be versatile to meet most possible needs, which means that it should be able to accept strings as the message, but it should also be able to accept data packets (which would typically be buffers of `unsigned char`, or bytes). As such, `Datagram` has several ways to set the message:

    void setData(char* data, std::size_t length);
    void setData(std::string message);
    void setData(std::vector<unsigned char> data);

All three accepted data types (`char*`, `std::vector<unsigned char>`, and `std::string`) are also accepted in the constructor.

In addition, just like a normal `std::vector`, you can `push_back()` into the `Datagram`, as well as get an iterator with `begin()` and `end()`.

Both `UdpSender` and `UdpReceiver` send and receive asynchronously, so the preferred way to deal with the results is to use callbacks. With both classes you can attach a function callback that accepts a `std::shared_ptr<Datagram>` via the functions `addOnReceiveFn()` and `addOnSendFn()`. If you're not sure what I'm talking about, check out the examples.

## Contributing

This project uses the [Git Flow](http://nvie.com/posts/a-successful-git-branching-model/) paradigm. Before contributing, please make your own feature branch with your changes.

## More Information

- [Asio Homepage](http://think-async.com/)
