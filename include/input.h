#pragma once

#include "sead.h"

// TODO: finish, verify

class Controller {
	public:
	s32 getTilt(u32*, float multiplier);
};

class InputMgr : public sead::IDisposer {
	public:
	static InputMgr *instance;

	Controller controllers[4];
	// TODO
};
