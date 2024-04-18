<h1 align="center">
<br>
<img src="FiberWire.PNG">
<br>

</h1>

# Features

- Initial execution delayed using KUSER_SHARED_DATA sleeping and benign WinAPI calls. Additional delay between actions that could constitute a pattern

- API hashing using Fowler-Noll-Vo functions

- Payload Injection via chunking. Since the protection is RX, it does not support polymorphic payloads

- Execution using thread fibers

- CRT independent


# Usage

Project still very much WIP!


# To-do

- Get the payload from a .rc file

### Credits

- https://github.com/iilegacyyii/ThreadlessInject-BOF
- https://github.com/NUL0x4C/AtomLdr
