#pragma once
#include "Scene.h"

class StageBase;
class StageManager;
class SceneMain : public Scene
{
public:
	SceneMain(SceneManager& mgr);
	virtual ~SceneMain();
    virtual void Init();
    virtual void Update(Input& input);
    virtual void Draw();

private:
    int frame_;
    // メンバ関数ポインタの宣言
    using UpdateFunc_t = void (SceneMain::*)(Input&);
    using DrawFunc_t = void (SceneMain::*)();
    UpdateFunc_t m_updateFunc;
    DrawFunc_t m_drawFunc;

    StageBase* m_pSBase;
    StageManager* m_pSManager;
    

    // 更新状態を表す関数
    void FadeInUpdate(Input&);
    void NormalUpdate(Input& input);
    void FadeOutUpdate(Input&);

    // 描画状態を表す関数
    void FadeDraw();
    void NormalDraw();
};