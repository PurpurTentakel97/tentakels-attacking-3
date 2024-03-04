#
# Purpur Tentakel
# 02.03.2024
#

import raw_field
import raw_config_file
import file
import helper
import enums
import include


def gen_header() -> file.File:
    indent: int = 1
    text: str = f"{helper.indent(indent)}struct {helper.config_io_name} final {helper.left_bracket}\n"

    indent += 1
    text += f"{helper.indent(indent)}static void LoadConfig();\n\n"
    text += f"{helper.indent(indent)}static void SaveConfig();\n"

    indent -= 1
    text += f"{helper.indent(indent)}{helper.right_bracket};\n"

    return file.File(helper.config_io_name, enums.FileType.HEADER, [], "cst", text)


def gen_source(fields: tuple[raw_field.RawField], config_files: tuple[raw_config_file.RawConfigFile]) -> file.File:
    indent: int = 1
    text: str = ""

    return file.File(helper.config_io_name, enums.FileType.SOURCE,
                     [include.Include(f"{helper.config_io_name}.hpp", False)], "cst", text)


def gen(fields: tuple[raw_field.RawField], config_files: tuple[raw_config_file.RawConfigFile]) -> tuple[
    file.File, file.File]:
    return gen_header(), gen_source(fields, config_files)
