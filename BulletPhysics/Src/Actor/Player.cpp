#include "Player.h"
#include "../Graphic/Graphic.h"

Player::Player(IWorld& world_)
:Actor(world_),
animSpeed(10.0f),
animBlendSpeed(10.0f){
}

Player::~Player(){

}

void Player::Initialize(){
	Graphic::GetInstance().SetAnimation(
		shared_from_this(),
		ANIM_ID::NEPHILA_WALKFRONT_ANIM,
		0.0f,
		&animSpeed,
		ANIM_ID::NEPHILA_WALKFRONT_ANIM,
		0.0f,
		&animSpeed,
		0.0f,
		true,
		&animBlendSpeed);
}
void Player::Update(float frameTime){
}

//描画
void Player::Draw(CAMERA_ID cID_, bool first) const{
	Graphic::GetInstance().SetShader(SHADER_ID::PLAYER_SHADER);
	//テクニックとパスをセット
	Graphic::GetInstance().SetTechniquePass(SHADER_ID::PLAYER_SHADER, "TShader", "P0");
	Graphic::GetInstance().BindAnimation(shared_from_this());
	Graphic::GetInstance().DrawMesh(MODEL_ID::TARENTULE_MODEL, vector3(0, 0, 0), vector3(0.1f, 0.1f, 0.1f), vector3(0, 0, 0),cID_);
}

void Player::OnCollide(Actor& other, CollisionParameter colpara){

}
