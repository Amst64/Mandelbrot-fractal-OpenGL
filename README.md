# Mandelbrot-fractal-OpenGL

This is a project that draw on screen the Mandelbrot fractal.

## Compile and run on Windows

You need to install [CMake](https://cmake.org/download/).
Then create a *build* folder at the root of this project, open a terminal and run `cmake ..` in the *build* folder.
Open the *build* folder and open the visual studio solution *Mandelbrot.sln*.
Build the project.
A *bin* folder will be created at the root of this project. Open the folder, there will be another folder *Debug*.
Open a terminal, place yourself in the *Debug* folder and run this command `./Mandelbrot_exe.exe mandelbrot.vs.glsl mandelbrot.fs.glsl`.

## Compile and run on Linux

You need to install [CMake](https://cmake.org/download/).
Then create a *build* folder at the root of this project, open a terminal and run `cmake ..` in the *build* folder and run `make`.
A *bin* folder will be created at the root of this project.
Open a terminal, place yourself in the *bin* folder and run this command `./Mandelbrot_exe.exe mandelbrot.vs.glsl mandelbrot.fs.glsl`.
