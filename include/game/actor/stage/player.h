#pragma once

#include "game/actor/stage/playerbase.h"

// TODO: Player virtuals, members

class Player : public PlayerBase { // Size: 0x34D8
    SEAD_RTTI_OVERRIDE(Player, PlayerBase);

public:
    Player(const ActorBuildInfo* buildInfo);
    virtual ~Player();

    u32 onCreate() override;

    u32 beforeExecute() override;

    void afterExecute(u32) override;

    u32 beforeDraw() override;
    u32 onDraw() override;

    u32 onDelete() override;

    void setPlayerID(s8 id);

    ActorPhysicsMgr* getActorPhysicsMgr() override;
    void vfAC() override;
    bool vfB4() override;
    void vfBC() override;
    void vfC4() override;
    void vfCC() override;

    void vf10C() override;
    void vf114() override;
    u32 vf11C() override;
    void vf124(PowerupState::__type__, bool) override;
    void vf12C(PowerupState::__type__, bool) override;
    bool vf134() override;
    TallType getTallType(PowerupState::__type__ powerupState) override;
    void vf144() override;
    void vf14C(Vec3f*, f32*) override;
    u32 vf154() override;
    f32* vf15C() override;
    f32 vf164() override;
    void vf16C() override;
    void vf174() override;
    void vf17C() override;

    bool vf19C() override;

    void vf1CC();
    void vf1D4(u32);
    bool vf1DC();
    void vf1E4(const Vec3f&, u32);
    void vf1EC();
    void vf1F4(f32, u32);
    void vf1FC();
    void vf204(f32, u32);
    void vf20C();
    void vf214();
    void vf21C();
    void vf224(u32);
    void vf22C();
    void vf234();
    void vf23C();
    void vf244();
    void vf24C();
    void vf254();
    void vf25C();

    DECLARE_STATE_OVERRIDE(Player, PlayerBaseState5);

    DECLARE_STATE_OVERRIDE(Player, PlayerBaseState18);
    DECLARE_STATE_OVERRIDE(Player, PlayerBaseState19);

    DECLARE_STATE_OVERRIDE(Player, PlayerBaseState21);

    DECLARE_STATE_OVERRIDE(Player, PlayerBaseState25);

    void vf4BC(bool) override;

    bool vf4EC() override;
    bool vf4F4() override;
    bool vf4FC() override;
    bool vf504() override;
    void vf50C(f32*, u32, f32) override;
    bool vf514() override;
    void vf51C(u32) override;
    void vf524(void*, u32) override;
    void vf52C() override;
    void vf534() override;
    void vf53C() override;
    void vf544() override;
    void vf54C() override;
    void vf554() override;
    u32 vf55C(u32) override;
    void vf564() override;
    bool vf56C() override;
    bool vf574() override;
    void vf57C(u32) override;
    f32 vf584() override;
    void vf58C(Vec3f*) override;

    void vf59C() override;
    void vf5A4() override;
    void vf5AC(u32) override;

    bool vf5BC() override;
    bool vf5C4(f32, f32, u32, u32, u32) override;

    void vf5E4() override;
    void vf5EC() override;
    void vf5F4() override;
    void vf5FC() override;
    void vf604() override;
    void vf60C() override;
    void vf614() override;
    void vf61C() override;
    void vf624() override;
    void vf62C() override;
    void vf634() override;
    void vf63C() override;
    void vf644() override;
    void vf64C() override;
    void vf654() override;
    void vf65C() override;
    void vf664() override;
    void vf66C() override;
    void vf674() override;
    void vf67C() override;
    void vf684() override;
    void vf68C() override;
    void vf694() override;
    void vf69C() override;
    void vf6A4() override;
    void vf6AC() override;
    void vf6B4() override;
    void vf6BC() override;
    void vf6C4() override;
    void vf6CC() override;
    void vf6D4() override;
    void vf6DC() override;
    void vf6E4() override;
    void vf6EC() override;
    void vf6F4() override;
    void vf6FC() override;
    void vf704() override;
    void vf70C() override;
    void vf714() override;

    bool vf77C() override;
    void vf784(bool) override;
    void vf78C(u32) override;
    void vf794() override;
    u32 vf79C() override;
    void vf7A4() override;
    bool vf7AC() override;
    bool vf7B4() override;
    void vf7BC() override;
    void vf7C4() override;
    void vf7CC() override;
    bool vf7D4() override;
    void vf7DC() override;

    bool vf7EC() override;
    bool vf7F4(void*, void*) override;
    void vf7FC() override;
    f32 vf804() override;
    void vf80C() override;

    void vf81C() override;
    void vf824(u32) override;
    void vf82C(u32) override;
    bool vf834() override;
    bool vf83C() override;
    bool vf844() override;
    bool vf84C() override;
    void vf854() override;
    void vf85C(f32) override;
    void vf864(u32) override;
    void vf86C() override;
    bool vf874() override;
    u32 vf87C() override;
    void resetFallSpeed() override;
    void vf88C() override;
    f32 vf894() override;
    f32 vf89C() override;
    void vf8A4(u32) override;
    void vf8AC(u32) override;
    bool vf8B4() override;

    bool tryDamage(HitboxCollider* hcOther) override;
    bool trySpecialDamage(StageActor* collidingActor, DamageType::__type__ damageType) override;
    bool vf8D4(StageActor* collidingActor, DamageType::__type__ damageType) override;
    void vf8DC(f32, f32, u32, u32, u32, u32) override;
    bool doDamage(StageActor* collidingActor, DamageType::__type__ damageType) override;
    u32 vf8EC(u32, u32) override;
    void vf8F4() override;
    u8 vf8FC() override;
    u32 vf904(u32) override;
    void vf90C(u32, u32) override;
    bool hasStar() override;
    void vf91C() override;
    void vf924(PlayerBase*) override;
    void vf92C() override;
    u32 vf934() override;
    u32 vf93C() override;
    u32 vf944() override;
    u32 vf94C() override;
    u32 vf954() override;
    u32 vf95C() override;
    u32 vf964() override;
    u32 vf96C() override;
    u32 vf974() override;
    u32 vf97C() override;
    u32 vf984(bool) override;
    u32 vf98C() override;
    u32 vf994(bool) override;
    u32 vf99C(bool) override;
    u32 vf9A4() override;

    void vfA2C() override;
    void vfA34() override;
    void vfA3C() override;
    void vfA44() override;
};
