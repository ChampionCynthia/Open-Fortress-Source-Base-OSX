// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of C_TFPlayer
// Author(s): Fenteale, Nopey
//

#include "cbase.h"
#include "c_of_player.h"
#include "c_basetempentity.h"

// Don't alias here
// Why not? -Nopey
#if defined( COFPlayer )
#undef COFPlayer
#endif

// -------------------------------------------------------------------------------- //
// Player animation event reciever. Sent to the client when a player fires, jumps, reloads, etc..
// -------------------------------------------------------------------------------- //

class C_TEPlayerAnimEvent : public C_BaseTempEntity
{
public:
	DECLARE_CLASS( C_TEPlayerAnimEvent, C_BaseTempEntity );
	DECLARE_CLIENTCLASS();

	virtual void PostDataUpdate( DataUpdateType_t updateType )
	{
		// Create the effect.
		C_OFPlayer *pPlayer = dynamic_cast< C_OFPlayer* >( m_hPlayer.Get() );
		if ( pPlayer && !pPlayer->IsDormant() )
		{
			pPlayer->DoAnimationEvent( (PlayerAnimEvent_t)m_iEvent.Get(), m_nData );
		}	
	}

	CNetworkHandle( C_BasePlayer, m_hPlayer );
	CNetworkVar( int, m_iEvent );
	CNetworkVar( int, m_nData );
};

IMPLEMENT_CLIENTCLASS_EVENT( C_TEPlayerAnimEvent, DT_TEPlayerAnimEvent, CTEPlayerAnimEvent );

BEGIN_RECV_TABLE_NOBASE( C_TEPlayerAnimEvent, DT_TEPlayerAnimEvent )
	RecvPropEHandle( RECVINFO( m_hPlayer ) ),
	RecvPropInt( RECVINFO( m_iEvent ) ),
	RecvPropInt( RECVINFO( m_nData ) )
END_RECV_TABLE()

LINK_ENTITY_TO_CLASS( player, C_OFPlayer );

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
