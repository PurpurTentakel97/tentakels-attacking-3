#
# Purpur Tentakel
# 02.03.2024
#

import file
import include

f: file.File = file.File("test-file", file.FileType.HEADER, [include.Include("string")], "app",
                         "\tich bin der super text, der hier irgendwann mal rein soll!\n\n\tPups")

f2: file.File = file.File("test-file", file.FileType.HEADER, [include.Include("test-file.hpp", False)], "app",
                         "\tich bin der super text, der hier irgendwann mal rein soll!\n\n\tPups")

print(f.dump())
print(f2.dump())
