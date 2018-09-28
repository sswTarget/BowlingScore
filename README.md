# BowlingScore
Score a game of bowling

### To build:
A CMakeLists.txt file is included. If you don't have CMake, you can download it [here](https://cmake.org/download/).

Open a command line in your desired build location.

\>`cmake sourcedir`

CMake will generate the necessary files in the current directory.  CMake will choose a default generator, but you can override with the -G option.  CMake --help will print a list of supported generators.

Build the executable using e.g. make, VS, etc.

For more information on CMake, visit https://cmake.org

### To run tests: 
Run ctest in the root build directory (i.e. where you ran cmake):

\>`ctest`

See CMakeLists.txt to add or change tests.

Example sequence for Windows with Visual Studio generator:

\> `cmake ../src -G "Visual Studio 14 2015"`

Open .sln in Visual Studio and build.

Run tests:

\> `ctest`

Example usage:

\>`BowlingScore.exe 10 10 10 10 10 10 10 10 10 10 10 10`
