# Cool Game Engine
## Game engine for Hacklab Turku gamejamming

This is a simple SFML template for making games at gamejams and similar. It requires SFML 2 and C++11 to compile.

## Core ideas

The game renders Scenes which are managed by a Scenehandler. Each Scene may contain its own graphics, logic, world and everything. This is where majority of your code should go.

The Input class reads input, and this is where you should create calls to Scene objects if you want them to react in any way when a mouse is clicked or keys pressed.

The DataStorage is used for loading pixmaps, audio and fonts, and stores those in std::map.

## Project setup

### Windows

Download SFML 2 at http://www.sfml-dev.org/download/sfml/2.1/ for your compiler, most likely Visual C++ 2010 or 2012. Note you need at least 2010 for C++11.

Open the .sln file, go to hackjam_roottori at solution explorer, right click and properties, go to VC++ directories:
* Go to include directories and add the SFML 2 include dir. For example c:/SFML/include
* Go to library directories and add the SFML 2 library dir. For example c:/SFML/lib

Copy SFML .dlls from the SFML directory in your project folder, build and run. If the game doesn't find data, copy the folder in Debug / Release folder.

### Linux

* Enter game's source directory
* mkdir build
* cd build
* cmake ..
* make
* cp -r ../data ./
* ./game_binary_here


### OS X

I dunno, I don't use Macs
