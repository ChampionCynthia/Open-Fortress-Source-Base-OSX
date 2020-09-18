// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of the MOTD Panel
// Author(s): Ms
//
#pragma once

#include "vguitextwindow.h"

// OFSTATUS: INCOMPLETE, missing functions
class COFTextWindow : public CTextWindow
{
private:
	DECLARE_CLASS_SIMPLE( COFTextWindow, CTextWindow );

public:
	COFTextWindow( IViewPort* pViewPort );

	virtual void ApplySchemeSettings( vgui::IScheme* pScheme ) override;

	virtual void SetData( KeyValues* data ) override;

	virtual void OnCommand( const char* command ) override;

	virtual void OnThink() override;

	virtual void PaintBackground() override;

	virtual void ShowPanel( bool bShow );

protected:
	virtual void OnKeyCodePressed( vgui::KeyCode code );

private:
	bool m_bCustomSvr;
};