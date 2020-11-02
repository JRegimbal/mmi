# README Multimodal Interpolation

Project doing RBFI from a joint tactile and audio control space to a 2D surface and back.
Currently a work in progress.

## Dependencies

This project requires Eigen (included as a submodule), flext, and Pd to be available with
headers. You don't need to worry about Eigen, but insttall flext and Pd however you would
for your OS. CMake is used as the default build system, but you can use whatever you want
if you don't mind extra work.

For Debian:
```
sudo apt install puredata pd-flext-dev cmake
```

## Building

There are two build targets of this project.
The first is `mm-interpolation`, which is a C++ test program using Eigen
that does the kind of interpolation we do in Pd with random variables.
The second is `mmi`, which is the Pd external.

```bash
mkdir build && cd build
cmake ..
make
```
