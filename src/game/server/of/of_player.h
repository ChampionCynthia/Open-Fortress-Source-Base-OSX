// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of COFPlayer
// Author(s): Fenteale, Nopey
//

#pragma once

#include "player.h"
#include "dbg.h"
#include "of_playeranimstate.h"

class COFWeaponBase;

class COFPlayer : public CBasePlayer {
public:
	DECLARE_CLASS( COFPlayer, CBasePlayer );
	DECLARE_DATADESC();
	DECLARE_SERVERCLASS();

	// This passes the event to the client's and server's CPlayerAnimState.
	void DoAnimationEvent( PlayerAnimEvent_t event, int nData = 0 );

	COFPlayer();
	static COFPlayer* CreatePlayer( const char * name, edict_t* pEdict);

	// Called from of_gamerules
	void PreCacheKart();
	static void PreCacheMvM();
	void Precache();
	void Spawn();
	void InitialSpawn();

	bool ClientCommand(const CCommand& args);
	
	COFWeaponBase 	*GetActiveOFWeapon( void ) const;
	
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

	// set to true from of_gamerules
	//OFTODO: I'm assuming the init value of m_bOFPlayerNeedsPrecache is false.
	static bool m_bOFPlayerNeedsPrecache;

	// Tracks our ragdoll entity.
	CNetworkHandle( CBaseEntity, m_hRagdoll );	// networked entity handle 	
	
private:
	COFPlayerAnimState *m_PlayerAnimState;
};

inline COFPlayer *ToOFPlayer( CBaseEntity *pEntity )
{
	if ( !pEntity || !pEntity->IsPlayer() )
		return nullptr;

	return assert_cast<COFPlayer*>( pEntity );
}