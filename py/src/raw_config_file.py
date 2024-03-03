#
# Purpur Tentakel
# 02.03.2024
#

import enums
import include


class RawConfigFile:
    def __init__(self, prefix: str, name: str, type_: int, includes: list[dict], namespace: str) -> None:
        self.prefix = prefix.strip().title()
        self.name: str = name.strip().title()
        self.type_: enums.FileType = enums.FileType(type_)
        self.includes: list[include.Include] = list()
        self.namespace: str = namespace

        for i in includes:
            self.includes.append(include.Include(i["name"], i["s_brackets"]))

    def full_name(self) -> str:
        return f"{self.prefix}{self.name}"


def load_raw_entries(entries: dict) -> tuple[RawConfigFile]:
    r: list[RawConfigFile] = list()
    for l in entries:
        load = entries[l]
        entry: RawConfigFile = RawConfigFile(
            # @formatter off
            load["prefix"],
            load["name"],
            load["type"],
            load["includes"],
            load["namespace"]
            # @formatter on
        )
        r.append(entry)
    return tuple(r)


def raw_file_from_name(name: str, files: tuple[RawConfigFile]) -> RawConfigFile:
    for f in files:
        if name == f.full_name():
            return f
    # todo print