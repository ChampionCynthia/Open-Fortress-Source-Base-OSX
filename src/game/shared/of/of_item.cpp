// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFItem
// Author(s): Cherry!
//

#include "cbase.h"
#include "of_item.h"
#include "of_shareddefs.h"

#ifdef CLIENT_DLL
	#include "haptics/ihaptics.h"
	#include "c_of_player.h"
#else
	#include "of_player.h"
#endif

IMPLEMENT_NETWORKCLASS_ALIASED(OFItem, DT_OFItem)

BEGIN_NETWORK_TABLE(COFItem, DT_OFItem)
END_NETWORK_TABLE()

// OFSTATUS: COMPLETE
int COFItem::GetItemID() const
{
	return OF_ITEM_UNDEFINDED;
}

// OFSTATUS: COMPLETE
void COFItem::Pickup(COFPlayer *pPlayer, bool bNoDraw)
{
	SetOwnerEntity(pPlayer);
	SetParent(pPlayer, 0);
	SetLocalOrigin(vec3_origin);
	SetLocalAngles(vec3_angle);

	if (bNoDraw)
	{
		AddEffects(EF_NODRAW);
	}

	pPlayer->SetItem(this);

	#ifdef CLIENT_DLL
	
	if (pPlayer->IsLocalPlayer())
	{
		haptics->ProcessHapticEvent(2, "Game", "ctf_item_start");
	}

	#endif
}

// OFSTATUS: COMPLETE
// those other parameters may go unused?
void COFItem::Drop(COFPlayer *pPlayer, bool bNoDraw, bool param_3, bool param_4)
{
	pPlayer->SetItem(NULL);

	if (bNoDraw == false)
	{
		RemoveEffects(EF_NODRAW);
	}

	#ifdef CLIENT_DLL

	if (pPlayer->IsLocalPlayer())
	{
		haptics->ProcessHapticEvent(2, "Game", "ctf_item_stop");
	}

	#endif

	SetParent(NULL,0);
	SetOwnerEntity(NULL);
}

#ifdef CLIENT_DLL

// OFSTATUS: COMPLETE
bool COFItem::ShouldDraw()
{
	if (ToOFPlayer(GetMoveParent())->InFirstPersonView())
	{
		return false;
	}

	return BaseClass::ShouldDraw();
}

// OFSTATUS: COMPLETE
ShadowType_t COFItem::ShadowCastType()
{
	if (ToOFPlayer(GetMoveParent())->ShouldDrawThisPlayer())
	{
		return SHADOWS_NONE;
	}

	return BaseClass::ShadowCastType();
}

// OFSTATUS: COMPLETE
bool COFItem::ShouldHideGlowEffect()
{
	return false;
}

#endif