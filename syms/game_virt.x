SECTIONS {

/* Math */
    sinf = 0x2AFDD40;
    cosf = 0x2AFE528;
    atan2f = 0x2AFE670;
    fmodf = 0x2AFD97C;
    powf = 0x2AFDEA8;
    sqrtf = 0x2AFDCCC;
    globalSinCosTbl__Q3_2nw4math8internal = 0x10191538;

/* new/delete */
    __nw__FUi = 0x29F1594;
    __nw__FUiPQ2_4sead4Heapi = 0x29F1858;
    __nwa__FUi = 0x29F1630;
    __nwa__FUiPQ2_4sead4Heapi = 0x29F18DC;
    __dl__FPv = 0x29F1748;
    __dla__FPv = 0x29F17D0;

/* GHS */
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
    _f_ftoll = 0x2AFEBFC;
    __array_new_prefix_size = 0x101E9338;
    __placement_array_new = 0x2AFA30C;

/* Cafe SDK Static */
    ASM_MTXConcat = 0x2AF98A0;
    ASM_MTXScale = 0x2AF9B64;
    ASM_VECDistance = 0x2AF9718;
    GFDGetPixelShaderCount = 0x2AF8C10;
    GFDGetPixelShaderHeaderSize = 0x2AF8D10;
    GFDGetPixelShaderProgramSize = 0x2AF8D40;
    GFDGetPixelShader = 0x2AF8FC0;
    GFDGetVertexShaderCount = 0x2AF8C04;
    GFDGetVertexShaderHeaderSize = 0x2AF8D00;
    GFDGetVertexShaderProgramSize = 0x2AF8D40;
    GFDGetVertexShader = 0x2AF8E3C;
    _GFDCheckHeaderVersions = 0x02AF8A18;
    _GFDCheckBlockHeaderMagicVersions = 0x02AF8ABC;
    _GFDRelocateBlock = 0x02AF8E04;

/* agl::RenderBuffer */
    __ct__Q2_3agl12RenderBufferFR13Vec2__tm__2_ffN32 = 0x2A1EADC;
    __ct__Q2_3agl12RenderBufferFv = 0x2A1E9DC;
    __dt__Q2_3agl12RenderBufferFv = 0x2A1E33C;
    clear__Q2_3agl12RenderBufferFUiT1RCQ2_4sead7Color4ffT1 = 0x2A1E644;
    initialize__Q2_3agl12RenderBufferFv = 0x2A1E9B4;

/* agl::RenderTargetColor */
    __ct__Q2_3agl17RenderTargetColorFv = 0x2A1EFDC;

/* agl::ShaderProgramArchive */
    __ct__Q2_3agl20ShaderProgramArchiveFv = 0x2A22934;
    FUN_2A23f1C__Q2_3agl20ShaderProgramArchiveFPUcRCUiUiPQ2_4sead4Heap = 0x2A23F1C;

/* agl::TextureData */
    __ct__Q2_3agl11TextureDataFv = 0x2A249A0;
    invalidateGPUCache__Q2_3agl11TextureDataFv = 0x2A24A64;
    initializeFromSurface__Q2_3agl11TextureDataFRC11_GX2Surface = 0x2A24E80;

/* agl::TextureDataInitializerGTX */
    initialize__Q2_3agl25TextureDataInitializerGTXSFPQ2_3agl11TextureDataPvUi = 0x2A24F38;

/* agl::TextureSampler */
    __ct__Q2_3agl14TextureSamplerFv = 0x2A2587C;
    __ct__Q2_3agl14TextureSamplerFRCQ2_3agl11TextureData = 0x2A25A64;
    __dt__Q2_3agl14TextureSamplerFv = 0x2A25C60;
    applyTextureData___Q2_3agl14TextureSamplerFRCQ2_3agl11TextureData = 0x2A25990;

/* agl::driver::GX2Resource */
    sInstance__Q3_3agl6driver11GX2Resource = 0x101E88C4;
    restoreContextState__Q3_3agl6driver11GX2ResourceFv = 0x2A283C4;

/* agl::lyr::Layer */
    pushBackDrawMethod__Q3_3agl3lyr5LayerFUiPQ3_3agl3lyr18DrawMethodImplBase = 0x2A376B8;
    pushBackDrawMethod__Q3_3agl3lyr5LayerFPQ3_3agl3lyr10DrawMethod = 0x2A37710;

/* agl::lyr::Renderer */
    draw__Q3_3agl3lyr8RendererCFQ3_3agl3lyr11DisplayType = 0x2A3AB90;
    sInstance__Q3_3agl3lyr8Renderer = 0x101E8A2C;
    initLayer___Q3_3agl3lyr8RendererFPQ3_3agl3lyr5LayerUiRCQ2_4sead23SafeStringBase__tm__2_cT2PQ2_4sead4Heap = 0x2A3AEE8;

/* agl::lyr::RenderInfo */
    __ct__Q3_3agl3lyr10RenderInfoFQ3_3agl3lyr11DisplayTypePCQ2_4sead11FrameBufferbPCQ3_3agl3lyr5LayerPQ2_3agl11DisplayList = 0x2a3b2c0;

/* agl::utl::DevTools */
    drawTextureTexCoord__Q3_3agl3utl8DevToolsSFRCQ2_3agl14TextureSamplerRC5Mtx34RC5Mtx44RC13Vec2__tm__2_ffT4Q2_3agl10ShaderMode = 0x2A51A28;

/* agl::utl::ImageFilter2D */
    drawTextureMSAA__Q3_3agl3utl13ImageFilter2DSFRCQ2_3agl14TextureSamplerRCQ2_4sead8ViewportRC13Vec2__tm__2_fT3Ui = 0x2A533EC;

/* sead::CalculateTask */
    RTTI__Q2_4sead13CalculateTask = 0x101ea764;
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

/* sead::Camera */
    __vtbl__Q2_4sead6Camera = 0x10190824;

/* sead::ControllerMgr */
    sInstance__Q2_4sead13ControllerMgr = 0x101E7EFC;

/* sead::FileDevice */
    tryClose__Q2_4sead10FileDeviceFPQ2_4sead10FileHandle = 0x29F78C0;
    tryWrite__Q2_4sead10FileDeviceFPUiPQ2_4sead10FileHandlePCUcUi = 0x29F7AE8;
    __CPR84__trySeek__Q2_4sead10FileDeviceFPQ2_J12J10FileHandleiQ3_J12JJ17J10SeekOrigin = 0x29F7B98;

/* sead::FileDeviceMgr */
    sInstance__Q2_4sead13FileDeviceMgr = 0x101E7F18;
    tryLoad__Q2_4sead13FileDeviceMgrFRQ3_4sead10FileDevice7LoadArg = 0x29F8BBC;
    tryOpen__Q2_4sead13FileDeviceMgrFPQ2_4sead10FileHandleRCQ2_4sead23SafeStringBase__tm__2_cQ3_4sead10FileDevice12FileOpenFlagUi = 0x29F8B0C;

/* sead::FileHandle */
    read__Q2_4sead10FileHandleFPUcUi = 0x29F81D0;
    getFileSize__Q2_4sead10FileHandleFv = 0x29F8368;

/* sead::FrameBuffer */
    bind__Q2_4sead11FrameBufferCFv = 0x2A058F0;

/* sead::FrustumProjection */
    __ct__Q2_4sead17FrustumProjectionFfN51 = 0x2A06944;
    __dt__Q2_4sead17FrustumProjectionFv = 0x2A06A4C;

/* sead::GlobalRandom */
    sInstance__Q2_4sead12GlobalRandom = 0x101E806C;

/* sead::GraphicsContext */
    __ct__Q2_4sead15GraphicsContextFv = 0x2A07BBC;
    apply__Q2_4sead15GraphicsContextFv = 0x2A07CB0;

/* sead::HeapMgr */
    sRootHeaps__Q2_4sead7HeapMgr = 0x105EA148;
    sInstancePtr__Q2_4sead7HeapMgr = 0x101E8040;
    getCurrentHeap__Q2_4sead7HeapMgrFv = 0x2A0D554;

/* sead::IDisposer */
    __ct__Q2_4sead9IDisposerFv = 0x2A0A2FC;
    __dt__Q2_4sead9IDisposerFv = 0x2A0A384;

/* sead::LookAtCamera */
    __dt__Q2_4sead12LookAtCameraFv = 0x2A04B94;
    __vtbl__Q2_4sead12LookAtCamera = 0x1019084C;
    doUpdateMatrix__Q2_4sead12LookAtCameraCFP5Mtx34 = 0x2A04BE8;

/* sead::MathCalcCommon */
    chase__Q2_4sead23MathCalcCommon__tm__2_fSFPZ1ZZ1ZT2_b = 0x2027984;
    chase__Q2_4sead24MathCalcCommon__tm__3_UiSFPZ1ZZ1ZT2_b = 0x29E0DE8;
    cSinCosTbl__Q2_4sead23MathCalcCommon__tm__2_f = 0x10191538;

/* sead::OrthoCamera */
    __ct__Q2_4sead11OrthoCameraFv = 0x2A04D54;

/* sead::OrthoProjection */
    __ct__Q2_4sead15OrthoProjectionFv = 0x2A06518;
    __ct__Q2_4sead15OrthoProjectionFfT1RCQ2_4sead8Viewport = 0x2A066B4;
    setTBLR__Q2_4sead15OrthoProjectionFfN31 = 0x2A06818;
    __dt__Q2_4sead15OrthoProjectionFv = 0x2A067C4;

/* sead::PerspectiveProjection */
    __ct__Q2_4sead21PerspectiveProjectionFv = 0x2A06108;
    __ct__Q2_4sead21PerspectiveProjectionFfN31 = 0x2A061AC;
    set__Q2_4sead21PerspectiveProjectionFfN31 = 0x2A062EC;
    __dt__Q2_4sead21PerspectiveProjectionFv = 0x2A06298;

/* sead::PrimitiveRenderer */
    sInstance__Q2_4sead17PrimitiveRenderer = 0x101E8010;
    setCamera__Q2_4sead17PrimitiveRendererFRCQ2_4sead6Camera = 0x2A083D0;
    setProjection__Q2_4sead17PrimitiveRendererFRCQ2_4sead10Projection = 0x2A083E4;
    setModelMatrix__Q2_4sead17PrimitiveRendererFRC5Mtx34 = 0x2A083F8;
    begin__Q2_4sead17PrimitiveRendererFv = 0x2A08408;
    end__Q2_4sead17PrimitiveRendererFv = 0x2A0841C;

/* sead::PrimitiveRendererCafe */
    drawTriangles___Q2_4sead21PrimitiveRendererCafeFRC5Mtx34RCQ2_4sead7Color4fT2PQ3_4sead21PrimitiveRendererUtil6VertexUiPUsT5PC11_GX2Texture = 0x2A0A190;

/* sead::Projection */
    getDeviceProjectionMatrix__Q2_4sead10ProjectionCFv = 0x2A05A9C;

/* sead::Random */
    getU32__Q2_4sead6RandomFv = 0x2A13780;

/* sead::SafeStringBase */
    sNullChar__Q2_4sead23SafeStringBase__tm__2_c = 0x1011BF6B;

/* sead::TaskBase */
    pauseCalcChild__Q2_4sead8TaskBaseFb = __deleted_virtual_called;
    pauseDrawChild__Q2_4sead8TaskBaseFb = __deleted_virtual_called;
    prepare__Q2_4sead8TaskBaseFv = 0x29FFF6C;
    exit__Q2_4sead8TaskBaseFv = 0x29FFF74;
    onEvent__Q2_4sead8TaskBaseFRCQ2_4sead9TaskEvent = 0x29FFF78;
    onDestroy__Q2_4sead8TaskBaseFv = __deleted_virtual_called;
    enterCommon__Q2_4sead8TaskBaseFv = 0x29FF818;
    adjustHeapAll__Q2_4sead8TaskBaseFv = 0x29FF9DC;
    RTTI__Q2_4sead8TaskBase = 0x101ea768;

/* sead::Viewport */
    __ct__Q2_4sead8ViewportFfN31 = 0x2A072FC;
    __ct__Q2_4sead8ViewportFRCQ2_4sead18LogicalFrameBuffer = 0x2A074C8;
    apply__Q2_4sead8ViewportCFRCQ2_4sead18LogicalFrameBuffer = 0x2A0783C;

/* Actor */
    RTTI__5Actor = 0x101e9cc8;
    __ct__5ActorFPC14ActorBuildInfo = 0x2002CE0;
    __dt__5ActorFv = 0x2002E68;
    __vtbl__5Actor = 0x100006C0;
    checkDerivedRuntimeTypeInfo__5ActorCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x2002F40;
    getRuntimeTypeInfo__5ActorCFv = __deleted_virtual_called;
    onCreate__5ActorFv = 0x2002F84;
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
    findActorByID__11ActorBufferFRCUi = 0x200A5C8;

/* ActorGlobalsHolder */
    sInstance__18ActorGlobalsHolder = 0x101C30D0;

/* ActorInfo */
    sDefault__9ActorInfo = 0x100018F4;

/* ActorMgr */
    sInstance__8ActorMgr = 0x101C30C8;
    create__8ActorMgrFR14ActorBuildInfoUi = 0x2009A58;
    findActorByType__8ActorMgrFQ2_9ProfileId13ProfileIdTypePP5Actor = 0x2009B6C;
    createInstance__8ActorMgrSFPQ2_4sead4Heap = 0x2008CB4;
    createHeaps__8ActorMgrFPQ2_4sead4Heap = 0x200959C;
    executeActors__8ActorMgrFv = 0x2009D58;
    drawActors__8ActorMgrFv = 0x2009ECC;

/* AreaTask */
    sInstance__8AreaTask = 0x101D1598;

/* Animation */
    shouldLoop__9AnimationFb = 0x24DEED4;
    reset__9AnimationFv = 0x24DEEAC;

/* ZoneRumbleMgr */
    sInstance__13ZoneRumbleMgr = 0x101D1660;
    rumble__13ZoneRumbleMgrFiScN22 = 0x24C4D3C;

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

/* Boss */
    RTTI__4Boss = 0x101e9f24;
    getRuntimeTypeInfo__4BossCFv = __deleted_virtual_called;
    FUN_202D0F8__4BossFP10StageActorP13Vec3__tm__2_fUi = 0x202D0F8;
    FUN_202D030__4BossFP10StageActorP13Vec3__tm__2_fUi = 0x202D030;
    checkDerivedRuntimeTypeInfo__4BossCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x202dab0;
    StateID_BossState1__4Boss = 0x101f09e0;
    StateID_BossState5__4Boss = 0x101f0a70;
    onCreate__4BossFv = 0x202bb68;
    setPlayerID__4BossFSc = 0x202d9c0;
    removeHitboxColliders__4BossFv = 0x202ddf0;
    addHitboxColliders__4BossFv = 0x202de7c;
    getActorPhysicsMgr__4BossFv = 0x202d9f8;
    move__4BossFR13Vec2__tm__2_f = 0x202da00;
    collisionPlayer__4BossFP14HitboxColliderT1 = 0x202bfdc;
    collisionYoshi__4BossFP14HitboxColliderT1 = 0x202c2b4;
    collisionStar__4BossFP14HitboxColliderT1 = 0x202dcc8;
    collisionSlide__4BossFP14HitboxColliderT1 = 0x202dcd0;
    collisionPropellerDrill__4BossFP14HitboxColliderT1 = 0x202c5d0;
    vf244__4BossFP14HitboxColliderT1 = 0x202dcd8;
    collisionGroundPound__4BossFP14HitboxColliderT1 = 0x202c3ac;
    collisionPenguinSlide__4BossFP14HitboxColliderT1 = 0x202c5e0;
    collisionThrowableObject__4BossFP14HitboxColliderT1 = 0x202c8e0;
    collisionFireball__4BossFP14HitboxColliderT1 = 0x202c6d4;
    collisionIceball__4BossFP14HitboxColliderT1 = 0x202cbcc;
    addScoreWhenHit__4BossFv = 0x202dd38;
    onStomp__4BossFP10StageActor = 0x202d214;
    onStompKill__4BossFP10StageActor = 0x202df2c;
    __ct__4BossFPC14ActorBuildInfo = 0x202b968;
    __dt__4BossFv = 0x202e2e0;
    beforeExecute__4BossFv = 0x202bd0c;
    afterExecute__4BossFUi = 0x202bddc;
    onDelete__4BossFv = 0x202dc2c;
    setPlayerId__4BossFSc = 0x202d9c0;
    removeActiveColliders__4BossFv = 0x202ddf0;
    addActiveColliders__4BossFv = 0x202de7c;
    getCollisionMgr__4BossFv = 0x202d9f8;
    vfAC__4BossFv = 0x202d9c8;
    vfB4__4BossFv = 0x202d9cc;
    vfBC__4BossFv = 0x202d9d4;
    vfC4__4BossFv = 0x202d9d8;
    vfCC__4BossFv = 0x202d9dc;
    vf10C__4BossFUc = 0x202d9e0;
    vf11C__4BossFv = 0x202d9e8;
    vf124__4BossFf = 0x202d9ec;
    vf12C__4BossFv = 0x202d9f0;
    vf154__4BossFv = 0x202ce40;
    move__4BossFR4Vec2 = 0x202da00;
    setYSpeed__4BossFf = 0x202da14;
    vf16C__4BossFv = 0x202da1c;
    vf174__4BossFv = 0x202da24;
    getRect__4BossFR4Rect = 0x202e254;
    vf18C__4BossFv = 0x202daa8;
    freeze__4BossFv = 0x202ceac;
    vf1BC__4BossFv = 0x202cf64;
    vf1C4__4BossFv = 0x202e2d0;
    collisionPlayer__4BossFP14ActiveColliderT1 = 0x202bfdc;
    collisionYoshi__4BossFP14ActiveColliderT1 = 0x202c2b4;
    collisionStar__4BossFP14ActiveColliderT1 = 0x202dcc8;
    collisionSlide__4BossFP14ActiveColliderT1 = 0x202dcd0;
    collisionPropellerDrill__4BossFP14ActiveColliderT1 = 0x202c5d0;
    vf244__4BossFP14ActiveColliderT1 = 0x202dcd8;
    collisionGroundPound__4BossFP14ActiveColliderT1 = 0x202c3ac;
    collisionPenguinSlide__4BossFP14ActiveColliderT1 = 0x202c5e0;
    collisionThrowableObject__4BossFP14ActiveColliderT1 = 0x202c8e0;
    collisionFireball__4BossFP14ActiveColliderT1 = 0x202c6d4;
    collisionIceball__4BossFP14ActiveColliderT1 = 0x202cbcc;
    isOnGround__4BossFv = 0x202ce00;
    vf2F4__4BossFv = 0x202dd38;
    beginState_DieFumi__4BossFv = 0x202dc9c;
    executeState_DieFumi__4BossFv = 0x202dca0;
    endState_DieFumi__4BossFv = 0x202dca4;
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
    startCutscene__4BossFv = 0x202dca8;
    endCutscene__4BossFv = 0x202dcb4;
    vf56C__4BossFv = 0x202dcc0;
    vf574__4BossFv = 0x202bfbc;
    vf57C__4BossFv = 0x202dcc4;
    vf584__4BossFv =  __deleted_virtual_called;
    vf58C__4BossFv = 0x202dd3c;
    vf594__4BossFv = 0x202dd4c;
    vf59C__4BossFv =  __deleted_virtual_called;
    isNextDamageKill__4BossFv =  __deleted_virtual_called;
    vf5AC__4BossFv =  __deleted_virtual_called;
    isDamageHit__4BossFv = 0x202dd90;
    processHits__4BossFUi = 0x202dd98;
    playDamageAnim__4BossFv = 0x202ddbc;
    timerEnd__4BossFv = 0x202ddc0;
    beforeUpdate__4BossFv = 0x202ddc4;
    fireTime__4BossFv = 0x202ddc8;
    vf624__4BossFv =  __deleted_virtual_called;
    stompTime__4BossFv = 0x202ddd0;
    vf634__4BossFUi = 0x202ddd8;
    vf63C__4BossFUi = 0x202dde4;
    vf644__4BossFv = 0x202d120;
    onStomp__4BossFP5Actor = 0x202d214;
    onStompDamage__4BossFP5Actor = 0x202df28;
    onStompKill__4BossFP5Actor = 0x202df2c;
    vf664__4BossFv = 0x202df44;
    changeState_BossState1__4BossFv = 0x202df48;
    onGroundPoundDamage__4BossFv = 0x202df60;
    onGroundPoundKill__4BossFv = 0x202df70;
    vf684__4BossFv =  __deleted_virtual_called;
    vf68C__4BossFv =  __deleted_virtual_called;
    vf694__4BossFv =  __deleted_virtual_called;
    vf69C__4BossFv =  __deleted_virtual_called;
    onStompDamageEx__4BossFv = 0x202df80;
    onStompKillEx__4BossFv = 0x202df84;
    onStompDamage2__4BossFv = 0x202df9c;
    onStompKill2__4BossFv = 0x202dfa0;
    vf6C4__4BossFv =  __deleted_virtual_called;
    vf6CC__4BossFv =  __deleted_virtual_called;
    vf6D4__4BossFv = 0x202dfb8;
    onDamage__4BossFv = 0x202dfc0;
    onKill__4BossFv = 0x202dfc4;
    immuneToGroundPound__4BossFv = 0x202dfd4;
    vf6F4__4BossFv = 0x202dfdc;
    vf6FC__4BossFv = 0x202dfe4;
    immuneToFire__4BossFv = 0x202dfec;
    vf70C__4BossFv =  __deleted_virtual_called;
    vf714__4BossFv =  __deleted_virtual_called;
    vf71C__4BossFv =  __deleted_virtual_called;
    spawnDamageKillEffect__4BossFv = 0x202dff4;
    spawnDamageNormalEffect__4BossFv = 0x202dff8;
    vf734__4BossFv = 0x202dffc;
    vf73C__4BossFv =  __deleted_virtual_called;
    vf744__4BossFv = 0x202e000;
    playStompSound__4BossFv = 0x202e004;
    playStompKillSound__4BossFv = 0x202e01c;
    vf75C__4BossFv =  __deleted_virtual_called;
    playStarKillSound__4BossFv = 0x202e034;
    vf76C__4BossFv =  __deleted_virtual_called;
    playDamageKillSound__4BossFv = 0x202e04c;
    playFireDamageSound__4BossFv = 0x202e064;
    playDamageKillFSound__4BossFv = 0x202e0d8;
    playFireDamageSound2__4BossFv = 0x202e130;
    playFireKillSound__4BossFv = 0x202e1a4;
    playStarDamageSound__4BossFv = 0x202e1fc;
    playDamageKillFSound2__4BossFv = 0x202e214;
    playLoseSound__4BossFv = 0x202e22c;
    vf7B4__4BossFv =  __deleted_virtual_called;
    vf7BC__4BossFv =  __deleted_virtual_called;
    setLookTarget__4BossFv = 0x202e230;
    vf7CC__4BossFv = 0x202d3bc;
    initHitboxCollider__4BossFv = 0x202d3f4;
    initModels__4BossFv = 0x202e2b8;
    initHitsToDeath__4BossFv = 0x202e2c0;
    initHitsToDamage__4BossFv = 0x202e2c4;
    init__4BossFv = 0x202e2c8;
    updateModelTrampoline__4BossFv = 0x23291DC;
    FUN_202D094__4BossFP10StageActorP13Vec3__tm__2_fUi = 0x202d094;

/* BossController */
    getRuntimeTypeInfo__14BossControllerCFv = __deleted_virtual_called;
    checkDerivedRuntimeTypeInfo__14BossControllerCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x202f644;
    StateID_StartSequence__14BossController = 0x101f0ac4;
    __ct__14BossControllerFPC14ActorBuildInfo = 0x202e448;
    __dt__14BossControllerFv = 0x202f7c0;
    onCreate__14BossControllerFv = 0x202e4dc;
    onExecute__14BossControllerFv = 0x202e578;
    beginState_Initialize__14BossControllerFv = 0x202e6d4;
    executeState_Initialize__14BossControllerFv = 0x202e754;
    endState_Initialize__14BossControllerFv = 0x202ee6c;
    beginState_StartSequence__14BossControllerFv = 0x202e758;
    executeState_StartSequence__14BossControllerFv = 0x202e7d8;
    endState_StartSequence__14BossControllerFv = 0x202e948;
    beginState_Wait__14BossControllerFv = 0x202e9b8;
    executeState_Wait__14BossControllerFv = 0x202ead8;
    endState_Wait__14BossControllerFv = 0x202f784;
    beginState_EndSequence__14BossControllerFv = 0x202eb50;
    executeState_EndSequence__14BossControllerFv = 0x202ee6c;
    endState_EndSequence__14BossControllerFv = 0x202f788;
    vf1E4__14BossControllerFv = 0x202f110;
    vf1EC__14BossControllerFv = 0x202f158;
    vf21C__14BossControllerFv = 0x202f7b0;

/* CircularCollider */
    RTTI__16CircularCollider = 0x101EA398;

/* ColliderBase */
    RTTI__12ColliderBase = 0x101e9fa4;
    setType__12ColliderBaseFQ2_12ColliderBase4Type = 0x21A5A70;
    __CPR61__setSurfaceType__12ColliderBaseFQ2_J16J11SurfaceType = 0x21a5ad0;

/* ColliderBase::Node */
    __ct__Q2_12ColliderBase4NodeFv = 0x21A1ACC;

/* ColliderMgr */
    sInstance__11ColliderMgr = 0x101C9360;
    add__11ColliderMgrFP12ColliderBase = 0x219269C;
    remove__11ColliderMgrFP12ColliderBase = 0x219282C;

/* CourseTask */
    sInstance__10CourseTask = 0x101D15F0;
    construct__10CourseTaskSFRCQ2_4sead16TaskConstructArg = 0x202B4C8;

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
    RTTI__16CSCollisionActor = 0x101ea3e8;
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

/* CutsceneKamek */
    StateID_CutsceneKamekState2__13CutsceneKamek = 0x101F1BCC;

/* Direction */
    directionToRotationList__9Direction = 0x10200DD8;

/* DoorBase */
    RTTI__8DoorBase = 0x101eb330;
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
    setTargetLayer__7DrawMgrFPQ3_3agl3lyr5LayerUi = 0x24FAA50;
    resetTargetLayer__7DrawMgrFv = 0x24FAB4C;
    drawTile__7DrawMgrFUsRC13Vec3__tm__2_fRCUiT2 = 0x24fad28;

/* DRCModeTask */
    sInstance__11DRCModeTask = 0x101D1904;

/* Effect */
    spawn__6EffectSFUiPC13Vec3__tm__2_fPC14Vec3__tm__3_UiT2 = 0x22AB080;

/* Enemy */
    RTTI__5Enemy = 0x101e9ef0;
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

/* EnvTerrain */
    onExecute__10EnvTerrainFv = 0x26F0E9C;

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

/* LayerAGL */
    vf44__8LayerAglFv = 0x24F9340;
    vf4C__8LayerAglFv = 0x24F9344;

/* LayoutAnimator */
    __ct__14LayoutAnimatorFv = 0x25ce268;

/* LayoutContainer */
    __ct__15LayoutContainerFP14LayoutAnimatori = 0x2672f04;
    getArchive__15LayoutContainerFRCQ2_4sead23SafeStringBase__tm__2_c = 0x2673008;
    loadBFLYT__15LayoutContainerFRCQ2_4sead23SafeStringBase__tm__2_cUiN22 = 0x2673050;
    __dt__15LayoutContainerFv = 0x2672f80;

/* LayoutHandler */
    init__13LayoutHandlerFPQ2_4sead4Heap = 0x26711c8;
    update__13LayoutHandlerFUiP5Mtx34 = 0x2672a4c;
    draw__13LayoutHandlerFRC5Mtx44 = 0x2672d14;
    initAnims__13LayoutHandlerFPCQ2_4sead23SafeStringBase__tm__2_cRUi = 0x2671c54;
    playAnim__13LayoutHandlerFUiRCQ2_4sead23SafeStringBase__tm__2_cb = 0x2671680;

/* Level */
    sInstance__5Level = 0x101DB048;

/* Level::Area */
    getArea__5LevelFUi = 0x269A2DC;
    getLocation__Q2_5Level4AreaFP4RectUc = 0x269A020;
    getSprite__Q2_5Level4AreaFUiPQ3_5Level4Area6Sprite = 0x2699C08;

/* LevelCamera */
    sInstance__11LevelCamera = 0x101E7C54;

/* LevelInfo */
    sInstance__9LevelInfo = 0x101D18EC;
    setDestEntrance__9LevelInfoFSc = 0x24D2984;
    setDestWorld__9LevelInfoFUc = 0x24D293C;
    setDestLevel__9LevelInfoFUc = 0x24D2954;
    setDestArea__9LevelInfoFUc = 0x24D296C;
    setDestZone__9LevelInfoFUi = 0x24D299C;

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

/* MovementHandler */
    __ct__15MovementHandlerFv = 0x2849c40;
    execute__15MovementHandlerFv = 0x284b8c4;
    getMaskForMovementType__15MovementHandlerFUi = 0x284a37c;
    link__15MovementHandlerFRC13Vec3__tm__2_fUiUc = 0x284b6f4;

/* Mtx34 */
    rotateAndTranslate__5Mtx34FRC14Vec3__tm__3_UiRC13Vec3__tm__2_f = 0x203C1C8;
    makeST__5Mtx34SFR5Mtx34RC13Vec3__tm__2_fT2 = 0x2222A88;
    makeSRT__5Mtx34SFR5Mtx34RC13Vec3__tm__2_fN22 = 0x2508424;

/* MultiStateActor */
    RTTI__15MultiStateActor = 0x101e9ce8;
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

/* MusicPlayer */
    shouldHurryUp__11MusicPlayerFv = 0x29B83D8;

/* ObjLayer */
    checkDerivedRuntimeTypeInfo__8ObjLayerCFPCQ3_4sead15RuntimeTypeInfo9Interface = 0x24FCF4C;
    getRuntimeTypeInfo__8ObjLayerCFv = __deleted_virtual_called;
    vf3C__8ObjLayerFv = 0x24FD0E8;
    vf5C__8ObjLayerFv = 0x24FD0F4;
    setParentRenderer__8ObjLayerFP16ObjLayerRenderer = 0x24FCA24;

/* ObjLayerRenderer */
    __dt__16ObjLayerRendererFv = 0x24FB0AC;
    __ct__16ObjLayerRendererFRCQ2_4sead23SafeStringBase__tm__2_c = 0x24FAF58;
    init__16ObjLayerRendererFUiN31PQ2_4sead4Heap = 0x24FB128;

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

/* PlatformModel */
    init__13PlatformModelFv = 0x27BE110;
    update__13PlatformModelFR13Vec3__tm__2_ff = 0x27BE428;
    draw__13PlatformModelFv = 0x27BE4FC;

/* Player */
    throwProjectile__6Player__PowerupStateNotFire = 0x293AE28;
    FUN_0293b080__6Player__IsProjectilePowerup = 0x293B198;

/* PlayerInput */
    isUpHeld__11PlayerInputCFv = 0x2916114;
    isDownHeld__11PlayerInputCFv = 0x2915F84;
    isRightHeld__11PlayerInputCFv = 0x2915F9C;
    isLeftHeld__11PlayerInputCFv = 0x2915F90;

/* PlayerMgr */
    sInstance__9PlayerMgr = 0x101E6994;

/* Poison */
    build__6PoisonSFPC14ActorBuildInfo = 0x26f6e6c;

/* Powerup */
    RTTI__7Powerup = 0x101ead38;
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
    initHitboxes__11PowerupBaseFv = 0x251784C;
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
    resourcesLoadAtOriginal__7Profile = 0x10002064;
    resourceCountOriginal__7Profile = 0x100023F8;
    resourceListsOriginal__7Profile = 0x101C321C;
    loadProfileResources__7ProfileSFQ2_7Profile15LoadResourcesAtPQ2_4sead4Heap = 0x200A738;

/* Quicksand */
    build__9QuicksandSFPC14ActorBuildInfo = 0x26f7c84;

/* RDashMgr */
    sInstance__8RDashMgr = 0x101E7D9C;

/* Rect */
    sZero__4Rect = 0x105EA79C;

/* RectCollider */
    __vtbl__12RectCollider = 0x100FB820;

/* RenderObjLayer */
    __ct__14RenderObjLayerFv = 0x24FCA6C;
    __dt__14RenderObjLayerFv = 0x24FCB18;
    vf24__14RenderObjLayerFv = 0x24FD00C;
    vf2C__14RenderObjLayerFPvUi = 0x24FCB6C;
    doInitialize__14RenderObjLayerFPQ2_4sead4Heap = 0x24FCBCC;
    vf54__14RenderObjLayerFUi = 0x24FD014;
    vf64__14RenderObjLayerFUi = 0x24FCE18;

/* ResArchive */
    getModel__10ResArchiveFRCQ2_4sead23SafeStringBase__tm__2_cUiN42bPQ2_4sead4Heap = 0x24EE440;

/* ResArchiveMgr */
    sInstance__13ResArchiveMgr = 0x101D2D50;
    get__13ResArchiveMgrFRCQ2_4sead23SafeStringBase__tm__2_c = 0x24F60EC;
    loadResArchive__13ResArchiveMgrFRCQ2_4sead23SafeStringBase__tm__2_cT1PQ2_4sead4Heap = 0x24F6140;

/* ResMgr */
    sInstance__6ResMgr = 0x101E7D94;
    loadRes__6ResMgrFRCQ2_4sead23SafeStringBase__tm__2_cT1PQ2_4sead4Heapb = 0x29D34A8;
    ResMgr_LoadLevelResource = 0x29D2A20;
    ResMgr_LoadLevelArchiveFail = 0x29D333C;
    ResMgr_LoadLevelArchiveSuccess = 0x29D3354;

/* SaveMgr */
    createInstance__7SaveMgrSFPQ2_4sead4Heap  = 0x29D6D00;
    sInstance__7SaveMgr = 0x101E7DA4;
    save__7SaveMgrFPQ2_4sead14DelegateThread = 0x29D9560;

/* ShaderAnimation */
    playTexSrtAnim__15ShaderAnimationFP10ResArchiveRCQ2_4sead23SafeStringBase__tm__2_c = 0x24FEE50;

/* ShapedCollider */
    __CPR62__init__14ShapedColliderFP10StageActorRCQ2_J6J4Info = 0x21ad3bc;
    execute__14ShapedColliderFv = 0x21a871c;
    __dt__14ShapedColliderFv = 0x21A7A04;
    RTTI__14ShapedCollider = 0x101e9fb4;

    /* //! THIS IS PROBABLY WRONG THE CTOR IS INLINED TODO: FIX THIS FIX THIS */
    __ct__14ShapedColliderFiP13Vec2__tm__2_fPQ2_12ColliderBase4NodeT3 = 0x21A7904;

/* SkeletalAnimation */
    play__17SkeletalAnimationFP10ResArchiveRCQ2_4sead23SafeStringBase__tm__2_c = 0x24FDADC;

/* SolidOnTopCollider */
    RTTI__18SolidOnTopCollider = 0x101E9FA8;
    __ct__18SolidOnTopColliderFv = 0x21a1d38;
    __dt__18SolidOnTopColliderFv = 0x21a1f18;
    execute__18SolidOnTopColliderFv = 0x21a2e0c;
    __CPR85__init__18SolidOnTopColliderFP10StageActorRCQ2_J6J4InfoiPQ2_4sead4Heap = 0x21a2378;

/* SoundSystem */
    sInstance__11SoundSystem = 0x101E7C84;

/* SoundSystemBase */
    getAudioFx__15SoundSystemBaseFv = 0x29B1AA4;

/* StageActor */
    actorHCCallback0__10StageActorFP14HitboxColliderP13Vec2__tm__2_f = 0x219e7e8;
    actorHCCallback2__10StageActorFP14HitboxColliderP13Vec2__tm__2_f = 0x219e8a4;
    actorCBCallback0__10StageActorFP12ColliderBaseP13Vec2__tm__2_f = 0x219e8b8;
    actorCBCallback2__10StageActorFP12ColliderBaseP13Vec2__tm__2_f = 0x219e974;
    RTTI__10StageActor = 0x101e9cc0;
    __vtbl__10StageActor = 0x10000268;
    __LSG__typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x101E9CBC;
    typeInfo__L0__getRuntimeTypeInfoStatic__10StageActorSFv = 0x101E9CC0;
    __ct__10StageActorFPC14ActorBuildInfo = 0x2000AC8;
    directionToPlayerH__10StageActorFRC13Vec3__tm__2_f = 0x20005EC;
    directionToPlayerV__10StageActorFRC13Vec3__tm__2_f = 0x20006B4;
    directionToActorH__10StageActorFRC10StageActor = 0x200C800;
    distanceToPlayer__10StageActorFR4Vec2 = 0x20005A4;
    offscreenDelete__10StageActorFUi = 0x20007A0;
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

/* StateActor */
    vfAC__10StateActorFv = 0x200ABB0;
    vfB4__10StateActorFv = 0x200ABB4;
    vfBC__10StateActorFv = 0x200ABBC;
    vfC4__10StateActorFv = 0x200ABC0;
    vfCC__10StateActorFv = 0x200ABC4;
    vf10C__10StateActorFUc = 0x200ABCC;
    vf11C__10StateActorFv = 0x200ABD4;
    vf124__10StateActorFf = 0x200ABD8;
    vf12C__10StateActorFv = 0x200ABDC;
    setYSpeed__10StateActorFf = 0x200AC08;
    vf16C__10StateActorFv = 0x200AC10;
    vf174__10StateActorFv = 0x200AC18;
    damageFromUnder__10StateActorFv = 0x200ABC8;
    vf154__10StateActorFv = 0x200ABEC;
    move__10StateActorFR13Vec2__tm__2_f = 0x200ABF4;
    setPlayerID__10StateActorFSc = 0x200ABA8;
    getActorPhysicsMgr__10StateActorFv = 0x200ABE4;
    getRect__10StateActorFR4Rect = 0x200AC20;

/* StateBase */
    sCurrentID__9StateBase = 0x101E9F04;
    sNullState__9StateBase = 0x1022D390;

/* StateMgr */
    __ct__8StateMgrFP17StateExecutorBaseP9StateBase = 0x29C4A08;
    execute__8StateMgrFv = 0x29C4A80;
    changeState__8StateMgrFP9StateBase = 0x29C4AF0;

/* TaskMgr */
    sInstance__7TaskMgr = 0x101E7B28;
    startLevel__7TaskMgrFPQ2_4sead8TaskBaseUcT2 = 0x29941D0;
    changeTask__7TaskMgrFPQ2_4sead8TaskBaseRQ2_4sead11TaskClassIDUiT3 = 0x2994164;

/* TerrainEffects */
    updateWaveCollisions__14TerrainEffectsFv = 0x28B8D5C;

/* TileMgr */
    sInstance__7TileMgr = 0x101DAB94;
    getTilePtrCurrentArea__7TileMgrSFUsT1UcPUi = 0x2685000;

/* Water */
    build__5WaterSFPC14ActorBuildInfo = 0x26f9af0;

/* WindGenerator */
    __dt__13WindGeneratorFv = 0x288EFA0;
    RTTI__13WindGenerator = 0x101e9cc0;
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

/* WrappedController */
    __ct__17WrappedControllerFv = 0x2514150;
    init__17WrappedControllerFUi = 0x25141B0;
    __dt__17WrappedControllerFv = 0x25140E8;

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
    SE_VOC = 0x1018393C;
    mapPositionToScreen__FR13Vec2__tm__2_fRC13Vec2__tm__2_f = 0x2029368;
    DAT_101c30d0 = 0x101C30D0;
    PlayerJumpArc = 0x1016A800;
    MiniPlayerJumpArc = 0x1016A848;
    PlayerJumpMax = 0x10166E68;
    PlayerDescentRate = 0x10166E74;
    InfiniteLivesContinue = 0x24C005C;
    InfiniteTimeContinue = 0x24C1388;
    InvincibilityContinue = 0x2931180;
}
