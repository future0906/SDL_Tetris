#include"tetris_data.h"
#include<time.h>
#include<random>
#include"debug.h"

TetrisData::TetrisData() : m_running(true), m_new_block(1), m_last_down_time(0), m_last_repeat_time(0), 
						   m_action(kActionNone)
{
	srand(time(NULL));
	ClearBoard();
	m_free_block_list.m_next_block = &m_free_block_list;
}

void TetrisData::ClearBoard()
{
	for (int y = 0; y < kBoardGridHeight; y++) {
		for (int x = 0; x < kBoardGridWidth; x++) {
			m_board[y][x].m_type = kTNone;
			m_generate_data[y][x].m_type = kTNone;
		}
	}
}
void TetrisData::TestNewBlock()
{
	for (int i = 0; i < 1; i++) {
		RandNewBlock(1);
	}
}
TetrisData::~TetrisData()
{
}

void TetrisData::TestInit()
{
	for (int y = 0; y < kBoardGridHeight; y++) {
		for (int x = 0; x < kBoardGridWidth; x++) {
			m_board[0][x].m_type = (TetrominoesType)(rand() % (int)(kTetrominoesMax));
		}
	}
}

// Data����ѭ��
void TetrisData::Loop(Uint32 cur_tick, Uint32 down_speed, Uint32 repeat_speed)
{
	if (!m_running) {
		return;
	}

	if (m_new_block > 0) {
		bool new_block_success = RandNewBlock(m_new_block);
		if (!new_block_success) {
			abort();
		}
		m_new_block = 0;
	}
	
	// ��ʱ�½�
	if (cur_tick - m_last_down_time >= down_speed &&
		m_action != kActionDown) {
		FreeBlockMoveDown();
		m_last_down_time = cur_tick;
	}
	
	// �����ظ�
	if (cur_tick - m_last_repeat_time >= repeat_speed) {
		switch (m_action)
		{
			case kActionLeft:
				FreeBlockMoveLeft();
				break;
			case kActionRight:
				FreeBlockMoveRight();
				break;
			case kActionDown:
				FreeBlockMoveDown();
				break;
			case kActionRotate:
				RotateFreeBlock();
				break;
			case kActionNone:
			default:
				break;
		}
		m_last_repeat_time = cur_tick;
	}

	GenerateBoardData();
	// TODO 1.����Ƿ����п�������
	//			a.����У�����֮���������³�
}

// �����Ƿ񳬳��߽�
// ע�⣬��������ЩTricky, ��Ҫ����
bool TetrisData::IsBlockInBoard(TetrisBlock* block)
{
	// �������������Ϸ����
	if (block->m_x >= 0 && ((block->m_x + kBlockWidth - 1) < kBoardGridWidth) &&
		block->m_y >= 0 && ((block->m_y + kBlockHeight - 1) < kBoardGridHeight)) {
		return true;
	}

	// ���ļ�鷽��
	int point_x = 0;
	int point_y = 0;
	for (int y = 0; y < kBlockHeight; y++) {
		for (int x = 0; x < kBlockWidth; x++) {
			if (kTetrisTransCollection[block->m_type][block->m_rotate][y][x] == 1) {
				point_x = block->m_x + x;
				point_y = block->m_y + y;
				if (point_x < 0 || point_x >= kBoardGridWidth ||
					point_y < 0 || point_y >= kBoardGridHeight) {
					// �����߽�
					return false;
				}
			}
		}
	}
	return true;
}

void TetrisData::FreeBlockMoveRight()
{
	// TODO �����Ƿ񳬳��߽�
	TetrisBlock* cur_block = NULL;
	cur_block = m_free_block_list.m_next_block;
	while (cur_block != &m_free_block_list) {
		(cur_block->m_x)++;
		if (!IsBlockInBoard(cur_block) || CollideDetectOne(cur_block, true)) {
			(cur_block->m_x)--;
		}

		cur_block = cur_block->m_next_block;
	}
}

// ��ת���ɿ�
void TetrisData::RotateFreeBlock()
{
	// TODO �����Ƿ񳬳��߽�
	TetrisBlock* cur_block = NULL;
	cur_block = m_free_block_list.m_next_block;
	int before_rotate = 0;
	while (cur_block != &m_free_block_list) {
		// ���浱ǰ����ת״̬
		before_rotate = cur_block->m_rotate;
		cur_block->m_rotate = (cur_block->m_rotate + 1) % kTetrisTransformOptionCount[cur_block->m_type];
		CopyTetrisBlockStruct(cur_block);
		// �����ת���block�Ƿ��г�������
		if (!IsBlockInBoard(cur_block) || CollideDetectOne(cur_block, true)) {
			cur_block->m_rotate = before_rotate;
			CopyTetrisBlockStruct(cur_block);
		}
		cur_block = cur_block->m_next_block;
	}
}

