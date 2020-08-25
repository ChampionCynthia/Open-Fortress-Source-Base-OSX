// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: COFWeaponBase is the root of all OF weapons
// Author(s): Nopey
//
#pragma once

#include "basecombatweapon_shared.h"
#include "of_weapon_parse.h"
#include "econ/ihasowner.h"
#include "predictable_entity.h"

//--------------------------------------------------------------------------------------------------------
//
// Weapon IDs for all OF Game weapons
//
typedef enum
{
    WEAPON_NONE = 0,

    WEAPON_OFTODO,

    WEAPON_MAX,
} OFWeaponID;

#if defined( CLIENT_DLL )
    #define COFWeaponBase C_OFWeaponBase
#endif

//OFTODO: low priority: implement and make weaponbase inherit IHasGenericMeter (for shields and stuff, i think)
class COFWeaponBase: public CBaseCombatWeapon, IHasOwner /*, IHasGenericMeter */ {
    DECLARE_CLASS(COFWeaponBase, CBaseCombatWeapon);
    DECLARE_NETWORKCLASS();
    DECLARE_PREDICTABLE();

    #ifdef GAME_DLL
        DECLARE_DATADESC();
    #endif
    //NOTE: I'm basing this class interface entirely on the serverside vtable, and so..
    //OFTODO: Compare COFWeaponBase members to client.dylib CTFWeaponBase

    COFWeaponBase();

    // virtual GetTracerType();
    // virtual Spawn();
    #ifdef GAME_DLL
    // virtual Precache();
    #endif
    // virtual Activate();
    // got lazy and stopped marking them virtual. I'll get that when I find the return value, and whether its an override.
    // ChangeTeam();
    // Use();
    // UpdateOnRemove();
    // Respawn();
    // GetDamageType();
    // ReapplyProvision();
    // TranslateViewmodelHandActivityInternal();

    // All predicted weapons need to implement and return true
	virtual bool        IsPredicted() const { return true; }
    virtual OFWeaponID  GetWeaponID() const { return WEAPON_NONE; }

    // Equip();
    // Drop();
    // VisibleInWeaponSelection();
    // HasAmmo();
    // SendWeaponAnim();
    // CanHolster();
    // Deploy();
    // Holster();
    // SetWeaponVisible();
    // OnActiveStateChanged();
    // Detach();
    // ItemPostFrame();
    // ItemBusyFrame();
    // ItemHolsterFrame();
    // WeaponIdle();
    // CanPerformSecondaryAttack();
    // CheckReload();
    // FinishReload();
    // AbortReload();
    // Reload();
    // AutoFiresFullClip();
    // PrimaryAttack();
    // SecondaryAttack();
    // GetBulletSpread(); // not to be confused with the cbasecombatweapon overload of this
    // GetViewModel();
    // GetWorldModel();
    // GetMaxClip1();
    // GetDefaultClip1();
    // ForceWeaponSwitch();
    // GetShootSound();
    // Clip1();
    // Clip2();
    // ActivityOverride();
    // ActivityList();
    // FallInit();
    // Materialize();
    // CheckRespawn();
    // Operator_HandleAnimEvent();
    // Ready();
    // Lower();
    // GetNextSecondaryAttackDelay();
    // GetCustomDamageType();
    // UsesPrimaryAmmo();
    // UberChargeAmmoPerShot();
    // GetPlayerPoseParamList();
    // GetItemPoseParamList();

    // IHasOwner::GetOwnerViaInterface
    CBaseEntity *GetOwnerViaInterface () override;

    // StartHolsterAnim();
    // UpdateHands();
    // OwnerCanTaunt();
    // CanBeCritBoosted();
    // GetTauntItem();
    // UpdateExtraWearables();
    // ExtraWearableEquipped();
    // ExtraWearableViewModelEquipped();
    // // awful name, just awful.
    // HideAttachmentsAndShowBodygroupsWhenPerformingWeaponIndependentTaunt();
    // RemoveExtraWearables();
    // Misfire();
    // FireFullClipAtOnce();
    // FireFullClipAtOnce();
    // CalcIsAttackCriticalHelper();
    // CalcIsAttackCriticalHelperNoCrits();
    // GetPenetrateType();
    // GetProjectileFireSetup();
    // GetSpreadAngles();
    // IsFiring();
    // AreRandomCritsEnabled();
    // DefaultReload();
    // IsReloading();
    // GetReloadSpeedScale();
    // CheckReloadMisfire();
    // CanDrop();
    // AllowTaunts();
    // ApplyFireDelay();
    // GetActivityWeaponRole();
    // GetViewModelWeaponRole();
    // AddAssociatedObject();
    // RemoveAssociatedObject();
    // ApplyOnHitAttributes();
    // ApplyPostHitEffects();
    // ApplyOnInjuredAttributes();
    // DeflectProjectiles();
    // DeflectPlayer();
    // DeflectEntity();
    // PlayDeflectionSound();
    // GetDeflectionRadius();
    // GetJarateTime();
    // CanAttack();
    // GetCanAttackFlags();
    // WeaponReset();
    // WeaponRegenerate();
    // GetMuzzleFlashEffectName_3rd();
    // GetMuzzleFlashEffectName_1st();
    // GetMuzzleFlashModel();
    // GetMuzzleFlashModelLifetime();
    // GetMuzzleFlashParticleEffect();
    // GetInventoryModel();
    // GetSpeedMod();
    // CanFireCriticalShot();
    // CanFireRandomCriticalShot();
    // OnControlStunned();
    // HideWhileStunned();
    // IsViewModelFlipped();
    // GetMaxHealthMod();
    // GetLastDeployTime();
    // IsEnergyWeapon();
    // IsBlastImpactWeapon();
    // Energy_GetShotCost();
    // Energy_GetRechargeCost();
    // GetParticleColor();
    // HasLastShotCritical();
    // UseServerRandomSeed();
    // IsBroken();
    // SetBroken();
    // OnBulletFire();
    // OnPlayerKill();
    // GetLastHitTime();
    // GetDropSkinOverride();
    // GetInitialAfterburnDuration();
    // GetAfterburnRateOnHit();
    // GetSkin();
    // GetEffectBarProgress();
    // CanPickupOtherWeapon();
    // ShouldRemoveInvisibilityOnPrimaryAttack();
    // GetEffectBarAmmo();
    // InternalGetEffectBarRechargeTime();
    // CanInspect();
    // HookAttributes();
    // OnUpgraded();
};
