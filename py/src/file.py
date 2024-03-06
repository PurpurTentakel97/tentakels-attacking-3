#
# Purpur Tentakel
# 02.03.2024
#

import helper
import include
import enums
import forward_declaration


class File:
    def __init__(self, name: str, type_: enums.FileType, includes: list[include.Include],
                 forward_declarations: list[forward_declaration.ForwardDeclaration], namespace: str, text: str) -> None:
        self.name: str = name
        self.type_: enums.FileType = type_
        self.includes: list[include.Include] = includes
        self.forward_declarations: list[forward_declaration.ForwardDeclaration] = forward_declarations
        self.namespace: str = namespace
        self.text: str = text

    def dump(self) -> str:
        text: str = helper.header
        if self.type_ == enums.FileType.HEADER:
            text += helper.pragma

        for incl in self.includes:
            text += incl.dump()

        text += '\n'

        for f in self.forward_declarations:
            text += f.dump()

        text += f"\nnamespace {self.namespace} {helper.left_bracket}\n" \
                f"{self.text}\n" \
                f"{helper.right_bracket} // namespace {self.namespace}\n"

        return text
