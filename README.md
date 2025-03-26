# miniguys

## How to build and run
*You will need vcpkg installed on your machine, see [how to install here](https://learn.microsoft.com/pt-br/vcpkg/get_started/get-started?pivots=shell-cmd)*
```
vcpkg install glad glfw3
cmake --preset=default
cmake --build build
./build/miniguys
``` 

## Important notes
### Dependencies
- This project user opengl 3.3, so make sure your machine supports it.
- This project uses vcpkg to manage dependencies, so make sure you have it installed.
- This project uses cmake to build, so make sure you have it installed.
- This project uses clang-format to format the code, so make sure you have it installed.
