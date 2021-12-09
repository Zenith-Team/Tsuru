#pragma once

namespace ProfileID {

// Remember to add your new profile to the profile array in profile.cpp as well as the end of the list below
enum ProfileIDType {
    BossCannon = 262,
    BuzzyBeetle = 381,
    BigBuzzyBeetle = 382,
    StarCoin = 426,
    Goomba = 467,
    ParaGoomba = 469,
    PricklyGoomba = 470,
    MiniGoomba = 471,
    MediumGoomba = 472,
    BigGoomba = 473,
    PlayerIceBall = 474,
    PiranhaPlantIceBall = 475,
    PlayerFireball = 476,
    PiranhaPlantFireball = 477,
    YoshiFireball = 478,
    KoopaTroopa = 512,
    BigKoopa = 514,
    ParaKoopa = 515,
    GroupParaKoopa = 516,
    Spiny = 517,
    UpsideDownSpiny = 518,
    Mechakoopa = 524,
    SpinyCheepCheep = 539,
    Thwomp = 635,
    DryBonesHead = 647,
    DryBones = 648,
    BigDryBones = 649,
    Poltergeist = 670,
    KoopalingMagic = 694,
    BowserFireballSpawner = 716,
    BowserFireball = 717,
    FinalBowserFireball = 724,
    FinalBowserJrFireball = 726,
    FireBroFireball = 762,
    Star = 853,
    CSW2Goomba = 898,
    CSW9StarGate = 908,

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
    Kamiya,
    KamiyaMagic,

    // Atlys profiles
    AtlysCamera,
    AtlysPlayer,

    Num
};

}
