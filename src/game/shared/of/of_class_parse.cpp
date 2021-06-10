// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of ClassData
// Author(s): KaydemonLP
//

#include "cbase.h"
#include "of_class_parse.h"
#include "filesystem.h"
#include "of_shareddefs.h"

// RE: GetWeaponID, GetAmmoName and GetBuildableId aren't RE-d yet

void TFPlayerClassData_t::ParseData( KeyValues *kvData )
{
/*
	puVar1 = __nl_symbol_ptr::___stack_chk_guard;
	local_14 = *(int *)__nl_symbol_ptr::___stack_chk_guard;
*/
	V_strncpy( m_szName, kvData->GetString( "name" ), sizeof(m_szName) );
	
	V_strncpy( m_szModelHWM, kvData->GetString( "model_hwm" ), sizeof(m_szModelHWM) );
	
	V_strncpy( m_szModel, kvData->GetString( "model" ), sizeof(m_szModel) );
	
	V_strncpy( m_szViewmodel, kvData->GetString( "model_hands" ), sizeof(m_szViewmodel) );
	
	V_strncpy( m_szNameLocalized, kvData->GetString( "localize_name" ), sizeof(m_szNameLocalized) );
	
	m_flMaxSpeed = kvData->GetFloat( "speed_max" );
	
	m_iMaxHealth = kvData->GetInt( "health_max" );
	m_iMaxArmor = kvData->GetInt( "armor_max" );
	
	for( int i = 0; i < sizeof(m_iWeaponIDs); i++ )
	{
		m_iWeaponIDs[i] = GetWeaponId( kvData->GetString( UTIL_VarArgs( "weapon%d", i ) ) );
	}
	
	for( int i = 0; i < sizeof(m_iGrenades); i++ )
	{
		m_iGrenades[i] = GetWeaponId( kvData->GetString( UTIL_VarArgs( "grenade%d", i ) ) );
	}
	
	KeyValues *kvAmmoMax = kvData->FindKey( "AmmoMax" );
	if( kvAmmoMax )
	{
		for( int i = 0; i < sizeof(m_iGrenades); i++ )
		{
			m_iMaxAmmo[i] = kvAmmoMax->GetInt(GetAmmoName(i),0);
		}
	}

	for( int i = 0; i < sizeof(m_iBuildable); i++ )
	{
		m_iBuildable[i] = GetBuildableId( kvData->GetString( UTIL_VarArgs( "buildable%d", i ), "") );
	}

	m_bDontDoAirwalk = kvData->GetBool( "DontDoAirwalk" );
	m_bDontDoNewJump = kvData->GetBool( "DontDoNewJump" );

	m_flCameraOffsetForward = kvData->GetFloat( "cameraoffset_forward" );
	m_flCameraOffsetRight = kvData->GetFloat( "cameraoffset_right" );
	m_flCameraOffsetUp = kvData->GetFloat( "cameraoffset_up" );
	
	V_strncpy( m_szDeathSounds[0], kvData->GetString( "sound_death", "Player.Death" ), 
	sizeof(m_szDeathSounds[0]) );
	
	V_strncpy( m_szDeathSounds[1], kvData->GetString( "sound_crit_death", "TFPlayer.CritDeath" ), 
	sizeof(m_szDeathSounds[1]) );
	
	V_strncpy( m_szDeathSounds[2], kvData->GetString( "sound_melee_death", "Player.MeleeDeath" ), 
	sizeof(m_szDeathSounds[2]) );
	
	V_strncpy( m_szDeathSounds[3], kvData->GetString( "sound_explosion_death", "Player.ExplosionDeath" ), 
	sizeof(m_szDeathSounds[3]) );

	m_bIsParsed = true;
	/*
	if (*(int *)puVar1 == local_14) 
	{
		return;
	}*/
}

void TFPlayerClassData_t::AddAdditionalPlayerDeathSounds()
{
	CopySoundNameWithModifierToken( m_szDeathSounds[4], m_szDeathSounds[0], sizeof(m_szDeathSounds[4]),"MVM_" );
	CopySoundNameWithModifierToken( m_szDeathSounds[8], m_szDeathSounds[0], sizeof(m_szDeathSounds[8]),"M_MVM_" );

	CopySoundNameWithModifierToken( m_szDeathSounds[5], m_szDeathSounds[1], sizeof(m_szDeathSounds[5]),"MVM_" );
	CopySoundNameWithModifierToken( m_szDeathSounds[9], m_szDeathSounds[1], sizeof(m_szDeathSounds[9]),"M_MVM_" );

	CopySoundNameWithModifierToken( m_szDeathSounds[6], m_szDeathSounds[2], sizeof(m_szDeathSounds[6]),"MVM_" );
	CopySoundNameWithModifierToken( m_szDeathSounds[10], m_szDeathSounds[2], sizeof(m_szDeathSounds[10]),"M_MVM_" );

	CopySoundNameWithModifierToken( m_szDeathSounds[7], m_szDeathSounds[3], sizeof(m_szDeathSounds[7]),"MVM_" );
	CopySoundNameWithModifierToken( m_szDeathSounds[11], m_szDeathSounds[3], sizeof(m_szDeathSounds[11]),"M_MVM_" );
	return;
}

char *TFPlayerClassData_t::GetDeathSound( int iSoundIndex )
{
	return m_szDeathSounds[iSoundIndex];
}

char *TFPlayerClassData_t::GetModelName( void )
{
	return m_szModel;
}

char *GetTFEncryptionKey( void )
{
	return "E2NcUkG2";
}

