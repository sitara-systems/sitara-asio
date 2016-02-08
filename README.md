# ofxAsio

A wrapper to simplify using the ASIO library in openFrameworks.

## Requirements
This addon unfortunately does *NOT* work with the project generator, due to ofxAsio being a header-only library and oddities with how the project generators adds libraries.

You'll need to point your IDE to the ASIO library in the `libs/` folder.  There is a property sheet in the `config` folder that will do this for you in Visual Studio.  What this property sheet does is:

* Add `ASIO_STANDLONE` and `_WIN32_WINNT=0x0501` to the PreProcessor definitions.
* Make sure `asio-1.10.6\include` is added to your include paths.

After doing this, you'll need to add all files in `ofxAsio\src` to your project to be compiled.

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
