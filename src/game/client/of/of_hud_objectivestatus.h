// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFHudObjectiveStatus
// Author(s): Cherry!
//

#include "hud_controlpointicons.h"
#include "c_of_player.h"
#include "of_shareddefs.h"

class COFHudObjectiveStatus : public CHudElement, public vgui::EditablePanel
{
public:
	DECLARE_CLASS_SIMPLE(COFHudObjectiveStatus, vgui::EditablePanel);

	COFHudObjectiveStatus(const char *pElementName);
	void ApplySchemeSettings(IScheme *pScheme);
	void Reset();
	CControlPointProgressBar *GetControlPointProgressBar();

private:

	CHudControlPointIcons *m_pPointIconsPanel;
	CControlPointProgressBar *m_pPointProgressBarPanel;
};