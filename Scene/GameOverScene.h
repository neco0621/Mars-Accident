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
    //Fade�Ɋւ���t���[����
    int frame_;
    //�Q�[���I�[�o�[�̕����\��
    int m_gameOver;
    //�^�C�g���ɖ߂�{�^��
    int m_titleBack;
    //���g���C�̕����\��
    int m_retry;
    //�w�i
    int m_bg;
    //BGM
    int m_bgm;

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

