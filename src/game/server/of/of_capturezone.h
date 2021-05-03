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

class CCaptureZone : public CBaseTrigger
{
public:
	DECLARE_CLASS(CCaptureZone, CBaseTrigger);

	CCaptureZone();
	~CCaptureZone();

	void Spawn();
	void SetDisabled(bool bDisable);
	void Activate();
	bool IsDisabled();
	void ShimTouch(COFPlayer *pPlayer);
	void Capture(COFPlayer *pPlayer);

private:

	float field_0x514;
};