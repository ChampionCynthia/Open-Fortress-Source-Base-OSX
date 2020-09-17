// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of C_TFPlayer
// Author(s): Fenteale
//

#pragma once

#include "c_baseplayer.h"
#include "of_playeranimstate.h"

class C_OFWeaponBase;

class C_OFPlayer : public C_BasePlayer {
public:
	DECLARE_CLASS( C_OFPlayer, C_BasePlayer );
	DECLARE_CLIENTCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_INTERPOLATION();

	C_OFPlayer();
	void DoAnimationEvent( PlayerAnimEvent_t event, int nData = 0 );
	C_OFWeaponBase 	*GetActiveOFWeapon( void ) const;

	virtual void FireBullet( 
						   Vector vecSrc,	// shooting postion
						   const QAngle &shootAngles,  //shooting angle
						   float vecSpread, // spread vector
						   int iDamage, // base damage
						   int iBulletType, // ammo type
						   CBaseEntity *pevAttacker, // shooter
						   bool bDoEffects,	// create impact effect ?
						   float x,	// spread x factor
						   float y	// spread y factor
						   );
						   
public:
	COFPlayerAnimState *m_PlayerAnimState;
};

inline C_OFPlayer *ToOFPlayer( CBaseEntity *pEntity )
{
	if ( !pEntity || !pEntity->IsPlayer() )
		return nullptr;

	return assert_cast<C_OFPlayer*>( pEntity );
}