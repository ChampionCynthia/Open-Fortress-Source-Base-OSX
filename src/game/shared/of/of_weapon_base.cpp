// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Impl COFWeaponBase, the root of all OF weapons
// Author(s): Nopey, Fenteale
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
bool COFWeaponBase::VisibleInWeaponSelection()
{
    //NOTE: Trimmed code related to checking if the game is in training mode.
    return CBaseCombatWeapon::VisibleInWeaponSelection();
}

//OFSTATUS: COMPLETE
bool COFWeaponBase::HasAmmo()
{
    /* NOTE: Trimmed code
    if(IsEnergyWeapon())
        return true;
    else
    */
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

    // CBaseCombatCharacter* p_Character = CBaseCombatWeapon::GetOwner();
    /*
    //This comment block is not compiling, OFTODO: Fix this!
    if(p_Character && p_Character->IsPlayer())
        if(p_Character->GetActiveWeapon() != this || p_Character->MysteryThing <= gpGlobals + 0xc)
            // Only for Attributes stuff
            // if( CAttributeManager::AttribHookValue<int>(0, "honorbound", static_cast_pointer<CBaseEntity>(this), nullptr, true)
            if( p_Character->MysteryThing2 == 0 && p_Character->MysteryThing3 < 0x33)
                return false;
    */
    return true;
    
}

//OFSTATUS: INCOMPLETE
void COFWeaponBase::SetWeaponVisible(bool visible)
{
    if(!visible)
    {
        AddEffects(EF_NODRAW);
        return;
    }
    /*
    byte *pbVar1;
    ushort uVar2;
    vtableCTFWeaponBase *this_00; //pretty sure this is supposed to be another member
    ushort *puVar3;
    ushort *puVar4;
    ushort uVar5;
    uint uVar6;
    uint uVar7;
    vtableCTFWeaponBase *pvVar8; //pretty sure this is supposed to be another member
    uint local_24;
    

    pvVar8 = (vtableCTFWeaponBase *)((uint)this[0x37].vtable & 0xffffffdf);
    if (this[0x37].vtable != pvVar8)
    {
        if (*(char *)&this[0x17].vtable == '\0') {
            this_00 = this[8].vtable;
            if ((this_00 != (vtableCTFWeaponBase *)0x0) &&
            (((uint)this_00->CTFWeaponBase::~CTFWeaponBase & 0x100) == 0)) {
                this_00->CTFWeaponBase::~CTFWeaponBase =
                    (~CTFWeaponBase *)((uint)this_00->CTFWeaponBase::~CTFWeaponBase | 1);
                puVar4 = (ushort *)GetChangeAccessor((CBaseEdict *)this_00);
                puVar3 = *(ushort **)PTR__g_pSharedChangeInfo_00e31128;
                uVar2 = *puVar3;

                bool uCond1 = false;
                bool uCond2 = false;

                if (puVar4[1] == uVar2) {
                    uVar6 = (uint)*puVar4;
                    uVar2 = puVar3[uVar6 * 0x14 + 0x14];
                    local_24 = 0;
                    uVar5 = 0;
                    if (uVar2 != 0) {
                        uVar7 = 0;

                        uVar5 = uVar2;
                        local_24 = (uint)uVar2;
                        uCond1 = uVar2 == 0x13;
                        do {
                            if (puVar3[uVar6 * 0x14 + uVar7 + 1] == 0xdc) 
                            {
                                uCond2 = true;
                                break;
                            }
                            uVar7 = uVar7 + 1;
                        } while (uVar7 < (uint)uVar2);
                        
                        
                    }
                    if(uCond1 && !uCond2)
                        puVar4[1] = 0
                        pbVar1 = (byte *)((int)&this_00->CTFWeaponBase::~CTFWeaponBase + 1);
                        *pbVar1 = *pbVar1 | 1;
                    else if(!uCond2)
                    {
                        puVar3[uVar6 * 0x14 + 0x14] = uVar5 + 1;
                        puVar3[uVar6 * 0x14 + local_24 + 1] = 0xdc;
                    }
                }
                else {
                    uVar5 = puVar3[0x7d1];
                    if (uVar5 == 100) {
                        puVar4[1] = 0;
                        pbVar1 = (byte *)((int)&this_00->CTFWeaponBase::~CTFWeaponBase + 1);
                        *pbVar1 = *pbVar1 | 1;
                    }
                    else {
                        *puVar4 = uVar5;
                        puVar3[0x7d1] = uVar5 + 1;
                        puVar4[1] = uVar2;
                        puVar3[(uint)uVar5 * 0x14 + 1] = 0xdc;
                        puVar3[(uint)uVar5 * 0x14 + 0x14] = 1;
                    }
                }
            }
        }
        else {
            *(byte *)&this[0x18].vtable = *(byte *)&this[0x18].vtable | 1;
        }
        this[0x37].vtable = pvVar8;
    }

    pvVar8 = this[8].vtable;
    if (pvVar8 != (vtableCTFWeaponBase *)0x0) {
        *(byte *)&pvVar8->CTFWeaponBase::~CTFWeaponBase =
            *(byte *)&pvVar8->CTFWeaponBase::~CTFWeaponBase | 0x80;
    }
    DispatchUpdateTransmitState((CBaseEntity *)this);
    return;
    */
}

