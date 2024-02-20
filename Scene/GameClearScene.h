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
    
    //�t�F�C�h�Ɋւ���t���[����
    int frame_;    
    //�Q�[���N���A����SE
    int m_clearSE;    
    //BGM
    int m_bgm;    
    //�w�i
    int m_bg;    
    //�Q�[���N���A�̕����\��
    int m_gameClear;    
    //�^�C�g���ɖ߂�{�^��
    int m_titleBack;    
    //�`�掞��X���̒����l
    int m_widthAdjustment;    
    //�`�掞��Y���̒����l
    int m_heightAdjustment;

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

