//
// Purpur Tentakel
// 28.10.2022
//

#include "HPrint.h"



void Print(PrintType printType, std::string const& message) {
#ifndef _DEBUG
	if (printType == PrintType::ONLY_DEBUG) { return; }
#endif // _DEBUG

	std::string const typeS   { GetPrintTypeString(printType) };
	std::string const toExport{ typeS + " " + message + '\n'  };

	TryExport(toExport, printType);
	std::cout << std::setw(GetPrintTypeString(longestType).size()) << typeS << ' ' << message << '\n';
}
