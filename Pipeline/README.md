## Pipeline ##

### Pipeline Simulator ###

In this task I had to implement a tool that simulates the execution of a **MIPS's 5 Stages Pipeline**. The simulator recieves as input a set of instructions in **Assembly MIPS**, simulates the executions of this instructions considering all data dependencies and structural conflicts and has, as output, the amount of cycles that was necessary to execute this instructions and the situation of each stage in each cycle.

### Rules ###
1. It's a **Harvard's 5 Stages Pipeline** where the stages are:
	* **IF**: Searches the next instruction.
	* **ID**: Decodifies the instruction and searches the operands that are registers.
	* **EX**: Executes the instruction.
	* **MEM**: Memory's read.
	* **WB**: Saves on memory or in the register.
2. Recieves an **Assembly** code and will assemble, at the end, its execution on **Pipeline** cycle by cycle.
3. The instructions are **ADD**, **SUB**, **BEQ**, **BNE**, **LW**, **SW** and **JUMP**
4. There are no **reorder** or **forwarding**

### Compiling ###

To compile the program use the following code:

`make`

### Input ###

Put the inputs files on the `data/` folder. Use `.in` files.

### Running ###

To run the program use the following code:

`user@user-pc:~/Pipeline$ bin/main <./data/fileName.in> ./results/resultName.out`

This codes were made by RAYAN AVELINO.
