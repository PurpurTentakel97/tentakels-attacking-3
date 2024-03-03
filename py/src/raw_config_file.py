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
        self.includes: list[include.Include] = list()
        self.namespace: str = namespace

        try:
            self.type_: enums.FileType = enums.FileType(type_)
        except ValueError as e:
            enums.my_print(enums.PrintType.ERROR, str(e))
            enums.my_print(enums.PrintType.INFO, "valid value would be one of:")
            enums.print_enum(enums.FileType)
            exit()

        for i in includes:
            self.includes.append(include.Include(i["name"], i["s_brackets"]))

    def full_name(self) -> str:
        return f"{self.prefix}{self.name}"


reference_entry: dict = {
    "prefix": str(),
    "name": str(),
    "type": int(),
    "includes": list(),
    "namespace": str(),
}
reference_include_entry: dict = {
    "name": str(),
    "s_brackets": bool()
}


def load_raw_config_files(entries: dict) -> tuple[RawConfigFile]:
    if len(entries) == 0:
        enums.my_print(enums.PrintType.ERROR, "empty raw config files json")
        return tuple()

    r: list[RawConfigFile] = list()
    for l in entries:
        load = entries[l]
        if len(load) > len(reference_entry):
            enums.my_print(enums.PrintType.ERROR, f"key '{l}' has too many entries")
            enums.my_print(enums.PrintType.INFO, f"expected: {len(reference_entry)} | provided: {len(load)}")
            return tuple()
        for r_e in reference_entry:
            if r_e not in load:
                enums.my_print(enums.PrintType.ERROR, f"key '{r_e}' missing in '{l}' in raw config file json")
                return tuple()
            if not isinstance(load[r_e], type(reference_entry[r_e])):
                enums.my_print(enums.PrintType.ERROR, f"value '{r_e}' in '{l}' has unexpected value type")
                enums.my_print(enums.PrintType.INFO,
                               f"expected type: {type(reference_entry[r_e])} | provided type: {type(load[r_e])}")
                return tuple()
            if r_e == "includes":
                for incl in load[r_e]:
                    if len(incl) > len(reference_include_entry):
                        enums.my_print(enums.PrintType.ERROR, f"key '{r_e}' has too many entries")
                        enums.my_print(enums.PrintType.INFO,
                                       f"expected: {len(reference_include_entry)} | provided: {len(incl)}")
                        return tuple()
                    for i_e in reference_include_entry:
                        if i_e not in incl:
                            enums.my_print(enums.PrintType.ERROR,
                                           f"key '{i_e}' missing in key '{r_e}' missing in '{l}' in raw config file json")
                            return tuple()
                        if not isinstance(incl[i_e], type(reference_include_entry[i_e])):
                            enums.my_print(enums.PrintType.ERROR,
                                           f"value '{i_e}' in '{r_e}' in '{l}' has unexpected value type")
                            enums.my_print(enums.PrintType.ERROR,
                                           f"expected type: {type(reference_include_entry[i_e])} | provided type: {type(incl[i_e])}")
                            return tuple()

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
