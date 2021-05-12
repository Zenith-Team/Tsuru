#pragma once

#include "sound.h"
#include "enemy.h"
#include "effect.h"
#include "misctemp.h"

// TODO: verify, finish if incomplete

class Boss : public Enemy {  // size: 0x
    SEAD_RTTI_OVERRIDE(Boss, Enemy)

public:
    Boss(const ActorBuildInfo* buildInfo);
    virtual ~Boss();

    u32 onCreate() override;
	u32 beforeExecute() override;
	void afterExecute(u32) override;
	u32 onDelete() override;
	
	bool checkDerivedRuntimeTypeInfo(void*);  // override?
	
	void removeActiveColliders() override;
	void addActiveColliders() override;
	bool vf154() override;
	
	DECLARE_STATE_VIRTUAL(Boss, BossState1)
	DECLARE_STATE_VIRTUAL(Boss, BossState2)
	DECLARE_STATE_VIRTUAL(Boss, BossState3)
	DECLARE_STATE_VIRTUAL(Boss, BossState4)
	DECLARE_STATE_VIRTUAL(Boss, BossState5)

	virtual void demoStart();       
	virtual void demoEnd();     
	virtual void vf56C();                               //nullsub
	virtual void vf574();       
	virtual void vf57C();                               //nullsub
	virtual void vf584();                       		//deleted
	virtual u8 vf58C();     
	virtual void vf594();       
	virtual void vf59C();                       		//deleted
	virtual bool isNextDamageKill();            		//deleted
	virtual void vf5AC();                       		//deleted
	virtual bool isDamageHit();     
	virtual void processHits(u32 amount);       
	virtual u32 getFireDamage() = 0;        
	virtual u32 getStompDamage() = 0;       
	virtual u32 getGroundPoundDamage() = 0;     
	virtual u32 vf5DC() = 0;                    		//deleted by sumo boss
	virtual u32 vf5E4() = 0;                    		//deleted by sumo boss
	virtual u32 vf5EC() = 0;                    		//deleted by sumo boss
	virtual u32 getStompDamage2() = 0;      
	virtual u32 getStompDamageEx() = 0;     
	virtual void playDamageAnim();                      //nullsub
	virtual void timerEnd();                            //nullsub
	virtual void beforeUpdate();                        //nullsub
	virtual u32 fireTime();                             //returns 24
	virtual void vf624();                       		//deleted
	virtual u32 stompTime();                            //returns 24
	virtual void vf634(PhysicsActor*);   
	virtual void vf63C(PhysicsActor*);   
	virtual void vf644();                               //Searches actor "Register for Fever -" and deletes it
	virtual void onStomp(PhysicsActor* player);   
	virtual void onStompDamage(PhysicsActor* other);    //nullsub
	virtual void onStompKill(PhysicsActor* killer);   
	virtual void vf664();                               //nullsub
	virtual void changeState_State1();  
	virtual void onGroundPoundDamage();                 //calls vf654
	virtual void onGroundPoundKill();   
	virtual void vf684();                       		//deleted
	virtual void vf68C();                       		//deleted
	virtual void vf694();                       		//deleted
	virtual void vf69C();                       		//deleted
	virtual void onStompDamageEx();                     //nullsub
	virtual void onStompKillEx();   
	virtual void onStompDamage2();                      //nullsub
	virtual void onStompKill2();    
	virtual void vf6C4();                       		//deleted
	virtual void vf6CC();                       		//deleted
	virtual u32 vf6D4();    							//returns 1
	virtual void onDamage();                            //nullsub
	virtual void onKill();                              //calls vf574
	virtual bool immuneToGroundPound(); 
	virtual u32 vf6F4();    
	virtual u32 vf6FC();    
	virtual bool immuneToFire();    
	virtual void vf70C();                       		//deleted
	virtual void vf714();                       		//deleted
	virtual void vf71C();                       		//deleted
	virtual EffectWrapper* spawnDamageKillEffect();     //nullsub
	virtual EffectWrapper* spawnDamageNormalEffect();   //nullsub
	virtual EffectWrapper* spawnDamageEffect();         //nullsub
	virtual void vf73C();                       		//deleted
	virtual u32 vf744();                                //nullsub
	virtual void playStompSound();
	virtual void playStompKillSound();
	virtual void vf75C();                       		//deleted
	virtual void playStarKillSound();
	virtual void vf76C();                       		//deleted
	virtual void playDamageKillSound();
	virtual void playFireDamageSound();
	virtual void playDamageKillFSound();
	virtual void playFireDamageSound2();
	virtual void playFireKillSound();
	virtual void playStarDamageSound();
	virtual void playDamageKillFSound2();
	virtual void playLoseSound();                       //nullsub
	virtual void vf7B4();                       		//deleted
	virtual void vf7BC();                       		//deleted
	virtual void vf7C4();                               //does some position stuff
	virtual u32 vf7CC();
	virtual void initActiveCollider();
	virtual void initModels();
	virtual void updateModel();
	virtual void initHitsToDeath();
	virtual void initHitsToDamage();
	virtual u32 init();									//returns 1

    bool freezeActor();
	void vf1BC();
	void vf1C4(); //Calls vf7E4
	void playerCollision(ActiveCollider* acSelf, ActiveCollider* acOther);
	void yoshiCollision(ActiveCollider* acSelf, ActiveCollider* acOther);
	void vf22C(ActiveCollider* acSelf, ActiveCollider* acOther);
	bool hitJump(ActiveCollider* acSelf, ActiveCollider* acOther);
	bool collidesSomething(ActiveCollider* acSelf, ActiveCollider* acOther);
	bool hitEnemyDown(ActiveCollider* acSelf, ActiveCollider* acOther);
	bool hitGroundPound(ActiveCollider* acSelf, ActiveCollider* acOther);
	bool hitEnemyKame2(ActiveCollider* acSelf, ActiveCollider* acOther);
	bool hitEnemyKameDown(ActiveCollider* acSelf, ActiveCollider* acOther);
	bool fireballCollision(ActiveCollider* acSelf, ActiveCollider* acOther);
	bool vf284(ActiveCollider* acSelf, ActiveCollider* acOther);
	void hitEx();
	void vf2C4();
	bool isGrounded();
	void vf2F4();

	DECLARE_STATE(Boss, JumpKill)

    u32 hitsToDeath;
	u32 hitsToDamage;
	u32 timer;
	bool isRumbling;
	bool isDemoRunning;
	u8    _188E;
	u8    _188F;
	u8    _1890[0x10];
	MovingSoundActor soundActor;
	u16   _19BC;
	u16   _19BE;
	PlayerLookTarget lookTarget;
	ActorScaler scaler;
	ActiveCollider bossActiveCollider;
	void* _1B34; //? some kind of vtable
	Vec3  _1B38;
	Vec3  _1B44;
	Vec3  _1B50;
	Vec3  _1B5C;
	f32   _1B68;
	f32   _1B6C;
	u32   _1B70;
	u32   _1B74;
};
