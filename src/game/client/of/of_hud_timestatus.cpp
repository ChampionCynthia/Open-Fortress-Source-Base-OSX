// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFHudTimeStatus
// Author(s): Cherry!
//

#include "cbase.h"
#include "of_hud_timestatus.h"
#include "of_gamerules.h"
#include "of_clientmode.h"
#include "c_of_player.h"
#include <vgui_controls/AnimationController.h>
#include "vgui_controls/ScalableImagePanel.h"
#include "vgui_controls/EditablePanel.h"
#include "vgui/ISurface.h"
#include "vgui/ILocalize.h"

ConVar tf_hud_show_servertimelimit("tf_hud_show_servertimelimit", "0", FCVAR_CLIENTDLL, "Display time left before the current map ends.");
extern ConVar tf_arena_round_time;

// OFSTATUS: INCOMPLETE
COFHudTimeStatus::COFHudTimeStatus(Panel *parent, const char *pName) : vgui::EditablePanel(parent, pName)
{
	m_pTimePanelValueLabel = new COFLabel(this, "TimePanelValue", "");
	//m_pTimePanelProgressBar = NULL;
	m_pOvertimeLabel = NULL;
	m_pOvertimeBG = NULL;
	m_pSuddenDeathLabel = NULL;
	m_pSuddenDeathBG = NULL;
	m_pWaitingForPlayersLabel = NULL;
	m_pWaitingForPlayersBG = NULL;
	m_pSetupLabel = NULL;
	m_pSetupBG = NULL;
	m_pServerTimerLimitLabel = NULL;
	m_pServerTimerLimitLabelBG = NULL;

	ListenForGameEvent("teamplay_update_timer");
	ListenForGameEvent("teamplay_timer_time_added");
	ListenForGameEvent("localplayer_changeteam");

	field_0x254 = 0;
	field_0x255 = false;
	m_iTimerIndex = 0;
	field_0x1cc = 0;

	for (int i = 0; i < DELTATABLE_SIZE; i++)
	{
		m_DeltaTable[i].m_flDeathTime = 0.0;
	}
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

// OFSTATUS: COMPLETE
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
		int iTimer = event->GetInt("timer", -1);
		int iSecondsAdded = event->GetInt("seconds_added", 0);

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
		if (m_pTimePanelBG) m_pTimePanelBG->SetVisible(false);
		//if (m_pTimePanelProgressBar) m_pTimePanelProgressBar->SetVisible(false);
		if (m_pWaitingForPlayersLabel) m_pWaitingForPlayersLabel->SetVisible(false);
		if (m_pWaitingForPlayersBG) m_pWaitingForPlayersBG->SetVisible(false);
		if (m_pOvertimeLabel) m_pOvertimeLabel->SetVisible(false);
		if (m_pOvertimeBG) m_pOvertimeBG->SetVisible(false);
		if (m_pSetupLabel) m_pSetupLabel->SetVisible(false);
		if (m_pSetupBG) m_pSetupBG->SetVisible(false);
		if (m_pSuddenDeathLabel) m_pSuddenDeathLabel->SetVisible(false);
		if (m_pSuddenDeathBG) m_pSuddenDeathBG->SetVisible(false);
		if (m_pServerTimerLimitLabel) m_pServerTimerLimitLabel->SetVisible(false);
		if (m_pServerTimerLimitLabelBG) m_pServerTimerLimitLabelBG->SetVisible(false);

		return;
	}

	bool bInSetup = OFGameRules()->InSetup(); //0x35 
	bool bWaitingForPlayers = OFGameRules()->IsInWaitingForPlayers(); //0x40

	if (m_pSetupLabel && m_pSetupBG)
	{
		m_pSetupLabel->SetVisible(bInSetup);
		m_pSetupBG->SetVisible(bInSetup);
	}

	if (m_pSuddenDeathLabel && m_pSuddenDeathBG)
	{
		bool bIsInArenaMode = false;

		if (OFGameRules()->State_Get() == GR_STATE_STALEMATE)
		{
			bIsInArenaMode = OFGameRules()->IsInArenaMode();
		}

		bool bSDLabelVisible = m_pSuddenDeathLabel->IsVisible();
		if ((!bSDLabelVisible && bIsInArenaMode) || (bSDLabelVisible && !bIsInArenaMode))
		{
			if (bIsInArenaMode)
			{
				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence(this, "SuddenDeathLabelPulseRed");
			}
			else
			{
				g_pClientMode->GetViewportAnimationController()->StopAnimationSequence(this, "SuddenDeathLabelPulseRed");
			}
		}

		m_pSuddenDeathBG->SetVisible(bSDLabelVisible);
		m_pSuddenDeathLabel->SetVisible(bSDLabelVisible);
	}

	if (m_pOvertimeBG && m_pOvertimeLabel)
	{

		bool bOverTime = OFGameRules()->InOvertime(); // 0xd
		bool bCheck = false;

		if (OFGameRules()->IsInKothMode())
		{
			if (bOverTime)
			{
				float fRemainingTime = pTimer->GetTimeRemaining();
				if (fRemainingTime <= 0)
				{
					bCheck = true;
					field_0x255 = true;
				}
			}
			else
			{
				if (field_0x255)
				{
					float fRemainingTime = pTimer->GetTimeRemaining();
					if (fRemainingTime > 0)
					{
						bCheck = true;
						field_0x255 = false;
					}
				}
			}
		}

		if (bCheck)
		{
			if (m_pSuddenDeathBG && m_pSuddenDeathLabel)
			{
				m_pSuddenDeathBG->SetVisible(false);
				m_pSuddenDeathLabel->SetVisible(false);
			}

			if (!m_pOvertimeLabel->IsVisible())
			{
				m_pOvertimeBG->SetVisible(true);
				m_pOvertimeLabel->SetVisible(true);

				g_pClientMode->GetViewportAnimationController()->StartAnimationSequence(this, "OvertimeLabelPulseRed");
				CheckClockLabelLength(m_pOvertimeLabel, m_pOvertimeBG);
			}
		}
		else
		{
			m_pOvertimeBG->SetVisible(false);
			m_pOvertimeLabel->SetVisible(false);
		
			g_pClientMode->GetViewportAnimationController()->StopAnimationSequence(this, "OvertimeLabelPulseRed");
		}
	}

	if (m_pWaitingForPlayersBG && m_pWaitingForPlayersLabel)
	{
		m_pWaitingForPlayersBG->SetVisible(bWaitingForPlayers);
		m_pWaitingForPlayersLabel->SetVisible(bWaitingForPlayers);

		if (bWaitingForPlayers)
		{
			if (m_pSetupBG && m_pSetupLabel)
			{
				m_pSetupBG->SetVisible(false);
				m_pSetupLabel->SetVisible(false);
			}
			CheckClockLabelLength(m_pWaitingForPlayersLabel, m_pWaitingForPlayersBG);
		}
	}

	if (m_pServerTimerLimitLabel && m_pServerTimerLimitLabelBG)
	{
		bool bShowServerTimeLimit = false;
		if (tf_hud_show_servertimelimit.GetBool() && !bWaitingForPlayers && !bInSetup)
		{
			bShowServerTimeLimit = true;
		}

		m_pServerTimerLimitLabel->SetVisible(bShowServerTimeLimit);
		m_pServerTimerLimitLabelBG->SetVisible(bShowServerTimeLimit);
	}
}

