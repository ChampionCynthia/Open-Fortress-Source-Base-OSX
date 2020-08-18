// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Game logic manager
// Author(s): ficool2, Fenteale
//

#ifndef OF_GAMERULES_H
#define OF_GAMERULES_H
#pragma once

#include "gamerules.h"
#include "teamplay_gamerules.h"
#include "gamevars_shared.h"

#ifndef CLIENT_DLL
#include "of_player.h"
#endif

#ifdef CLIENT_DLL
	#define COFGameRules C_OFGameRules
	#define COFGameRulesProxy C_OFGameRulesProxy
#endif

#define HUD_ALERT_SCRAMBLE_TEAMS	0

class COFGameRulesProxy : public CGameRulesProxy
{
public:
	DECLARE_CLASS( COFGameRulesProxy, CGameRulesProxy );
	DECLARE_NETWORKCLASS();
};

class COFGameRules : public CTeamplayRules
{
public:
	DECLARE_CLASS( COFGameRules, CTeamplayRules );

	 // This makes datatables able to access our private vars
#ifdef CLIENT_DLL
	DECLARE_CLIENTCLASS_NOBASE();
#else
	DECLARE_SERVERCLASS_NOBASE(); 
#endif
	
	COFGameRules();
	virtual ~COFGameRules();

	virtual void Precache( void );
	virtual bool ShouldCollide( int collisionGroup0, int collisionGroup1 );
	virtual bool ClientCommand( CBaseEntity *pEdict, const CCommand &args );
	virtual void Think( void );
	virtual void CreateStandardEntities( void );
	virtual int PlayerRelationship( CBaseEntity *pPlayer, CBaseEntity *pTarget );
	virtual void GoToIntermission( void );
	virtual void DeathNotice( CBasePlayer *pVictim, const CTakeDamageInfo &info );
	virtual const char *GetGameDescription( void );
	virtual const unsigned char *GetEncryptionKey( void ) { return (unsigned char *)"E2NcUkG2"; }
	virtual void ClientDisconnected( edict_t *pClient );
	virtual bool IsConnectedUserInfoChangeAllowed( CBasePlayer *pPlayer );

	virtual bool IsPlayingSpecialDeliveryMode( void );
};

inline COFGameRules* OFGameRules()
{
	return static_cast< COFGameRules* >( g_pGameRules );
}

#endif
