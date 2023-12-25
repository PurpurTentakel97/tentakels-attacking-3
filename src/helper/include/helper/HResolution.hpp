//
// Purpur Tentakel
// 10.12.2022
//

#pragma once

enum class Resolution {
	// 16:9
	UHD2 = 0,
	_5K,
	UHD1,
	WQHD,
	FULL_HD,
	HD,

	// 21:9
	_5K_ULTRAWIDE,
	UWQHD,
	UWHD,

	// 4:3
	QXGA,
	UXGA,
	SXGA_Plus,
	XGA_plus,
	XGA,
	SVGA,
	PAL,
	VGA,

	SCREEN,
	NATIVE,
	LAST,
};
