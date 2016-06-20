#pragma once
#include "ID.h"
#include "../math/Matrix4.h"
#include "../math/Vector3.h"
#include "../math/Vector3Utility.h"
#include "../math/MatrixUtility.h"
#include "../Graphic/Rgr/OctreeUser.h"
#include "../Other/DX11User.h"
#include <functional>
#include "../world/IWorld.h"
//あたり判定のパラメータ
struct CollisionParameter{
	bool colFlag = false;
};
//アクターのパラメータ
struct ActorParameter
{
	ACTOR_ID id;
	Matrix4 matrix;
	bool isDead = false;
	Vector3 cubeScale;
	float radius;
	OCT_ID octId = OCT_ID::NULL_OCT;
	Vector3 moveVec;
	Vector3 inertiaVec;
	Vector3 lastNor;

};
enum TEAM_ID{
	FIRST_TEAM,
	SECOND_TEAM,
};
class Actor{
public:
	Actor(IWorld& world_);
	~Actor();
	virtual void Initialize() = 0;
	virtual void Update(float frameTime) = 0;
	virtual void Draw(CAMERA_ID cID, bool first) const = 0;
	void Collide(COL_ID id, Actor& other);
	virtual bool IsDead() const{ return parameter.isDead; }
	void SetIsDead(bool flag){ parameter.isDead = flag; }
	ActorParameter GetParameter();
protected:
	virtual void OnCollide(Actor& other,CollisionParameter colpara) = 0;
	ActorParameter parameter;
	IWorld& world;

private:
	std::map<COL_ID, std::function<CollisionParameter(const Actor&)>> colFunc;
	CollisionParameter colpara;
	int cubeCount;
};