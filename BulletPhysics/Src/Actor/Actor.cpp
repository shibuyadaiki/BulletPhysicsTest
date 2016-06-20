#include "Actor.h"
#include "../Math/Converter.h"
#include "../Graphic/Graphic.h"
#include <float.h>
Actor::Actor(IWorld& world_) :world(world_)
{
	cubeCount = 0;
	//colFunc[COL_ID::RAY_MODEL_ONTHREAD_COLL] = std::bind(&Actor::RayModelOnThread, this, std::placeholders::_1);
}

Actor::~Actor(){

}

void Actor::Collide(COL_ID id, Actor& other){
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