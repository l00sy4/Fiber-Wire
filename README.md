<h1 align="center">
<br>
<img src="FiberWire.PNG">
<br>
DLL loader
</h1>

# Features

- Initial execution delayed using KUSER_SHARED_DATA sleeping and benign WinAPI calls. Additional delay between certain actions.

- API hashing using Fowler-Noll-Vo functions

- Finds natural RWX sections and injects payload via chunking.

- Execution using thread fibers

- CRT independent

# Usage

Project still very much WIP!

# To-do

- Get the payload from a .rc file

- Add option to allocate chunks and change their protection to RWX if no natural section is found
