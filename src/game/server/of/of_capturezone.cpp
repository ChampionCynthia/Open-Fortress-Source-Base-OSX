// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CCaptureZone
// Author(s): Cherry!
//

#include "cbase.h"
#include "of_capturezone.h"
#include "of_gamerules.h"
#include "of_flag.h"
#include "of_shareddefs.h"

IMPLEMENT_AUTO_LIST(ICaptureZoneAutoList);
LINK_ENTITY_TO_CLASS(func_capturezone, CCaptureZone);

// OFSTATUS: INCOMPLETE
CCaptureZone::CCaptureZone()
{
	BaseClass::CBaseTrigger();
}

// OFSTATUS: INCOMPLETE
CCaptureZone::~CCaptureZone()
{
}

// OFSTATUS: INCOMPLETE
void CCaptureZone::Spawn()
{
	BaseClass::InitTrigger();
	
	//SetTouch();

	if (m_bDisabled) SetDisabled(true);

	field_0x514 = -1.0;
	AddSpawnFlags(SF_TRIGGER_ALLOW_ALL);
}

// OFSTATUS: INCOMPLETE
void CCaptureZone::SetDisabled(bool bDisable)
{
	//m_bDisabled = bDisable; // kinda pointless when disable and enable already do this

	if (bDisable)
	{
		BaseClass::Disable();
		SetTouch(NULL);
	}
	else
	{
		BaseClass::Enable();
		//SetTouch();
	}
}

// OFSTATUS: COMPLETE
void CCaptureZone::Activate()
{
	BaseClass::Activate();

	// ignoring this portion
	//if (OFGameRules() && OFGameRules()->GetGameType() == TF_GAMETYPE_PLAYERDESTRUCTION)
	//{
	//}

	SetThink(NULL);
}

// OFSTATUS: COMPLETE
bool CCaptureZone::IsDisabled()
{
	return m_bDisabled;
}

// OFSTATUS: INCOMPLETE
void CCaptureZone::ShimTouch(COFPlayer *pPlayer)
{
	if (pPlayer)
	{
		if (!IsDisabled() && pPlayer->IsPlayer() && pPlayer->HasItem())
		{
			COFItem *pItem = pPlayer->GetItem();
			int iItemID = pItem->GetItemID();

			if (iItemID == OF_ITEM_FLAG)
			{
				CCaptureFlag *pFlag = dynamic_cast<CCaptureFlag*>(pItem);
				if (pFlag && !pFlag->IsCaptured() && GetTeamNumber() != TEAM_UNASSIGNED && pPlayer->GetTeamNumber() != TEAM_UNASSIGNED)
				{
					int iPlayerTeam = pPlayer->GetTeamNumber();
					int iTeam = GetTeamNumber();

					if (iPlayerTeam != iTeam)
					{
						if (pFlag->GetFlagType() != TF_FLAGTYPE_CTF) return;

						if (gpGlobals->curtime <= field_0x514) return;

						//CRecipientFilter::CRecipientFilter((CRecipientFilter *)appuStack52);
						//appuStack52[0] = &PTR_~CSingleUserRecipientFilter_00f2aed8;
						//CRecipientFilter::AddRecipient((CRecipientFilter *)appuStack52, (CBasePlayer *)param_1);
						//OFGameRules()->SendHudNotification(appuStack52, 8, false);

						field_0x514 = gpGlobals->curtime + 5.0;

						//CRecipientFilter::~CRecipientFilter((CRecipientFilter *)appuStack52);

						return;
					}
				}

				if (OFGameRules()->FlagsMayBeCapped())
				{
					Capture(pPlayer);
					return;
				}
			}

		}
	}
}

// OFSTATUS: INCOMPLETE
void CCaptureZone::Capture(COFPlayer *pPlayer)
{
	if (!pPlayer) return;

	if (!pPlayer->IsPlayer()) return;

}