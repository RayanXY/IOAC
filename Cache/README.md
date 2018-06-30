## Cache ##

### Cache Simulator ###

In this taks was implemented a tool that simulates the internal behavior of a **L1 Cache** and a **Main Memory**. The Simulator receive as input commands that can be for reading or writing and the desired address. The simulated cache must verified the presence or not of the block that contains the desired address (leading to a **Hit** or a **Miss**). The simulator is configurable about the **Mapping** and **Replacement Policy**. 

### Mapping ###

The chosen mapping can be of three type: **Direct**, **Fully Associative** and **Set Associative**. According to the chosen mapping and after the input command of reading or writting the simulator informs the outcome of the operation (**Hit** or **Miss**) and the cache's line that contains the requested block.

### Replacement Policy ###

The replacement algorithm of blocks can be of four types: **Random**, **FIFO**, **LFU**, **LRU**. According with the replacement policy chosen and after the command of reading or writting the simulator must additionally inform if there was replacement and which block was removed of which cache's line.

### Commands ###

The simulator accepts as input three commands: **Read**, **Write** and **Show**. The **Read** command receive as parameter the address to be readed. As answer the simulator must inform the result (**Hit** or **Miss**) and the cache's line that contains the requested block. The **Write** command works in a similary way, although besides of the address to be wrote it has as parameter the new value to be wrote. At last, the **Show** command shows the content of the whole Cache and of the Main Memory.

### The Conifg.txt file ###

The simulator manages a cache memory with a pre-defined setup. In a file of configuration (config.txt) must be stored the user's choices to the following characteristcs(in this order):
```
"Block's size (in number of words)"
"Number of Cache's lines"
"Number of Main Memory's blocks"
"Mapping type (1 - Direct | 2 - Fully Associative | 3 - Set Associative)"
"Number of set (Only for Set Associative mapping)"
"Replacement Policy (1 - Random | 2 - FIFO | 3 - LFU | 4 - LRU)"
```
The `config.txt` file its on the `data/` folder.

### Compiling ###

To compile the program use the following code:

`make`


### Running ###

To run the program use the following code:

`user@user-pc:~/Cache$ bin/simulator `

### Google Test Framework ###

Google test is a framework for writing C++ unit tests

### Installing Google Test ###

Start by installing the gtest development package:
`sudo apt-get install libgtest-dev`

Install **cmake**:
`sudo apt-get install cmake`

And then go to folder where the **Google Test** was installed, it should be at /usr/src/gtest:

`cd /usr/src/gtest`

Then do the following code to end the installing process:
```
"sudo cmake CMakeLists.txt"
"sudo make"
"sudo cp *.a /usr/lib"
```
### Executing the test file ###

To execute the test file go to the `/test` folder then do the following code:

```
"user@user-pc:~/Cache/test$ sudo cmake CMakeLists.txt"
"user@user-pc:~/Cache/test$ make"
"user@user-pc:~/Cache/test$ ./runTests"
```

This codes were made by RAYAN AVELINO.