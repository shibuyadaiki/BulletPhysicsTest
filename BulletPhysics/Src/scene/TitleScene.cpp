#include "TitleScene.h"
#include "../Input/Input.h"
#include "../Other/Device.h"
#include "../Graphic/Graphic.h"
#include "../Actor/Player.h"
#include "../Actor/Enemy.h"
#include "../Actor/Stage.h"

#include "../stdafx.h"

#define FREEGLUT_STATIC

#define ARRAY_SIZE_X 5
#define ARRAY_SIZE_Y 1
#define ARRAY_SIZE_Z 5

#define MAX_PROXIES (ARRAY_SIZE_X*ARRAY_SIZE_Y*ARRAY_SIZE_Z + 1024)

#define SCALING 1.
#define START_POS_X 0
#define START_POS_Y 0
#define START_POS_Z 0

//コンストラクタ
TitleScene::TitleScene(std::weak_ptr<SceneParameter> sp_) :
	sp(sp_), gameExit(false),triangleIndices(NULL),triangleVertices(NULL), pMeshData(NULL)
{
	pCollConfig = new btDefaultCollisionConfiguration;
	pDispatcher = new	btCollisionDispatcher(pCollConfig);
	pBroadphase = new btDbvtBroadphase;
	pSolver = new btSequentialImpulseConstraintSolver;
	pDynamicsWorld = new btDiscreteDynamicsWorld(pDispatcher, pBroadphase, pSolver, pCollConfig);

	pDynamicsWorld->setDebugDrawer(nullptr);
	pDynamicsWorld->setGravity(btVector3(0, -10, 0));
	Graphic::GetInstance().LoadMesh(MODEL_ID::STAGE_MODEL, "Res/Rgr/Stage/testStage.rgr");
}

