#
# Purpur Tentakel
# 02.03.2024
#

import enums
import include
import forward_declaration


class RawConfigFile:
    def __init__(self, prefix: str, name: str, type_: int, includes: list[dict], forward_declarations: list[dict],
                 namespace: str) -> None:
        self.prefix = prefix.strip().title()
        self.name: str = name.strip().title()
        self.includes: list[include.Include] = list()
        self.forward_declarations: list[forward_declaration.ForwardDeclaration] = list()
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

        for f in forward_declarations:
            self.forward_declarations.append(forward_declaration.ForwardDeclaration(f["namespace"], f["name"]))

    def full_name(self) -> str:
        return f"{self.prefix}{self.name}"

    def enum_name(self) -> str:
        return self.full_name().upper()

    def enum_return_value(self) -> str:
        return self.name.lower()


reference_entry: dict = {
    "prefix": str(),
    "name": str(),
    "type": int(),
    "includes": list(),
    "forward_declaration": list(),
    "namespace": str(),
}
reference_include_entry: dict = {
    "name": str(),
    "s_brackets": bool(),
}

reference_forward_entry: dict = {
    "namespace": str(),
    "name": str(),
}


def _check_import_list(entries: list, reference: dict, key: str, outer_key: str) -> bool:
    for incl in entries:
        if len(incl) > len(reference):
            enums.my_print(enums.PrintType.ERROR, f"key '{key}' has too many entries")
            enums.my_print(enums.PrintType.INFO,
                           f"expected: {len(reference)} | provided: {len(incl)}")
            return False
        for i_e in reference:
            if i_e not in incl:
                enums.my_print(enums.PrintType.ERROR,
                               f"key '{i_e}' missing in key '{key}' missing in '{outer_key}' in raw config file json")
                return False
            if not isinstance(incl[i_e], type(reference[i_e])):
                enums.my_print(enums.PrintType.ERROR,
                               f"value '{i_e}' in '{key}' in '{outer_key}' has unexpected value type")
                enums.my_print(enums.PrintType.ERROR,
                               f"expected type: {type(reference[i_e])} | provided type: {type(incl[i_e])}")
                return False
    return True


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
                if not _check_import_list(load[r_e], reference_include_entry, r_e, l):
                    return tuple()
            if r_e == "forward_declaration":
                if not _check_import_list(load[r_e], reference_forward_entry, r_e, l):
                    return tuple()

        entry: RawConfigFile = RawConfigFile(
            # @formatter off
            load["prefix"],
            load["name"],
            load["type"],
            load["includes"],
            load["forward_declaration"],
            load["namespace"]
            # @formatter on
        )
        r.append(entry)
    return tuple(r)


def raw_file_from_name(name: str, files: tuple[RawConfigFile]) -> RawConfigFile:
    for f in files:
        if name == f.full_name():
            return f
    enums.my_print(enums.PrintType.ERROR, f"requested config class name '{name}' not existing")
    enums.my_print(enums.PrintType.INFO, f"collected config class names:")
    for f in files:
        enums.my_print(enums.PrintType.INFO, f.full_name())
    exit()
