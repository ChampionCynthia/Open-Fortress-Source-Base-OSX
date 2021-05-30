// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFHudObjectiveStatus
// Author(s): Cherry!
//

#include "cbase.h"
#include "of_hud_objectivestatus.h"
#include "of_gamerules.h"
#include "c_of_objectiveresource.h"
#include "spectatorgui.h"
#include "iclientmode.h"

DECLARE_HUDELEMENT(COFHudObjectiveStatus);

// OFSTATUS: INCOMPLETE
COFHudObjectiveStatus::COFHudObjectiveStatus(const char *pElementName) : CHudElement(pElementName), BaseClass(NULL, "HudObjectiveStatus")
{
	vgui::Panel *pParent = g_pClientMode->GetViewport();
	SetParent(pParent);

	m_pTimePanel = new COFHudTimeStatus(this, "ObjectiveStatusTimePanel");
	//m_pFlagStatusPanel = new CTFHudFlagObjectives(this, "ObjectiveStatusFlagPanel");
	m_pPointIconsPanel = NULL;
	m_pPointProgressBarPanel = new CControlPointProgressBar(this);
	// OFTODO: Rename all the escort stuff to payload
	//m_pPayloadPanel = new CTFHudEscort(this, "ObjectiveStatusEscort");
	//m_pMultiplePayloadPanel = new CTFHudMultipleEscort(this, "ObjectiveStatusMultipleEscort");

	SetHiddenBits(0);
	RegisterForRenderGroup("mid");
	RegisterForRenderGroup("commentary");
}

// OFSTATUS: COMPLETE
void COFHudObjectiveStatus::Think()
{
	if (!OFGameRules()) return;

	//SetVisiblePanels();

	// NOTE: this is in CTFHudMatchStatus, but from i can tell it's the meet your match top player count hud,
	// so ill be ignoring it and disecting what i need and placing it here instead - cherry

	if (m_pTimePanel)
	{
		CBasePlayer *pPlayer = CBasePlayer::GetLocalPlayer();
		bool bPass = !(pPlayer && pPlayer->GetObserverMode() == OBS_MODE_FREEZECAM);

		if (bPass)
		{
			CTeamRoundTimer *pTimer = dynamic_cast<CTeamRoundTimer*>(cl_entitylist->GetBaseEntity(m_pTimePanel->GetTimerIndex()));
			// 0x152 = m_bIsDisabled
			if (pTimer && !pTimer->IsDormant() && !pTimer->IsDisabled() && pTimer->ShowInHud())
			{
				bPass = true;
			}
			else
			{
				if (ObjectiveResource())
				{
					int iTimerIndex = ObjectiveResource()->GetTimerToShowInHUD();
					CTeamRoundTimer *pHudTimer = dynamic_cast<CTeamRoundTimer*>(cl_entitylist->GetBaseEntity(iTimerIndex));
					bPass = (pHudTimer && !pHudTimer->IsDormant());
					m_pTimePanel->SetTimerIndex(iTimerIndex);
				}
			}
		}

		if (bPass)
		{
			if (OFGameRules()->IsInKothMode())
			{
				m_pTimePanel->SetVisible(true);
				if (g_pSpectatorGUI) g_pSpectatorGUI->InvalidateLayout();
			}
			else
			{
				if (OFGameRules()->IsInWaitingForPlayers() != m_pTimePanel->IsVisible())
				{
					m_pTimePanel->SetVisible(true);
					if (g_pSpectatorGUI) g_pSpectatorGUI->InvalidateLayout();
				}
			}
		}
		else
		{
			m_pTimePanel->SetVisible(false);
		}
	}
}

void COFHudObjectiveStatus::ApplySchemeSettings(IScheme *pScheme)
{
	LoadControlSettings("resource/UI/HudObjectiveStatus.res");

	if (!m_pPointIconsPanel)
	{
		m_pPointIconsPanel = GET_HUDELEMENT(CHudControlPointIcons);
		m_pPointIconsPanel->SetParent(this);
	}

	if (m_pPointProgressBarPanel)
	{
		m_pPointProgressBarPanel->InvalidateLayout(true, true);
	}

	BaseClass::ApplySchemeSettings(pScheme);
}

// OFSTATUS: COMPLETE
void COFHudObjectiveStatus::Reset()
{
	if (m_pTimePanel)
	{
		m_pTimePanel->Reset();
	}

	/*
	if (m_pFlagStatusPanel)
	{
		m_pFlagStatusPanel->Reset();
	}

	if (m_pPayloadPanel)
	{
		m_pPayloadPanel->Reset();
	}

	if (m_pMultiplePayloadPanel)
	{
		m_pMultiplePayloadPanel->Reset();
	}
	*/

	if (m_pPointProgressBarPanel)
	{
		m_pPointProgressBarPanel->Reset();
	}
}

CControlPointProgressBar *COFHudObjectiveStatus::GetControlPointProgressBar()
{
	return m_pPointProgressBarPanel;
}