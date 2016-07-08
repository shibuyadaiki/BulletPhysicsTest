#include "Player.h"
#include "../Graphic/Graphic.h"

const float PLAYERSPEED = 2.0f;

Player::Player(IWorld& world_)
:Actor(world_),
animSpeed(10.0f),
animBlendSpeed(10.0f),
scale(vector3(1.0f,1.0f,1.0f)),
color(vector3(1,0,0)),
beforePos(vector3(-0.5f,0.0f,0.0f))
{
	parameter.radius = 0.3f;
	parameter.id = ACTOR_ID::PLAYER_ACTOR;
	parameter.matrix = 
		RCMatrix4::scale(scale) *
		RCMatrix4::translate(vector3(-0.5f,0.0f,0.0f));
}

Player::~Player(){

}

void Player::Initialize(){
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
void Player::Update(float frameTime){
	color = vector3(1, 0, 0);
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::ENEMY_ACTOR, COL_ID::SPHERE_SPHERE_COLL);
	Vector3 position = RCMatrix4::getPosition(parameter.matrix);
	beforePos = position;
	Vector3 vec = vector3(0, 0, 0);
	if (Device::GetInstance().GetInput()->KeyDown(INPUTKEY::KEY_W, false)) {
		vec = vector3(0, 1, 0);
	}
	if (Device::GetInstance().GetInput()->KeyDown(INPUTKEY::KEY_S, false)) {
		vec = vector3(0, -1, 0);
	}
	if (Device::GetInstance().GetInput()->KeyDown(INPUTKEY::KEY_A, false)) {
		vec = vector3(-1, 0, 0);
	}
	if (Device::GetInstance().GetInput()->KeyDown(INPUTKEY::KEY_D, false)) {
		vec = vector3(1, 0, 0);
	}

	position += RCVector3::normalize(vec) * PLAYERSPEED * frameTime;

	parameter.matrix =
		RCMatrix4::scale(scale) *
		RCMatrix4::translate(position);
}

//描画
void Player::Draw(CAMERA_ID cID_, bool first) const{
	//Graphic::GetInstance().SetShader(SHADER_ID::PLAYER_SHADER);
	////テクニックとパスをセット
	//Graphic::GetInstance().SetTechniquePass(SHADER_ID::PLAYER_SHADER, "TShader", "P1");
	//Graphic::GetInstance().BindAnimation(shared_from_this());
	//Graphic::GetInstance().DrawMesh(MODEL_ID::TARENTULE_MODEL, vector3(0.5f, 0, 0), vector3(0.1f, 0.1f, 0.1f), vector3(0, 0, 0),cID_);
	Graphic::GetInstance().DrawSphere(RCMatrix4::getPosition(parameter.matrix), parameter.radius, cID_,color,1.0f);
}

void Player::OnCollide(Actor& other, CollisionParameter colpara){
	parameter.matrix =
		RCMatrix4::scale(scale) *
		RCMatrix4::translate(beforePos);
}