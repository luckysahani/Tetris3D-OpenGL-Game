**************************************************************************
**	Cel Shading
**
**	www.paulsprojects.net
**
**	paul@paulsprojects.net
**************************************************************************

Description:

This program displays a torus rendered with "cartoon lighting". The dot product between the normal and light vector is performed in object space, and used as a lookup into a 1D texture with "sharp lighting" values. The dot product is computed manually, or using a vertex program. The back faces are then drawn in wireframe mode to create an outline.

The download for this project contains two separate versions, one using NV_vertex_program to perform the lighting calculations and one using ARB_vertex_program. 


Requirements:

EXT_compiled_vertex_array
EXT_texture_edge_clamp

Required for vertex program calculations:
NV_vertex_program/ARB_vertex_program


References:

Cel-Shading by Sami "MENTAL" Hamlaoui. From www.gamedev.net


Keys:

F1	-	Take a screenshot
Escape	-	Quit

1	-	Use manual cartoon lighting calculations
2	-	Use vertex program

Up Arrow-	Increase outline width
Down Arrow-	Decrease outline width

Use the mouse to spin the object.
