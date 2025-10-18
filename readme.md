# Chip-8 Emulator

A high-performance **Chip-8 emulator** implemented in C using **SDL2** for graphics rendering. This emulator executes classic Chip-8 programs (ROMs) and closely follows the original memory layout and instruction set architecture (ISA), with minor modifications for improved clarity and usability.

---

## Table of Contents

- [Chip-8 Emulator](#chip-8-emulator)
  - [Table of Contents](#table-of-contents)
  - [Features](#features)
  - [Project Structure](#project-structure)
  - [Requirements](#requirements)
  - [Installation](#installation)
  - [Usage](#usage)
  - [memory layout ( from blog i used )](#memory-layout--from-blog-i-used-)
  - [References](#references)

---

## Features

- Implements the **core Chip-8 CPU and memory architecture**.  
- Utilizes **SDL2** to render pixels directly from memory.  
- Handles user input events and display updates in real time.  
- Supports loading and running standard Chip-8 ROMs, including:  
  - BMP Viewer - Hello  
  - IBM Logo  

---

## Project Structure

.
├── makefile
├── readme
├── roms
│ ├── BMP Viewer - Hello (C8 example) [Hap, 2005].ch8
│ └── IBM Logo.ch8
└── src
├── cpu.c
├── cpu.h
├── display.c
├── display.h
├── input.c
├── input.h
└── main.c
- `src/` – Source code for CPU, display, input handling, and main program.  
- `roms/` – Sample Chip-8 ROMs for testing.  
- `makefile` – Build instructions to compile the emulator.  

---

## Requirements

- **SDL2** (graphics rendering)  
- **Make** (build tool)  
- **Clang** or compatible C compiler  

Install dependencies on Ubuntu/Debian:

```bash
sudo apt install libsdl2-dev libsdl2-2.0-0 make clang
```
## Installation

- Clone or download the project.

- Navigate to the project root directory.

- Compile the emulator using:
  
```bash
    make
```

This will generate the executable chip8.

## Usage

Run the emulator with a ROM file as an argument:
```bash
./chip8 <path-to-rom>
```
Example:
```bash
./chip8 ./roms/IBM\ Logo.ch8
```

## memory layout ( from blog i used )
```
 ADDRESS                                         CONTENT
 ~~~~~~~                                         ~~~~~~~

   0x000  --------------------------------  <--  Start of RAM
          |                              |
          |  Interpreter code, fonts     |
          |                              |
   0x200  --------------------------------  <--  Start of user programs
          |                              |
          |                              |
          |      User programs and       |
          |        data go here          |
          |                              |
          |                              |
   0x600  ................................  <--  Start of user programs (ETI 660)
          |                              |
          |                              |
          |                              |
          |                              |
          |      User programs and       |
          |        data go here          |
          |                              |
          |                              |
          |                              |
          |                              |
   0xFFF  --------------------------------  <--  End of RAM
```
## References
- [Chip-8 Specification by Tonis Agrista]("https://tonisagrista.com/blog/2021/chip8-spec/#jmp-v0-nnn--bnnn") – Detailed opcode reference.
- SDL2 official documentation for graphics ( used ai as it was a bit difficult to understand at first ) and input handling ( read code and referred docs ).
- The readme is also mostly  AI generated. Just formatted into markdown format myself.

