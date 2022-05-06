This is a incomplete PlayStation 3 port of Postal 1. This port is broken and i'll not guarantee all of issues will be fixed.
I'll do my best as long as i have time. 

What's working
* Game logic
* Controller
* Sound

What's broken
* Renderer (Colors are messed up (Black => Blue) otherwise works)
* Game stall in real hw but works in emulator(rpcs3)

What's deleted
* Steamworks and trophy code

TODO:
* Find and fix issue that prevents game launching in real hw
* Fix renderer

To build this port you need to install PSL1GHT and SDL2 port of PS3.
https://github.com/ps3dev/ps3toolchain <br>
https://github.com/sergiou87/SDL2_PSL1GHT <br>
To make pkg file you need to copy assets from your copy of postal 1.
Copy res and title folders to under USRDIR directory.
Then run these instructions to build.

```
make PSL1GHT=1
make ps3pkg
```
