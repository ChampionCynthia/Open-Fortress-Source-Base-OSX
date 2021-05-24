// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFHudTimeStatus
// Author(s): Cherry!
//

#include "cbase.h"
#include "of_hud_timestatus.h"
#include "of_shareddefs.h"
#include "of_gamerules.h"
#include "c_of_player.h"

// OFSTATUS: INCOMPLETE
COFHudTimeStatus::COFHudTimeStatus(Panel *parent, const char *pName) : vgui::EditablePanel(parent, pName)
{
	m_pTimePanelValueLabel = new CExLabel(this, "TimePanelValue", "");
	//m_pTimePanelProgresssBar = NULL;
	m_pOvertimeLabel = NULL;
	m_pOvertimeBG = NULL;
	m_pSuddenDeathLabel = NULL;
	m_pSuddenDeathBG = NULL;
	m_pWaitingForPlayersLabel = NULL;
	m_pWaitingForPlayersBG = NULL;
	m_pSetupLabel = NULL;
	m_pSetupBG = NULL;
	m_pServerTimeLimitLabel = NULL;
	m_pServerTimerLimitLabelBG = NULL;

	ListenForGameEvent("teamplay_update_timer");
	ListenForGameEvent("teamplay_timer_time_added");
	ListenForGameEvent("localplayer_changeteam");
}

// OFSTATUS: COMPLETE
void COFHudTimeStatus::SetTeamBackground()
{
	ScalableImagePanel *pPanel = dynamic_cast<ScalableImagePanel*>(FindChildByName("TimePanelBG"));
	m_pTimePanelBG = pPanel; //field_0x1a0

	if (!pPanel) return;

	if (OFGameRules() && (!OFGameRules()->IsInKothMode() || !OFGameRules()->IsInWaitingForPlayers()))
	{
		switch (GetLocalPlayerTeam())
		{
		case OF_TEAM_RED:
			pPanel->SetImage("../hud/objectives_timepanel_red_bg");
			break;
		case OF_TEAM_BLUE:
			pPanel->SetImage("../hud/objectives_timepanel_blue_bg");
			break;
		}
	}
	else
	{
		switch (field_0x250)
		{
		case OF_TEAM_RED:
			pPanel->SetImage("../hud/objectives_timepanel_red_bg");
			break;
		case OF_TEAM_BLUE:
			pPanel->SetImage("../hud/objectives_timepanel_blue_bg");
			break;
		}
	}
}

// OFSTATUS: INCOMPLETE
void COFHudTimeStatus::FireGameEvent(IGameEvent *event)
{
	if (!V_strcmp(event->GetName(), "teamplay_update_timer"))
	{
		if (OFGameRules() && OFGameRules()->IsInKothMode())
		{
			InvalidateLayout(false, true);
		}
		SetExtraTimePanels();
		return;
	}

	if (!V_strcmp(event->GetName(), "teamplay_timer_time_added"))
	{
		int iTimer = event->GetInt();
		int iSecondsAdded = event->GetInt();

		if (m_iTimerIndex == iTimer)
		{
			if (iSecondsAdded != 0 && C_OFPlayer::GetLocalOFPlayer())
			{
				// field_0x244 = m_flDeltaLifetime
				//(&this->field_0x1d4)[iVar4 * 2] = (float)this->field_0x244 + *(float *)(*(int *)PTR__gpGlobals_00f8a098 + 0xc);
				(&m_DeltaTable[field_0x1cc])->m_flDeathTime = m_flDeltaLifetime + gpGlobals->curtime;
				//(&this->field_0x1d0)[field_0x1cc] = iSecondsAdded;
				(&m_DeltaTable[field_0x1cc])->m_iSeconds = iSecondsAdded;

				//int iVar4 = field_0x1cc;
				//this->field_0x1cc = iVar4 + 1 + ((iVar4 + 1) / 10) * -10;
				field_0x1cc++;
				field_0x1cc %= DELTATABLE_SIZE;
			}
		}
		return;
	}

	if (!V_strcmp(event->GetName(), "localplayer_changeteam"))
	{
		SetTeamBackground();
		return;
	}
}

// OFSTATUS: INCOMPLETE
void COFHudTimeStatus::SetExtraTimePanels()
{
	if (!OFGameRules()) return;

	CTeamRoundTimer *pTimer = dynamic_cast<CTeamRoundTimer*>(cl_entitylist->GetBaseEntity(m_iTimerIndex));

	if (pTimer && pTimer->IsStopWatchTimer())
	{
		
	}

	//if (field_0x1b8)
	//{}
}

// OFSTATUS: INCOMPLETE
void COFHudTimeStatus::ApplySchemeSettings(IScheme *pScheme)
{
	LoadControlSettings("resource/UI/HudObjectiveTimePanel.res");

	//m_pTimePanelProgresssBar = dynamic_cast<COFProgressBar*>(FindChildByName("TimePanelProgressBar")); //field_0x19c

	m_pOvertimeLabel = dynamic_cast<CExLabel*>(FindChildByName("OvertimeLabel")); //field_0x1ac

	m_pOvertimeBG = FindChildByName("OvertimeBG"); //field_0x1b0 

	m_pSuddenDeathLabel = dynamic_cast<CExLabel*>(FindChildByName("SuddenDeathLabel")); //field_0x1c4

	m_pSuddenDeathBG = FindChildByName("SuddenDeathBG"); //field_0x1c8

	m_pWaitingForPlayersLabel = dynamic_cast<CExLabel*>(FindChildByName("WaitingForPlayersLabel")); //field_0x1a4 

	m_pWaitingForPlayersBG = FindChildByName("WaitingForPlayersBG"); //field_0x1a8

	m_pSetupLabel = dynamic_cast<CExLabel*>(FindChildByName("SetupLabel")); //field_0x1b4

	m_pSetupBG = FindChildByName("SetupBG"); //field_0x1b8

	m_pTimePanelBG = dynamic_cast<ScalableImagePanel*>(FindChildByName("TimePanelBG")); //field_0x1a0

	SetTeamBackground();

	m_pServerTimeLimitLabel = dynamic_cast<CExLabel*>(FindChildByName("ServerTimeLimitLabel")); //field_0x1bc

	m_pServerTimerLimitLabelBG = FindChildByName("ServerTimerLimitLabelBG"); //field_0x1c0

	//field_0x18c = 0;
	//field_0x190 = 0;

	SetExtraTimePanels();
	BaseClass::ApplySchemeSettings(pScheme);
}