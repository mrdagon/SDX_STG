#pragma once
#include <SDXFrameWork.h>
#include "ModelMove.h"

namespace SDX
{
/// <summary>�������郌�C���[�̎��ʎq</summary>
enum class Belong
{
	Ally,
	EnemyF,
	EnemyG,
	Item,
	Block,
	Etc
};

/// <summary>Model��STG�p�̋@�\��ǉ������N���X</summary>
///	\include
class Object : public Model , public ModelMove
{
friend class Layer;

protected:
	int  timer = 0;///�������Ă���o�߂����t���[����
	bool isOutCheck = true;///�͈͊O�������s�����t���O
	double  power;///�U����
	int  attribute;///�U������
	int  lifeTime = -1;///��������
	Belong belong;///�������郌�C���[

	/// <summary>���Ŕ�����s��</summary>
	virtual bool RemoveCheck(Rect* ���݉\�͈�)
	{
		if(
			timer == this->lifeTime ||
			(isOutCheck && !shape->Hit( ���݉\�͈� ) )
			)
		{
			this->isRemove = true;
		}

		if (isRemove) Remove();

		return this->isRemove;
	}

	/// <summary>�Փ˂�������ɍU������</summary>
	virtual void Attack(Object *�U���Ώ� )
	{
		�U���Ώ�->Damaged( power , attribute);
	}

	void SetTimer(int �t���[����)
	{
		timer = �t���[����;
	}

public:
	/// <summary>����</summary>
	Object( Shape *�����蔻�� , Sprite *�f�t�H���g�X�v���C�g , double �U���� = 0 , Belong ���� = Belong::Etc):
		Model( �����蔻�� , �f�t�H���g�X�v���C�g ),
		ModelMove(this),
		power(�U����),
		belong(����)
	{}

	int GetTimer()
	{
		return timer;
	}

	virtual ~Object(){}

	/// <summary>��Ԃ̍X�V</summary>
	virtual void Update()
	{
		this->timer++;
		AnimeUpdate();
		this->Act();
	}


	Belong GetBelong()
	{
		return belong;
	}

	/// <summary>Update���̍s������</summary>
	virtual void Act(){}

	/// <summary>���Ŏ��̏���</summary>
	virtual void Remove(){}

	/// <summary>�_���[�W���󂯂����̏���</summary>
	virtual void React(){}

	/// <summary>�U�����ꂽ���̏���</summary>
	virtual void Damaged(double damage, int attribute){}

};
}