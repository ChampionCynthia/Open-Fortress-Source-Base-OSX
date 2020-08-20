// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of C_TFPlayer
// Author(s): Fenteale
//

#ifndef C_OF_PLAYER_H
#define C_OF_PLAYER_H

#ifdef _WIN32
#pragma once
#endif

#include "c_baseplayer.h"
#include "of_playeranimstate.h"

class C_OFPlayer : public C_BasePlayer {
public:
	DECLARE_CLASS( C_OFPlayer, C_BasePlayer );
	DECLARE_CLIENTCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_INTERPOLATION();

	C_OFPlayer();
	void DoAnimationEvent( PlayerAnimEvent_t event, int nData = 0 );
private:
	COFPlayerAnimState *m_PlayerAnimState;
};

#endif