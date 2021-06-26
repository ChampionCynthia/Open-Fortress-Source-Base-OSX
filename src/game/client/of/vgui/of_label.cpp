// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: CExLabel implementation
// Author(s): Ms, Cherry!
//
#include "cbase.h"
#include "of_label.h"

DECLARE_BUILD_FACTORY_DEFAULT_TEXT(COFLabel, COFLabel);

COFLabel::COFLabel(Panel* parent, const char* panelName, const char* text) : BaseClass(parent, panelName, text)
{
	m_szColor[0] = '\0';
}

COFLabel::COFLabel(Panel* parent, const char* panelName, const wchar_t* text) : BaseClass(parent, panelName, text)
{
	m_szColor[0] = '\0';
}

void COFLabel::ApplySettings(KeyValues *pKey)
{
	BaseClass::ApplySettings(pKey);

	//vgui::IScheme *pScheme = g_pVGuiSchemeManager->GetIScheme(GetScheme());
	//Color pColor = pScheme->GetColor(pKey->GetString("fgcolor", "Label.TextColor"), Color(255, 255, 255, 255));
	//V_snprintf(m_szColor, sizeof(m_szColor), "%d %d %d %d", pColor.r(), pColor.g(), pColor.b(), pColor.a());
	//SetFgColor(pColor);
	SetColorStr(pKey->GetString("fgcolor", "Label.TextColor"));
}

void COFLabel::SetColorStr(const char *pchar)
{
	vgui::IScheme *pScheme = g_pVGuiSchemeManager->GetIScheme(GetScheme());
	Color pColor = pScheme->GetColor(pchar, Color(255, 255, 255, 255));
	V_snprintf(m_szColor, sizeof(m_szColor), "%d %d %d %d", pColor.r(), pColor.g(), pColor.b(), pColor.a());
	SetFgColor(pColor);
}

void COFLabel::ApplySchemeSettings(vgui::IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);
	SetColorStr(m_szColor);
}

void COFLabel::SetColorStr(Color pColor)
{
	V_snprintf(m_szColor, sizeof(m_szColor), "%d %d %d %d", pColor.r(), pColor.g(), pColor.b(), pColor.a());
	SetFgColor(pColor);
}