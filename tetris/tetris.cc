#include "tetris.h"

TetrisApp::TetrisApp() : m_render(NULL), m_data(NULL), m_base_down_speed(kInitDownSpeed), 
						 m_factor_down_speed(1.0), m_down_speed(m_base_down_speed * m_factor_down_speed)
{

}

TetrisApp::~TetrisApp()
{
}

int TetrisApp::OnKeyPress()
{
	return 1;
}

// 转换SDL事件到TetrisEvent
void TetrisApp::TranslateEventSDL(SDL_Event* sdl_event, TetrisEvent* tetris_event)
{
	tetris_event->m_type = kTetrisEventNone;
	if (sdl_event->type == SDL_QUIT) {
		tetris_event->m_type = kTetrisEventQuit;
	}
	else if (sdl_event->type == SDL_KEYDOWN) {
		// TODO 这里写死了每个键对应的操作
		TransKeyDownToEvent(sdl_event->key.keysym.sym, tetris_event);
	}
	else if (sdl_event->type == SDL_KEYUP) {
		TransKeyUpToEvent(sdl_event->key.keysym.sym, tetris_event);
	}
}

void TetrisApp::TransKeyDownToEvent(int key_code, TetrisEvent* tetris_event)
{
	if (key_code == SDLK_UP) {
		tetris_event->m_type = kTetrisEventStartRotate;
	}
	else if (key_code == SDLK_LEFT) {
		tetris_event->m_type = kTetrisEventStartMoveLeft;
	}
	else if (key_code == SDLK_RIGHT) {
		tetris_event->m_type = kTetrisEventStartMoveRight;
	}
	else if (key_code == SDLK_DOWN) {
		tetris_event->m_type = kTetrisEventStartDownAccelerate;
	}
}

void TetrisApp::TransKeyUpToEvent(int key_code, TetrisEvent* tetris_event)
{
	if (key_code == SDLK_UP) {
		tetris_event->m_type = kTetrisEventStopRotate;
	}
	else if (key_code == SDLK_LEFT) {
		tetris_event->m_type = kTetrisEventStopMoveLeft;
	}
	else if (key_code == SDLK_RIGHT) {
		tetris_event->m_type = kTetrisEventStopMoveRight;
	}
	else if (key_code == SDLK_DOWN) {
		tetris_event->m_type = kTetrisEventStopDownAccelerate;
	}
}

// 事件处理
void TetrisApp::OnEvent(TetrisEvent* tetris_event)
{
	switch (tetris_event->m_type)
	{
		case kTetrisEventQuit:
			m_running = false;
			break;
		case kTetrisEventStartRotate:
			m_data->MarkRotate();
			break;
		case kTetrisEventStopRotate:
			m_data->ClearRotate();
			break;
		case kTetrisEventStartMoveLeft:
			m_data->MarkMoveLeft();
			break;
		case kTetrisEventStopMoveLeft:
			m_data->ClearMoveLeft();
			break;
		case kTetrisEventStartMoveRight:
			m_data->MarkMoveRight();
			break;
		case kTetrisEventStopMoveRight:
			m_data->ClearMoveRight();
			break;
		case kTetrisEventStartDownAccelerate:
			m_data->MarkMoveDown();
			break;
		case kTetrisEventStopDownAccelerate:
			m_data->ClearMoveDown();
			break;
		default:
			break;
	}
}

void TetrisApp::SetDownSpeedFactor(double factor)
{
	m_factor_down_speed = factor;
	m_down_speed = m_base_down_speed * m_factor_down_speed;
}
// 初始化
void TetrisApp::Init(TetrisRender* render, TetrisData* data)
{
	m_render = render;
	m_render->Init();

	m_data = data;
}

void TetrisApp::Destory()
{
	m_render->Destory();
}

int TetrisApp::Execute()
{
	SDL_Event sdl_event;
	TetrisEvent tetris_event;
	Uint32 start_tick = 0;
	Uint32 end_tick = 0;
	Uint32 sleep_time = 0;
	while (m_running) {
		start_tick = SDL_GetTicks();
		// 1. Get SDL Event
		while (SDL_PollEvent(&sdl_event)) {
			TranslateEventSDL(&sdl_event, &tetris_event);
			OnEvent(&tetris_event);
		}
		// 2. Looping
		m_data->Loop(start_tick, m_down_speed, kKeyboardRepeatTime);
		// 3. Rendering
		m_render->Render(m_data, start_tick);
		end_tick = SDL_GetTicks();
		Uint32 timespan = end_tick - start_tick;
		if (timespan < kTickPerSecond) {
			sleep_time = kTickPerSecond - timespan;
			SDL_Delay(sleep_time);
		}
	}
	return 1;
}

int TetrisApp::Loop()
{
	return 1;
}
