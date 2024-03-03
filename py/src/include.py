#
# Purpur Tentakel
# 02.03.2024
#

import helper


class Include:
    def __init__(self, name: str, squared_brackets: bool) -> None:
        self.name: str = name
        self.squared_brackets: bool = squared_brackets

    def dump(self) -> str:
        l_b: str = "<" if self.squared_brackets else '"'
        r_b: str = ">" if self.squared_brackets else '"'
        return f"#include {l_b}{self.name}{r_b}\n"
