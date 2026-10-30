# Tic-Tac-Toe in C

A two-player, command-line Tic-Tac-Toe game written in C. Players enter their names and take turns marking squares on a numbered 3×3 board. The game detects wins and draws, then saves the result and date and time to a history file.

## Features

- Two-player gameplay
- Player names displayed during turns
- Numbered 3×3 board
- Win and draw detection
- Input checks for invalid and already occupied squares
- Results appended to `GAME RESULT HISTORY.txt` with the date and time
- Colored X and O marks in supported terminals

## Requirements

- A C compiler, such as GCC

## Compile

```bash
gcc tictactoe.c -o tictactoe
