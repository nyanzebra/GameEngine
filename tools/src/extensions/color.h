#pragma once

#ifdef linux
#define reset_format 0
#define bold 1
#define underscore 4
#define blink 5
#define conceal 8

#define black 31
#define red 31
#define green 32
#define yellow 33
#define blue 34
#define purple 35
#define cyan 36
#define white 37

#define AS_BACKGROUND(color) color + 10
#else
#include <windows.h>
//some redefs for ease of switching between 'nix and windows
#define BLACK 0
#define GREY 8
#define BLUE 9
#define GREEN 10
#define CYAN 11
#define RED 12
#define PURPLE 13
#define YELLOW 14
#define WHITE 15

#define DARKER(color) color - 8
#define AS_BACKGROUND(color) color << 4
#define AS_ASCII(color) ((color < 10) ? color + 48: color + 55) 

#endif
