#include "TitleScene.h"
#include "../Input/Input.h"
#include "../Other/Device.h"
#include "../Graphic/Graphic.h"
#include "../Actor/Player.h"

//コンストラクタ
TitleScene::TitleScene(std::weak_ptr<SceneParameter> sp_) :
sp(sp_), gameExit(false)
{
}

//デストラクタ
TitleScene::~TitleScene()
{
}

//開始
void TitleScene::Initialize()
{
	Device::GetInstance().CameraInit(CAMERA_ID::NORMAL_CAMERA);
	gameExit = false;
	mIsEnd = false;
	wa.Initialize();
	Graphic::GetInstance().LoadMesh(MODEL_ID::TARENTULE_MODEL, "Res/Rgr/kumo/kumo.rgr");
	Graphic::GetInstance().LoadShader(SHADER_ID::PLAYER_SHADER, "Shader/cso/fbxModelShader.cso");
	Graphic::GetInstance().LoadAnimation(ANIM_ID::NEPHILA_WALKFRONT_ANIM, "Res/RgrA/kumo/kumoFront.rgra");
	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa));
}

void TitleScene::Update(float frameTime)
{
	Device::GetInstance().GetCamera(CAMERA_ID::NORMAL_CAMERA)->SetCamera(
		vector3(0, 0, 5.0f),
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