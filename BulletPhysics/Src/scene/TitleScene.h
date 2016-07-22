#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include "../Actor/Actor.h"
#include "../Math/Vector2.h"
#include "SceneParameter.h"
#include "../Bullet/BulletDraw.h"
#include <vector>

#define BT_NO_SIMD_OPERATOR_OVERLOADS //演算子のオーバーロードがdirectxmathと競合するので
#include "bullet/btBulletDynamicsCommon.h"

enum TITLE_SELECT{
	SELECT_GAMESTART,
	SELECT_OPTION,
	SELECT_RETURN,
};

class  TitleScene :public IScene{
public:
	//コンストラクタ 
	TitleScene(std::weak_ptr<SceneParameter> sp_);
	//デストラクタ
	~TitleScene();

	//更新前初期化
	virtual void Initialize() override;
	//更新処理
	virtual void Update(float frameTime)override;
	//描画処理
	virtual void Draw() const override;
	//終了しているか？
	virtual bool IsEnd() const override;
	//次のシーンを返す
	virtual Scene Next() const override;
	//終了時処理
	virtual void End()override;

	virtual bool GameExit() override;
	/*******************/

private:
	std::weak_ptr<SceneParameter> sp; 

	btDefaultCollisionConfiguration* pCollConfig = nullptr;
	btCollisionDispatcher* pDispatcher = nullptr;
	btDbvtBroadphase* pBroadphase = nullptr;
	btSequentialImpulseConstraintSolver* pSolver = nullptr;
	btDiscreteDynamicsWorld* pDynamicsWorld = nullptr;
	
	btAlignedObjectArray<btCollisionShape*>	aCollisionShapes;
	btClock Clock;

	float fps;

private:
	bool mIsEnd;
	bool gameExit;
	World wa;
	Matrix4 mat;
	DxDebugDraw bulletDraw;
	int* triangleIndices;
	btVector3*    triangleVertices;
	btStridingMeshInterface* pMeshData;

	/*float ts_scale[TITLE_SELECT_NUM];
	float ts_nextScale[TITLE_SELECT_NUM], ts_prevScale[TITLE_SELECT_NUM];
	float ts_alpha[TITLE_SELECT_NUM];
	float ts_nextAlpha[TITLE_SELECT_NUM];*/
};