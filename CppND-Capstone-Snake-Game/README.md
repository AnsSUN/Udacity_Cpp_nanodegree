# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

## Files added to Capstone Snake Game
I added new class foodnbomb for food and bomb. Food for snake to grow one point and bomb to destroy by 4 points,
Food is green color and bomb is red in color. Messages will be displayed on the terminal about the ststus of the snake. Snake will die if there is no body remaining after going through the bomb.
The scores, fps, number of food that ate by snake, number of bombs through by snake will be shown on window title.


## Files and structure of class FoodnBomb
There are two files for class FoodnBomb, the base class (foodnbomb.h) and foodnbomb.cpp.
In the FoodnBomb.h file there are enum variable called Flag_type, declare of attributes and methods of foodnbomb class i.e Checkflag(), Setflag(), Count(), GetCount(), Distroy(), food_body, bomb_body, _flag_type, _count, _count_food, _count_bomb and string of messages. Methodsare defined in foodnbomb.cpp.


## After adding the feature in the game
1. There are two points on the screen which represents food(green in color) and bomb(red in color).
2. Snake will expand one point/ pixel as it will eat the food and contract by 4 points/pixels if gone through a bomb.
3. Food and bomb positions are place randomly in the gaming screen.
4. Score will increase by one when it eats food and decrease by 4 when go through a bomb.
5. If the body of snake is distroyed by the bomb, snake will die.
6. Snake will die if its eat their own body.

## Rubric points that are addresed:
1. Point number one in table "Loops, Functions, I/O", 
   Implemented in foodnbomb.cpp (line 4 - 37), foodnbomb.h (line 17 - 32), game.h (line 20 - 37), snake.h (line 19 - 20), the functions/method called in game.cpp (line 55 - 85, 95 - 123, 128 - 134), in snake.cpp (line 57 - 66, line 77), renderer.cpp (line 57 - 62).
2. Point number 1 to 8 in table "Object Oriented Programming",
   Implemented in foodnbomb.h (all lines) and foodnbomb.cpp(all lines).
   

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