//OFSTATUS: COMPLETE
void COFWeaponBase::Detach() {
    return;
}

//OFSTATUS: COMPLETE
bool COFWeaponBase::CanPerformSecondaryAttack() const
{
    //NOTE: Trimmed code for checking if demo shield
    
    return CBaseCombatWeapon::CanPerformSecondaryAttack();
}

//OFSTATUS: COMPLETE
bool COFWeaponBase::HideAttachmentsAndShowBodygroupsWhenPerformingWeaponIndependentTaunt() const {
    return true;
}

//OFSTATUS: COMPLETE
void COFWeaponBase::Misfire()
{
    CalcIsAttackCritical();
}

//OFSTATUS: INCOMPLETE
void COFWeaponBase::CalcIsAttackCritical()
{
    //This is a very large and fat method.
}

//OFSTATUS: COMPLETE
bool COFWeaponBase::IsFiring() const {
    return false;
}

//OFSTATUS: INCOMPLETE
bool COFWeaponBase::AreRandomCritsEnabled()
{
    //wtf is DAT_0105baec ?
    //I will assume offset 0x30 is an integer pointer


    return false;

    //GetCurrentMatchGroup I think is a method of CTFGameRules.  Is this matchmaking stuff?
    //Also there is a class "ETFMatchGroup" that we dont have created yet
    /*
    int iVar1;
    bool bVar2;
    int local_c;

    if (*(int *)g_pGameRules == 0) {
        bVar2 = *(DAT_0105baec + 0x30) == 0;
    }
    else {
        if (*(char *)(*(int *)g_pGameRules + 0x961) != '\0') {
            bVar2 = true;  
        }
        else
        {
            local_c = GetCurrentMatchGroup();
            iVar1 = GetMatchGroupDescription((ETFMatchGroup *)&local_c);
            if (iVar1 == 0)
                bVar2 = *(DAT_0105baec + 0x30) == 0;
            else
                bVar2 = *(char *)(iVar1 + 0x43) == '\0';
        }
    }
    bVar2 = !bVar2;
    return (uint)bVar2;
    */
}

//OFSTATUS: COMPLETE
float COFWeaponBase::GetReloadSpeedScale() const {
    return 1.0f;
}

//OFSTATUS: COMPLETE
bool COFWeaponBase::CheckReloadMisfire() const {
    return false;
}

//OFSTATUS: COMPLETE
bool COFWeaponBase::CanDrop() const {
    return false;
}

//OFSTATUS: COMPLETE
bool COFWeaponBase::AllowTaunts() const {
    return true;
}