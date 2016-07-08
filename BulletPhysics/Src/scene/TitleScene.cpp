#include "TitleScene.h"
#include "../Input/Input.h"
#include "../Other/Device.h"
#include "../Graphic/Graphic.h"
#include "../Actor/Player.h"
#include "../Actor/Enemy.h"
#include "../Actor/Stage.h"

#include "../stdafx.h"

#define FREEGLUT_STATIC

//コンストラクタ
TitleScene::TitleScene(std::weak_ptr<SceneParameter> sp_) :
sp(sp_), gameExit(false)
{
	pCollConfig = new btDefaultCollisionConfiguration;
	pDispatcher = new	btCollisionDispatcher(pCollConfig);
	pBroadphase = new btDbvtBroadphase;
	pSolver = new btSequentialImpulseConstraintSolver;
	pDynamicsWorld = new btDiscreteDynamicsWorld(pDispatcher, pBroadphase, pSolver, pCollConfig);
	
	pDynamicsWorld->setDebugDrawer(nullptr);
	pDynamicsWorld->setGravity(btVector3(0, -10, 0));
}

//デストラクタ
TitleScene::~TitleScene()
{
	int i;
	for (i = pDynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = pDynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		pDynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	for (int j = 0; j<aCollisionShapes.size(); j++)
	{
		btCollisionShape* shape = aCollisionShapes[j];
		delete shape;
	}

	aCollisionShapes.clear();
	if (pDynamicsWorld)delete pDynamicsWorld;
	if (pSolver)delete pSolver;
	if (pBroadphase)delete pBroadphase;
	if (pDispatcher)delete pDispatcher;
	if (pCollConfig)delete pCollConfig;
}

//開始
void TitleScene::Initialize()
{
	Device::GetInstance().CameraInit(CAMERA_ID::NORMAL_CAMERA);
	gameExit = false;
	mIsEnd = false;
	wa.Initialize();
	Graphic::GetInstance().LoadShader(SHADER_ID::PLAYER_SHADER, "Shader/cso/fbxModelShader.cso");
	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	wa.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<Enemy>(wa));
	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));
}

void TitleScene::Update(float frameTime)
{
	Device::GetInstance().GetCamera(CAMERA_ID::NORMAL_CAMERA)->SetCamera(
		vector3(0, 2.0f, -5.0f),
		vector3(0, 0, 0));

	wa.Update(frameTime);
	if(Device::GetInstance().GetInput()->KeyDown(INPUTKEY::KEY_ESC, true))gameExit = true;

	Graphic::GetInstance().SetFrameTime(frameTime);
}

//描画
void TitleScene::Draw() const
{
	wa.Draw(CAMERA_ID::NORMAL_CAMERA);
}

//終了しているか？
bool TitleScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene TitleScene::Next() const
{
	return Scene::GamePlay;
}

void TitleScene::End(){
	wa.Clear();
}

bool TitleScene::GameExit(){
	return gameExit;
}