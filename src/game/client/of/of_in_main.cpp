// ========= Copyright Open Fortress Developers, CC-BY-NC-SA ============
// Purpose: Input manager
// Author(s): ficool2
//

#include "cbase.h"
#include "kbutton.h"
#include "input.h"

class COFInput : public CInput
{
};

static COFInput g_Input;

IInput *input = ( IInput * )&g_Input;
