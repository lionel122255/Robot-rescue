# Robo Rescue

<h1>Robo Rescue</h1>

<p align="center">
  <img src="./display/Capture d&apos;écran 2026-06-13 174929.png" width="800">
</p>



**Author:** Lionel DOFONHAKOU

## Overview

Robo Rescue is a 2D maze-based game developed in **C** using the **SDL2** library and its extensions (**SDL_image**, **SDL_ttf**, and **SDL_mixer**).

The player controls a robot whose objective is to reach the exit of the level while managing limited resources and overcoming various obstacles scattered throughout the map.

The main purpose of this project was to become familiar with SDL2 and graphical programming in C, while revisiting several fundamental concepts studied during programming courses.

## Educational Objectives

This project was designed to practice and reinforce the following concepts:

* Modular programming in C
* Dynamic memory allocation
* Structures and enumerations
* File handling
* Event-driven programming
* 2D graphics rendering with SDL2
* Texture management
* Keyboard input handling
* Sound and music integration
* Project organization using multiple source files
* Compilation automation with Makefiles
* Version control with Git and GitHub
* Memory debugging using Valgrind

## Game Description

The player starts in the upper-left area of the map and must reach the exit represented by a yellow star.

Several types of tiles can be encountered during the game:

| Tile   | Description                       |
| ------ | --------------------------------- |
| Grass  | Standard traversable tile         |
| Flower | Grants additional movement points |
| Sand   | Grants additional water units     |
| Fire   | Requires water to be crossed      |
| Wall   | Blocks movement                   |
| Star   | Level exit                        |

The player must manage three resources:

* **MOVE**: available movement points
* **WATER**: water supply used to extinguish fire
* **TIME**: remaining time before the game ends

The player wins by reaching the exit before running out of resources.

The player loses when either the time counter or the available movement points reach zero.

## Installation

### Required Dependencies

On Ubuntu / WSL:

```bash
sudo apt update

sudo apt install build-essential
sudo apt install libsdl2-dev
sudo apt install libsdl2-image-dev
sudo apt install libsdl2-ttf-dev
sudo apt install libsdl2-mixer-dev
sudo apt install valgrind
```

## Clone the Repository

```bash
git clone <repository-url>
cd robo-rescue
```

## Build the Project

```bash
make
```

## Run the Game

Launch a specific level:

```bash
make level1
```

```bash
make level2
```

```bash
make level3
```

```bash
make level4
```

```bash
make level5
```

You may also launch the executable manually:

```bash
./main map/level1.txt
```

## Controls

| Key          | Action               |
| ------------ | -------------------- |
| ↑            | Move up              |
| ↓            | Move down            |
| ←            | Move left            |
| →            | Move right           |
| M            | Pause / Resume music |
| Close Window | Quit game            |

## Project Structure

```text
robo-rescue/
│
├── include/
│   ├── game.h
│   ├── map.h
│   ├── player.h
│   └── render.h
│
├── src/
│   ├── game.c
│   ├── map.c
│   ├── player.c
│   ├── render.c
│   └── main.c
│
├── map/
│   ├── level1.txt
│   ├── level2.txt
│   ├── level3.txt
│   ├── level4.txt
│   └── level5.txt
│
├── display/
│   ├── textures
│   ├── sounds
│   ├── music
│   └── fonts
│
├── build/
├── Makefile
└── README.md
```

## Memory Verification

The project was tested using Valgrind to detect memory leaks:

```bash
make valgrind
```

## Future Improvements

Possible future enhancements include:

* Main menu
* Animated sprites
* Additional sound effects
* Enemy AI
* Procedural level generation
* Save system
* Score system
* Difficulty levels
* Leaderboard

## Acknowledgments

This project was developed as a personal learning exercise to explore SDL2 and strengthen practical programming skills in C.

