// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: 
// Author(s): KaydemonLP
//
#pragma once

#include "of_weapon_base_gun.h"

// Client specific.
#ifdef CLIENT_DLL
#define COFSMG C_OFSMG
#endif



//=============================================================================
//
// TF Weapon Sub-machine gun.
//
class COFSMG : public COFWeaponBaseGun
{
public:

	DECLARE_CLASS( COFSMG, COFWeaponBaseGun );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

#ifdef GAME_DLL
	DECLARE_DATADESC();
#endif

	virtual OFWeaponID	GetWeaponID(void) const			{ return OF_WEAPON_SMG; }
};