//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//
// Open Fortress Modifications (CC-BY-NC-CA)
// * include the new activitylist.inc file rather than listing out all two thousand here

#ifndef AI_ACTIVITY_H
#define AI_ACTIVITY_H
#ifdef _WIN32
#pragma once
#endif

#define ACTIVITY_NOT_AVAILABLE		-1

typedef enum
{
	// ACT_INVALID can't be moved to activitylist.inc, as it shouldn't appear in ActivityList_RegisterSharedActivities
	ACT_INVALID = -1,			// So we have something more succint to check for than '-1'
	#define ACT(_n) _n,
	#include "activitylist.inc"
	#undef ACT
	// this is the end of the global activities, private per-monster activities start here.
	LAST_SHARED_ACTIVITY,
} Activity;


#endif // AI_ACTIVITY_H

