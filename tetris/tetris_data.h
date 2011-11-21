/*
	����˹���� ������
	��������
*/
#ifndef __TETRIS_TETRIS_DATA_H_
#define __TETRIS_TETRIS_DATA_H_

#include<list>
#include<SDL.h>
#include"const.h"

// ����ÿһ�����������Ⱥ͸߶�
const int kBlockWidth = 4;
const int kBlockHeight = 4;
const int kMaxTransform = 4;

// ����һ����
struct TetrisPoint {
	TetrominoesType m_type;
};

// һ������Ľṹ
struct TetrisBlock {
	int m_point_used[kBlockHeight][kBlockWidth];		// ��Ľṹ
	TetrominoesType m_type;								// ��������
	int m_x;											// �����������Ϸ���е�����
	int m_y;
	int m_rotate;
	TetrisBlock* m_next_block;
};

typedef int TetrisTransform[kMaxTransform][kBlockHeight][kBlockWidth];

// ÿ�ַ������Ϳ��Ա任������
const int kTetrisTransformOptionCount[] = {0, 2, 4, 4, 1, 2, 2, 4};
const TetrisTransform kTetrisTransCollection[] = {
	// kNone
	{
		0
	},
	// kI,
	{
		{
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,0},
		}
	},
	// kJ,
	{
		{
			{0,0,0,0},
			{0,1,1,1},
			{0,0,0,1},
			{0,0,0,0}
		},
		{
			{0,0,1,1},
			{0,0,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,1,1},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,0,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
	},
	// kL,
	{
		{
			{0,0,0,0},
			{0,1,1,1},
			{0,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,0,1,0},
			{0,0,1,1},
			{0,0,0,0}
		},
		{
			{0,0,0,1},
			{0,1,1,1},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,1,1,0},
			{0,0,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
	},
	// kO,
	{
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
	},
	// kS,
	{
		{
			{0,0,0,0},
			{0,0,1,1},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,0,1,1},
			{0,0,0,1},
			{0,0,0,0}
		},
	},
	// kZ,
	{
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,0,1,1},
			{0,0,0,0}
		},
		{
			{0,0,0,1},
			{0,0,1,1},
			{0,0,1,0},
			{0,0,0,0}
		},
	},
	// kT,
	{
		{
			{0,0,0,0},
			{0,1,1,1},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,0,1,1},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,1,1,1},
			{0,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,1,0},
			{0,1,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
	},
};

enum TetrisAction {
	kActionNone = 0x0,
	kActionLeft = 0x1,
	kActionRight = 0x2,
	kActionDown = 0x3,
	kActionRotate = 0x4,
};

class TetrisData {
public:
	TetrisPoint* GetBoardGrid(int x, int y) { return &m_generate_data[y][x]; }
	TetrisData();
	~TetrisData();
	void ClearBoard();
	void Loop(Uint32 cur_tick, Uint32 down_speed, Uint32 repeat_speed);
	// ��ͣ
	void Pause() { m_running = false; }
	// �ָ�
	void Resume() { m_running = true; }
	
	// ��ӿ鵽��ǰ���� �����Ķ���˹����ֻ��һ�� �����ų�������ı䣬����������ʾ
	void AppendFreeBlock(TetrisBlock* free_block);
	// ɾ�����ɿ�
	TetrisBlock* RemoveFreeBlock(TetrisBlock* free_block);
	// �̶��鵽��Ϸ��
	void FastenFreeBlock(TetrisBlock* fasten_block);
	// ����Ƿ񳬳��߽�
	bool IsInBoard(int x, int y);
	void MarkMoveRight();
	void MarkMoveDown();
	void MarkMoveLeft();
	void MarkRotate();
	void ClearMoveRight();
	void ClearMoveLeft();
	void ClearMoveDown();
	void ClearRotate();
	bool IsBlockInBoard(TetrisBlock* block);
private:
	void FreeBlockMoveLeft();
	void FreeBlockMoveRight();
	void FreeBlockMoveDown();
	void RotateFreeBlock();

	bool DisposeCompleteLine(int start_y, int end_y);
	bool CollideDetectOne(TetrisBlock* block, bool no_check_bottom = false);
	void CopyTetrisBlockStruct(TetrisBlock* block);
	void MoveDown(int start_y, int end_y);
	void GenerateBoardData();
	int CollideDetect();
	bool RandNewBlock(int count = 1);
	void TestNewBlock();
	void TestInit();
	TetrisPoint m_board[kBoardGridHeight][kBoardGridWidth];
	TetrisPoint m_generate_data[kBoardGridHeight][kBoardGridWidth];
	bool m_running;
	bool m_new_block;
	// ���ɵķ����б���ͷ���ĵ���ѭ������
	TetrisBlock m_free_block_list;
	// ��һ���½���ʱ��
	Uint32 m_last_down_time;
	Uint32 m_last_repeat_time;
	TetrisAction m_action;
};

#endif