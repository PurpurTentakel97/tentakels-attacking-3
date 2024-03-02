#
# Purpur Tentakel
# 02.03.2024
#

import helper
import include
import enums


class File:
    def __init__(self, name: str, type_: enums.FileType, includes: list[include.Include], namespace: str, text: str) -> None:
        self.name: str = name
        self.type_: enums.FileType = type_
        self.includes: list[include.Include] = includes
        self.namespace: str = namespace
        self.text: str = text

    def dump(self) -> str:
        text:str = helper.header
        if self.type_ == enums.FileType.HEADER:
            text += helper.pragma

        for incl in self.includes:
            text += incl.dump()

        text += f"\nnamespace {self.namespace} {helper.left_bracket}\n"
        text += self.text + '\n'
        text += f"{helper.right_bracket} // namespace {self.namespace}\n"

        return text
