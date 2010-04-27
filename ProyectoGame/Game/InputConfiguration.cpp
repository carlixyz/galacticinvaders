#include "InputConfiguration.h"

tActionMapping kaActionMapping[] = {
	{ eIA_CloseApplication, eKeyboard, VK_ESCAPE },
	{ eIA_GoUp, eKeyboard, VK_UP },
	{ eIA_GoDown, eKeyboard, VK_DOWN },
	{ eIA_GoRight, eKeyboard, VK_RIGHT },
	{ eIA_GoLeft, eKeyboard, VK_LEFT },
	{ eIA_Accept, eKeyboard, VK_RETURN },


	{ eIA_Shoot, eKeyboard, VK_SPACE }, // just 4 now only exit ...
	// { eIA_Cancel, eKeyboard, VK_ESCAPE },
	{ -1, -1, -1 } // Final de la tabla
};
