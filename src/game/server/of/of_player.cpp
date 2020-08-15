// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFPlayer
// Author(s): Fenteale
//

#include "of_player.h"

COFPlayer::COFPlayer() : BaseClass() {
	return;
}

COFPlayer* COFPlayer::CreatePlayer( const char * name, edict_t* pEdict)
{
	CBasePlayer::s_PlayerEdict = pEdict;
	return (COFPlayer *)CreateEntityByName(name, -1);
}