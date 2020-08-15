// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFPlayer
// Author(s): Fenteale
//

#ifndef OF_PLAYER_H
#define OF_PLAYER_H

#ifdef _WIN32
#pragma once
#endif

#include "player.h"

class COFPlayer : public CBasePlayer {
public:
	DECLARE_CLASS( COFPlayer, CBasePlayer );
	DECLARE_DATADESC();
	DECLARE_SERVERCLASS();

	COFPlayer();
	static COFPlayer* CreatePlayer( const char * name, edict_t* pEdict);
};

inline COFPlayer *ToOFPlayer( CBaseEntity *pEntity )
{
	if ( !pEntity || !pEntity->IsPlayer() )
		return NULL;

#ifdef _DEBUG
	Assert( dynamic_cast<COFPlayer*>( pEntity ) != 0 );
#endif
	return static_cast< COFPlayer* >( pEntity );
}

#endif