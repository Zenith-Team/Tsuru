SECTIONS {

/* Math */
    sinf__Ff = 0x2AFDD40;
    cosf__Ff = 0x2AFE528;
    atan2f__FfT1 = 0x2AFE670;
    fmodf__FfT1 = 0x2AFD97C;
    powf__FfT1 = 0x2AFDEA8;
    sqrtf__Ff = 0x2AFDCCC;
    cSinCosTbl = 0x10191538;

/* new/delete */
    __nw__FUi = 0x29F1594;
    __nw__FUiPQ2_4sead4Heapi = 0x29F1858;
    __nwa__FUi = 0x29F1630;
    __nwa__FUiPQ2_4sead4Heapi = 0x29F18DC;
    __dl__FPv = 0x29F1748;
    __dla__FPv = 0x29F17D0;

/* GHS C++ Functions */
    __pure_virtual_called = 0x2AFA554;
    __deleted_virtual_called = 0x2AFA5E8;
    __vec_new = 0x2AFA350;
    __vec_delete = 0x2AFA490;
    __record_needed_destruction = 0x2AFA52C;
    __gh_float_printf = 0x2AFABA8;
    __gh_long_long_printf = 0x2AFAB84;
    __gh_memclr32 = 0x2AFF1E0;
    __ghs_strcmp = 0x2AFA60C;
    __memzero = 0x2AFA55C;
    vsnprintf = 0x2AFBD54;

/* GHS C Functions */
    _f_ftoll = 0x2AFEBFC;

/* Cafe SDK Static */
    ASM_MTXConcat = 0x2AF98A0;
    GFDGetPixelShaderCount = 0x2AF8C10;
    GFDGetPixelShaderHeaderSize = 0x2AF8D10;
    GFDGetPixelShaderProgramSize = 0x2AF8D40;
    GFDGetPixelShader = 0x2AF8FC0;
    GFDGetVertexShaderCount = 0x2AF8C04;
    GFDGetVertexShaderHeaderSize = 0x2AF8D00;
    GFDGetVertexShaderProgramSize = 0x2AF8D40;
    GFDGetVertexShader = 0x2AF8E3C;

/* agl::lyr::Layer */
    pushBackDrawMethod__Q3_3agl3lyr5LayerFUiPQ3_3agl3lyr10DrawMethod = 0x2A376B8;

/* agl::lyr::Renderer */
    sInstance__Q3_3agl3lyr8Renderer = 0x101E8A2C;

/* sead::CalculateTask */
    __ct__Q2_4sead13CalculateTaskFRCQ2_4sead16TaskConstructArgPCc = 0x29FC508;
    __dt__Q2_4sead13CalculateTaskFv = 0x29FC2F0;
    checkDerivedRuntimeTypeInfo__Q2_4sead13CalculateTaskCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x29FC7D8;
    pauseCalc__Q2_4sead13CalculateTaskFb = 0x29FC444;
    pauseDraw__Q2_4sead13CalculateTaskFb = 0x29FC85C;
    pauseCalcRec__Q2_4sead13CalculateTaskFb = __deleted_virtual_called;
    pauseDrawRec__Q2_4sead13CalculateTaskFb = __deleted_virtual_called;
    attachCalcImpl__Q2_4sead13CalculateTaskFv = 0x29FC384;
    attachDrawImpl__Q2_4sead13CalculateTaskFv = 0x29FC854;
    detachCalcImpl__Q2_4sead13CalculateTaskFv = 0x29FC43C;
    detachDrawImpl__Q2_4sead13CalculateTaskFv = 0x29FC858;
    getCorrespondingMethodTreeMgrTypeInfo__Q2_4sead13CalculateTaskCFv = __deleted_virtual_called;
    getMethodTreeNode__Q2_4sead13CalculateTaskFi = 0x29FC4F0;

/* sead::FileDevice */
    tryClose__Q2_4sead10FileDeviceFPQ2_4sead10FileHandle = 0x29F78C0;
    tryWrite__Q2_4sead10FileDeviceFPUiPQ2_4sead10FileHandlePCUcUi = 0x29F7AE8;

/* sead::FileDeviceMgr */
    sInstance__Q2_4sead13FileDeviceMgr = 0x101E7F18
    tryLoad__Q2_4sead13FileDeviceMgrFRQ3_4sead10FileDevice7LoadArg = 0x29F8BBC;
    tryOpen__Q2_4sead13FileDeviceMgrFPQ2_4sead10FileHandleRCQ2_4sead23SafeStringBase__tm__2_cQ3_4sead10FileDevice12FileOpenFlagUi = 0x29F8B0C;

/* sead::FileHandle */
    read__Q2_4sead10FileHandleFPUcUi = 0x29F81D0;

/* sead::FrustumProjection */
    __ct__Q2_4sead17FrustumProjectionFfN51 = 0x2A06944;
    __dt__Q2_4sead17FrustumProjectionFv = 0x2A06A4C;

/* sead::GlobalRandom */
    sInstance__Q2_4sead12GlobalRandom = 0x101E806C;

/* sead::IDisposer */
    __ct__Q2_4sead9IDisposerFv = 0x2A0A2FC;
    __dt__Q2_4sead9IDisposerFv = 0x2A0A384;

/* sead::OrthoProjection */
    __ct__Q2_4sead15OrthoProjectionFv = 0x2A06518;
    setTBLR__Q2_4sead15OrthoProjectionFfN31 = 0x2A06818;
    __dt__Q2_4sead15OrthoProjectionFv = 0x2A067C4;

/* sead::PerspectiveProjection */
    __ct__Q2_4sead21PerspectiveProjectionFv = 0x2A06108;
    set__Q2_4sead21PerspectiveProjectionFfN31 = 0x2A062EC;
    __dt__Q2_4sead21PerspectiveProjectionFv = 0x2A06298;

/* sead::PrimitiveRenderer */
    sInstance__Q2_4sead17PrimitiveRenderer = 0x101E8010;
    setCamera__Q2_4sead17PrimitiveRendererFRCQ2_4sead6Camera = 0x2A083D0;
    setProjection__Q2_4sead17PrimitiveRendererFRCQ2_4sead10Projection = 0x2A083E4;
    begin__Q2_4sead17PrimitiveRendererFv = 0x2A08408;
    end__Q2_4sead17PrimitiveRendererFv = 0x2A0841C;

/* sead::PrimitiveRendererCafe */
    drawTriangles___Q2_4sead21PrimitiveRendererCafeFRC5Mtx34RCQ2_4sead7Color4fT2PQ3_4sead21PrimitiveRendererUtil6VertexUiPUsT5PC11_GX2Texture = 0x2A0A190;

/* sead::Random */
    getU32__Q2_4sead6RandomFv = 0x2A13780;

/* sead::TaskBase */
    pauseCalcChild__Q2_4sead8TaskBaseFb = __deleted_virtual_called;
    pauseDrawChild__Q2_4sead8TaskBaseFb = __deleted_virtual_called;
    prepare__Q2_4sead8TaskBaseFv = 0x29FFF6C;
    exit__Q2_4sead8TaskBaseFv = 0x29FFF74;
    onEvent__Q2_4sead8TaskBaseFRCQ2_4sead9TaskEvent = 0x29FFF78;
    onDestroy__Q2_4sead8TaskBaseFv = __deleted_virtual_called;
    enterCommon__Q2_4sead8TaskBaseFv = 0x29FF818;
    adjustHeapAll__Q2_4sead8TaskBaseFv = 0x29FF9DC;

/* Actor */
    __vtbl__5Actor = 0x100006C0;
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__5ActorSFv = 0x101E9CC4;
    typeInfo__L0__getRuntimeTypeInfoStatic__5ActorSFv = 0x101E9CC8;
    removeChild__5ActorFP5Actor = 0x2002C8C;
    beforeCreate__5ActorFv = 0x2002F7C;
    afterCreate__5ActorFUi = 0x2002F00;
    beforeExecute__5ActorFv = 0x2002F04;
    onExecute__5ActorFv = 0x2002F8C;
    afterExecute__5ActorFUi = 0x2002F34;
    finalExecute__5ActorFv = 0x2002F94;
    beforeDraw__5ActorFv = 0x2002F98;
    onDraw__5ActorFv = 0x2002FA0;
    afterDraw__5ActorFUi = 0x2002F38;
    beforeDelete__5ActorFv = 0x2002FA8;
    onDelete__5ActorFv = 0x2002FB0;
    afterDelete__5ActorFUi = 0x2002F3C;
    getProfileID__5ActorFv = 0x2002C80;

/* ActorBuffer */
    findActorByID__11ActorBufferFPUi = 0x200A5C8;

/* ActorInfo */
    sDefault__9ActorInfo = 0x100018F4;

/* ActorMgr */
    sInstance__8ActorMgr = 0x101C30C8;
    create__8ActorMgrFR14ActorBuildInfoUi = 0x2009A58;
    findActorByType__8ActorMgrFQ2_9ProfileId13ProfileIdTypePP5Actor = 0x2009B6C;

/* AreaTask */
    sInstance__8AreaTask = 0x101D1598;

/* Animation */
    setRepeat__9AnimationFb = 0x24DEED4;
    reset__9AnimationFv = 0x24DEEAC;

/* AreaRumbleMgr */
    sInstance__13AreaRumbleMgr = 0x101D1660;
    rumble__13AreaRumbleMgrFiScN22 = 0x24C4D3C;

/* AreaTask */
    drawLayer3D__8AreaTaskFRCQ3_3agl3lyr10RenderInfo = 0x24B84A8;

/* ApplicationTask */
    sInstance__15ApplicationTask = 0x101E7D40;

/* AudioFx */
    getReverbHiParam__7AudioFxFv = 0x29B2FD8;
    getDelayParam__7AudioFxFv = 0x29B2FE0;

/* BasicSoundActor */
    GlobalBasicSoundActorA__15BasicSoundActor = 0x101C63CC;
    GlobalBasicSoundActorB__15BasicSoundActor = 0x101C63D0;
    playSound__15BasicSoundActorFPCcP13Vec2__tm__2_fUi = 0x29BED48;

/* ColliderBase */
    __ct__Q2_12ColliderBase4NodeFv = 0x21A1ACC;

/* ColliderMgr */
    sInstance__11ColliderMgr = 0x101C9360;
    add__11ColliderMgrFP12ColliderBase = 0x219269C;
    remove__11ColliderMgrFP12ColliderBase = 0x219282C;

/* CourseTask */
    sInstance__10CourseTask = 0x101D15F0;

/* CourseSelectActor */
    __ct__17CourseSelectActorFPC14ActorBuildInfo = 0x21D4CB4;
    __dt__17CourseSelectActorFv = 0x21D5838;
    checkDerivedRuntimeTypeInfo__17CourseSelectActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x21D588C;
    getRuntimeTypeInfo__17CourseSelectActorCFv = __deleted_virtual_called;
    beforeExecute__17CourseSelectActorFv = 0x21D4D60;
    beforeDraw__17CourseSelectActorFv = 0x21D4DB8;
    vf8C__17CourseSelectActorFv = 0x21D5948;
    vf94__17CourseSelectActorFv = 0x21D5950;
    vf9C__17CourseSelectActorFv = 0x21D595C;
    vfA4__17CourseSelectActorFv = 0x21D5968;
    updateCSScriptInteractions__17CourseSelectActorFv = 0x21D4F1C;

/* CourseSelectTask */
    sInstance__16CourseSelectTask = 0x101CC96C;
    drawLayer3D__16CourseSelectTaskFRCQ3_3agl3lyr10RenderInfo = 0x22676A4;
    construct__16CourseSelectTaskSFRCQ2_4sead16TaskConstructArg = 0x202B870;

/* CSPlayerMgr */
    sInstance__11CSPlayerMgr = 0x101CC30C;

/* CSCollisionActor */
    __ct__16CSCollisionActorFPC14ActorBuildInfo = 0x21D596C;
    __dt__16CSCollisionActorFv = 0x21D60EC;
    checkDerivedRuntimeTypeInfo__16CSCollisionActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x21D5FF0;
    getRuntimeTypeInfo__16CSCollisionActorCFv = __deleted_virtual_called;
    vf8C__16CSCollisionActorFv = 0x21D5FCC;
    vf94__16CSCollisionActorFv = 0x21D5FD4;
    vf9C__16CSCollisionActorFv = 0x21D5FE0;
    vfA4__16CSCollisionActorFv = 0x21D5FEC;
    vfAC__16CSCollisionActorFv = 0x21D614C;
    vfB4__16CSCollisionActorFv = 0x21D6150;
    vfBC__16CSCollisionActorFv = 0x21D6158;
    vfC4__16CSCollisionActorFdP13Vec3__tm__2_f = 0x21D6160;
    vfCC__16CSCollisionActorFv = 0x21D6180;
    vfD4__16CSCollisionActorFv = 0x21D6184;
    vfDC__16CSCollisionActorFv = 0x21D618C;
    vfE4__16CSCollisionActorFv = 0x21D6198;
    vfEC__16CSCollisionActorFv = 0x21D61A0;
    vfF4__16CSCollisionActorFP13Vec3__tm__2_f = 0x21D5D4C;
    vfFC__16CSCollisionActorFv = 0x21D5D5C;
    vf104__16CSCollisionActorFUi = 0x21D5E40;
    vf10C__16CSCollisionActorFv = 0x21D5E54;
    vf114__16CSCollisionActorFv = 0x21D5F08;
    vf11C__16CSCollisionActorFv = 0x21D61A8;
    vf124__16CSCollisionActorFv = 0x21D61C0;

/* CSHitboxCollider */
    __CPR72__init__16CSHitboxColliderFP16CSCollisionActorPCQ2_J6J4Info = 0x21C5634;

/* CSHitboxColliderMgr */
    sInstance__19CSHitboxColliderMgr = 0x101C9758;
    add__19CSHitboxColliderMgrFP16CSHitboxCollider = 0x21C5800;
    FUN_21c5894__19CSHitboxColliderMgrFP16CSHitboxCollider = 0x21C5894;

/* CSScriptMgr */
    sInstance__11CSScriptMgr = 0x101CBBC4;
    getCurrentScriptCommandType__11CSScriptMgrFPUi = 0x21E42FC;

/* CSSomethingActor */
    __ct__16CSSomethingActorFPC14ActorBuildInfo = 0x2201C04;
    __dt__16CSSomethingActorFv = 0x2201D08;
    checkDerivedRuntimeTypeInfo__16CSSomethingActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x2201D5C;
    getRuntimeTypeInfo__16CSSomethingActorCFv = __deleted_virtual_called;
    vf8C__16CSSomethingActorFv = 0x2201CE4;
    vf94__16CSSomethingActorFv = 0x2201CEC;
    vf9C__16CSSomethingActorFv = 0x2201CF8;
    vfA4__16CSSomethingActorFv = 0x2201D04;

/* Direction */
    directionToRotationList__9Direction = 0x10200DD8;

/* DoorBase */
    __ct__8DoorBaseFPC14ActorBuildInfo = 0x27583F0;
    __dt__8DoorBaseFv = 0x2759534;
    checkDerivedRuntimeTypeInfo__8DoorBaseCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x27593B8;
    getRuntimeTypeInfo__8DoorBaseCFv = __deleted_virtual_called;
    onCreate__8DoorBaseFv = 0x2758540;
    onExecute__8DoorBaseFv = 0x2758778;
    onDraw__8DoorBaseFv = 0x27587C4;
    vf18C__8DoorBaseFv = 0x27593B0;
    vf4E4__8DoorBaseFv = __deleted_virtual_called;
    ZOrder__8DoorBaseFv = 0x2758804;
    beginState_DoorBaseState1__8DoorBaseFv = 0x2758814;
    executeState_DoorBaseState1__8DoorBaseFv = 0x2758860;
    endState_DoorBaseState1__8DoorBaseFv = 0x275893C;
    beginState_DoorBaseState2__8DoorBaseFv = 0x2758948;
    executeState_DoorBaseState2__8DoorBaseFv = 0x2758988;
    endState_DoorBaseState2__8DoorBaseFv = 0x27595A0;
    beginState_DoorBaseState3__8DoorBaseFv = 0x2758A2C;
    executeState_DoorBaseState3__8DoorBaseFv = 0x2758A48;
    endState_DoorBaseState3__8DoorBaseFv = 0x27595A4;
    beginState_DoorBaseState4__8DoorBaseFv = 0x2758AC8;
    executeState_DoorBaseState4__8DoorBaseFv = 0x2758B90;
    endState_DoorBaseState4__8DoorBaseFv = 0x27595A8;
    isCurrentStateDoorBaseState3__8DoorBaseFv = 0x27595AC;
    vf55C__8DoorBaseFv = 0x275961C;
    vf564__8DoorBaseFv = __deleted_virtual_called;
    vf56C__8DoorBaseFv = __deleted_virtual_called;
    vf584__8DoorBaseFv = 0x275962C;
    vf58C__8DoorBaseFv = 0x2759630;
    playOpenDoorAnim__8DoorBaseFv = 0x2759634;
    playOpenDoorSound__8DoorBaseFv = 0x2759638;
    playCloseDoorAnim__8DoorBaseFv = 0x2759698;
    playCloseDoorSound__8DoorBaseFv = 0x275969C;
    vf5B4__8DoorBaseFv = 0x27596FC;
    vf5BC__8DoorBaseFv = 0x2759700;
    vf5C4__8DoorBaseFv = 0x2759704;
    collisionCallback__8DoorBaseSFP14HitboxColliderT1 = 0x2758C58;

/* DrawMgr */
    sInstance__7DrawMgr = 0x101D2D88;
    drawModel__7DrawMgrFP5Model = 0x24FAB58;
    drawModel__7DrawMgrFP12ModelWrapper = 0x24FAC98;
    drawTile__7DrawMgrFUsRC4Vec3RCUiT2 = 0x24FAD28;

/* DRCModeTask */
    sInstance__11DRCModeTask = 0x101D1904;

/* Effect */
    spawn__6EffectSFUiPC13Vec3__tm__2_fPC14Vec3__tm__3_UiT2 = 0x22AB080;

/* Enemy */
    __ct__5EnemyFPC14ActorBuildInfo = 0x2328494;
    processCollision__5EnemyFP14HitboxColliderT1Ui = 0x2329B88;
    killPlayerJump__5EnemyFP10StageActorRC13Vec2__tm__2_fP9StateBase = 0x232DA34;
    checkDerivedRuntimeTypeInfo__5EnemyCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x232A70C;
    getRuntimeTypeInfo__5EnemyCFv = __deleted_virtual_called;
    __dt__5EnemyFv = 0x232A868;
    collisionCallback__5EnemySFP14HitboxColliderT1 = 0x2328C50;
    beforeExecute__5EnemyFv = 0x2328644;
    setPlayerID__5EnemyFSc = 0x232A63C;
    getActorPhysicsMgr__5EnemyFv = 0x232A674;
    vfAC__5EnemyFv = 0x232A644;
    vfB4__5EnemyFv = 0x232A648;
    vfBC__5EnemyFv = 0x232A650;
    vfC4__5EnemyFv = 0x232A654;
    vfCC__5EnemyFv = 0x232A658;
    damageFromUnder__5EnemyFv = 0x2328914;
    vf10C__5EnemyFUc = 0x232A65C;
    vf11C__5EnemyFv = 0x232A664;
    vf124__5EnemyFf = 0x232A668;
    vf12C__5EnemyFv = 0x232A66C;
    vf154__5EnemyFv = 0x232E1A4;
    setYSpeed__5EnemyFf = 0x232A690;
    vf16C__5EnemyFv = 0x232A698;
    vf174__5EnemyFv = 0x232A6A0;
    doStateChange__5EnemyFP9StateBase = 0x2330404;
    vf18C__5EnemyFv = 0x232A848;
    damagePlayer__5EnemyFP14HitboxColliderT1 = 0x2328B84;
    vf19C__5EnemyFv = 0x232910C;
    vf1AC__5EnemyFv = 0x23310BC;
    vf1B4__5EnemyFv = 0x23310C0;
    vf1BC__5EnemyFv = 0x2330568;
    vf1C4__5EnemyFv = 0x232A858;
    vf1CC__5EnemyFv = 0x232A85C;
    vf1D4__5EnemyFP14HitboxColliderT1 = 0x23291F8;
    vf1DC__5EnemyFP14HitboxColliderT1 = 0x2329250;
    vf1E4__5EnemyFRbP14HitboxColliderT2 = 0x2329520;
    vf1EC__5EnemyFP14HitboxColliderT1 = 0x2329578;
    vf1F4__5EnemyFP14HitboxColliderT1 = 0x232957C;
    vf1FC__5EnemyFP14HitboxColliderT1 = 0x23296E8;
    vf204__5EnemyFP14HitboxColliderT1 = 0x2329800;
    collisionEnemy__5EnemyFP14HitboxColliderT1 = 0x23299F0;
    collisionPlayer__5EnemyFP14HitboxColliderT1 = 0x23299F4;
    collisionYoshi__5EnemyFP14HitboxColliderT1 = 0x2329A04;
    vf224__5EnemyFP14HitboxColliderT1 = 0x2329A08;
    collisionStar__5EnemyFP14HitboxColliderT1 = 0x232CE84;
    collisionSlide__5EnemyFP14HitboxColliderT1 = 0x232CF20;
    collisionPropellerDrill__5EnemyFP14HitboxColliderT1 = 0x232D014;
    vf244__5EnemyFP14HitboxColliderT1 = 0x232D0E4;
    collisionGroundPound__5EnemyFP14HitboxColliderT1 = 0x232D240;
    collisionGroundPoundYoshi__5EnemyFP14HitboxColliderT1 = 0x232D3B4;
    collisionPenguinSlide__5EnemyFP14HitboxColliderT1 = 0x232D48C;
    collisionPipeCannon__5EnemyFP14HitboxColliderT1 = 0x232D49C;
    vf26C__5EnemyFP14HitboxColliderT1 = 0x232D56C;
    collisionThrowableObject__5EnemyFP14HitboxColliderT1 = 0x232D57C;
    collisionFireball__5EnemyFP14HitboxColliderT1 = 0x232D70C;
    collisionIceball__5EnemyFP14HitboxColliderT1 = 0x232D7A4;
    collisionHammer__5EnemyFP14HitboxColliderT1 = 0x232D824;
    collisionFireballYoshi__5EnemyFP14HitboxColliderT1 = 0x232D938;
    f29C__5EnemyFP14HitboxColliderT1 = 0x232DA04;
    collisionGlowBabyYoshi__5EnemyFP14HitboxColliderT1 = 0x232DA0C;
    vf2AC__5EnemyFP14HitboxColliderT1 = 0x232DA14;
    vf2B4__5EnemyFP14HitboxColliderT1 = 0x232DA24;
    vf2BC__5EnemyFv = 0x232DAF0;
    vf2C4__5EnemyFv = 0x232DD48;
    vf2CC__5EnemyFv = 0x232E048;
    isOnGround__5EnemyFv = 0x232E2EC;
    playFireHitSound__5EnemyFv = 0x232E2F8;
    vf2E4__5EnemyFv = 0x232E358;
    bouncePlayerWhenJumpedOn__5EnemyFv = 0x2329EA4;
    addScoreWhenHit__5EnemyFv = 0x2329FA8;
    vf2FC__5EnemyFv = 0x2329FAC;
    vf304__5EnemyFv = 0x2329FB0;
    vf30C__5EnemyFv = 0x2329FC0;
    vf314__5EnemyFv = 0x232A094;
    vf31C__5EnemyFv = 0x232A118;
    vf324__5EnemyFv = 0x232A1BC;
    vf32C__5EnemyFv = 0x232A240;
    vf334__5EnemyFv = 0x232A24C;
    vf33C__5EnemyFv = 0x232A250;
    vf344__5EnemyFv = 0x232A2D4;
    vf34C__5EnemyFv = 0x232A2E4;
    vf354__5EnemyFv = 0x232A2FC;
    vf35C__5EnemyFv = 0x232A364;
    vf364__5EnemyFv = 0x232A418;
    vf36C__5EnemyFv = 0x232A4CC;
    vf374__5EnemyFv = 0x232A864;
    freeze__5EnemyFv = 0x23304F8;
    vf29C__5EnemyFP14HitboxColliderT1 = 0x232DA04;
    beginState_DieFumi__5EnemyFv = 0x232E518;
    executeState_DieFumi__5EnemyFv = 0x232E5E8;
    endState_DieFumi__5EnemyFv = 0x232EED0;
    beginState_DieFall__5EnemyFv = 0x232E63C;
    executeState_DieFall__5EnemyFv = 0x232E640;
    endState_DieFall__5EnemyFv = 0x232EED4;
    beginState_EnemyState3__5EnemyFv = 0x232E72C;
    executeState_EnemyState3__5EnemyFv = 0x232E79C;
    endState_EnemyState3__5EnemyFv = 0x232EED8;
    beginState_EnemyState4__5EnemyFv = 0x232E7A8;
    executeState_EnemyState4__5EnemyFv = 0x232E7B8;
    endState_EnemyState4__5EnemyFv = 0x232EEDC;
    beginState_EnemyState5__5EnemyFv = 0x232E7C4;
    executeState_EnemyState5__5EnemyFv = 0x232E7C8;
    endState_EnemyState5__5EnemyFv = 0x232EEE0;
    beginState_EnemyState6__5EnemyFv = 0x232E7D4;
    executeState_EnemyState6__5EnemyFv = 0x232EEE4;
    endState_EnemyState6__5EnemyFv = 0x232EEE8;
    beginState_EnemyState7__5EnemyFv = 0x232E7E0;
    executeState_EnemyState7__5EnemyFv = 0x232EEEC;
    endState_EnemyState7__5EnemyFv = 0x232EEF0;
    beginState_EnemyState8__5EnemyFv = 0x23305E4;
    executeState_EnemyState8__5EnemyFv = 0x23305EC;
    endState_EnemyState8__5EnemyFv = 0x23310C4;
    beginState_EnemyState9__5EnemyFv = 0x23310C8;
    executeState_EnemyState9__5EnemyFv = 0x23310CC;
    endState_EnemyState9__5EnemyFv = 0x23310D0;
    beginState_EnemyState10__5EnemyFv = 0x23310D4;
    executeState_EnemyState10__5EnemyFv = 0x23310D8;
    endState_EnemyState10__5EnemyFv = 0x23310DC;
    beginState_EnemyState11__5EnemyFv = 0x23306E8;
    executeState_EnemyState11__5EnemyFv = 0x23306F0;
    endState_EnemyState11__5EnemyFv = 0x23310E0;
    beginState_EnemyState12__5EnemyFv = 0x23310E4;
    executeState_EnemyState12__5EnemyFv = 0x23310E8;
    endState_EnemyState12__5EnemyFv = 0x23310EC;
    beginState_EnemyState13__5EnemyFv = 0x23310F0;
    executeState_EnemyState13__5EnemyFv = 0x23310F4;
    endState_EnemyState13__5EnemyFv = 0x23310F8;
    beginState_EnemyState14__5EnemyFv = 0x23310FC;
    executeState_EnemyState14__5EnemyFv = 0x2331100;
    endState_EnemyState14__5EnemyFv = 0x2331104;
    beginState_Ice__5EnemyFv = 0x2330720;
    executeState_Ice__5EnemyFv = 0x23307A0;
    endState_Ice__5EnemyFv = 0x2330944;
    move__5EnemyFR13Vec2__tm__2_f = 0x232A67C;
    getRect__5EnemyFR4Rect = 0x232A6A8;

/* EnemyFreezeMgr */
    setFlags__14EnemyFreezeMgrFRCQ2_14EnemyFreezeMgr5Flags = 0x237CB94;

/* ErrorViewerTask */
    sInstance__15ErrorViewerTask = 0x101D1904;

/* EventMgr */
    sInstance__8EventMgr = 0x101DB06C;
    set__8EventMgrFUiT1bN41 = 0x269CD68;

/* HitboxCollider */
    __ct__14HitboxColliderFv = 0x219A960;
    __dt__14HitboxColliderFv = 0x219AB90;
    __CPR65__init__14HitboxColliderFP10StageActorPCQ2_J6J4InfoPPv = 0x219AF1C;
    Default__Q2_14HitboxCollider4Info = 0x10041BC0;

/* HitboxColliderMgr */
    sInstance__17HitboxColliderMgr = 0x101C95D8;

/* LevelInfo */
    sInstance__9LevelInfo = 0x101D18EC;
    setDestEntrance__9LevelInfoFSc = 0x24D2984;

/* LevelTimer */
    sInstance__10LevelTimer = 0x101D15F4;
    addTime__10LevelTimerFi = 0x24C14C0;

/* LightMask */
    __ct__9LightMaskFv = 0x2815C9C;
    init__9LightMaskFPQ2_4sead4HeapUi = 0x2815D20;
    update__9LightMaskFv = 0x2815DCC;
    draw__9LightMaskFv = 0x28160C8;

/* LightSource */
    __ct__11LightSourceFv = 0x24E24BC;
    update__11LightSourceFP13Vec3__tm__2_fPfN22PQ2_4sead7Color4fN22 = 0x24E25F4;
    __dt__11LightSourceFv = 0x24E2580;
    update__11LightSourceFUiP13Vec3__tm__2_fPUiPfT4PQ2_4sead7Color4fN24 = 0x24E26BC;

/* ModelWrapper */
    __ct__12ModelWrapperFP5ModelUiN42 = 0x24D4798;
    setup__12ModelWrapperFP10ResArchivePvPQ2_4sead4Heap = 0x24D49A0;
    updateModel__12ModelWrapperFv = 0x24D4E84;
    updateAnimations__12ModelWrapperFv = 0x24D4D20;

/* Mtx34 */
    rotateAndTranslate__5Mtx34FRC14Vec3__tm__3_UiRC13Vec3__tm__2_f = 0x203C1C8;
    makeST__5Mtx34SFR5Mtx34RC13Vec3__tm__2_fT2 = 0x2222A88;
    makeSRT__5Mtx34SFR5Mtx34RC13Vec3__tm__2_fN22 = 0x2508424;

/* MultiStateActor */
    __vtbl__15MultiStateActor = 0x10001048;
    __ct__15MultiStateActorFPC14ActorBuildInfo = 0x200AA8C;
    vfAC__15MultiStateActorFv = 0x200ABB0;
    vfB4__15MultiStateActorFv = 0x200ABB4;
    vfBC__15MultiStateActorFv = 0x200ABBC;
    vfC4__15MultiStateActorFv = 0x200ABC0;
    vfCC__15MultiStateActorFv = 0x200ABC4;
    vf10C__15MultiStateActorFUc = 0x200ABCC;
    vf11C__15MultiStateActorFv = 0x200ABD4;
    vf124__15MultiStateActorFf = 0x200ABD8;
    vf12C__15MultiStateActorFv = 0x200ABDC;
    setYSpeed__15MultiStateActorFf = 0x200AC08;
    vf16C__15MultiStateActorFv = 0x200AC10;
    vf174__15MultiStateActorFv = 0x200AC18;
    damageFromUnder__15MultiStateActorFv = 0x200ABC8;
    vf154__15MultiStateActorFv = 0x200ABEC;
    move__15MultiStateActorFR13Vec2__tm__2_f = 0x200ABF4;
    __dt__15MultiStateActorFv = 0x200B098;
    checkDerivedRuntimeTypeInfo__15MultiStateActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x200AF94;
    getRuntimeTypeInfo__15MultiStateActorCFv = __deleted_virtual_called;
    setPlayerID__15MultiStateActorFSc = 0x200ABA8;
    getActorPhysicsMgr__15MultiStateActorFv = 0x200ABE4;
    getRect__15MultiStateActorFR4Rect = 0x200AC20;
    doStateChange__15MultiStateActorFP9StateBase = 0x200B090;

/* PhysicsActor */
    __vtbl__12PhysicsActor = 0x1000084C;
    __ct__12PhysicsActorFPC14ActorBuildInfo = 0x2002FB8;
    __dt__12PhysicsActorFv = 0x20040B0;
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__12PhysicsActorSFv = 0x101E9CD4;
    typeInfo__L0__getRuntimeTypeInfoStatic__12PhysicsActorSFv = 0x101E9CD8;
    handleGravity__12PhysicsActorFv = 0x20039AC;
    handleSpeed__12PhysicsActorFv = 0x2003AE4;
    afterCreate__12PhysicsActorFUi = 0x200354C;
    beforeExecute__12PhysicsActorFv = 0x20035FC;
    afterExecute__12PhysicsActorFUi = 0x20036D8;
    onDelete__12PhysicsActorFv = 0x2003724;
    setPlayerId__12PhysicsActorFSc = 0x2003F10;
    vf114__12PhysicsActorFv = __deleted_virtual_called;
    vf134__12PhysicsActorFv = __deleted_virtual_called;
    vf13C__12PhysicsActorFv = 0x2004008;
    vf144__12PhysicsActorFb = 0x200375C;
    vf14C__12PhysicsActorFP10StageActor = 0x2003760;
    move__12PhysicsActorFR13Vec2__tm__2_f = 0x2004020;
    getRect__12PhysicsActorFR4Rect = 0x200404C;

/* PhysicsMgr */
    init__10PhysicsMgrFP10StageActorPCQ2_10PhysicsMgr6SensorN22 = 0x218AF6C;
    getSensor__10PhysicsMgrCFUi = 0x218CE74;
    setSensor__10PhysicsMgrFPCQ2_10PhysicsMgr6SensorUi = 0x218AEFC;
    processCollisions__10PhysicsMgrFv = 0x218D954;

/* PlayerInput */
    isUpHeld__11PlayerInputCFv = 0x2916114;
    isDownHeld__11PlayerInputCFv = 0x2915F84;
    isRightHeld__11PlayerInputCFv = 0x2915F9C;
    isLeftHeld__11PlayerInputCFv = 0x2915F90;

/* PlayerMgr */
    sInstance__9PlayerMgr = 0x101E6994;

/* Powerup */
    __ct__7PowerupFPC14ActorBuildInfo = 0x251EBFC;
    __dt__7PowerupFv = 0x251FE04;
    checkDerivedRuntimeTypeInfo__7PowerupCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x251FC68;
    getRuntimeTypeInfo__7PowerupCFv = __deleted_virtual_called;
    setPlayerID__7PowerupFSc = 0x251FAF0;
    StateID_PowerupState1__7Powerup = 0x1020AC50;
    getActorPhysicsMgr__7PowerupFv = 0x251FB1C;
    vfAC__7PowerupFv = 0x251FAF8;
    vfB4__7PowerupFv = 0x251FAFC;
    vfBC__7PowerupFv = 0x251FB04;
    vfC4__7PowerupFv = 0x251FB08;
    vfCC__7PowerupFv = 0x251FB0C;
    damageFromUnder__7PowerupFv = 0x251D8FC;
    vf10C__7PowerupFUc = 0x251FB14;
    vf11C__7PowerupFv = 0x251FC54;
    vf124__7PowerupFf = 0x251FC58;
    vf12C__7PowerupFv = 0x251FC5C;
    vf13C__7PowerupFv = 0x251FC4C;
    vf154__7PowerupFv = 0x251D918;
    move__7PowerupFR13Vec2__tm__2_f = 0x251FB2C;
    setYSpeed__7PowerupFf = 0x251FB40;
    vf16C__7PowerupFv = 0x251FB48;
    vf174__7PowerupFv = 0x251FB50;
    getRect__7PowerupFR4Rect = 0x251FB58;
    doStateChange__7PowerupFP9StateBase = 0x251FBC4;
    vf29C__7PowerupFv = 0x251FDEC;
    vf2A4__7PowerupFv = 0x251FDF0;
    vf2AC__7PowerupFv = 0x251EC6C;

/* PowerupBase */
    setupActor__11PowerupBaseFv = 0x2517F90;
    spawnMethod__11PowerupBaseFv = 0x2518470;
    updateModel__11PowerupBaseFv = 0x2518A4C;
    FUN_2518f94__11PowerupBaseFv = 0x2518F94;
    FUN_25183ac__11PowerupBaseFv = 0x25183AC;
    onDraw__11PowerupBaseFv = 0x25176EC;
    killAtGoal__11PowerupBaseFv = 0x2517BD0;
    splashWater__11PowerupBaseFP13Vec3__tm__2_f = 0x2517C20;
    splashLava__11PowerupBaseFP13Vec3__tm__2_f = 0x2517D5C;
    splashLavaWave__11PowerupBaseFP13Vec3__tm__2_f = 0x2517E18;
    splashPoison__11PowerupBaseFP13Vec3__tm__2_f = 0x2517ED4;
    vf144__11PowerupBaseFb = 0x251771C;
    vf1BC__11PowerupBaseFv = 0x251784C;
    vf1CC__11PowerupBaseFv = 0x25178C0;
    vf1D4__11PowerupBaseFv = 0x2517908;
    vf1DC__11PowerupBaseFv = 0x2517950;
    vf1E4__11PowerupBaseFv = 0x2517A40;
    vf1EC__11PowerupBaseFv = 0x2517A84;
    vf1F4__11PowerupBaseFv = 0x2517B3C;
    vf204__11PowerupBaseFv = 0x2517B4C;
    beginState_PowerupBaseState12__11PowerupBaseFv = 0x251BBE8;
    executeState_PowerupBaseState12__11PowerupBaseFv = 0x251BC88;
    endState_PowerupBaseState12__11PowerupBaseFv = 0x251DC94;
    beginState_PowerupBaseState13__11PowerupBaseFv = 0x251BD60;
    executeState_PowerupBaseState13__11PowerupBaseFv = 0x251BEAC;
    endState_PowerupBaseState13__11PowerupBaseFv = 0x251DC98;
    beginState_PowerupBaseState14__11PowerupBaseFv = 0x251C0D8;
    executeState_PowerupBaseState14__11PowerupBaseFv = 0x251C29C;
    endState_PowerupBaseState14__11PowerupBaseFv = 0x251DC9C;
    beginState_PowerupBaseState15__11PowerupBaseFv = 0x251C2AC;
    executeState_PowerupBaseState15__11PowerupBaseFv = 0x251C414;
    endState_PowerupBaseState15__11PowerupBaseFv = 0x251DCA0;
    beginState_PowerupBaseState16__11PowerupBaseFv = 0x251C424;
    executeState_PowerupBaseState16__11PowerupBaseFv = 0x251C530;
    endState_PowerupBaseState16__11PowerupBaseFv = 0x251DCA4;
    beginState_SpatByYoshi__11PowerupBaseFv = 0x251C5FC;
    executeState_SpatByYoshi__11PowerupBaseFv = 0x251C714;
    endState_SpatByYoshi__11PowerupBaseFv = 0x251DCA8;
    FUN_25196e8__11PowerupBaseFPvQ2_11PowerupBase12PowerupStateUi = 0x25196E8;
    FUN_2519580__11PowerupBaseFUiT1 = 0x2519580;

/* Profile */
    profilesOriginal__7Profile = 0x101ED8DC;
    prioritiesOriginal__7Profile = 0x10001940;
    hasResourcesOriginal__7Profile = 0x10002064;
    resourceCountOriginal__7Profile = 0x100023F8;
    resourceListsOriginal__7Profile = 0x101C321C;

/* RDashMgr */
    sInstance__8RDashMgr = 0x101E7D9C;

/* Rect */
    sZero__4Rect = 0x105EA79C;

/* RectCollider */
    __vtbl__12RectCollider = 0x100FB820;

/* ResArchive */
    getModel__10ResArchiveFRCQ2_4sead23SafeStringBase__tm__2_cUiN42bPQ2_4sead4Heap = 0x24EE440;

/* ResArchiveMgr */
    sInstance__13ResArchiveMgr = 0x101D2D50;
    get__13ResArchiveMgrFRCQ2_4sead23SafeStringBase__tm__2_c = 0x24F60EC;

/* ResMgr */
    ResMgr_LoadLevelResource = 0x29D2A20;
    ResMgr_LoadLevelArchiveFail = 0x29D333C;
    ResMgr_LoadLevelArchiveSuccess = 0x29D3354;

/* SaveMgr */
    sInstance__7SaveMgr = 0x101E7DA4;

/* ShaderAnimation */
    playTexSrtAnim__15ShaderAnimationFP10ResArchiveRCQ2_4sead23SafeStringBase__tm__2_c = 0x24FEE50;

/* ShapedCollider */
    __ct__14ShapedColliderFiP13Vec2__tm__2_fPQ2_12ColliderBase4NodeT3 = 0x21A7904;
    execute__14ShapedColliderFv = 0x21A871C;
    __CPR62__init__14ShapedColliderFP10StageActorRCQ2_J6J4Info = 0x21AD3BC;
    __dt__14ShapedColliderFv = 0x21A7A04;

/* SkeletalAnimation */
    play__17SkeletalAnimationFP10ResArchiveRCQ2_4sead23SafeStringBase__tm__2_c = 0x24FDADC;

/* SoundSystem */
    sInstance__11SoundSystem = 0x101E7C84;

/* SoundSystemBase */
    getAudioFx__15SoundSystemBaseFv = 0x29B1AA4;

/* StageActor */
    __vtbl__10StageActor = 0x10000268;
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x101E9CBC;
    typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x101E9CC0;
    __ct__10StageActorFPC14ActorBuildInfo = 0x2000AC8;
    directionToPlayerH__10StageActorFRC13Vec3__tm__2_f = 0x20005EC;
    directionToActorH__10StageActorFRC10StageActor = 0x200C800;
    distanceToPlayer__10StageActorFR4Vec2 = 0x20005A4;
    deleteActorWhenOutOfView__10StageActorFUi = 0x20007A0;
    actorAcCallback0__10StageActorFP14HitboxColliderP4Vec2 = 0x219E7E8;
    actorAcCallback2__10StageActorFP14HitboxColliderP4Vec2 = 0x219E8A4;
    actorCbCallback0__10StageActorFP12ColliderBaseP4Vec2 = 0x219E8B8;
    checkDerivedRuntimeTypeInfo__10StageActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x2002A38;
    getRuntimeTypeInfo__10StageActorCFv = __deleted_virtual_called;
    __dt__10StageActorFv = 0x2000F18;
    afterCreate__10StageActorFUi = 0x2000FB8;
    beforeExecute__10StageActorFv = 0x2000FE8;
    afterExecute__10StageActorFUi = 0x20010BC;
    beforeDraw__10StageActorFv = 0x20011A0;
    removeHitboxColliders__10StageActorFv = 0x20002CC;
    addHitboxColliders__10StageActorFv = 0x2000328;
    killAtGoal__10StageActorFv = 0x2002AD8;
    splashWater__10StageActorFP13Vec3__tm__2_f = 0x2002ADC;
    splashLava__10StageActorFP13Vec3__tm__2_f = 0x2002AE0;
    splashLavaWave__10StageActorFP13Vec3__tm__2_f = 0x2000960;
    splashPoison__10StageActorFP13Vec3__tm__2_f = 0x2002AE4;
    isOffScreen__10StageActorFv = 0x2001254;
    setPlayerID__10StageActorFSc = 0x2002AB0;
    getActorPhysicsMgr__10StageActorFv = 0x2002AB8;
    damageFromUnder__10StageActorFv = 0x2002AE8;
    vfAC__10StageActorFv = 0x2002AC0;
    vfB4__10StageActorFv = 0x2002AC4;
    vfBC__10StageActorFv = 0x2002ACC;
    vfC4__10StageActorFv = 0x2002AD0;
    vfCC__10StageActorFv = 0x2002AD4;
    distanceToPlayer__10StageActorFR13Vec2__tm__2_f = 0x20005A4;

/* StateBase */
    sCurrentID__9StateBase = 0x101E9F04;

/* StateMgr */
    execute__8StateMgrFv = 0x29C4A80;
    changeState__8StateMgrFP9StateBase = 0x29C4AF0;

/* TaskMgr */
    sInstance__7TaskMgr = 0x101E7B28;
    startLevel__7TaskMgrFPQ2_4sead8TaskBaseUcT2 = 0x29941D0;
    changeTask__7TaskMgrFPQ2_4sead8TaskBaseRQ2_4sead11TaskClassIDUiT3 = 0x2994164;

/* WindGenerator */
    __dt__13WindGeneratorFv = 0x288EFA0;
    checkDerivedRuntimeTypeInfo__13WindGeneratorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x288EEFC;
    getRuntimeTypeInfo__13WindGeneratorCFv = __deleted_virtual_called;
    onCreate__13WindGeneratorFv = 0x288EBC4;
    setPlayerID__13WindGeneratorFSc = 0x288EF74;
    getActorPhysicsMgr__13WindGeneratorFv = 0x288EF7C;
    vfAC__13WindGeneratorFv = 0x288EF84;
    vfB4__13WindGeneratorFv = 0x288EF88;
    vfBC__13WindGeneratorFv = 0x288EF90;
    vfC4__13WindGeneratorFv = 0x288EF94;
    vfCC__13WindGeneratorFv = 0x288EF98;
    damageFromUnder__13WindGeneratorFv = 0x288EF9C;

/* Unknown Class */
    FUN_02902b08__FP10StageActor = 0x2902B08;
    setBufferedString = 0x29D4240;
    formatBufferedString = 0x2A0F308;

/* Misc */
    BLOSDynLoad_Acquire = 0x2A9EF58;
    BOSDynLoad_FindExport = 0x2A9F418;
    DefaultReverbHiParam = 0x1022D328;
    DefaultDelayParam = 0x1022D354;
    moveValueTo__FPUiUiT2 = 0x29E0DE8;
    SFXReverb_0 = 0x101E7D14;
    SFXReverb_1 = 0x101E7D18;
    SFXReverbPlyJump_0 = 0x101E7D1C;
    SFXReverbPlyJump_1 = 0x101E7D20;
    nullterminator = 0x1018A56D;
    moveFloatTo__FRffT2 = 0x2027984;
    SE_VOC = 0x1018393C;
    mapPositionToScreen__FR13Vec2__tm__2_fRC13Vec2__tm__2_f = 0x2029368;
}
