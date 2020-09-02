// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Impl COFWeaponBase, the root of all OF weapons
// Author(s): Nopey
//
#include "cbase.h"
#include "of_weapon_base.h"

// ----------------------------------------------------------------------------- //
// COFWeaponBase tables.
// ----------------------------------------------------------------------------- //

IMPLEMENT_NETWORKCLASS_ALIASED( OFWeaponBase, DT_OFWeaponBase )

BEGIN_NETWORK_TABLE( COFWeaponBase, DT_OFWeaponBase )
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
BEGIN_PREDICTION_DATA( COFWeaponBase )
    DEFINE_PRED_FIELD( m_flTimeWeaponIdle, FIELD_FLOAT, FTYPEDESC_OVERRIDE | FTYPEDESC_NOERRORCHECK ),
END_PREDICTION_DATA()
#endif

LINK_ENTITY_TO_CLASS( tf_weapon_base, COFWeaponBase );


#ifdef GAME_DLL

    BEGIN_DATADESC( COFWeaponBase )

        // New weapon Think and Touch Functions go here..

    END_DATADESC()

#endif


// ----------------------------------------------------------------------------- //
// COFWeaponBase implementation. 
// ----------------------------------------------------------------------------- //

//OFSTATUS: INCOMPLETE, massive (~500 lines). (lots of fields, too)
COFWeaponBase::COFWeaponBase() {}

//OFSTATUS: COMPLETE
CBaseEntity *COFWeaponBase::GetOwnerViaInterface ()
{
    return CBaseCombatWeapon::GetOwner();
}

//OFSTATUS: COMPLETE
bool COFWeaponBase::HasAmmo()
{
    if(IsEnergyWeapon())
        return true;
    else
        return CBaseCombatWeapon::HasAmmo();
}

//OFSTATUS: INCOMPLETE
bool COFWeaponBase::CanHolster() const
{
    /*
    MysteryThing:  offset 0x769*4
    MysteryThing2: offset 0x768*4
    MysteryThing3: offset 0x42*4
    */

    CBaseCombatCharacter* p_Character = CBaseCombatWeapon::GetOwner();
    if(p_Character && p_Character->IsPlayer())
        if(p_Character->GetActiveWeapon() != this || p_Character->MysteryThing <= gpGlobals + 0xc)
            // Only for Attributes stuff
            // if( CAttributeManager::AttribHookValue<int>(0, "honorbound", static_cast_pointer<CBaseEntity>(this), nullptr, true)
            if( p_Character->MysteryThing2 == 0 && p_Character->MysteryThing3 < 0x33)
                return false;
    
    return true;
}


//OFSTATUS: COMPLETE
bool COFWeaponBase::IsEnergyWeapon() const
{
    return false;
}