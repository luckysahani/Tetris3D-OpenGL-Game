//////////////////////////////////////////////////////////////////////////////////////////
//	Main.h
//	Cel Shading
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef MAIN_H
#define MAIN_H

bool DemoInit();
bool GLInit();

void UpdateFrame();
void RenderFrame();

void DemoShutdown();

int WINAPI WinMain(HINSTANCE	hInstance,
				   HINSTANCE	hPervInstance,
				   LPSTR		lpCmdLine,
				   int			nCmdShow);					//main entry point

#endif	//MAIN_H