// OFSTATUS: COMPLETE
void COFHudTimeStatus::CheckClockLabelLength(COFLabel *pLabel, Panel *pPanel)
{
	if (!pLabel || !pPanel) return;

	int wideContent, tallContent;
	pLabel->GetContentSize(wideContent, tallContent);

	int iLabelWide = pLabel->GetWide();

	if (iLabelWide < wideContent)
	{
		int x, y, wide, tall;
		pLabel->GetBounds(x, y, wide, tall);

		pLabel->SetBounds((wide * 0.5) + x - (wideContent * 0.5), y, wideContent, tall);
	}

	int iWideLabel = pLabel->GetWide();
	int iWidePanel = pPanel->GetWide();

	if (iWidePanel < iWideLabel)
	{
		pPanel->SetVisible(false);
	}
}

// OFSTATUS: COMPLETE
void COFHudTimeStatus::Reset()
{
	field_0x18c = gpGlobals->curtime + 0.05;
	m_iTimerIndex = 0;

	field_0x1cc = 0;
	for (int i = 0; i < DELTATABLE_SIZE; i++)
	{
		m_DeltaTable[i].m_flDeathTime = 0.0;
	}
}

// OFSTATUS: INCOMPLETE
void COFHudTimeStatus::OnThink()
{
	if (field_0x18c < gpGlobals->curtime)
	{
		CTeamRoundTimer *pTimer = dynamic_cast<CTeamRoundTimer*>(cl_entitylist->GetBaseEntity(m_iTimerIndex));
		
		char textTimePanel[256];

		if (OFGameRules() && field_0x254 != OFGameRules()->IsInKothMode())
		{
			field_0x254 = OFGameRules()->IsInKothMode();
			InvalidateLayout(false, true);
		}

		if (pTimer)
		{
			int iTimerMaxLength = pTimer->GetTimerMaxLength();
			float flTimeRemaining = pTimer->GetTimeRemaining();
			int iTimePassed = flTimeRemaining;

			// 0x565
			if (!pTimer->ShowTimeRemaining())
			{
				iTimePassed = iTimerMaxLength - flTimeRemaining;
			}

			if (m_pTimePanelValueLabel && m_pTimePanelValueLabel->IsVisible())
			{
				int iVar13 = 0;

				if (iTimePassed < 1)
				{
					iTimePassed = 0;

					if (OFGameRules()->IsInKothMode())
					{
						SetExtraTimePanels();
					}
				}
				else
				{
					iVar13 = iTimePassed / 60;
					iTimePassed %= 60;
				}

				V_snprintf(textTimePanel, sizeof(textTimePanel), "%d:%02d", iVar13, iTimePassed);
				m_pTimePanelValueLabel->SetText(textTimePanel);
			}

			/*
			if (m_pTimePanelProgressBar && m_pTimePanelProgressBar->IsVisible())
			{
				if (iTimerMaxLength)
				{
					m_pTimePanelProgressBar->field_0x180 = (iTimerMaxLength - flTimeRemaining) / iTimerMaxLength;
				}
				else
				{
					m_pTimePanelProgressBar->field_0x180 = 0;
				}
			}
			*/

			if (m_pServerTimerLimitLabel && m_pServerTimerLimitLabelBG)
			{
				bool bShowServerTimeLimit = (tf_hud_show_servertimelimit.GetBool() != 0 && !OFGameRules()->InSetup() && !OFGameRules()->IsInWaitingForPlayers() && mp_timelimit.GetInt() && pTimer->IsRoundMaxTimerSet());

				if (m_pServerTimerLimitLabel->IsVisible() != bShowServerTimeLimit)
				{
					m_pServerTimerLimitLabel->SetVisible(bShowServerTimeLimit);
				}

				if (m_pServerTimerLimitLabelBG->IsVisible() != bShowServerTimeLimit)
				{
					m_pServerTimerLimitLabelBG->SetVisible(bShowServerTimeLimit);
				}

				if (bShowServerTimeLimit)
				{
					// no limit set
					if (mp_timelimit.GetInt() == 0)
					{
						SetDialogVariable("servertimeleft", g_pVGuiLocalize->Find("#TF_HUD_ServerNoTimeLimit"));
						return;
					}

					// time limit set
					int iTimeLeft = OFGameRules()->GetTimeLeft();
					if (OFGameRules() && 0 < iTimeLeft && iTimeLeft != 0)
					{
						wchar_t textServerTime[512];
						wchar_t textHoursLeft[128]; // local_214
						wchar_t textMinutesLeft[128]; // local_414
						wchar_t textSecondsLeft[128]; // local_614

						int iHoursLeft = iTimeLeft / 3600;
						int iMinutesLeft = (iTimeLeft % 3600) / 60;
						int iSecondsLeft = iTimeLeft % 60;

						_snwprintf(textHoursLeft, sizeof(textHoursLeft), L"%i", iHoursLeft);
						_snwprintf(textMinutesLeft, sizeof(textMinutesLeft), L"%i", iMinutesLeft);
						_snwprintf(textSecondsLeft, sizeof(textSecondsLeft), L"%i", iSecondsLeft);

						// no hours left
						if (iHoursLeft == 0)
						{
							g_pVGuiLocalize->ConstructString(textServerTime, sizeof(textServerTime), g_pVGuiLocalize->Find("#TF_HUD_ServerTimeLeftNoHours"), 2, textMinutesLeft, textSecondsLeft);
							SetDialogVariable("servertimeleft", textServerTime);
							return;
						}

						g_pVGuiLocalize->ConstructString(textServerTime, sizeof(textServerTime), g_pVGuiLocalize->Find("#TF_HUD_ServerTimeLeft"), 3, textHoursLeft, textMinutesLeft, textSecondsLeft);
						SetDialogVariable("servertimeleft", textServerTime);
						return;
					}

					// server time limit reached
					SetDialogVariable("servertimeleft", g_pVGuiLocalize->Find("#TF_HUD_ServerChangeOnRoundEnd"));
					return;
				}
			}
		}
		field_0x18c = gpGlobals->curtime + 0.1;
	}

	/*
	CHudArenaPlayerCount *pArenaElement = gHUD.FindElement("CHudArenaPlayerCount");
	if (OFGameRules()->IsInArenaMode() && tf_arena_round_time.GetInt() > 0 && pArenaElement)
	{
		int x, y;
		GetPos(x, y);

		if (pArenaElement->IsVisible())
		{
			int ArenaX, ArenaY, ArenaWide, ArenaTall;
			pArena->ElementGetBound(ArenaX, ArenaY, ArenaWide, ArenaTall);
			SetPos(x,ScreenHeight() * 0.025 + (ArenaTall + ArenaY));
		}
		else
		{
			SetPos(x, 0);
		}
	}
	*/
}

