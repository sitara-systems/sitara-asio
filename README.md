# ofxAsio

A wrapper to simplify using the ASIO library in openFrameworks.

## Requirements
To use this add-on, use the projector generator.  The one trick is that you'll then manually have to *remove* the `libs` folder from the project, so that your compiler doesn't try to compile the headers.  Once you've created a project, use the `asio.props` property sheet in `config/` to set up your compiler properly.

This library has been tested with Visual Studio 2015 and openFrameworks v0.9.1

## Usage
* `Endpoint` is the combination of an ip address and a port number.  This represents the destination for datagrams.
* `Datagram` is a class that contains a message and a destination endpoint.  You can set the message using a `char*`, `std::string`, or a `std::vector<unsigned char>`.
* `UdpSender` is a class for sending UDP messages.
* `UdpReceiver` is a class for receiving UDP messages.

Both `UdpSender` and `UdpReceiver` send and receive asynchronously, so the preferred way to deal with the results is to use callbacks.  With both classes you can attach a function callback that accepts a `std::shared_ptr<Datagram>` via the functions `addOnReceiveFn` and `addOnSendFn`.  If you're not sure what I'm talking about, check out the examples.

## Examples
* 'example-udpSender` shows how to send messages repeatedly.
* `example-udpReceiver` shows how to asynchronously wait for and print messages.

## Contributing
This project uses the [Git Flow](http://nvie.com/posts/a-successful-git-branching-model/) paradigm.  Before contributing, please make your own feature branch with your changes.

## More Information