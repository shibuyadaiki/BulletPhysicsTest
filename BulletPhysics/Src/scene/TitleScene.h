#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../Actor/Actor.h"
#include "../Math/Vector2.h"
#include "SceneParameter.h"
#include <vector>

#pragma push_macro("new")
#undef new
#include <bullet/btBulletDynamicsCommon.h>
#pragma pop_macro("new")

enum TITLE_SELECT{
	SELECT_GAMESTART,
	SELECT_OPTION,
	SELECT_RETURN,
};

class  TitleScene :public IScene{
public:
	//�R���X�g���N�^ 
	TitleScene(std::weak_ptr<SceneParameter> sp_);
	//�f�X�g���N�^
	~TitleScene();

	//�X�V�O������
	virtual void Initialize() override;
	//�X�V����
	virtual void Update(float frameTime)override;
	//�`�揈��
	virtual void Draw() const override;
	//�I�����Ă��邩�H
	virtual bool IsEnd() const override;
	//���̃V�[����Ԃ�
	virtual Scene Next() const override;
	//�I��������
	virtual void End()override;

	virtual bool GameExit() override;
	/*******************/

private:
	std::weak_ptr<SceneParameter> sp; 

private:
	bool mIsEnd;
	bool gameExit;
	World wa;

	//btDefaultCollisionConfiguration* pCollConfig = nullptr;
	//btCollisionDispatcher* pDispatcher = nullptr;
	//btDbvtBroadphase* pBroadphase = nullptr;
	//btSequentialImpulseConstraintSolver* pSolver = nullptr;
	//btDiscreteDynamicsWorld* pDynamicsWorld = nullptr;
	//
	//btAlignedObjectArray<btCollisionShape*>	aCollisionShapes;
	//btClock Clock;
	/*float ts_scale[TITLE_SELECT_NUM];
	float ts_nextScale[TITLE_SELECT_NUM], ts_prevScale[TITLE_SELECT_NUM];
	float ts_alpha[TITLE_SELECT_NUM];
	float ts_nextAlpha[TITLE_SELECT_NUM];*/
};