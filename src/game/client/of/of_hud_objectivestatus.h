// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFHudObjectiveStatus
// Author(s): Cherry!
//

#include "hud_controlpointicons.h"
#include "of_hud_timestatus.h"
#include "c_of_player.h"

class COFHudObjectiveStatus : public CHudElement, public vgui::EditablePanel
{
public:
	DECLARE_CLASS_SIMPLE(COFHudObjectiveStatus, vgui::EditablePanel);

	COFHudObjectiveStatus(const char *pElementName);
	void Think();
	void ApplySchemeSettings(IScheme *pScheme);
	void Reset();
	CControlPointProgressBar *GetControlPointProgressBar();

private:

	COFHudTimeStatus *m_pTimePanel;
	CHudControlPointIcons *m_pPointIconsPanel;
	CControlPointProgressBar *m_pPointProgressBarPanel;
};