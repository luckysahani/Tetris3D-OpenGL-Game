//////////////////////////////////////////////////////////////////////////////////////////
//	NV_vertex_program_extension.cpp
//	NV_vertex_program extension setup
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
#include "NV_vertex_program_extension.h"

extern LOG errorLog;

bool NV_vertex_program_supported=false;

bool SetUpNV_vertex_program()
{
	//Check for support
	char * extensionString=(char *)glGetString(GL_EXTENSIONS);
	char * extensionName="GL_NV_vertex_program";

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
			NV_vertex_program_supported=true;
		}

		//if not, move on
		extensionString+=distanceToSpace+1;
	}

	if(!NV_vertex_program_supported)
	{
		errorLog.OutputError("NV_vertex_program unsupported!");
		return false;
	}

	errorLog.OutputSuccess("NV_vertex_program supported!");

	//get function pointers
	glBindProgramNV						=	(PFNGLBINDPROGRAMNVPROC)
											wglGetProcAddress("glBindProgramNV");
	glDeleteProgramsNV					=	(PFNGLDELETEPROGRAMSNVPROC)
											wglGetProcAddress("glDeleteProgramsNV");
	glExecuteProgramNV					=	(PFNGLEXECUTEPROGRAMNVPROC)
											wglGetProcAddress("glExecuteProgramNV");
	glGenProgramsNV						=	(PFNGLGENPROGRAMSNVPROC)
											wglGetProcAddress("glGenProgramsNV");
	
	glAreProgramsResidentNV				=	(PFNGLAREPROGRAMSRESIDENTNVPROC)
											wglGetProcAddress("glAreProgramsResidentNV");
	glRequestResidentProgramsNV			=	(PFNGLREQUESTRESIDENTPROGRAMSNVPROC)
											wglGetProcAddress("glRequestResidentProgramsNV");

	glGetProgramParameterfvNV			=	(PFNGLGETPROGRAMPARAMETERFVNVPROC)
											wglGetProcAddress("glGetProgramParameterfvNV");
	glGetProgramParameterdvNV			=	(PFNGLGETPROGRAMPARAMETERDVNVPROC)
											wglGetProcAddress("glGetProgramParameterdvNV");

	glGetProgramivNV					=	(PFNGLGETPROGRAMIVNVPROC)
											wglGetProcAddress("glGetProgramivNV");
	glGetProgramStringNV				=	(PFNGLGETPROGRAMSTRINGNVPROC)
											wglGetProcAddress("glGetProgramStringNV");
	glGetTrackMatrixivNV				=	(PFNGLGETTRACKMATRIXIVNVPROC)
											wglGetProcAddress("glGetTrackMatrixivNV");

	glGetVertexAttribdvNV				=	(PFNGLGETVERTEXATTRIBDVNVPROC)
											wglGetProcAddress("glGetVertexAttribdvNV");
	glGetVertexAttribfvNV				=	(PFNGLGETVERTEXATTRIBFVNVPROC)
											wglGetProcAddress("glGetVertexAttribfvNV");
	glGetVertexAttribivNV				=	(PFNGLGETVERTEXATTRIBIVNVPROC)
											wglGetProcAddress("glGetVertexAttribivNV");

	glGetVertexAttribPointervNV			=	(PFNGLGETVERTEXATTRIBPOINTERVNVPROC)
											wglGetProcAddress("glGetVertexAttribPointervNV");

	glIsProgramNV						=	(PFNGLISPROGRAMNVPROC)
											wglGetProcAddress("glIsProgramNV");

	glLoadProgramNV						=	(PFNGLLOADPROGRAMNVPROC)
											wglGetProcAddress("glLoadProgramNV");

	glProgramParameter4fNV				=	(PFNGLPROGRAMPARAMETER4FNVPROC)
											wglGetProcAddress("glProgramParameter4fNV");
	glProgramParameter4dNV				=	(PFNGLPROGRAMPARAMETER4DNVPROC)
											wglGetProcAddress("glProgramParameter4dNV");
	
	glProgramParameter4fvNV				=	(PFNGLPROGRAMPARAMETER4FVNVPROC)
											wglGetProcAddress("glProgramParameter4fvNV");
	glProgramParameter4dvNV				=	(PFNGLPROGRAMPARAMETER4DVNVPROC)
											wglGetProcAddress("glProgramParameter4dvNV");

	glProgramParameters4fvNV			=	(PFNGLPROGRAMPARAMETERS4FVNVPROC)
											wglGetProcAddress("glProgramParameters4fvNV");
	glProgramParameters4dvNV			=	(PFNGLPROGRAMPARAMETERS4DVNVPROC)
											wglGetProcAddress("glProgramParameters4dvNV");

	glTrackMatrixNV						=	(PFNGLTRACKMATRIXNVPROC)
											wglGetProcAddress("glTrackMatrixNV");

	glVertexAttribPointerNV				=	(PFNGLVERTEXATTRIBPOINTERNVPROC)
											wglGetProcAddress("glVertexAttribPointerNV");

	glVertexAttrib1sNV					=	(PFNGLVERTEXATTRIB1SNVPROC)
											wglGetProcAddress("glVertexAttrib1sNV");
	glVertexAttrib1fNV					=	(PFNGLVERTEXATTRIB1FNVPROC)
											wglGetProcAddress("glVertexAttrib1fNV");
	glVertexAttrib1dNV					=	(PFNGLVERTEXATTRIB1DNVPROC)
											wglGetProcAddress("glVertexAttrib1dNV");
	glVertexAttrib2sNV					=	(PFNGLVERTEXATTRIB2SNVPROC)
											wglGetProcAddress("glVertexAttrib2sNV");
	glVertexAttrib2fNV					=	(PFNGLVERTEXATTRIB2FNVPROC)
											wglGetProcAddress("glVertexAttrib2fNV");
	glVertexAttrib2dNV					=	(PFNGLVERTEXATTRIB2DNVPROC)
											wglGetProcAddress("glVertexAttrib2dNV");
	glVertexAttrib3sNV					=	(PFNGLVERTEXATTRIB3SNVPROC)
											wglGetProcAddress("glVertexAttrib3sNV");
	glVertexAttrib3fNV					=	(PFNGLVERTEXATTRIB3FNVPROC)
											wglGetProcAddress("glVertexAttrib3fNV");
	glVertexAttrib3dNV					=	(PFNGLVERTEXATTRIB3DNVPROC)
											wglGetProcAddress("glVertexAttrib3dNV");
	glVertexAttrib4sNV					=	(PFNGLVERTEXATTRIB4SNVPROC)
											wglGetProcAddress("glVertexAttrib4sNV");
	glVertexAttrib4fNV					=	(PFNGLVERTEXATTRIB4FNVPROC)
											wglGetProcAddress("glVertexAttrib4fNV");
	glVertexAttrib4dNV					=	(PFNGLVERTEXATTRIB4DNVPROC)
											wglGetProcAddress("glVertexAttrib4dNV");
	glVertexAttrib4ubNV					=	(PFNGLVERTEXATTRIB4UBNVPROC)
											wglGetProcAddress("glVertexAttrib4ubNV");


	glVertexAttrib1svNV					=	(PFNGLVERTEXATTRIB1SVNVPROC)
											wglGetProcAddress("glVertexAttrib1svNV");
	glVertexAttrib1fvNV					=	(PFNGLVERTEXATTRIB1FVNVPROC)
											wglGetProcAddress("glVertexAttrib1fvNV");
	glVertexAttrib1dvNV					=	(PFNGLVERTEXATTRIB1DVNVPROC)
											wglGetProcAddress("glVertexAttrib1dvNV");
	glVertexAttrib2svNV					=	(PFNGLVERTEXATTRIB2SVNVPROC)
											wglGetProcAddress("glVertexAttrib2svNV");
	glVertexAttrib2fvNV					=	(PFNGLVERTEXATTRIB2FVNVPROC)
											wglGetProcAddress("glVertexAttrib2fvNV");
	glVertexAttrib2dvNV					=	(PFNGLVERTEXATTRIB2DVNVPROC)
											wglGetProcAddress("glVertexAttrib2dvNV");
	glVertexAttrib3svNV					=	(PFNGLVERTEXATTRIB3SVNVPROC)
											wglGetProcAddress("glVertexAttrib3svNV");
	glVertexAttrib3fvNV					=	(PFNGLVERTEXATTRIB3FVNVPROC)
											wglGetProcAddress("glVertexAttrib3fvNV");
	glVertexAttrib3dvNV					=	(PFNGLVERTEXATTRIB3DVNVPROC)
											wglGetProcAddress("glVertexAttrib3dvNV");
	glVertexAttrib4svNV					=	(PFNGLVERTEXATTRIB4SVNVPROC)
											wglGetProcAddress("glVertexAttrib4svNV");
	glVertexAttrib4fvNV					=	(PFNGLVERTEXATTRIB4FVNVPROC)
											wglGetProcAddress("glVertexAttrib4fvNV");
	glVertexAttrib4dvNV					=	(PFNGLVERTEXATTRIB4DVNVPROC)
											wglGetProcAddress("glVertexAttrib4dvNV");
	glVertexAttrib4ubvNV				=	(PFNGLVERTEXATTRIB4UBVNVPROC)
											wglGetProcAddress("glVertexAttrib4ubvNV");

	glVertexAttribs1svNV				=	(PFNGLVERTEXATTRIBS1SVNVPROC)
											wglGetProcAddress("glVertexAttribs1svNV");
	glVertexAttribs1fvNV				=	(PFNGLVERTEXATTRIBS1FVNVPROC)
											wglGetProcAddress("glVertexAttribs1fvNV");
	glVertexAttribs1dvNV				=	(PFNGLVERTEXATTRIBS1DVNVPROC)
											wglGetProcAddress("glVertexAttribs1dvNV");
	glVertexAttribs2svNV				=	(PFNGLVERTEXATTRIBS2SVNVPROC)
											wglGetProcAddress("glVertexAttribs2svNV");
	glVertexAttribs2fvNV				=	(PFNGLVERTEXATTRIBS2FVNVPROC)
											wglGetProcAddress("glVertexAttribs2fvNV");
	glVertexAttribs2dvNV				=	(PFNGLVERTEXATTRIBS2DVNVPROC)
											wglGetProcAddress("glVertexAttribs2dvNV");
	glVertexAttribs3svNV				=	(PFNGLVERTEXATTRIBS3SVNVPROC)
											wglGetProcAddress("glVertexAttribs3svNV");
	glVertexAttribs3fvNV				=	(PFNGLVERTEXATTRIBS3FVNVPROC)
											wglGetProcAddress("glVertexAttribs3fvNV");
	glVertexAttribs3dvNV				=	(PFNGLVERTEXATTRIBS3DVNVPROC)
											wglGetProcAddress("glVertexAttribs3dvNV");
	glVertexAttribs4svNV				=	(PFNGLVERTEXATTRIBS4SVNVPROC)
											wglGetProcAddress("glVertexAttribs4svNV");
	glVertexAttribs4fvNV				=	(PFNGLVERTEXATTRIBS4FVNVPROC)
											wglGetProcAddress("glVertexAttribs4fvNV");
	glVertexAttribs4dvNV				=	(PFNGLVERTEXATTRIBS4DVNVPROC)
											wglGetProcAddress("glVertexAttribs4dvNV");
	glVertexAttribs4ubvNV				=	(PFNGLVERTEXATTRIBS4UBVNVPROC)
											wglGetProcAddress("glVertexAttribs4ubvNV");

	return true;
}

