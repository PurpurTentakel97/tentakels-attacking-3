#
# Purpur Tentakel
# 02.03.2024
#

import helper


class ForwardDeclaration:
    def __init__(self, namespace: str, name: str) -> None:
        self.namespace: str = namespace.strip()
        self.name: str = name.strip()

    def dump(self) -> str:
        return f"namespace {self.namespace} {{\n" \
               f"{helper.indent(1)} {self.name};\n" \
               f"}}\n"
