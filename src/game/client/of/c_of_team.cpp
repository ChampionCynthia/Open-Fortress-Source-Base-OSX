// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose:
// Author(s): Ms
#include "cbase.h"
#include "c_of_team.h"

void RecvProxy_TeamObjectList( const CRecvProxyData* pData, void* pStruct, void* pOut )
{
	C_OFTeam* pTeam = ( C_OFTeam* )pOut;
	pTeam->m_aObjects[pData->m_iElement] = pData->m_Value.m_Int;
}

void RecvProxyArrayLength_TeamObjectArray( void* pStruct, int objectID, int currentArrayLength )
{
	C_OFTeam* pTeam = ( C_OFTeam* )pStruct;

	if ( pTeam->m_aObjects.Size() != currentArrayLength )
		pTeam->m_aObjects.SetSize( currentArrayLength );
}

// OFSTATUS: COMPLETE.
IMPLEMENT_CLIENTCLASS_DT( C_OFTeam, DT_OFTeam, COFTeam )
	RecvPropInt( RECVINFO( m_nFlagCaptures ) ),
	RecvPropInt( RECVINFO( m_iRole ) ),
	RecvPropArray2(
		RecvProxyArrayLength_TeamObjectArray,
		RecvPropInt( "team_object_array_element", 0, SIZEOF_IGNORE, 0, RecvProxy_TeamObjectList ),
		4 * MAX_PLAYERS,
		0,
		"team_object_array"
	)
	// m_hLeader should go here, however is not implented because it is only related to player destruction.
END_NETWORK_TABLE()

// OFSTATUS: INCOMPLETE
C_OFTeam::C_OFTeam()
{
}

// OFSTATUS: INCOMPLETE
C_OFTeam::~C_OFTeam()
{
}

// OFSTATUS: INCOMPLETE
void C_OFTeam::ClientThink()
{
	BaseClass::ClientThink();
//	UpdateTeamName();
//	( **( code** )( *( int* )this + 600 ) )
//		( this, *( float* )( *( int* )PTR__gpGlobals_00f8d098 + 12 ) + 0.50000000 );
}