PFNGLBINDPROGRAMNVPROC						glBindProgramNV					=NULL;
PFNGLDELETEPROGRAMSNVPROC					glDeleteProgramsNV				=NULL;
PFNGLEXECUTEPROGRAMNVPROC					glExecuteProgramNV				=NULL;
PFNGLGENPROGRAMSNVPROC						glGenProgramsNV					=NULL;
	
PFNGLAREPROGRAMSRESIDENTNVPROC				glAreProgramsResidentNV			=NULL;
PFNGLREQUESTRESIDENTPROGRAMSNVPROC			glRequestResidentProgramsNV		=NULL;

PFNGLGETPROGRAMPARAMETERFVNVPROC			glGetProgramParameterfvNV		=NULL;
PFNGLGETPROGRAMPARAMETERDVNVPROC			glGetProgramParameterdvNV		=NULL;

PFNGLGETPROGRAMIVNVPROC						glGetProgramivNV				=NULL;
PFNGLGETPROGRAMSTRINGNVPROC					glGetProgramStringNV			=NULL;
PFNGLGETTRACKMATRIXIVNVPROC					glGetTrackMatrixivNV			=NULL;

PFNGLGETVERTEXATTRIBDVNVPROC				glGetVertexAttribdvNV			=NULL;
PFNGLGETVERTEXATTRIBFVNVPROC				glGetVertexAttribfvNV			=NULL;
PFNGLGETVERTEXATTRIBIVNVPROC				glGetVertexAttribivNV			=NULL;

