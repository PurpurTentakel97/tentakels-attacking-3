#
# Purpur Tentakel
# 02.03.2024
#

import enums
import file
import helper
import include
import raw_field
import raw_config_file


def _gen_source(fields: tuple[raw_field.RawField], config_files: tuple[raw_config_file.RawConfigFile]) -> file.File:
    indent: int = 1
    text: str = f"{helper.indent(indent)}std::string {helper.config_switch_function_name}({helper.config_enum_name} const value) {helper.left_bracket}\n"

    indent += 1
    text += f"{helper.indent(indent)}switch (value) {helper.left_bracket}\n"

    indent += 1
    text += f"{helper.indent(indent)}case {helper.config_enum_name}::CONFIG: return \"config\";\n\n"

    for c in config_files:
        text += f"{helper.indent(indent)}case {helper.config_enum_name}::{c.enum_name()}: return \"{c.enum_return_value()}\";\n"

    text += '\n'

    for f in fields:
        if f.is_config:
            text += f"{helper.indent(indent)}case {helper.config_enum_name}::{f.enum_name()}: return \"{f.enum_return_value()}\";\n"

    indent -= 1
    text += f"{helper.indent(indent)}{helper.right_bracket}\n"

    indent -= 1
    text += f"{helper.indent(indent)}std::unreachable();\n"
    text += f"{helper.indent(indent)}{helper.right_bracket}\n"

    return file.File(helper.config_enum_name, enums.FileType.SOURCE,
                     [include.Include(f"{helper.config_enum_name}.hpp", False), include.Include("utility", True)],
                     "cst", text)


def _gen_header(fields: tuple[raw_field.RawField], config_files: tuple[raw_config_file.RawConfigFile]) -> file.File:
    indent: int = 1
    text: str = f"{helper.indent(indent)}enum class {helper.config_enum_name} {helper.left_bracket}\n"
    indent += 1

    text += f"{helper.indent(indent)}CONFIG,\n\n"

    for c in config_files:
        text += f"{helper.indent(indent)}{c.enum_name()},\n"

    text += '\n'

    for f in fields:
        if f.is_config:
            text += f"{helper.indent(indent)}{f.enum_name()},\n"

    indent -= 1
    text += f"{helper.indent(indent)}{helper.right_bracket};\n\n"

    text += f"{helper.indent(indent)}[[nodiscard]] std::string {helper.config_switch_function_name}({helper.config_enum_name} value);\n"

    return file.File(helper.config_enum_name, enums.FileType.HEADER, [include.Include("string", True)], "cst", text)


def gen(fields: tuple[raw_field.RawField], config_files: tuple[raw_config_file.RawConfigFile]) -> tuple[
    file.File, file.File]:
    return _gen_header(fields, config_files), _gen_source(fields, config_files)
