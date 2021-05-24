// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFHudTimeStatus
// Author(s): Cherry!
//

#pragma once

#include "hudelement.h"
#include "vgui_controls/ScalableImagePanel.h"
#include "vgui_controls/EditablePanel.h"
#include "vgui/of_controls.h"
#include "IconPanel.h"

#define DELTATABLE_SIZE 10

typedef struct
{
	float m_flDeathTime;
	int m_iSeconds;
} delta_tablet_t;

class COFHudTimeStatus : public vgui::EditablePanel, public CGameEventListener
{
public:
	DECLARE_CLASS_SIMPLE(COFHudTimeStatus, vgui::EditablePanel);

	COFHudTimeStatus(Panel *parent, const char *name);

	virtual void SetTeamBackground();
	virtual void FireGameEvent(IGameEvent *event);
	virtual void SetExtraTimePanels();
	//virtual void CheckClockLabelLength(CExLabel *pLabel, Panel *pPanel);
	//virtual void Reset();
	virtual void ApplySchemeSettings(IScheme *pScheme);

private:

	CExLabel *m_pTimePanelValueLabel;
	//COFProgressBar *m_pTimePanelProgresssBar;
	CExLabel *m_pOvertimeLabel;
	Panel *m_pOvertimeBG;
	CExLabel *m_pSuddenDeathLabel;
	Panel *m_pSuddenDeathBG;
	CExLabel *m_pWaitingForPlayersLabel;
	Panel *m_pWaitingForPlayersBG;
	CExLabel *m_pSetupLabel;
	Panel *m_pSetupBG;
	CExLabel *m_pServerTimeLimitLabel;
	Panel *m_pServerTimerLimitLabelBG;

	ScalableImagePanel *m_pTimePanelBG;

	CPanelAnimationVarAliasType(float, m_flDeltaItemStartPos, "delta_item_start_y", "100", "proportional_float");
	CPanelAnimationVarAliasType(float, m_flDeltaItemEndPos, "delta_item_end_y", "0", "proportional_float");
	CPanelAnimationVarAliasType(float, m_flDeltaItemX, "delta_item_x", "0", "proportional_float");
	CPanelAnimationVar(Color, m_DeltaPositiveColor, "PositiveColor", "0 255 0 255");
	CPanelAnimationVar(Color, m_DeltaNegativeColor, "NegativeColor", "255 0 0 255");
	CPanelAnimationVar(float, m_flDeltaLifetime, "delta_lifetime", "2.0");
	CPanelAnimationVar(vgui::HFont, m_hDeltaItemFont, "delta_item_font", "Default");

	int field_0x250;
	int m_iTimerIndex; //field_0x190;

	delta_tablet_t m_DeltaTable[DELTATABLE_SIZE];
	int field_0x1cc;
};