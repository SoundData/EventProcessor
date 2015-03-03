EventProcessor
==============
This component connects to the TF2 server which is specified on the command line. Then, it waits to receive TF2 game events and processes them in the order they are received. See EventProcessor/Main.cpp for an example of a message processing loop.

Usage
-----
On Windows, you can use the included binary in the Debug folder.

*Example*:
```EventProcessor.exe tcp://104.236.52.206:7633```

tells the EventProcessor to connect over TCP to the server at 104.236.52.206 port 7633 and listen for game message events.

On Mac, the contents of the Debug folder are not much use to you. You will need to compile this project separately and link against the zmq lib (-lzmq).