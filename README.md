# Cython Example

This project presents an example of creating a cython (python) wrapper for a
c++ class/library.

To begin, create the following folder structure:

```python
|- include/
    |- myClass.h  # place C++ header files here
|- src/
    |- myClass.cpp  # place C++ source files here
|- python/
    |- myClass.pyx  # this will be python interface
|- CmakeLists.txt  # this will define C++ class compile
|- setup.py   # this will define cython wrapper creation & python package
              # installation
|- requirements.txt  # this is the python virtual environment requirements.
| .gitignore  # ingore some byproduct files
```

This example project is built around the use of `cmake` with python virutal
environments to ensure clean builds of custom packages.

The general process flow to create a C++ library and wrap it with python using
cython follows:

1. Write C++ library in `src` and `include` folders and create `CmakeLists.txt`
that defines compilation of the custom class as a static library

2. Wrap the C++ library with python in the `python/myClass.pyx` file by creating
python interfaces for specific class members and functions.

3. Compile C++ library with `cmake` and `make`:

  ```bash
  mkdir build
  cd build
  cmake ..
  make
  ```

4. [Optionally - but highly recommended] Create local python virtual environment
with at minimum `cython` package installed. Enable virtual environment before
installing wrapped package.

5. Write python package install script `setup.py`.

6. Cythonize and install wrapped python package using (*in virtual environment*):
  ```bash
  python setup.py install  
  ```

## Example Usage

Once the C++ has been compiled and the cython wrapper generated and installed
(into virtual environment), the following usage example is provided in `ipython`
console:

```python
import myClass

obj = myClass.PymyClass()
# test getters:
obj.getInt()
obj.getFloat()
obj.getChar()
obj.getString()

# test setters:
obj.setInt(12398)
obj.setFloat(10.312)
obj.setDouble(842.129381084170238102489712)
obj.setChar('c')
obj.setString("test string")  # <- WILL NOT WORK
b = bytes("test string with bytes", "UTF-8")  # UTF-8 or ascii encoding will print out correctly on C++ side; otherwise it will just receive a byte array, which is useful for data such as images.
obj.setBytes(b, len(b))

```

## Some Issues to resolve

*IMPORTANT*
The current CMakeLists.txt file creates a Static library object `.a`, this works fine with MacOS compiler, however
when moving to linux, gcc compiler has trouble linking to a static library, therefore the CmakeLists.txt should
change the desigation of the library from `STATIC` to `SHARED` when non-MacOs host is detected. 

Next problem is that the compiled shared library in Linux is locaated in the build folder `build/*.so`, however,
when trying to load the class object in python, python says it cannot open the library object.
[this](https://stackoverflow.com/questions/1099981/why-cant-python-find-shared-objects-that-are-in-directories-in-sys-path) 
suggests that the LD_LIBRARY_PATH should include the `.so` location - need to verify this and check.

- string is passed as an array of bytes to python
- not sure if setString works expected bytes but got string..
