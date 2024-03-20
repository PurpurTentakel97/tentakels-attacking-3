#
# Purpur Tentakel
# 20.03.2024
#

import raw_file
import raw_field
import file
import helper
import enums

_load_function: str = "LoadGame"
_save_function: str = "SaveGame"


def _gen_header() -> file.File:
    indent: int = 1
    text: str = f"{helper.indent(indent)}struct {helper.save_io_name} final {{\n" \
                f"{helper.indent(indent + 1)}static void {_load_function}();\n" \
                f"\n" \
                f"{helper.indent(indent + 1)}static void {_save_function}();\n" \
                f"{helper.indent(indent)}}};\n"
    return file.File(helper.save_io_name, enums.FileType.HEADER, [], [], "utl", text)


def gen(fields: tuple[raw_field.RawSaveField], file: tuple[raw_file.RawFile]) -> tuple[file.File]:
    return _gen_header(),
