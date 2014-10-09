***Tetris-3D***

--------------------------------------------------------------------------

The traditional game of Tetris is rethought here by adding an extra dimension to it, making the gameplay more challenging and the aesthetics more appealing using the graphic capabilities of OpenGL.
The added 3rd dimension adds another degree of freedom to the rotations of a block exponentially increasing the number of possible configurations of the block object in 3-D space. The goal of traditional tetris was to clear 2 dimensional tiles by obtaining a continous row of horizontal tiles across the length of play area. In this game the player will have to aim to clear a cuboidal volume by achieving a completely filled horizontal level.  The gameplay would become more difficult with time by increasing the falling speed of the blocks. 

--------------------------------------------------------------------------

**THE RULES OF THE GAME**

1.	Player starts out with an empty game volume.
2.	Bricks falls at fixed intervals. Every next block is chosen randomly from the set of available blocks.
3.	A brick freezes in its position and orientation once it touches the base of the game volume.
4.	Player can rotate the brick using two keys. One rotates the block in horizontal plane. Other rotates it in the vertical 	plane. All possible space orientations of the block are achievable using this combination of two rotations.
5.	A horizontal level is cleared if it contains no holes.
6.	A player loses if the top of any block touches the ceiling of the game volume.
7.	The fall speed of the blocks increases with time.

--------------------------------------------------------------------------

**Instructions for compilation**

1.	Install OpenGl and OpenAl -
	OpenGL: sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
	OpenAL: sudo apt-get install libopenal0a libopenal-dev
	ALUT:   sudo apt-get install libalut0 libalut-dev

2.	Makefile in Project folder contains the compilation commnads. So , just make and your executable will be ready.

--------------------------------------------------------------------------

**PROGRESS-I**

1.	Created a base for the falling blocks. The base defines the playable game volume.
2.	Modelled 5 different type of blocks in Blender.
3.	Created an .obj parser to parse the model files into OpenGL standards.
4.	Wrote the library for displaying the parsed object models onto the viewport.
5.	Have used basic materials ( only the diffuse, specular, ambient and illumination parameters, no textures or shadows 		yet) to render the objects.
6.	Implemented a restrictedly navigable camera with rotation bound to translation bound together for a nice cinematic zoom 	effect.
7.	Currently placed blocks into the game volume randomly.
8.	Implemented basic block selection and movement (albeit without any animation).

--------------------------------------------------------------------------

**PROGRESS-II**

1.	Implemented falling animation for blocks.
2.	Added the background music and button triggered sounds.
3.	Implemented partial game logic.
4.	Allow players to save screenshots.
5.	Loading a character, that is, an object which is not part of the world. 
6.	A navigable camera.

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

Arrow Keys : Sample sound for block move (implemented as test for now)

Mouse Left Click & Right Click (Hold) and drag : Navigate camera

--------------------------------------------------------------------------

**FURTHER WORK**

1.	These are the objectives that we plan to include in our game before final submission:
2.	Designing a Heads-up Display (HUD) - the HUD will display the current player score, Game title in fancy text and a side 	window displaying the next block, highest score.
3.	Implement an algorithm for evaluation of the game state at every timer tick. Need to define the possible states of each 	block in higher dimensional arrays and find a way to detect collision using these orientation arrays.
4.	Implement texture mapping for the blocks.
5.	Use ambient lights and particle effects to add visual appeal. Will make the blocks glow with a light.
6.	Use raytracing( if feasible) or lightmaps to create realistic shadows.
7.	Create smooth transition animations for going from one state to other.
8.	(Optional gameplay element) Add the concept of powers. Bonuses that will destroy large volumes of blocks in single turn.
9.	Add sound effects to game
10.	Create a background score - either digital (launchpad or some other application) or create instrumental recordings.  
