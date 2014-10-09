Tetris-3D
The traditional game of Tetris is rethought here by adding an extra dimension to it, making the gameplay more challenging and the aesthetics more appealing using the graphic capabilities of OpenGL.
The added 3rd dimension adds another degree of freedom to the rotations of a block exponentially increasing the number of possible configurations of the block object in 3-D space. The goal of traditional tetris was to clear 2 dimensional tiles by obtaining a continous row of horizontal tiles across the length of play area. In this game the player will have to aim to clear a cuboidal volume by achieving a completely filled horizontal level.  The gameplay would become more difficult with time by increasing the falling speed of the blocks. 
THE RULES OF THE GAME
Player starts out with an empty game volume.
Bricks falls at fixed intervals. Every next block is chosen randomly from the set of available blocks.
A brick freezes in its position and orientation once it touches the base of the game volume.
Player can rotate the brick using two keys. One rotates the block in horizontal plane. Other rotates it in the vertical plane. All possible space orientations of the block are achievable using this combination of two rotations.
A horizontal level is cleared if it contains no holes.
A player loses if the top of any block touches the ceiling of the game volume.
The fall speed of the blocks increases with time.

PROGRESS-I
Created a base for the falling blocks. The base defines the playable game volume.
Modelled 5 different type of blocks in Blender.
Created an .obj parser to parse the model files into OpenGL standards.
Wrote the library for displaying the parsed object models onto the viewport.
Have used basic materials ( only the diffuse, specular, ambient and illumination parameters, no textures or shadows yet) to render the objects.
Implemented a restrictedly navigable camera with rotation bound to translation bound together for a nice cinematic zoom effect.
Currently placed blocks into the game volume randomly.
Implemented basic block selection and movement (albeit without any animation).

PROGRESS-II
Added the animation effect.
Added the music.
Implemented some game logic.
Allow players to save screenshots.
Loading a character, that is, an object which is not part of the world. 
A navigable camera.


FURTHER WORK
These are the objectives that we plan to include in our game before final submission:
Designing a Heads-up Display (HUD) - the HUD will display the current player score, Game title in fancy text and a side window displaying the next block, highest score.
Implement an algorithm for evaluation of the game state at every timer tick. Need to define the possible states of each block in higher dimensional arrays and find a way to detect collision using these orientation arrays.
Implement texture mapping for the blocks.
Use ambient lights and particle effects to add visual appeal. Will make the blocks glow with a light.
Use raytracing( if feasible) or lightmaps to create realistic shadows.
Create smooth transition animations for going from one state to other.
(Optional gameplay element) Add the concept of powers. Bonuses that will destroy large volumes of blocks in single turn.
Add sound effects to game
Create a background score - either digital (launchpad or some other application) or create instrumental recordings.  
