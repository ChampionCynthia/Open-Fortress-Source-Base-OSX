// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFHudTimeStatus
// Author(s): Cherry!
//

#pragma once

#include "GameEventListener.h"
#include "hudelement.h"
#include "vgui/of_controls.h"
#include "IconPanel.h"

#define DELTATABLE_SIZE 10

typedef struct
{
	float m_flDeathTime;
	int m_iSeconds;
} delta_table_t;

class COFHudTimeStatus : public vgui::EditablePanel, public CGameEventListener
{
public:
	DECLARE_CLASS_SIMPLE(COFHudTimeStatus, vgui::EditablePanel);

	COFHudTimeStatus(Panel *parent, const char *name);

	virtual void SetTeamBackground();
	virtual void FireGameEvent(IGameEvent *event);
	virtual void SetExtraTimePanels();
	virtual void CheckClockLabelLength(COFLabel *pLabel, Panel *pPanel);
	virtual void Reset();
	virtual void OnThink();
	virtual void Paint();
	virtual void SetTimerIndex(int iTimerIndex);
	virtual int GetTimerIndex() { return m_iTimerIndex; }
	virtual void ApplySchemeSettings(IScheme *pScheme);

private:

	COFLabel *m_pTimePanelValueLabel;
	//COFProgressBar *m_pTimePanelProgresssBar;
	COFLabel *m_pOvertimeLabel;
	Panel *m_pOvertimeBG;
	COFLabel *m_pSuddenDeathLabel;
	Panel *m_pSuddenDeathBG;
	COFLabel *m_pWaitingForPlayersLabel;
	Panel *m_pWaitingForPlayersBG;
	COFLabel *m_pSetupLabel;
	Panel *m_pSetupBG;
	COFLabel *m_pServerTimerLimitLabel;
	Panel *m_pServerTimerLimitLabelBG;

	ScalableImagePanel *m_pTimePanelBG;

	CPanelAnimationVarAliasType(float, m_flDeltaItemStartPos, "delta_item_start_y", "100", "proportional_float");
	CPanelAnimationVarAliasType(float, m_flDeltaItemEndPos, "delta_item_end_y", "0", "proportional_float");
	CPanelAnimationVarAliasType(float, m_flDeltaItemX, "delta_item_x", "0", "proportional_float");
	CPanelAnimationVar(Color, m_DeltaPositiveColor, "PositiveColor", "0 255 0 255"); // field_0x238 + 1
	CPanelAnimationVar(Color, m_DeltaNegativeColor, "NegativeColor", "255 0 0 255"); // field_0x23c + 2
	CPanelAnimationVar(float, m_flDeltaLifetime, "delta_lifetime", "2.0");
	CPanelAnimationVar(vgui::HFont, m_hDeltaItemFont, "delta_item_font", "Default");

	int field_0x250;
	int m_iTimerIndex; //field_0x190;

	delta_table_t m_DeltaTable[DELTATABLE_SIZE];
	int field_0x1cc;

	float field_0x18c;

	bool field_0x254;
	bool field_0x255;
};