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
    
    //フェイドに関するフレーム数
    int frame_;    
    //ゲームクリア時のSE
    int m_clearSE;    
    //BGM
    int m_bgm;    
    //背景
    int m_bg;    
    //ゲームクリアの文字表示
    int m_gameClear;    
    //タイトルに戻るボタン
    int m_titleBack;    
    //描画時のX軸の調整値
    int m_widthAdjustment;    
    //描画時のY軸の調整値
    int m_heightAdjustment;

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

