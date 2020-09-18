// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: General functions related to clients
// Author(s): ficool2, Fenteale
//

#include "cbase.h"
#include "of_player.h"
#include "of_gamerules.h"
#include "gamerules.h"
#include "teamplay_gamerules.h"
#include "entitylist.h"
#include "physics.h"
#include "game.h"
#include "player_resource.h"
#include "filesystem.h"

#include "tier0/vprof.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

extern CBaseEntity*	FindPickerEntityClass( CBasePlayer *pPlayer, char *classname );
extern bool			g_fGameOver;

// OFSTATUS: INCOMPLETE
void FinishClientPutInServer( COFPlayer *pPlayer )
{
	pPlayer->InitialSpawn();
	pPlayer->Spawn();

	char sName[128];
	Q_strncpy( sName, pPlayer->GetPlayerName(), sizeof( sName ) );
	
	// First parse the name and remove any %'s
	for ( char *pApersand = sName; pApersand != NULL && *pApersand != 0; pApersand++ )
	{
		// Replace it with a space
		if ( *pApersand == '%' )
				*pApersand = ' ';
	}

	// notify other clients of player joining the game
	UTIL_ClientPrintAll( HUD_PRINTNOTIFY, "#Game_connected", sName[0] != 0 ? sName : "<unconnected>" );
}

// OFSTATUS: INCOMPLETE
// Called each time a player is spawned into the game
void ClientPutInServer( edict_t *pEdict, const char *playername )
{
	COFPlayer *pPlayer = COFPlayer::CreatePlayer( "player", pEdict );
	pPlayer->SetPlayerName( playername );
}

// OFSTATUS: INCOMPLETE
void ClientActive( edict_t *pEdict, bool bLoadGame )
{
	if ( bLoadGame )
		return;

	COFPlayer *pPlayer = ToOFPlayer( CBaseEntity::Instance( pEdict ) );
	FinishClientPutInServer( pPlayer );
}

// OFSTATUS: COMPLETE
// Returns the descriptive name of this .dll.  E.g., Half-Life, or Team Fortress 2
const char *GetGameDescription()
{
	if ( g_pGameRules ) // this function may be called before the world has spawned, and the game rules initialized
		return g_pGameRules->GetGameDescription();
	else
		return "Open Fortress";
}

// OFSTATUS: COMPLETE
// Given a player and optional name returns the entity of that classname that the player is nearest facing
CBaseEntity* FindEntity( edict_t *pEdict, char *classname )
{
	// If no name was given set bits based on the picked
	if ( FStrEq( classname, "" ) )  
	{
		return ( FindPickerEntityClass( static_cast<CBasePlayer*>( GetContainingEntity( pEdict ) ), classname ) );
	}
	
	return NULL;
}

#define CLIENT_PRECACHE_FILE "scripts/client_precache.txt"
// OFSTATUS: COMPLETE
void ClientGamePrecache( void )
{
	KeyValues *pKeys = new KeyValues( "ClientPrecache" );
	
	if ( pKeys->LoadFromFile( g_pFullFileSystem, CLIENT_PRECACHE_FILE, "GAME" ) )
	{
		for ( KeyValues *pSubKey = pKeys->GetFirstSubKey(); pSubKey != NULL; pSubKey = pSubKey->GetNextKey() )
		{
			if ( !V_stricmp( pSubKey->GetName(), "model" ) )
			{
				CBaseEntity::PrecacheModel( pSubKey->GetString() );
				continue;
			}
			else if ( !V_stricmp( pSubKey->GetName(), "scriptsound" ) )
			{
				CBaseEntity::PrecacheScriptSound( pSubKey->GetString() );
				continue;
			}
			else if ( !V_stricmp( pSubKey->GetName(), "particle" ) )
			{
				PrecacheParticleSystem( pSubKey->GetString() );
				continue;
			}	
		}
		
		pKeys->deleteThis();
		return;
	}
	
	Error( "Can't open %s for client precache info.", CLIENT_PRECACHE_FILE );
	pKeys->deleteThis();
}


// OFSTATUS: INCOMPLETE
// Called by ClientKill and DeadThink
void respawn( CBaseEntity *pEdict, bool fCopyCorpse )
{
	COFPlayer *pPlayer = ToOFPlayer( pEdict );

	if ( pPlayer )
	{
		if ( gpGlobals->curtime > pPlayer->GetDeathTime() + DEATH_ANIMATION_TIME )
		{		
			// respawn player
			pPlayer->Spawn();			
		}
		else
		{
			pPlayer->SetNextThink( gpGlobals->curtime + 0.1f );
		}
	}
}

extern void Bot_RunAll();

// OFSTATUS: INCOMPLETE
void GameStartFrame( void )
{
	VPROF("GameStartFrame()");
	
	if ( g_fGameOver )
		return;

	// OFTODO: this really should be a convar callback!
	gpGlobals->teamplay = ( teamplay.GetInt() != 0 );
	
	Bot_RunAll();
}

// OFSTATUS: COMPLETE
// Instantiate the proper game rules object
void InstallGameRules()
{
	CreateGameRulesObject( "COFGameRules" );
}