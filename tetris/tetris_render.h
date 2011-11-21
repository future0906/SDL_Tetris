#ifndef __TETRIS_TETRIS_RENDER_H_
#define __TETRIS_TETRIS_RENDER_H_

#include<SDL.h>
#include<SDL_gfxPrimitives.h>
#include "const.h"

const unsigned int kTetrominoesColor[] = {
	0xff000000,	//kNone
	0xffff0000,	//kI
	0xfff900f9,	//kJ
	0xffffff00,	//kL
	0xff00ffff,	//kO
	0xff0000ff,	//kS
	0xff00ff00,	//kZ
	0xffc0c0c0,	//kT
	0xffffffff, //kMax
};

/* Forward declaration */
class TetrisData;


class TetrisRender {
public:
	TetrisRender();
	~TetrisRender();
	void DrawGridPos(int x, int y, TetrominoesType type);
	void InitGridLayer();
	void Render(TetrisData* data, Uint32 cur_tick);
	void DrawBoard();
	void DrawGridData(TetrisData*);
	void Init();
	void Destory();
private:
	SDL_Surface* m_display;
	SDL_Surface* m_grid_layer;
	SDL_Surface* m_board;
};
#endif//__TETRIS_TETRIS_RENDER_H_