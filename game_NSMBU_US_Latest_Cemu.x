/* 0xEBC0000 is 0x2000000 in IDA/Ghidra/Cemu. For any offset >= 0xEBC0000, subtract 0xCBC0000 to get its value in IDA/Ghidra/Cemu. */
/* 0x10502200 is 0x10000000 in IDA/Ghidra/Cemu. For any offset >= 0x10502200, subtract 0x502200 to get its value in IDA/Ghidra/Cemu. */

SECTIONS {

/* Math */
sin__Ff = 0x2afdd40;
cos__Ff = 0x2afe528;
atan2__FfT1 = 0x2afe670;
fmod__FfT1 = 0x2afd97c;
pow__FfT1 = 0x2afdea8;
sqrt__Ff = 0x2afdccc;

/* new/delete */
__nw__FUi = 0x29f1594;
__nw__FUiPQ2_4sead4Heapi = 0x29f1858;
__nwa__FUi = 0x29f1630;
__nwa__FUiPQ2_4sead4Heapi = 0x29f18dc;
__dl__FPv = 0x29f1748;
__dla__FPv = 0x29f17d0;

/* GHS C++ FUNCTIONS */
__pure_virtual_called = 0x2afa554;
__deleted_virtual_called = 0x2afa5e8;
__vec_new = 0x2afa350;
__vec_delete = 0x2afa490;
__record_needed_destruction = 0x2afa52c;
__gh_float_printf = 0x2afaba8;
__gh_long_long_printf = 0x2afab84;
__ghs_strcmp = 0x2afa60c;
__gh_memclr32 = 0x2aff1e0;
vsnprintf = 0x2afbd54;

/* CAFE SDK STATIC */
ASM_VECDistance = 0x2af9b18;

/* CAFE SDK IMPORTS */
OSBlockSet = 0x2b049b0;

/* sead::IDisposer */
__ct__Q2_4sead9IDisposerFv = 0x2a0a2fc;
__dt__Q2_4sead9IDisposerFv = 0x2a0a384;

/* sead::Random */
getU32__Q2_4sead6RandomFv = 0x2a13780;

/* sead::GlobalRandom */
instance__Q2_4sead12GlobalRandom = 0x101e806c;

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

/* sead::TaskBase */
pauseCalcChild__Q2_4sead8TaskBaseFb = 0x2afa5e8;
pauseDrawChild__Q2_4sead8TaskBaseFb = 0x2afa5e8;
enterCommon__Q2_4sead8TaskBaseFv = 0x29ff818;
onDestroy__Q2_4sead8TaskBaseFv = 0x2afa5e8;

/* sead::CalculateTask */
__ct__Q2_4sead13CalculateTaskFRCQ2_4sead16TaskConstructArgPCc = 0x29fc508;
__dt__Q2_4sead13CalculateTaskFv = 0x29fc2f0;
checkDerivedRuntimeTypeInfo__Q2_4sead13CalculateTaskCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x29fc7d8;
pauseCalc__Q2_4sead13CalculateTaskFb = 0x29fc444;
pauseCalcRec__Q2_4sead13CalculateTaskFb = 0x2afa5e8;
pauseDrawRec__Q2_4sead13CalculateTaskFb = 0x2afa5e8;
attachCalcImpl__Q2_4sead13CalculateTaskFv = 0x29fc384;
detachCalcImpl__Q2_4sead13CalculateTaskFv = 0x29fc43c;
getCorrespondingMethodTreeMgrTypeInfo__Q2_4sead13CalculateTaskCFv = 0x2afa5e8;

/* sead::Endian */
cHostEndian__Q2_4sead6Endian = 0x105eaa78;
cConvFuncTable__Q2_4sead6Endian = 0x101929a8;

/* Profile */
__ct__7ProfileFPFPC14ActorBuildInfo_P9ActorBaseUiRCQ2_4sead23SafeStringBase__tm__2_cPC9ActorInfoT2 = 0x2019554;
get__7ProfileSFUi = 0x2019774;
spriteToProfileList__7Profile = 0x101ecd8c;
prioritiesOriginal__7Profile = 0x10001940;
hasResourcesOriginal__7Profile = 0x10002064;
resourceCountOriginal__7Profile = 0x100023f8;
profilesOriginal__7Profile = 0x101ed8dc;
resourceListsOriginal__7Profile = 0x101c321c;

/* ActorInfo */
Default__9ActorInfo = 0x100018f4;

/* ActorMgr */
instance__8ActorMgr = 0x101c30c8;
create__8ActorMgrFP14ActorBuildInfoUi = 0x2009a58;
createActor__8ActorMgrFP14ActorBuildInfoUi = 0x2009a58;
findActorByType__8ActorMgrFQ2_9ProfileId13ProfileIdTypePP9ActorBase = 0x2009b6c;

/* ActorList */
findById__9ActorListFPUi = 0x200a5c8;
findActorById__9ActorListFPUi = 0x200a5c8;

/* ActorMgr */
sInstance__8ActorMgr = 0x101c30c8;
create__8ActorMgrFP14ActorBuildInfoUi = 0x2009a58;

/* ActorBase */
__vtbl__9ActorBase = 0x100006c0;
__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__9ActorBaseSFv = 0x101e9cc4;
typeInfo__L0__getRuntimeTypeInfoStatic__9ActorBaseSFv = 0x101e9cc8;
removeChild__9ActorBaseFP9ActorBase = 0x2002c8c;
beforeCreate__9ActorBaseFv = 0x2002f7c;
onExecute__9ActorBaseFv = 0x2002f8c;
finalExecute__9ActorBaseFv = 0x2002f94;
onDraw__9ActorBaseFv = 0x2002fa0;
afterDraw__9ActorBaseFUi = 0x2002f38;
beforeDelete__9ActorBaseFv = 0x2002fa8;
onDelete__9ActorBaseFv = 0x2002fb0;
afterDelete__9ActorBaseFUi = 0x2002f3c;
getProfileId__9ActorBaseFv = 0x2002c80;

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
__vtbl__12PhysicsActor = 0x1000084c;
__ct__12PhysicsActorFPC14ActorBuildInfo = 0x2002fb8;
__dt__12PhysicsActorFv = 0x20040b0;
__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__12PhysicsActorSFv = 0x101e9cd4;
typeInfo__L0__getRuntimeTypeInfoStatic__12PhysicsActorSFv = 0x101e9cd8;
handleGravity__12PhysicsActorFv = 0x20039ac;
handleSpeed__12PhysicsActorFv = 0x2003ae4;
afterCreate__12PhysicsActorFUi = 0x200354c;
beforeExecute__12PhysicsActorFv = 0x20035fc;
afterExecute__12PhysicsActorFUi = 0x20036d8;
onDelete__12PhysicsActorFv = 0x2003724;
setPlayerId__12PhysicsActorFSc = 0x2003f10;
vf114__12PhysicsActorFv = 0x2afa5e8;
vf134__12PhysicsActorFv = 0x2afa5e8;
vf13C__12PhysicsActorFv = 0x2004008;
vf144__12PhysicsActorFb = 0x200375c;
vf14C__12PhysicsActorFP5Actor = 0x2003760;

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

/* Enemy */
StateID_DieFumi__5Enemy = 0x10200fb0;
__vtbl__5Enemy = 0x1007209c;
__ct__5EnemyFPC14ActorBuildInfo = 0x2328494;
collisionCallback__5EnemySFP14ActiveColliderT1 = 0x2328c50;
processCollision__5EnemyFP14ActiveColliderT1Ui = 0x2329b88;
killPlayerJump__5EnemyFP5ActorRC4Vec2P9StateBase = 0x232da34;
killPlayerSpin__5EnemyFP5Actor = 0x232cc98;
killYoshiStomp__5EnemyFP5Actor = 0x232d31c;
__dt__5EnemyFv = 0x232a868;
checkDerivedRuntimeTypeInfo__5EnemyCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x232a70c;
getRuntimeTypeInfo__5EnemyCFv = 0x2afa5e8;
beforeExecute__5EnemyFv = 0x2328644;
damageFromUnder__5EnemyFv = 0x2328914;
vf14C__5EnemyFP5Actor = 0x232dc88;
vf154__5EnemyFv = 0x232e1a4;
doStateChange__5EnemyFP9StateBase = 0x2330404;
vf18C__5EnemyFv = 0x232a848;
damagePlayer__5EnemyFP14ActiveColliderT1 = 0x2328b84;
vf19C__5EnemyFv = 0x232910c;
freeze__5EnemyFv = 0x23304f8;
vf1AC__5EnemyFv = 0x23310bc;
vf1B4__5EnemyFv = 0x23310c0;
vf1BC__5EnemyFv = 0x2330568;
vf1C4__5EnemyFv = 0x232a858;
vf1CC__5EnemyFv = 0x232a85c;
vf1D4__5EnemyFP14ActiveColliderT1 = 0x23291f8;
vf1DC__5EnemyFP14ActiveColliderT1 = 0x2329250;
vf1E4__5EnemyFRbP14ActiveColliderT2 = 0x2329520;
vf1EC__5EnemyFP14ActiveColliderT1 = 0x2329578;
vf1F4__5EnemyFP14ActiveColliderT1 = 0x232957c;
vf1FC__5EnemyFP14ActiveColliderT1 = 0x23296e8;
vf204__5EnemyFP14ActiveColliderT1 = 0x2329800;
collisionEnemy__5EnemyFP14ActiveColliderT1 = 0x23299f0;
collisionPlayer__5EnemyFP14ActiveColliderT1 = 0x23299f4;
collisionYoshi__5EnemyFP14ActiveColliderT1 = 0x2329a04;
vf224__5EnemyFP14ActiveColliderT1 = 0x2329a08;
collisionStar__5EnemyFP14ActiveColliderT1 = 0x232ce84;
collisionSlide__5EnemyFP14ActiveColliderT1 = 0x232cf20;
collisionPropellerDrill__5EnemyFP14ActiveColliderT1 = 0x232d014;
vf244__5EnemyFP14ActiveColliderT1 = 0x232d0e4;
collisionGroundPound__5EnemyFP14ActiveColliderT1 = 0x232d240;
collisionGroundPoundYoshi__5EnemyFP14ActiveColliderT1 = 0x232d3b4;
collisionPenguinSlide__5EnemyFP14ActiveColliderT1 = 0x232d48c;
collisionPipeCannon__5EnemyFP14ActiveColliderT1 = 0x232d49c;
vf26C__5EnemyFP14ActiveColliderT1 = 0x232d56c;
collisionThrowableObject__5EnemyFP14ActiveColliderT1 = 0x232d57c;
collisionFireball__5EnemyFP14ActiveColliderT1 = 0x232d70c;
collisionIceball__5EnemyFP14ActiveColliderT1 = 0x232d7a4;
collisionHammer__5EnemyFP14ActiveColliderT1 = 0x232d824;
collisionFireballYoshi__5EnemyFP14ActiveColliderT1 = 0x232d938;
vf29C__5EnemyFP14ActiveColliderT1 = 0x232da04;
vf2A4__5EnemyFP14ActiveColliderT1 = 0x232da0c;
vf2AC__5EnemyFP14ActiveColliderT1 = 0x232da14;
vf2B4__5EnemyFP14ActiveColliderT1 = 0x232da24;
vf2BC__5EnemyFv = 0x232daf0;
vf2C4__5EnemyFv = 0x232dd48;
vf2CC__5EnemyFv = 0x232e048;
isOnGround__5EnemyFv = 0x232e2ec;
vf2DC__5EnemyFv = 0x232e2f8;
vf2E4__5EnemyFv = 0x232e358;
vf2EC__5EnemyFv = 0x2329ea4;
vf2F4__5EnemyFv = 0x2329fa8;
vf2FC__5EnemyFv = 0x2329fac;
vf304__5EnemyFv = 0x2329fb0;
vf30C__5EnemyFv = 0x2329fc0;
vf314__5EnemyFv = 0x232a094;
vf31C__5EnemyFv = 0x232a118;
vf324__5EnemyFv = 0x232a1bc;
vf32C__5EnemyFv = 0x232a240;
vf334__5EnemyFv = 0x232a24c;
vf33C__5EnemyFv = 0x232a250;
vf344__5EnemyFv = 0x232a2d4;
vf34C__5EnemyFv = 0x232a2e4;
vf354__5EnemyFv = 0x232a2fc;
vf35C__5EnemyFv = 0x232a364;
vf364__5EnemyFv = 0x232a418;
vf36C__5EnemyFv = 0x232a4cc;
vf374__5EnemyFv = 0x232a864;
beginState_DieFumi__5EnemyFv = 0x232e518;
executeState_DieFumi__5EnemyFv = 0x232e5e8;
endState_DieFumi__5EnemyFv = 0x232eed0;
beginState_DieFall__5EnemyFv = 0x232e63c;
executeState_DieFall__5EnemyFv = 0x232e640;
endState_DieFall__5EnemyFv = 0x232eed4;
vf3AC__5EnemyFv = 0x232e72c;
vf3B4__5EnemyFv = 0x232e79c;
vf3BC__5EnemyFv = 0x232eed8;
vf3C4__5EnemyFv = 0x232e7a8;
vf3CC__5EnemyFv = 0x232e7b8;
vf3D4__5EnemyFv = 0x232eedc;
vf3DC__5EnemyFv = 0x232e7c4;
vf3E4__5EnemyFv = 0x232e7c8;
vf3EC__5EnemyFv = 0x232eee0;
vf3F4__5EnemyFv = 0x232e7d4;
vf3FC__5EnemyFv = 0x232eee4;
vf404__5EnemyFv = 0x232eee8;
vf40C__5EnemyFv = 0x232e7e0;
vf414__5EnemyFv = 0x232eeec;
vf41C__5EnemyFv = 0x232eef0;
vf424__5EnemyFv = 0x23305e4;
vf42C__5EnemyFv = 0x23305ec;
vf434__5EnemyFv = 0x23310c4;
vf43C__5EnemyFv = 0x23310c8;
vf444__5EnemyFv = 0x23310cc;
vf44C__5EnemyFv = 0x23310d0;
vf454__5EnemyFv = 0x23310d4;
vf45C__5EnemyFv = 0x23310d8;
vf464__5EnemyFv = 0x23310dc;
vf46C__5EnemyFv = 0x23306e8;
vf474__5EnemyFv = 0x23306f0;
vf47C__5EnemyFv = 0x23310e0;
vf484__5EnemyFv = 0x23310e4;
vf48C__5EnemyFv = 0x23310e8;
vf494__5EnemyFv = 0x23310ec;
vf49C__5EnemyFv = 0x23310f0;
vf4A4__5EnemyFv = 0x23310f4;
vf4AC__5EnemyFv = 0x23310f8;
vf4B4__5EnemyFv = 0x23310fc;
vf4BC__5EnemyFv = 0x2331100;
vf4C4__5EnemyFv = 0x2331104;
beginState_Ice__5EnemyFv = 0x2330720;
executeState_Ice__5EnemyFv = 0x23307a0;
endState_Ice__5EnemyFv = 0x2330944;

/* Boss */
__vtbl__4Boss = 0x1000562c;
__ct__4BossFP14ActorBuildInfo = 0x202b968;
checkDerivedRuntimeTypeInfo__4BossFPv = 0x202dab0;
__dt__4BossFv = 0x202e2e0;
onCreate__4BossFv = 0x202bb68;
beforeExecute__4BossFv = 0x202bd0c;
afterExecute__4BossFi = 0x202bddc;
onDelete__4BossFv = 0x202dc2c;
removeColliders__4BossFv = 0x202ddf0;
addColliders__4BossFv = 0x202de7c;
vf154__4BossFv = 0x202ce40;
freezeActor__4BossFv = 0x202ceac;
vf1BC__4BossFv = 0x202cf64;
vf1C4__4BossFv = 0x202e2d0;
playerCollision__4BossFUiP8Collider = 0x202bfdc;
yoshiCollision__4BossFUiP8Collider = 0x202c2b4;
vf22C__4BossFv = 0x202dcc8;
hitJump__4BossFP8ColliderT1 = 0x202dcd0;
collidesSomething__4BossFP8ColliderT1 = 0x202c5d0;
hitEnemyDown__4BossFP8ColliderT1 = 0x202dcd8;
hitGroundPound__4BossFP8ColliderT1 = 0x202c3ac;
hitEnemyKame2__4BossFP8ColliderT1 = 0x202c5e0;
hitEnemyKameDown__4BossFP8ColliderT1 = 0x202c8e0;
vf27C__4BossFv = 0x202c6d4;
vf284__4BossFP8ColliderT1 = 0x202cbcc;
hitEx__4BossFv = 0x202ccb0;
vf2C4__4BossFv = 0x202dce0;
isGrounded__4BossFv = 0x202ce00;
vf2F4__4BossFv = 0x202dd38;
beginState_JumpKill__4BossFv = 0x202dc9c;
executeState_JumpKill__4BossFv = 0x202dca0;
endState_JumpKill__4BossFv = 0x202dca4;
beginState_BossState1__4BossFv = 0x202becc;
executeState_BossState1__4BossFv = 0x202bedc;
endState_BossState1__4BossFv = 0x202beec;
beginState_BossState2__4BossFv = 0x202befc;
executeState_BossState2__4BossFv = 0x202bf0c;
endState_BossState2__4BossFv = 0x202bf1c;
beginState_BossState3__4BossFv = 0x202bf2c;
executeState_BossState3__4BossFv = 0x202bf3c;
endState_BossState3__4BossFv = 0x202bf4c;
beginState_BossState4__4BossFv = 0x202bf5c;
executeState_BossState4__4BossFv = 0x202bf6c;
endState_BossState4__4BossFv = 0x202bf7c;
beginState_BossState5__4BossFv = 0x202bf8c;
executeState_BossState5__4BossFv = 0x202bf9c;
endState_BossState5__4BossFv = 0x202bfac;
vf55C__4BossFv = 0x202dca8;
vf564__4BossFv = 0x202dcb4;
vf56C__4BossFv = 0x202dcc0;
vf574__4BossFv = 0x202bfbc;
vf57C__4BossFv = 0x202dcc4;
vf584__4BossFv = 0x2afa5e8;
vf58C__4BossFv = 0x202dd3c;
vf594__4BossFv = 0x202dd4c;
vf59C__4BossFv = 0x2afa5e8;
vf5A4__4BossFv = 0x2afa5e8;
vf5AC__4BossFv = 0x2afa5e8;
vf5B4__4BossFv = 0x202dd90;
vf5BC__4BossFUi = 0x202dd98;
vf604__4BossFv = 0x202ddbc;
vf60C__4BossFv = 0x202ddc0;
vf614__4BossFv = 0x202ddc4;
vf61C__4BossFv = 0x202ddc8;
vf624__4BossFv = 0x2afa5e8;
vf62C__4BossFv = 0x202ddd0;
vf634__4BossFP12PhysicsActor = 0x202ddd8;
vf63C__4BossFP12PhysicsActor = 0x202dde4;
vf644__4BossFv = 0x202d120;
vf64C__4BossFUi = 0x202d214;
vf654__4BossFv = 0x202df28;
changeState_JumpKill__4BossFv = 0x202df2c;
vf664__4BossFv = 0x202df44;
changeState_State1__4BossFv = 0x202df48;
vf674__4BossFv = 0x202df60;
vf67C__4BossFv = 0x202df70;
vf684__4BossFv = 0x2afa5e8;
vf68C__4BossFv = 0x2afa5e8;
vf694__4BossFv = 0x2afa5e8;
vf69C__4BossFv = 0x2afa5e8;
vf6A4__4BossFv = 0x202df80;
changeState_State5__4BossFv = 0x202df84;
vf6B4__4BossFv = 0x202df9c;
changeState_State3__4BossFv = 0x202dfa0;
vf6C4__4BossFv = 0x2afa5e8;
vf6CC__4BossFv = 0x2afa5e8;
vf6D4__4BossFv = 0x202dfb8;
vf6DC__4BossFv = 0x202dfc0;
vf6E4__4BossFv = 0x202dfc4;
vf6EC__4BossFv = 0x202dfd4;
vf6F4__4BossFv = 0x202dfdc;
vf6FC__4BossFv = 0x202dfe4;
vf704__4BossFv = 0x202dfec;
vf70C__4BossFv = 0x2afa5e8;
vf714__4BossFv = 0x2afa5e8;
vf71C__4BossFv = 0x2afa5e8;
vf724__4BossFv = 0x202dff4;
vf72C__4BossFv = 0x202dff8;
vf734__4BossFv = 0x202dffc;
vf73C__4BossFv = 0x2afa5e8;
vf744__4BossFv = 0x202e000;
stomp__4BossFv = 0x202e004;
lastStomp__4BossFv = 0x202e01c;
vf75C__4BossFv = 0x2afa5e8;
damageStar__4BossFv = 0x202e034;
vf76C__4BossFv = 0x2afa5e8;
damageLast__4BossFv = 0x202e04c;
damageFire__4BossFv = 0x202e064;
damageFireLast__4BossFv = 0x202e0d8;
damageFire2__4BossFv = 0x202e130;
damageFireLast2__4BossFv = 0x202e1a4;
damageStarDef__4BossFv = 0x202e1fc;
damageLast2__4BossFv = 0x202e214;
vf7AC__4BossFv = 0x202e22c;
vf7B4__4BossFv = 0x2afa5e8;
vf7BC__4BossFv = 0x2afa5e8;
vf7C4__4BossFv = 0x202e230;
vf7CC__4BossFv = 0x202d3bc;
initBossCollider__4BossFv = 0x202d3f4;
initModels__4BossFv = 0x202e2b8;
vf7E4__4BossFv = 0x202e2bc;
vf7EC__4BossFv = 0x202e2c0;
vf7F4__4BossFv = 0x202e2c4;
vf7FC__4BossFv = 0x202e2c8;

/* WindGeneratorBase */
__vtbl__13WindGenerator = 0x101560a8;
__dt__17WindGeneratorBaseFv = 0x288f044;
onCreate__17WindGeneratorBaseFv = 0x288ec68;
onExecute__17WindGeneratorBaseFv = 0x288ed94;

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

/* EnemyFreezeMgr */
freeze__14EnemyFreezeMgrFRCQ2_14EnemyFreezeMgr4InfoUi = 0x237d63c;
setFlags__14EnemyFreezeMgrFRCQ2_14EnemyFreezeMgr5Flags = 0x237cb94;

/* StateBase */
currentId__9StateBase = 0x101e9f04;
NullState__9StateBase = 0x1022d390;

/* StateMgr */
execute__8StateMgrFv = 0x29c4a80;
changeState__8StateMgrFP9StateBase = 0x29c4af0;

/* CollisionMgr */
instance__12CollisionMgr = 0x101c95d8;
addCollider__12CollisionMgrFP8Collider = 0x219e028;
__dt__12CollisionMgrFv = 0x218adfc;
init__12CollisionMgrFP5ActorPCQ2_12CollisionMgr6SensorN22 = 0x218af6c;
setSensor__12CollisionMgrFPCQ2_12CollisionMgr6SensorUi = 0x218aefc;
getSensor__12CollisionMgrCFUi = 0x218ce74;
process__12CollisionMgrFv = 0x218d954;

/* EventMgr */
instance__8EventMgr = 0x101db06c;
set__8EventMgrFUiT1bN41 = 0x269cd68;

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
updateAnimations__12ModelWrapperFv = 0x24d4d20;

/* Mtx34 */
rotateAndTranslate__5Mtx34FRC5Vec3uRC4Vec3 = 0x203c1c8;

/* Animation */
setRepeat__9AnimationFb = 0x24deed4;

/* SkeletalAnimation */
play__17SkeletalAnimationFP10ResArchiveRCQ2_4sead23SafeStringBase__tm__2_c = 0x24fdadc;

/* TextureAnimation */
play__16TextureAnimationFP10ResArchiveRCQ2_4sead23SafeStringBase__tm__2_c = 0x250b1ec;

/* DrawMgr */
instance__7DrawMgr = 0x101d2d88;
drawModel__7DrawMgrFP5Model = 0x24fab58;
drawModel__7DrawMgrFP12ModelWrapper = 0x24fac98;
drawTile__7DrawMgrFUsRC4Vec3RCUiT2 = 0x24fad28;

/* AreaRumbleMgr */
sInstance__13AreaRumbleMgr = 0x101d1660;

/* LightMask */
__ct__9LightMaskFv = 0x2815c9c;
init__9LightMaskFPQ2_4sead4HeapUi = 0x2815d20;
update__9LightMaskFv = 0x2815dcc;
draw__9LightMaskFv = 0x28160c8;

/* LightSource */
__ct__11LightSourceFv = 0x24e24bc;
__dt__11LightSourceFv = 0x24e2580;
update__11LightSourceFUiP4Vec3PfN23PQ2_4sead7Color4fN23 = 0x24e26bc;

/* LineFollower */
__ct__12LineFollowerFv = 0x200dc14;
init__12LineFollowerFv = 0x200df60;
start__12LineFollowerFb = 0x200e178;

/* MovementHandler */
__ct__15MovementHandlerFv = 0x2849c40;
link__15MovementHandlerFRC4Vec3UiUc = 0x284b6f4;
getMaskForMovementType__15MovementHandlerFUi = 0x284a37c;
execute__15MovementHandlerFv = 0x284b8c4;

/* Effect */
spawn__6EffectSFiP4Vec3P5Vec3uT2 = 0x22ab080;

/* EffectWrapper */
__ct__13EffectWrapperFv = 0x22ab868;
update__13EffectWrapperFiP4Vec3P5Vec3uT2 = 0x22ab52c;

/* SoundSystemBase */
getAudioFx__15SoundSystemBaseFv = 0x29b1aa4;

/* SoundSystem */
sInstance__11SoundSystem = 0x101e7c84;
getSoundArchive__11SoundSystemFv = 0x29b3ba8;

/* AudioFx */
getReverbHiParam__7AudioFxFv = 0x29b2fd8;
getDelayParam__7AudioFxFv = 0x29b2fe0;

/* Level */
instance__5Level = 0x101db048;
getArea__5LevelFUi = 0x269a2dc;
instance__10LevelTimer = 0x101d15f4;
addTime__10LevelTimerFi = 0x24c14c0;

/* Level::Area */
getSprite__Q2_5Level4AreaFUiPv = 0x2699c08;
getLocation__Q2_5Level4AreaFP4RectUc = 0x269a020;
getPath__Q2_5Level4AreaFUc = 0x269a0a8;
getPathNodes__Q2_5Level4AreaFUi = 0x269a0f4;

/* LevelInfo */
instance__9LevelInfo = 0x101d18ec;

/* nw::snd::SoundArchive */
GetItemLabel__Q3_2nw3snd12SoundArchiveCFUi = 0x2ad6980;

/* BasicSoundActor */
GlobalBasicSoundActorA = 0x101c63d0;
instance__15BasicSoundActor = 0x101c63d0;
playSound__15BasicSoundActorFPCcP4Vec2Ui = 0x29bedec;

/* Level */
sInstance__5Level = 0x101db048;
getArea__5LevelFUi = 0x269a2dc;

/* Level::Area */
getSprite__Q2_5Level4AreaFUiPv = 0x2699c08;
getLocation__Q2_5Level4AreaFP4RectUc = 0x269a020;
getPath__Q2_5Level4AreaFUc = 0x269a0a8;
getPathNodes__Q2_5Level4AreaFUi = 0x269a0f4;

/* LevelInfo */
sInstance__9LevelInfo = 0x101d18ec;

/* LevelCamera */
sInstance__11LevelCamera = 0x101e7c54;

/* LevelTimer */
sInstance__10LevelTimer = 0x101d15f4;
setTime__10LevelTimerFi = 0x24c134c;
addTime__10LevelTimerFi = 0x24c14c0;

/* TileMgr */
instance__7TileMgr = 0x101dab94;
getTilePtrCurrentArea__7TileMgrSFUsT1UcPUi = 0x2685000;

/* PlayerMgr */
instance__9PlayerMgr = 0x101e6994;

/* RDashMgr */
sInstance__8RDashMgr = 0x101e7d9c;

/* CourseTask */
sInstance__10CourseTask = 0x101d15f0;

/* TaskMgr */
sInstance__7TaskMgr = 0x101e7b28;
startLevel__7TaskMgrFPQ2_4sead8TaskBaseUcT2 = 0x29941d0;
changeTask__7TaskMgrFPQ2_4sead8TaskBaseRQ2_4sead11TaskClassIDUiT3 = 0x2994164;

/* TwoWayPlatform */
cbCallback4__14TwoWayPlatformSFP5Actor = 0x283fbac;
cbCallback5__14TwoWayPlatformSFP5Actor = 0x283fbe0;
cbCallback6__14TwoWayPlatformSFP5ActorUiT2 = 0x283fc14;
twoWayPlatformCbCallback2__14TwoWayPlatformFP12ColliderBaseP4Vec2 = 0x284184c;

/* ResMgr */
ResMgr_LoadLevelResource = 0x29d2a20;
ResMgr_LoadLevelArchiveSuccess = 0x29d3354;
ResMgr_LoadLevelArchiveFail = 0x29d333c;

/* RDashMgr */
instance__8RDashMgr = 0x101e7d9c;

/* TODO: THIS CRASHES Input
instance__8InputMgr = 0x101d2df8;
getTilt__10ControllerFPUif = 0xF0CED50; */

/* TerrainEffects */
__CPR79__init__14TerrainEffectsFP4Vec3fbT3Q2_J6J11TerrainTypePQ2_4sead4Heap = 0x28b7378;
setWaveValues__14TerrainEffectsFUiN51 = 0x28b7598;
checkMarioWaveHit__14TerrainEffectsFv = 0x28b8c98;
updateWaveCollisions__14TerrainEffectsFv = 0x28b8e00;

/* EnvTerrain */
onExecute__10EnvTerrainFv = 0x26f0f40;
setTop__10EnvTerrainFf = 0x26f131c;

/* Misc */
mapPositionToScreen__FR4Vec2RC4Vec2 = 0x2029368;
mapPosToScreen__FP4Vec2T1 = 0x2029368;
moveValueTo__FPUiUiT2 = 0x29e11f0;
moveFloatTo__FPffT2 = 0x2027984;
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
directionToRotationList = 0x10200dd8;
formatBufferedString = 0x2a0f308;
setBufferedStringMaybe = 0x29d4240;
nullterminator = 0x1018a56d;

}