void TetrisData::FreeBlockMoveLeft()
{
	// TODO �����Ƿ񳬳��߽�
	TetrisBlock* cur_block = NULL;
	cur_block = m_free_block_list.m_next_block;
	while (cur_block != &m_free_block_list) {
		
		(cur_block->m_x)--;
		if (!IsBlockInBoard(cur_block) || CollideDetectOne(cur_block, true)) {
			(cur_block->m_x)++;
		}

		cur_block = cur_block->m_next_block;
	}
}

void TetrisData::MarkMoveDown()
{
	m_action = kActionDown;
}
void TetrisData::MarkMoveLeft()
{
	m_action = kActionLeft;
}

void TetrisData::MarkMoveRight()
{
	m_action = kActionRight;
}

void TetrisData::MarkRotate()
{
	m_action = kActionRotate;
}

void TetrisData::ClearMoveRight()
{
	if (m_action == kActionRight) {
		m_action = kActionNone;
	}
}
void TetrisData::ClearMoveLeft()
{
	if (m_action == kActionLeft) {
		m_action = kActionNone;
	}
}

void TetrisData::ClearMoveDown()
{
	if (m_action == kActionDown) {
		m_action = kActionNone;
	}
}

void TetrisData::ClearRotate()
{
	if (m_action == kActionRotate) {
		m_action = kActionNone;
	}
}
void TetrisData::FreeBlockMoveDown()
{
	// ����Ƿ�����ײ
	int collide_block_count = CollideDetect();
	// ���ص���ײ���ɿ����1��
	if (collide_block_count != 0) {
		m_new_block += collide_block_count;
	}

	// TODO �����Ƿ񳬳��߽�
	TetrisBlock* cur_block = NULL;
	cur_block = m_free_block_list.m_next_block;
	while (cur_block != &m_free_block_list) {
		
		(cur_block->m_y)++;
		if (!IsBlockInBoard(cur_block)) {
			(cur_block->m_y)--;
		}

		cur_block = cur_block->m_next_block;
	}

}
void TetrisData::CopyTetrisBlockStruct(TetrisBlock* block)
{
	for (int y = 0; y < kBlockHeight; y++) {
		for (int x = 0; x < kBlockWidth; x++) {
			block->m_point_used[y][x] = kTetrisTransCollection[block->m_type][block->m_rotate][y][x];
		}
	}
}

bool TetrisData::DisposeCompleteLine(int start_y, int end_y)
{
	TETRIS_ASSERT(start_y > end_y, "����,start_y ��end_y��");
	int is_line_complete = false;
	for (int y = start_y; y <= end_y; y++) {
		is_line_complete = true;
		for (int x = 0; x < kBoardGridWidth; x++) {
			if (m_board[y][x].m_type == kTNone) {
				is_line_complete = false;
				break;
			}
		}
		// �����Ѿ���ɣ���������
		if (is_line_complete) {
			MoveDown(0, y);
			is_line_complete = false;
		}
	}
	return true;
}

void TetrisData::MoveDown(int start_y, int end_y)
{
	for (int y = end_y - 1; y >= start_y; y --) {
		for (int x = 0; x < kBoardGridWidth; x++) {
			m_board[y + 1][x].m_type = m_board[y][x].m_type;
			m_board[y][x].m_type = kTNone;
		}
	}
}

// �����ɿ�̶�����Ϸ����
void TetrisData::FastenFreeBlock(TetrisBlock* fasten_block)
{
	// ÿ��������Ϸ�̵�ʵ������
	int real_x, real_y = 0;
	for (int y = 0; y < kBlockHeight; y++) {
		for (int x = 0; x < kBlockWidth; x++) {
			real_x = fasten_block->m_x + x;
			real_y = fasten_block->m_y + y;
			if (!IsInBoard(real_x, real_y) ||
				(fasten_block->m_point_used[y][x] == 0)) {
				continue;
			}
			m_board[real_y][real_x].m_type = fasten_block->m_type;
		}
	}
	DisposeCompleteLine(fasten_block->m_y, fasten_block->m_y + kBlockHeight);
}
bool TetrisData::RandNewBlock(int count)
{
	for (int i = 0; i < count; i++) {
		// ��(kTNone, kTetrominoesMax)���������
		TetrominoesType type = static_cast<TetrominoesType>((rand() % (kTetrominoesMax - (kTNone + 1))) + (kTNone + 1));
		TETRIS_ASSERT(type <= kTNone || type >= kTetrominoesMax, "������Χ");
		// �����µĿ�
		TetrisBlock* block = new TetrisBlock();
		block->m_type = type;
		block->m_x = 3;
		block->m_y = 0;
		block->m_rotate = 0;
		CopyTetrisBlockStruct(block);
		// �����ײ
		if (CollideDetectOne(block, true)) {
			delete block;
			return false;
		}
		AppendFreeBlock(block);
	}
	return true;
}

