// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Game logic manager
// Author(s): ficool2, Fenteale, Nopey
//
#pragma once

#include "gamerules.h"
#include "teamplayroundbased_gamerules.h"
#include "gamevars_shared.h"

#ifndef CLIENT_DLL
#include "of_player.h"
#endif

#ifdef CLIENT_DLL
	#define COFGameRules C_OFGameRules
	#define COFGameRulesProxy C_OFGameRulesProxy
#endif

#ifdef GAME_DLL
class COFTeam;
#endif

#define HUD_ALERT_SCRAMBLE_TEAMS	0

class COFGameRulesProxy : public CTeamplayRoundBasedRulesProxy, public CGameEventListener
{
public:
	DECLARE_CLASS( COFGameRulesProxy, CTeamplayRoundBasedRulesProxy );
	DECLARE_NETWORKCLASS();

	// CGameEventListener::
	virtual void FireGameEvent( IGameEvent *pEvent ) override;
};

class COFGameRules : public CTeamplayRoundBasedRules
{
public:
	DECLARE_CLASS( COFGameRules, CTeamplayRoundBasedRules );

	 // This makes datatables able to access our private vars
	DECLARE_NETWORKCLASS_NOBASE();
	
	COFGameRules();
	virtual ~COFGameRules();

#ifdef GAME_DLL
	virtual void Precache( void );
#endif
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
#ifdef GAME_DLL
	void TeamPlayerCountChanged(COFTeam *);
#endif
	// overrides & chains to CTeamplayRoundBasedRules's impl of CGameEventListener::FireGameEvent
	virtual void FireGameEvent (IGameEvent *) override;

	//OFSTATUS: COMPLETE, unless we want special.. delivery? no we don't, and why would we?
	inline bool IsPlayingSpecialDeliveryMode( void ) { return false; };
};

inline COFGameRules* OFGameRules()
{
	return static_cast< COFGameRules* >( g_pGameRules );
}
