#pragma once

#include "GBC/Core/Core.h"

// Taken from glfw3.h and modified

namespace gbc
{
	GBC_DEFINE_BOUNDED_ENUM(
		MouseButton, uint8_t,
		
		B1 = 1, Left     = B1,
		B2 = 2, Right    = B2,
		B3 = 3, Middle   = B3,
		B4 = 4, Backward = B4,
		B5 = 5, Forward  = B5,
		B6 = 6,
		B7 = 7,
		B8 = 8
	);
}
