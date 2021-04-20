// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: COFTeam implementation
// Author(s): Nopey, Ms, Cherry!
//
#include "cbase.h"
#include "of_team.h"
#include "of_gamerules.h"
#include "of_shareddefs.h"
#include "dbg.h"

void SendProxy_TeamObjectList( const SendProp* pProp, const void* pStruct, const void* pData, DVariant* pOut, int iElement, int objectID )
{
    COFTeam* pTeam = ( COFTeam* )pData;

    // If this assertion fails, then SendProxyArrayLength_TeamObjectArray must have failed.
    Assert( iElement < pTeam->m_aObjects.Size() );

    CBaseEntity* pPlayer = pTeam->m_aObjects[iElement];
    pOut->m_Int = pPlayer->entindex();
}

int SendProxyArrayLength_TeamObjectArray( const void* pStruct, int objectID )
{
    COFTeam* pTeam = ( COFTeam* )pStruct;
    return pTeam->m_aObjects.Count();
}

// Datatable
// OFSTATUS: COMPLETE.
IMPLEMENT_SERVERCLASS_ST( COFTeam, DT_OFTeam )
    SendPropInt( SENDINFO( m_nFlagCaptures ), 8 ),
    SendPropInt( SENDINFO( m_iRole ), 4, SPROP_UNSIGNED ),
    SendPropArray2(
	    SendProxyArrayLength_TeamObjectArray,
        SendPropInt( "team_object_array_element", 0, 4, 21, SPROP_UNSIGNED, SendProxy_TeamObjectList ),
	    4 * MAX_PLAYERS,
	    0,
	    "team_object_array"
    )
    // m_hLeader should go here, however is not implented because it is only related to player destruction.
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS( tf_team, COFTeam );

//=========================================================
// COFTeam functions
//=========================================================

// OFSTATUS: COMPLETE
COFTeam::COFTeam()
{
	m_TeamColor = {0,0,0,0};
	m_nFlagCaptures = 0;
}

// OFSTATUS: COMPLETE
COFTeam::~COFTeam()
{}

// OFSTATUS: COMPLETE
// OFTODO: replace CBaseEntity with CBaseObject later!
void COFTeam::AddObject(CBaseEntity *pObject)
{
	if (!IsObjectOnTeam(pObject))
	{
		m_aObjects.AddToTail(pObject);
	}
}

// OFSTATUS: COMPLETE
// OFTODO: replace CBaseEntity with CBaseObject later!
bool COFTeam::IsObjectOnTeam(CBaseEntity *pObject)
{
	return (m_aObjects.Find(pObject) != -1);
}

// OFSTATUS: COMPLETE
// OFTODO: replace CBaseEntity with CBaseObject later!
void COFTeam::RemoveObject(CBaseEntity *pObject)
{
	if (IsObjectOnTeam(pObject))
	{
		m_aObjects.FindAndRemove(pObject);
	}
}

// OFSTATUS: INCOMPLETE
void COFTeam::AddPlayer( CBasePlayer *pPlayer )
{
    CTeam::AddPlayer(pPlayer);
    //OFTODO: something regarding setting a CBasePlayer *NetworkVar_m_hLeader
    OFGameRules()->TeamPlayerCountChanged(this);
}
// OFSTATUS: INCOMPLETE
void COFTeam::RemovePlayer( CBasePlayer *pPlayer )
{
    CTeam::RemovePlayer(pPlayer);
    //OFTODO: something regarding setting a CBasePlayer *NetworkVar_m_hLeader
    OFGameRules()->TeamPlayerCountChanged(this);
}

void COFTeam::SetColor(color32 Color)
{
	m_TeamColor = Color;
}

// OFSTATUS: COMPLETE
COFTeam *GetGlobalOFTeam( int iIndex )
{
    // TF2 dynamic casts in release builds
    // We'll just assert_cast, only checking if the CTeams are COFTeams in debug builds.
    return assert_cast<COFTeam *>(GetGlobalTeam( iIndex ));
}

//=========================================================
// COFTeamManager functions
//=========================================================

COFTeamManager s_OFTeamManager;

COFTeamManager *OFTeamMgr()
{
	return &s_OFTeamManager;
}

