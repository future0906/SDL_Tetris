#include<iostream>
#include<sdl.h>
#include"tetris.h"
#include"tetris_render.h"
#include"tetris_data.h"

int SDL_main(int argc, char* argv[])
{
	TetrisApp theApp;
	TetrisRender theRender;
	TetrisData theData;

	theApp.Init(&theRender, &theData);

	theApp.Execute();
	
	theApp.Destory();
	return 1;
}