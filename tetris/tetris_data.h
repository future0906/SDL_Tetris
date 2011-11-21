/*
	俄罗斯方块 数据类
	包含棋盘
*/
#ifndef __TETRIS_TETRIS_DATA_H_
#define __TETRIS_TETRIS_DATA_H_

#include<list>
#include<SDL.h>
#include"const.h"

// 定义每一个方块的最大宽度和高度
const int kBlockWidth = 4;
const int kBlockHeight = 4;
const int kMaxTransform = 4;

// 方块一个点
struct TetrisPoint {
	TetrominoesType m_type;
};

// 一个方块的结构
struct TetrisBlock {
	int m_point_used[kBlockHeight][kBlockWidth];		// 块的结构
	TetrominoesType m_type;								// 方块类型
	int m_x;											// 块的中心在游戏盘中的坐标
	int m_y;
	int m_rotate;
	TetrisBlock* m_next_block;
};

typedef int TetrisTransform[kMaxTransform][kBlockHeight][kBlockWidth];

// 每种方块类型可以变换的类型
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
	// 暂停
	void Pause() { m_running = false; }
	// 恢复
	void Resume() { m_running = true; }
	
	// 添加块到当前链表 正常的俄罗斯方块只有一个 但不排除有特殊改变，因此用链表表示
	void AppendFreeBlock(TetrisBlock* free_block);
	// 删除自由块
	TetrisBlock* RemoveFreeBlock(TetrisBlock* free_block);
	// 固定块到游戏盘
	void FastenFreeBlock(TetrisBlock* fasten_block);
	// 检查是否超出边界
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
	// 自由的方块列表，带头结点的单向循环链表
	TetrisBlock m_free_block_list;
	// 上一次下降的时间
	Uint32 m_last_down_time;
	Uint32 m_last_repeat_time;
	TetrisAction m_action;
};

#endif