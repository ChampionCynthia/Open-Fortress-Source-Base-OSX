//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
#ifndef IN_BUTTONS_H
#define IN_BUTTONS_H
#ifdef _WIN32
#pragma once
#endif

#define IN_ATTACK		(1 << 0)    // 1
#define IN_JUMP			(1 << 1)    // 2
#define IN_DUCK			(1 << 2)    // 4
#define IN_FORWARD		(1 << 3)    // 8
#define IN_BACK			(1 << 4)    // 16
#define IN_USE			(1 << 5)    // 32
#define IN_CANCEL		(1 << 6)    // 64
#define IN_LEFT			(1 << 7)    // 128
#define IN_RIGHT		(1 << 8)    // 256
#define IN_MOVELEFT		(1 << 9)    // 512
#define IN_MOVERIGHT	(1 << 10)   // 1024
#define IN_ATTACK2		(1 << 11)   // 2048
#define IN_RUN			(1 << 12)   // 4096
#define IN_RELOAD		(1 << 13)   // 8192
#define IN_ALT1			(1 << 14)   // 16384
#define IN_ALT2			(1 << 15)   // 32768
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2
#define	IN_ATTACK3		(1 << 25)

#endif // IN_BUTTONS_H
