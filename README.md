# cpp & gtk4.

## install gtk4, ubuntu 22.04
$ sudo apt install libgtk-4-dev

## compile C
$ gcc $( pkg-config --cflags gtk4 ) -o main main.c $( pkg-config --libs gtk4 )

## compile C++11
$ gcc $( pkg-config --cflags gtk4 ) -o main main.cpp $( pkg-config --libs gtk4 )
$ g++ $( pkg-config --cflags gtk4 ) -o main main.cpp $( pkg-config --libs gtk4 )

## compile c++17
$ g++ -std=c++17 $( pkg-config --cflags gtk4 ) -o main main.cpp $( pkg-config --libs gtk4 )

## compile c++20
$ g++ -std=c++20 $( pkg-config --cflags gtk4 ) -o main main.cpp $( pkg-config --libs gtk4 )

## run de app
./main

