// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of COFPlayer
// Author(s): Fenteale, Nopey
//

#ifndef OF_PLAYER_H
#define OF_PLAYER_H

#ifdef _WIN32
#pragma once
#endif

#include "player.h"
#include "dbg.h"
#include "of_playeranimstate.h"

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
	void PreCacheMvM();
	// set to true from of_gamerules
	//OFTODO: I'm assuming the init value of m_bOFPlayerNeedsPrecache is false.
	static bool m_bOFPlayerNeedsPrecache = false;

private:
	COFPlayerAnimState *m_PlayerAnimState;
};

inline COFPlayer *ToOFPlayer( CBaseEntity *pEntity )
{
	if ( !pEntity || !pEntity->IsPlayer() )
		return nullptr;

	return assert_cast<COFPlayer*>( pEntity );
}

#endif