void COFHudTimeStatus::Paint()
{
	BaseClass::Paint();

	for (int i = 0; i < DELTATABLE_SIZE; i++)
	{
		if (gpGlobals->curtime < m_DeltaTable[i].m_flDeathTime)
		{
			Color pColor = m_DeltaPositiveColor;
			if (m_DeltaTable[i].m_iSeconds < 1)
			{
				pColor = m_DeltaNegativeColor;
			}

			float fVar15 = (m_DeltaTable[i].m_flDeathTime - gpGlobals->curtime) / m_flDeltaLifetime;

			if (fVar15 < 0.5)
			{
				pColor[3] = int(fVar15 * 510.0);
			}

			vgui::surface()->DrawSetTextFont(m_hDeltaItemFont); // field_0x24c
			vgui::surface()->DrawSetTextColor(pColor);
			vgui::surface()->DrawSetTextPos(m_flDeltaItemX, int((m_flDeltaItemStartPos - m_flDeltaItemEndPos) * fVar15 + m_flDeltaItemEndPos)); // field_0x234
			//m_flDeltaItemStartPos - m_flDeltaItemEndPos

			wchar_t timeChangeText[20];
			int iCalc = -m_DeltaTable[i].m_iSeconds;
			if (0 < m_DeltaTable[i].m_iSeconds) iCalc = m_DeltaTable[i].m_iSeconds;
			int iMinutes = iCalc / 60;
			int iSeconds = iCalc % 60;


			if (0 < m_DeltaTable[i].m_iSeconds)
			{
				// fun fact: when i was trying to figure out why it kept pointing me to DAT_00d90ae4
				// i tilted my head to the side thinking "haha that'll solve it," but it seriously did as i then seen the characters - cherry
				V_swprintf_safe(timeChangeText, L"+%d:%02d", iMinutes, iSeconds);
			}
			else
			{
				V_swprintf_safe(timeChangeText, L"-%d:%02d", iMinutes, iSeconds);
			}

			vgui::surface()->DrawPrintText(timeChangeText, wcslen(timeChangeText), FONT_DRAW_NONADDITIVE);
		}
	}
}

