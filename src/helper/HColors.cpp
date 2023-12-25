//
// Purpur Tentakel
// 20.10.2022
//

#include "HColors.h"
#include "event/UIEvents.hpp"
#include "HGeneral.h"
#include "AppContext.h"

bool Colors::CheckValidColor(Color const& color) const {
	return std::find(m_colors.begin(), m_colors.end(), color)
		== m_colors.end();
}
Colors::ColorArray Colors::GetColors() const {
    return m_colors;
}
std::string Colors::AsString(Color color) {
	     if (AreSame(color, YELLOW))     { return AppContext::GetInstance().languageManager.Text("helper_color_yellow");      }
	else if (AreSame(color, GOLD))       { return AppContext::GetInstance().languageManager.Text("helper_color_gold");        }
	else if (AreSame(color, PINK))       { return AppContext::GetInstance().languageManager.Text("helper_color_pink");        }
	else if (AreSame(color, MAGENTA))    { return AppContext::GetInstance().languageManager.Text("helper_color_magenta");     }
	else if (AreSame(color, ORANGE))     { return AppContext::GetInstance().languageManager.Text("helper_color_orange");      }
	else if (AreSame(color, RED))        { return AppContext::GetInstance().languageManager.Text("helper_color_red");         }
	else if (AreSame(color, MAROON))     { return AppContext::GetInstance().languageManager.Text("helper_color_maroon");      }
	else if (AreSame(color, NECRO))      { return "Necro"; /* no translation because its a name */                            }
	else if (AreSame(color, LIME))       { return AppContext::GetInstance().languageManager.Text("helper_color_lime");        }
	else if (AreSame(color, DARKGREEN))  { return AppContext::GetInstance().languageManager.Text("helper_color_dark_green");  }
	else if (AreSame(color, SKYBLUE))    { return AppContext::GetInstance().languageManager.Text("helper_color_sky_blue");    }
	else if (AreSame(color, BLUE))       { return AppContext::GetInstance().languageManager.Text("helper_color_blue");        }
	else if (AreSame(color, DARKBLUE))   { return AppContext::GetInstance().languageManager.Text("helper_color_dark_blue");   }
	else if (AreSame(color, PURPLE))     { return AppContext::GetInstance().languageManager.Text("helper_color_purple");      }
	else if (AreSame(color, VIOLET))     { return AppContext::GetInstance().languageManager.Text("helper_color_violet");      }
	else if (AreSame(color, DARKPURPLE)) { return AppContext::GetInstance().languageManager.Text("helper_color_dark_purple"); }
	else                                 { return AppContext::GetInstance().languageManager.Text("helper_color_invalid");     }
}
bool Colors::AreSame(Color lhs, Color rhs) {
	return  {
			lhs.r == rhs.r
		and lhs.g == rhs.g
		and lhs.b == rhs.b
		and lhs.a == rhs.a 
	};
}
bool Colors::NeedBackground(Color color) {
	return AreSame(color, MAGENTA  )
	    or AreSame(color, DARKGREEN)
	    or AreSame(color, DARKBLUE )
	    or AreSame(color, VIOLET   );
}
