#include "Enemy.h"
#include "../Graphic/Graphic.h"

Enemy::Enemy(IWorld& world_)
	:Actor(world_),
	animSpeed(10.0f),
	animBlendSpeed(10.0f)
{
	parameter.radius = 0.3f;
	parameter.id = ACTOR_ID::ENEMY_ACTOR;
	parameter.matrix =
		RCMatrix4::scale(vector3(1.0f, 1.0f, 1.0f)) *
		RCMatrix4::translate(vector3(0.5f, 0.0f, 0.0f));
}

Enemy::~Enemy() {

}

void Enemy::Initialize() {
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
void Enemy::Update(float frameTime) {
}

//描画
void Enemy::Draw(CAMERA_ID cID_, bool first) const {
	//Graphic::GetInstance().SetShader(SHADER_ID::Enemy_SHADER);
	////テクニックとパスをセット
	//Graphic::GetInstance().SetTechniquePass(SHADER_ID::Enemy_SHADER, "TShader", "P1");
	//Graphic::GetInstance().BindAnimation(shared_from_this());
	//Graphic::GetInstance().DrawMesh(MODEL_ID::TARENTULE_MODEL, vector3(0.5f, 0, 0), vector3(0.1f, 0.1f, 0.1f), vector3(0, 0, 0),cID_);
	Graphic::GetInstance().DrawSphere(RCMatrix4::getPosition(parameter.matrix), parameter.radius, cID_, vector3(0, 0, 1), 1.0f);
}

void Enemy::OnCollide(Actor& other, CollisionParameter colpara) {

}
