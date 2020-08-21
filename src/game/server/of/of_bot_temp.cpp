// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of COFBot
// Author(s): Fenteale
//

//OFTODO: This is mainly a copy of sdk_bot_temp.cpp.  We gotta RE this!

#include "cbase.h"
#include "player.h"
#include "of_player.h"
#include "in_buttons.h"
#include "movehelper_server.h"
#include "gameinterface.h"


class CSDKBot;
void Bot_Think( CSDKBot *pBot );


ConVar bot_forcefireweapon( "bot_forcefireweapon", "", 0, "Force bots with the specified weapon to fire." );
ConVar bot_forceattack2( "bot_forceattack2", "0", 0, "When firing, use attack2." );
ConVar bot_forceattackon( "bot_forceattackon", "0", 0, "When firing, don't tap fire, hold it down." );
ConVar bot_flipout( "bot_flipout", "0", 0, "When on, all bots fire their guns." );
ConVar bot_changeclass( "bot_changeclass", "0", 0, "Force all bots to change to the specified class." );
static ConVar bot_mimic( "bot_mimic", "0", 0, "Bot uses usercmd of player by index." );
static ConVar bot_mimic_yaw_offset( "bot_mimic_yaw_offset", "0", 0, "Offsets the bot yaw." );

ConVar bot_sendcmd( "bot_sendcmd", "", 0, "Forces bots to send the specified command." );

ConVar bot_crouch( "bot_crouch", "0", 0, "Bot crouches" );

static int g_CurBotNumber = 1;


// This is our bot class.
class COFBot : public COFPlayer
{
public:
	bool			m_bBackwards;

	float			m_flNextTurnTime;
	bool			m_bLastTurnToRight;

	float			m_flNextStrafeTime;
	float			m_flSideMove;

	QAngle			m_ForwardAngle;
	QAngle			m_LastAngles;
};

LINK_ENTITY_TO_CLASS( of_bot, COFBot );

class CBotManager
{
public:
	static CBasePlayer* ClientPutInServerOverride_Bot( edict_t *pEdict, const char *playername )
	{
		// This tells it which edict to use rather than creating a new one.
		CBasePlayer::s_PlayerEdict = pEdict;

		COFBot *pPlayer = static_cast<COFBot *>( CreateEntityByName( "of_bot" ) );
		if ( pPlayer )
		{
			pPlayer->SetPlayerName( playername );
		}

		return pPlayer;
	}
};


//-----------------------------------------------------------------------------
// Purpose: Create a new Bot and put it in the game.
// Output : Pointer to the new Bot, or NULL if there's no free clients.
//-----------------------------------------------------------------------------
CBasePlayer *BotPutInServer( bool bFrozen, int iTeam, int iClass )
{
	char botname[ 64 ];
	Q_snprintf( botname, sizeof( botname ), "Bot%02i", g_CurBotNumber );

	
	// This trick lets us create a CSDKBot for this client instead of the CSDKPlayer
	// that we would normally get when ClientPutInServer is called.
	ClientPutInServerOverride( &CBotManager::ClientPutInServerOverride_Bot );
	edict_t *pEdict = engine->CreateFakeClient( botname );
	ClientPutInServerOverride( NULL );

	if (!pEdict)
	{
		Msg( "Failed to create Bot.\n");
		return NULL;
	}

	// Allocate a player entity for the bot, and call spawn
	COFBot *pPlayer = ((COFBot*)CBaseEntity::Instance( pEdict ));

	pPlayer->ClearFlags();
	pPlayer->AddFlag( FL_CLIENT | FL_FAKECLIENT );

	if ( bFrozen )
		pPlayer->AddEFlags( EFL_BOT_FROZEN );

	pPlayer->ChangeTeam( TEAM_UNASSIGNED );
	pPlayer->RemoveAllItems( true );
	pPlayer->Spawn();

	g_CurBotNumber++;

	return pPlayer;
}