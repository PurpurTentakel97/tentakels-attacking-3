#
# Purpur Tentakel
# 02.03.2024
#

import enums


class RawEntry:
    def __init__(self, prefix: str, name: str, type_: enums.CppType, is_config: bool, constants_class: str,
                 value: str) -> None:
        self.prefix: str = prefix.lower().strip()
        self.name: str = name.lower().strip()
        self.type_: enums.CppType = type_
        self.is_config: bool = is_config
        self.constants_class: str = constants_class.title().strip()
        self.value: str = value

        def enum_name() -> str:
            return self.name.upper()

        def enum_return_value() -> str:
            return self.name


def load_raw_entries(entries: dict) -> tuple[RawEntry]:
    r: list[RawEntry] = list()
    for l in entries:
        load = entries[l]
        entry: RawEntry = RawEntry(
            # @formatter off
            load["prefix"],
            load["name"],
            enums.CppType(load["type"]),
            load["config"],
            load["constants_class"],
            load["value"]
            # @formatter on
        )
        r.append(entry)
    return tuple(r)