void COFHudTimeStatus::SetTimerIndex(int iTimerIndex)
{
	int iIndex = iTimerIndex;
	if (iTimerIndex < 0) iIndex = 0;
	m_iTimerIndex = iIndex;
	SetExtraTimePanels();
}

// OFSTATUS: INCOMPLETE
void COFHudTimeStatus::ApplySchemeSettings(IScheme *pScheme)
{
	LoadControlSettings("resource/UI/HudObjectiveTimePanel.res");

	//m_pTimePanelProgressBar = dynamic_cast<COFProgressBar*>(FindChildByName("TimePanelProgressBar")); //field_0x19c

	m_pOvertimeLabel = dynamic_cast<COFLabel*>(FindChildByName("OvertimeLabel")); //field_0x1ac

	m_pOvertimeBG = dynamic_cast<COFImagePanel*>(FindChildByName("OvertimeBG")); //field_0x1b0 

	m_pSuddenDeathLabel = dynamic_cast<COFLabel*>(FindChildByName("SuddenDeathLabel")); //field_0x1c4

	m_pSuddenDeathBG = dynamic_cast<COFImagePanel*>(FindChildByName("SuddenDeathBG")); //field_0x1c8

	m_pWaitingForPlayersLabel = dynamic_cast<COFLabel*>(FindChildByName("WaitingForPlayersLabel")); //field_0x1a4 

	m_pWaitingForPlayersBG = dynamic_cast<COFImagePanel*>(FindChildByName("WaitingForPlayersBG")); //field_0x1a8

	m_pSetupLabel = dynamic_cast<COFLabel*>(FindChildByName("SetupLabel")); //field_0x1b4

	m_pSetupBG = dynamic_cast<COFImagePanel*>(FindChildByName("SetupBG")); //field_0x1b8

	m_pTimePanelBG = dynamic_cast<ScalableImagePanel*>(FindChildByName("TimePanelBG")); //field_0x1a0

	SetTeamBackground();

	m_pServerTimerLimitLabel = dynamic_cast<COFLabel*>(FindChildByName("ServerTimeLimitLabel")); //field_0x1bc

	m_pServerTimerLimitLabelBG = FindChildByName("ServerTimerLimitLabelBG"); //field_0x1c0

	field_0x18c = 0;
	m_iTimerIndex = 0; //field_0x190 = 0;

	SetExtraTimePanels();
	BaseClass::ApplySchemeSettings(pScheme);
}