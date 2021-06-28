/* 0xEBC0000 is 0x2000000 in IDA/Ghidra/Cemu. For any offset >= 0xEBC0000, subtract 0xCBC0000 to get its value in IDA/Ghidra/Cemu. */
/* 0x10502200 is 0x10000000 in IDA/Ghidra/Cemu. For any offset >= 0x10502200, subtract 0x502200 to get its value in IDA/Ghidra/Cemu. */

SECTIONS {

	/* Math */
	sin__Ff = 0xF6BDD40;
	cos__Ff = 0xF6BE528;
	atan2__FfT1 = 0xF6BE670;
	fmod__FfT1 = 0xF6BD97C;
	pow__FfT1 = 0xF6BDEA8;
	sqrt__Ff = 0xF6BDCCC;

	/* new/delete */
	__nw__FUi = 0xF5B1594;
	__nw__FUiPQ2_4sead4Heapi = 0xF5B1858;
	__nwa__FUi = 0xF5B1630;
	__nwa__FUiPQ2_4sead4Heapi = 0xF5B18DC;
	__dl__FPv = 0xF5B1748;
	__dla__FPv = 0xF5B17D0;

	/* GHS C++ FUNCTIONS */
	__pure_virtual_called = 0xF6BA554;
	__deleted_virtual_called = 0xF6BA5E8;
	__vec_new = 0xF6BA350;
	__vec_delete = 0xF6BA490;
	__record_needed_destruction = 0xF6BA52C;
	__gh_float_printf = 0xF6BABA8;
	__gh_long_long_printf = 0xF6BAB84;
	__ghs_strcmp = 0xF6BA60C;
	__gh_memclr32 = 0xF6BF1E0;
	vsnprintf = 0xF6BBD54;

	/* CAFE SDK STATIC */
	ASM_VECDistance = 0xF6B9B18;

	/* CAFE SDK IMPORTS */
	OSBlockSet = 0xF6C49B0;

	/* sead::IDisposer */
	__ct__Q2_4sead9IDisposerFv = 0xF5CA2FC;
	__dt__Q2_4sead9IDisposerFv = 0xF5CA384;

	/* sead::PrimitiveRenderer */
	instance__Q2_4sead17PrimitiveRenderer = 0x106EA210;
	setCamera__Q2_4sead17PrimitiveRendererFRCQ2_4sead6Camera = 0xF5C83D0;
	setProjection__Q2_4sead17PrimitiveRendererFRCQ2_4sead10Projection = 0xF5C83E4;
	begin__Q2_4sead17PrimitiveRendererFv = 0xF5C8408;
	end__Q2_4sead17PrimitiveRendererFv = 0xF5C841C;

	/* sead::Random */
	getU32__Q2_4sead6RandomFv = 0xF5D3780;

	/* sead::GlobalRandom */
	instance__Q2_4sead12GlobalRandom = 0x106EA26C;

	/* sead::HeapMgr */
	sInstancePtr__Q2_4sead7HeapMgr = 0x106EA240;
	getCurrentHeap__Q2_4sead7HeapMgrFv = 0xF5CD554;

	/* sead::FileDevice */
	__CPR122__tryOpen__Q2_4sead10FileDeviceFPQ2_J12J10FileHandleRCQ2_J12J23SafeStringBase__tm__2_cQ3_J12JJ17J12FileOpenFlagUi = 0xF5B7804;
	tryClose__Q2_4sead10FileDeviceFPQ2_4sead10FileHandle = 0xF5B78C0;

	/* sead::FileDeviceMgr */
	sInstance__Q2_4sead13FileDeviceMgr = 0x106EA118;
	tryOpen__Q2_4sead13FileDeviceMgrFPQ2_4sead10FileHandleRCQ2_4sead23SafeStringBase__tm__2_cQ3_4sead10FileDevice12FileOpenFlagUi = 0xF5B8B0C;

	/* sead::FileHandle */
	read__Q2_4sead10FileHandleFPUcUi = 0xF5B81D0;

	/* sead::SZSDecompressor */
	getDecompSize__Q2_4sead15SZSDecompressorSFPCv = 0xF5D54CC;
	getDecompAlignment__Q2_4sead15SZSDecompressorSFPCv = 0xF5D5AA0;
	decomp__Q2_4sead15SZSDecompressorSFPvUiPCvT2 = 0xF5D5654;
	__CPR87__streamDecomp__Q2_4sead15SZSDecompressorSFPQ3_J17JJ22J13DecompContextPCvUi = 0xF5D57FC;

	/* sead::SZSDecompressor::DecompContext */
	__ct__Q3_4sead15SZSDecompressor13DecompContextFPv = 0xF5D5AF4;

	/* sead::DirectResource */
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead14DirectResourceSFv = 0x106EBDB8;
	typeInfo__L0__getRuntimeTypeInfoStatic__Q2_4sead14DirectResourceSFv = 0x106EC118;

	/* sead::TaskBase */
	pauseCalcChild__Q2_4sead8TaskBaseFb = __deleted_virtual_called;
	pauseDrawChild__Q2_4sead8TaskBaseFb = __deleted_virtual_called;
	enterCommon__Q2_4sead8TaskBaseFv = 0xF5BF818;
	onDestroy__Q2_4sead8TaskBaseFv = __deleted_virtual_called;

	/* sead::CalculateTask */
	__ct__Q2_4sead13CalculateTaskFRCQ2_4sead16TaskConstructArgPCc = 0xF5BC508;
	__dt__Q2_4sead13CalculateTaskFv = 0xF5BC2F0;
	checkDerivedRuntimeTypeInfo__Q2_4sead13CalculateTaskCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xF5BC7D8;
	pauseCalc__Q2_4sead13CalculateTaskFb = 0xF5BC444;
	pauseCalcRec__Q2_4sead13CalculateTaskFb = __deleted_virtual_called;
	pauseDrawRec__Q2_4sead13CalculateTaskFb = __deleted_virtual_called;
	attachCalcImpl__Q2_4sead13CalculateTaskFv = 0xF5BC384;
	detachCalcImpl__Q2_4sead13CalculateTaskFv = 0xF5BC43C;
	getCorrespondingMethodTreeMgrTypeInfo__Q2_4sead13CalculateTaskCFv = __deleted_virtual_called;

	/* sead::Endian */
	cHostEndian__Q2_4sead6Endian = 0x10AECC78;
	cConvFuncTable__Q2_4sead6Endian = 0x10694BA8;

	/* Profile */
	__ct__7ProfileFPFPC14ActorBuildInfo_P9BaseActorUiRCQ2_4sead23SafeStringBase__tm__2_cPC9ActorInfoT2 = 0xEBD9554;
	get__7ProfileSFUi = 0xEBD9774;
	spriteToProfileList__7Profile = 0x106EEF8C;
	prioritiesOriginal__7Profile = 0x10503B40;
	hasResourcesOriginal__7Profile = 0x10504264;
	resourceCountOriginal__7Profile = 0x105045F8;
	profilesOriginal__7Profile = 0x106EFADC;
	resourceListsOriginal__7Profile = 0x106C541C;
 
	/* ActorInfo */
	Default__9ActorInfo = 0x10503AF4;

    /* ActorMgr */
	instance__8ActorMgr = 0x106C52C8;
	create__8ActorMgrFP14ActorBuildInfoUi = 0xEBC9A58;
	createActor__8ActorMgrFP14ActorBuildInfoUi = 0xEBC9A58;
	findActorByType__8ActorMgrFQ2_9ProfileId13ProfileIdTypePP9BaseActor = 0xEBC9B6C;

	/* ActorList */
	findById__9ActorListFPUi = 0xEBCA5C8;
	findActorById__9ActorListFPUi = 0xEBCA5C8;

	/* ActorMgr */
	sInstance__8ActorMgr = 0x106C52C8;
	create__8ActorMgrFP14ActorBuildInfoUi = 0xEBC9A58;

	/* ActorBase */
	__vtbl__9BaseActor = 0x105028C0;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__9BaseActorSFv = 0x106EBEC4;
	typeInfo__L0__getRuntimeTypeInfoStatic__9BaseActorSFv = 0x106EBEC8;
	removeChild__9BaseActorFP9BaseActor = 0xEBC2C8C;
	beforeCreate__9BaseActorFv = 0xEBC2F7C;
	onExecute__9BaseActorFv = 0xEBC2F8C;
	finalExecute__9BaseActorFv = 0xEBC2F94;
	onDraw__9BaseActorFv = 0xEBC2FA0;
	afterDraw__9BaseActorFUi = 0xEBC2F38;
	beforeDelete__9BaseActorFv = 0xEBC2FA8;
	onDelete__9BaseActorFv = 0xEBC2FB0;
	afterDelete__9BaseActorFUi = 0xEBC2F3C;
	getProfileId__9BaseActorFv = 0xEBC2C80;

	/* Actor */
	__vtbl__10StageActor = 0x10502468;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x106EBEBC;
	typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x106EBEC0;
	__ct__10StageActorFPC14ActorBuildInfo = 0xEBC0AC8;
	directionToPlayerH__10StageActorFRC4Vec3 = 0xEBC05EC;
	directionToActorH__10StageActorFRC10StageActor = 0xEBCC800;
	distanceToPlayer__10StageActorFR4Vec2 = 0xEBC05A4;
	deleteActorWhenOutOfView__10StageActorFUi = 0xEBC07A0;
	actorAcCallback0__10StageActorFP14HitboxColliderP4Vec2 = 0xED5E7E8;
	actorAcCallback2__10StageActorFP14HitboxColliderP4Vec2 = 0xED5E8A4;
	actorCbCallback0__10StageActorFP12ColliderBaseP4Vec2 = 0xED5E8B8;
	checkDerivedRuntimeTypeInfo__10StageActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xEBC2A38;
	getRuntimeTypeInfo__10StageActorCFv = __deleted_virtual_called;
	__dt__10StageActorFv = 0xEBC0F18;
	afterCreate__10StageActorFUi = 0xEBC0FB8;
	beforeExecute__10StageActorFv = 0xEBC0FE8;
	afterExecute__10StageActorFUi = 0xEBC10BC;
	beforeDraw__10StageActorFv = 0xEBC11A0;
	removeHitboxColliders__10StageActorFv = 0xEBC02CC;
	addHitboxColliders__10StageActorFv = 0xEBC0328;
	killAtGoal__10StageActorFv = 0xEBC2AD8;
	splashWater__10StageActorFP4Vec3 = 0xEBC2ADC;
	splashLava__10StageActorFP4Vec3 = 0xEBC2AE0;
	splashLavaWave__10StageActorFP4Vec3 = 0xEBC0960;
	splashPoison__10StageActorFP4Vec3 = 0xEBC2AE4;
	isOffScreen__10StageActorFv = 0xEBC1254;

	/* PhysicsActor */
	__vtbl__12PhysicsActor = 0x10502A4C;
	__ct__12PhysicsActorFPC14ActorBuildInfo = 0xEBC2FB8;
	__dt__12PhysicsActorFv = 0xEBC40B0;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__12PhysicsActorSFv = 0x106EBED4;
	typeInfo__L0__getRuntimeTypeInfoStatic__12PhysicsActorSFv = 0x106EBED8;
	handleGravity__12PhysicsActorFv = 0xEBC39AC;
	handleSpeed__12PhysicsActorFv = 0xEBC3AE4;
	afterCreate__12PhysicsActorFUi = 0xEBC354C;
	beforeExecute__12PhysicsActorFv = 0xEBC35FC;
	afterExecute__12PhysicsActorFUi = 0xEBC36D8;
	onDelete__12PhysicsActorFv = 0xEBC3724;
	setPlayerId__12PhysicsActorFSc = 0xEBC3F10;
	vf114__12PhysicsActorFv = __deleted_virtual_called;
	vf134__12PhysicsActorFv = __deleted_virtual_called;
	vf13C__12PhysicsActorFv = 0xEBC4008;
	vf144__12PhysicsActorFb = 0xEBC375C;
	vf14C__12PhysicsActorFP10StageActor = 0xEBC3760;

	/* MultiStateActor */
	__vtbl__15MultiStateActor = 0x10503248;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__15MultiStateActorSFv = 0x106EBEE4;
	typeInfo__L0__getRuntimeTypeInfoStatic__15MultiStateActorSFv = 0x106EBEE8;
	__ct__15MultiStateActorFPC14ActorBuildInfo = 0xEBCAA8C;
	checkDerivedRuntimeTypeInfo__15MultiStateActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xEBCAF94;

	/* BlockCoinBase */
	__vtbl__13BlockCoinBase = 0x10603C80;
	StateID_BlockCoinState3__13BlockCoinBase = 0x10722764;
	StateID_BumpUp2__13BlockCoinBase = 0x1072271C;
	checkDerivedRuntimeTypeInfo__13BlockCoinBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xF2C8DC0;
	vf18C__13BlockCoinBaseFv = 0xF2C8EFC;
	vf194__13BlockCoinBaseFv = 0xF2C8F00;
	setBelowSensor__13BlockCoinBaseFv = 0xF2C8F04;
	vf1A4__13BlockCoinBaseFv = 0xF2C8F08;
	spawnItemUp__13BlockCoinBaseFv = 0xF2C8F0C;
	vf1B4__13BlockCoinBaseFv = 0xF2C8F10;
	vf1BC__13BlockCoinBaseFv = 0xF2C8F14;
	spawnItemDown__13BlockCoinBaseFv = 0xF2C8F18;
	vf1CC__13BlockCoinBaseFv = 0xF2C8F1C;
	vf1D4__13BlockCoinBaseFb = 0xF2C4868;
	vf1DC__13BlockCoinBaseFv = 0xF2C8F20;
	spawnCoinShower__13BlockCoinBaseFv = 0xF2C48E4;
	vf1EC__13BlockCoinBaseFv = 0xF2C8F28;
	beginState_BumpUp__13BlockCoinBaseFv = 0xF2C7CB4;
	executeState_BumpUp__13BlockCoinBaseFv = 0xF2C7CF0;
	endState_BumpUp__13BlockCoinBaseFv = 0xF2C8F2C;
	beginState_BlockCoinState1__13BlockCoinBaseFv = 0xF2C7D94;
	executeState_BlockCoinState1__13BlockCoinBaseFv = 0xF2C7DA0;
	endState_BlockCoinState1__13BlockCoinBaseFv = 0xF2C8F30;
	beginState_BumpDown__13BlockCoinBaseFv = 0xF2C7DB8;
	executeState_BumpDown__13BlockCoinBaseFv = 0xF2C7DFC;
	endState_BumpDown__13BlockCoinBaseFv = 0xF2C8F34;
	beginState_BlockCoinState2__13BlockCoinBaseFv = 0xF2C7E9C;
	executeState_BlockCoinState2__13BlockCoinBaseFv = 0xF2C7EA8;
	endState_BlockCoinState2__13BlockCoinBaseFv = 0xF2C8F38;
	beginState_BumpUp2__13BlockCoinBaseFv = 0xF2C7ED0;
	executeState_BumpUp2__13BlockCoinBaseFv = 0xF2C7F58;
	endState_BumpUp2__13BlockCoinBaseFv = 0xF2C8F3C;
	beginState_BumpDown2__13BlockCoinBaseFv = 0xF2C812C;
	executeState_BumpDown2__13BlockCoinBaseFv = 0xF2C8198;
	endState_BumpDown2__13BlockCoinBaseFv = 0xF2C8F40;
	beginState_BlockCoinState3__13BlockCoinBaseFv = 0xF2C828C;
	executeState_BlockCoinState3__13BlockCoinBaseFv = 0xF2C8298;
	endState_BlockCoinState3__13BlockCoinBaseFv = 0xF2C8F44;
	spawnPortableSpring__13BlockCoinBaseFv = 0xF2C6430;
	spawnVine__13BlockCoinBaseFv = 0xF2C62A8;
	spawnYoshiEgg__13BlockCoinBaseFb = 0xF2C6BA4;
	spawnPowerup__13BlockCoinBaseFP4Vec3UiT2b = 0xF2C6D1C;
	spawnMultiPowerup__13BlockCoinBaseFP4Vec3UiT2b = 0xF2C6FF4;

	/* MovementBlockCoinBase */
	__vtbl__21MovementBlockCoinBase = 0x106097AC;
	checkDerivedRuntimeTypeInfo__21MovementBlockCoinBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xF2E7A08;
	spawnItemUp__21MovementBlockCoinBaseFv = 0xF2E6610;
	spawnItemDown__21MovementBlockCoinBaseFv = 0xF2E6634;
	vf1DC__21MovementBlockCoinBaseFv = 0xF2E6644;
	vf1EC__13BlockCoinBaseFv = 0xF2E7980;
	vf29C__21MovementBlockCoinBaseFv = 0xF2E7984;
	setTileFlag__21MovementBlockCoinBaseFv = 0xF2E65BC;
	vf2AC__21MovementBlockCoinBaseFv = 0xF2E7988;
	vf2B4__21MovementBlockCoinBaseFv = 0xF2E7990;
	vf2BC__21MovementBlockCoinBaseFv = 0xF2E7994;
	vf2C4__21MovementBlockCoinBaseFv = 0xF2E7998;
	vf2CC__21MovementBlockCoinBaseFv = 0xF2E6654;
	registerColliderActiveInfo__21MovementBlockCoinBaseFv = 0xF2E6760;

	/* BlockBase */
	StateID_Wait__9BlockBase = 0x10720AE0;
	StateID_Used__9BlockBase = 0x10720B04;
	activeTopCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xF2C4ECC;
	activeBottomCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xF2C5528;
	activeSideCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xF2C5EFC;
	usedTopCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xF2C50F0;
	usedBottomCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xF2C595C;
	usedSideCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xF2C60C0;
	init__9BlockBaseFbT1 = 0xF25F6C8;
	initMover__9BlockBaseFv = 0xF25FB30;
	__vtbl__9BlockBase = 0x105E8B60;
	__ct__9BlockBaseFPC14ActorBuildInfo = 0xF25E614;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__9BlockBaseSFv = 0x106EBEF4;
	typeInfo__L0__getRuntimeTypeInfoStatic__9BlockBaseSFv = 0x106EBEF8;
	checkDerivedRuntimeTypeInfo__9BlockBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xF260460;
	getRuntimeTypeInfo__9BlockBaseCFv = __deleted_virtual_called;
	onExecute__9BlockBaseFv = 0xF25E6C4;
	onDraw__9BlockBaseFv = 0xF25E77C;
	setBelowSensor__9BlockBaseFv = 0xF25F400;
	spawnItemUp__9BlockBaseFv = 0xF25EBC0;
	spawnItemDown__9BlockBaseFv = 0xF25EBC4;
	vf1CC__9BlockBaseFv = 0xF25EC04;
	vf1EC__9BlockBaseFv = 0xF25F674;
	vf2C4__9BlockBaseFv = 0xF25F410;
	isActive__9BlockBaseFv = 0xF25EC1C;
	vf2DC__9BlockBaseFv = 0xF260404;
	getContent__9BlockBaseFv = 0xF260408;
	vf2EC__9BlockBaseFv = 0xF25EFE4;
	vf2F4__9BlockBaseFPv = 0xF260418;
	execute__9BlockBaseFv = 0xF25F078;
	destroy__9BlockBaseFv = 0xF25F25C;
	destroy2__9BlockBaseFv = 0xF25F33C;
	vf314__9BlockBaseFv = 0xF260434;
	vf31C__9BlockBaseFv = 0xF260438;
	vf324__9BlockBaseFv = 0xF26043C;
	vf32C__9BlockBaseFv = 0xF260440;
	beginState_Wait__9BlockBaseFv = 0xF26061C;
	executeState_Wait__9BlockBaseFv = 0xF260068;
	endState_Wait__9BlockBaseFv = 0xF260620;
	beginState_Used__9BlockBaseFv = 0xF260624;
	executeState_Used__9BlockBaseFv = 0xF260074;
	endState_Used__9BlockBaseFv = 0xF260628;

	/* BrosBase */
	__ct__8BrosBaseFPC14ActorBuildInfo = 0xEE9A0AC;
	__dt__8BrosBaseFv = 0xEE9E7A4;
	checkDerivedRuntimeTypeInfo__8BrosBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xEE9E628;
	getRuntimeTypeInfo__8BrosBaseCFv = __deleted_virtual_called;
	onCreate__8BrosBaseFv = 0xEE9A758;
	onExecute__8BrosBaseFv = 0xEE9AFE8;
	onDraw__8BrosBaseFv = 0xEE9B08C;
	onDelete__8BrosBaseFv = 0xEE9E848;
	setPlayerId__8BrosBaseFSc = 0xEE9E460;
	getCollisionMgr__8BrosBaseFv = 0xEE9E498;
	vfAC__8BrosBaseFv = 0xEE9E468;
	vfB4__8BrosBaseFv = 0xEE9E46C;
	vfBC__8BrosBaseFv = 0xEE9E474;
	vfC4__8BrosBaseFv = 0xEE9E478;
	vfCC__8BrosBaseFv = 0xEE9E47C;
	killAtGoal__8BrosBaseFv = 0xEE9D66C;
	vf10C__8BrosBaseFUc = 0xEE9E480;
	vf11C__8BrosBaseFv = 0xEE9E488;
	vf124__8BrosBaseFf = 0xEE9E48C;
	vf12C__8BrosBaseFv = 0xEE9E490;
	move__8BrosBaseFR4Vec2 = 0xEE9E4A0;
	setYSpeed__8BrosBaseFf = 0xEE9E4B4;
	vf16C__8BrosBaseFv = 0xEE9E4BC;
	vf174__8BrosBaseFv = 0xEE9E4C4;
	getRect__8BrosBaseFR4Rect = 0xEE9E4CC;
	vf18C__8BrosBaseFv = 0xEE9E620;
	damagePlayer__8BrosBaseFP14HitboxColliderT1 = 0xEE9D264;
	freeze__8BrosBaseFv = 0xEE9D3D8;
	vf1AC__8BrosBaseFv = 0xEE9D484;
	vf1BC__8BrosBaseFv = 0xEE9D3C0;
	vf1C4__8BrosBaseFv = 0xEE9B0C0;
	collisionPlayer__8BrosBaseFP14HitboxColliderT1 = 0xEE9B0C4;
	collisionYoshi__8BrosBaseFP14HitboxColliderT1 = 0xEE9B210;
	collisionStar__8BrosBaseFP14HitboxColliderT1 = 0xEE9B6A0;
	collisionPropellerDrill__8BrosBaseFP14HitboxColliderT1 = 0xEE9B318;
	collisionGroundPound__8BrosBaseFP14HitboxColliderT1 = 0xEE9B50C;
	collisionIceball__8BrosBaseFP14HitboxColliderT1 = 0xEE9B870;
	collisionHammer__8BrosBaseFP14HitboxColliderT1 = 0xEE9B510;
	vf2A4__8BrosBaseFP14HitboxColliderT1 = 0xEE9B954;
	beginState_DieFumi__8BrosBaseFv = 0xEE9CE14;
	executeState_DieFumi__8BrosBaseFv = 0xEE9CEA8;
	endState_DieFumi__8BrosBaseFv = 0xEE9E860;
	beginState_DieFall__8BrosBaseFv = 0xEE9CEF4;
	executeState_DieFall__8BrosBaseFv = 0xEE9CF88;
	endState_DieFall__8BrosBaseFv = 0xEE9E864;
	beginState_Move__8BrosBaseFv = 0xEE9BE48;
	executeState_Move__8BrosBaseFv = 0xEE9C000;
	endState_Move__8BrosBaseFv = 0xEE9E850;
	beginState_Attack__8BrosBaseFv = 0xEE9C294;
	executeState_Attack__8BrosBaseFv = 0xEE9C2D4;
	endState_Attack__8BrosBaseFv = 0xEE9E854;
	beginState_JumpSt__8BrosBaseFv = 0xEE9C5C8;
	executeState_JumpSt__8BrosBaseFv = 0xEE9C61C;
	endState_JumpSt__8BrosBaseFv = 0xEE9E858;
	beginState_JumpMd__8BrosBaseFv = 0xEE9C768;
	executeState_JumpMd__8BrosBaseFv = 0xEE9C878;
	endState_JumpMd__8BrosBaseFv = 0xEE9C928;
	beginState_JumpEd__8BrosBaseFv = 0xEE9C934;
	executeState_JumpEd__8BrosBaseFv = 0xEE9C9AC;
	endState_JumpEd__8BrosBaseFv = 0xEE9E85C;
	beginState_AirAttack__8BrosBaseFv = 0xEE9CA88;
	executeState_AirAttack__8BrosBaseFv = 0xEE9CAD4;
	endState_AirAttack__8BrosBaseFv = 0xEE9CDFC;
	beginState_Down__8BrosBaseFv = 0xEE9D000;
	executeState_Down__8BrosBaseFv = 0xEE9D094;
	endState_Down__8BrosBaseFv = 0xEE9D21C;
	vf58C__8BrosBaseFv = __deleted_virtual_called;
	getProjectileCreateFrame__8BrosBaseFv = 0xEE9E868;
	getProjectileThrowFrame__8BrosBaseFv = 0xEE9E874;
	setWalkingSpeed__8BrosBaseFv = 0xEE9E880;
	vf5AC__8BrosBaseFv = __deleted_virtual_called;
	getTextureId__8BrosBaseFv = 0xEE9E884;
	setWalkingTimer__8BrosBaseFv = 0xEE9E88C;
	vf5C4__8BrosBaseFv = __deleted_virtual_called;
	vf5CC__8BrosBaseFv = 0xEE9D500;
	vf5D4__8BrosBaseFv = 0xEE9E890;
	createProjectile__8BrosBaseFv = 0xEE9E894;
	setHopTimer__8BrosBaseFv = 0xEE9E89C;
	setHopSpeed__8BrosBaseFv = 0xEE9E8A0;
	doAirAttack__8BrosBaseFv = 0xEE9E8A4;
	vf604__8BrosBaseFv = 0xEE9E8F8;
	vf60C__8BrosBaseFv = 0xEE9E900;
	doAttack__8BrosBaseFv = 0xEE9E908;
	setThrowAnimation__8BrosBaseFv = 0xEE9D598;
	vf624__8BrosBaseFv = 0xEE9E928;
	vf62C__8BrosBaseFv = 0xEE9E934;
	vf634__8BrosBaseFv = 0xEE9E938;
	vf63C__8BrosBaseFv = __deleted_virtual_called;
	vf644__8BrosBaseFv = __deleted_virtual_called;
	vf64C__8BrosBaseFv = 0xEE9E93C;
	vf654__8BrosBaseFv = 0xEE9E940;
	vf65C__8BrosBaseFv = 0xEE9D768;
	vf664__8BrosBaseFv = 0xEE9E944;
	vf66C__8BrosBaseFv = 0xEE9E948;

	/* Enemy */
	StateID_DieFumi__5Enemy = 0x107031B0;
	__vtbl__5Enemy = 0x1057429C;
	__ct__5EnemyFPC14ActorBuildInfo = 0xEEE8494;
	collisionCallback__5EnemySFP14HitboxColliderT1 = 0xEEE8C50;
	processCollision__5EnemyFP14HitboxColliderT1Ui = 0xEEE9B88;
	killPlayerJump__5EnemyFP10StageActorRC4Vec2P9StateBase = 0xEEEDA34;
	killPlayerSpin__5EnemyFP10StageActor = 0xEEECC98;
	killYoshiStomp__5EnemyFP10StageActor = 0xEEED31C;
	__dt__5EnemyFv = 0xEEEA868;
	checkDerivedRuntimeTypeInfo__5EnemyCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xEEEA70C;
    getRuntimeTypeInfo__5EnemyCFv = __deleted_virtual_called;
	beforeExecute__5EnemyFv = 0xEEE8644;
	damageFromUnder__5EnemyFv = 0xEEE8914;
	vf14C__5EnemyFP10StageActor = 0xEEEDC88;
	vf154__5EnemyFv = 0xEEEE1A4;
	doStateChange__5EnemyFP9StateBase = 0xEEF0404;
	vf18C__5EnemyFv = 0xEEEA848;
	damagePlayer__5EnemyFP14HitboxColliderT1 = 0xEEE8B84;
	vf19C__5EnemyFv = 0xEEE910C;
	freeze__5EnemyFv = 0xEEF04F8;
	vf1AC__5EnemyFv = 0xEEF10BC;
	vf1B4__5EnemyFv = 0xEEF10C0;
	vf1BC__5EnemyFv = 0xEEF0568;
	vf1C4__5EnemyFv = 0xEEEA858;
	vf1CC__5EnemyFv = 0xEEEA85C;
	vf1D4__5EnemyFP14HitboxColliderT1 = 0xEEE91F8;
	vf1DC__5EnemyFP14HitboxColliderT1 = 0xEEE9250;
	vf1E4__5EnemyFRbP14HitboxColliderT2 = 0xEEE9520;
	vf1EC__5EnemyFP14HitboxColliderT1 = 0xEEE9578;
	vf1F4__5EnemyFP14HitboxColliderT1 = 0xEEE957C;
	vf1FC__5EnemyFP14HitboxColliderT1 = 0xEEE96E8;
	vf204__5EnemyFP14HitboxColliderT1 = 0xEEE9800;
	collisionEnemy__5EnemyFP14HitboxColliderT1 = 0xEEE99F0;
	collisionPlayer__5EnemyFP14HitboxColliderT1 = 0xEEE99F4;
	collisionYoshi__5EnemyFP14HitboxColliderT1 = 0xEEE9A04;
	vf224__5EnemyFP14HitboxColliderT1 = 0xEEE9A08;
	collisionStar__5EnemyFP14HitboxColliderT1 = 0xEEECE84;
	collisionSlide__5EnemyFP14HitboxColliderT1 = 0xEEECF20;
	collisionPropellerDrill__5EnemyFP14HitboxColliderT1 = 0xEEED014;
	vf244__5EnemyFP14HitboxColliderT1 = 0xEEED0E4;
	collisionGroundPound__5EnemyFP14HitboxColliderT1 = 0xEEED240;
	collisionGroundPoundYoshi__5EnemyFP14HitboxColliderT1 = 0xEEED3B4;
	collisionPenguinSlide__5EnemyFP14HitboxColliderT1 = 0xEEED48C;
	collisionPipeCannon__5EnemyFP14HitboxColliderT1 = 0xEEED49C;
	vf26C__5EnemyFP14HitboxColliderT1 = 0xEEED56C;
	collisionThrowableObject__5EnemyFP14HitboxColliderT1 = 0xEEED57C;
	collisionFireball__5EnemyFP14HitboxColliderT1 = 0xEEED70C;
	collisionIceball__5EnemyFP14HitboxColliderT1 = 0xEEED7A4;
	collisionHammer__5EnemyFP14HitboxColliderT1 = 0xEEED824;
	collisionFireballYoshi__5EnemyFP14HitboxColliderT1 = 0xEEED938;
	vf29C__5EnemyFP14HitboxColliderT1 = 0xEEEDA04;
	vf2A4__5EnemyFP14HitboxColliderT1 = 0xEEEDA0C;
	vf2AC__5EnemyFP14HitboxColliderT1 = 0xEEEDA14;
	vf2B4__5EnemyFP14HitboxColliderT1 = 0xEEEDA24;
	vf2BC__5EnemyFv = 0xEEEDAF0;
	vf2C4__5EnemyFv = 0xEEEDD48;
	vf2CC__5EnemyFv = 0xEEEE048;
	isOnGround__5EnemyFv = 0xEEEE2EC;
	vf2DC__5EnemyFv = 0xEEEE2F8;
	vf2E4__5EnemyFv = 0xEEEE358;
	vf2EC__5EnemyFv = 0xEEE9EA4;
	vf2F4__5EnemyFv = 0xEEE9FA8;
	vf2FC__5EnemyFv = 0xEEE9FAC;
	vf304__5EnemyFv = 0xEEE9FB0;
	vf30C__5EnemyFv = 0xEEE9FC0;
	vf314__5EnemyFv = 0xEEEA094;
	vf31C__5EnemyFv = 0xEEEA118;
	vf324__5EnemyFv = 0xEEEA1BC;
	vf32C__5EnemyFv = 0xEEEA240;
	vf334__5EnemyFv = 0xEEEA24C;
	vf33C__5EnemyFv = 0xEEEA250;
	vf344__5EnemyFv = 0xEEEA2D4;
	vf34C__5EnemyFv = 0xEEEA2E4;
	vf354__5EnemyFv = 0xEEEA2FC;
	vf35C__5EnemyFv = 0xEEEA364;
	vf364__5EnemyFv = 0xEEEA418;
	vf36C__5EnemyFv = 0xEEEA4CC;
	vf374__5EnemyFv = 0xEEEA864;
	beginState_DieFumi__5EnemyFv = 0xEEEE518;
	executeState_DieFumi__5EnemyFv = 0xEEEE5E8;
	endState_DieFumi__5EnemyFv = 0xEEEEED0;
	beginState_DieFall__5EnemyFv = 0xEEEE63C;
	executeState_DieFall__5EnemyFv = 0xEEEE640;
	endState_DieFall__5EnemyFv = 0xEEEEED4;
	vf3AC__5EnemyFv = 0xEEEE72C;
	vf3B4__5EnemyFv = 0xEEEE79C;
	vf3BC__5EnemyFv = 0xEEEEED8;
	vf3C4__5EnemyFv = 0xEEEE7A8;
	vf3CC__5EnemyFv = 0xEEEE7B8;
	vf3D4__5EnemyFv = 0xEEEEEDC;
	vf3DC__5EnemyFv = 0xEEEE7C4;
	vf3E4__5EnemyFv = 0xEEEE7C8;
	vf3EC__5EnemyFv = 0xEEEEEE0;
	vf3F4__5EnemyFv = 0xEEEE7D4;
	vf3FC__5EnemyFv = 0xEEEEEE4;
	vf404__5EnemyFv = 0xEEEEEE8;
	vf40C__5EnemyFv = 0xEEEE7E0;
	vf414__5EnemyFv = 0xEEEEEEC;
	vf41C__5EnemyFv = 0xEEEEEF0;
	vf424__5EnemyFv = 0xEEF05E4;
	vf42C__5EnemyFv = 0xEEF05EC;
	vf434__5EnemyFv = 0xEEF10C4;
	vf43C__5EnemyFv = 0xEEF10C8;
	vf444__5EnemyFv = 0xEEF10CC;
	vf44C__5EnemyFv = 0xEEF10D0;
	vf454__5EnemyFv = 0xEEF10D4;
	vf45C__5EnemyFv = 0xEEF10D8;
	vf464__5EnemyFv = 0xEEF10DC;
	vf46C__5EnemyFv = 0xEEF06E8;
	vf474__5EnemyFv = 0xEEF06F0;
	vf47C__5EnemyFv = 0xEEF10E0;
	vf484__5EnemyFv = 0xEEF10E4;
	vf48C__5EnemyFv = 0xEEF10E8;
	vf494__5EnemyFv = 0xEEF10EC;
	vf49C__5EnemyFv = 0xEEF10F0;
	vf4A4__5EnemyFv = 0xEEF10F4;
	vf4AC__5EnemyFv = 0xEEF10F8;
	vf4B4__5EnemyFv = 0xEEF10FC;
	vf4BC__5EnemyFv = 0xEEF1100;
	vf4C4__5EnemyFv = 0xEEF1104;
	beginState_Ice__5EnemyFv = 0xEEF0720;
	executeState_Ice__5EnemyFv = 0xEEF07A0;
	endState_Ice__5EnemyFv = 0xEEF0944;

	/* Boss */
	__vtbl__4Boss = 0x1050782C;
	__ct__4BossFP14ActorBuildInfo = 0xEBEB968;
	checkDerivedRuntimeTypeInfo__4BossFPv = 0xEBEDAB0;
	__dt__4BossFv = 0xEBEE2E0;
	onCreate__4BossFv = 0xEBEBB68;
	beforeExecute__4BossFv = 0xEBEBD0C;
	afterExecute__4BossFi = 0xEBEBDDC;
	onDelete__4BossFv = 0xEBEDC2C;
	removeColliders__4BossFv = 0xEBEDDF0;
	addColliders__4BossFv = 0xEBEDE7C;
	vf154__4BossFv = 0xEBECE40;
	freezeActor__4BossFv = 0xEBECEAC;
	vf1BC__4BossFv = 0xEBECF64;
	vf1C4__4BossFv = 0xEBEE2D0;
	playerCollision__4BossFUiP8Collider = 0xEBEBFDC;
	yoshiCollision__4BossFUiP8Collider = 0xEBEC2B4;
	vf22C__4BossFv = 0xEBEDCC8;
	hitJump__4BossFP8ColliderT1 = 0xEBEDCD0;
	collidesSomething__4BossFP8ColliderT1 = 0xEBEC5D0;
	hitEnemyDown__4BossFP8ColliderT1 = 0xEBEDCD8;
	hitGroundPound__4BossFP8ColliderT1 = 0xEBEC3AC;
	hitEnemyKame2__4BossFP8ColliderT1 = 0xEBEC5E0;
	hitEnemyKameDown__4BossFP8ColliderT1 = 0xEBEC8E0;
	vf27C__4BossFv = 0xEBEC6D4;
	vf284__4BossFP8ColliderT1 = 0xEBECBCC;
	hitEx__4BossFv = 0xEBECCB0;
	vf2C4__4BossFv = 0xEBEDCE0;
	isGrounded__4BossFv = 0xEBECE00;
	vf2F4__4BossFv = 0xEBEDD38;
	beginState_JumpKill__4BossFv = 0xEBEDC9C;
	executeState_JumpKill__4BossFv = 0xEBEDCA0;
	endState_JumpKill__4BossFv = 0xEBEDCA4;
	beginState_BossState1__4BossFv = 0xEBEBECC;
	executeState_BossState1__4BossFv = 0xEBEBEDC;
	endState_BossState1__4BossFv = 0xEBEBEEC;
	beginState_BossState2__4BossFv = 0xEBEBEFC;
	executeState_BossState2__4BossFv = 0xEBEBF0C;
	endState_BossState2__4BossFv = 0xEBEBF1C;
	beginState_BossState3__4BossFv = 0xEBEBF2C;
	executeState_BossState3__4BossFv = 0xEBEBF3C;
	endState_BossState3__4BossFv = 0xEBEBF4C;
	beginState_BossState4__4BossFv = 0xEBEBF5C;
	executeState_BossState4__4BossFv = 0xEBEBF6C;
	endState_BossState4__4BossFv = 0xEBEBF7C;
	beginState_BossState5__4BossFv = 0xEBEBF8C;
	executeState_BossState5__4BossFv = 0xEBEBF9C;
	endState_BossState5__4BossFv = 0xEBEBFAC;
	vf55C__4BossFv = 0xEBEDCA8;
	vf564__4BossFv = 0xEBEDCB4;
	vf56C__4BossFv = 0xEBEDCC0;
	vf574__4BossFv = 0xEBEBFBC;
	vf57C__4BossFv = 0xEBEDCC4;
	vf584__4BossFv = __deleted_virtual_called;
	vf58C__4BossFv = 0xEBEDD3C;
	vf594__4BossFv = 0xEBEDD4C;
	vf59C__4BossFv = __deleted_virtual_called;
	vf5A4__4BossFv = __deleted_virtual_called;
	vf5AC__4BossFv = __deleted_virtual_called;
	vf5B4__4BossFv = 0xEBEDD90;
	vf5BC__4BossFUi = 0xEBEDD98;
	vf604__4BossFv = 0xEBEDDBC;
	vf60C__4BossFv = 0xEBEDDC0;
	vf614__4BossFv = 0xEBEDDC4;
	vf61C__4BossFv = 0xEBEDDC8;
	vf624__4BossFv = __deleted_virtual_called;
	vf62C__4BossFv = 0xEBEDDD0;
	vf634__4BossFP12PhysicsActor = 0xEBEDDD8;
	vf63C__4BossFP12PhysicsActor = 0xEBEDDE4;
	vf644__4BossFv = 0xEBED120;
	vf64C__4BossFUi = 0xEBED214;
	vf654__4BossFv = 0xEBEDF28;
	changeState_JumpKill__4BossFv = 0xEBEDF2C;
	vf664__4BossFv = 0xEBEDF44;
	changeState_State1__4BossFv = 0xEBEDF48;
	vf674__4BossFv = 0xEBEDF60;
	vf67C__4BossFv = 0xEBEDF70;
	vf684__4BossFv = __deleted_virtual_called;
	vf68C__4BossFv = __deleted_virtual_called;
	vf694__4BossFv = __deleted_virtual_called;
	vf69C__4BossFv = __deleted_virtual_called;
	vf6A4__4BossFv = 0xEBEDF80;
	changeState_State5__4BossFv = 0xEBEDF84;
	vf6B4__4BossFv = 0xEBEDF9C;
	changeState_State3__4BossFv = 0xEBEDFA0;
	vf6C4__4BossFv = __deleted_virtual_called;
	vf6CC__4BossFv = __deleted_virtual_called;
	vf6D4__4BossFv = 0xEBEDFB8;
	vf6DC__4BossFv = 0xEBEDFC0;
	vf6E4__4BossFv = 0xEBEDFC4;
	vf6EC__4BossFv = 0xEBEDFD4;
	vf6F4__4BossFv = 0xEBEDFDC;
	vf6FC__4BossFv = 0xEBEDFE4;
	vf704__4BossFv = 0xEBEDFEC;
	vf70C__4BossFv = __deleted_virtual_called;
	vf714__4BossFv = __deleted_virtual_called;
	vf71C__4BossFv = __deleted_virtual_called;
	vf724__4BossFv = 0xEBEDFF4;
	vf72C__4BossFv = 0xEBEDFF8;
	vf734__4BossFv = 0xEBEDFFC;
	vf73C__4BossFv = __deleted_virtual_called;
	vf744__4BossFv = 0xEBEE000;
	stomp__4BossFv = 0xEBEE004;
	lastStomp__4BossFv = 0xEBEE01C;
	vf75C__4BossFv = __deleted_virtual_called;
	damageStar__4BossFv = 0xEBEE034;
	vf76C__4BossFv = __deleted_virtual_called;
	damageLast__4BossFv = 0xEBEE04C;
	damageFire__4BossFv = 0xEBEE064;
	damageFireLast__4BossFv = 0xEBEE0D8;
	damageFire2__4BossFv = 0xEBEE130;
	damageFireLast2__4BossFv = 0xEBEE1A4;
	damageStarDef__4BossFv = 0xEBEE1FC;
	damageLast2__4BossFv = 0xEBEE214;
	vf7AC__4BossFv = 0xEBEE22C;
	vf7B4__4BossFv = __deleted_virtual_called;
	vf7BC__4BossFv = __deleted_virtual_called;
	vf7C4__4BossFv = 0xEBEE230;
	vf7CC__4BossFv = 0xEBED3BC;
	initBossCollider__4BossFv = 0xEBED3F4;
	initModels__4BossFv = 0xEBEE2B8;
	vf7E4__4BossFv = 0xEBEE2BC;
	vf7EC__4BossFv = 0xEBEE2C0;
	vf7F4__4BossFv = 0xEBEE2C4;
	vf7FC__4BossFv = 0xEBEE2C8;

	/* Thwomp */
	__ct__6ThwompFPC14ActorBuildInfo = 0xEEE1F08;
	__dt__6ThwompFv = 0xEEE4980;
	checkDerivedRuntimeTypeInfo__6ThwompCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xEEE472C;
 	getRuntimeTypeInfo__6ThwompCFv = __deleted_virtual_called;
	onCreate__6ThwompFv = 0xEEE26AC;
	onExecute__6ThwompFv = 0xEEE2AAC;
	onDraw__6ThwompFv = 0xEEE2B28;
	onDelete__6ThwompFv = 0xEEE48A8;
	setPlayerId__6ThwompFSc = 0xEEE4564;
	getCollisionMgr__6ThwompFv = 0xEEE459C;
	vfAC__6ThwompFv = 0xEEE456C;
	vfB4__6ThwompFv = 0xEEE4570;
	vfBC__6ThwompFv = 0xEEE4578;
	vfC4__6ThwompFv = 0xEEE457C;
	vfCC__6ThwompFv = 0xEEE4580;
	killAtGoal__6ThwompFv = 0xEEE2B58;
	damageFromUnder__6ThwompFv = 0xEEE497C;
	vf10C__6ThwompFUc = 0xEEE4584;
	vf11C__6ThwompFv = 0xEEE458C;
	vf124__6ThwompFf = 0xEEE4590;
	vf12C__6ThwompFv = 0xEEE4594;
	move__6ThwompFR4Vec2 = 0xEEE45A4;
	setYSpeed__6ThwompFf = 0xEEE45B8;
	vf16C__6ThwompFv = 0xEEE45C0;
	vf174__6ThwompFv = 0xEEE45C8;
	getRect__6ThwompFR4Rect = 0xEEE45D0;
	vf18C__6ThwompFv = 0xEEE4724;
	collisionStar__6ThwompFP14HitboxColliderT1 = 0xEEE3924;
	collisionPropellerDrill__6ThwompFP14HitboxColliderT1 = 0xEEE48D4;
	collisionGroundPound__6ThwompFP14HitboxColliderT1 = 0xEEE48DC;
	collisionPenguinSlide__6ThwompFP14HitboxColliderT1 = 0xEEE3930;
	collisionThrowableObject__6ThwompFP14HitboxColliderT1 = 0xEEE48E4;
	collisionFireball__6ThwompFP14HitboxColliderT1 = 0xEEE48EC;
	collisionIceball__6ThwompFP14HitboxColliderT1 = 0xEEE4954;
	vf2BC__6ThwompFv = 0xEEE3A08;
	beginState_DieFall__6ThwompFv = 0xEEE344C;
	executeState_DieFall__6ThwompFv = 0xEEE36B4;
	endState_DieFall__6ThwompFv = 0xEEE48D0;

	/* WindGeneratorBase */
	__vtbl__13WindGenerator = 0x106582A8;
	__dt__17WindGeneratorBaseFv = 0xF44F044;
	onCreate__17WindGeneratorBaseFv = 0xF44EC68;
	onExecute__17WindGeneratorBaseFv = 0xF44ED94;

	/* HitboxCollider */
	__ct__14HitboxColliderFv = 0xED5A960;
	__dt__14HitboxColliderFv = 0xED5AB90;
	__CPR65__init__14HitboxColliderFP10StageActorPCQ2_J6J4InfoPPv = 0xED5AF1C;
	Default__Q2_14HitboxCollider4Info = 0x10543DC0;

	/* HitboxColliderMgr */
	instance__17HitboxColliderMgr = 0x106CB7D8;

	/* ColliderBase */
	setType__12ColliderBaseFQ2_12ColliderBase5Types = 0xED65A70;
	__CPR62__setSurfaceType__12ColliderBaseFQ2_J16J12SurfaceTypes = 0xED65AD0;

	/* ColliderBase::Node */
	__ct__Q2_12ColliderBase4NodeFv = 0xED61ACC;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__12ColliderBaseSFv = 0x106EBF2C;
	typeInfo__L0__getRuntimeTypeInfoStatic__12ColliderBaseSFv = 0x106EC1A4;

	/* ShapedCollider */
	__ct__14ShapedColliderFiP4Vec2PQ2_12ColliderBase4NodeT3 = 0xED67904;
	__CPR62__init__14ShapedColliderFP10StageActorRCQ2_J6J4Info = 0xED6D3BC;
	execute__14ShapedColliderFv = 0xED6871C;
	__dt__14ShapedColliderFv = 0xED67A04;
	setRect__14ShapedColliderFP4Vec2T1 = 0xED6D25C;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__14ShapedColliderSFv = 0x106EBF30;
	typeInfo__L0__getRuntimeTypeInfoStatic__14ShapedColliderSFv = 0x106EC1B4;

	/* RectCollider */
	__vtbl__12RectCollider = 0x105FDA20;

	/* SolidOnTopCollider */
	__ct__18SolidOnTopColliderFv = 0xED61D38;
	__CPR85__init__18SolidOnTopColliderFP10StageActorRCQ2_J6J4InfoiPQ2_4sead4Heap = 0xED62378;
	execute__18SolidOnTopColliderFv = 0xED62E0C;
	__dt__18SolidOnTopColliderFv = 0xED61F18;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__18SolidOnTopColliderSFv = 0x106EBF48;
	typeInfo__L0__getRuntimeTypeInfoStatic__18SolidOnTopColliderSFv = 0x106EC1A8;

	/* CircularCollider */
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__16CircularColliderSFv = 0x106EC188;
	typeInfo__L0__getRuntimeTypeInfoStatic__16CircularColliderSFv = 0x106EC598;

	/* ColliderMgr */
	instance__11ColliderMgr = 0x106CB560;
	add__11ColliderMgrFP12ColliderBase = 0xED5269C;
	remove__11ColliderMgrFP12ColliderBase = 0xED5282C;

	/* EnemyFreezeMgr */
	freeze__14EnemyFreezeMgrFRCQ2_14EnemyFreezeMgr4InfoUi = 0xEF3D63C;
	setFlags__14EnemyFreezeMgrFRCQ2_14EnemyFreezeMgr5Flags = 0xEF3CB94;

	/* StateBase */
	currentId__9StateBase = 0x106EC104;
	NullState__9StateBase = 0x1072F590;

	/* StateMgr */
	execute__8StateMgrFv = 0xF584A80;
	changeState__8StateMgrFP9StateBase = 0xF584AF0;

	/* CollisionMgr */
	instance__12CollisionMgr = 0x106CB7D8;
	addCollider__12CollisionMgrFP8Collider = 0xED5E028;
	__dt__12CollisionMgrFv = 0xED4ADFC;
	__CPR63__init__12CollisionMgrFP10StageActorPCQ2_J6J6SensorN22 = 0xED4AF6C;
	setSensor__12CollisionMgrFPCQ2_12CollisionMgr6SensorUi = 0xED4AEFC;
	getSensor__12CollisionMgrCFUi = 0xED4CE74;
	process__12CollisionMgrFv = 0xED4D954;

	/* EventMgr */
	instance__8EventMgr = 0x106DD26C;
	set__8EventMgrFUiT1bN41 = 0xF25CD68;

	/* MusicPlayer */
	shouldHurryUp__11MusicPlayerFv = 0xF5783D8;

	/* ResArchive */
	getModel__10ResArchiveFRCQ2_4sead23SafeStringBase__tm__2_cUiN42bPQ2_4sead4Heap = 0xF0AE440;

	/* ResArchiveMgr */
	instance__13ResArchiveMgr = 0x106D4F50;
	get__13ResArchiveMgrFRCQ2_4sead23SafeStringBase__tm__2_c = 0xF0B60EC;

	/* ModelWrapper */
	__ct__12ModelWrapperFP5ModelUiN42 = 0xF094798;
	setup__12ModelWrapperFP10ResArchivePvPQ2_4sead4Heap = 0xF0949A0;
	updateModel__12ModelWrapperFv = 0xF094E84;
	updateAnimations__12ModelWrapperFv = 0xF094D20;

	/* Mtx34 */
	rotateAndTranslate__5Mtx34FRC5Vec3uRC4Vec3 = 0xEBFC1C8;
	makeST__5Mtx34SFR5Mtx34RC4Vec3T2 = 0xEDE2A88;
	makeSRT__5Mtx34SFR5Mtx34RC4Vec3N22 = 0xF0C8424;

	/* Animation */
	setRepeat__9AnimationFb = 0xF09EED4;

	/* SkeletalAnimation */
	play__17SkeletalAnimationFP10ResArchiveRCQ2_4sead23SafeStringBase__tm__2_c = 0xF0BDADC;

	/* TextureAnimation */
	play__16TextureAnimationFP10ResArchiveRCQ2_4sead23SafeStringBase__tm__2_c = 0xF0CB1EC;

	/* DrawMgr */
	instance__7DrawMgr = 0x106D4F88;
	drawModel__7DrawMgrFP5Model = 0xF0BAB58;
	drawModel__7DrawMgrFP12ModelWrapper = 0xF0BAC98;
	drawTile__7DrawMgrFUsRC4Vec3RCUiT2 = 0xF0BAD28;

	/* AreaRumbleMgr */
	sInstance__13AreaRumbleMgr = 0x106D3860;

	/* LightMask */
	__ct__9LightMaskFv = 0xF3D5C9C;
	init__9LightMaskFPQ2_4sead4HeapUi = 0xF3D5D20;
	update__9LightMaskFv = 0xF3D5DCC;
	draw__9LightMaskFv = 0xF3D60C8;

	/* LightSource */
	__ct__11LightSourceFv = 0xF0A24BC;
	__dt__11LightSourceFv = 0xF0A2580;
	update__11LightSourceFUiP4Vec3PfN23PQ2_4sead7Color4fN23 = 0xF0A26BC;

	/* LineFollower */
	__ct__12LineFollowerFv = 0xEBCDC14;
	init__12LineFollowerFv = 0xEBCDF60;
	start__12LineFollowerFb = 0xEBCE178;

	/* MovementHandler */
	__ct__15MovementHandlerFv = 0xF409C40;
	link__15MovementHandlerFRC4Vec3UiUc = 0xF40B6F4;
	getMaskForMovementType__15MovementHandlerFUi = 0xF40A37C;
	execute__15MovementHandlerFv = 0xF40B8C4;

	/* Effect */
	spawn__6EffectSFiP4Vec3P5Vec3uT2 = 0xEE6B080;

	/* EffectWrapper */
	__ct__13EffectWrapperFv = 0xEE6B868;
	update__13EffectWrapperFiP4Vec3P5Vec3uT2 = 0xEE6B52C;

	/* SoundSystemBase */
	getAudioFx__15SoundSystemBaseFv = 0xF571AA4;

	/* SoundSystem */
	sInstance__11SoundSystem = 0x106E9E84;
	getSoundArchive__11SoundSystemFv = 0xF573BA8;

	/* AudioFx */
	getReverbHiParam__7AudioFxFv = 0xF572FD8;
	getDelayParam__7AudioFxFv = 0xF572FE0;

    /* Level */
	instance__5Level = 0x106DD248;
	getArea__5LevelFUi = 0xF25A2DC;
	instance__10LevelTimer = 0x106D37F4;
	addTime__10LevelTimerFi = 0xF0814C0;

	/* Level::Area */
	getSprite__Q2_5Level4AreaFUiPv = 0xF259C08;
	getLocation__Q2_5Level4AreaFP4RectUc = 0xF25A020;
	getPath__Q2_5Level4AreaFUc = 0xF25A0A8;
	getPathNodes__Q2_5Level4AreaFUi = 0xF25A0F4;

	/* LevelInfo */
	instance__9LevelInfo = 0x106D3AEC;

	/* nw::snd::SoundArchive */
	GetItemLabel__Q3_2nw3snd12SoundArchiveCFUi = 0xF696980;

	/* BasicSoundActor */
	GlobalBasicSoundActorA = 0x106C85D0;
	instance__15BasicSoundActor = 0x106C85D0;
	playSound__15BasicSoundActorFPCcP4Vec2Ui = 0xF57EDEC;

	/* Level */
	sInstance__5Level = 0x106DD248;
	getArea__5LevelFUi = 0xF25A2DC;

	/* Level::Area */
	getSprite__Q2_5Level4AreaFUiPv = 0xF259C08;
	getLocation__Q2_5Level4AreaFP4RectUc = 0xF25A020;
	getPath__Q2_5Level4AreaFUc = 0xF25A0A8;
	getPathNodes__Q2_5Level4AreaFUi = 0xF25A0F4;

	/* LevelInfo */
	instance__9LevelInfo = 0x106D3AEC;

	/* LevelCamera */
	instance__11LevelCamera = 0x106E9E54;

	/* LevelTimer */
	instance__10LevelTimer = 0x106D37F4;
	setTime__10LevelTimerFi = 0xF08134C;
	addTime__10LevelTimerFi = 0xF0814C0;

	/* TileMgr */
	instance__7TileMgr = 0x106DCD94;
	getTilePtrCurrentArea__7TileMgrSFUsT1UcPUi = 0xF245000;

	/* PlayerMgr */
	instance__9PlayerMgr = 0x106E8B94;

	/* AreaTask */
	drawLayer3D__8AreaTaskFRCQ3_3agl3lyr10RenderInfo = 0xF0784A8;

	/* Rect */
	zero__4Rect = 0x10AEC99C;


	/* RDashMgr */
	sInstance__8RDashMgr = 0x106E9F9C;

	/* CourseTask */
	sInstance__10CourseTask = 0x106D37F0;

	/* TaskMgr */
	sInstance__7TaskMgr = 0x106E9D28;
	startLevel__7TaskMgrFPQ2_4sead8TaskBaseUcT2 = 0xF5541D0;
	changeTask__7TaskMgrFPQ2_4sead8TaskBaseRQ2_4sead11TaskClassIDUiT3 = 0xF554164;

	/* TwoWayPlatform */
	cbCallback4__14TwoWayPlatformSFP10StageActor = 0xF3FFBAC;
	cbCallback5__14TwoWayPlatformSFP10StageActor = 0xF3FFBE0;
	cbCallback6__14TwoWayPlatformSFP10StageActorUiT2 = 0xF3FFC14;
	twoWayPlatformCbCallback2__14TwoWayPlatformFP12ColliderBaseP4Vec2 = 0xF40184C;

	/* ResMgr */
	ResMgr_LoadLevelResource = 0xF592A20;
	ResMgr_LoadLevelArchiveSuccess = 0xF593354;
	ResMgr_LoadLevelArchiveFail = 0xF59333C;

    /* RDashMgr */
	instance__8RDashMgr = 0x106E9F9C;

	/* TerrainEffects */
	__CPR79__init__14TerrainEffectsFP4Vec3fbT3Q2_J6J11TerrainTypePQ2_4sead4Heap = 0xF4772D4;
	setWaveValues__14TerrainEffectsFUiN51 = 0xF4774F4;
	checkMarioWaveHit__14TerrainEffectsFv = 0xF478BF4;
	updateWaveCollisions__14TerrainEffectsFv = 0xF478D5C;
	someUpdateFunctionMaybe__14TerrainEffectsFv = 0xF478E64;

	/* EnvTerrain */
	onExecute__10EnvTerrainFv = 0xF2B0E9C;
	setTop__10EnvTerrainFf = 0xF2B1278;

	/* Pokey */
	collisionFireball__5PokeyFP14HitboxColliderT1 = 0xEFF3A38;

	/* Misc */
	ASM_MTXConcat = 0xF6B98A0;
	mapPositionToScreen__FR4Vec2RC4Vec2 = 0xEBE9368;
	moveValueTo__FPUiUiT2 = 0xF5A11F0;
	moveFloatTo__FPffT2 = 0xEBE7984;
	BLOSDynLoad_Acquire = 0xF65EF58;
	BOSDynLoad_FindExport = 0xF65F418;
	PlayerJumpArc = 0x1066CA00;
	MiniPlayerJumpArc = 0x1066CA48;
	PlayerJumpMax = 0x10669068;
	PlayerDescentRate = 0x10669074;
	DefaultReverbHiParam = 0x1072F528;
	DefaultDelayParam = 0x1072F554;
	SFXReverb_0 = 0x106E9F14;
	SFXReverb_1 = 0x106E9F18;
	SFXReverbPlyJump_0 = 0x106E9F1C;
	SFXReverbPlyJump_1 = 0x106E9F20;
	directionToRotationList = 0x10702FD8;
	formatBufferedString = 0xF5CF308;
	setBufferedStringMaybe = 0xF594240;
	nullterminator = 0x1068C76D;

}
