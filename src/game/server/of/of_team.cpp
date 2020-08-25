// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: COFTeam implementation
// Author(s): Nopey
//
#include "cbase.h"
#include "of_team.h"
#include "of_gamerules.h"
#include "dbg.h"

// Datatable
// OFSTATUS: INCOMPLETE. missing netprops
IMPLEMENT_SERVERCLASS_ST(COFTeam, DT_OFTeam)
        //SendPropBool( SENDINFO( ?? ) ),
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