PFNGLGETVERTEXATTRIBPOINTERVNVPROC			glGetVertexAttribPointervNV		=NULL;

PFNGLISPROGRAMNVPROC						glIsProgramNV					=NULL;

PFNGLLOADPROGRAMNVPROC						glLoadProgramNV					=NULL;

PFNGLPROGRAMPARAMETER4FNVPROC				glProgramParameter4fNV			=NULL;
PFNGLPROGRAMPARAMETER4DNVPROC				glProgramParameter4dNV			=NULL;
	
PFNGLPROGRAMPARAMETER4FVNVPROC				glProgramParameter4fvNV			=NULL;
PFNGLPROGRAMPARAMETER4DVNVPROC				glProgramParameter4dvNV			=NULL;

PFNGLPROGRAMPARAMETERS4FVNVPROC				glProgramParameters4fvNV		=NULL;
PFNGLPROGRAMPARAMETERS4DVNVPROC				glProgramParameters4dvNV		=NULL;

PFNGLTRACKMATRIXNVPROC						glTrackMatrixNV					=NULL;

PFNGLVERTEXATTRIBPOINTERNVPROC				glVertexAttribPointerNV			=NULL;

PFNGLVERTEXATTRIB1SNVPROC					glVertexAttrib1sNV				=NULL;
PFNGLVERTEXATTRIB1FNVPROC					glVertexAttrib1fNV				=NULL;
PFNGLVERTEXATTRIB1DNVPROC					glVertexAttrib1dNV				=NULL;
PFNGLVERTEXATTRIB2SNVPROC					glVertexAttrib2sNV				=NULL;
PFNGLVERTEXATTRIB2FNVPROC					glVertexAttrib2fNV				=NULL;
PFNGLVERTEXATTRIB2DNVPROC					glVertexAttrib2dNV				=NULL;
PFNGLVERTEXATTRIB3SNVPROC					glVertexAttrib3sNV				=NULL;
PFNGLVERTEXATTRIB3FNVPROC					glVertexAttrib3fNV				=NULL;
PFNGLVERTEXATTRIB3DNVPROC					glVertexAttrib3dNV				=NULL;
PFNGLVERTEXATTRIB4SNVPROC					glVertexAttrib4sNV				=NULL;
PFNGLVERTEXATTRIB4FNVPROC					glVertexAttrib4fNV				=NULL;
PFNGLVERTEXATTRIB4DNVPROC					glVertexAttrib4dNV				=NULL;
PFNGLVERTEXATTRIB4UBNVPROC					glVertexAttrib4ubNV				=NULL;

