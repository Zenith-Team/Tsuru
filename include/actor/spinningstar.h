#pragma once

#include "actor/multistateactor.h"

// TODO: verify

class SpinningStar : public MultiStateActor {  // size: 0x1DC4
public:
    SpinningStar(const ActorBuildInfo* buildInfo);
    virtual ~SpinningStar();

	bool checkDerivedRuntimeTypeInfo(void*);

	u32 onCreate() override;
	u32 onExecute() override;
	u32 onDraw() override;

	void setPlayerId(s8 id) override;

	CollisionMgr* getCollisionMgr() override;

	void vfAC() override;

	bool vfB4() override;

	void vfBC() override;
	void vfC4() override;
	void vfCC() override;

	void damageFromUnder() override;

	void vf10C(u8 unk) override;
	void vf11C() override;
	void vf124(f32) override;

	u32 vf12C() override;

	bool vf154() override;

	void move(Vec2& dest) override;
	void setYSpeed(f32 ySpeed) override;

	u32 vf16C() override;
	u32 vf174() override;

	void getRect(Rect& rect) override;

    static ActorInfo actorInfo;

	Vec3 _17C8;
	u32 _17D4;
	f32 _17D8;
	f32 _17DC;
	u32 _17E0;
	u32 _17E4;
	u8 customCollider[0x5A8];  //? Fix this for current collider names
	Vec3 _1D90;
	u32 _1D9C;
	u8 _1DA0;
	u32 _1DA4;
	u16 _1DA8;
	u16 _1DAA;
	u16 _1DAC;
	u16 _1DAE;
	u16 _1DB0;
	u8 _1DB2;
	u8 _1DB3;
	u8 _1DB4;
	u8 _1DB5;
	u8 _1DB6;
	u8 _1DB7;
	u8 _1DB8;
	u8 _1DB9;
	u32 _1DBC;
};
