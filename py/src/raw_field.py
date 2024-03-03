#
# Purpur Tentakel
# 02.03.2024
#

import enums
import helper


class RawField:
    def __init__(self, prefix: str, name: str, type_: int, is_config: bool, constants_class: str,
                 value: str) -> None:
        self.prefix: str = prefix.lower().strip()
        self.name: str = name.lower().strip()
        self.type_: enums.CppType = enums.CppType(type_)
        self.is_config: bool = is_config
        self.constants_class: str = constants_class.title().strip()
        self.value: str = value

    def enum_name(self) -> str:
        return self.name.upper()

    def enum_return_value(self) -> str:
        return self.name

    def _complete_name(self) -> str:
        return f"{self.prefix}{self.name}"

    def dump_field(self, indent: int) -> str:
        text: str = f"{helper.indent(indent)}{enums.field_type_lookup[self.type_]} {self._complete_name()} = "
        if helper.needs_quotes(self.type_):
            text += f"\"{self.value}\";\n"
        else:
            text += f"{self.value};\n"
        return text

    def dump_getter(self, indent: int) -> str:
        text: str = f"{helper.indent(indent)}[[nodiscard]] {enums.return_type_lookup[self.type_]} get_{self.name}() const {helper.left_bracket}\n"
        text += f"{helper.indent(indent + 1)}return {self._complete_name()};\n"
        text += f"{helper.indent(indent)}{helper.right_bracket}\n"
        return text

    def dump_setter(self, indent: int) -> str:
        if not helper.needs_setter(self.type_):
            return ""
        text: str = f"{helper.indent(indent)} void set_{self.name}({enums.passed_type_lookup[self.type_]} value) {helper.left_bracket}\n"
        text += f"{helper.indent(indent + 1)}{self._complete_name()} = value;\n"
        text += f"{helper.indent(indent)}{helper.right_bracket}\n"
        return text


reference_entry: dict = {
    "prefix": str(),
    "name": str(),
    "type": int(),
    "config": bool(),
    "constants_class": str(),
    "value": str()
}


def load_raw_entries(entries: dict) -> tuple[RawField]:
    if len(entries) == 0:
        enums.my_print(enums.PrintType.ERROR, "empty raw field json")
        return tuple()

    r: list[RawField] = list()

    for l in entries:
        load = entries[l]
        if len(load) > len(reference_entry):
            enums.my_print(enums.PrintType.ERROR, f"key '{l}' has too many entries")
            enums.my_print(enums.PrintType.INFO, f"expected: {len(reference_entry)} | provided: {len(load)}")
            return tuple()
        for r_e in reference_entry:
            if r_e not in load:
                enums.my_print(enums.PrintType.ERROR, f"key '{r_e}' missing in '{l}' in raw field json")
                return tuple()
            if not isinstance(reference_entry[r_e], type(load[r_e])):
                enums.my_print(enums.PrintType.ERROR, f"value '{r_e}' in '{l}' has unexpected value type")
                enums.my_print(enums.PrintType.INFO,
                               f"expected type: {type(reference_entry[r_e])} | provided type: {type(load[r_e])}")
                return tuple()
        entry: RawField = RawField(
            # @formatter off
            load["prefix"],
            load["name"],
            load["type"],
            load["config"],
            load["constants_class"],
            load["value"]
            # @formatter on
        )
        r.append(entry)
    return tuple(r)
