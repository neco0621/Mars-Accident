#include "Bg.h"
#include "Game.h"

Bg::Bg() :
//������
m_handle(-1),
m_pMain(nullptr)
{
}

Bg::~Bg()
{
	//�������̊J��
	DeleteGraph(m_handle);
}

void Bg::Draw()
{
	//�w�i�̕`��
	DrawGraph(0,0 - 133,m_handle,false);
}
