#pragma once
#include "Scene.h"
class GameOverScene : public Scene
{
public:
    GameOverScene(SceneManager& mgr);
    ~GameOverScene();
    virtual void Init();
    virtual void Update(Input& input);
    virtual void Draw();

private:
    int frame_;
    int m_gameOver;
    int m_titleBack;
    int m_bg;
    int m_bgm;
    int m_retry;
    // メンバ関数ポインタの宣言
    using UpdateFunc_t = void (GameOverScene::*)(Input&);
    using DrawFunc_t = void (GameOverScene::*)();
    UpdateFunc_t m_updateFunc;
    DrawFunc_t m_drawFunc;

    // 更新状態を表す関数
    void FadeInUpdate(Input&);
    void NormalUpdate(Input& input);
    void FadeOutUpdate(Input&);

    // 描画状態を表す関数
    void FadeDraw();
    void NormalDraw();
};

