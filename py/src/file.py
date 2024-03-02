#
# Purpur Tentakel
# 02.03.2024
#

import helper
import include
from enum import Enum


class FileType(Enum):
    HEADER = 1
    SOURCE = 2


type_lookup: dict[FileType, str] = {
    FileType.HEADER: ".hpp",
    FileType.SOURCE: ".cpp",
}


class File:
    def __init__(self, name: str, type_: FileType, includes: list[include.Include], namespace: str, text: str) -> None:
        self.name: str = name
        self.type_: FileType = type_
        self.includes: list[include.Include] = includes
        self.namespace: str = namespace
        self.text: str = text

    def dump(self) -> str:
        text:str = helper.header
        if self.type_ == FileType.HEADER:
            text += helper.pragma

        for incl in self.includes:
            text += incl.dump()

        text += f"\nnamespace {self.namespace} {helper.left_bracket}\n"
        text += self.text + '\n'
        text += f"{helper.right_bracket} // namespace {self.namespace}\n"

        return text
