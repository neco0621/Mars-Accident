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
    // �����o�֐��|�C���^�̐錾
    using UpdateFunc_t = void (GameOverScene::*)(Input&);
    using DrawFunc_t = void (GameOverScene::*)();
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

