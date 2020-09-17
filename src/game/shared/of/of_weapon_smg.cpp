// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: 
// Author(s): KaydemonLP
//
#include "cbase.h"
#include "of_weapon_smg.h"

//=============================================================================
// SMG
//=============================================================================
IMPLEMENT_NETWORKCLASS_ALIASED( OFSMG, DT_WeaponSMG )

BEGIN_NETWORK_TABLE( COFSMG, DT_WeaponSMG )
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( COFSMG )
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS( tf_weapon_smg, COFSMG );

#ifdef GAME_DLL
BEGIN_DATADESC( COFSMG )
END_DATADESC()
#endif
