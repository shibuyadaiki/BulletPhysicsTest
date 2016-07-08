#include "Stage.h"
#include "../Graphic/Graphic.h"


Stage::Stage(IWorld& world_)
	:Actor(world_)
{
	parameter.radius = 0.3f;
	parameter.id = ACTOR_ID::STAGE_ACTOR;
	parameter.matrix =
		RCMatrix4::scale(vector3(1,1,1)) *
		RCMatrix4::translate(vector3(0.0f, -0.5f, 0.0f));
}

Stage::~Stage() {

}

void Stage::Initialize() {
	//Graphic::GetInstance().SetAnimation(
	//	shared_from_this(),
	//	ANIM_ID::NEPHILA_WALKFRONT_ANIM,
	//	0.0f,
	//	&animSpeed,
	//	ANIM_ID::NEPHILA_WALKFRONT_ANIM,
	//	0.0f,
	//	&animSpeed,
	//	0.0f,
	//	true,
	//	&animBlendSpeed);
}
void Stage::Update(float frameTime) {
	
}

//描画
void Stage::Draw(CAMERA_ID cID_, bool first) const {
	//Graphic::GetInstance().SetShader(SHADER_ID::Stage_SHADER);
	////テクニックとパスをセット
	//Graphic::GetInstance().SetTechniquePass(SHADER_ID::Stage_SHADER, "TShader", "P1");
	//Graphic::GetInstance().BindAnimation(shared_from_this());
	//Graphic::GetInstance().DrawMesh(MODEL_ID::TARENTULE_MODEL, vector3(0.5f, 0, 0), vector3(0.1f, 0.1f, 0.1f), vector3(0, 0, 0),cID_);
	Graphic::GetInstance().DrawCube(vector3(-3.0f,-0.5f,-3.0f), vector3(3.0f, -0.5f, 3.0f), cID_, vector3(1,1,1), 1.0f);
}

void Stage::OnCollide(Actor& other, CollisionParameter colpara) {
}
