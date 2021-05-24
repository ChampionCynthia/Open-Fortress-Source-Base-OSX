// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFHudObjectiveStatus
// Author(s): Cherry!
//

#include "cbase.h"
#include "of_hud_objectivestatus.h"
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