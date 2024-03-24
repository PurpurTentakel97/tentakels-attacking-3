#
# Purpur Tentakel
# 02.03.2024
#

import enums
import helper


class RawField:
    def __init__(self, prefix: str, name: str, type_: int, class_name: str,
                 value: str) -> None:
        self.prefix: str = prefix.lower().strip()
        self.name: str = name.lower().strip()
        self.class_name: str = class_name.title().strip()
        self.value: str = value

        try:
            self.type_: enums.CppType = enums.CppType(type_)
        except ValueError as e:
            enums.my_print(enums.PrintType.ERROR, str(e))
            enums.my_print(enums.PrintType.INFO, "valid value would be one of:")
            enums.print_enum(enums.CppType)
            exit()

    def enum_name(self) -> str:
        return f"{self.class_name_enum_name()}_{self.name.upper()}"

    def class_name_enum_name(self) -> str:
        return self.class_name.upper()

    def enum_return_value(self) -> str:
        return self.name

    def full_name(self) -> str:
        return f"{self.prefix}{self.name}"

    def getter_name(self) -> str:
        return f"get_{self.name}"

    def setter_name(self) -> str:
        return f"set_{self.name}"

    def dump_field(self, indent: int) -> str:
        text: str = f"{helper.indent(indent)}{enums.field_type_lookup[self.type_]} {self.full_name()} = "
        if helper.needs_quotes(self.type_):
            text += f"\"{self.value}\";\n"
        else:
            text += f"{self.value};\n"
        return text

    def dump_getter(self, indent: int) -> str:
        text: str = f"{helper.indent(indent)}[[nodiscard]] {enums.return_type_lookup[self.type_]} {self.getter_name()}() const {{\n"
        text += f"{helper.indent(indent + 1)}return {self.full_name()};\n"
        text += f"{helper.indent(indent)}}}\n"
        return text

    def dump_setter(self, indent: int) -> str:
        if not helper.needs_constants_setter(self.type_):
            return ""

        if helper.needs_move(self.type_):
            text: str = f"{helper.indent(indent)}void {self.setter_name()}({enums.return_type_lookup[self.type_]} value) {{\n"
            text += f"{helper.indent(indent + 1)}{self.full_name()} = std::move(value);\n"
            text += f"{helper.indent(indent)}}}\n"
        else:
            text: str = f"{helper.indent(indent)}void set_{self.name}({enums.passed_type_lookup[self.type_]} value) {{\n"
            text += f"{helper.indent(indent + 1)}{self.full_name()} = value;\n"
            text += f"{helper.indent(indent)}}}\n"
        return text


class RawSaveField(RawField):
    def __init__(self, prefix: str, name: str, type_: int, class_name: str,
                 value: str) -> None:
        super(RawSaveField, self).__init__(prefix, name, type_, class_name, value)

    def dump_field(self, indent: int) -> str:
        return super().dump_field(indent)


conf_reference_entry: dict = {
    "prefix": str(),
    "name": str(),
    "type": int(),
    "constants_class": str(),
    "value": str()
}


def load_raw_config_entries(entries: dict) -> tuple[RawField]:
    if len(entries) == 0:
        enums.my_print(enums.PrintType.ERROR, "empty raw field json")
        return tuple()

    r: list[RawField] = list()

    for l in entries:
        load = entries[l]
        if not helper.check_load_json(load, l, conf_reference_entry):
            return tuple()

        entry: RawField = RawField(
            # @formatter off
            load["prefix"],
            load["name"],
            load["type"],
            load["constants_class"],
            load["value"]
            # @formatter on
        )
        r.append(entry)
    return tuple(r)


save_reference_entry: dict = {
    "prefix": str(),
    "name": str(),
    "type": int(),
    "constants_class": str(),
    "value": str()
}


def load_raw_save_entries(entries: dict) -> tuple[RawSaveField]:
    if len(entries) == 0:
        enums.my_print(enums.PrintType.ERROR, "empty raw field json")
        return tuple()

    r: list[RawSaveField] = list()

    for l in entries:
        load = entries[l]
        if not helper.check_load_json(load, l, save_reference_entry):
            return tuple()

        entry: RawSaveField = RawSaveField(
            # @formatter off
            load["prefix"],
            load["name"],
            load["type"],
            load["constants_class"],
            load["value"]
            # @formatter on
        )
        r.append(entry)
    return tuple(r)