// ��ײ���
// ������ɿ�
int TetrisData::CollideDetect()
{
	int collide_block_count = 0;
	TetrisBlock* cur_block = NULL;
	TetrisBlock* to_delete_block = NULL;
	cur_block = m_free_block_list.m_next_block;

	while (cur_block != &m_free_block_list) {
		if (CollideDetectOne(cur_block)) {
			FastenFreeBlock(cur_block);
			to_delete_block = cur_block;
			cur_block = RemoveFreeBlock(cur_block);
			TETRIS_ASSERT(cur_block == NULL, "����ɾ�����ɿ�ʧ��");
			delete to_delete_block;
			collide_block_count++;
		}
		else {
			cur_block = cur_block->m_next_block;
		}
	}
	return collide_block_count;
}

// ����
bool TetrisData::CollideDetectOne(TetrisBlock* block, bool no_check_bottom)
{
	int real_x, real_y = 0;
	// ��ǰ���y������
	int forward_check_y = 1;
	if (no_check_bottom == true) {
		forward_check_y = 0;
	}

	for (int y = kBlockHeight - 1; y >= 0; y--) {
		for (int x = 0; x < kBlockWidth; x++) {
			real_x = block->m_x + x;
			real_y = block->m_y + y;
			// �ж��Ƿ�����Ϸ����
			if (block->m_point_used[y][x] == 0 ||
				!IsInBoard(real_x, real_y)) {
				continue;
			}
			TETRIS_ASSERT(real_y >= kBoardGridHeight, "��ĵײ����곬����Ϸ�̱߽�");
			if (real_y == (kBoardGridHeight - forward_check_y) ||
				(m_board[real_y + forward_check_y][real_x].m_type != kTNone)) {
				return true;
			}
		}
	}
	return false;
}

// ��ӿ鵽��������ֱ�Ӳ���ͷ���ĺ���
void TetrisData::AppendFreeBlock(TetrisBlock* free_block)
{
	free_block->m_next_block = m_free_block_list.m_next_block;
	m_free_block_list.m_next_block = free_block;
}

// ���б���ɾ�����ɿ�
TetrisBlock* TetrisData::RemoveFreeBlock(TetrisBlock* free_block)
{
	TetrisBlock* prv_block_ptr = &m_free_block_list;
	TetrisBlock* cur_block_ptr = prv_block_ptr->m_next_block;
	while (cur_block_ptr != &m_free_block_list) {
		if (cur_block_ptr == free_block) {
			// ���б���ɾ����
			prv_block_ptr->m_next_block = cur_block_ptr->m_next_block;
			return prv_block_ptr->m_next_block;
		}
		prv_block_ptr = cur_block_ptr;
		cur_block_ptr = cur_block_ptr->m_next_block;
	}
	return NULL;
}

// �������е���Ϸ�����ݺ����ɿ��б�������Ⱦ����
void TetrisData::GenerateBoardData()
{
	// 1.����m_board
	for (int y = 0; y < kBoardGridHeight; y++) {
		for (int x = 0; x < kBoardGridWidth; x++) {
			m_generate_data[y][x] = m_board[y][x];
		}
	}
	// 2.�������ɿ����Ϸ��
	TetrisBlock* cur_block = NULL;
	cur_block = m_free_block_list.m_next_block;
	while (cur_block != &m_free_block_list) {
		for (int y = 0; y < kBlockHeight; y++) {
			for (int x = 0; x < kBlockWidth; x++) {
				if (cur_block->m_point_used[y][x] == 1) {
					m_generate_data[cur_block->m_y + y][cur_block->m_x + x].m_type = cur_block->m_type;
				}
			}
		}
		cur_block = cur_block->m_next_block;
	}
}
bool TetrisData::IsInBoard(int x, int y)
{
	if (x < 0 || x > kBoardGridWidth ||
		y < 0 || y > kBoardGridHeight) {
		return false;
	}
	return true;
}