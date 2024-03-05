#
# Purpur Tentakel
# 02.03.2024
#

import enums
import file
import helper
import include
import raw_config_file
import raw_field


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
    constants: str = "constants"
    indent: int = 1
    load_text: str = f"{helper.indent(indent)}void {helper.config_io_name}::LoadConfig() {helper.left_bracket}\n"
    save_text: str = f"{helper.indent(indent)}void {helper.config_io_name}::SaveConfig() {helper.left_bracket}\n"

    indent += 1

    # setup
    load_text += f"{helper.indent(indent)}loadEntryCount = 0;\n{helper.indent(indent)}nlohmann::json load;\n" \
                 f"{helper.indent(indent)}auto& {constants} = app::AppContext::GetInstance().{constants};\n" \
                 f"{helper.indent(indent)}if (not LoadAndValidateConfigJson(load)) {helper.left_bracket}\n"
    indent += 1
    load_text += f"{helper.indent(indent)}return;\n"
    indent -= 1
    load_text += f"{helper.indent(indent)}{helper.right_bracket}\n\n"
    save_text += f"{helper.indent(indent)}auto const& {constants} = app::AppContext::GetInstance().{constants};\n" \
                 f"{helper.indent(indent)}nlohmann::json save;\n\n"

    # gen

    # end
    load_text += f"{helper.indent(indent)}CheckLoadEntryCount();\n" \
                 f"{helper.indent(indent)}hlp::Print(hlp::PrintType::INFO, \"config loaded\");\n"
    save_text += f"{helper.indent(indent)}hlp::SaveFile(Files::s_savesDir, Files::s_configFile, save.dump(4));\n" \
                 f"{helper.indent(indent)}hlp::Print(hlp::PrintType::INFO, \"config saved\");\n"

    indent -= 1
    load_text += f"{helper.indent(indent)}{helper.right_bracket}\n"
    save_text += f"{helper.indent(indent)}{helper.right_bracket}\n"

    return file.File(helper.config_io_name, enums.FileType.SOURCE,
                     [include.Include(f"{helper.config_io_name}.hpp", False),
                      include.Include("HelperConfigIO.hpp", False)], "cst", f"{load_text}\n{save_text}")


def gen(fields: tuple[raw_field.RawField], config_files: tuple[raw_config_file.RawConfigFile]) -> tuple[
    file.File, file.File]:
    return gen_header(), gen_source(fields, config_files)
