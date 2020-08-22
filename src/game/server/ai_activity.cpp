//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Activities that are available to all NPCs.
//
//=============================================================================//
// Open Fortress Modifications (CC-BY-NC-CA)
// * Rename ADD_ACTIVITY_TO_SR macro to ACT for use in activitylist.inc
// * include the new activitylist.inc file rather than listing out all two thousand here

#include "cbase.h"
#include "ai_activity.h"
#include "ai_basenpc.h"
#include "stringregistry.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//=============================================================================
// Init static variables
//=============================================================================
CStringRegistry* CAI_BaseNPC::m_pActivitySR	= NULL;
int				 CAI_BaseNPC::m_iNumActivities = 0;

//-----------------------------------------------------------------------------
// Purpose: Add an activity to the activity string registry and increment
//			the acitivty counter
//-----------------------------------------------------------------------------
void CAI_BaseNPC::AddActivityToSR(const char *actName, int actID) 
{
	Assert( m_pActivitySR );
	if ( !m_pActivitySR )
		return;

	// technically order isn't dependent, but it's too damn easy to forget to add new ACT_'s to all three lists.

	// NOTE: This assertion generally means that the activity enums are out of order or that new enums were not added to all
	//		 relevant tables.  Make sure that you have included all new enums in:
	//			game_shared/ai_activity.h
	//			game_shared/activitylist.cpp
	//			dlls/ai_activity.cpp
	MEM_ALLOC_CREDIT();

	static int lastActID = -2;
	Assert( actID >= LAST_SHARED_ACTIVITY || actID == lastActID + 1 || actID == ACT_INVALID );
	lastActID = actID;

	m_pActivitySR->AddString(actName, actID);
	m_iNumActivities++;
}

//-----------------------------------------------------------------------------
// Purpose: Given and activity ID, return the activity name
//-----------------------------------------------------------------------------
const char *CAI_BaseNPC::GetActivityName(int actID) 
{
	if ( actID == -1 )
		return "ACT_INVALID";

	// m_pActivitySR only contains public activities, ActivityList_NameForIndex() has them all
	const char *name = ActivityList_NameForIndex(actID);	

	if( !name )
	{
		AssertOnce( !"CAI_BaseNPC::GetActivityName() returning NULL!" );
	}

	return name;
}

//-----------------------------------------------------------------------------
// Purpose: Given and activity name, return the activity ID
//-----------------------------------------------------------------------------
int CAI_BaseNPC::GetActivityID(const char* actName) 
{
	Assert( m_pActivitySR );
	if ( !m_pActivitySR )
		return ACT_INVALID;

	return m_pActivitySR->GetStringID(actName);
}


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CAI_BaseNPC::InitDefaultActivitySR(void) 
{
	#define ACT(activityname) AddActivityToSR(#activityname,activityname);
	// ACT_INVALID can't be moved to activitylist.inc, as it shouldn't appear in ActivityList_RegisterSharedActivities
	ACT( ACT_INVALID );
	#include "activitylist.inc"
	#undef ACT
}
