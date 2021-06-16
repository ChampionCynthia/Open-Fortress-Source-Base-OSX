// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: CExButton implementation, currently a placeholder that acts the same as vgui::Button
// Author(s): Ms, Cherry!
//
#pragma once

#include "vgui_controls/Button.h"

class COFButton : public vgui::Button
{
public:
	DECLARE_CLASS_SIMPLE(COFButton, vgui::Button);

	COFButton(Panel* parent, const char* panelName, const char* text);
	COFButton(Panel* parent, const char* panelName, const wchar_t* text);

	void ApplySettings(KeyValues *pKey);
	void SetFontStr(const char *pchar);
	void SetColorStr(const char *pchar);
	vgui::IBorder *GetBorder(bool depressed, bool armed, bool selected, bool keyfocus);

private:

	char m_szFont[64];
	char m_szColor[64];
	vgui::IBorder *m_pBorderDefault;
	vgui::IBorder *m_pBorderArmed;
	vgui::IBorder *m_pBorderDisabled;
	vgui::IBorder *m_pBorderSelected;
};