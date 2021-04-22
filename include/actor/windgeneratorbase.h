#pragma once

#include "actor/actor.h"

class WindGeneratorBase : public Actor {  // size: 0x 
public:
	f32 finalWindStrength;
	f32 windStrengthValue;
	f32 strengthMultiplier;
	f32 directionMultiplier;
	u32 _28C;
	u32 timeOn;
	u32 timeOff;
	u32 windState;
	u32 timer;
	
	inline WindGeneratorBase(const ActorBuildInfo* buildInfo) : Actor(buildInfo) { }
	
	~WindGeneratorBase();
	u32 onCreate();
	u32 onExecute();
};
