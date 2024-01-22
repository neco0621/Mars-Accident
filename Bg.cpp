#include "Bg.h"
#include "Game.h"

Bg::Bg() :
m_handle(-1)
{
}

Bg::~Bg()
{
}

void Bg::Init()
{
}

void Bg::Update()
{
}

void Bg::Draw()
{
	DrawGraph(0,0,m_handle,false);
}
