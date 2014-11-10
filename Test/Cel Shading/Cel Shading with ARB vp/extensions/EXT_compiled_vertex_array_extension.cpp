//////////////////////////////////////////////////////////////////////////////////////////
//	EXT_compiled_vertex_array_extension.cpp
//	EXT_compiled_vertex_array extension setup
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	
#include <windows.h>
#include <GL\gl.h>
#include <GL\glext.h>
#include <GL\wglext.h>
#include "../LOG.h"
#include "EXT_compiled_vertex_array_extension.h"

extern LOG errorLog;

bool EXT_compiled_vertex_array_supported=false;

bool SetUpEXT_compiled_vertex_array()
{
	//Check for support
	char * extensionString=(char *)glGetString(GL_EXTENSIONS);
	char * extensionName="GL_EXT_compiled_vertex_array";

	char * endOfString;									//store pointer to end of string
	unsigned int distanceToSpace;						//distance to next space

	endOfString=extensionString+strlen(extensionString);

	//loop through string
	while(extensionString<endOfString)
	{
		//find distance to next space
		distanceToSpace=strcspn(extensionString, " ");

		//see if we have found extensionName
		if((strlen(extensionName)==distanceToSpace) &&
			(strncmp(extensionName, extensionString, distanceToSpace)==0))
		{
			EXT_compiled_vertex_array_supported=true;
		}

		//if not, move on
		extensionString+=distanceToSpace+1;
	}

	if(!EXT_compiled_vertex_array_supported)
	{
		errorLog.OutputError("EXT_compiled_vertex_array unsupported!");
		return false;
	}

	errorLog.OutputSuccess("EXT_compiled_vertex_array supported!");

	//get function pointers
	glLockArraysEXT					=	(PFNGLLOCKARRAYSEXTPROC)
										wglGetProcAddress("glLockArraysEXT");
	glUnlockArraysEXT				=	(PFNGLUNLOCKARRAYSEXTPROC)
										wglGetProcAddress("glUnlockArraysEXT");

	return true;
}

//function pointers
PFNGLLOCKARRAYSEXTPROC					glLockArraysEXT					=NULL;
PFNGLUNLOCKARRAYSEXTPROC				glUnlockArraysEXT				=NULL;

