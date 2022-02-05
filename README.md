# Inter_Process_Communication

Part of an assignment for the Operating System course (CSE-231) at IIIT Delhi.

## Question Statement

This would require you to write two programs P1 and P2. The first program P1 needs to generate an array of 50 random strings (of characters) of fixed length each. P1 then sends a group of five consecutive elements of the array of strings to P2 along with the ID’s of the strings, where the ID is the index of the array corresponding to the string.
The second program P2 needs to accept the received strings, and send back the highest ID received back to P1 to acknowledge the strings received. The program P2 simply prints the ID’s and the strings on the console. On receiving the acknowledged packet, P1 sends the next five strings, with the string elements starting from the successor of the acknowledged ID.

The above mechanism needs to be implemented using three different techniques: (i) Unix domain sockets, (ii) FIFOs, and (iii) message passing queues.

Please note that you may NOT make assumptions about the reliability of the interprocess communication mechanism, unless they are guaranteed by the mechanism itself.
