// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Lag Prediction manager
// Author(s): ficool2
//

#include "cbase.h"
#include "prediction.h"
#include "c_baseplayer.h"
#include "igamemovement.h"

static CMoveData g_MoveData;
CMoveData *g_pMoveData = &g_MoveData;

class COFPrediction : public CPrediction
{
	DECLARE_CLASS( COFPrediction, CPrediction );
};

static COFPrediction g_Prediction;

EXPOSE_SINGLE_INTERFACE_GLOBALVAR( COFPrediction, IPrediction, VCLIENT_PREDICTION_INTERFACE_VERSION, g_Prediction );

CPrediction *prediction = &g_Prediction;