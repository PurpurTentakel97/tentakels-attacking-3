#
# Purpur Tentakel
# 02.03.2024
#

import enums
import file
import helper
import include
import raw_file
import raw_field

_constants: str = "constants"
_loadEntryCount: str = "loadEntryCount"


# dict
def _gen_load_dict(fields: tuple[raw_field.RawField], config_files: tuple[raw_file.RawFile]) -> dict[
    str, list[str]]:
    load: dict[str, list[str]] = dict()

    for c in config_files:
        text: str = f"if (nlohmann::json son; hlp::LoadSection(load, son, {helper.config_enum_name}::{c.enum_name()}, " \
                    f"{c.full_name()}::s_total_config_entry_count)) {helper.left_bracket}"
        l: list[str] = list()
        l.append(text)
        load[c.full_name()] = l

    for f in fields:
        if helper.no_config_load(f.type_):
            continue

        text = f"{helper.indent(1)}if ({enums.load_type_lookup[f.type_]} out; hlp::{enums.load_function_lookup[f.type_]}" \
               f"(son, out, {helper.config_enum_name}::{f.enum_name()}, {_loadEntryCount})) {helper.left_bracket} " \
               f"{_constants}.{f.class_name.lower()}.{f.full_name()} = "
        if f.type_ == enums.CppType.RESOLUTION:
            text += f"static_cast<Resolution>(out)"  # cast here if necessary
        else:
            text += f"out"  # cast here if necessary
        text += f"; {helper.right_bracket}"
        load[f.class_name].append(text)

    for c in config_files:
        load[c.full_name()].append(f"{helper.right_bracket}\n")

    return load


def _gen_save_dict(fields: tuple[raw_field.RawField], config_files: tuple[raw_file.RawFile]) -> dict[
    str, list[str]]:
    save: dict[str, list[str]] = dict()

    for c in config_files:
        text: str = f"save[{helper.config_switch_function_name}({helper.config_enum_name}::{c.enum_name()})] = {helper.left_bracket}"
        l: list[str] = list()
        l.append(text)
        save[c.full_name()] = l

    for f in fields:
        text: str = f"{helper.indent(1)}{helper.left_bracket} {helper.config_switch_function_name}({helper.config_enum_name}::" \
                    f"{f.enum_name()}), "
        if f.type_ == enums.CppType.PROBABILITY:
            text += f"{_constants}.{f.class_name.lower()}.{f.full_name()}.value"
        else:
            text += f"{_constants}.{f.class_name.lower()}.{f.full_name()}"
        text += f" {helper.right_bracket},"
        save[f.class_name].append(text)

    for c in config_files:
        save[c.full_name()].append(f"{helper.right_bracket};\n")

    return save


# source
def _gen_source_from_dict(dict_: dict[str, list[str]], indent: int) -> str:
    text: str = str()

    for entry in dict_:
        for e in dict_[entry]:
            text += f"{helper.indent(indent)}{e}\n"

    return text


# file
def _gen_header() -> file.File:
    indent: int = 1
    text: str = f"{helper.indent(indent)}struct {helper.config_io_name} final {helper.left_bracket}\n"

    indent += 1
    text += f"{helper.indent(indent)}static void LoadConfig();\n\n"
    text += f"{helper.indent(indent)}static void SaveConfig();\n"

    indent -= 1
    text += f"{helper.indent(indent)}{helper.right_bracket};\n"

    return file.File(helper.config_io_name, enums.FileType.HEADER, [], [], "cst", text)


def _gen_source(fields: tuple[raw_field.RawField], config_files: tuple[raw_file.RawFile]) -> file.File:
    indent: int = 1
    load_text: str = f"{helper.indent(indent)}void {helper.config_io_name}::LoadConfig() {helper.left_bracket}\n"
    save_text: str = f"{helper.indent(indent)}void {helper.config_io_name}::SaveConfig() {helper.left_bracket}\n"

    indent += 1

    # setup
    load_text += f"{helper.indent(indent)}utl::usize {_loadEntryCount} = 0;\n{helper.indent(indent)}nlohmann::json load;\n" \
                 f"{helper.indent(indent)}auto& {_constants} = app::AppContext::GetInstance().{_constants};\n" \
                 f"{helper.indent(indent)}if (not LoadAndValidateConfigJson(load, {_loadEntryCount})) {helper.left_bracket}\n"
    indent += 1
    load_text += f"{helper.indent(indent)}return;\n"
    indent -= 1
    load_text += f"{helper.indent(indent)}{helper.right_bracket}\n\n"
    save_text += f"{helper.indent(indent)}auto const& {_constants} = app::AppContext::GetInstance().{_constants};\n" \
                 f"{helper.indent(indent)}nlohmann::json save;\n\n"

    # gen
    load_entries: dict[str, list[str]] = _gen_load_dict(fields, config_files)
    save_entries: dict[str, list[str]] = _gen_save_dict(fields, config_files)
    load_text += _gen_source_from_dict(load_entries, indent)
    save_text += _gen_source_from_dict(save_entries, indent)

    # end
    load_text += f"{helper.indent(indent)}CheckLoadEntryCount({_loadEntryCount});\n" \
                 f"{helper.indent(indent)}hlp::Print(hlp::PrintType::INFO, \"config loaded\");\n"
    save_text += f"{helper.indent(indent)}hlp::SaveFile(Files::s_savesDir, Files::s_configFile, save.dump(4));\n" \
                 f"{helper.indent(indent)}hlp::Print(hlp::PrintType::INFO, \"config saved\");\n"

    indent -= 1
    load_text += f"{helper.indent(indent)}{helper.right_bracket}\n"
    save_text += f"{helper.indent(indent)}{helper.right_bracket}\n"

    includes: list[include.Include] = list()
    for c in config_files:
        includes.append(include.Include(f"{c.full_name()}.hpp", False))
    includes.extend([include.Include(f"{helper.config_io_name}.hpp", False),
                     include.Include("HelperConfigIO.hpp", False)])

    return file.File(helper.config_io_name, enums.FileType.SOURCE, includes, [], "cst", f"{load_text}\n{save_text}")


def gen(fields: tuple[raw_field.RawField], config_files: tuple[raw_file.RawFile]) -> tuple[
    file.File, file.File]:
    return _gen_header(), _gen_source(fields, config_files)
