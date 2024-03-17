#
# Purpur Tentakel
# 17.03.2024
#

import raw_file
import raw_field
import file
import helper
import enums
import include


def _gen_header(fields: tuple[raw_field.RawSaveField], files: tuple[raw_file.RawFile]) -> file.File:
    indent: int = 1
    text: str = f"{helper.indent(indent)}enum class {helper.save_enum_name} {{\n"
    indent += 1

    for f in files:
        text += f"{helper.indent(indent)}{f.enum_name()},\n"

    text += '\n'

    for f in fields:
        text += f"{helper.indent(indent)}{f.enum_name()},\n"

    indent -= 1
    text += f"{helper.indent(indent)}}};\n\n" \
            f"{helper.indent(indent)}" \
            f"[[nodiscard]] std::string {helper.save_switch_function_name}({helper.save_enum_name} const& type);\n"

    return file.File(helper.save_enum_name, enums.FileType.HEADER, [include.Include("string", True)], [], "app", text)


def _gen_source(fields: tuple[raw_field.RawSaveField], files: tuple[raw_file.RawFile]) -> file.File:
    indent: int = 1
    text: str = f"{helper.indent(indent)}std::string " \
                f"{helper.save_switch_function_name}({helper.save_enum_name} const& type) {{\n"
    indent += 1
    text += f"{helper.indent(indent)}switch (type) {{\n"
    indent += 1
    for f in files:
        text += f"{helper.indent(indent)}case {helper.save_enum_name}::{f.enum_name()}: return \"{f.enum_return_value()}\";\n"

    for f in fields:
        text += f"{helper.indent(indent)}case {helper.save_enum_name}::{f.enum_name()}: return \"{f.enum_return_value()}\";\n"

    indent -= 1
    text += f"{helper.indent(indent)}}}\n"
    indent -= 1
    text += f"{helper.indent(indent)}std::unreachable();\n" \
            f"{helper.indent(indent)}}}"

    return file.File(helper.save_enum_name, enums.FileType.SOURCE,
                     [include.Include(f"{helper.save_enum_name}.hpp", False)], [], "app", text)


def gen(fields: tuple[raw_field.RawSaveField], files: tuple[raw_file.RawFile]) -> tuple[file.File, ...]:
    return _gen_header(fields, files), _gen_source(fields, files)
