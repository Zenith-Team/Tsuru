#pragma once

#include "game/actor/stage/stageactor.h"
#include "game/playerinput.h"
#include "game/states.h"

//! Pain
class PlayerBase : public StageActor { // Size: 0x2750
    SEAD_RTTI_OVERRIDE(PlayerBase, StageActor);

public:
    ENUM_CLASS(PowerupState,
        Small,
        Big,
        Fire,
        Mini,
        Propeller,
        Penguin,
        Ice,
        Acorn,
        PAcorn
    );

    ENUM_CLASS(DamageType, // TODO: Figure out all these types
        SingleHit,
        SingleHit_2,
        SingleHitBounce,
        SingleHit_3,
        Bounce,
        Bounce_2,
        Unk1,
        Unk2,
        Unk3,
        LavaNoInstaKill,
        Lava,
        Ice,
        Ice_2,
        Electric,
        Poison,
        InstaKill,
        InstaKill_2
    );

    ENUM_CLASS(TallType,
        Mini,
        Small,
        Normal
    );

public:
    PlayerBase(const ActorBuildInfo* buildInfo);
    virtual ~PlayerBase();

    u32 onCreate() override;

    u32 beforeExecute() override;
    u32 onExecute() override;
    void afterExecute(u32) override;

    u32 beforeDraw() override;

    void setPlayerID(s8 id) override;

    ActorPhysicsMgr* getActorPhysicsMgr() override;
    void vfAC() override;
    bool vfB4() override;
    void vfBC() override;
    void vfC4() override;
    void vfCC() override;

    void damageFromUnder() override;