// OFSTATUS: COMPLETE
bool COFTeamManager::Init()
{
	//undefined *puVar1;
	//undefined *puVar2;
	//int iVar3;
	//int *in_stack_ffffffe4;

	/*
	puVar1 = PTR__g_Teams_00e34bdc;
	*(undefined4 *)(PTR__g_Teams_00e34bdc + 0xc) = 0;
	if (*(int *)(puVar1 + 8) < 0) {
		iVar3 = *(int *)puVar1;
	}
	else
	{
		iVar3 = *(int *)puVar1;
		if (iVar3 != 0) {
			in_stack_ffffffe4 = *(int **)__nl_symbol_ptr::_g_pMemAlloc;
			(**(code **)(*in_stack_ffffffe4 + 8))(in_stack_ffffffe4, iVar3);
			*(undefined4 *)puVar1 = 0;
			iVar3 = 0;
		}
		*(undefined4 *)(puVar1 + 4) = 0;
	}
	*/

	Shutdown();

	/*
	*(int *)(puVar1 + 0x10) = iVar3;

	puVar2 = PTR__g_aTeamColors_00e34dfc;
	puVar1 = PTR__g_aTeamNames_00e34dac;
	iVar3 = Create((CTFTeamManager *)in_stack_ffffffe4, *(char **)PTR__g_aTeamNames_00e34dac,
		SUB41(*(undefined4 *)PTR__g_aTeamColors_00e34dfc, 0));
	if (((iVar3 == 0) &&
		(iVar3 = Create((CTFTeamManager *)in_stack_ffffffe4, *(char **)(puVar1 + 4),
		SUB41(*(undefined4 *)(puVar2 + 4), 0)), iVar3 == 1)) &&
		(iVar3 = Create((CTFTeamManager *)in_stack_ffffffe4, *(char **)(puVar1 + 8),
		SUB41(*(undefined4 *)(puVar2 + 8), 0)), iVar3 == 2)) {
		iVar3 = Create((CTFTeamManager *)in_stack_ffffffe4, *(char **)(puVar1 + 0xc),
			SUB41(*(undefined4 *)(puVar2 + 0xc), 0));
		return iVar3 == 3;
	}
	*/

	for (int i = 0; i < OF_TEAM_COUNT; i++)
	{
		int index = Create( g_aTeamNames[i] , g_aTeamColors[i] );
		if (index != i)
			return false;
	}

	return true;
}

// OFSTATUS: COMPLETE
void COFTeamManager::Shutdown()
{
	// Note, don't delete each team since they are in the gEntList and will 
	// automatically be deleted from there, instead.
	g_Teams.Purge();
}

// OFSTATUS: COMPLETE
// this thing got messed up real bad
int COFTeamManager::Create(const char *TeamName, color32 TeamColor)
{
	CTeam *pTeam = static_cast<CTeam*>(CreateEntityByName("tf_team"));
	if (pTeam)
	{
		int iTeam = g_Teams.AddToTail(pTeam);
		pTeam->Init(TeamName, iTeam);
		pTeam->NetworkProp()->SetUpdateInterval(0.75f);
		
		// i dont think this teamcolor stuff is even used so... ignored
		//piVar4[0xf2] = _param_2;

		return iTeam;
	}
	return -1;
}

bool COFTeamManager::IsTeamValid(int iTeam)
{
	if ((-1 < iTeam) && (iTeam < g_Teams.Count()))
	{
		return true;
	}
	return false;
}

// OFSTATUS: COMPLETE
int COFTeamManager::GetFlagCaptures(int iTeam)
{
	if (IsTeamValid(iTeam))
	{
		COFTeam *pTeam = GetGlobalOFTeam(iTeam);
		if (!pTeam) return -1;

		pTeam->GetFlagCaptures();
	}
	return -1;
}

// OFSTATUS: COMPLETE
void COFTeamManager::IncrementFlagCaptures(int iTeam)
{
	// make this a function
	if (IsTeamValid(iTeam))
	{
		COFTeam *pTeam = GetGlobalOFTeam(iTeam);
		if (!pTeam) return;

		pTeam->IncrementFlagCaptures();
	}
}

// OFSTATUS: COMPLETE
void COFTeamManager::AddTeamScore(int iTeam, int iAmount)
{
	if (IsTeamValid(iTeam))
	{
		COFTeam *pTeam = GetGlobalOFTeam(iTeam);
		if (!pTeam) return;

		pTeam->AddScore(iAmount);
	}
}

// OFSTATUS: COMPLETE
int COFTeamManager::GetTeamCount()
{
	return g_Teams.Count();
}

// OFSTATUS: COMPLETE
COFTeam *COFTeamManager::GetTeam(int iTeam)
{
	if (IsTeamValid(iTeam))
	{
		return static_cast<COFTeam*>(g_Teams[iTeam]);
	}
	return NULL;
}

