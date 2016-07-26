#pragma once

#include "../Other/DX11User.h"
#include "../Other/D3D11User.h"
#include <map>
#include "ID.h"
#include "../Math/Matrix4.h"
#include "../Math/MatrixUtility.h"
#include "../Graphic/Rgr/MeshUser.h"
#include "Actor.h"

class Player :public Actor, public std::enable_shared_from_this<Player>{
public:
	Player(IWorld& world_);
	~Player();
	virtual void Initialize() override;
	virtual void Update(float frameTime) override;
	virtual void Draw(CAMERA_ID cID, bool first) const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	float animSpeed,animBlendSpeed;
	Vector3 scale,color;
	Vector3 beforePos;
};