//デストラクタ
TitleScene::~TitleScene()
{
	SAFE_DELETE_ARRAY(triangleIndices);
	SAFE_DELETE_ARRAY(triangleVertices);
	SAFE_DELETE_ARRAY(pMeshData);
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

	for (int j = 0; j < aCollisionShapes.size(); j++)
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
	mat = RCMatrix4::Identity();
	mat = RCMatrix4::scale(vector3(1, 1, 1)) *
		RCMatrix4::translate(vector3(0, -30, 10));

	Device::GetInstance().CameraInit(CAMERA_ID::NORMAL_CAMERA);
	gameExit = false;
	mIsEnd = false;
	wa.Initialize();
	Graphic::GetInstance().LoadShader(SHADER_ID::PLAYER_SHADER, "Shader/cso/fbxModelShader.cso");
	//	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	//	wa.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<Enemy>(wa));
	//	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));

	// 地面作成、ワールドに追加
	//{
		//// コリジョン形状　箱
		//btBoxShape* ground_shape = new btBoxShape(btVector3(btScalar(80.0f), btScalar(80.0f), btScalar(80.0f)));
		//aCollisionShapes.push_back(ground_shape);
		//
		//btTransform ground_pos;
		//ground_pos.setIdentity();
		//ground_pos.setOrigin(btVector3(0, -80, 0));
		//
		//// 動かないので質量0　慣性0
		//btScalar mass(0.0f);
		//btVector3 inertia(0, 0, 0);
		//
		//btDefaultMotionState* motion_state = new btDefaultMotionState(ground_pos);
		//btRigidBody::btRigidBodyConstructionInfo rb_cinfo(mass, motion_state, ground_shape, inertia);
		//btRigidBody* body = new btRigidBody(rb_cinfo);
		//pDynamicsWorld->addRigidBody(body);
	//}

	{
		std::vector<Vector3> bV = Graphic::GetInstance().ReturnBulletVertex(MODEL_ID::STAGE_MODEL, mat, CAMERA_ID::NORMAL_CAMERA);
		std::vector<int> bI = Graphic::GetInstance().ReturnBulletIndex(MODEL_ID::STAGE_MODEL);
		triangleIndices = new int[bI.size()];
		triangleVertices = new btVector3[bV.size()];

		for (int i = 0; i < bI.size(); i++) {
			triangleIndices[i] = bI[i];
		}
		for (int i = 0; i < bV.size(); i++) {
			triangleVertices[i] = btVector3(bV[i].x, bV[i].y, bV[i].z);
		}

		const int   numTriangles = bI.size() / 3;
		int*    pTriangleIndexBase = triangleIndices;
		const int   triangleIndexStride = sizeof(int) * 3;
		const int   numVertices = bV.size() / 3;
		btScalar*  pVertexBase = (btScalar*)triangleVertices;
		const int   vertexStride = sizeof(btVector3);

		 pMeshData = new btTriangleIndexVertexArray(
			numTriangles,
			triangleIndices,
			triangleIndexStride,
			numVertices,
			pVertexBase,
			vertexStride);
		
		 btCollisionShape* pColShape = new btBvhTriangleMeshShape(pMeshData, true);
		 aCollisionShapes.push_back(pColShape);
		 btTransform ground_pos;
		 ground_pos.setIdentity();
		 ground_pos.setOrigin(btVector3(0, 0, 0));
		 
		 // 動かないので質量0　慣性0
		 btScalar mass(0.0f);
		 btVector3 inertia(0, 0, 0);
		 
		 btDefaultMotionState* motion_state = new btDefaultMotionState(ground_pos);
		 btRigidBody::btRigidBodyConstructionInfo rb_cinfo(mass, motion_state,pColShape, inertia);
		 btRigidBody* body = new btRigidBody(rb_cinfo);
		 pDynamicsWorld->addRigidBody(body);
	}

	//最初の描画
	{
		//btBoxShape* colBox = new btBoxShape(btVector3(SCALING * 1, SCALING * 1, SCALING * 1));
		//btCollisionShape* colSphere = new btSphereShape(SCALING*btScalar(1.));
		//btCapsuleShape* colCapsule = new btCapsuleShape(SCALING*1.0f, SCALING*2.0f);
		//aCollisionShapes.push_back(colBox);
		//aCollisionShapes.push_back(colSphere);
		//aCollisionShapes.push_back(colCapsule);
		//
		///// Create Dynamic Objects
		//btTransform startTransform;
		//startTransform.setIdentity();
		//
		//btScalar	mass(1.f);
		//
		////rigidbody is dynamic if and only if mass is non zero, otherwise static
		//bool isDynamic = (mass != 0.f);
		//
		//btVector3 localInertiaBox(0, 0, 0);
		//btVector3 localInertiaSphere(0, 0, 0);
		//btVector3 localInertiaCapsule(0, 0, 0);
		//if (isDynamic) {
		//	colBox->calculateLocalInertia(mass, localInertiaBox);
		//	colSphere->calculateLocalInertia(mass, localInertiaSphere);
		//	colCapsule->calculateLocalInertia(mass, localInertiaCapsule);
		//}
		//float start_x = START_POS_X - ARRAY_SIZE_X / 2;
		//float start_y = START_POS_Y;
		//float start_z = START_POS_Z - ARRAY_SIZE_Z / 2;
		//
		//for (int k = 0; k<ARRAY_SIZE_Y; k++)
		//{
		//	for (int i = 0; i<ARRAY_SIZE_X; i++)
		//	{
		//		for (int j = 0; j<ARRAY_SIZE_Z; j++)
		//		{
		//			startTransform.setOrigin(SCALING*btVector3(
		//				btScalar(10.0*i + start_x),
		//				btScalar(20 + 10.0*k + start_y),
		//				btScalar(10.0*j + start_z)));
		//
		//			btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		//			btRigidBody* body = nullptr;
		//			switch ((k + i + j) % 3) {
		//			case 0:
		//				body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
		//					mass, myMotionState, colBox, localInertiaBox));
		//				break;
		//			case 1:
		//				body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
		//					mass, myMotionState, colSphere, localInertiaSphere));
		//				break;
		//			case 2:
		//				body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
		//					mass, myMotionState, colCapsule, localInertiaCapsule));
		//				break;
		//			}
		//			pDynamicsWorld->addRigidBody(body);
		//		}
		//	}
		//}

		btTransform startTransform;
		startTransform.setIdentity();
		
		btScalar	mass(1.0f);
		btCollisionShape* colSphere = new btSphereShape(SCALING*btScalar(1.));
		aCollisionShapes.push_back(colSphere);
		////rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);
		
		btVector3 localInertiaSphere(0, 0, 0);
		if (isDynamic) {
			colSphere->calculateLocalInertia(mass, localInertiaSphere);
		}
		startTransform.setOrigin(SCALING*btVector3(
			btScalar(0),
			btScalar(20),
			btScalar(0)));
		
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody* body = nullptr;
		body = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
			mass, myMotionState, colSphere, localInertiaSphere));
		pDynamicsWorld->addRigidBody(body);
	}
}

void TitleScene::Update(float frameTime)
{
	pDynamicsWorld->stepSimulation(frameTime, 0);
	Device::GetInstance().GetCamera(CAMERA_ID::NORMAL_CAMERA)->SetCamera(
		vector3(0, 20.0f, -70.0f),
		vector3(0, 0, 0));

	wa.Update(frameTime);
	if (Device::GetInstance().GetInput()->KeyDown(INPUTKEY::KEY_ESC, true))gameExit = true;

	Graphic::GetInstance().SetFrameTime(frameTime);

	pDynamicsWorld->setDebugDrawer(&bulletDraw);
	pDynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	fps = 1.0f / frameTime;
}

//描画
void TitleScene::Draw() const
{
	wa.Draw(CAMERA_ID::NORMAL_CAMERA);
	
	//Graphic::GetInstance().SetShader(SHADER_ID::PLAYER_SHADER);
	//Graphic::GetInstance().SetTechniquePass(SHADER_ID::PLAYER_SHADER, "TShader", "P1");
	//Graphic::GetInstance().DrawMesh(MODEL_ID::STAGE_MODEL, &mat, CAMERA_ID::NORMAL_CAMERA);
	pDynamicsWorld->debugDrawWorld();
	Graphic::GetInstance().DrawLineAll();
	Graphic::GetInstance().DrawFontDirect(FONT_ID::TEST_FONT, vector2(0.0f, 1080 - 30.0f), vector2(0.20f, 0.25f), 0.45f, "FPS:" + std::to_string((int)fps),vector3(1,1,1));
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

void TitleScene::End() {
	wa.Clear();
}

bool TitleScene::GameExit() {
	return gameExit;
}