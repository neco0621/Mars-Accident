#pragma once
#include <list> 
#include <memory>
class Input;
class Scene;

/// <summary>
/// �e�V�[���̑J�ڂƑ�����R���g���[������N���X
/// </summary>
class SceneManager
{
private:
	std::list<std::shared_ptr<Scene>>scenes_;
public:
	~SceneManager();
	/// <summary>
	/// �����Ă���V�[����Update�֐����Ăяo��
	/// </summary>
	/// <param name="input">���̓N���X</param>
	void Update(Input& input);

	/// <summary>
	/// �����Ă���V�[����Draw�֐����Ăяo��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���ݎ��s���̃V�[���������Ŏw�肳�ꂽ�V�[���ɐ؂�ւ���
	/// </summary>
	void ChangeScene(std::shared_ptr<Scene> nextScene);

	/// <summary>
	/// ���ݐ擪�Ŏ��s���̃V�[���̏�ɃV�[�����̂�����
	/// </summary>
	void PushScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// ���݂̐퓬�V�[�����|�b�v(�폜)����
	/// </summary>
	void popScene();
};

