#ifndef __TETRIS_CONST_H_
#define __TETRIS_CONST_H_

const int kFPS = 120;
const int kTickPerSecond = 1000 / kFPS;
const int kInitDownSpeed = 1000;

const int kBoardGridWidth = 10;		// һ��board�ĸ��ӿ��
const int kBoardGridHeight = 20;	// һ��board�ĸ��Ӹ߶�


const int kPWidthPerBlock = 4;		// ÿ���������ռ������
const int kPHeightPerBlock = 4;		
// ���ڸ߶�
const int kWinWidth = 600;
const int kWinHeight = 700;
const int kWinBPP = 32;
const char kWinTitle[] = "Tetris By ShaneYao";

const int kGridWidth = 30;			// ������ʾ�Ŀ��
const int kGridHeight = 30;			// ������ʾ�ĸ߶�

const int kLineWidth = 1;			// ������ʾ�ı߿���

const unsigned int kLinecolor = 0x000000FF; // �ߵ���ɫ
const unsigned int kGridLinecolor = 0x000000FF;	//�����ߵ���ɫ

const int kBoardWidth = (kGridWidth + kLineWidth) *  kBoardGridWidth + kLineWidth;	// board �����ؿ��
const int kBoardHeight = (kGridHeight + kLineWidth) * kBoardGridHeight + kLineWidth;	// board �����ظ߶�

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


// ��������
// �������� �ο�ά���ٿ�:
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