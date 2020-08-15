// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Game logic manager
// Author(s): ficool2, Fenteale
//

#include "cbase.h"
#include "of_shareddefs.h"
#include "of_gamerules.h"
#include "viewport_panel_names.h"
#include "gameeventdefs.h"
#include <KeyValues.h>
#include "ammodef.h"

#ifdef CLIENT_DLL
	#include "c_of_player.h"
#else
	#include "eventqueue.h"
	#include "player.h"
	#include "game.h"
	#include "items.h"
	#include "entitylist.h"
	#include "mapentities.h"
	#include "in_buttons.h"
	#include <ctype.h>
	#include "iscorer.h"
	#include "of_player.h"
	#include "of_gameinterface.h"	
	#include "of_bot_temp.h"

#endif

REGISTER_GAMERULES_CLASS( COFGameRules );

BEGIN_NETWORK_TABLE_NOBASE( COFGameRules, DT_OFGameRules )
#ifdef CLIENT_DLL
		//RecvPropBool( RECVINFO( ?? ) ),
#else
		//SendPropBool( SENDINFO( ?? ) ),
#endif
END_NETWORK_TABLE()

LINK_ENTITY_TO_CLASS( tf_gamerules, COFGameRulesProxy );

// OFSTATUS: COMPLETE
static const char *s_PreserveEnts[] =
{
	"tf_gamerules",
	"tf_player_manager",
	"tf_team",
	"tf_objective_resource",
	"keyframe_rope",
	"move_rope",
	"tf_",
	"tf_logic_training",
	"tf_logic_training_mode",
	"tf_powerup_bottle",
	"tf_mann_vs_machine_stats",
	"tf_wearable",
	"tf_wearable_demoshield",
	"tf_wearable_robot_arm",
	"tf_wearable_vm",
	"tf_logic_bonusround",
	"vote_controller",
	"monster_resource",
	"tf_logic_medieval",
	"tf_logic_cp_timer",
	"tf_logic_tower_defense",
	"tf_logic_mann_vs_machine",
	"func_upgradestation",
	"entity_rocket",
	"entity_carrier",
	"entity_sign",
	"entity_saucer",
	"tf_halloween_gift_pickup",
	"tf_logic_competitive",
	"tf_wearable_razorback",
	"entity_soldier_statue",
	"", // END Marker
};

#ifdef CLIENT_DLL
	void RecvProxy_OFGameRules( const RecvProp *pProp, void **pOut, void *pData, int objectID )
	{
		COFGameRules *pRules = OFGameRules();
		Assert( pRules );
		*pOut = pRules;
	}

	BEGIN_RECV_TABLE( COFGameRulesProxy, DT_OFGameRulesProxy )
		RecvPropDataTable( "tf_gamerules_data", 0, 0, &REFERENCE_RECV_TABLE( DT_OFGameRules ), RecvProxy_OFGameRules )
	END_RECV_TABLE()
#else
	void* SendProxy_OFGameRules( const SendProp *pProp, const void *pStructBase, const void *pData, CSendProxyRecipients *pRecipients, int objectID )
	{
		COFGameRules *pRules = OFGameRules();
		Assert( pRules );
		return pRules;
	}

	BEGIN_SEND_TABLE( COFGameRulesProxy, DT_OFGameRulesProxy )
		SendPropDataTable( "tf_gamerules_data", 0, &REFERENCE_SEND_TABLE( DT_OFGameRules ), SendProxy_OFGameRules )
	END_SEND_TABLE()
#endif

// OFSTATUS: INCOMPLETE	
COFGameRules::COFGameRules()
{
#ifndef CLIENT_DLL
#endif
}
	
// OFSTATUS: INCOMPLETE	
COFGameRules::~COFGameRules( void )
{
#ifndef CLIENT_DLL
#endif
}

// OFSTATUS: INCOMPLETE
void COFGameRules::CreateStandardEntities( void )
{
#ifndef CLIENT_DLL
	CBaseEntity::Create( "tf_gamerules", vec3_origin, vec3_angle );
#endif
}

// OFSTATUS: INCOMPLETE
void COFGameRules::Think( void )
{
#ifndef CLIENT_DLL	
	BaseClass::Think();
#endif
}

