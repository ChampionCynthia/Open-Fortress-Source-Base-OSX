//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//
// Open Fortress Modifications (CC-BY-NC-CA)
// * include animationlayer.h (client) or stub it (server) for CAnimationLayer.

#ifndef SEQUENCE_TRANSITIONER_H
#define SEQUENCE_TRANSITIONER_H
#ifdef _WIN32
#pragma once
#endif

#ifdef CLIENT_DLL
#include "animationlayer.h"
#else
class CAnimationLayer;
#endif

// ------------------------------------------------------------------------------------------------ //
// CSequenceTransitioner declaration.
// ------------------------------------------------------------------------------------------------ //
class CSequenceTransitioner
{
public:
	void CheckForSequenceChange( 
		// Describe the current animation state with these parameters.
		CStudioHdr *hdr,
		int nCurSequence, 

		// Even if the sequence hasn't changed, you can force it to interpolate from the previous
		// spot in the same sequence to the current spot in the same sequence by setting this to true.
		bool bForceNewSequence,

		// Follows EF_NOINTERP.
		bool bInterpolate
		);

	void UpdateCurrent( 
		// Describe the current animation state with these parameters.
		CStudioHdr *hdr,
		int nCurSequence, 
		float flCurCycle,
		float flCurPlaybackRate,
		float flCurTime
		);

	void RemoveAll( void ) { m_animationQueue.RemoveAll(); };

public:
	CUtlVector< CAnimationLayer >	m_animationQueue;
};

#endif // SEQUENCE_TRANSITIONER_H
