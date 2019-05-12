# swarm

For IVLabs, VNIT project "Swarm Communication".\
This is intended to be a cross platform implementation for sending and recieving data using [Xbee].

## Instructions

The repo was tested on Ubuntu 16.04

1. Clone the repo
```bash
git clone git@github.com:kamatajinkya/swarm.git
```
2. Create and go to build folder
```bash
mkdir -p swarm/build
cd swarm/build
```
3. Build the code
```bash
cmake ..
make
```
4. Run the program
```bash
./swarm
```
[Xbee]:https://www.digi.com/xbee
