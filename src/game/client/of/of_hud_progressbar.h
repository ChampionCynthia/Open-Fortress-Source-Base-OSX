// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CTFProgressBar
// Author(s): Cherry!
//

#pragma once

#include <vgui_controls/ImagePanel.h>

class COFProgressBar : public vgui::ImagePanel
{
public:
	DECLARE_CLASS_SIMPLE(COFProgressBar, vgui::ImagePanel);

	COFProgressBar(Panel *parent, const char *pName);
	void Paint();
	void SetRemainingTime(float fRemainingTime) { m_flRemainingTimePercentage = fRemainingTime; }

private:

	float m_flRemainingTimePercentage;
	int m_iTextureID; // field_0x184

	CPanelAnimationVar(float, m_flPercentWarning, "percent_warning", "0.75");
	CPanelAnimationVar(Color, m_ColorWarning, "color_warning", "TimerProgress.Warning");
	CPanelAnimationVar(Color, m_ColorInActive, "color_inactive", "TimerProgress.InActive");
	CPanelAnimationVar(Color, m_ColorActive, "color_active", "TimerProgress.Active");

};