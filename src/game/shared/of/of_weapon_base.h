// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: COFWeaponBase is the root of all OF weapons
// Author(s): Nopey, Fenteale
//
#pragma once

#include "basecombatweapon_shared.h"
#include "of_weapon_parse.h"
#include "econ/ihasowner.h"
#include "predictable_entity.h"

#ifdef CLIENT_DLL
#define COFPlayer C_OFPlayer
#endif

//--------------------------------------------------------------------------------------------------------
//
// Weapon IDs for all OF Game weapons
//
typedef enum
{
    WEAPON_NONE = 0,

	OF_WEAPON_SMG,
	OF_WEAPON_SHOTGUN,
    WEAPON_OFTODO,

    WEAPON_MAX,
} OFWeaponID;

const char *WeaponIDToAlias( int id );

#if defined( CLIENT_DLL )
    #define COFWeaponBase C_OFWeaponBase
#endif

// NOTE: Some methods in ghidra don't take `this` ptr, such
//  as CanFireCriticalShot
// Hypothesis: __thiscall calling convention places this in EAX,
//  and if you don't use it, you can simply ignore the value in
//  EAX and use the default calling conv.
// -Nopey


/*
 OFTODO: low priority: implement and make weaponbase inherit IHasGenericMeter (for shields and stuff, i think)
 IHasGenericMeter Notes
    ShouldUpdateMeter
    GetMeterMultiplier
    OnResourceMeterFilled
    GetChargeInterval
*/

class COFPlayer;

//OFTODO: Mark many COFWeaponBase getters const
class COFWeaponBase: public CBaseCombatWeapon, IHasOwner /*, IHasGenericMeter */ 
{
    DECLARE_CLASS(COFWeaponBase, CBaseCombatWeapon);
    DECLARE_NETWORKCLASS();
    DECLARE_PREDICTABLE();

    #ifdef GAME_DLL
        DECLARE_DATADESC();
    #endif
    //NOTE: I'm basing this class interface entirely on the serverside vtable, and so..
    //OFTODO: Compare COFWeaponBase members to client.dylib CTFWeaponBase

    COFWeaponBase();

    // CBaseEntity::
    virtual const char *GetTracerType() override;

    // CBaseCombatWeapon::
    virtual void Spawn() override;
    #ifdef GAME_DLL
    virtual void Activate() override;
    #endif

    // CBaseEntity::
    #ifdef CLIENT_DLL
    virtual void Precache() override;
    #endif
    #ifdef GAME_DLL
    virtual void ChangeTeam(int iTeamNum) override;
    #endif
    // virtual void Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value ) override;
    // virtual void UpdateOnRemove() override;
    // virtual CBaseEntity *Respawn ( void ) override;
    // virtual int GetDamageType() override;

    // virtual void ReapplyProvision();
    // virtual Activity TranslateViewmodelHandActivityInternal(Activity);

    // All predicted weapons need to implement and return true
	virtual bool        IsPredicted() const { return true; }
    virtual OFWeaponID  GetWeaponID() const { return WEAPON_NONE; }

