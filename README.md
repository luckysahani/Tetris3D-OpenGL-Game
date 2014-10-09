**Tetris-3D**

--------------------------------------------------------------------------

**PROGRESS-I**

Created a base for the falling blocks. The base defines the playable game volume.
Modelled 5 different type of blocks in Blender.
Created an .obj parser to parse the model files into OpenGL standards.
Wrote the library for displaying the parsed object models onto the viewport.
Have used basic materials ( only the diffuse, specular, ambient and illumination parameters, no textures or shadows yet) to render the objects.
Implemented a restrictedly navigable camera with rotation bound to translation bound together for a nice cinematic zoom effect.
Currently placed blocks into the game volume randomly.
Implemented basic block selection and movement (albeit without any animation).

--------------------------------------------------------------------------

**PROGRESS-II**

Added the animation effect.
Added the music.
Implemented some game logic.
Allow players to save screenshots.
Loading a character, that is, an object which is not part of the world. 
A navigable camera.

--------------------------------------------------------------------------

**Instructions for compilation**

1.	Install OpenGl and OpenAl -
	OpenGL: sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
	OpenAL: sudo apt-get install libopenal0a libopenal-dev
	ALUT:   sudo apt-get install libalut0 libalut-dev

2.	Makefile in Project folder contains the compilation commnads. So , just make and your executable will be ready.

--------------------------------------------------------------------------

**Controls**

A : Move along x-axis
S : Move along y-axis
D : Move along x-axis(opposite to A)
W : Move along y-axis(opposite to S)
B : Move above the z axis
N : Move below the z axis
Z : Screenshot
X : Exit