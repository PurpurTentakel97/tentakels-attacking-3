#
# Purpur Tentakel
# 20.03.2024
#

import raw_file
import raw_field
import file
import helper
import enums
import include

_load_function: str = "LoadGame"
_save_function: str = "SaveGame"
_save_state_cass: str = "utl::SaveState"
_save_state_variable: str = "saveState"
_dir: str = "dir"
_file: str = "file"


def _gen_header() -> file.File:
    indent: int = 1
    text: str = f"{helper.indent(indent)}struct {helper.save_io_name} final {{\n" \
                f"{helper.indent(indent + 1)}static void {_load_function}({_save_state_cass}& {_save_state_variable}, " \
                f"std::string const& {_dir}, std::string const& {_file});\n\n" \
                f"{helper.indent(indent + 1)}static void {_save_function}({_save_state_cass} const& {_save_state_variable}, " \
                f"std::string const& {_dir}, std::string const& {_file});\n" \
                f"{helper.indent(indent)}}};\n"
    return file.File(helper.save_io_name, enums.FileType.HEADER, [include.Include("utils/SaveState.hpp", True)], [],
                     "app",
                     text)


def _gen_source(fields: tuple[raw_field.RawSaveField], files: tuple[raw_file.RawFile]) -> file.File:
    indent: int = 1
    load_text: str = f"{helper.indent(indent)}void {helper.save_io_name}::{_load_function}({_save_state_cass}& {_save_state_variable}, " \
                     f"std::string const& {_dir}, std::string const& {_file}) {{\n"
    save_text: str = f"{helper.indent(indent)}void {helper.save_io_name}::{_save_function}({_save_state_cass} const& {_save_state_variable}, " \
                     f"std::string const& {_dir}, std::string const& {_file}) {{\n"

    indent += 1

    load_text += f"// enter preparation"
    save_text += f"{helper.indent(indent)} nlohmann::json save{{}};\n\n"

    for current_file in files:
        load_text += f"{helper.indent(indent)}// enter file loop here\n"
        save_text += f"{helper.indent(indent)}save[{helper.save_switch_function_name}(utl::{helper.save_enum_name}::{current_file.enum_name()})] = {{\n"
        indent += 1

        for current_field in fields:
            if current_field.class_name != current_file.full_name():
                continue
            save_text += f"{helper.indent(indent)}{{ {helper.save_switch_function_name}(utl::{helper.save_enum_name}::{current_field.enum_name()})," \
                         f" {_save_state_variable}.{current_field.class_name.lower()}.{current_field.getter_name()}() }},\n"

        indent -= 1
        save_text += f"{helper.indent(indent)}}};\n"

    save_text += f"{helper.indent(indent)}hlp::SaveFile({_dir}, {_file}, save.dump(4));\n"

    indent -= 1

    load_text += f"{helper.indent(indent)}}}\n"
    save_text += f"{helper.indent(indent)}}}\n"

    text: str = f"{load_text}\n{save_text}"

    return file.File(helper.save_io_name, enums.FileType.SOURCE,
                     [include.Include("nlohmann/json.hpp", True), include.Include("helper/SaveLoadFile.hpp", True),
                      include.Include(f"{helper.save_io_name}.hpp", False), include.Include("HelperSaveIO.hpp", False)],
                     [], "app", text)


def gen(fields: tuple[raw_field.RawSaveField], files: tuple[raw_file.RawFile]) -> tuple[file.File, file.File]:
    return _gen_header(), _gen_source(fields, files)