    // CBaseCombatWeapon::
    // virtual void Equip( CBaseCombatCharacter *pOwner ) override;
    // virtual void Drop( const Vector &vecVelocity ) override;
    virtual bool VisibleInWeaponSelection() override;
    virtual bool HasAmmo() override;
    // virtual bool SendWeaponAnim( int iActivity ) override;
    virtual bool CanHolster() const override;
    // virtual void Deploy() override;
    // virtual bool Holster( CBaseCombatWeapon *pSwitchingTo ) override;
    virtual void SetWeaponVisible( bool visible ) override;
    // virtual void OnActiveStateChanged( int iOldState ) override;
    virtual void Detach() override;
    virtual void ItemPostFrame() override;
	virtual void ReloadSinglyPostFrame();
	virtual bool Reload();
	virtual bool ReloadSingly();
	virtual void IncrementAmmo();
	virtual void SetReloadTimer( float flReloadTime );
    // virtual void ItemBusyFrame() override;
    // virtual void ItemHolsterFrame() override;
    // virtual void WeaponIdle() override;
    virtual bool CanPerformSecondaryAttack() const override;
    // virtual void CheckReload() override;
    // virtual void FinishReload() override;
    // virtual void AbortReload() override;
    // virtual bool Reload() override;
    #ifdef CLIENT_DLL
    virtual bool AutoFiresFullClip() const override { return false; };
    #endif
    // virtual void PrimaryAttack() override;
    // virtual void SecondaryAttack() override;
    // virtual const Vector &GetBulletSpread();
    // virtual const char GetViewModel() const override;
    // virtual const char GetWorldModel() const override;
    // virtual int GetMaxClip1() const override;
    // virtual int GetDefaultClip1() const override;
    // virtual bool ForceWeaponSwitch() const override;
    // virtual char const *GetShootSound( int iIndex ) const override;
    // virtual int Clip1() override;
    // virtual int Clip2() override;
    // virtual Activity ActivityOverride( Activity baseAct, bool *pRequired );
    // virtual acttable_t* ActivityList( int &iActivityCount );
    #ifdef CLIENT_DLL
    virtual void FallInit() override { /*Intentionally blank*/ };
    #endif
    // virtual void Materialize() override;
    // virtual void CheckRespawn() override;
    // virtual void Operator_HandleAnimEvent( animevent_t *pEvent, CBaseCombatCharacter *pOperator ) override;
    // virtual bool Ready() override;
    // virtual bool Lower() override;
    
    // ghidra says it returns a float10.. magical.
    // virtual float GetNextSecondaryAttackDelay();
    // probably returns an enum
    // virtual int GetCustomDamageType();
    
    // CBaseCombatWeapon::
    // virtual bool UsesPrimaryAmmo() override;

    // again with float10, ghidra. I wonder what it means..
    // virtual float UberChargeAmmoPerShot();
    // some kind of pointer? maybe a reference.
    // virtual void *GetPlayerPoseParamList(int *);
    // virtual void *GetItemPoseParamList(int *);

    // IHasOwner::
    CBaseEntity *GetOwnerViaInterface () override;

