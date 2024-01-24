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
    // �����o�֐��|�C���^�̐錾
    using UpdateFunc_t = void (GameClearScene::*)(Input&);
    using DrawFunc_t = void (GameClearScene::*)();
    UpdateFunc_t m_updateFunc;
    DrawFunc_t m_drawFunc;

    // �X�V��Ԃ�\���֐�
    void FadeInUpdate(Input&);
    void NormalUpdate(Input& input);
    void FadeOutUpdate(Input&);

    // �`���Ԃ�\���֐�
    void FadeDraw();
    void NormalDraw();
};

