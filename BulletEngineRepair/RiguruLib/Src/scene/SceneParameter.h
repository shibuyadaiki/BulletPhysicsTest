#pragma once
#include "../Actor/ID.h"

class SceneParameter{
public:
	SceneParameter(){
		vID = VICTORY_ID::PLAYER_WIN;
	}
	~SceneParameter(){}
	void SetVictoryID(VICTORY_ID vID_){ vID = vID_; }

	VICTORY_ID* ReturnVictoryID(){ return &vID; }
private:
	VICTORY_ID vID;
};