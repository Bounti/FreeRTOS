# Re-hosting LPC1850 DB1 on the DMon platform

## Requirements
1. GNU Arm Embedded Toolchain download [here](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
3. DMon download [here](https://github.com/Bounti/dmon)
2. Make (tested on version 3.82)
4. Linux OS (tested on Ubuntu 20.04)
5. GDB Ubuntu 9.2

## How to build
Navigate with the command line to FreeRTOS/Demo/CORTEX\_M3\_LPC1850\_DB1
For a release build run:

```
$ export PATH=/path/to/arm/toolchain:$PATH
$ make
```
and for a versions with debugging symbols and no optimizations activated, run:
```
$ make DEBUG=1
```

## How to run
run:
```
$ gdb-multiarch -x ./load.gdb
```
	
## Demo
This Demo implements the blinky demo, the user should expect the led D3 
and D4 to be repeatedly toogle.
