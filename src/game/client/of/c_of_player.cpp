// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of C_TFPlayer
// Author(s): Fenteale, Nopey
//

#include "cbase.h"
#include "c_of_player.h"

// Don't alias here
// Why not? -Nopey
#if defined( COFPlayer )
#undef COFPlayer
#endif

LINK_ENTITY_TO_CLASS( of_player, C_OFPlayer );

IMPLEMENT_CLIENTCLASS_DT(C_OFPlayer, DT_OF_Player, COFPlayer)
END_RECV_TABLE()

BEGIN_PREDICTION_DATA( C_OFPlayer )
END_PREDICTION_DATA()

C_OFPlayer::C_OFPlayer() : BaseClass() {
	return;
}

void C_OFPlayer::DoAnimationEvent( PlayerAnimEvent_t event, int nData )
{
	m_PlayerAnimState->DoAnimationEvent( event, nData );
}
