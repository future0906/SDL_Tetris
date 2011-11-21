#ifndef __TETRIS_H_
#define __TETRIS_TETRIS_H_
#include<SDL.h>
#include"tetris_data.h"
#include"tetris_render.h"

struct TetrisEvent {
	int m_type;
	int m_param1;
	int m_param2;
};
const double kDownAccelerateFactor = 0.05;
const double kKeyboardRepeatTime = 70;
class TetrisApp {
public:
	int Execute();	// Ö´ÐÐ³ÌÐò
	int Loop();		// Ñ­»·
	void Stop() { m_running = false; }
	int OnKeyPress();
	void OnEvent(TetrisEvent* tetris_event);
	void TranslateEventSDL(SDL_Event* sdl_event, TetrisEvent* tetris_event);
	void Init(TetrisRender* render, TetrisData* data);
	void Destory();
	TetrisApp();
	~TetrisApp();
private:
	void SetDownSpeedFactor(double factor);
	void TransKeyDownToEvent(int key_code, TetrisEvent* tetris_event);
	void TransKeyUpToEvent(int key_code, TetrisEvent* tetris_event);
private:
	bool m_running;
	TetrisRender* m_render;
	TetrisData* m_data;
	Uint32 m_base_down_speed;
	double m_factor_down_speed;
	Uint32 m_down_speed;
};

#endif