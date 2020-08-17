// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of C_TFPlayer
// Author(s): Fenteale
//

#include "c_of_player.h"

// Don't alias here
#if defined( COFPlayer )
#undef COFPlayer	
#endif

COF_Player::COF_Player() : BaseClass() {
	return;
}

COF_Player* COF_Player::CreatePlayer( const char * name, edict_t* pEdict)
{
	C_BasePlayer::s_PlayerEdict = pEdict;
	return (COF_Player *)CreateEntityByName(name, -1);
}

void C_OFPlayer::DoAnimationEvent( PlayerAnimEvent_t event, int nData )
{
	m_PlayerAnimState->DoAnimationEvent( event, nData );
}