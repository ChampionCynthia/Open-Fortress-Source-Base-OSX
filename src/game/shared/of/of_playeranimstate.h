// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: 
// Author(s): Nopey
//
//OFTODO: Proper OFPlayerAnimState. Currently placeholder. -Nopey
#pragma once

#include "iplayeranimstate.h"
#include "base_playeranimstate.h"
#include "Multiplayer/multiplayer_animstate.h"

class COFPlayerAnimState : public CMultiPlayerAnimState
{
public:
	// This is called by both the client and the server in the same way to trigger events for
	// players
	void DoAnimationEvent( PlayerAnimEvent_t event, int nData = 0 ) override;
};

COFPlayerAnimState* CreatePlayerAnimState( CBaseAnimatingOverlay *pEntity );
