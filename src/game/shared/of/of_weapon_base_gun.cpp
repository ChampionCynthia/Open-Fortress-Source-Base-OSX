// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Impl COFWeaponBase, the root of all OF weapons
// Author(s): Nopey, Fenteale
//
#include "cbase.h"
#include "of_weapon_base.h"

// ----------------------------------------------------------------------------- //
// COFWeaponBase tables.
// ----------------------------------------------------------------------------- //

IMPLEMENT_NETWORKCLASS_ALIASED( COFWeaponBaseGun, DT_OFWeaponBaseGun )

BEGIN_NETWORK_TABLE( COFWeaponBaseGun, DT_OFWeaponBaseGun )
#ifdef CLIENT_DLL
  
#else
/* SDK Garbo that might or might not be useful
    // world weapon models have no animations
      SendPropExclude( "DT_AnimTimeMustBeFirst", "m_flAnimTime" ),
    SendPropExclude( "DT_BaseAnimating", "m_nSequence" ),
*/
#endif
END_NETWORK_TABLE()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA( COFWeaponBaseGun )

END_PREDICTION_DATA()
#endif

// Do we need this? Weapon bases never get used on their own - Kay
LINK_ENTITY_TO_CLASS( tf_weapon_base_gun, COFWeaponBaseGun );


#ifdef GAME_DLL

    BEGIN_DATADESC( COFWeaponBaseGun )

        // New weapon Think and Touch Functions go here..

    END_DATADESC()

#endif
