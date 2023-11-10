#include "Application.h"
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"
#include "Input.h"

#include <DxLib.h>
#include <assert.h>

namespace
{
	constexpr int screen_width = 640;
	constexpr int screen_height = 480;
}

int MyLoadGraph(const wchar_t* path) {
	int handle = LoadGraph(path);
	assert(handle != -1);
	return handle;
}


void Application::Terminate()
{
	DxLib_End();
}

bool Application::Init()
{
	windowSize_ = { screen_width,screen_height };

	ChangeWindowMode(true);	//非スクリーン
	SetGraphMode(windowSize_.w, windowSize_.h, 32);
	//ウィンドウ名を変更
	SetWindowText(L"Mars Accident");
	if (DxLib_Init() == -1) {	//初期化に失敗したらアプリを落とす
		return false;	//異常終了
	}
	SetDrawScreen(DX_SCREEN_BACK);
	return true;
}

void Application::Run()
{
	SceneManager manager;
	manager.ChangeScene(std::make_shared<TitleScene>(manager));

	Input input;

	while (ProcessMessage() != -1) {
		LONGLONG time = GetNowHiPerformanceCount();

		ClearDrawScreen();

		input.Update();
		manager.Update(input);
		manager.Draw();

		ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		while (16667 > GetNowHiPerformanceCount() - time);
	}

	Terminate();
}

const Size& Application::GetWindowSize() const
{
	return windowSize_;
}