PFNGLVERTEXATTRIB1SVNVPROC					glVertexAttrib1svNV				=NULL;
PFNGLVERTEXATTRIB1FVNVPROC					glVertexAttrib1fvNV				=NULL;
PFNGLVERTEXATTRIB1DVNVPROC					glVertexAttrib1dvNV				=NULL;
PFNGLVERTEXATTRIB2SVNVPROC					glVertexAttrib2svNV				=NULL;
PFNGLVERTEXATTRIB2FVNVPROC					glVertexAttrib2fvNV				=NULL;
PFNGLVERTEXATTRIB2DVNVPROC					glVertexAttrib2dvNV				=NULL;
PFNGLVERTEXATTRIB3SVNVPROC					glVertexAttrib3svNV				=NULL;
PFNGLVERTEXATTRIB3FVNVPROC					glVertexAttrib3fvNV				=NULL;
PFNGLVERTEXATTRIB3DVNVPROC					glVertexAttrib3dvNV				=NULL;
PFNGLVERTEXATTRIB4SVNVPROC					glVertexAttrib4svNV				=NULL;
PFNGLVERTEXATTRIB4FVNVPROC					glVertexAttrib4fvNV				=NULL;
PFNGLVERTEXATTRIB4DVNVPROC					glVertexAttrib4dvNV				=NULL;
PFNGLVERTEXATTRIB4UBVNVPROC					glVertexAttrib4ubvNV			=NULL;

PFNGLVERTEXATTRIBS1SVNVPROC					glVertexAttribs1svNV			=NULL;
PFNGLVERTEXATTRIBS1FVNVPROC					glVertexAttribs1fvNV			=NULL;
PFNGLVERTEXATTRIBS1DVNVPROC					glVertexAttribs1dvNV			=NULL;
PFNGLVERTEXATTRIBS2SVNVPROC					glVertexAttribs2svNV			=NULL;
PFNGLVERTEXATTRIBS2FVNVPROC					glVertexAttribs2fvNV			=NULL;
PFNGLVERTEXATTRIBS2DVNVPROC					glVertexAttribs2dvNV			=NULL;
PFNGLVERTEXATTRIBS3SVNVPROC					glVertexAttribs3svNV			=NULL;
PFNGLVERTEXATTRIBS3FVNVPROC					glVertexAttribs3fvNV			=NULL;
PFNGLVERTEXATTRIBS3DVNVPROC					glVertexAttribs3dvNV			=NULL;
PFNGLVERTEXATTRIBS4SVNVPROC					glVertexAttribs4svNV			=NULL;
PFNGLVERTEXATTRIBS4FVNVPROC					glVertexAttribs4fvNV			=NULL;
PFNGLVERTEXATTRIBS4DVNVPROC					glVertexAttribs4dvNV			=NULL;
PFNGLVERTEXATTRIBS4UBVNVPROC				glVertexAttribs4ubvNV			=NULL;
