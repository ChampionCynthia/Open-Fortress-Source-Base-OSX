// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Networking between server and client Fire effects, mostly a copy of sdk_fx_shared
// Author(s): KaydemonLP
//

#pragma once

#ifdef CLIENT_DLL
#define COFWeaponBase C_OFWeaponBase
#endif

class COFWeaponBase;

// This runs on both the client and the server.
// On the server, it only does the damage calculations.
// On the client, it does all the effects.
void FX_FireBullets(
	COFWeaponBase *pWeapon,
	int iPlayer,
	const Vector &vOrigin,
	const QAngle &vAngles,
	int iWeaponID,
	int iMode,
	int iSeed,
	float flSpread,
	float flDamage,
	bool bCritical
	);

