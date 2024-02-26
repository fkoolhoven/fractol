<div align="center">

  <img src="img/FRACTOL3.png" alt="logo" width="1000" height="auto" />
  
  <p>
    This project is about creating graphically beautiful fractals.
  </p>
</div>
  

# About the project

A project made in accordance with the fractol project which is part of the Codam Core Curriculum. For this project it was mandatory to use [the school's graphics library](https://github.com/codam-coding-college/MLX42). The purpose of the project is to create graphically beautiful fractals. A fractal is a shape that looks similar at different scales. This means that if you zoom in on a fractal, it will look similar to the original shape. Fractals are often found in nature, like in the patterns of snowflakes or the branching of trees. They can also be created mathematically using recursive equasions. Fractol was built to run on MacOS.

# Features
- The mouse wheel zooms in and out, almost infinitely (within the limits of the computer).
- The view can be adjusted using the arrow keys.
- The program can display the Mandelbrot set.
- The program is able to create different Julia sets by passing different parameters to the program.
- The colors show the depth of each fractal.
 
 <img src="img/Julia2.png" alt="logo" width="1000" height="auto" />
 <img src="img/Zoomed3.png" alt="logo" width="1000" height="auto" />
 <img src="img/Zoomed2.png" alt="logo" width="1000" height="auto" />

# Getting started

Start by cloning the repository:
```c
git clone https://github.com/fkoolhoven/fractol.git
```

Compile by using make:
```c
make
```

# Usage

To display the Mandelbrot set:
```c
./fractol mandelbrot
```
To display the Julia set:
```c
./fractol julia [real component of c] [imaginary component of c]
```
For example:
```c
./fractol julia -0.538 0.50695
```
- Zoom in and out with the mousewheel
- Adjust view using the arrow keys
- Quit the program with ESC or the window's close button

# Important learnings

This project was my introduction into programming graphics. I learned to use a simple graphics library, practiced event handling and gained some insight into optimization. Additionally I learned about the mathematical notion of complex numbers. The most challening part of this project for me was generating the colors and having them blend into each other. I dove into the concept of linear interpolation for this, which wasn't mandatory. I passed the project with 115%.

# Contact

See my profile page for ways to contact me!
