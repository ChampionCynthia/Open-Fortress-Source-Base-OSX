// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFImagePanel
// Author(s): Cherry!
//

#pragma once

#include "GameEventListener.h"
#include "of_shareddefs.h"
#include "vgui_controls/ScalableImagePanel.h"

class COFImagePanel : public vgui::ScalableImagePanel, public CGameEventListener
{
public:
	DECLARE_CLASS_SIMPLE(COFImagePanel, vgui::ScalableImagePanel);

	COFImagePanel(Panel* parent, const char* panelName);
	void ApplySettings(KeyValues *pKey);
	void UpdateBGImage();
	void FireGameEvent(IGameEvent *pEvent);

private:

	char m_szTeamImage[OF_TEAM_COUNT][128];
	int m_iPlayerTeam;
};