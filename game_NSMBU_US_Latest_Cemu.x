/* 0xEBC0000 is 0x2000000 in IDA/Ghidra/Cemu. For any offset >= 0xEBC0000, subtract 0xCBC0000 to get its value in IDA/Ghidra/Cemu. */
/* 0x10502200 is 0x10000000 in IDA/Ghidra/Cemu. For any offset >= 0x10502200, subtract 0x502200 to get its value in IDA/Ghidra/Cemu. */

SECTIONS {

/* Math */
sin__Ff = 0x2afdd40;
cos__Ff = 0x2afe528;

/* new/delete */
__nw__FUi = 0x29f1594;
__nwa__FUi = 0x29f1630;
__nwa__FUiPQ2_4sead4Heapi = 0x29f18dc;
__dl__FPv = 0x29f1748;
__dla__FPv = 0x29f17d0;

/* GHS C++ FUNCTIONS */
__pure_virtual_called = 0x2afa554;
__deleted_virtual_called = 0x2afa5e8;
__vec_new = 0x2afa350;

/* sead::IDisposer */
__ct__Q2_4sead9IDisposerFv = 0x2a0a2fc;
__dt__Q2_4sead9IDisposerFv = 0x2a0a384;

/* sead::HeapMgr */
sInstancePtr__Q2_4sead7HeapMgr = 0x101e8040;
getCurrentHeap__Q2_4sead7HeapMgrFv = 0x2a0d554;

/* sead::FileDevice */
__CPR122__tryOpen__Q2_4sead10FileDeviceFPQ2_J12J10FileHandleRCQ2_J12J23SafeStringBase__tm__2_cQ3_J12JJ17J12FileOpenFlagUi = 0x29f7804;
tryClose__Q2_4sead10FileDeviceFPQ2_4sead10FileHandle = 0x29f78c0;

/* sead::FileDeviceMgr */
sInstance__Q2_4sead13FileDeviceMgr = 0x101e7f18;
tryOpen__Q2_4sead13FileDeviceMgrFPQ2_4sead10FileHandleRCQ2_4sead23SafeStringBase__tm__2_cQ3_4sead10FileDevice12FileOpenFlagUi = 0x29f8b0c;

/* sead::FileHandle */
read__Q2_4sead10FileHandleFPUcUi = 0x29f81d0;

/* sead::SZSDecompressor */
getDecompSize__Q2_4sead15SZSDecompressorSFPCv = 0x2a154cc;
getDecompAlignment__Q2_4sead15SZSDecompressorSFPCv = 0x2a15aa0;
decomp__Q2_4sead15SZSDecompressorSFPvUiPCvT2 = 0x2a15654;
__CPR87__streamDecomp__Q2_4sead15SZSDecompressorSFPQ3_J17JJ22J13DecompContextPCvUi = 0x2a157fc;

/* sead::SZSDecompressor::DecompContext */
__ct__Q3_4sead15SZSDecompressor13DecompContextFPv = 0x2a15af4;

/* sead::DirectResource */
__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead14DirectResourceSFv = 0x101e9bb8;
typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead14DirectResourceSFv = 0x101e9f18;

/* sead::Endian */
cHostEndian__Q2_4sead6Endian = 0x105eaa78;
cConvFuncTable__Q2_4sead6Endian = 0x101929a8;

/* Profile */
__ct__7ProfileFPFPC14ActorBuildInfo_P4BaseUiRCQ2_4sead23SafeStringBase__tm__2_cPC9ActorInfoT2 = 0x2019554;
get__7ProfileSFUi = 0x2019774;
spriteToProfileList__7Profile = 0x101ecd8c;
hasResourcesOriginal__7Profile = 0x10002064;
resourceCountOriginal__7Profile = 0x100023f8;
resourceListsOriginal__7Profile = 0x101c321c;

/* ActorMgr */
instance__8ActorMgr = 0x101c30c8;
create__8ActorMgrFP14ActorBuildInfoUi = 0x2009a58;

/* Base */
__vtbl__4Base = 0x100006c0;
__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__4BaseSFv = 0x101e9cc4;
typeInfo__L0__getRuntimeTypeInfoStatic__4BaseSFv = 0x101e9cc8;
beforeCreate__4BaseFv = 0x2002f7c;
onExecute__4BaseFv = 0x2002f8c;
finalExecute__4BaseFv = 0x2002f94;
onDraw__4BaseFv = 0x2002fa0;
afterDraw__4BaseFUi = 0x2002f38;
beforeDelete__4BaseFv = 0x2002fa8;
onDelete__4BaseFv = 0x2002fb0;
afterDelete__4BaseFUi = 0x2002f3c;

/* Actor */
__vtbl__5Actor = 0x10000268;
__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__5ActorSFv = 0x101e9cbc;
typeInfo__L0__getRuntimeTypeInfoStatic__5ActorSFv = 0x101e9cc0;
__ct__5ActorFPC14ActorBuildInfo = 0x2000ac8;
directionToPlayerH__5ActorFRC4Vec3 = 0x20005ec;
directionToActorH__5ActorFRC5Actor = 0x200c800;
distanceToPlayer__5ActorFR4Vec2 = 0x20005a4;
deleteActorWhenOutOfView__5ActorFUi = 0x20007a0;
actorAcCallback0__5ActorFP14ActiveColliderP4Vec2 = 0x219e7e8;
actorAcCallback2__5ActorFP14ActiveColliderP4Vec2 = 0x219e8a4;
actorCbCallback0__5ActorFP12ColliderBaseP4Vec2 = 0x219e8b8;
checkDerivedRuntimeTypeInfo__5ActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x2002a38;
getRuntimeTypeInfo__5ActorCFv = 0x2afa5e8;
__dt__5ActorFv = 0x2000f18;
afterCreate__5ActorFUi = 0x2000fb8;
beforeExecute__5ActorFv = 0x2000fe8;
afterExecute__5ActorFUi = 0x20010bc;
beforeDraw__5ActorFv = 0x20011a0;
removeActiveColliders__5ActorFv = 0x20002cc;
addActiveColliders__5ActorFv = 0x2000328;
killAtGoal__5ActorFv = 0x2002ad8;
splashWater__5ActorFP4Vec3 = 0x2002adc;
splashLava__5ActorFP4Vec3 = 0x2002ae0;
splashLavaWave__5ActorFP4Vec3 = 0x2000960;
splashPoison__5ActorFP4Vec3 = 0x2002ae4;
isOffScreen__5ActorFv = 0x2001254;

/* StageActor */
__vtbl__10StageActor = 0x1000084c;
__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x101e9cd4;
typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x101e9cd8;
handleGravity__10StageActorFv = 0x20039ac;
handleSpeed__10StageActorFv = 0x2003ae4;
afterCreate__10StageActorFUi = 0x200354c;
beforeExecute__10StageActorFv = 0x20035fc;
afterExecute__10StageActorFUi = 0x20036d8;
onDelete__10StageActorFv = 0x2003724;
vf114__10StageActorFv = 0x2afa5e8;
vf134__10StageActorFv = 0x2afa5e8;
vf13C__10StageActorFv = 0x2004008;
vf144__10StageActorFb = 0x200375c;
vf14C__10StageActorFP5Actor = 0x2003760;

/* ActorMultiState */
__vtbl__15ActorMultiState = 0x10001048;
__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__15ActorMultiStateSFv = 0x101e9ce4;
typeInfo__L0__getRuntimeTypeInfoStatic__15ActorMultiStateSFv = 0x101e9ce8;
__ct__15ActorMultiStateFPC14ActorBuildInfo = 0x200aa8c;
checkDerivedRuntimeTypeInfo__15ActorMultiStateCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x200af94;

/* BlockCoinBase */
__vtbl__13BlockCoinBase = 0x10101a80;
StateID_BlockCoinState3__13BlockCoinBase = 0x10220564;
StateID_BumpUp2__13BlockCoinBase = 0x1022051c;
checkDerivedRuntimeTypeInfo__13BlockCoinBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x2708dc0;
vf18C__13BlockCoinBaseFv = 0x2708efc;
vf194__13BlockCoinBaseFv = 0x2708f00;
setBelowSensor__13BlockCoinBaseFv = 0x2708f04;
vf1A4__13BlockCoinBaseFv = 0x2708f08;
spawnItemUp__13BlockCoinBaseFv = 0x2708f0c;
vf1B4__13BlockCoinBaseFv = 0x2708f10;
vf1BC__13BlockCoinBaseFv = 0x2708f14;
spawnItemDown__13BlockCoinBaseFv = 0x2708f18;
vf1CC__13BlockCoinBaseFv = 0x2708f1c;
vf1D4__13BlockCoinBaseFb = 0x2704868;
vf1DC__13BlockCoinBaseFv = 0x2708f20;
spawnCoinShower__13BlockCoinBaseFv = 0x27048e4;
vf1EC__13BlockCoinBaseFv = 0x2708f28;
beginState_BumpUp__13BlockCoinBaseFv = 0x2707cb4;
executeState_BumpUp__13BlockCoinBaseFv = 0x2707cf0;
endState_BumpUp__13BlockCoinBaseFv = 0x2708f2c;
beginState_BlockCoinState1__13BlockCoinBaseFv = 0x2707d94;
executeState_BlockCoinState1__13BlockCoinBaseFv = 0x2707da0;
endState_BlockCoinState1__13BlockCoinBaseFv = 0x2708f30;
beginState_BumpDown__13BlockCoinBaseFv = 0x2707db8;
executeState_BumpDown__13BlockCoinBaseFv = 0x2707dfc;
endState_BumpDown__13BlockCoinBaseFv = 0x2708f34;
beginState_BlockCoinState2__13BlockCoinBaseFv = 0x2707e9c;
executeState_BlockCoinState2__13BlockCoinBaseFv = 0x2707ea8;
endState_BlockCoinState2__13BlockCoinBaseFv = 0x2708f38;
beginState_BumpUp2__13BlockCoinBaseFv = 0x2707ed0;
executeState_BumpUp2__13BlockCoinBaseFv = 0x2707f58;
endState_BumpUp2__13BlockCoinBaseFv = 0x2708f3c;
beginState_BumpDown2__13BlockCoinBaseFv = 0x270812c;
executeState_BumpDown2__13BlockCoinBaseFv = 0x2708198;
endState_BumpDown2__13BlockCoinBaseFv = 0x2708f40;
beginState_BlockCoinState3__13BlockCoinBaseFv = 0x270828c;
executeState_BlockCoinState3__13BlockCoinBaseFv = 0x2708298;
endState_BlockCoinState3__13BlockCoinBaseFv = 0x2708f44;
spawnPortableSpring__13BlockCoinBaseFv = 0x2706430;
spawnVine__13BlockCoinBaseFv = 0x27062a8;
spawnYoshiEgg__13BlockCoinBaseFb = 0x2706ba4;
spawnPowerup__13BlockCoinBaseFP4Vec3UiT2b = 0x2706d1c;
spawnMultiPowerup__13BlockCoinBaseFP4Vec3UiT2b = 0x2706ff4;

/* MovementBlockCoinBase */
__vtbl__21MovementBlockCoinBase = 0x101075ac;
checkDerivedRuntimeTypeInfo__21MovementBlockCoinBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x2727a08;
spawnItemUp__21MovementBlockCoinBaseFv = 0x2726610;
spawnItemDown__21MovementBlockCoinBaseFv = 0x2726634;
vf1DC__21MovementBlockCoinBaseFv = 0x2726644;
vf1EC__13BlockCoinBaseFv = 0x2727980;
vf29C__21MovementBlockCoinBaseFv = 0x2727984;
setTileFlag__21MovementBlockCoinBaseFv = 0x27265bc;
vf2AC__21MovementBlockCoinBaseFv = 0x2727988;
vf2B4__21MovementBlockCoinBaseFv = 0x2727990;
vf2BC__21MovementBlockCoinBaseFv = 0x2727994;
vf2C4__21MovementBlockCoinBaseFv = 0x2727998;
vf2CC__21MovementBlockCoinBaseFv = 0x2726654;
registerColliderActiveInfo__21MovementBlockCoinBaseFv = 0x2726760;

/* BlockBase */
StateID_Wait__9BlockBase = 0x1021e8e0;
StateID_Used__9BlockBase = 0x1021e904;
activeTopCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0x2704ecc;
activeBottomCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0x2705528;
activeSideCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0x2705efc;
usedTopCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0x27050f0;
usedBottomCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0x270595c;
usedSideCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0x27060c0;
init__9BlockBaseFbT1 = 0x269f6c8;
initMover__9BlockBaseFv = 0x269fb30;
__vtbl__9BlockBase = 0x100e6960;
__ct__9BlockBaseFPC14ActorBuildInfo = 0x269e614;
__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__9BlockBaseSFv = 0x101e9cf4;
typeInfo__L0__getRuntimeTypeInfoStatic__9BlockBaseSFv = 0x101e9cf8;
checkDerivedRuntimeTypeInfo__9BlockBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x26a0460;
getRuntimeTypeInfo__9BlockBaseCFv = 0x2afa5e8;
onExecute__9BlockBaseFv = 0x269e6c4;
onDraw__9BlockBaseFv = 0x269e77c;
setBelowSensor__9BlockBaseFv = 0x269f400;
spawnItemUp__9BlockBaseFv = 0x269ebc0;
spawnItemDown__9BlockBaseFv = 0x269ebc4;
vf1CC__9BlockBaseFv = 0x269ec04;
vf1EC__9BlockBaseFv = 0x269f674;
vf2C4__9BlockBaseFv = 0x269f410;
isActive__9BlockBaseFv = 0x269ec1c;
vf2DC__9BlockBaseFv = 0x26a0404;
getContent__9BlockBaseFv = 0x26a0408;
vf2EC__9BlockBaseFv = 0x269efe4;
vf2F4__9BlockBaseFPv = 0x26a0418;
execute__9BlockBaseFv = 0x269f078;
destroy__9BlockBaseFv = 0x269f25c;
destroy2__9BlockBaseFv = 0x269f33c;
vf314__9BlockBaseFv = 0x26a0434;
vf31C__9BlockBaseFv = 0x26a0438;
vf324__9BlockBaseFv = 0x26a043c;
vf32C__9BlockBaseFv = 0x26a0440;
beginState_Wait__9BlockBaseFv = 0x26a061c;
executeState_Wait__9BlockBaseFv = 0x26a0068;
endState_Wait__9BlockBaseFv = 0x26a0620;
beginState_Used__9BlockBaseFv = 0x26a0624;
executeState_Used__9BlockBaseFv = 0x26a0074;
endState_Used__9BlockBaseFv = 0x26a0628;

/* ActiveCollider */
__ct__14ActiveColliderFv = 0x219a960;
__dt__14ActiveColliderFv = 0x219ab90;
__CPR59__init__14ActiveColliderFP5ActorPCQ2_J6J4InfoPPv = 0x219af1c;
Default__Q2_14ActiveCollider4Info = 0x10041bc0;

/* ColliderBase */
setType__12ColliderBaseFQ2_12ColliderBase5Types = 0x21a5a70;
__CPR62__setSurfaceType__12ColliderBaseFQ2_J16J12SurfaceTypes = 0x21a5ad0;

/* ColliderBase::Node */
__ct__Q2_12ColliderBase4NodeFv = 0x21a1acc;
__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__12ColliderBaseSFv = 0x101e9d2c;
typeInfo__L0__getRuntimeTypeInfoStatic__12ColliderBaseSFv = 0x101e9fa4;

/* ShapedCollider */
__ct__14ShapedColliderFiP4Vec2PQ2_12ColliderBase4NodeT3 = 0x21a7904;
init__14ShapedColliderFP5ActorRCQ2_14ShapedCollider4Info = 0x21ad3bc;
execute__14ShapedColliderFv = 0x21a871c;
__dt__14ShapedColliderFv = 0x21a7a04;
setRect__14ShapedColliderFP4Vec2T1 = 0x21ad25c;
__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__14ShapedColliderSFv = 0x101e9d30;
typeInfo__L0__getRuntimeTypeInfoStatic__14ShapedColliderSFv = 0x101e9fb4;

/* RectCollider */
__vtbl__12RectCollider = 0x100fb820;

/* SolidOnTopCollider */
__ct__18SolidOnTopColliderFv = 0x21a1d38;
__CPR79__init__18SolidOnTopColliderFP5ActorRCQ2_J6J4InfoiPQ2_4sead4Heap = 0x21a2378;
execute__18SolidOnTopColliderFv = 0x21a2e0c;
__dt__18SolidOnTopColliderFv = 0x21a1f18;
__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__18SolidOnTopColliderSFv = 0x101e9d48;
typeInfo__L0__getRuntimeTypeInfoStatic__18SolidOnTopColliderSFv = 0x101e9fa8;

/* ColliderMgr */
instance__11ColliderMgr = 0x101c9360;
add__11ColliderMgrFP12ColliderBase = 0x219269c;
remove__11ColliderMgrFP12ColliderBase = 0x219282c;

/* StateBase */
currentId__9StateBase = 0x101e9f04;
NullState__9StateBase = 0x1022d390;

/* StateMgr */
execute__8StateMgrFv = 0x29c4a80;
changeState__8StateMgrFP9StateBase = 0x29c4af0;

/* CollisionMgr */
__dt__12CollisionMgrFv = 0x218adfc;
init__12CollisionMgrFP5ActorPCQ2_12CollisionMgr6SensorN22 = 0x218af6c;
setSensor__12CollisionMgrFPCQ2_12CollisionMgr6SensorUi = 0x218aefc;
getSensor__12CollisionMgrCFUi = 0x218ce74;
process__12CollisionMgrFv = 0x218d954;

/* EventMgr */
instance__8EventMgr = 0x101db06c;

/* MusicPlayer */
shouldHurryUp__11MusicPlayerFv = 0x29b83d8;

/* ResArchive */
getModel__10ResArchiveFRCQ2_4sead23SafeStringBase__tm__2_cUiN42bPQ2_4sead4Heap = 0x24ee440;

/* ResArchiveMgr */
instance__13ResArchiveMgr = 0x101d2d50;
get__13ResArchiveMgrFRCQ2_4sead23SafeStringBase__tm__2_c = 0x24f60ec;

/* ModelWrapper */
__ct__12ModelWrapperFP5ModelUiN42 = 0x24d4798;
setup__12ModelWrapperFP10ResArchivePvPQ2_4sead4Heap = 0x24d49a0;
updateModel__12ModelWrapperFv = 0x24d4e84;

/* Mtx34 */
rotateAndTranslate__5Mtx34FRC5Vec3uRC4Vec3 = 0x203c1c8;

/* DrawMgr */
instance__7DrawMgr = 0x101d2d88;
drawModel__7DrawMgrFP5Model = 0x24fab58;
drawModel__7DrawMgrFP12ModelWrapper = 0x24fac98;
drawTile__7DrawMgrFUsRC4Vec3RCUiT2 = 0x24fad28;

/* MovementHandler */
__ct__15MovementHandlerFv = 0x2849c40;
link__15MovementHandlerFRC4Vec3UiUc = 0x284b6f4;
getMaskForMovementType__15MovementHandlerFUi = 0x284a37c;
execute__15MovementHandlerFv = 0x284b8c4;

/* SoundSystemBase */
getAudioFx__15SoundSystemBaseFv = 0x29b1aa4;

/* SoundSystem */
instance__11SoundSystem = 0x101e7c84;

/* AudioFx */
getReverbHiParam__7AudioFxFv = 0x29b2fd8;
getDelayParam__7AudioFxFv = 0x29b2fe0;

/* Level */
instance__5Level = 0x101db048;
getArea__5LevelFUi = 0x269a2dc;

/* Level::Area */
getSprite__Q2_5Level4AreaFUiPv = 0x2699c08;
getLocation__Q2_5Level4AreaFP4RectUc = 0x269a020;
getPath__Q2_5Level4AreaFUc = 0x269a0a8;
getPathNodes__Q2_5Level4AreaFUi = 0x269a0f4;

/* LevelInfo */
instance__9LevelInfo = 0x101d18ec;

/* TileMgr */
getTilePtrCurrentArea__7TileMgrSFUsT1UcPUi = 0x2685000;

/* PlayerMgr */
instance__9PlayerMgr = 0x101e6994;

/* TwoWayPlatform */
cbCallback4__14TwoWayPlatformSFP5Actor = 0x283fbac;
cbCallback5__14TwoWayPlatformSFP5Actor = 0x283fbe0;
cbCallback6__14TwoWayPlatformSFP5ActorUiT2 = 0x283fc14;
twoWayPlatformCbCallback2__14TwoWayPlatformFP12ColliderBaseP4Vec2 = 0x284184c;

/* Misc */
BLOSDynLoad_Acquire = 0x2a9ef58;
BOSDynLoad_FindExport = 0x2a9f418;
PlayerJumpArc = 0x1016a800;
MiniPlayerJumpArc = 0x1016a848;
PlayerJumpMax = 0x10166e68;
PlayerDescentRate = 0x10166e74;
DefaultReverbHiParam = 0x1022d328;
DefaultDelayParam = 0x1022d354;
SFXReverb_0 = 0x101e7d14;
SFXReverb_1 = 0x101e7d18;
SFXReverbPlyJump_0 = 0x101e7d1c;
SFXReverbPlyJump_1 = 0x101e7d20;

}
