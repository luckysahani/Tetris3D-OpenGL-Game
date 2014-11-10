//////////////////////////////////////////////////////////////////////////////////////////
//	NV_vertex_program.cpp
//	functions for a vertex program
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	

#include <windows.h>
#include <fstream>
#include <GL\gl.h>
#include <GL\glext.h>
#include "LOG.h"
#include "extensions/NV_vertex_program_extension.h"

extern LOG errorLog;

bool LoadNV_vertex_program(char * filename, GLuint programID)
{
	//load from file
	std::ifstream vpFile(filename, std::ios::in | std::ios::binary);
	if(vpFile.fail())
	{
		printf("Unable to open vertex program\n");
		return false;
	}

	//calculate the size of the file
	vpFile.seekg(0, std::ios::end);
	int vpSize=vpFile.tellg();
	vpFile.seekg(0, std::ios::beg);
	
	//allocate memory
	unsigned char * vpText=new unsigned char[vpSize];
	if(!vpText)
	{
		printf("Unable to allocate space for vertex program text\n");
		return false;
	}

	//read file
	vpFile.read(reinterpret_cast<char *>(vpText), vpSize);
	vpFile.close();

	//load program
	glLoadProgramNV(GL_VERTEX_PROGRAM_NV, programID, vpSize, vpText);
	
	if(vpText)
		delete [] vpText;
	vpText=NULL;

	//Output if there was an error
	int errorPos;
	glGetIntegerv(GL_PROGRAM_ERROR_POSITION_NV, &errorPos);
	if(errorPos!=-1)
	{
		errorLog.OutputError("Program error at position %d in %s\n", errorPos, filename);
		return false;
	}

	return true;
}