// OFSTATUS: INCOMPLETE (theres some kind of holiday calc here)
void COFGameRules::GoToIntermission( void )
{
#ifndef CLIENT_DLL
#endif
}

// OFSTATUS: INCOMPLETE
void COFGameRules::ClientDisconnected( edict_t *pClient )
{
#ifndef CLIENT_DLL
	CBasePlayer *pPlayer = (CBasePlayer *)CBaseEntity::Instance( pClient );
	if ( pPlayer )
	{
		// Remove the player from his team
		if ( pPlayer->GetTeam() )
		{
			pPlayer->GetTeam()->RemovePlayer( pPlayer );
		}
	}

	BaseClass::ClientDisconnected( pClient );

#endif
}


// OFSTATUS: INCOMPLETE ( this is a big function! )
void COFGameRules::DeathNotice( CBasePlayer *pVictim, const CTakeDamageInfo &info )
{
#ifndef CLIENT_DLL

	// Work out what killed the player, and send a message to all clients about it
	const char *killer_weapon_name = "world";		// by default, the player is killed by the world
	int killer_ID = 0;

	// Find the killer & the scorer
	CBaseEntity *pInflictor = info.GetInflictor();
	CBaseEntity *pKiller = info.GetAttacker();
	CBasePlayer *pScorer = GetDeathScorer( pKiller, pInflictor );

	// Custom kill type?
	if ( info.GetDamageCustom() )
	{
		killer_weapon_name = GetDamageCustomString( info );
		if ( pScorer )
		{
			killer_ID = pScorer->GetUserID();
		}
	}
	else
	{
		// Is the killer a client?
		if ( pScorer )
		{
			killer_ID = pScorer->GetUserID();
			
			if ( pInflictor )
			{
				if ( pInflictor == pScorer )
				{
					// If the inflictor is the killer,  then it must be their current weapon doing the damage
					if ( pScorer->GetActiveWeapon() )
					{
						killer_weapon_name = pScorer->GetActiveWeapon()->GetClassname();
					}
				}
				else
				{
					killer_weapon_name = pInflictor->GetClassname();  // it's just that easy
				}
			}
		}
		else
		{
			killer_weapon_name = pInflictor->GetClassname();
		}
	}

	IGameEvent *event = gameeventmanager->CreateEvent( "player_death" );
	if( event )
	{
		event->SetInt("userid", pVictim->GetUserID() );
		event->SetInt("attacker", killer_ID );
		event->SetString("weapon", killer_weapon_name );
		event->SetInt( "priority", 7 );
		gameeventmanager->FireEvent( event );
	}
#endif
}

// OFSTATUS: COMPLETE
const char *COFGameRules::GetGameDescription( void )
{ 
	return "Open Fortress"; 
} 

// OFSTATUS: INCOMPLETE 
bool COFGameRules::IsConnectedUserInfoChangeAllowed( CBasePlayer *pPlayer )
{
	return true;
}
 
// OFSTATUS: INCOMPLETE
void COFGameRules::Precache( void )
{
}

