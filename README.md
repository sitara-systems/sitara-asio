# ofxAsio

A wrapper to simplify using the ASIO library in openFrameworks.

## Requirements
You'll need to point your IDE to the ASIO library in the `libs/` folder.  There is a property sheet in `config` that will do this for you.

This addon has been tested with openFrameworks v0.9.1

## Usage
* `Endpoint` is the combination of an ip address and a port number.  This represents the destination for datagrams.
* `Datagram` is a class that contains a message and a destination endpoint.
* `UdpSender` is a class for sending UDP messages.
* `UdpReceiver` is a class for receiving UDP messages.

## Examples

## Contributing
This project uses the [Git Flow](http://nvie.com/posts/a-successful-git-branching-model/) paradigm.  Before contributing, please make your own feature branch with your changes.

## More Information
