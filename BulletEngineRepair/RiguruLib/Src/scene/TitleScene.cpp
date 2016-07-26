#include "TitleScene.h"
#include "../Input/Input.h"
#include "../Other/Device.h"
#include "../Graphic/Graphic.h"
#include "../Actor/Player.h"
#include "../Actor/Enemy.h"
#include "../Actor/Stage.h"
#include "../Math/Converter.h"

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

const float RADIUS =  10.0f;

//�R���X�g���N�^
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
	Graphic::GetInstance().LoadMesh(MODEL_ID::STAGE_MODEL, "Res/Rgr/Stage/map01/stageDraw.rgr");
}

//�f�X�g���N�^
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

//�J�n
void TitleScene::Initialize()
{
	mat = RCMatrix4::Identity();
	mat = RCMatrix4::scale(vector3(30, 30, 30)) *
		RCMatrix4::translate(vector3(0, 0, 0));

	Device::GetInstance().CameraInit(CAMERA_ID::NORMAL_CAMERA);
	gameExit = false;
	mIsEnd = false;
	wa.Initialize();
	Graphic::GetInstance().LoadShader(SHADER_ID::PLAYER_SHADER, "Shader/cso/fbxModelShader.cso");
	//	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
	//	wa.Add(ACTOR_ID::ENEMY_ACTOR, std::make_shared<Enemy>(wa));
	//	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));

	// �n�ʍ쐬�A���[���h�ɒǉ�
	//{
		//// �R���W�����`��@��
		//btBoxShape* ground_shape = new btBoxShape(btVector3(btScalar(80.0f), btScalar(80.0f), btScalar(80.0f)));
		//aCollisionShapes.push_back(ground_shape);
		//
		//btTransform ground_pos;
		//ground_pos.setIdentity();
		//ground_pos.setOrigin(btVector3(0, -80, 0));
		//
		//// �����Ȃ��̂Ŏ���0�@����0
		//btScalar mass(0.0f);
		//btVector3 inertia(0, 0, 0);
		//
		//btDefaultMotionState* motion_state = new btDefaultMotionState(ground_pos);
		//btRigidBody::btRigidBodyConstructionInfo rb_cinfo(mass, motion_state, ground_shape, inertia);
		//btRigidBody* body = new btRigidBody(rb_cinfo);
		//pDynamicsWorld->addRigidBody(body);
	//}

	{
		triangleVertices = Graphic::GetInstance().ReturnBulletVertex(MODEL_ID::STAGE_MODEL, mat, CAMERA_ID::NORMAL_CAMERA);
		triangleIndices = Graphic::GetInstance().ReturnBulletIndex(MODEL_ID::STAGE_MODEL);
		
		for (int i = 0; i < triangleIndices.size(); i++) {
			const int   numTriangles = triangleIndices[i].size() / 3;
			const int   triangleIndexStride = sizeof(int) * 3;
			const int   numVertices = triangleVertices[i].size() / 3;
			const int   vertexStride = sizeof(btVector3);

			pMeshData[i] = std::make_shared<btTriangleIndexVertexArray>(
				numTriangles,
				triangleIndices[i].data(),
				triangleIndexStride,
				numVertices,
				(btScalar*)triangleVertices[i].data(),
				vertexStride);

			btCollisionShape* pColShape = new btBvhTriangleMeshShape(pMeshData[i].get(), true);
			aCollisionShapes.push_back(pColShape);
			btTransform ground_pos;
			ground_pos.setIdentity();
			ground_pos.setOrigin(btVector3(0, 0, 0));

			// �����Ȃ��̂Ŏ���0�@����0
			btScalar mass(0.0f);
			btVector3 inertia(0, 0, 0);

			btDefaultMotionState* motion_state = new btDefaultMotionState(ground_pos);
			btRigidBody::btRigidBodyConstructionInfo rb_cinfo(mass, motion_state, pColShape, inertia);
			btRigidBody* body = new btRigidBody(rb_cinfo);
			pDynamicsWorld->addRigidBody(body);
		}
	}

	//�ŏ��̕`��
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
		btCollisionShape* colSphere = new btSphereShape(SCALING*btScalar(RADIUS));
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
		
		ball = new btRigidBody(btRigidBody::btRigidBodyConstructionInfo(
			mass, myMotionState, colSphere, localInertiaSphere));
		pDynamicsWorld->addRigidBody(ball);
	}
}

void TitleScene::Update(float frameTime)
{
	pDynamicsWorld->stepSimulation(frameTime, 0);
	Vector3 v =RConvertB(ball->getWorldTransform().getOrigin());
	Device::GetInstance().GetCamera(CAMERA_ID::NORMAL_CAMERA)->SetCamera(
		v + vector3(0, 50.0f, -70.0f),
		v);

	wa.Update(frameTime);
	if (Device::GetInstance().GetInput()->KeyDown(INPUTKEY::KEY_ESC, true))gameExit = true;

	Graphic::GetInstance().SetFrameTime(frameTime);

	pDynamicsWorld->setDebugDrawer(&bulletDraw);
	pDynamicsWorld->getDebugDrawer()->setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	fps = 1.0f / frameTime;
}

//�`��
void TitleScene::Draw() const
{
	wa.Draw(CAMERA_ID::NORMAL_CAMERA);
	
	//Graphic::GetInstance().SetShader(SHADER_ID::PLAYER_SHADER);
	//Graphic::GetInstance().SetTechniquePass(SHADER_ID::PLAYER_SHADER, "TShader", "P1");
	//Graphic::GetInstance().DrawMesh(MODEL_ID::STAGE_MODEL, &mat, CAMERA_ID::NORMAL_CAMERA);
	//
	//Vector3 v = RConvertB(ball->getWorldTransform().getOrigin());
	//Graphic::GetInstance().DrawSphere(v, RADIUS, CAMERA_ID::NORMAL_CAMERA);

	pDynamicsWorld->debugDrawWorld();
	Graphic::GetInstance().DrawLineAll();
	Graphic::GetInstance().DrawFontDirect(FONT_ID::TEST_FONT, vector2(0.0f, 1080 - 30.0f), vector2(0.20f, 0.25f), 0.45f, "FPS:" + std::to_string((int)fps),vector3(1,1,1));
}

//�I�����Ă��邩�H
bool TitleScene::IsEnd() const
{
	return mIsEnd;
}

//���̃V�[����Ԃ�
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