// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CCaptureZone
// Author(s): Cherry!
//

#include "cbase.h"
#include "of_capturezone.h"
#include "of_flag.h"
#include "of_team.h"
#include "of_gamerules.h"

IMPLEMENT_AUTO_LIST(ICaptureZoneAutoList);

BEGIN_DATADESC(CCaptureZone)
// Touch functions
DEFINE_FUNCTION(CCaptureZoneShim::Touch),

// Keyfields
//DEFINE_KEYFIELD(m_nCapturePoint, FIELD_INTEGER, "capturepoint"), // unused?
//DEFINE_KEYFIELD(m_flCaptureDelay, FIELD_FLOAT, "capture_delay"), // player destruction
//DEFINE_KEYFIELD(m_flCaptureDelayOffset, FIELD_FLOAT, "capture_delay_offset"), // player destruction
//DEFINE_KEYFIELD(m_bShouldBlock, FIELD_BOOL, "shouldBlock"), // player destruction

// Inputs

// Outputs
DEFINE_OUTPUT(m_outputOnCapture, "OnCapture"), // 0x49C
DEFINE_OUTPUT(m_OnCapTeam1, "OnCapTeam1"), // 0x4B4
DEFINE_OUTPUT(m_OnCapTeam2, "OnCapTeam2"), // 0x4CC

END_DATADESC();

LINK_ENTITY_TO_CLASS(func_capturezone, CCaptureZone);

// OFSTATUS: INCOMPLETE
CCaptureZone::CCaptureZone()
{
}

// OFSTATUS: INCOMPLETE
CCaptureZone::~CCaptureZone()
{
}

// OFSTATUS: COMPLETE
void CCaptureZone::Spawn()
{
	BaseClass::InitTrigger();
	
	SetTouch(&CCaptureZoneShim::Touch);

	if (m_bDisabled) SetDisabled(true);

	field_0x514 = -1.0;
	AddSpawnFlags(SF_TRIGGER_ALLOW_ALL);
}

// OFSTATUS: COMPLETE
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
		SetTouch(&CCaptureZoneShim::Touch);
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
void CCaptureZone::ShimTouch(CBaseEntity *pOther)
{
	if (pOther)
	{
		COFPlayer *pPlayer = dynamic_cast<COFPlayer*>(pOther);

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

	if (!pPlayer->HasItem())
	{
		//puVar2 = PTR__g_pGameRules_00e340a8;
		//cVar4 = CTFGameRules::CanFlagBeCaptured(*(CTFGameRules **)PTR__g_pGameRules_00e340a8, param_1);
		if (!OFGameRules()->CanFlagBeCaptured(pPlayer))
		{
			//ClientPrint((CBasePlayer *)param_1, 4, "#TF_CTF_Cannot_Capture", (char *)0x0, (char *)0x0,(char *)0x0, (char *)0x0);
			ClientPrint(pPlayer, 4, "#TF_CTF_Cannot_Capture");
		}
		return;
	}

	COFItem *pItem = pPlayer->GetItem();
	if (pItem->GetItemID() != OF_ITEM_FLAG || !OFGameRules()->CanFlagBeCaptured(pPlayer))
	{
		//ClientPrint((CBasePlayer *)param_1, 4, "#TF_CTF_Cannot_Capture", (char *)0x0, (char *)0x0,(char *)0x0, (char *)0x0);
		ClientPrint(pPlayer, 4, "#TF_CTF_Cannot_Capture");
		return;
	}

	CCaptureFlag *pFlag = dynamic_cast<CCaptureFlag*>(pItem);
	if (!pFlag) return;

	//if (pFlag->GetFlagType() == TF_FLAGTYPE_PLAYERDESTRUCTION)

	if (pFlag->IsCaptured() != false) return;

	pFlag->Capture(pPlayer, 0); // the second param is m_nCapturePoint though its unused i think

	m_outputOnCapture.FireOutput(this, this, 0.0);

	switch (pPlayer->GetTeamNumber())
	{
	case OF_TEAM_RED:
		m_OnCapTeam1.FireOutput(this, this, 0.0);
		break;
	case OF_TEAM_BLUE:
		m_OnCapTeam2.FireOutput(this, this, 0.0);
		break;
	}

	IGameEvent *pEvent = gameeventmanager->CreateEvent("ctf_flag_captured");
	if (pEvent)
	{
		int iTeamNumber = pPlayer->GetTeamNumber();
		COFTeam *pTeam = pPlayer->GetOFTeam();

		pEvent->SetInt("capping_team", iTeamNumber);
		pEvent->SetInt("capping_team_score", pTeam->GetFlagCaptures());
		pEvent->SetInt("capper", pPlayer->GetUserID());
		pEvent->SetInt("priority", 9);
		gameeventmanager->FireEvent(pEvent);
	}
}

// OFSTATUS: COMPLETE
int CCaptureZone::UpdateTransmitState()
{
	return SetTransmitState(FL_EDICT_ALWAYS);
}

// OFSTATUS: COMPLETE
void CCaptureZone::InputEnable()
{
	SetDisabled(false);
}

// OFSTATUS: COMPLETE
void CCaptureZone::InputDisable()
{
	SetDisabled(true);
}