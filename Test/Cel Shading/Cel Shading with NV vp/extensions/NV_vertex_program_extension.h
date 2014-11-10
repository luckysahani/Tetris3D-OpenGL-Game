//////////////////////////////////////////////////////////////////////////////////////////
//	NV_vertex_program_extension.h
//	Extension setup header
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef NV_VERTEX_PROGRAM_EXTENSION_H
#define NV_VERTEX_PROGRAM_EXTENSION_H

bool SetUpNV_vertex_program();
extern bool NV_vertex_program_supported;

extern PFNGLBINDPROGRAMNVPROC						glBindProgramNV;
extern PFNGLDELETEPROGRAMSNVPROC					glDeleteProgramsNV;
extern PFNGLEXECUTEPROGRAMNVPROC					glExecuteProgramNV;
extern PFNGLGENPROGRAMSNVPROC						glGenProgramsNV;
	
extern PFNGLAREPROGRAMSRESIDENTNVPROC				glAreProgramsResidentNV;
extern PFNGLREQUESTRESIDENTPROGRAMSNVPROC			glRequestResidentProgramsNV;

extern PFNGLGETPROGRAMPARAMETERFVNVPROC				glGetProgramParameterfvNV;
extern PFNGLGETPROGRAMPARAMETERDVNVPROC				glGetProgramParameterdvNV;

extern PFNGLGETPROGRAMIVNVPROC						glGetProgramivNV;
extern PFNGLGETPROGRAMSTRINGNVPROC					glGetProgramStringNV;
extern PFNGLGETTRACKMATRIXIVNVPROC					glGetTrackMatrixivNV;

extern PFNGLGETVERTEXATTRIBDVNVPROC					glGetVertexAttribdvNV;
extern PFNGLGETVERTEXATTRIBFVNVPROC					glGetVertexAttribfvNV;
extern PFNGLGETVERTEXATTRIBIVNVPROC					glGetVertexAttribivNV;

extern PFNGLGETVERTEXATTRIBPOINTERVNVPROC			glGetVertexAttribPointervNV;

extern PFNGLISPROGRAMNVPROC							glIsProgramNV;

extern PFNGLLOADPROGRAMNVPROC						glLoadProgramNV;

extern PFNGLPROGRAMPARAMETER4FNVPROC				glProgramParameter4fNV;
extern PFNGLPROGRAMPARAMETER4DNVPROC				glProgramParameter4dNV;
	
extern PFNGLPROGRAMPARAMETER4FVNVPROC				glProgramParameter4fvNV;
extern PFNGLPROGRAMPARAMETER4DVNVPROC				glProgramParameter4dvNV;

extern PFNGLPROGRAMPARAMETERS4FVNVPROC				glProgramParameters4fvNV;
extern PFNGLPROGRAMPARAMETERS4DVNVPROC				glProgramParameters4dvNV;

extern PFNGLTRACKMATRIXNVPROC						glTrackMatrixNV;

extern PFNGLVERTEXATTRIBPOINTERNVPROC				glVertexAttribPointerNV;

extern PFNGLVERTEXATTRIB1SNVPROC					glVertexAttrib1sNV;
extern PFNGLVERTEXATTRIB1FNVPROC					glVertexAttrib1fNV;
extern PFNGLVERTEXATTRIB1DNVPROC					glVertexAttrib1dNV;
extern PFNGLVERTEXATTRIB2SNVPROC					glVertexAttrib2sNV;
extern PFNGLVERTEXATTRIB2FNVPROC					glVertexAttrib2fNV;
extern PFNGLVERTEXATTRIB2DNVPROC					glVertexAttrib2dNV;
extern PFNGLVERTEXATTRIB3SNVPROC					glVertexAttrib3sNV;
extern PFNGLVERTEXATTRIB3FNVPROC					glVertexAttrib3fNV;
extern PFNGLVERTEXATTRIB3DNVPROC					glVertexAttrib3dNV;
extern PFNGLVERTEXATTRIB4SNVPROC					glVertexAttrib4sNV;
extern PFNGLVERTEXATTRIB4FNVPROC					glVertexAttrib4fNV;
extern PFNGLVERTEXATTRIB4DNVPROC					glVertexAttrib4dNV;
extern PFNGLVERTEXATTRIB4UBNVPROC					glVertexAttrib4ubNV;

extern PFNGLVERTEXATTRIB1SVNVPROC					glVertexAttrib1svNV;
extern PFNGLVERTEXATTRIB1FVNVPROC					glVertexAttrib1fvNV;
extern PFNGLVERTEXATTRIB1DVNVPROC					glVertexAttrib1dvNV;
extern PFNGLVERTEXATTRIB2SVNVPROC					glVertexAttrib2svNV;
extern PFNGLVERTEXATTRIB2FVNVPROC					glVertexAttrib2fvNV;
extern PFNGLVERTEXATTRIB2DVNVPROC					glVertexAttrib2dvNV;
extern PFNGLVERTEXATTRIB3SVNVPROC					glVertexAttrib3svNV;
extern PFNGLVERTEXATTRIB3FVNVPROC					glVertexAttrib3fvNV;
extern PFNGLVERTEXATTRIB3DVNVPROC					glVertexAttrib3dvNV;
extern PFNGLVERTEXATTRIB4SVNVPROC					glVertexAttrib4svNV;
extern PFNGLVERTEXATTRIB4FVNVPROC					glVertexAttrib4fvNV;
extern PFNGLVERTEXATTRIB4DVNVPROC					glVertexAttrib4dvNV;
extern PFNGLVERTEXATTRIB4UBVNVPROC					glVertexAttrib4ubvNV;

extern PFNGLVERTEXATTRIBS1SVNVPROC					glVertexAttribs1svNV;
extern PFNGLVERTEXATTRIBS1FVNVPROC					glVertexAttribs1fvNV;
extern PFNGLVERTEXATTRIBS1DVNVPROC					glVertexAttribs1dvNV;
extern PFNGLVERTEXATTRIBS2SVNVPROC					glVertexAttribs2svNV;
extern PFNGLVERTEXATTRIBS2FVNVPROC					glVertexAttribs2fvNV;
extern PFNGLVERTEXATTRIBS2DVNVPROC					glVertexAttribs2dvNV;
extern PFNGLVERTEXATTRIBS3SVNVPROC					glVertexAttribs3svNV;
extern PFNGLVERTEXATTRIBS3FVNVPROC					glVertexAttribs3fvNV;
extern PFNGLVERTEXATTRIBS3DVNVPROC					glVertexAttribs3dvNV;
extern PFNGLVERTEXATTRIBS4SVNVPROC					glVertexAttribs4svNV;
extern PFNGLVERTEXATTRIBS4FVNVPROC					glVertexAttribs4fvNV;
extern PFNGLVERTEXATTRIBS4DVNVPROC					glVertexAttribs4dvNV;
extern PFNGLVERTEXATTRIBS4UBVNVPROC					glVertexAttribs4ubvNV;

#endif	//NV_VERTEX_PROGRAM_EXTENSION_H