    virtual void vf10C() = 0;
    virtual void vf114() = 0;
    virtual u32 vf11C() = 0;
    virtual void vf124(PowerupState::__type__, bool); // Calls vf12C
    virtual void vf12C(PowerupState::__type__, bool) = 0;
    virtual bool vf134();
    // @return The TallType value for the corresponding PowerupState
    virtual TallType getTallType(PowerupState::__type__ powerupState) = 0;
    virtual void vf144() = 0;
    virtual void vf14C(Vec3f*, f32*) = 0;
    virtual u32 vf154();
    virtual f32* vf15C() = 0; //? TallType related
    virtual f32 vf164() = 0;
    virtual void vf16C() = 0;
    virtual void vf174() = 0;
    virtual void vf17C() = 0;
    virtual void initHitboxes(const HitboxCollider::Info&, const HitboxCollider::Info&);
    virtual void vf18C();
    virtual void vf194();
    virtual bool vf19C() = 0;
    virtual void vf1A4();
    virtual void vf1AC(u32, u32);
    virtual void vf1B4();
    // @return Always true
    virtual bool vf1BC(Vec3f* out);
    virtual void vf1C4();
    virtual void vf1CC() = 0;
    virtual void vf1D4(u32) = 0;
    virtual bool vf1DC() = 0;
    virtual void vf1E4(const Vec3f&, u32);
    virtual void vf1EC();
    virtual void vf1F4(f32, u32);
    virtual void vf1FC();
    virtual void vf204(f32, u32);
    virtual void vf20C();
    virtual void vf214();
    virtual void vf21C();
    virtual void vf224(u32);
    virtual void vf22C();
    virtual void vf234();
    virtual void vf23C();
    virtual void vf244();
    virtual void vf24C(); // Calls vf1F4
    virtual void vf254();
    virtual void vf25C();
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState1);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState2);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState3);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState4);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState5);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState6);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState7);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState8);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState9);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState10);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState11);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState12);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState13);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState14);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState15);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState16);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState17);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState18);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState19);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState20);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState21);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState22);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState23);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState24);
    DECLARE_STATE_VIRTUAL(PlayerBase, PlayerBaseState25);
    virtual void vf4BC(bool) = 0;
    virtual void vf4C4(u32); // Add flag to _20DC
    virtual void vf4CC(u32); // Remove flag from _20DC
    virtual void vf4D4(); // Clear flags from _20DC
    virtual bool vf4DC(); // Is any flag set in _20DC
    virtual bool vf4E4(u32); // Is specific flag set in _20DC
    virtual bool vf4EC() = 0;
    virtual bool vf4F4();
    virtual bool vf4FC() = 0;
    virtual bool vf504() = 0;
    virtual void vf50C(f32*, u32, f32) = 0;
    virtual bool vf514() = 0;
    virtual void vf51C(u32); // Deleted
    virtual void vf524(void*, u32) = 0;
    virtual void vf52C() = 0;
    virtual void vf534();
    virtual void vf53C() = 0;
    virtual void vf544() = 0;
    virtual void vf54C() = 0;
    virtual void vf554() = 0;
    virtual u32 vf55C(u32) = 0;
    virtual void vf564() = 0;
    virtual bool vf56C() = 0;
    virtual bool vf574() = 0;
    virtual void vf57C(u32);
    virtual f32 vf584() = 0; // TODO: Mess with this
    virtual void vf58C(Vec3f*) = 0;
    virtual void vf594(u32);
    virtual void vf59C() = 0;
    virtual void vf5A4() = 0;
    virtual void vf5AC(u32) = 0;
    virtual void vf5B4(); // Deleted
    virtual bool vf5BC() = 0;
    virtual bool vf5C4(f32, f32, u32, u32, u32) = 0;
    virtual void vf5CC();
    virtual void vf5D4();
    virtual void vf5DC();
    virtual void vf5E4();
    virtual void vf5EC();
    virtual void vf5F4();
    virtual void vf5FC();
    virtual void vf604();
    virtual void vf60C();
    virtual void vf614();
    virtual void vf61C();
    virtual void vf624();
    virtual void vf62C();
    virtual void vf634();
    virtual void vf63C();
    virtual void vf644();
    virtual void vf64C();
    virtual void vf654();
    virtual void vf65C();
    virtual void vf664();
    virtual void vf66C();
    virtual void vf674();
    virtual void vf67C();
    virtual void vf684();
    virtual void vf68C();
    virtual void vf694();
    virtual void vf69C();
    virtual void vf6A4();
    virtual void vf6AC();
    virtual void vf6B4();
    virtual void vf6BC();
    virtual void vf6C4();
    virtual void vf6CC();
    virtual void vf6D4();
    virtual void vf6DC();
    virtual void vf6E4();
    virtual void vf6EC();
    virtual void vf6F4();
    virtual void vf6FC();
    virtual void vf704();
    virtual void vf70C();
    virtual void vf714();
    virtual void vf71C();
    virtual void vf724();
    virtual void vf72C();
    virtual void vf734();
    virtual void vf73C();
    virtual void vf744();
    virtual void vf74C();
    virtual void vf754();
    virtual void vf75C();
    virtual void vf764();
    virtual void vf76C();
    virtual void vf774();
    virtual bool vf77C() = 0;
    virtual void vf784(bool) = 0;
    virtual void vf78C(u32) = 0;
    virtual void vf794() = 0;
    virtual u32 vf79C();
    virtual void vf7A4() = 0;
    virtual bool vf7AC() = 0;
    virtual bool vf7B4() = 0;
    virtual void vf7BC() = 0;
    virtual void vf7C4() = 0;
    virtual void vf7CC() = 0;
    virtual bool vf7D4() = 0;
    virtual void vf7DC();
    virtual bool vf7E4();
    virtual bool vf7EC() = 0;
    virtual bool vf7F4(void*, void*) = 0;
    virtual void vf7FC() = 0;
    virtual f32 vf804() = 0; // Return value is from arrays based on powerup state
    virtual void vf80C();
    virtual void vf814();
    virtual void vf81C();
    virtual void vf824(u32);
    virtual void vf82C(u32);
    virtual bool vf834();
    virtual bool vf83C();
    virtual bool vf844(); // Deleted
    virtual bool vf84C();
    virtual void vf854() = 0;
    virtual void vf85C(f32) = 0;
    virtual void vf864(u32) = 0;
    virtual void vf86C() = 0;
    virtual bool vf874();
    virtual u32 vf87C();
    virtual void resetFallSpeed();
    virtual void vf88C() = 0;
    virtual f32 vf894() = 0;
    virtual f32 vf89C() = 0;
    virtual void vf8A4(u32) = 0;
    virtual void vf8AC(u32) = 0;
    virtual bool vf8B4() = 0;
    virtual void vf8BC() = 0;
    virtual bool tryDamage(HitboxCollider* hcOther) = 0;
    virtual bool trySpecialDamage(StageActor* collidingActor, DamageType::__type__ damageType) = 0;
    virtual bool vf8D4(StageActor* collidingActor, DamageType::__type__ damageType) = 0;
    virtual void vf8DC(f32, f32, u32, u32, u32, u32) = 0;
    virtual bool doDamage(StageActor* collidingActor, DamageType::__type__ damageType) = 0;
    virtual u32 vf8EC(u32, u32) = 0;
    virtual void vf8F4() = 0;
    virtual u8 vf8FC() = 0;
    virtual u32 vf904(u32) = 0;
    virtual void vf90C(u32, u32) = 0;
    virtual bool hasStar() = 0;
    virtual void vf91C() = 0;
    virtual void vf924(PlayerBase*) = 0;
    virtual void vf92C();
    virtual u32 vf934() = 0; // TallType related
    virtual u32 vf93C() = 0; // TallType related
    virtual u32 vf944() = 0; // TallType related
    virtual u32 vf94C() = 0; // TallType related
    virtual u32 vf954() = 0; // TallType related
    virtual u32 vf95C() = 0; // TallType related
    virtual u32 vf964() = 0; // TallType related
    virtual u32 vf96C() = 0; // TallType related
    virtual u32 vf974() = 0; // TallType related
    virtual u32 vf97C() = 0; // TallType related
    virtual u32 vf984(bool) = 0; // TallType related
    virtual u32 vf98C() = 0; // TallType related
    virtual u32 vf994(bool) = 0; // TallType related
    virtual u32 vf99C(bool) = 0; // TallType related
    virtual u32 vf9A4() = 0; // TallType related
    virtual void vf9AC(bool);
    virtual void vf9B4();
    virtual void vf9BC();
    virtual void vf9C4();
    virtual void vf9CC();
    virtual void vf9D4();
    virtual void vf9DC();
    virtual void vf9E4();
    virtual void vf9EC();
    virtual void vf9F4();
    virtual void vf9FC();
    virtual void vfA04();
    virtual void vfA0C();
    virtual void vfA14();
    virtual void vfA1C();
    virtual void vfA24();
    virtual void vfA2C() = 0;
    virtual void vfA34() = 0;
    virtual void vfA3C() = 0;
    virtual void vfA44() = 0;

    u8 _27C[0x2C];                        // 27C
    PlayerInput input;                    // 2A8
    u8 _33C[0x1C4];                       // 33C
    PowerupState::__type__ powerupState;  // 500
    u8 _504[0x4];                         // 504
    ActorPhysicsMgr playerPhysicsMgr;     // 508
    u8 _19E8[0xC0];                       // 19E8
    PhysicsMgr::Sensor sensorID2;         // 1AA8
    PhysicsMgr::Sensor sensorID3;         // 1AB4
    PhysicsMgr::Sensor sensorID0_1;       // 1AC0
    u8 _1ACC[0xEC];                       // 1ACC
    HitboxCollider playerHitboxCollider1; // 1BB8
    HitboxCollider playerHitboxCollider2; // 1CE0
    HitboxCollider playerHitboxCollider3; // 1E08
    HitboxCollider playerHitboxCollider4; // 1F30
    u8 _2058[0x6F8];                      // 2058
};
