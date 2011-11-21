#include"tetris_render.h"
#include"tetris_data.h"
#include<assert.h>

TetrisRender::TetrisRender() : m_display(NULL), m_board(NULL)
{

}

TetrisRender::~TetrisRender()
{
}

void TetrisRender::Destory()
{
	SDL_Quit();
}

void TetrisRender::Init()
{
	int rtn = 0;
	rtn = SDL_Init(SDL_INIT_EVERYTHING);
	assert(rtn >= 0);
	m_display = SDL_SetVideoMode(kWinWidth, kWinHeight, kWinBPP, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWACCEL);
	assert(m_display != NULL);

	SDL_WM_SetCaption(kWinTitle, NULL);

	// 初始化背景板
	DrawBoard();

	// 初始化方块层
	InitGridLayer();

}

void TetrisRender::Render(TetrisData* data, Uint32 cur_tick)
{
	// 背景色
	SDL_FillRect(m_display, NULL, 0x00E0DFE3);

	// 复制游戏板到背景
	SDL_Rect board_rect;
	board_rect.y =  20;
	board_rect.x = 20;
	SDL_BlitSurface(m_board, NULL, m_display, &board_rect);
	// 绘画方块
	DrawGridData(data);
	SDL_BlitSurface(m_grid_layer, NULL, m_display, &board_rect);
	// 交换缓冲区
	SDL_Flip(m_display);
}
void TetrisRender::DrawGridData(TetrisData* data)
{
	SDL_FillRect(m_grid_layer, NULL, 0x00000000);
	for (int y = 0; y < kBoardGridHeight; y++) {
		for (int x = 0; x < kBoardGridWidth; x++) {
			DrawGridPos(x, y, data->GetBoardGrid(x, y)->m_type);
		}
	}
}
void TetrisRender::DrawBoard()
{
	m_board = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWACCEL, kBoardWidth, kBoardHeight, kWinBPP, kRmask, kGmask, kBmask, kAmask);
	rectangleColor(m_board, 0, 0, kBoardWidth - 1, kBoardHeight - 1, kLinecolor);

	// 画水平线
	for (int i = 0; i < kBoardGridHeight; i++) {
		hlineColor(m_board, 0, kBoardWidth, (i + 1) * (kGridHeight + kLineWidth), kLinecolor);
	}

	// 画垂线
	for (int i = 0; i < kBoardGridWidth; i++) {
		vlineColor(m_board, (i + 1) * (kGridWidth + kLineWidth), 0, kBoardHeight, kLinecolor);
	}
}

void TetrisRender::InitGridLayer()
{
	m_grid_layer = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_HWACCEL, kBoardWidth, kBoardHeight, kWinBPP, kRmask, kGmask, kBmask, kAmask);
}

// 绘画方块
void TetrisRender::DrawGridPos(int grid_x, int grid_y, TetrominoesType type)
{
	if (type == kTNone) {
		return;
	}
	int pos_x = grid_x * (kLineWidth + kGridWidth);
	int pos_y = grid_y * (kLineWidth + kGridHeight);
	int width = kGridWidth + kLineWidth;
	int height = kGridHeight + kLineWidth;

	rectangleColor(m_grid_layer, pos_x, pos_y, pos_x + width, pos_y + height, kGridLinecolor);
	SDL_Rect grid_rect;
	// 填充矩形颜色
	grid_rect.x = pos_x + kLineWidth;
	grid_rect.y = pos_y + kLineWidth;
	grid_rect.w = width - kLineWidth;
	grid_rect.h = height - kLineWidth;
	int color = kTetrominoesColor[type];
	SDL_FillRect(m_grid_layer, &grid_rect, color);
}