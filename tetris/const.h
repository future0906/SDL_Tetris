#ifndef __TETRIS_CONST_H_
#define __TETRIS_CONST_H_

const int kFPS = 120;
const int kTickPerSecond = 1000 / kFPS;
const int kInitDownSpeed = 1000;

const int kBoardGridWidth = 10;		// 一个board的格子宽度
const int kBoardGridHeight = 20;	// 一个board的格子高度


const int kPWidthPerBlock = 4;		// 每个方块最多占几个格
const int kPHeightPerBlock = 4;		
// 窗口高度
const int kWinWidth = 600;
const int kWinHeight = 700;
const int kWinBPP = 32;
const char kWinTitle[] = "Tetris By ShaneYao";

const int kGridWidth = 30;			// 格子显示的宽度
const int kGridHeight = 30;			// 格子显示的高度

const int kLineWidth = 1;			// 格子显示的边框宽度

const unsigned int kLinecolor = 0x000000FF; // 线的颜色
const unsigned int kGridLinecolor = 0x000000FF;	//格子线的颜色

const int kBoardWidth = (kGridWidth + kLineWidth) *  kBoardGridWidth + kLineWidth;	// board 的像素宽度
const int kBoardHeight = (kGridHeight + kLineWidth) * kBoardGridHeight + kLineWidth;	// board 的像素高度

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
const int kRmask = 0xff000000;
const int kGmask = 0x00ff0000;
const int kBmask = 0x0000ff00;
const int kAmask = 0x000000ff;
#else
const int kRmask = 0x000000ff;
const int kGmask = 0x0000ff00;
const int kBmask = 0x00ff0000;
const int kAmask = 0xff000000;
#endif


// 方块类型
// 命名规则 参考维基百科:
// http://en.wikipedia.org/wiki/Tetromino
enum TetrominoesType {
	kTNone = 0x0,
	kI,
	kJ,
	kL,
	kO,
	kS,
	kZ,
	kT,
	kTetrominoesMax,
};

enum EventType {
	kTetrisEventNone = 0x00000,
	kTetrisEventQuit = 0x00001,
	kTetrisEventStartRotate = 0x00002,
	kTetrisEventStopRotate = 0x00003,
	kTetrisEventStartMoveLeft = 0x00004,
	kTetrisEventStopMoveLeft = 0x00005,
	kTetrisEventStartMoveRight = 0x00006,
	kTetrisEventStopMoveRight = 0x00007,
	kTetrisEventStartDownAccelerate = 0x00008,
	kTetrisEventStopDownAccelerate = 0x0009,
};

enum MoveDir {
	kMoveUP = 0x0001,
	kMoveLeft = 0x0002,
	kMoveDown = 0x0003,
	kMoveRight = 0x0004,
};
#endif//__TETRIS_CONST_H_