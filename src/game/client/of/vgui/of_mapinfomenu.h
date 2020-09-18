// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of the Map Info Panel
// Author(s): Ms
//
#pragma once

#include "vgui_controls/Frame.h"
#include "game/client/iviewport.h"

class COFMapInfoMenu : public vgui::Frame, public IViewPortPanel
{
private:
	DECLARE_CLASS_SIMPLE( COFMapInfoMenu, vgui::Frame );

public:
	COFMapInfoMenu( IViewPort* pViewPort );

	virtual const char* GetName( void ) { return "mapinfo"; }
	virtual void SetData( KeyValues* data );
	virtual void Reset();
	virtual void Update();
	virtual bool NeedsUpdate( void ) { return false; }
	virtual bool HasInputElements( void ) { return true; }
	virtual void ShowPanel( bool bShow );

	// both vgui::Frame and IViewPortPanel define these, so explicitly define them here as passthroughs to vgui
	vgui::VPANEL GetVPanel( void ) { return BaseClass::GetVPanel(); }
	virtual bool IsVisible() { return BaseClass::IsVisible(); }
	virtual void SetParent( vgui::VPANEL parent ) { BaseClass::SetParent( parent ); }

	void LoadMapPage();

	virtual void ApplySchemeSettings( vgui::IScheme* pScheme ) override;

	virtual void OnCommand( const char* command );
private:
	char m_szMapName[260];
};