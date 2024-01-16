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
    // �����o�֐��|�C���^�̐錾
    using UpdateFunc_t = void (SceneMain::*)(Input&);
    using DrawFunc_t = void (SceneMain::*)();
    UpdateFunc_t m_updateFunc;
    DrawFunc_t m_drawFunc;

    StageBase* m_pSBase;
    StageManager* m_pSManager;
    

    // �X�V��Ԃ�\���֐�
    void FadeInUpdate(Input&);
    void NormalUpdate(Input& input);
    void FadeOutUpdate(Input&);

    // �`���Ԃ�\���֐�
    void FadeDraw();
    void NormalDraw();
};