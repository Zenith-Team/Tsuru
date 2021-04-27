/* 0xEBC0000 is 0x2000000 in IDA/Ghidra/Cemu. For any offset >= 0xEBC0000, subtract 0xCBC0000 to get its value in IDA/Ghidra/Cemu. */
/* 0x10502200 is 0x10000000 in IDA/Ghidra/Cemu. For any offset >= 0x10502200, subtract 0x502200 to get its value in IDA/Ghidra/Cemu. */

SECTIONS {

	/* Math */
	sin__Ff = 0xf6bdd40;
	cos__Ff = 0xf6be528;
	atan2__FfT1 = 0xf6be670;
	fmod__FfT1 = 0xf6bd97c;
	pow__FfT1 = 0xF6BDEA8;
	sqrt__Ff = 0xF6BDCCC;

	/* new/delete */
	__nw__FUi = 0xF5B1594;
	__nw__FUiPQ2_4sead4Heapi = 0xF5B1858;
	__nwa__FUi = 0xf5b1630;
	__nwa__FUiPQ2_4sead4Heapi = 0xF5B18DC;
	__dl__FPv = 0xF5B1748;
	__dla__FPv = 0xF5B17D0;

	/* GHS C++ FUNCTIONS */
	__pure_virtual_called = 0xF6BA554;
	__deleted_virtual_called = 0xf6ba5e8;
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
	__dt__Q2_4sead9IDisposerFv = 0xf5ca384;

	/* sead::Random */
	getU32__Q2_4sead6RandomFv = 0xf5d3780;

	/* sead::GlobalRandom */
	instance__Q2_4sead12GlobalRandom = 0x106ea26c;

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
	instance__8ActorMgr = 0x106c52c8;
	create__8ActorMgrFP14ActorBuildInfoUi = 0xebc9a58;
	createActor__8ActorMgrFP14ActorBuildInfoUi = 0xEBC9A58;
	findActorByType__8ActorMgrFQ2_9ProfileId13ProfileIdTypePP9BaseActor = 0xEBC9B6C;

	/* ActorList */
	findById__9ActorListFPUi = 0xEBCA5C8;
	findActorById__9ActorListFPUi = 0xEBCA5C8;

	/* ActorMgr */
	sInstance__8ActorMgr = 0x106c52c8;
	create__8ActorMgrFP14ActorBuildInfoUi = 0xebc9a58;

	/* BaseActor */
	__vtbl__9BaseActor = 0x105028c0;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__9BaseActorSFv = 0x106EBEC4;
	typeInfo__L0__getRuntimeTypeInfoStatic__9BaseActorSFv = 0x106EBEC8;
	removeChild__9BaseActorFP9BaseActor = 0xEBC2C8C;
	beforeCreate__9BaseActorFv = 0xebc2f7c;
	onExecute__9BaseActorFv = 0xebc2f8c;
	finalExecute__9BaseActorFv = 0xebc2f94;
	onDraw__9BaseActorFv = 0xebc2fa0;
	afterDraw__9BaseActorFUi = 0xebc2f38;
	beforeDelete__9BaseActorFv = 0xebc2fa8;
	onDelete__9BaseActorFv = 0xebc2fb0;
	afterDelete__9BaseActorFUi = 0xebc2f3c;
	getProfileId__9BaseActorFv = 0xEBC2C80;

	/* Actor */
	__vtbl__5Actor = 0x10502468;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__5ActorSFv = 0x106EBEBC;
	typeInfo__L0__getRuntimeTypeInfoStatic__5ActorSFv = 0x106EBEC0;
	__ct__5ActorFPC14ActorBuildInfo = 0xebc0ac8;
	directionToPlayerH__5ActorFRC4Vec3 = 0xebc05ec;
	directionToActorH__5ActorFRC5Actor = 0xEBCC800;
	distanceToPlayer__5ActorFR4Vec2 = 0xebc05a4;
	deleteActorWhenOutOfView__5ActorFUi = 0xEBC07A0;
	actorAcCallback0__5ActorFP14ActiveColliderP4Vec2 = 0xED5E7E8;
	actorAcCallback2__5ActorFP14ActiveColliderP4Vec2 = 0xED5E8A4;
	actorCbCallback0__5ActorFP12ColliderBaseP4Vec2 = 0xED5E8B8;
	checkDerivedRuntimeTypeInfo__5ActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xebc2a38;
	getRuntimeTypeInfo__5ActorCFv = __deleted_virtual_called;
	__dt__5ActorFv = 0xebc0f18;
	afterCreate__5ActorFUi = 0xebc0fb8;
	beforeExecute__5ActorFv = 0xebc0fe8;
	afterExecute__5ActorFUi = 0xebc10bc;
	beforeDraw__5ActorFv = 0xebc11a0;
	removeActiveColliders__5ActorFv = 0xebc02cc;
	addActiveColliders__5ActorFv = 0xebc0328;
	killAtGoal__5ActorFv = 0xebc2ad8;
	splashWater__5ActorFP4Vec3 = 0xebc2adc;
	splashLava__5ActorFP4Vec3 = 0xebc2ae0;
	splashLavaWave__5ActorFP4Vec3 = 0xebc0960;
	splashPoison__5ActorFP4Vec3 = 0xebc2ae4;
	isOffScreen__5ActorFv = 0xebc1254;

	/* StageActor */
	__vtbl__10StageActor = 0x10502a4c;
	__ct__10StageActorFPC14ActorBuildInfo = 0xEBC2FB8;
	__dt__10StageActorFv = 0xEBC40B0;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x106EBED4;
	typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x106EBED8;
	handleGravity__10StageActorFv = 0xEBC39AC;
	handleSpeed__10StageActorFv = 0xEBC3AE4;
	afterCreate__10StageActorFUi = 0xebc354c;
	beforeExecute__10StageActorFv = 0xebc35fc;
	afterExecute__10StageActorFUi = 0xebc36d8;
	onDelete__10StageActorFv = 0xebc3724;
	setPlayerId__10StageActorFSc = 0xEBC3F10;
	vf114__10StageActorFv = __deleted_virtual_called;
	vf134__10StageActorFv = __deleted_virtual_called;
	vf13C__10StageActorFv = 0xebc4008;
	vf144__10StageActorFb = 0xebc375c;
	vf14C__10StageActorFP5Actor = 0xebc3760;

	/* ActorMultiState */
	__vtbl__15ActorMultiState = 0x10503248;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__15ActorMultiStateSFv = 0x106EBEE4;
	typeInfo__L0__getRuntimeTypeInfoStatic__15ActorMultiStateSFv = 0x106EBEE8;
	__ct__15ActorMultiStateFPC14ActorBuildInfo = 0xebcaa8c;
	checkDerivedRuntimeTypeInfo__15ActorMultiStateCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xebcaf94;

	/* BlockCoinBase */
	__vtbl__13BlockCoinBase = 0x10603c80;
	StateID_BlockCoinState3__13BlockCoinBase = 0x10722764;
	StateID_BumpUp2__13BlockCoinBase = 0x1072271C;
	checkDerivedRuntimeTypeInfo__13BlockCoinBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xf2c8dc0;
	vf18C__13BlockCoinBaseFv = 0xf2c8efc;
	vf194__13BlockCoinBaseFv = 0xf2c8f00;
	setBelowSensor__13BlockCoinBaseFv = 0xf2c8f04;
	vf1A4__13BlockCoinBaseFv = 0xf2c8f08;
	spawnItemUp__13BlockCoinBaseFv = 0xf2c8f0c;
	vf1B4__13BlockCoinBaseFv = 0xf2c8f10;
	vf1BC__13BlockCoinBaseFv = 0xf2c8f14;
	spawnItemDown__13BlockCoinBaseFv = 0xf2c8f18;
	vf1CC__13BlockCoinBaseFv = 0xf2c8f1c;
	vf1D4__13BlockCoinBaseFb = 0xf2c4868;
	vf1DC__13BlockCoinBaseFv = 0xf2c8f20;
	spawnCoinShower__13BlockCoinBaseFv = 0xf2c48e4;
	vf1EC__13BlockCoinBaseFv = 0xf2c8f28;
	beginState_BumpUp__13BlockCoinBaseFv = 0xf2c7cb4;
	executeState_BumpUp__13BlockCoinBaseFv = 0xf2c7cf0;
	endState_BumpUp__13BlockCoinBaseFv = 0xf2c8f2c;
	beginState_BlockCoinState1__13BlockCoinBaseFv = 0xf2c7d94;
	executeState_BlockCoinState1__13BlockCoinBaseFv = 0xf2c7da0;
	endState_BlockCoinState1__13BlockCoinBaseFv = 0xf2c8f30;
	beginState_BumpDown__13BlockCoinBaseFv = 0xf2c7db8;
	executeState_BumpDown__13BlockCoinBaseFv = 0xf2c7dfc;
	endState_BumpDown__13BlockCoinBaseFv = 0xf2c8f34;
	beginState_BlockCoinState2__13BlockCoinBaseFv = 0xf2c7e9c;
	executeState_BlockCoinState2__13BlockCoinBaseFv = 0xf2c7ea8;
	endState_BlockCoinState2__13BlockCoinBaseFv = 0xf2c8f38;
	beginState_BumpUp2__13BlockCoinBaseFv = 0xf2c7ed0;
	executeState_BumpUp2__13BlockCoinBaseFv = 0xf2c7f58;
	endState_BumpUp2__13BlockCoinBaseFv = 0xf2c8f3c;
	beginState_BumpDown2__13BlockCoinBaseFv = 0xf2c812c;
	executeState_BumpDown2__13BlockCoinBaseFv = 0xf2c8198;
	endState_BumpDown2__13BlockCoinBaseFv = 0xf2c8f40;
	beginState_BlockCoinState3__13BlockCoinBaseFv = 0xf2c828c;
	executeState_BlockCoinState3__13BlockCoinBaseFv = 0xf2c8298;
	endState_BlockCoinState3__13BlockCoinBaseFv = 0xf2c8f44;
	spawnPortableSpring__13BlockCoinBaseFv = 0xf2c6430;
	spawnVine__13BlockCoinBaseFv = 0xf2c62a8;
	spawnYoshiEgg__13BlockCoinBaseFb = 0xf2c6ba4;
	spawnPowerup__13BlockCoinBaseFP4Vec3UiT2b = 0xf2c6d1c;
	spawnMultiPowerup__13BlockCoinBaseFP4Vec3UiT2b = 0xf2c6ff4;

	/* MovementBlockCoinBase */
	__vtbl__21MovementBlockCoinBase = 0x106097ac;
	checkDerivedRuntimeTypeInfo__21MovementBlockCoinBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xf2e7a08;
	spawnItemUp__21MovementBlockCoinBaseFv = 0xf2e6610;
	spawnItemDown__21MovementBlockCoinBaseFv = 0xf2e6634;
	vf1DC__21MovementBlockCoinBaseFv = 0xf2e6644;
	vf1EC__13BlockCoinBaseFv = 0xf2e7980;
	vf29C__21MovementBlockCoinBaseFv = 0xf2e7984;
	setTileFlag__21MovementBlockCoinBaseFv = 0xf2e65bc;
	vf2AC__21MovementBlockCoinBaseFv = 0xf2e7988;
	vf2B4__21MovementBlockCoinBaseFv = 0xf2e7990;
	vf2BC__21MovementBlockCoinBaseFv = 0xf2e7994;
	vf2C4__21MovementBlockCoinBaseFv = 0xf2e7998;
	vf2CC__21MovementBlockCoinBaseFv = 0xf2e6654;
	registerColliderActiveInfo__21MovementBlockCoinBaseFv = 0xF2E6760;

	/* BlockBase */
	StateID_Wait__9BlockBase = 0x10720ae0;
	StateID_Used__9BlockBase = 0x10720b04;
	activeTopCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xF2C4ECC;
	activeBottomCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xF2C5528;
	activeSideCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xF2C5EFC;
	usedTopCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xf2c50f0;
	usedBottomCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xf2c595c;
	usedSideCollisionCallback__9BlockBaseSFP12ColliderBaseP12CollisionMgrUi = 0xf2c60c0;
	init__9BlockBaseFbT1 = 0xf25f6c8;
	initMover__9BlockBaseFv = 0xF25FB30;
	__vtbl__9BlockBase = 0x105e8b60;
	__ct__9BlockBaseFPC14ActorBuildInfo = 0xf25e614;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__9BlockBaseSFv = 0x106EBEF4;
	typeInfo__L0__getRuntimeTypeInfoStatic__9BlockBaseSFv = 0x106EBEF8;
	checkDerivedRuntimeTypeInfo__9BlockBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xf260460;
	getRuntimeTypeInfo__9BlockBaseCFv = __deleted_virtual_called;
	onExecute__9BlockBaseFv = 0xf25e6c4;
	onDraw__9BlockBaseFv = 0xf25e77c;
	setBelowSensor__9BlockBaseFv = 0xf25f400;
	spawnItemUp__9BlockBaseFv = 0xf25ebc0;
	spawnItemDown__9BlockBaseFv = 0xf25ebc4;
	vf1CC__9BlockBaseFv = 0xf25ec04;
	vf1EC__9BlockBaseFv = 0xF25F674;
	vf2C4__9BlockBaseFv = 0xf25f410;
	isActive__9BlockBaseFv = 0xf25ec1c;
	vf2DC__9BlockBaseFv = 0xf260404;
	getContent__9BlockBaseFv = 0xf260408;
	vf2EC__9BlockBaseFv = 0xf25efe4;
	vf2F4__9BlockBaseFPv = 0xf260418;
	execute__9BlockBaseFv = 0xf25f078;
	destroy__9BlockBaseFv = 0xf25f25c;
	destroy2__9BlockBaseFv = 0xf25f33c;
	vf314__9BlockBaseFv = 0xf260434;
	vf31C__9BlockBaseFv = 0xf260438;
	vf324__9BlockBaseFv = 0xf26043c;
	vf32C__9BlockBaseFv = 0xf260440;
	beginState_Wait__9BlockBaseFv = 0xf26061c;
	executeState_Wait__9BlockBaseFv = 0xf260068;
	endState_Wait__9BlockBaseFv = 0xf260620;
	beginState_Used__9BlockBaseFv = 0xf260624;
	executeState_Used__9BlockBaseFv = 0xf260074;
	endState_Used__9BlockBaseFv = 0xf260628;

	/* Enemy */
	StateID_DieFumi__5Enemy = 0x107031B0;
	__vtbl__5Enemy = 0x1057429C;
	__ct__5EnemyFPC14ActorBuildInfo = 0xeee8494;
	collisionCallback__5EnemySFP14ActiveColliderT1 = 0xeee8c50;
	processCollision__5EnemyFP14ActiveColliderT1Ui = 0xEEE9B88;
	killPlayerJump__5EnemyFP5ActorRC4Vec2P9StateBase = 0xEEEDA34;
	killPlayerSpin__5EnemyFP5Actor = 0xEEECC98;
	killYoshiStomp__5EnemyFP5Actor = 0xEEED31C;
	__dt__5EnemyFv = 0xeeea868;
	checkDerivedRuntimeTypeInfo__5EnemyCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xeeea70c;
    getRuntimeTypeInfo__5EnemyCFv = __deleted_virtual_called;
	beforeExecute__5EnemyFv = 0xeee8644;
	damageFromUnder__5EnemyFv = 0xeee8914;
	vf14C__5EnemyFP5Actor = 0xeeedc88;
	vf154__5EnemyFv = 0xeeee1a4;
	doStateChange__5EnemyFP9StateBase = 0xeef0404;
	vf18C__5EnemyFv = 0xeeea848;
	damagePlayer__5EnemyFP14ActiveColliderT1 = 0xeee8b84;
	vf19C__5EnemyFv = 0xeee910c;
	freeze__5EnemyFv = 0xeef04f8;
	vf1AC__5EnemyFv = 0xeef10bc;
	vf1B4__5EnemyFv = 0xeef10c0;
	vf1BC__5EnemyFv = 0xeef0568;
	vf1C4__5EnemyFv = 0xeeea858;
	vf1CC__5EnemyFv = 0xeeea85c;
	vf1D4__5EnemyFP14ActiveColliderT1 = 0xeee91f8;
	vf1DC__5EnemyFP14ActiveColliderT1 = 0xeee9250;
	vf1E4__5EnemyFRbP14ActiveColliderT2 = 0xeee9520;
	vf1EC__5EnemyFP14ActiveColliderT1 = 0xeee9578;
	vf1F4__5EnemyFP14ActiveColliderT1 = 0xeee957c;
	vf1FC__5EnemyFP14ActiveColliderT1 = 0xeee96e8;
	vf204__5EnemyFP14ActiveColliderT1 = 0xeee9800;
	collisionEnemy__5EnemyFP14ActiveColliderT1 = 0xeee99f0;
	collisionPlayer__5EnemyFP14ActiveColliderT1 = 0xeee99f4;
	collisionYoshi__5EnemyFP14ActiveColliderT1 = 0xeee9a04;
	vf224__5EnemyFP14ActiveColliderT1 = 0xeee9a08;
	collisionStar__5EnemyFP14ActiveColliderT1 = 0xeeece84;
	collisionSlide__5EnemyFP14ActiveColliderT1 = 0xeeecf20;
	collisionPropellerDrill__5EnemyFP14ActiveColliderT1 = 0xeeed014;
	vf244__5EnemyFP14ActiveColliderT1 = 0xeeed0e4;
	collisionGroundPound__5EnemyFP14ActiveColliderT1 = 0xeeed240;
	collisionGroundPoundYoshi__5EnemyFP14ActiveColliderT1 = 0xeeed3b4;
	collisionPenguinSlide__5EnemyFP14ActiveColliderT1 = 0xeeed48c;
	collisionPipeCannon__5EnemyFP14ActiveColliderT1 = 0xeeed49c;
	vf26C__5EnemyFP14ActiveColliderT1 = 0xeeed56c;
	collisionThrowableObject__5EnemyFP14ActiveColliderT1 = 0xeeed57c;
	collisionFireball__5EnemyFP14ActiveColliderT1 = 0xeeed70c;
	collisionIceball__5EnemyFP14ActiveColliderT1 = 0xeeed7a4;
	collisionHammer__5EnemyFP14ActiveColliderT1 = 0xeeed824;
	collisionFireballYoshi__5EnemyFP14ActiveColliderT1 = 0xeeed938;
	vf29C__5EnemyFP14ActiveColliderT1 = 0xeeeda04;
	vf2A4__5EnemyFP14ActiveColliderT1 = 0xeeeda0c;
	vf2AC__5EnemyFP14ActiveColliderT1 = 0xeeeda14;
	vf2B4__5EnemyFP14ActiveColliderT1 = 0xeeeda24;
	vf2BC__5EnemyFv = 0xeeedaf0;
	vf2C4__5EnemyFv = 0xeeedd48;
	vf2CC__5EnemyFv = 0xeeee048;
	isOnGround__5EnemyFv = 0xeeee2ec;
	vf2DC__5EnemyFv = 0xeeee2f8;
	vf2E4__5EnemyFv = 0xeeee358;
	vf2EC__5EnemyFv = 0xeee9ea4;
	vf2F4__5EnemyFv = 0xeee9fa8;
	vf2FC__5EnemyFv = 0xeee9fac;
	vf304__5EnemyFv = 0xeee9fb0;
	vf30C__5EnemyFv = 0xeee9fc0;
	vf314__5EnemyFv = 0xeeea094;
	vf31C__5EnemyFv = 0xeeea118;
	vf324__5EnemyFv = 0xeeea1bc;
	vf32C__5EnemyFv = 0xeeea240;
	vf334__5EnemyFv = 0xeeea24c;
	vf33C__5EnemyFv = 0xeeea250;
	vf344__5EnemyFv = 0xeeea2d4;
	vf34C__5EnemyFv = 0xeeea2e4;
	vf354__5EnemyFv = 0xeeea2fc;
	vf35C__5EnemyFv = 0xeeea364;
	vf364__5EnemyFv = 0xeeea418;
	vf36C__5EnemyFv = 0xeeea4cc;
	vf374__5EnemyFv = 0xeeea864;
	beginState_DieFumi__5EnemyFv = 0xeeee518;
	executeState_DieFumi__5EnemyFv = 0xeeee5e8;
	endState_DieFumi__5EnemyFv = 0xeeeeed0;
	beginState_DieFall__5EnemyFv = 0xeeee63c;
	executeState_DieFall__5EnemyFv = 0xeeee640;
	endState_DieFall__5EnemyFv = 0xeeeeed4;
	vf3AC__5EnemyFv = 0xeeee72c;
	vf3B4__5EnemyFv = 0xeeee79c;
	vf3BC__5EnemyFv = 0xeeeeed8;
	vf3C4__5EnemyFv = 0xeeee7a8;
	vf3CC__5EnemyFv = 0xeeee7b8;
	vf3D4__5EnemyFv = 0xeeeeedc;
	vf3DC__5EnemyFv = 0xeeee7c4;
	vf3E4__5EnemyFv = 0xeeee7c8;
	vf3EC__5EnemyFv = 0xeeeeee0;
	vf3F4__5EnemyFv = 0xeeee7d4;
	vf3FC__5EnemyFv = 0xeeeeee4;
	vf404__5EnemyFv = 0xeeeeee8;
	vf40C__5EnemyFv = 0xeeee7e0;
	vf414__5EnemyFv = 0xeeeeeec;
	vf41C__5EnemyFv = 0xeeeeef0;
	vf424__5EnemyFv = 0xeef05e4;
	vf42C__5EnemyFv = 0xeef05ec;
	vf434__5EnemyFv = 0xeef10c4;
	vf43C__5EnemyFv = 0xeef10c8;
	vf444__5EnemyFv = 0xeef10cc;
	vf44C__5EnemyFv = 0xeef10d0;
	vf454__5EnemyFv = 0xeef10d4;
	vf45C__5EnemyFv = 0xeef10d8;
	vf464__5EnemyFv = 0xeef10dc;
	vf46C__5EnemyFv = 0xeef06e8;
	vf474__5EnemyFv = 0xeef06f0;
	vf47C__5EnemyFv = 0xeef10e0;
	vf484__5EnemyFv = 0xeef10e4;
	vf48C__5EnemyFv = 0xeef10e8;
	vf494__5EnemyFv = 0xeef10ec;
	vf49C__5EnemyFv = 0xeef10f0;
	vf4A4__5EnemyFv = 0xeef10f4;
	vf4AC__5EnemyFv = 0xeef10f8;
	vf4B4__5EnemyFv = 0xeef10fc;
	vf4BC__5EnemyFv = 0xeef1100;
	vf4C4__5EnemyFv = 0xeef1104;
	beginState_Ice__5EnemyFv = 0xeef0720;
	executeState_Ice__5EnemyFv = 0xeef07a0;
	endState_Ice__5EnemyFv = 0xeef0944;

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
	vf634__4BossFP10StageActor = 0xEBEDDD8;
	vf63C__4BossFP10StageActor = 0xEBEDDE4;
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

	/* WindGeneratorBase */
	__vtbl__13WindGenerator = 0x106582A8;
	__dt__17WindGeneratorBaseFv = 0xF44F044;
	onCreate__17WindGeneratorBaseFv = 0xF44EC68;
	onExecute__17WindGeneratorBaseFv = 0xF44ED94;

	/* ActiveCollider */
	__ct__14ActiveColliderFv = 0xED5A960;
	__dt__14ActiveColliderFv = 0xED5AB90;
	__CPR59__init__14ActiveColliderFP5ActorPCQ2_J6J4InfoPPv = 0xed5af1c;
	Default__Q2_14ActiveCollider4Info = 0x10543DC0;

	/* ColliderBase */
	setType__12ColliderBaseFQ2_12ColliderBase5Types = 0xED65A70;
	__CPR62__setSurfaceType__12ColliderBaseFQ2_J16J12SurfaceTypes = 0xED65AD0;

	/* ColliderBase::Node */
	__ct__Q2_12ColliderBase4NodeFv = 0xED61ACC;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__12ColliderBaseSFv = 0x106EBF2C;
	typeInfo__L0__getRuntimeTypeInfoStatic__12ColliderBaseSFv = 0x106EC1A4;

	/* ShapedCollider */
	__ct__14ShapedColliderFiP4Vec2PQ2_12ColliderBase4NodeT3 = 0xED67904;
	init__14ShapedColliderFP5ActorRCQ2_14ShapedCollider4Info = 0xed6d3bc;
	execute__14ShapedColliderFv = 0xED6871C;
	__dt__14ShapedColliderFv = 0xED67A04;
	setRect__14ShapedColliderFP4Vec2T1 = 0xed6d25c;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__14ShapedColliderSFv = 0x106EBF30;
	typeInfo__L0__getRuntimeTypeInfoStatic__14ShapedColliderSFv = 0x106EC1B4;

	/* RectCollider */
	__vtbl__12RectCollider = 0x105FDA20;

	/* SolidOnTopCollider */
	__ct__18SolidOnTopColliderFv = 0xED61D38;
	__CPR79__init__18SolidOnTopColliderFP5ActorRCQ2_J6J4InfoiPQ2_4sead4Heap = 0xED62378;
	execute__18SolidOnTopColliderFv = 0xED62E0C;
	__dt__18SolidOnTopColliderFv = 0xED61F18;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__18SolidOnTopColliderSFv = 0x106EBF48;
	typeInfo__L0__getRuntimeTypeInfoStatic__18SolidOnTopColliderSFv = 0x106EC1A8;

	/* ColliderMgr */
	instance__11ColliderMgr = 0x106CB560;
	add__11ColliderMgrFP12ColliderBase = 0xED5269C;
	remove__11ColliderMgrFP12ColliderBase = 0xED5282C;

	/* EnemyFreezeMgr */
	freeze__14EnemyFreezeMgrFRCQ2_14EnemyFreezeMgr4InfoUi = 0xEF3D63C;
	setFlags__14EnemyFreezeMgrFRCQ2_14EnemyFreezeMgr5Flags = 0xEF3CB94;

	/* StateBase */
	currentId__9StateBase = 0x106ec104;
	NullState__9StateBase = 0x1072F590;

	/* StateMgr */
	execute__8StateMgrFv = 0xf584a80;
	changeState__8StateMgrFP9StateBase = 0xF584AF0;

	/* CollisionMgr */
	instance__12CollisionMgr = 0x106CB7D8;
	addCollider__12CollisionMgrFP8Collider = 0xED5E028;
	__dt__12CollisionMgrFv = 0xED4ADFC;
	init__12CollisionMgrFP5ActorPCQ2_12CollisionMgr6SensorN22 = 0xED4AF6C;
	setSensor__12CollisionMgrFPCQ2_12CollisionMgr6SensorUi = 0xED4AEFC;
	getSensor__12CollisionMgrCFUi = 0xED4CE74;
	process__12CollisionMgrFv = 0xED4D954;

	/* EventMgr */
	instance__8EventMgr = 0x106dd26c;
	set__8EventMgrFUiT1bN41 = 0xF25CD68;

	/* MusicPlayer */
	shouldHurryUp__11MusicPlayerFv = 0xF5783D8;

	/* ResArchive */
	getModel__10ResArchiveFRCQ2_4sead23SafeStringBase__tm__2_cUiN42bPQ2_4sead4Heap = 0xf0ae440;

	/* ResArchiveMgr */
	instance__13ResArchiveMgr = 0x106d4f50;
	get__13ResArchiveMgrFRCQ2_4sead23SafeStringBase__tm__2_c = 0xf0b60ec;

	/* ModelWrapper */
	__ct__12ModelWrapperFP5ModelUiN42 = 0xf094798;
	setup__12ModelWrapperFP10ResArchivePvPQ2_4sead4Heap = 0xf0949a0;
	updateModel__12ModelWrapperFv = 0xf094e84;
	updateAnimations__12ModelWrapperFv = 0xf094d20;

	/* Mtx34 */
	rotateAndTranslate__5Mtx34FRC5Vec3uRC4Vec3 = 0xebfc1c8;

	/* Animation */
	setRepeat__9AnimationFb = 0xF09EED4;

	/* SkeletalAnimation */
	play__17SkeletalAnimationFP10ResArchiveRCQ2_4sead23SafeStringBase__tm__2_c = 0xf0bdadc;

	/* TextureAnimation */
	play__16TextureAnimationFP10ResArchiveRCQ2_4sead23SafeStringBase__tm__2_c = 0xf0cb1ec;

	/* DrawMgr */
	instance__7DrawMgr = 0x106d4f88;
	drawModel__7DrawMgrFP5Model = 0xf0bab58;
	drawModel__7DrawMgrFP12ModelWrapper = 0xf0bac98;
	drawTile__7DrawMgrFUsRC4Vec3RCUiT2 = 0xf0bad28;

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
	spawn__6EffectSFiP4Vec3P5Vec3uT2 = 0xee6b080;

	/* EffectWrapper */
	__ct__13EffectWrapperFv = 0xee6b868;
	update__13EffectWrapperFiP4Vec3P5Vec3uT2 = 0xee6b52c;

	/* SoundSystemBase */
	getAudioFx__15SoundSystemBaseFv = 0xF571AA4;

	/* SoundSystem */
	sInstance__11SoundSystem = 0x106E9E84;
	getSoundArchive__11SoundSystemFv = 0xf573ba8;

	/* AudioFx */
	getReverbHiParam__7AudioFxFv = 0xF572FD8;
	getDelayParam__7AudioFxFv = 0xF572FE0;

    /* Level */
	instance__5Level = 0x106dd248;
	getArea__5LevelFUi = 0xf25a2dc;
	instance__10LevelTimer = 0x106D37F4;
	addTime__10LevelTimerFi = 0xF0814C0;

	/* Level::Area */
	getSprite__Q2_5Level4AreaFUiPv = 0xF259C08;
	getLocation__Q2_5Level4AreaFP4RectUc = 0xf25a020;
	getPath__Q2_5Level4AreaFUc = 0xf25a0a8;
	getPathNodes__Q2_5Level4AreaFUi = 0xf25a0f4;

	/* LevelInfo */
	instance__9LevelInfo = 0x106D3AEC;

	/* nw::snd::SoundArchive */
	GetItemLabel__Q3_2nw3snd12SoundArchiveCFUi = 0xf696980;

	/* BasicSoundActor */
	GlobalBasicSoundActorA = 0x106c85d0;
	instance__15BasicSoundActor = 0x106C85D0;
	playSound__15BasicSoundActorFPCcP4Vec2Ui = 0xF57EDEC;

	/* Level */
	sInstance__5Level = 0x106dd248;
	getArea__5LevelFUi = 0xf25a2dc;

	/* Level::Area */
	getSprite__Q2_5Level4AreaFUiPv = 0xF259C08;
	getLocation__Q2_5Level4AreaFP4RectUc = 0xf25a020;
	getPath__Q2_5Level4AreaFUc = 0xf25a0a8;
	getPathNodes__Q2_5Level4AreaFUi = 0xf25a0f4;

	/* LevelInfo */
	sInstance__9LevelInfo = 0x106D3AEC;

	/* LevelCamera */
	sInstance__11LevelCamera = 0x106E9E54;

	/* LevelTimer */
	sInstance__10LevelTimer = 0x106D37F4;
	setTime__10LevelTimerFi = 0xF08134C;
	addTime__10LevelTimerFi = 0xF0814C0;

	/* TileMgr */
	instance__7TileMgr = 0x106DCD94;
	getTilePtrCurrentArea__7TileMgrSFUsT1UcPUi = 0xF245000;

	/* PlayerMgr */
	instance__9PlayerMgr = 0x106E8B94;

	/* RDashMgr */
	sInstance__8RDashMgr = 0x106E9F9C;

	/* CourseTask */
	sInstance__10CourseTask = 0x106D37F0;

	/* TaskMgr */
	sInstance__7TaskMgr = 0x106E9D28;
	startLevel__7TaskMgrFPQ2_4sead8TaskBaseUcT2 = 0xF5541D0;
	changeTask__7TaskMgrFPQ2_4sead8TaskBaseRQ2_4sead11TaskClassIDUiT3 = 0xF554164;

	/* TwoWayPlatform */
	cbCallback4__14TwoWayPlatformSFP5Actor = 0xF3FFBAC;
	cbCallback5__14TwoWayPlatformSFP5Actor = 0xF3FFBE0;
	cbCallback6__14TwoWayPlatformSFP5ActorUiT2 = 0xF3FFC14;
	twoWayPlatformCbCallback2__14TwoWayPlatformFP12ColliderBaseP4Vec2 = 0xF40184C;

	/* ResMgr */
	ResMgr_LoadLevelResource = 0xF592A20;
	ResMgr_LoadLevelArchiveSuccess = 0xF593354;
	ResMgr_LoadLevelArchiveFail = 0xF59333C;

    /* RDashMgr */
    instance__8RDashMgr = 0x106E9F9C;

	/* TODO: THIS IS WRONG!!!!!!!! Input */
	instance__8InputMgr = 0x106D4FF8;
	getTilt__10ControllerFPUif = 0xF0CED50;

	/* TerrainEffects */
	__CPR79__init__14TerrainEffectsFP4Vec3fbT3Q2_J6J11TerrainTypePQ2_4sead4Heap = 0xF477378;
	setWaveValues__14TerrainEffectsFUiN51 = 0xF477598;
	checkMarioWaveHit__14TerrainEffectsFv = 0xF478C98;
	updateWaveCollisions__14TerrainEffectsFv = 0xF478E00;

	/* EnvTerrain */
	onExecute__10EnvTerrainFv = 0xF2B0F40;
	setTop__10EnvTerrainFf = 0xF2B131C;

	/* Misc */
	mapPositionToScreen__FR4Vec2RC4Vec2 = 0xebe9368;
	mapPosToScreen__FP4Vec2T1 = 0xEBE9368;
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
