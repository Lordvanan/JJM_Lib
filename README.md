
```
    ___        ___  _____ ______           ___       ___  ________     
   |\  \      |\  \|\   _ \  _   \        |\  \     |\  \|\   __  \    
   \ \  \     \ \  \ \  \\\__\ \  \       \ \  \    \ \  \ \  \|\ /_   
 __ \ \  \  __ \ \  \ \  \\|__| \  \       \ \  \    \ \  \ \   __  \  
|\  \\_\  \|\  \\_\  \ \  \    \ \  \       \ \  \____\ \  \ \  \|\  \ 
\ \________\ \________\ \__\    \ \__\       \ \_______\ \__\ \_______\
 \|________|\|________|\|__|     \|__|        \|_______|\|__|\|_______|
```
 *********************************************************************
 This is my personal project for the purpose of streamlining creating
 routine features used in my school assignments. This library makes
 creating feature full console applications fast and easy.

 Here's what you need to get started using this library.
 First, you'll need to link the library in your project.
 I use CMake in my projects, so here is my setup for a single file:

    cmake_minimum_required(VERSION 3.23.3)
    project(MyProject VERSION 1.0 LANGUAGES CXX C)

    add_subdirectory(../JJM_Lib JJM_Lib_build)

    add_executable(MyProject)
    target_sources(MyProject PRIVATE main.cpp)

    target_link_libraries(MyProject PUBLIC JJM_Lib)