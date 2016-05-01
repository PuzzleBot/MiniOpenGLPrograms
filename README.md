# MiniOpenGLPrograms
This repository contains my work for the Computer Graphics course at the University of Guelph. Each directory contains a separate program produced for each assignment. For information on how to use each program, read the corresponding README files in each directory. 
All programs require the OpenGL libraries to be installed, and have been designed specifically to operate on Macs. Some of the early programs were built up from OpenGL examples from their website.
Each directory also contains a "Specifications.txt" file under the docs directory which contain the outline of the problem to be solved, given by the professor of the course when the assignment was given.

## a1: Simple shape transformations
This is a simple program which displays tranformed spheres, cubes and cones from a file containing specifications. Each object specification defines which object is displayed (sphere, cube or cone), its initial transformation, an offset transformation, and how many times the offset transformation should be performed. 
The shape after EVERY offset tranformation is displayed.

## a2: Heightmap display and shading
This is a program which displays a heightmap from a file, and can apply different types of shading and colour schemes to the heightmap.

## a3: Textures and Fake Shadows
This program displays a simple scene consisting of a textured cube on a plane with a light rotating in a circle above the cube. The scene also creates a Jim Blinn fake shadow casting from the cube onto the plane, corresponding to the rotating light.

## a4: Ray Tracing
This program is a simple ray tracer which generates a scene of spheres with a single light source, based on a specification file. This one is a bit buggy, but is functional enough to demonstrate the techniques of ray tracing.



