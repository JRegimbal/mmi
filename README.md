# Multimodal Interpolation

Project doing RBFI from a joint tactile and audio control space to a 2D surface and back.
Unpolished, but it *should* work!
[NIME'21 paper](https://doi.org/10.21428/92fbeb44.1084cb07)

## Dependencies

This project requires Eigen (included as a submodule), flext, and Pd to be available with
headers. You don't need to worry about Eigen, but install flext and Pd however you would
for your OS. CMake is used as the default build system, but you can use whatever you want
if you don't mind extra work.

For Debian/Ubuntu:
```
sudo apt install puredata pd-flext-dev cmake
```

## Building

This has been tested using Github Actions against macOS and Ubuntu. It *should* be compilable on
Windows, but honestly compiling software on Windows is arcane knowledge I do not possess.

There are two build targets of this project.
The first is `mm-interpolation`, which is a C++ test program using Eigen
that does the kind of interpolation we do in Pd with random variables.
The second is `mmi`, which is the Pd external.

```bash
mkdir build && cd build
cmake ..
make
```

Note for macOS: Your headers for Pd are required but may not be somewhere this program works. If the above
complains about `Flext_PD_INCLUDE` being unset, please find your path to the Pd headers.
It could be something like `/Applications/Pd-0.51-3/Contents/Resources/src`, but the headers should be in the
app bundle under `Contents/Resources/src`. Once you find this path, replace the cmake step with
```bash
cmake .. -DPD_PATH=$PATH_TO_YOUR_PD_HEADERS
```

## Running

This should be loadable as a Pd external int he usual way. If you don't want to move it to your externals
directory, you can load it at start from the `build` directory by `puredata -lib mmi`.
