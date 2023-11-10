#include "KeyConfigScene.h"
#include "DxLib.h"
#include "../Input.h"
#include "../Application.h"
#include "SceneManager.h"
#include "../StringUtility.h"

constexpr int apper_interval = 30;
constexpr int menu_margin = 60;

void KeyConfigScene::AppearUpdate(Input&)
{
	++frame_;
	if (frame_ == apper_interval)
	{
		updateFunc_ = &KeyConfigScene::NormalUpdate;
		drawFunc_ = &KeyConfigScene::NormalDraw;
	}
}

void KeyConfigScene::NormalUpdate(Input& input)
{
	if (input.IsTriggered("keyconf"))
	{
		updateFunc_ = &KeyConfigScene::DisappearUpdate;
		drawFunc_ = &KeyConfigScene::ExpandDraw;

	}
}

void KeyConfigScene::DisappearUpdate(Input&)
{
	--frame_;
	if (frame_ == 0)
	{
		manager_.popScene();

	}
}

void KeyConfigScene::ExpandDraw()
{
	Application& app = Application::GetInstance();
	const auto& size = app.GetWindowSize();

	int halfHeight = (size.h - 120) / 2;
	int centerY = size.h / 2;

	float rate = static_cast<float>(frame_) / static_cast<float> (apper_interval);	//Œ»Ý‚ÌŽžŠÔ‚ÌŠ„‡(0.0 ` 1.0)

	int currntHalfHeight = rate * halfHeight;

	//”–‚¢ŽlŠp‚ð•\Ž¦
	DrawBox(menu_margin, centerY - currntHalfHeight, size.w - menu_margin, centerY + currntHalfHeight, 0x444444, true);

	//”’ˆä˜gü‚ð•\Ž¦
	DrawBox(menu_margin, centerY - currntHalfHeight, size.w - menu_margin, centerY + currntHalfHeight, 0xffffff, false);

}

void KeyConfigScene::NormalDraw()
{
	Application& app = Application::GetInstance();
	const auto& size = app.GetWindowSize();


	DrawBox(menu_margin, menu_margin, size.w - menu_margin, size.h - menu_margin, 0x4444444, true);

	DrawString(100, menu_margin + 10, L"KeyConfigScene", 0xffffff);
	DrawBox(menu_margin, menu_margin, size.w - menu_margin, size.h - menu_margin, 0xffffff, false);

	DrawCommandList();
}

void KeyConfigScene::DrawCommandList()
{
	const auto& cmdTable = input_.GetCommandTable();

	int x = menu_margin + 50;
	int y = menu_margin + 50 + 10;

	for (const auto& cmd : keyCommandTable_)
	{
		std::wstring cmdName = StringUtility::StringToWString(cmd.first);
		DrawFormatString(x, y, 0xffffff, L"%s", cmdName.c_str());	//•¶Žš‰»‚¯‚µ‚Ä‚¢‚é
		y += 20;
	}
}

KeyConfigScene::KeyConfigScene(SceneManager& manager, Input& input) :
	Scene(manager),
	input_(input)
{
	keyCommandTable_ = input.GetCommandTable();
	updateFunc_ = &KeyConfigScene::AppearUpdate;
	drawFunc_ = &KeyConfigScene::ExpandDraw;
}

KeyConfigScene::~KeyConfigScene()
{
}

void KeyConfigScene::Update(Input& input)
{
	(this->*updateFunc_)(input);
}

void KeyConfigScene::Draw()
{

	(this->*drawFunc_)();

}

