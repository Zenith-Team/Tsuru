SECTIONS {

/* Math */
	sinf__Ff = 0xF6BDD40;
	cosf__Ff = 0xF6BE528;
	atan2f__FfT1 = 0xF6BE670;
	fmodf__FfT1 = 0xF6BD97C;
	powf__FfT1 = 0xF6BDEA8;
	sqrtf__Ff = 0xF6BDCCC;

/* new/delete */
	__nw__FUi = 0xF5B1594;
	__nw__FUiPQ2_4sead4Heapi = 0xF5B1858;
	__nwa__FUi = 0xF5B1630;
	__nwa__FUiPQ2_4sead4Heapi = 0xF5B18DC;
	__dl__FPv = 0xF5B1748;
	__dla__FPv = 0xF5B17D0;

/* GHS C++ Functions */
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

/* GHS C Functions */
	_f_ftoll = 0xF6BEBFC;

/* sead::GlobalRandom */
	instance__Q2_4sead12GlobalRandom = 0x106EA26C;

/* sead::Random */
	getU32__Q2_4sead6RandomFv = 0xF5D3780;

/* ActorInfo */
	sDefault__9ActorInfo = 0x10503AF4;

/* ActorMgr */
	sInstance__8ActorMgr = 0x106C52C8;
	create__8ActorMgrFP14ActorBuildInfoUi = 0xEBC9A58;
	findActorByType__8ActorMgrFQ2_9ProfileId13ProfileIdTypePP9BaseActor = 0xEBC9B6C;

/* ApplicationTask */
	sInstance__15ApplicationTask = 0x106E9F40;

/* BaseActor */
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

/* CourseTask */
	sInstance__10CourseTask = 0x106D37F0;

/* CourseSelectTask */
	sInstance__16CourseSelectTask = 0x106CEB6C;

/* DrawMgr */
	sInstance__7DrawMgr = 0x106D4F88;
	drawModel__7DrawMgrFP5Model = 0xF0BAB58;
	drawModel__7DrawMgrFP12ModelWrapper = 0xF0BAC98;
	drawTile__7DrawMgrFUsRC4Vec3RCUiT2 = 0xF0BAD28;

/* DRCModeTask */
	sInstance__11DRCModeTask = 0x106D3B04;

/* Enemy */
	__ct__5EnemyFPC14ActorBuildInfo = 0xEEE8494;
	processCollision__5EnemyFP14HitboxColliderT1Ui = 0xEEE9B88;
	killPlayerJump__5EnemyFP10StageActorRC16Vector2__tm__2_fP9StateBase = 0xEEEDA34;
	checkDerivedRuntimeTypeInfo__5EnemyCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0xEEEA70C;
	__dt__5EnemyFv = 0xEEEA868;
	collisionCallback__5EnemySFP14HitboxColliderT1 = 0xEEE8C50;
	beforeExecute__5EnemyFv = 0xEEE8644;
	setPlayerID__5EnemyFSc = 0xEEEA63C;
	getActorPhysicsMgr__5EnemyFv = 0xEEEA674;
	vfAC__5EnemyFv = 0xEEEA644;
	vfB4__5EnemyFv = 0xEEEA648;
	vfBC__5EnemyFv = 0xEEEA650;
	vfC4__5EnemyFv = 0xEEEA654;
	vfCC__5EnemyFv = 0xEEEA658;
	damageFromUnder__5EnemyFv = 0xEEE8914;
	vf10C__5EnemyFUc = 0xEEEA65C;
	vf11C__5EnemyFv = 0xEEEA664;
	vf124__5EnemyFf = 0xEEEA668;
	vf12C__5EnemyFv = 0xEEEA66C;
	vf154__5EnemyFv = 0xEEEE1A4;
	setYSpeed__5EnemyFf = 0xEEEA690;
	vf16C__5EnemyFv = 0xEEEA698;
	vf174__5EnemyFv = 0xEEEA6A0;
	doStateChange__5EnemyFP9StateBase = 0xEEF0404;
	vf18C__5EnemyFv = 0xEEEA848;
	damagePlayer__5EnemyFP14HitboxColliderT1 = 0xEEE8B84;
	vf19C__5EnemyFv = 0xEEE910C;
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
	f29C__5EnemyFP14HitboxColliderT1 = 0xEEEDA04;
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
	freeze__5EnemyFv = 0xEEF04F8;
	vf29C__5EnemyFP14HitboxColliderT1 = 0xEEEDA04;
	beginState_DieFumi__5EnemyFv = 0xEEEE518;
	executeState_DieFumi__5EnemyFv = 0xEEEE5E8;
	endState_DieFumi__5EnemyFv = 0xEEEEED0;
	beginState_DieFall__5EnemyFv = 0xEEEE63C;
	executeState_DieFall__5EnemyFv = 0xEEEE640;
	endState_DieFall__5EnemyFv = 0xEEEEED4;
	beginState_EnemyState3__5EnemyFv = 0xEEEE72C;
	executeState_EnemyState3__5EnemyFv = 0xEEEE79C;
	endState_EnemyState3__5EnemyFv = 0xEEEEED8;
	beginState_EnemyState4__5EnemyFv = 0xEEEE7A8;
	executeState_EnemyState4__5EnemyFv = 0xEEEE7B8;
	endState_EnemyState4__5EnemyFv = 0xEEEEEDC;
	beginState_EnemyState5__5EnemyFv = 0xEEEE7C4;
	executeState_EnemyState5__5EnemyFv = 0xEEEE7C8;
	endState_EnemyState5__5EnemyFv = 0xEEEEEE0;
	beginState_EnemyState6__5EnemyFv = 0xEEEE7D4;
	executeState_EnemyState6__5EnemyFv = 0xEEEEEE4;
	endState_EnemyState6__5EnemyFv = 0xEEEEEE8;
	beginState_EnemyState7__5EnemyFv = 0xEEEE7E0;
	executeState_EnemyState7__5EnemyFv = 0xEEEEEEC;
	endState_EnemyState7__5EnemyFv = 0xEEEEEF0;
	beginState_EnemyState8__5EnemyFv = 0xEEF05E4;
	executeState_EnemyState8__5EnemyFv = 0xEEF05EC;
	endState_EnemyState8__5EnemyFv = 0xEEF10C4;
	beginState_EnemyState9__5EnemyFv = 0xEEF10C8;
	executeState_EnemyState9__5EnemyFv = 0xEEF10CC;
	endState_EnemyState9__5EnemyFv = 0xEEF10D0;
	beginState_EnemyState10__5EnemyFv = 0xEEF10D4;
	executeState_EnemyState10__5EnemyFv = 0xEEF10D8;
	endState_EnemyState10__5EnemyFv = 0xEEF10DC;
	beginState_EnemyState11__5EnemyFv = 0xEEF06E8;
	executeState_EnemyState11__5EnemyFv = 0xEEF06F0;
	endState_EnemyState11__5EnemyFv = 0xEEF10E0;
	beginState_EnemyState12__5EnemyFv = 0xEEF10E4;
	executeState_EnemyState12__5EnemyFv = 0xEEF10E8;
	endState_EnemyState12__5EnemyFv = 0xEEF10EC;
	beginState_EnemyState13__5EnemyFv = 0xEEF10F0;
	executeState_EnemyState13__5EnemyFv = 0xEEF10F4;
	endState_EnemyState13__5EnemyFv = 0xEEF10F8;
	beginState_EnemyState14__5EnemyFv = 0xEEF10FC;
	executeState_EnemyState14__5EnemyFv = 0xEEF1100;
	endState_EnemyState14__5EnemyFv = 0xEEF1104;
	beginState_Ice__5EnemyFv = 0xEEF0720;
	executeState_Ice__5EnemyFv = 0xEEF07A0;
	endState_Ice__5EnemyFv = 0xEEF0944;
	move__5EnemyFR16Vector2__tm__2_f = 0xEEEA67C;
	getRect__5EnemyFR4Rect = 0xEEEA6A8;

/* ErrorViewerTask */
	sInstance__15ErrorViewerTask = 0x106D3B04;


/* EventMgr */
	sInstance__8EventMgr = 0x106DD26C;
	set__8EventMgrFUiT1bN41 = 0xF25CD68;

/* HitboxCollider */
	__ct__14HitboxColliderFv = 0xED5A960;
	__dt__14HitboxColliderFv = 0xED5AB90;
	__CPR65__init__14HitboxColliderFP10StageActorPCQ2_J6J4InfoPPv = 0xED5AF1C;
	Default__Q2_14HitboxCollider4Info = 0x10543DC0;

/* ModelWrapper */
	__ct__12ModelWrapperFP5ModelUiN42 = 0xF094798;
	setup__12ModelWrapperFP10ResArchivePvPQ2_4sead4Heap = 0xF0949A0;
	updateModel__12ModelWrapperFv = 0xF094E84;
	updateAnimations__12ModelWrapperFv = 0xF094D20;

/* Mtx34 */
	rotateAndTranslate__5Mtx34FRC17Vector3__tm__3_UiRC16Vector3__tm__2_f = 0xEBFC1C8;
	makeST__5Mtx34SFR5Mtx34RC4Vec3T2 = 0xEDE2A88;
	makeSRT__5Mtx34SFR5Mtx34RC4Vec3N22 = 0xF0C8424;

/* MultiStateActor */
	vfAC__15MultiStateActorFv = 0xEBCABB0;
	vfB4__15MultiStateActorFv = 0xEBCABB4;
	vfBC__15MultiStateActorFv = 0xEBCABBC;
	vfC4__15MultiStateActorFv = 0xEBCABC0;
	vfCC__15MultiStateActorFv = 0xEBCABC4;
	vf10C__15MultiStateActorFUc = 0xEBCABCC;
	vf11C__15MultiStateActorFv = 0xEBCABD4;
	vf124__15MultiStateActorFf = 0xEBCABD8;
	vf12C__15MultiStateActorFv = 0xEBCABDC;
	setYSpeed__15MultiStateActorFf = 0xEBCAC08;
	vf16C__15MultiStateActorFv = 0xEBCAC10;
	vf174__15MultiStateActorFv = 0xEBCAC18;

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
	move__12PhysicsActorFR16Vector2__tm__2_f = 0xEBC4020;
	getRect__12PhysicsActorFR4Rect = 0xEBC404C;

/* Profile */
	profilesOriginal__7Profile = 0x106EFADC;
	prioritiesOriginal__7Profile = 0x10503B40;
	hasResourcesOriginal__7Profile = 0x10504264;
	resourceCountOriginal__7Profile = 0x105045F8;
	resourceListsOriginal__7Profile = 0x106C541C;

/* ResArchive */
	getModel__10ResArchiveFRCQ2_4sead23SafeStringBase__tm__2_cUiN42bPQ2_4sead4Heap = 0xF0AE440;

/* ResArchiveMgr */
	sInstance__13ResArchiveMgr = 0x106D4F50;
	get__13ResArchiveMgrFRCQ2_4sead23SafeStringBase__tm__2_c = 0xF0B60EC;

/* SkeletalAnimation */
	play__17SkeletalAnimationFP10ResArchiveRCQ2_4sead23SafeStringBase__tm__2_c = 0xF0BDADC;

/* StageActor */
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
	splashWater__10StageActorFP16Vector3__tm__2_f = 0xEBC2ADC;
	splashLava__10StageActorFP16Vector3__tm__2_f = 0xEBC2AE0;
	splashLavaWave__10StageActorFP16Vector3__tm__2_f = 0xEBC0960;
	splashPoison__10StageActorFP16Vector3__tm__2_f = 0xEBC2AE4;
	isOffScreen__10StageActorFv = 0xEBC1254;
	setPlayerID__10StageActorFSc = 0xEBC2AB0;
	getActorPhysicsMgr__10StageActorFv = 0xEBC2AB8;
	damageFromUnder__10StageActorFv = 0xEBC2AE8;
	vfAC__10StageActorFv = 0xEBC2AC0;
	vfB4__10StageActorFv = 0xEBC2AC4;
	vfBC__10StageActorFv = 0xEBC2ACC;
	vfC4__10StageActorFv = 0xEBC2AD0;
	vfCC__10StageActorFv = 0xEBC2AD4;


/* StateBase */
	sCurrentID__9StateBase = 0x106EC104;

/* StateMgr */
	execute__8StateMgrFv = 0xF584A80;
	changeState__8StateMgrFP9StateBase = 0xF584AF0;

/* TaskMgr */
	sInstance__7TaskMgr = 0x106E9D28;
	startLevel__7TaskMgrFPQ2_4sead8TaskBaseUcT2 = 0xF5541D0;
	changeTask__7TaskMgrFPQ2_4sead8TaskBaseRQ2_4sead11TaskClassIDUiT3 = 0xF554164;

/* Misc */
	BLOSDynLoad_Acquire = 0xF65EF58;
	BOSDynLoad_FindExport = 0xF65F418;
	directionToRotationList = 0x10702FD8;
}
