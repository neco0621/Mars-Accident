#include "Bg.h"
#include "Game.h"

Bg::Bg() :
//‰Šú‰»
m_handle(-1),
m_pMain(nullptr)
{
}

Bg::~Bg()
{
	//ƒƒ‚ƒŠ‚ÌŠJ•ú
	DeleteGraph(m_handle);
}

void Bg::Draw()
{
	//”wŒi‚Ì•`‰æ
	DrawGraph(0,0 - 133,m_handle,false);
}