    virtual void StartHolsterAnim();
    // virtual void UpdateHands();
    // virtual bool OwnerCanTaunt();
    // virtual bool CanBeCritBoosted();
    // OFTODO: this is almost certainly not an int pointer.
    // virtual int *GetTauntItem();
    // warning: massive chonkey function
    // virtual void UpdateExtraWearables();
    // virtual void ExtraWearableEquipped(CTFWearable *);
    // virtual void ExtraWearableViewModelEquipped(CTFWearable *);
    // // awful name, just awful.
    virtual bool HideAttachmentsAndShowBodygroupsWhenPerformingWeaponIndependentTaunt() const;
    // virtual void RemoveExtraWearables();
    virtual void Misfire();
    virtual void CalcIsAttackCritical();
    virtual void FireFullClipAtOnce(){ return; };
    // virtual bool CalcIsAttackCriticalHelper();
    // virtual bool CalcIsAttackCriticalHelperNoCrits();
    // virtual int GetPenetrateType();
    // some of these could be references. (Any that aren't null checked, make into refs.)
    // virtual void GetProjectileFireSetup (CTFPlayer *,Vector,Vector *,QAngle *, bool, float);
    // This return type is almost certainly incorrect.
    // virtual void GetSpreadAngles();
    virtual bool IsFiring() const;
    virtual bool AreRandomCritsEnabled();
    // virtual bool DefaultReload( int iClipSize1, int iClipSize2, int iActivity );
    // virtual bool IsReloading();
    virtual float GetReloadSpeedScale() const;
    virtual bool CheckReloadMisfire() const;
    virtual bool CanDrop() const;
    virtual bool AllowTaunts() const;
    // virtual float ApplyFireDelay( float );
    // virtual int GetActivityWeaponRole();
    // virtual int GetViewModelWeaponRole();
    // virtual void AddAssociatedObject();
    // virtual void RemoveAssociatedObject();
    // virtual void ApplyOnHitAttributes(CBaseEntity *,CTFPlayer *,CTakeDamageInfo *);
    // virtual void ApplyPostHitEffects(CTakeDamageInfo *, CTFPlayer *);
    // virtual void ApplyOnInjuredAttributes(CTFPlayer *,CTFPlayer *,CTakeDamageInfo *);
    // return types may be incorrect here
    // virtual bool DeflectProjectiles();
    // OFTODO: Look for other implementations of CTFWeaponBase::DeflectPlayer (pyro flamethrower, probs) and check this signature.
    // virtual bool DeflectPlayer(CTFPlayer *,CTFPlayer *,Vector *);
    // virtual bool DeflectEntity(CBaseEntity *,CTFPlayer *,Vector *);
    // virtual void PlayDeflectionSound(bool);
    // virtual float GetDeflectionRadius();
    virtual float GetJarateTime() { return 0.0f };
    virtual bool CanAttack();
    virtual bool GetCanAttackFlags() const { return false; };
    // virtual void WeaponReset();
    // virtual void WeaponRegenerate();
    // virtual const char *GetMuzzleFlashEffectName_3rd();
    // virtual const char *GetMuzzleFlashEffectName_1st();
    // virtual const char *GetMuzzleFlashModel();
    // virtual float GetMuzzleFlashModelLifetime();
    // virtual const char *GetMuzzleFlashParticleEffect();
    // virtual const char *GetInventoryModel();
    virtual float GetSpeedMod();
    // virtual bool CanFireCriticalShot();
    // virtual bool CanFireRandomCriticalShot(CBaseEntity *);
    // Probably the MvM rottenburg cap stun :P
    #ifdef CLIENT_DLL
    virtual void OnControlStunned();
    #endif
    #ifdef GAME_DLL
    virtual bool HideWhileStunned();
    virtual bool IsViewModelFlipped();
    virtual int GetMaxHealthMod();
    virtual float GetLastDeployTime();
    #endif
    virtual bool IsEnergyWeapon() const { return false; };
    virtual bool IsBlastImpactWeapon() const { return false; };
	// OFSTATUS: COMPLETE
    virtual float Energy_GetShotCost(){ return 4.0f; };
	// OFSTATUS: COMPLETE
    virtual float Energy_GetRechargeCost(){ return 4.0f; };
    virtual Vector GetParticleColor(int iColor);
    virtual bool HasLastShotCritical() const { return false; };
    virtual bool UseServerRandomSeed() const { return true; };
    // int param is probs a bool or an enum
    // void OnBulletFire(int);
    // virtual void OnPlayerKill(CTFPlayer *pSmellyUnfortunate, CTakeDamageInfo *);
    // virtual float GetLastHitTime();
    #ifdef GAME_DLL
    virtual int GetDropSkinOverride() { return -1; };
    #endif
    virtual float GetInitialAfterburnDuration() { return 0.0f; };
    virtual float GetAfterburnRateOnHit() { return 0.0f; };
    // return value is probably the model's skin index
    // virtual uint GetSkin();
    // virtual float GetEffectBarProgress();
    virtual bool CanPickupOtherWeapon() const { return true; };
    virtual bool ShouldRemoveInvisibilityOnPrimaryAttack() const { return true; };
    // virtual int GetEffectBarAmmo();
    virtual float InternalGetEffectBarRechargeTime() { return 0.0f; };
    virtual bool CanInspect() { return true; } ;
    virtual void HookAttributes();

    // NOTE: This MvM function literally just calls HookAttributes, unless ghidra is malfunctioning.
    // (oh, and it doesn't have any overrides)
    // or in other words, all my homies hate CTFWeaponBase::OnUpgraded
    // void OnUpgraded();
	
	COFPlayer	*GetOFPlayerOwner() const;
	
	const COFWeaponInfo	&GetOFWpnData( void ) const;
	
public:
	int m_iWeaponMode; // Used in stuff like airblast 'n similar
	CNetworkVar( int, m_iReloadStage );
private:
	CNetworkVar( bool, m_bAnimReload );
	CNetworkVar( bool, m_bInAttack );
	CNetworkVar( bool, m_bInAttack2 );
	CNetworkVar( float, m_flEnergy );
	CNetworkVar( int, m_iConsecutiveShots );
	CNetworkVar( int, m_iOldClip );
	CNetworkVar( float, m_flOldPrimaryAttack );
};