// OFSTATUS: NEEDS LABELS
bool COFGameRules::ShouldCollide( int collisionGroup0, int collisionGroup1 )
{
	if ( collisionGroup0 > collisionGroup1 )
	{
		V_swap( collisionGroup0, collisionGroup1 );
	}

	bool var1 = false;
	switch ( collisionGroup0 )
	{
		case COLLISION_GROUP_PLAYER_MOVEMENT:
			if ( collisionGroup1 == COLLISION_GROUP_WEAPON || collisionGroup1 == COLLISION_GROUP_PROJECTILE 
				|| collisionGroup1 == OF_COLLISION_GROUP_ROCKETS || collisionGroup1 == OF_COLLISION_GROUP_UNKNOWN27 )
				return false;		
			if ( collisionGroup1 == OF_COLLISION_GROUP_UNKNOWN20 )
				return false;
			break;		
		case COLLISION_GROUP_PLAYER:
			if ( collisionGroup1 == OF_COLLISION_GROUP_ROCKETS || collisionGroup1 == OF_COLLISION_GROUP_UNKNOWN27 )
				return true;
			if ( collisionGroup1 == OF_COLLISION_GROUP_UNKNOWN20 )
				return false;
			var1 = true;
			break;
		case COLLISION_GROUP_WEAPON:
		case OF_COLLISION_GROUP_UNKNOWN20:
		case COLLISION_GROUP_PROJECTILE:
			if ( collisionGroup1 == OF_COLLISION_GROUP_ROCKETS )
				return true;
			break;
		case OF_COLLISION_GROUP_ROCKETS:
		case OF_COLLISION_GROUP_UNKNOWN27:
			break;
		default:
			var1 = true;
			break;
	}
	
	if ( !var1 && collisionGroup1 == OF_COLLISION_GROUP_UNKNOWN27 )
		return false; 
	
	if ( collisionGroup1 != OF_COLLISION_GROUP_UNKNOWN25 )
	{
		switch ( collisionGroup0 )
		{
			case OF_COLLISION_GROUP_UNKNOWN20:
				if ( collisionGroup1 == OF_COLLISION_GROUP_UNKNOWN20 )
					return false;
				return BaseClass::ShouldCollide( collisionGroup0, collisionGroup1 );
			case COLLISION_GROUP_PLAYER_MOVEMENT:
				if ( collisionGroup1 == OF_COLLISION_GROUP_UNKNOWN23 )
					return false;			
				break;
			case COLLISION_GROUP_PLAYER:
				if ( collisionGroup1 == OF_COLLISION_GROUP_UNKNOWN23 )
					return false;				
				break;
			default:
				return BaseClass::ShouldCollide( collisionGroup0, collisionGroup1 );
		}
		
		if ( collisionGroup1 != OF_COLLISION_GROUP_UNKNOWN26 )
			return BaseClass::ShouldCollide( collisionGroup0, collisionGroup1 );
		
		return false;
	}
	
	return ( collisionGroup0 == COLLISION_GROUP_PLAYER || collisionGroup0 == COLLISION_GROUP_PLAYER_MOVEMENT );
}

// OFSTATUS: INCOMPLETE 
bool COFGameRules::ClientCommand( CBaseEntity *pEdict, const CCommand &args )
{
#ifndef CLIENT_DLL
	if ( BaseClass::ClientCommand( pEdict, args ) )
		return true;

	COFPlayer *pPlayer = (COFPlayer *) pEdict;

	if ( pPlayer->ClientCommand( args ) )
		return true;
#endif

	return false;
}

//OFSTATUS: INCOMPLETE
//do we want to handle this?
bool COFGameRules::IsPlayingSpecialDeliveryMode( void ) {
	return false;
}

ConVar ammo_max( "ammo_max", "5000", FCVAR_GAMEDLL | FCVAR_REPLICATED );

// OFSTATUS: COMPLETE
CAmmoDef *GetAmmoDef()
{
	static CAmmoDef def;
	static bool bInitted = false;
	
	if ( !bInitted )
	{
		bInitted = true;
	
		int iAmmoIndex = AMMONAME_FIRST;
		do
		{
			def.AddAmmoType( g_aAmmoNames[iAmmoIndex], DMG_BULLET | DMG_NOCLOSEDISTANCEMOD | DMG_USEDISTANCEMOD, 1,	0, 0, ammo_max.GetInt(), 2400.0, 10, 14, 8 );
			iAmmoIndex++;
		}
		while ( iAmmoIndex != AMMONAME_LAST )
	}

	return &def;
}

#ifdef GAME_DLL
// OFSTATUS: INCOMPLETE (move this to of_bot_temp?) 
void Bot_f()
{		
	// Look at -count.
	int count = 1;
	count = clamp( count, 1, 16 );

	int iTeam = TEAM_COMBINE;
			
	// Look at -frozen.
	bool bFrozen = false;
		
	// Ok, spawn all the bots.
	while ( --count >= 0 )
	{
		BotPutInServer( bFrozen, iTeam );
	}
}

ConCommand cc_Bot( "bot", Bot_f, "Add a bot.", FCVAR_CHEAT );
#endif