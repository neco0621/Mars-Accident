#pragma once
#include "Scene.h"
class GameClearScene : public Scene
{
public:
    GameClearScene(SceneManager& mgr);
    ~GameClearScene();
    virtual void Init();
    virtual void Update(Input& input);
    virtual void Draw();

private:
    int frame_;
    // メンバ関数ポインタの宣言
    using UpdateFunc_t = void (GameClearScene::*)(Input&);
    using DrawFunc_t = void (GameClearScene::*)();
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