char *g_szClassFilepaths[] =
{
	"", // UNDEFINED
	"scripts/playerclasses/scout",
	"scripts/playerclasses/sniper",
	"scripts/playerclasses/soldier",
	"scripts/playerclasses/demoman",
	"scripts/playerclasses/medic",
	"scripts/playerclasses/heavywepons",
	"scripts/playerclasses/pyro",
	"scripts/playerclasses/spy",
	"scripts/playerclasses/engineer",
	"scripts/playerclasses/civilian"
};

// RE: This seems like a weird way of managing this?
// Valve I guess - Kay
CTFPlayerClassDataMgr g_TFPlayerClassDataMgr;
CTFPlayerClassDataMgr *g_pTFPlayerClassDataMgr = &g_TFPlayerClassDataMgr;

TFPlayerClassData_t *GetPlayerClassData( uint32 iClassIndex )
{
  return g_pTFPlayerClassDataMgr->Get( iClassIndex );
}


bool CTFPlayerClassDataMgr::Init( void )
{
	V_strncpy( m_ClassDatabase[0].m_szName, "undefined", sizeof(m_ClassDatabase[0].m_szName) );
	V_strncpy( m_ClassDatabase[0].m_szModel, "models/player/scout.mdl", sizeof(m_ClassDatabase[0].m_szName) );
	V_strncpy( m_ClassDatabase[0].m_szNameLocalized, "undefined", sizeof(m_ClassDatabase[0].m_szName) );
	
	for( int i = 1; i < OF_CLASS_COUNT; i++ )
	{
		if( m_ClassDatabase[i].m_bIsParsed )
			continue;

		KeyValues *kvClassData = ReadEncryptedKVFile( filesystem, g_szClassFilepaths[i], (const unsigned char *)GetTFEncryptionKey() );
		if( kvClassData )
		{
			m_ClassDatabase[i].ParseData( kvClassData );
			kvClassData->deleteThis();
		}
	}

	return true;
}

TFPlayerClassData_t *CTFPlayerClassDataMgr::Get( unsigned int iClassIndex )
{
	return &m_ClassDatabase[iClassIndex];
}

// RE: Called somewhere in CSoundEmitterSystem::LevelInitPreEntity()
void CTFPlayerClassDataMgr::AddAdditionalPlayerDeathSounds( void )
{
	for( int i = 1; i < sizeof(m_ClassDatabase); i++ )
	{
		m_ClassDatabase[i].AddAdditionalPlayerDeathSounds();
	}
}

CTFPlayerClassShared::CTFPlayerClassShared()
{
	m_iClass = 0;
#ifdef CLIENT_DLL
	m_szClassIcon[0] = '\0';
	m_szCustomModel[0] = '\0';
#else
	m_szClassIcon.Set( NULL_STRING );
	m_szCustomModel.Set( NULL_STRING );
#endif
	// RE: I hate the fact that there is so much bloat for set custom model
	// But apparently some plugins use it so i gotta keep it - Kay
	m_vecCustomModelOffset = vec3_origin;
	m_angCustomModelRotation = vec3_angle;
	m_bCustomModelRotates = false;
	m_iCustomModelParity = 0;

	Reset();
}

bool CTFPlayerClassShared::Init( int iClassIndex )
{
	Reset();

	m_iClass = iClassIndex;

	// RE: Not defined yet, probably sould do that in the shareddefs
	m_szClassIcon.Set( AllocPooledString( g_aRawPlayerClassNamesShort[ m_iClass ] ) );
	
	return true;
}

void CTFPlayerClassShared::Reset( void )
{
	m_iClass = 0;
	m_szClassIcon = 0;

	m_szCustomModel = 0;
	m_vecCustomModelOffset = vec3_origin;
	m_angCustomModelRotation = vec3_angle;
	m_bCustomModelRotates = true;
	m_bCustomRotationSet = false;
	m_bCustomModelVisibleToSelf = true;
	m_bCustomModelClassAnim = false;
	m_iCustomModelParity = 0;
}

bool CTFPlayerClassShared::CanBuildObject( int iObjectIndex )
{
	TFPlayerClassData_t *pClassData = GetPlayerClassData( m_iClass );
	for( int i = 0; i < sizeof(pClassData->m_iBuildable); i++ )
	{
		if( pClassData->m_iBuildable[i] == iObjectIndex )
			return true;
	}

	return false;
}

#ifdef GAME_DLL
void CTFPlayerClassShared::SetCustomModel( const char *szModelName, bool bCustomModelClassAnim )
{
	if( !(szModelName && szModelName[0]) ) 
	{
		m_szCustomModel = 0;
		m_vecCustomModelOffset = vec3_origin;
		m_angCustomModelRotation = vec3_angle;
	}
	else 
	{
		CBaseEntity::SetAllowPrecache( true );
		CBaseEntity::PrecacheModel( szModelName, true );
		CBaseEntity::SetAllowPrecache( CBaseEntity::IsPrecacheAllowed() );
		
		m_szCustomModel = AllocPooledString(szModelName);

		m_bCustomModelClassAnim = bCustomModelClassAnim;
	}

	m_iCustomModelParity = ( m_iCustomModelParity + 1 ) & 7;
}
#endif

bool CTFPlayerClassShared::CustomModelHasChanged( void )
{
	if( m_iCustomModelParity != m_iOldCustomModelParity )
	{
		m_iOldCustomModelParity = m_iCustomModelParity;
		return true;
	}
	return false;
}