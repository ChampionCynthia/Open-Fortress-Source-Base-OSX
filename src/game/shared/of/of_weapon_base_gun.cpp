// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Impl COFWeaponBase, the root of all OF weapons
// Author(s): Nopey, Fenteale
//
#include "cbase.h"
#include "of_weapon_base.h"

// ----------------------------------------------------------------------------- //
// COFWeaponBase tables.
// ----------------------------------------------------------------------------- //

IMPLEMENT_NETWORKCLASS_ALIASED( COFWeaponBaseGun, DT_OFWeaponBaseGun )

BEGIN_NETWORK_TABLE( COFWeaponBaseGun, DT_OFWeaponBaseGun )
#ifdef CLIENT_DLL
  
#else
/* SDK Garbo that might or might not be useful
    // world weapon models have no animations
      SendPropExclude( "DT_AnimTimeMustBeFirst", "m_flAnimTime" ),
    SendPropExclude( "DT_BaseAnimating", "m_nSequence" ),
*/
#endif
END_NETWORK_TABLE()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA( COFWeaponBaseGun )

END_PREDICTION_DATA()
#endif

// Do we need this? Weapon bases never get used on their own - Kay
LINK_ENTITY_TO_CLASS( tf_weapon_base_gun, COFWeaponBaseGun );


#ifdef GAME_DLL

    BEGIN_DATADESC( COFWeaponBaseGun )

        // New weapon Think and Touch Functions go here..

    END_DATADESC()

#endif


void COFWeaponBaseGun::PrimaryAttack()
{
	// Something with UberChargeAmmoPerShot(), im not sure exactly what this means
	// (*this->vtable->CTFWeaponBase::UberChargeAmmoPerShot)((CTFWeaponBase *)this); - Kay
	
	// Abort if we dont have any reserve ammo
	if( /* 0 < (float)extraout_ST0 Checking reserve ammo?, but wouldnt that be >= then? - Kay */ 
	!HasPrimaryAmmo() )
		return;
	/*
	Since we check reserve ammo previously, im gonna assume that this checks if we have anything in the clip left
	aka that (int)this[0x17b].vtable is the clip size - Kay
	  if (((int)this[0x17b].vtable < 1) && (this[0x17b].vtable != (vtableCTFWeaponBaseGun *)0xffffffff))
	  {
		return;
	  }	
	*/
	
	// Abort if we have less than 1 bullet in the clip
	if( Clip1() < 1 )
		return;
	
	/*
		Im honestly not exactly sure but from what i can tell, this is the Fire time,
		so its checking against the CURRTIME ˇˇˇˇ to see if we can fire now - Kay
	  if (*(float *)(*(int *)PTR__gpGlobals_00e31080 + 0xc) <= (float)this[0x16a].vtable &&
		  (float)this[0x16a].vtable != *(float *)(*(int *)PTR__gpGlobals_00e31080 + 0xc)) {
		return;
	  }	
	*/
	
	// Dont shoot faster than the fire rate
	if( gpGlobals->curtime <= m_flNextPrimaryAttack )
		return;
	
	CTFPlayer *pPlayer = GetTFPlayerOwner();
	if( !pPlayer )
		return;
	
/*
  cVar7 = (*this_01->vtable->CBaseEntity::IsPlayer)(this_01);
  if (cVar7 == '\0') {
    return;
  }
  Skipped IsPlayer since GetTFPlayerOwner already does that for us
*/

	if( !CanAttack() )
		return;

	// OFTODO: Replace this with CTFWeaponBase::ApplyFireDelay whenever that function gets added - Kay
	m_flNextPrimaryAttack += GetOFWpnData()->m_WeaponModeInfo[m_iWeaponMode].m_flTimeFireDelay;
	
	m_iClip1 -= GetAmmoPerShot();
	
	DoFireEffects();
	
//	CalcIsAttackCritical();
	
	/* Uncomment these when we have the functions for it
	if( ShouldRemoveInvisibilityOnPrimaryAttack() )
		pPlayer->RemoveInvisibility(); 
	
	pPlayer->SpeakWeaponFire();
	
	globalTFStatsThing->Event_PlayerFiredWeapon(pPlayer, Some bool, not sure exactly); -Kay	*/
	
	SendWeaponAnim( GetPrimaryAttackActivity() );
	
	// Uncomment when we implement these -Kay
	//CBaseEntity *pProjectile = FireProjectile( pPlayer );
	
	//ModifyProjectile( pProjectile );

	// (*this_01->vtable[1].CBaseEntity::NetworkStateChanged_m_hGroundEntity)(this_01,5); Whats this used for?? We like, change our ground state or what? -Kay
	
	/*
	Everything beyond here is just French to me, if someone else can decypther it go ahead 
	By the looks of it its somethign todo with the animation playback speed - Kay
	if( !UsesClipsForAmmo1() )
	{
		
	}
	*/

	SetWeaponIdleTime( SequenceDuration() );
	
	if( ShouldRemoveDisguiseOnPrimaryAttack() )
		pPlayer()->RemoveDisguise();
	
	pPlayer->OnAttack();
}

int COFWeaponBaseGun::GetAmmoPerShot()
{
	return GetOFWpnData()->m_WeaponModeInfo[m_iWeaponMode].m_iAmmoPerShot;
}

void COFWeaponBaseGun::DoFireEffects()
{
	// From what i can tell this just casts to the player's active weapon and checks if it can do the muzzleflash
	// Question is, WHY? We're literally in the weapon itself, half of this is useless, so i just did the check the sane way - Kay
	COFPlayer *pPlayer = GetOFPlayerOwner();
	if( !pPlayer )
		return;

	if( ShouldDoMuzzleFlash() )
		pPlayer->DoMuzzleFlash();
}