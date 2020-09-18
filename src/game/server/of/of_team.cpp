// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: COFTeam implementation
// Author(s): Nopey, Ms
//
#include "cbase.h"
#include "of_team.h"
#include "of_gamerules.h"
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


// OFSTATUS: INCOMPLETE, about 100 lines decomped. plenty of members.
COFTeam::COFTeam()
{}

// OFSTATUS: COMPLETE
COFTeam::~COFTeam()
{}

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

// OFSTATUS: COMPLETE
COFTeam *GetGlobalOFTeam( int iIndex )
{
    // TF2 dynamic casts in release builds
    // We'll just assert_cast, only checking if the CTeams are COFTeams in debug builds.
    return assert_cast<COFTeam *>(GetGlobalTeam( iIndex ));
}
