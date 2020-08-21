// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: 
// Author(s): Nopey
//
//OFTODO: Proper OFPlayerAnimState. Currently placeholder. -Nopey
#include "of_playeranimstate.h"

void COFPlayerAnimState::DoAnimationEvent( PlayerAnimEvent_t event, int nData )
{
    CMultiPlayerAnimState::DoAnimationEvent(event, nData);
}

COFPlayerAnimState* CreatePlayerAnimState( CBaseAnimatingOverlay *pEntity )
{
    return new COFPlayerAnimState();
}