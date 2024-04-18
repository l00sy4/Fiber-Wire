<h1 align="center">
<br>
<img src="FiberWire.PNG">
<br>
DLL loader
</h1>


# Features

- Initial execution delayed using KUSER_SHARED_DATA sleeping and benign WinAPI calls. Additional delay between certain actions

- API hashing using Fowler-Noll-Vo functions

- Payload Injection via chunking (currently undergoing change)

- Execution using thread fibers

- CRT independent


# Usage

Project still very much WIP!


# To-do

- Get the payload from a .rc file

### Credits

- https://github.com/iilegacyyii/ThreadlessInject-BOF
- https://github.com/NUL0x4C/AtomLdr
