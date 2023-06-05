#pragma once

#include "GBC/Core/Core.h"

// Taken from glfw3.h and modified

namespace gbc
{
	using Codepoint = uint32_t;

	GBC_DEFINE_BOUNDED_ENUM(
		Keycode, uint16_t,

		/* Printable keys */
		Space          =  32,
		Apostrophe     =  39, /* ' */
		Comma          =  44, /* , */
		Minus          =  45, /* - */
		Period         =  46, /* . */
		Slash          =  47, /* / */

		D0             =  48, /* 0 */
		D1             =  49, /* 1 */
		D2             =  50, /* 2 */
		D3             =  51, /* 3 */
		D4             =  52, /* 4 */
		D5             =  53, /* 5 */
		D6             =  54, /* 6 */
		D7             =  55, /* 7 */
		D8             =  56, /* 8 */
		D9             =  57, /* 9 */

		Semicolon      =  59, /* ; */
		Equal          =  61, /* = */

		A              =  65,
		B              =  66,
		C              =  67,
		D              =  68,
		E              =  69,
		F              =  70,
		G              =  71,
		H              =  72,
		I              =  73,
		J              =  74,
		K              =  75,
		L              =  76,
		M              =  77,
		N              =  78,
		O              =  79,
		P              =  80,
		Q              =  81,
		R              =  82,
		S              =  83,
		T              =  84,
		U              =  85,
		V              =  86,
		W              =  87,
		X              =  88,
		Y              =  89,
		Z              =  90,

		LeftBracket    =  91, /* [ */
		BackSlash      =  92, /* \ */
		RightBracket   =  93, /* ] */
		GraveAccent    =  96, /* ` */
		World1         = 161, /* non-US #1 */
		World2         = 162, /* non-US #2 */

		/* Function keys */
		FEscape        = 256,
		FEnter         = 257,
		FTab           = 258,
		FBackspace     = 259,
		FInsert        = 260,
		FDelete        = 261,
		FRight         = 262,
		FLeft          = 263,
		FDown          = 264,
		FUp            = 265,
		FPageUp        = 266,
		FPageDown      = 267,
		FHome          = 268,
		FEnd           = 269,
		FCapsLock      = 280,
		FScrollLock    = 281,
		FNumLock       = 282,
		FPrintScreen   = 283,
		FPause         = 284,

		F1             = 290,
		F2             = 291,
		F3             = 292,
		F4             = 293,
		F5             = 294,
		F6             = 295,
		F7             = 296,
		F8             = 297,
		F9             = 298,
		F10            = 299,
		F11            = 300,
		F12            = 301,
		F13            = 302,
		F14            = 303,
		F15            = 304,
		F16            = 305,
		F17            = 306,
		F18            = 307,
		F19            = 308,
		F20            = 309,
		F21            = 310,
		F22            = 311,
		F23            = 312,
		F24            = 313,
		F25            = 314,

		/* Keypad */
		KeyPad0        = 320,
		KeyPad1        = 321,
		KeyPad2        = 322,
		KeyPad3        = 323,
		KeyPad4        = 324,
		KeyPad5        = 325,
		KeyPad6        = 326,
		KeyPad7        = 327,
		KeyPad8        = 328,
		KeyPad9        = 329,

		KeyPadDecimal  = 330,
		KeyPadDivide   = 331,
		KeyPadMultiply = 332,
		KeyPadSubtract = 333,
		KeyPadAdd      = 334,
		KeyPadEnter    = 335,
		KeyPadEqual    = 336,

		LeftShift      = 340,
		LeftControl    = 341,
		LeftAlt        = 342,
		LeftSuper      = 343,
		RightShift     = 344,
		RightControl   = 345,
		RightAlt       = 346,
		RightSuper     = 347,
		Menu           = 348
	);
}
