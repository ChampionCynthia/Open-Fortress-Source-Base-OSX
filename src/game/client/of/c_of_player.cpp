// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of C_TFPlayer
// Author(s): Fenteale, Nopey
//

#include "c_of_player.h"

// Don't alias here
// Why not? -Nopey
#if defined( COFPlayer )
#undef COFPlayer
#endif

C_OFPlayer::C_OFPlayer() : BaseClass() {
	return;
}

void C_OFPlayer::DoAnimationEvent( PlayerAnimEvent_t event, int nData )
{
	m_PlayerAnimState->DoAnimationEvent( event, nData );
}
