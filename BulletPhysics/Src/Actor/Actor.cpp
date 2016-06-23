#include "Actor.h"
#include "../Math/Converter.h"
#include "../Graphic/Graphic.h"
#include <float.h>
Actor::Actor(IWorld& world_) :world(world_)
{
	cubeCount = 0;
	colFunc[COL_ID::SPHERE_SPHERE_COLL] = std::bind(&Actor::SphereVsSphere, this, std::placeholders::_1);
}

Actor::~Actor(){

}

void Actor::Collide(COL_ID id, Actor& other){
	CollisionParameter colpara = colFunc[id](other);
	if (colpara.colFlag)
	{
		OnCollide(other, colpara);
		other.OnCollide(*this, colpara);
	}
}



ActorParameter Actor::GetParameter()
{
	return parameter;
}

CollisionParameter Actor::SphereVsSphere(const Actor & other) const
{
	CollisionParameter colpara;
	Vector3 pos = RCMatrix4::getPosition(parameter.matrix);
	Vector3 otherPos = RCMatrix4::getPosition(other.parameter.matrix);
	if (RCVector3::length(pos - otherPos) < parameter.radius + other.parameter.radius) {
		colpara.colFlag = true;
	}

	return colpara;
}