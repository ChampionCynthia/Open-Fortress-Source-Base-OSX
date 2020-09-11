// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFPlayer
// Author(s): Fenteale
//

// TODO: Check against tf2 server.dylib! Much lacking functionality. -@Nopey
// (Many functions are copied from sdk_player.cpp. Please mark any that match tf2 server.dylib)

#include "cbase.h"
#include "of_player.h"
#include "of_playeranimstate.h"
#include "of_shareddefs.h"

// -------------------------------------------------------------------------------- //
// Player animation event. Sent to the client when a player fires, jumps, reloads, etc..
// -------------------------------------------------------------------------------- //

class CTEPlayerAnimEvent : public CBaseTempEntity
{
public:
	DECLARE_CLASS( CTEPlayerAnimEvent, CBaseTempEntity );
	DECLARE_SERVERCLASS();

					CTEPlayerAnimEvent( const char *name ) : CBaseTempEntity( name )
					{
					}

	CNetworkHandle( CBasePlayer, m_hPlayer );
	CNetworkVar( int, m_iEvent );
	CNetworkVar( int, m_nData );
};

IMPLEMENT_SERVERCLASS_ST_NOBASE( CTEPlayerAnimEvent, DT_TEPlayerAnimEvent )
	SendPropEHandle( SENDINFO( m_hPlayer ) ),
	SendPropInt( SENDINFO( m_iEvent ), Q_log2( PLAYERANIMEVENT_COUNT ) + 1, SPROP_UNSIGNED ),
	SendPropInt( SENDINFO( m_nData ), 32 )
END_SEND_TABLE()

static CTEPlayerAnimEvent g_TEPlayerAnimEvent( "PlayerAnimEvent" );

void TE_PlayerAnimEvent( CBasePlayer *pPlayer, PlayerAnimEvent_t event, int nData )
{
	CPVSFilter filter( (const Vector&)pPlayer->EyePosition() );
	
	g_TEPlayerAnimEvent.m_hPlayer = pPlayer;
	g_TEPlayerAnimEvent.m_iEvent = event;
	g_TEPlayerAnimEvent.m_nData = nData;
	g_TEPlayerAnimEvent.Create( filter, 0 );
}

// implementation of COFPlayer begin

LINK_ENTITY_TO_CLASS( player, COFPlayer );

IMPLEMENT_SERVERCLASS_ST(COFPlayer, DT_OF_Player)
END_SEND_TABLE()

BEGIN_DATADESC( COFPlayer )
END_DATADESC()

COFPlayer::COFPlayer() : BaseClass() {
	m_PlayerAnimState = CreatePlayerAnimState(this);
}

bool COFPlayer::m_bOFPlayerNeedsPrecache { false };

COFPlayer* COFPlayer::CreatePlayer( const char * name, edict_t* pEdict)
{
	CBasePlayer::s_PlayerEdict = pEdict;
	return (COFPlayer *)CreateEntityByName(name, -1);
}

void COFPlayer::DoAnimationEvent( PlayerAnimEvent_t event, int nData )
{
	m_PlayerAnimState->DoAnimationEvent( event, nData );
	TE_PlayerAnimEvent( this, event, nData );	// Send to any clients who can see this guy.
}

//OFSTATUS: Incomplete, and low priority
void COFPlayer::PreCacheKart()
{
}

//OFSTATUS: Incomplete, and low priority
void COFPlayer::PreCacheMvM()
{
}

//OFSTATUS: Incomplete, only handles jointeam and in jointeam it only handles actual numbers.
bool COFPlayer::ClientCommand( const CCommand& args )
{
	if ( FStrEq( args[0], "jointeam" ) && args.ArgC() >= 2)
	{
		BaseClass::ChangeTeam( atoi( args[1] ) );
		return true;
	}

	return BaseClass::ClientCommand(args);
}
