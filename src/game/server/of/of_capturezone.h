// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Implementation of CCaptureZone
// Author(s): Cherry!
//

#pragma once

#include "triggers.h"

#ifdef CLIENT_DLL
	#define CCaptureZone C_CaptureZone
#endif

DECLARE_AUTO_LIST(ICaptureZoneAutoList);

class COFPlayer;

// Taken from trigger_area_capture.h
// This class is to get around the fact that DEFINE_FUNCTION doesn't like multiple inheritance
class CCaptureZoneShim : public CBaseTrigger
{
	virtual void ShimTouch(CBaseEntity *pOther) = 0;
public:
	void	Touch(CBaseEntity *pOther) { return ShimTouch(pOther); }
};

class CCaptureZone : public CCaptureZoneShim, public ICaptureZoneAutoList
{
public:
	DECLARE_CLASS(CCaptureZone, CCaptureZoneShim);
	DECLARE_DATADESC();

	CCaptureZone();
	~CCaptureZone();

	void Spawn();
	void SetDisabled(bool bDisable);
	void Activate();
	bool IsDisabled();
	void ShimTouch(CBaseEntity *pOther) override;
	void Capture(COFPlayer *pPlayer);
	int UpdateTransmitState();
	void InputEnable();
	void InputDisable();

private:

	float field_0x514;
	float m_flCaptureDelayOffset;

	COutputEvent m_outputOnCapture;
	COutputEvent m_OnCapTeam1;
	COutputEvent m_OnCapTeam2;
};