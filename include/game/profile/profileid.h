#pragma once

namespace ProfileID {

// Remember to add your new profile to the profile array in profile.cpp as well as the end of the list below
enum ProfileIDType {
    NumOriginal = 913,

    // Start of custom entries
    ActorSpawner = NumOriginal,
    ParaBones,
    CustomDoor,
    FakeActor,
    PAcorn,
    StarCoinShard,
    BeepBlock,
    FallingChestnut,
    TaskChanger,
    Cataquack,
    TimeClock,
    EffectSpawner,
    AngrySun,
    AngryMoon,
    RainbowLight,
    WavePlatform,
    DebugActor,
    LiquidOverlay,
    PhysicsModifier,

    // Atlys profiles
    AtlysCamera,
    AtlysPlayer,

    Num
};

}
