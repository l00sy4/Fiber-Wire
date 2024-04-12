<h1 align="center">
<br>
<img src="FiberWire.PNG">
<br>
Evasive DLL loader
</h1>

# Features

- Initial execution delayed using KUSER_SHARED_DATA sleeping and benign WinAPI calls. Additional delay between certain actions.

- API hashing using Fowler-Noll-Vo functions

- Finds natural RWX sections and injects payload via chunking.

- Execution using thread fibers

- CRT independent

# Usage


