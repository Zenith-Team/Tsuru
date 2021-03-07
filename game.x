/* 0xEBC0000 is 0x2000000 in IDA/Ghidra/Cemu. For any offset >= 0xEBC0000, subtract 0xCBC0000 to get its value in IDA/Ghidra/Cemu. */
/* 0x10502200 is 0x10000000 in IDA/Ghidra/Cemu. For any offset >= 0x10502200, subtract 0x502200 to get its value in IDA/Ghidra/Cemu. */

SECTIONS {

	/* Math */
	sin__Ff = 0xf6bdd40;
	cos__Ff = 0xf6be528;

	/* new/delete */
	__nw__FUi = 0xF5B1594;
	__nwa__FUi = 0xf5b1630;
	__nwa__FUiPQ2_4sead4Heapi = 0xF5B18DC;
	__dl__FPv = 0xF5B1748;
	__dla__FPv = 0xF5B17D0;

	/* GHS C++ FUNCTIONS */
	__pure_virtual_called = 0xF6BA554;
	__deleted_virtual_called = 0xf6ba5e8;
	__vec_new = 0xF6BA350;

	/* sead::IDisposer */
	__ct__Q2_4sead9IDisposerFv = 0xF5CA2FC;
	__dt__Q2_4sead9IDisposerFv = 0xf5ca384;

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

	/* sead::Endian */
	cHostEndian__Q2_4sead6Endian = 0x10AECC78;
	cConvFuncTable__Q2_4sead6Endian = 0x10694BA8;

	/* Profile */
	__ct__7ProfileFPFPC14ActorBuildInfo_P4BaseUiRCQ2_4sead23SafeStringBase__tm__2_cPC9ActorInfoT2 = 0xEBD9554;
	get__7ProfileSFUi = 0xEBD9774;
	spriteToProfileList__7Profile = 0x106EEF8C;
	hasResourcesOriginal__7Profile = 0x10504264;
	resourceCountOriginal__7Profile = 0x105045F8;
	resourceListsOriginal__7Profile = 0x106C541C;

	/* ActorMgr */
	instance__8ActorMgr = 0x106c52c8;
	create__8ActorMgrFP14ActorBuildInfoUi = 0xebc9a58;

	/* Base */
	__vtbl__4Base = 0x105028c0;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__4BaseSFv = 0x106EBEC4;
	typeInfo__L0__getRuntimeTypeInfoStatic__4BaseSFv = 0x106EBEC8;
	beforeCreate__4BaseFv = 0xebc2f7c;
	onExecute__4BaseFv = 0xebc2f8c;
	finalExecute__4BaseFv = 0xebc2f94;
	onDraw__4BaseFv = 0xebc2fa0;
	afterDraw__4BaseFUi = 0xebc2f38;
	beforeDelete__4BaseFv = 0xebc2fa8;
	onDelete__4BaseFv = 0xebc2fb0;
	afterDelete__4BaseFUi = 0xebc2f3c;

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
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x106EBED4;
	typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x106EBED8;
	handleGravity__10StageActorFv = 0xEBC39AC;
	handleSpeed__10StageActorFv = 0xEBC3AE4;
	afterCreate__10StageActorFUi = 0xebc354c;
	beforeExecute__10StageActorFv = 0xebc35fc;
	afterExecute__10StageActorFUi = 0xebc36d8;
	onDelete__10StageActorFv = 0xebc3724;
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

	/* StateBase */
	currentId__9StateBase = 0x106ec104;
	NullState__9StateBase = 0x1072F590;

	/* StateMgr */
	execute__8StateMgrFv = 0xf584a80;
	changeState__8StateMgrFP9StateBase = 0xF584AF0;

	/* CollisionMgr */
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
	updateAnimations__12ModelWrapperFv = 0xf094d20;
	updateModel__12ModelWrapperFv = 0xf094e84;

	/* Mtx34 */
	rotateAndTranslate__5Mtx34FRC5Vec3uRC4Vec3 = 0xebfc1c8;

	/* DrawMgr */
	instance__7DrawMgr = 0x106d4f88;
	drawModel__7DrawMgrFP5Model = 0xf0bab58;
	drawModel__7DrawMgrFP12ModelWrapper = 0xf0bac98;
	drawTile__7DrawMgrFUsRC4Vec3RCUiT2 = 0xf0bad28;

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
	instance__11SoundSystem = 0x106E9E84;

	/* AudioFx */
	getReverbHiParam__7AudioFxFv = 0xF572FD8;
	getDelayParam__7AudioFxFv = 0xF572FE0;

	/* Level */
	instance__5Level = 0x106dd248;
	getArea__5LevelFUi = 0xf25a2dc;

	/* Level::Area */
	getSprite__Q2_5Level4AreaFUiPv = 0xF259C08;
	getLocation__Q2_5Level4AreaFP4RectUc = 0xf25a020;
	getPath__Q2_5Level4AreaFUc = 0xf25a0a8;
	getPathNodes__Q2_5Level4AreaFUi = 0xf25a0f4;

	/* LevelInfo */
	instance__9LevelInfo = 0x106D3AEC;

	/* TileMgr */
	getTilePtrCurrentArea__7TileMgrSFUsT1UcPUi = 0xF245000;

	/* PlayerMgr */
	instance__9PlayerMgr = 0x106E8B94;

	/* TwoWayPlatform */
	cbCallback4__14TwoWayPlatformSFP5Actor = 0xF3FFBAC;
	cbCallback5__14TwoWayPlatformSFP5Actor = 0xF3FFBE0;
	cbCallback6__14TwoWayPlatformSFP5ActorUiT2 = 0xF3FFC14;
	twoWayPlatformCbCallback2__14TwoWayPlatformFP12ColliderBaseP4Vec2 = 0xF40184C;

	/* BasicSoundActor */
	GlobalBasicSoundActorA = 0x106c85d0;
	playSound__15BasicSoundActorFPCcP4Vec2Ui = 0xf57ed48;

	/* Misc */
	mapPositionToScreen__FR4Vec2RC4Vec2 = 0xebe9368;
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

}