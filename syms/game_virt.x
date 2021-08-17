SECTIONS {

/* Math */
	sinf__Ff = 0x2afdd40;
	cosf__Ff = 0x2afe528;
	atan2f__FfT1 = 0x2afe670;
	fmodf__FfT1 = 0x2afd97c;
	powf__FfT1 = 0x2afdea8;
	sqrtf__Ff = 0x2afdccc;

/* new/delete */
	__nw__FUi = 0x29f1594;
	__nw__FUiPQ2_4sead4Heapi = 0x29f1858;
	__nwa__FUi = 0x29f1630;
	__nwa__FUiPQ2_4sead4Heapi = 0x29f18dc;
	__dl__FPv = 0x29f1748;
	__dla__FPv = 0x29f17d0;

/* GHS C++ Functions */
	__pure_virtual_called = 0x2afa554;
	__deleted_virtual_called = 0x2afa5e8;
	__vec_new = 0x2afa350;
	__vec_delete = 0x2afa490;
	__record_needed_destruction = 0x2afa52c;
	__gh_float_printf = 0x2afaba8;
	__gh_long_long_printf = 0x2afab84;
	__gh_memclr32 = 0x2aff1e0;
	__ghs_strcmp = 0x2afa60c;
	__memzero = 0x2afa55c;
	vsnprintf = 0x2afbd54;

/* GHS C Functions */
	_f_ftoll = 0x2AFEBFC;

/* Cafe SDK Static */
	ASM_MTXConcat = 0x2af98a0;
	GFDGetPixelShaderCount = 0x2AF8C10;
	GFDGetPixelShaderHeaderSize = 0x2AF8D10;
	GFDGetPixelShaderProgramSize = 0x2AF8D40;
	GFDGetPixelShader = 0x2AF8FC0;
	GFDGetVertexShaderCount = 0x2AF8C04;
	GFDGetVertexShaderHeaderSize = 0x2AF8D00;
	GFDGetVertexShaderProgramSize = 0x2AF8D40;
	GFDGetVertexShader = 0x2AF8E3C;

/* sead::FileDeviceMgr */
	sInstance__Q2_4sead13FileDeviceMgr = 0x101E7F18
	tryLoad__Q2_4sead13FileDeviceMgrFRQ3_4sead10FileDevice7LoadArg = 0x29f8bbc;

/* sead::GlobalRandom */
    sInstance__Q2_4sead12GlobalRandom = 0x101e806c;

/* sead::IDisposer */
	__ct__Q2_4sead9IDisposerFv = 0x2a0a2fc;
	__dt__Q2_4sead9IDisposerFv = 0x2a0a384;

/* sead::PrimitiveRenderer */
	sInstance__Q2_4sead17PrimitiveRenderer = 0x101e8010;
	setCamera__Q2_4sead17PrimitiveRendererFRCQ2_4sead6Camera = 0x2a083d0;
	setProjection__Q2_4sead17PrimitiveRendererFRCQ2_4sead10Projection = 0x2a083e4;
	begin__Q2_4sead17PrimitiveRendererFv = 0x2a08408;
	end__Q2_4sead17PrimitiveRendererFv = 0x2a0841c;

/* sead::PrimitiveRendererCafe */
	drawTriangles___Q2_4sead21PrimitiveRendererCafeFRC5Mtx34RCQ2_4sead7Color4fT2PQ3_4sead21PrimitiveRendererUtil6VertexUiPUsT5PC11_GX2Texture = 0x2a0a190;

/* sead::Random */
	getU32__Q2_4sead6RandomFv = 0x2a13780;

/* ActorBase */
	__vtbl__9ActorBase = 0x100006c0;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__9ActorBaseSFv = 0x101e9cc4;
	typeInfo__L0__getRuntimeTypeInfoStatic__9ActorBaseSFv = 0x101e9cc8;
	removeChild__9ActorBaseFP9ActorBase = 0x2002c8c;
	beforeCreate__9ActorBaseFv = 0x2002f7c;
	afterCreate__9ActorBaseFUi = 0x2002f00;
	beforeExecute__9ActorBaseFv = 0x2002f04;
	onExecute__9ActorBaseFv = 0x2002f8c;
	afterExecute__9ActorBaseFUi = 0x2002f34;
	finalExecute__9ActorBaseFv = 0x2002f94;
	beforeDraw__9ActorBaseFv = 0x2002f98;
	onDraw__9ActorBaseFv = 0x2002fa0;
	afterDraw__9ActorBaseFUi = 0x2002f38;
	beforeDelete__9ActorBaseFv = 0x2002fa8;
	onDelete__9ActorBaseFv = 0x2002fb0;
	afterDelete__9ActorBaseFUi = 0x2002f3c;
	getProfileID__9ActorBaseFv = 0x2002c80;

/* ActorBuffer */
	findActorByID__11ActorBufferFPUi = 0x200a5c8;

/* ActorInfo */
	sDefault__9ActorInfo = 0x100018F4;

/* ActorMgr */
	sInstance__8ActorMgr = 0x101c30c8;
	create__8ActorMgrFP14ActorBuildInfoUi = 0x2009a58;
	findActorByType__8ActorMgrFQ2_9ProfileId13ProfileIdTypePP9ActorBase = 0x2009b6c;

/* Animation */
	setRepeat__9AnimationFb = 0x24deed4;
	reset__9AnimationFv = 0x24deeac;

/* AreaTask */
	drawLayer3D__8AreaTaskFRCQ3_3agl3lyr10RenderInfo = 0x24b84a8;

/* ApplicationTask */
	sInstance__15ApplicationTask = 0x101e7d40; 

/* ColliderBase */
	__ct__Q2_12ColliderBase4NodeFv = 0x21a1acc;

/* ColliderMgr */
	sInstance__11ColliderMgr = 0x101c9360;
	add__11ColliderMgrFP12ColliderBase = 0x219269c;
	remove__11ColliderMgrFP12ColliderBase = 0x219282c;

/* CourseTask */
	sInstance__10CourseTask = 0x101d15f0;

/* CourseSelectActor */
	__ct__17CourseSelectActorFPC14ActorBuildInfo = 0x21d4cb4;
	__dt__17CourseSelectActorFv = 0x21d5838;
	checkDerivedRuntimeTypeInfo__17CourseSelectActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x21d588c;
	getRuntimeTypeInfo__17CourseSelectActorCFv = __deleted_virtual_called;
	beforeExecute__17CourseSelectActorFv = 0x21d4d60;
	beforeDraw__17CourseSelectActorFv = 0x21d4db8;
	vf8C__17CourseSelectActorFv = 0x21d5948;
	vf94__17CourseSelectActorFv = 0x21d5950;
	vf9C__17CourseSelectActorFv = 0x21d595c;
	vfA4__17CourseSelectActorFv = 0x21d5968;

/* CourseSelectTask */
	sInstance__16CourseSelectTask = 0x101cc96c;
	drawLayer3D__16CourseSelectTaskFRCQ3_3agl3lyr10RenderInfo = 0x22676a4;

/* CSPlayerMgr */
	sInstance__11CSPlayerMgr = 0x101cc30c;

/* CSCollisionActor */
	__ct__16CSCollisionActorFPC14ActorBuildInfo = 0x21d596c;
	__dt__16CSCollisionActorFv = 0x21d60ec;
	checkDerivedRuntimeTypeInfo__16CSCollisionActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x21d5ff0;
	getRuntimeTypeInfo__16CSCollisionActorCFv = __deleted_virtual_called;
	vf8C__16CSCollisionActorFv = 0x21d5fcc;
	vf94__16CSCollisionActorFv = 0x21d5fd4;
	vf9C__16CSCollisionActorFv = 0x21d5fe0;
	vfA4__16CSCollisionActorFv = 0x21d5fec;
	vfAC__16CSCollisionActorFv = 0x21d614c;
	vfB4__16CSCollisionActorFv = 0x21d6150;
	vfBC__16CSCollisionActorFv = 0x21d6158;
	vfC4__16CSCollisionActorFdP13Vec3__tm__2_f = 0x21d6160;
	vfCC__16CSCollisionActorFv = 0x21d6180;
	vfD4__16CSCollisionActorFv = 0x21d6184;
	vfDC__16CSCollisionActorFv = 0x21d618c;
	vfE4__16CSCollisionActorFv = 0x21d6198;
	vfEC__16CSCollisionActorFv = 0x21d61a0;
	vfF4__16CSCollisionActorFP13Vec3__tm__2_f = 0x21d5d4c;
	vfFC__16CSCollisionActorFv = 0x21d5d5c;
	vf104__16CSCollisionActorFUi = 0x21d5e40;
	vf10C__16CSCollisionActorFv = 0x21d5e54;
	vf114__16CSCollisionActorFv = 0x21d5f08;
	vf11C__16CSCollisionActorFv = 0x21d61a8;
	vf124__16CSCollisionActorFv = 0x21d61c0;

/* CSHitboxCollider */
	__CPR72__init__16CSHitboxColliderFP16CSCollisionActorPCQ2_J6J4Info = 0x21c5634;

/* CSHitboxColliderMgr */
	sInstance__19CSHitboxColliderMgr = 0x101c9758;
	add__19CSHitboxColliderMgrFP16CSHitboxCollider = 0x21c5800;
	FUN_21c5894__19CSHitboxColliderMgrFP16CSHitboxCollider = 0x21c5894;

/* CSSomethingActor */
	__ct__16CSSomethingActorFPC14ActorBuildInfo = 0x2201c04;
	__dt__16CSSomethingActorFv = 0x2201d08;
	checkDerivedRuntimeTypeInfo__16CSSomethingActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x2201d5c;
	getRuntimeTypeInfo__16CSSomethingActorCFv = __deleted_virtual_called;
	vf8C__16CSSomethingActorFv = 0x2201ce4;
	vf94__16CSSomethingActorFv = 0x2201cec;
	vf9C__16CSSomethingActorFv = 0x2201cf8;
	vfA4__16CSSomethingActorFv = 0x2201d04;

/* DoorBase */
	__ct__8DoorBaseFPC14ActorBuildInfo = 0x27583f0;
	__dt__8DoorBaseFv = 0x2759534;
	checkDerivedRuntimeTypeInfo__8DoorBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x27593b8;
	getRuntimeTypeInfo__8DoorBaseCFv = __deleted_virtual_called;
	onCreate__8DoorBaseFv = 0x2758540;
	onExecute__8DoorBaseFv = 0x2758778;
	onDraw__8DoorBaseFv = 0x27587c4;
	vf18C__8DoorBaseFv = 0x27593b0;
	vf4E4__8DoorBaseFv = __deleted_virtual_called;
	ZOrder__8DoorBaseFv = 0x2758804;
	beginState_DoorBaseState1__8DoorBaseFv = 0x2758814;
    executeState_DoorBaseState1__8DoorBaseFv = 0x2758860;
    endState_DoorBaseState1__8DoorBaseFv = 0x275893c;
    beginState_DoorBaseState2__8DoorBaseFv = 0x2758948;
    executeState_DoorBaseState2__8DoorBaseFv = 0x2758988;
    endState_DoorBaseState2__8DoorBaseFv = 0x27595a0;
    beginState_DoorBaseState3__8DoorBaseFv = 0x2758a2c;
	executeState_DoorBaseState3__8DoorBaseFv = 0x2758a48;
    endState_DoorBaseState3__8DoorBaseFv = 0x27595a4;
    beginState_DoorBaseState4__8DoorBaseFv = 0x2758ac8;
    executeState_DoorBaseState4__8DoorBaseFv = 0x2758b90;
    endState_DoorBaseState4__8DoorBaseFv = 0x27595a8;
    isCurrentStateDoorBaseState3__8DoorBaseFv = 0x27595ac;
    vf55C__8DoorBaseFv = 0x275961c;
    vf564__8DoorBaseFv = __deleted_virtual_called;
    vf56C__8DoorBaseFv = __deleted_virtual_called;
    vf584__8DoorBaseFv = 0x275962c;
    vf58C__8DoorBaseFv = 0x2759630;
    playOpenDoorAnim__8DoorBaseFv = 0x2759634;
    playOpenDoorSound__8DoorBaseFv = 0x2759638;
    playCloseDoorAnim__8DoorBaseFv = 0x2759698;
    playCloseDoorSound__8DoorBaseFv = 0x275969c;
    vf5B4__8DoorBaseFv = 0x27596fc;
    vf5BC__8DoorBaseFv = 0x2759700;
    vf5C4__8DoorBaseFv = 0x2759704;
	collisionCallback__8DoorBaseSFP14HitboxColliderT1 = 0x2758c58;

/* DrawMgr */
	sInstance__7DrawMgr = 0x101d2d88;
	drawModel__7DrawMgrFP5Model = 0x24fab58;
	drawModel__7DrawMgrFP12ModelWrapper = 0x24fac98;
	drawTile__7DrawMgrFUsRC4Vec3RCUiT2 = 0x24fad28;

/* DRCModeTask */
	sInstance__11DRCModeTask = 0x101d1904;

/* Effect */
	spawn__6EffectSF12EffectIDTypePC13Vec3__tm__2_fPC14Vec3__tm__3_UiT2 = 0x22ab080;

/* Enemy */
	__ct__5EnemyFPC14ActorBuildInfo = 0x2328494;
	processCollision__5EnemyFP14HitboxColliderT1Ui = 0x2329b88;
	killPlayerJump__5EnemyFP10StageActorRC13Vec2__tm__2_fP9StateBase = 0x232da34;
	checkDerivedRuntimeTypeInfo__5EnemyCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x232a70c;
	__dt__5EnemyFv = 0x232a868;
	collisionCallback__5EnemySFP14HitboxColliderT1 = 0x2328c50;
	beforeExecute__5EnemyFv = 0x2328644;
	setPlayerID__5EnemyFSc = 0x232a63c;
	getActorPhysicsMgr__5EnemyFv = 0x232a674;
	vfAC__5EnemyFv = 0x232a644;
	vfB4__5EnemyFv = 0x232a648;
	vfBC__5EnemyFv = 0x232a650;
	vfC4__5EnemyFv = 0x232a654;
	vfCC__5EnemyFv = 0x232a658;
	damageFromUnder__5EnemyFv = 0x2328914;
	vf10C__5EnemyFUc = 0x232a65c;
	vf11C__5EnemyFv = 0x232a664;
	vf124__5EnemyFf = 0x232a668;
	vf12C__5EnemyFv = 0x232a66c;
	vf154__5EnemyFv = 0x232e1a4;
	setYSpeed__5EnemyFf = 0x232a690;
	vf16C__5EnemyFv = 0x232a698;
	vf174__5EnemyFv = 0x232a6a0;
	doStateChange__5EnemyFP9StateBase = 0x2330404;
	vf18C__5EnemyFv = 0x232a848;
	damagePlayer__5EnemyFP14HitboxColliderT1 = 0x2328b84;
	vf19C__5EnemyFv = 0x232910c;
	vf1AC__5EnemyFv = 0x23310bc;
	vf1B4__5EnemyFv = 0x23310c0;
	vf1BC__5EnemyFv = 0x2330568;
	vf1C4__5EnemyFv = 0x232a858;
	vf1CC__5EnemyFv = 0x232a85c;
	vf1D4__5EnemyFP14HitboxColliderT1 = 0x23291f8;
	vf1DC__5EnemyFP14HitboxColliderT1 = 0x2329250;
	vf1E4__5EnemyFRbP14HitboxColliderT2 = 0x2329520;
	vf1EC__5EnemyFP14HitboxColliderT1 = 0x2329578;
	vf1F4__5EnemyFP14HitboxColliderT1 = 0x232957c;
	vf1FC__5EnemyFP14HitboxColliderT1 = 0x23296e8;
	vf204__5EnemyFP14HitboxColliderT1 = 0x2329800;
	collisionEnemy__5EnemyFP14HitboxColliderT1 = 0x23299f0;
	collisionPlayer__5EnemyFP14HitboxColliderT1 = 0x23299f4;
	collisionYoshi__5EnemyFP14HitboxColliderT1 = 0x2329a04;
	vf224__5EnemyFP14HitboxColliderT1 = 0x2329a08;
	collisionStar__5EnemyFP14HitboxColliderT1 = 0x232ce84;
	collisionSlide__5EnemyFP14HitboxColliderT1 = 0x232cf20;
	collisionPropellerDrill__5EnemyFP14HitboxColliderT1 = 0x232d014;
	vf244__5EnemyFP14HitboxColliderT1 = 0x232d0e4;
	collisionGroundPound__5EnemyFP14HitboxColliderT1 = 0x232d240;
	collisionGroundPoundYoshi__5EnemyFP14HitboxColliderT1 = 0x232d3b4;
	collisionPenguinSlide__5EnemyFP14HitboxColliderT1 = 0x232d48c;
	collisionPipeCannon__5EnemyFP14HitboxColliderT1 = 0x232d49c;
	vf26C__5EnemyFP14HitboxColliderT1 = 0x232d56c;
	collisionThrowableObject__5EnemyFP14HitboxColliderT1 = 0x232d57c;
	collisionFireball__5EnemyFP14HitboxColliderT1 = 0x232d70c;
	collisionIceball__5EnemyFP14HitboxColliderT1 = 0x232d7a4;
	collisionHammer__5EnemyFP14HitboxColliderT1 = 0x232d824;
	collisionFireballYoshi__5EnemyFP14HitboxColliderT1 = 0x232d938;
	f29C__5EnemyFP14HitboxColliderT1 = 0x232da04;
	vf2A4__5EnemyFP14HitboxColliderT1 = 0x232da0c;
	vf2AC__5EnemyFP14HitboxColliderT1 = 0x232da14;
	vf2B4__5EnemyFP14HitboxColliderT1 = 0x232da24;
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
	freeze__5EnemyFv = 0x23304f8;
	vf29C__5EnemyFP14HitboxColliderT1 = 0x232da04;
	beginState_DieFumi__5EnemyFv = 0x232e518;
	executeState_DieFumi__5EnemyFv = 0x232e5e8;
	endState_DieFumi__5EnemyFv = 0x232eed0;
	beginState_DieFall__5EnemyFv = 0x232e63c;
	executeState_DieFall__5EnemyFv = 0x232e640;
	endState_DieFall__5EnemyFv = 0x232eed4;
	beginState_EnemyState3__5EnemyFv = 0x232e72c;
	executeState_EnemyState3__5EnemyFv = 0x232e79c;
	endState_EnemyState3__5EnemyFv = 0x232eed8;
	beginState_EnemyState4__5EnemyFv = 0x232e7a8;
	executeState_EnemyState4__5EnemyFv = 0x232e7b8;
	endState_EnemyState4__5EnemyFv = 0x232eedc;
	beginState_EnemyState5__5EnemyFv = 0x232e7c4;
	executeState_EnemyState5__5EnemyFv = 0x232e7c8;
	endState_EnemyState5__5EnemyFv = 0x232eee0;
	beginState_EnemyState6__5EnemyFv = 0x232e7d4;
	executeState_EnemyState6__5EnemyFv = 0x232eee4;
	endState_EnemyState6__5EnemyFv = 0x232eee8;
	beginState_EnemyState7__5EnemyFv = 0x232e7e0;
	executeState_EnemyState7__5EnemyFv = 0x232eeec;
	endState_EnemyState7__5EnemyFv = 0x232eef0;
	beginState_EnemyState8__5EnemyFv = 0x23305e4;
	executeState_EnemyState8__5EnemyFv = 0x23305ec;
	endState_EnemyState8__5EnemyFv = 0x23310c4;
	beginState_EnemyState9__5EnemyFv = 0x23310c8;
	executeState_EnemyState9__5EnemyFv = 0x23310cc;
	endState_EnemyState9__5EnemyFv = 0x23310d0;
	beginState_EnemyState10__5EnemyFv = 0x23310d4;
	executeState_EnemyState10__5EnemyFv = 0x23310d8;
	endState_EnemyState10__5EnemyFv = 0x23310dc;
	beginState_EnemyState11__5EnemyFv = 0x23306e8;
	executeState_EnemyState11__5EnemyFv = 0x23306f0;
	endState_EnemyState11__5EnemyFv = 0x23310e0;
	beginState_EnemyState12__5EnemyFv = 0x23310e4;
	executeState_EnemyState12__5EnemyFv = 0x23310e8;
	endState_EnemyState12__5EnemyFv = 0x23310ec;
	beginState_EnemyState13__5EnemyFv = 0x23310f0;
	executeState_EnemyState13__5EnemyFv = 0x23310f4;
	endState_EnemyState13__5EnemyFv = 0x23310f8;
	beginState_EnemyState14__5EnemyFv = 0x23310fc;
	executeState_EnemyState14__5EnemyFv = 0x2331100;
	endState_EnemyState14__5EnemyFv = 0x2331104;
	beginState_Ice__5EnemyFv = 0x2330720;
	executeState_Ice__5EnemyFv = 0x23307a0;
	endState_Ice__5EnemyFv = 0x2330944;
	move__5EnemyFR13Vec2__tm__2_f = 0x232a67c;
	getRect__5EnemyFR4Rect = 0x232a6a8;

/* ErrorViewerTask */
	sInstance__15ErrorViewerTask = 0x101d1904;

/* EventMgr */
	sInstance__8EventMgr = 0x101db06c;
	set__8EventMgrFUiT1bN41 = 0x269cd68;

/* HitboxCollider */
	__ct__14HitboxColliderFv = 0x219a960;
	__dt__14HitboxColliderFv = 0x219ab90;
	__CPR65__init__14HitboxColliderFP10StageActorPCQ2_J6J4InfoPPv = 0x219af1c;
	Default__Q2_14HitboxCollider4Info = 0x10041bc0;

/* HitboxColliderMgr */
	sInstance__17HitboxColliderMgr = 0x101c95d8;

/* ModelWrapper */
	__ct__12ModelWrapperFP5ModelUiN42 = 0x24d4798;
	setup__12ModelWrapperFP10ResArchivePvPQ2_4sead4Heap = 0x24d49a0;
	updateModel__12ModelWrapperFv = 0x24d4e84;
	updateAnimations__12ModelWrapperFv = 0x24d4d20;

/* Mtx34 */
	rotateAndTranslate__5Mtx34FRC14Vec3__tm__3_UiRC13Vec3__tm__2_f = 0x203c1c8;
	makeST__5Mtx34SFR5Mtx34RC13Vec3__tm__2_fT2 = 0x2222a88;
	makeSRT__5Mtx34SFR5Mtx34RC13Vec3__tm__2_fN22 = 0x2508424;

/* MultiStateActor */
	__vtbl__15MultiStateActor = 0x10001048;
	__ct__15MultiStateActorFPC14ActorBuildInfo = 0x200aa8c;
	vfAC__15MultiStateActorFv = 0x200abb0;
	vfB4__15MultiStateActorFv = 0x200abb4;
	vfBC__15MultiStateActorFv = 0x200abbc;
	vfC4__15MultiStateActorFv = 0x200abc0;
	vfCC__15MultiStateActorFv = 0x200abc4;
	vf10C__15MultiStateActorFUc = 0x200abcc;
	vf11C__15MultiStateActorFv = 0x200abd4;
	vf124__15MultiStateActorFf = 0x200abd8;
	vf12C__15MultiStateActorFv = 0x200abdc;
	setYSpeed__15MultiStateActorFf = 0x200ac08;
	vf16C__15MultiStateActorFv = 0x200ac10;
	vf174__15MultiStateActorFv = 0x200ac18;
	damageFromUnder__15MultiStateActorFv = 0x200abc8;
	vf154__15MultiStateActorFv = 0x200abec;
	move__15MultiStateActorFR13Vec2__tm__2_f = 0x200abf4;
	__dt__15MultiStateActorFv = 0x200b098;
	checkDerivedRuntimeTypeInfo__15MultiStateActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x200af94;
	getRuntimeTypeInfo__15MultiStateActorCFv = __deleted_virtual_called;
	setPlayerID__15MultiStateActorFSc = 0x200aba8;
	getActorPhysicsMgr__15MultiStateActorFv = 0x200abe4;
	getRect__15MultiStateActorFR4Rect = 0x200ac20;
	doStateChange__15MultiStateActorFP9StateBase = 0x200b090;

/* PhysicsActor */
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
	vf114__12PhysicsActorFv = __deleted_virtual_called;
	vf134__12PhysicsActorFv = __deleted_virtual_called;
	vf13C__12PhysicsActorFv = 0x2004008;
	vf144__12PhysicsActorFb = 0x200375c;
	vf14C__12PhysicsActorFP10StageActor = 0x2003760;
	move__12PhysicsActorFR13Vec2__tm__2_f = 0x2004020;
	getRect__12PhysicsActorFR4Rect = 0x200404c;

/* PhysicsMgr */
	getSensor__10PhysicsMgrCFUi = 0x218ce74;
	setSensor__10PhysicsMgrFPCQ2_10PhysicsMgr6SensorUi = 0x218aefc;

/* PlayerInput */
	isUpHeld__11PlayerInputCFv = 0x2916114;
	isDownHeld__11PlayerInputCFv = 0x2915F84;
	isRightHeld__11PlayerInputCFv = 0x2915F9C;
	isLeftHeld__11PlayerInputCFv = 0x2915F90;

/* PlayerMgr */
	sInstance__9PlayerMgr = 0x101e6994;

/* Powerup */
	__ct__7PowerupFPC14ActorBuildInfo = 0x251ebfc;
	__dt__7PowerupFv = 0x251fe04;
	checkDerivedRuntimeTypeInfo__7PowerupCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x251fc68;
	getRuntimeTypeInfo__7PowerupCFv = __deleted_virtual_called;
	setPlayerID__7PowerupFSc = 0x251faf0;
	StateID_PowerupState1__7Powerup = 0x1020ac50;
	getActorPhysicsMgr__7PowerupFv = 0x251fb1c;
	vfAC__7PowerupFv = 0x251faf8;
	vfB4__7PowerupFv = 0x251fafc;
	vfBC__7PowerupFv = 0x251fb04;
	vfC4__7PowerupFv = 0x251fb08;
	vfCC__7PowerupFv = 0x251fb0c;
	damageFromUnder__7PowerupFv = 0x251d8fc;
	vf10C__7PowerupFUc = 0x251fb14;
	vf11C__7PowerupFv = 0x251fc54;
	vf124__7PowerupFf = 0x251fc58;
	vf12C__7PowerupFv = 0x251fc5c;
	vf13C__7PowerupFv = 0x251fc4c;
	vf154__7PowerupFv = 0x251d918;
	move__7PowerupFR13Vec2__tm__2_f = 0x251fb2c;
	setYSpeed__7PowerupFf = 0x251fb40;
	vf16C__7PowerupFv = 0x251fb48;
	vf174__7PowerupFv = 0x251fb50;
	getRect__7PowerupFR4Rect = 0x251fb58;
	doStateChange__7PowerupFP9StateBase = 0x251fbc4;
	vf29C__7PowerupFv = 0x251fdec;
	vf2A4__7PowerupFv = 0x251fdf0;
	vf2AC__7PowerupFv = 0x251ec6c;

/* PowerupBase */
	setupActor__11PowerupBaseFv = 0x2517f90;
	spawnMethod__11PowerupBaseFv = 0x2518470;
	updateModel__11PowerupBaseFv = 0x2518a4c;
	FUN_2518f94__11PowerupBaseFv = 0x2518f94;
	FUN_25183ac__11PowerupBaseFv = 0x25183ac;
	onDraw__11PowerupBaseFv = 0x25176ec;
	killAtGoal__11PowerupBaseFv = 0x2517bd0;
	splashWater__11PowerupBaseFP13Vec3__tm__2_f = 0x2517c20;
	splashLava__11PowerupBaseFP13Vec3__tm__2_f = 0x2517d5c;
	splashLavaWave__11PowerupBaseFP13Vec3__tm__2_f = 0x2517e18;
	splashPoison__11PowerupBaseFP13Vec3__tm__2_f = 0x2517ed4;
	vf144__11PowerupBaseFb = 0x251771c;
	vf1BC__11PowerupBaseFv = 0x251784c;
	vf1CC__11PowerupBaseFv = 0x25178c0;
	vf1D4__11PowerupBaseFv = 0x2517908;
	vf1DC__11PowerupBaseFv = 0x2517950;
	vf1E4__11PowerupBaseFv = 0x2517a40;
	vf1EC__11PowerupBaseFv = 0x2517a84;
	vf1F4__11PowerupBaseFv = 0x2517b3c;
	vf204__11PowerupBaseFv = 0x2517b4c;
	beginState_PowerupBaseState12__11PowerupBaseFv = 0x251bbe8;
	executeState_PowerupBaseState12__11PowerupBaseFv = 0x251bc88;
	endState_PowerupBaseState12__11PowerupBaseFv = 0x251dc94;
	beginState_PowerupBaseState13__11PowerupBaseFv = 0x251bd60;
	executeState_PowerupBaseState13__11PowerupBaseFv = 0x251beac;
	endState_PowerupBaseState13__11PowerupBaseFv = 0x251dc98;
	beginState_PowerupBaseState14__11PowerupBaseFv = 0x251c0d8;
	executeState_PowerupBaseState14__11PowerupBaseFv = 0x251c29c;
	endState_PowerupBaseState14__11PowerupBaseFv = 0x251dc9c;
	beginState_PowerupBaseState15__11PowerupBaseFv = 0x251c2ac;
	executeState_PowerupBaseState15__11PowerupBaseFv = 0x251c414;
	endState_PowerupBaseState15__11PowerupBaseFv = 0x251dca0;
	beginState_PowerupBaseState16__11PowerupBaseFv = 0x251c424;
	executeState_PowerupBaseState16__11PowerupBaseFv = 0x251c530;
	endState_PowerupBaseState16__11PowerupBaseFv = 0x251dca4;
	beginState_SpatByYoshi__11PowerupBaseFv = 0x251c5fc;
	executeState_SpatByYoshi__11PowerupBaseFv = 0x251c714;
	endState_SpatByYoshi__11PowerupBaseFv = 0x251dca8;
	FUN_25196e8__11PowerupBaseFPvQ2_11PowerupBase12PowerupStateUi = 0x25196e8;
	FUN_2519580__11PowerupBaseFUiT1 = 0x2519580;

/* Profile */
	profilesOriginal__7Profile = 0x101ED8DC;
	prioritiesOriginal__7Profile = 0x10001940;
	hasResourcesOriginal__7Profile = 0x10002064;
	resourceCountOriginal__7Profile = 0x100023F8;
	resourceListsOriginal__7Profile = 0x101C321C;

/* Rect */
	sZero__4Rect = 0x105ea79c;

/* RectCollider */
	__vtbl__12RectCollider = 0x100fb820;

/* ResArchive */
	getModel__10ResArchiveFRCQ2_4sead23SafeStringBase__tm__2_cUiN42bPQ2_4sead4Heap = 0x24ee440;

/* ResArchiveMgr */
	sInstance__13ResArchiveMgr = 0x101d2d50;
	get__13ResArchiveMgrFRCQ2_4sead23SafeStringBase__tm__2_c = 0x24f60ec;

/* ShaderAnimation */
	playTexSrtAnim__15ShaderAnimationFP10ResArchiveRCQ2_4sead23SafeStringBase__tm__2_c = 0x24FEE50;

/* ShapedCollider */
	__ct__14ShapedColliderFiP13Vec2__tm__2_fPQ2_12ColliderBase4NodeT3 = 0x21a7904;
	execute__14ShapedColliderFv = 0x21a871c;
	__CPR62__init__14ShapedColliderFP10StageActorRCQ2_J6J4Info = 0x21ad3bc;
	__dt__14ShapedColliderFv = 0x21a7a04;

/* SkeletalAnimation */
	play__17SkeletalAnimationFP10ResArchiveRCQ2_4sead23SafeStringBase__tm__2_c = 0x24fdadc;

/* StageActor */
	__vtbl__10StageActor = 0x10000268;
	__LSG__typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x101e9cbc;
	typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x101e9cc0;
	__ct__10StageActorFPC14ActorBuildInfo = 0x2000ac8;
	directionToPlayerH__10StageActorFRC4Vec3 = 0x20005ec;
	directionToActorH__10StageActorFRC10StageActor = 0x200c800;
	distanceToPlayer__10StageActorFR4Vec2 = 0x20005a4;
	deleteActorWhenOutOfView__10StageActorFUi = 0x20007a0;
	actorAcCallback0__10StageActorFP14HitboxColliderP4Vec2 = 0x219e7e8;
	actorAcCallback2__10StageActorFP14HitboxColliderP4Vec2 = 0x219e8a4;
	actorCbCallback0__10StageActorFP12ColliderBaseP4Vec2 = 0x219e8b8;
	checkDerivedRuntimeTypeInfo__10StageActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x2002a38;
	getRuntimeTypeInfo__10StageActorCFv = __deleted_virtual_called;
	__dt__10StageActorFv = 0x2000f18;
	afterCreate__10StageActorFUi = 0x2000fb8;
	beforeExecute__10StageActorFv = 0x2000fe8;
	afterExecute__10StageActorFUi = 0x20010bc;
	beforeDraw__10StageActorFv = 0x20011a0;
	removeHitboxColliders__10StageActorFv = 0x20002cc;
	addHitboxColliders__10StageActorFv = 0x2000328;
	killAtGoal__10StageActorFv = 0x2002ad8;
	splashWater__10StageActorFP13Vec3__tm__2_f = 0x2002adc;
	splashLava__10StageActorFP13Vec3__tm__2_f = 0x2002ae0;
	splashLavaWave__10StageActorFP13Vec3__tm__2_f = 0x2000960;
	splashPoison__10StageActorFP13Vec3__tm__2_f = 0x2002ae4;
	isOffScreen__10StageActorFv = 0x2001254;
    setPlayerID__10StageActorFSc = 0x2002ab0;
    getActorPhysicsMgr__10StageActorFv = 0x2002ab8;
	damageFromUnder__10StageActorFv = 0x2002ae8;
	vfAC__10StageActorFv = 0x2002ac0;
	vfB4__10StageActorFv = 0x2002ac4;
	vfBC__10StageActorFv = 0x2002acc;
	vfC4__10StageActorFv = 0x2002ad0;
	vfCC__10StageActorFv = 0x2002ad4;

/* StateBase */
	sCurrentID__9StateBase = 0x101e9f04;

/* StateMgr */
	execute__8StateMgrFv = 0x29c4a80;
	changeState__8StateMgrFP9StateBase = 0x29c4af0;

/* TaskMgr */
	sInstance__7TaskMgr = 0x101e7b28;
	startLevel__7TaskMgrFPQ2_4sead8TaskBaseUcT2 = 0x29941d0;
	changeTask__7TaskMgrFPQ2_4sead8TaskBaseRQ2_4sead11TaskClassIDUiT3 = 0x2994164;

/* WindGenerator */
	__dt__13WindGeneratorFv = 0x288efa0;
	checkDerivedRuntimeTypeInfo__13WindGeneratorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x288eefc;
	getRuntimeTypeInfo__13WindGeneratorCFv = __deleted_virtual_called;
	onCreate__13WindGeneratorFv = 0x288ebc4;
	setPlayerID__13WindGeneratorFSc = 0x288ef74;
	getActorPhysicsMgr__13WindGeneratorFv = 0x288ef7c;
	vfAC__13WindGeneratorFv = 0x288ef84;
	vfB4__13WindGeneratorFv = 0x288ef88;
	vfBC__13WindGeneratorFv = 0x288ef90;
	vfC4__13WindGeneratorFv = 0x288ef94;
	vfCC__13WindGeneratorFv = 0x288ef98;
	damageFromUnder__13WindGeneratorFv = 0x288ef9c;

/* Unknown Class */
	FUN_02902b08__FP10StageActor = 0x2902b08;

/* Misc */
	BLOSDynLoad_Acquire = 0x2A9EF58;
	BOSDynLoad_FindExport = 0x2A9F418;
	directionToRotationList = 0x10200dd8;
}
