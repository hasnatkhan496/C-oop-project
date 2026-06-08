# C-oop-project
GUI base chess game using raylib 
# My Chess

A GUI-based Chess game built using C++ and Raylib.  
The project focuses on clean game logic, smooth rendering, and proper chess rules implementation.

---

## About

This is a two-player Chess game with a graphical interface.  
It is developed using C++ and Raylib for rendering the board and pieces.

The game supports all standard chess rules including valid moves, check detection, and checkmate.

---

## Features

- Graphical chess board using Raylib  
- Piece movement with mouse interaction  
- Valid move highlighting  
- Check detection  
- Checkmate detection  
- Turn-based gameplay  
- Smooth and responsive UI  

---

## Screenshots

### Starting Board
<img width="1010" height="1000" alt="screenshot-2026-05-10_23-10-47" src="https://github.com/user-attachments/assets/8793ac5b-bf01-430c-a1d6-2f5c2a83b196" />


### Valid Moves Highlighted
<img width="988" height="987" alt="screenshot-2026-05-10_23-11-22" src="https://github.com/user-attachments/assets/89c60dea-c587-430f-bcf6-1f3427d2329d" />


### Check Situation
<img width="986" height="1000" alt="screenshot-2026-05-10_23-11-40" src="https://github.com/user-attachments/assets/98020e5e-f51b-43e3-8360-484bd36aacae" />


### Checkmate
<img width="993" height="996" alt="screenshot-2026-05-10_23-12-12" src="https://github.com/user-attachments/assets/98abd3ef-526d-4d69-8c2a-7cc37ff60704" />


---


## Project Structure

```text
My-Chess/
├── src/
│   ├── board.cpp / board.h
│   ├── game.cpp / game.h
│   ├── pieces.cpp / pieces.h
│   └── main.cpp
├── sounds/
├── pieces_png/
├── CMakeLists.txt
└── README.md
```
---

## How to Run

```bash
mkdir build
cd build
cmake ..
make
./chess
