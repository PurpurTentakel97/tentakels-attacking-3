#
# Purpur Tentakel
# 02.03.2024
#

import load_save
import raw_field
import raw_config_file
import gen_all
import file
import enums

_global_export_path: str = "../../src/"
_constants_export_dir: str = "constants"


def _check_len(to_check, length: int, name: str) -> None:
    if len(to_check) == length:
        enums.my_print(enums.PrintType.ERROR, f"{name} has no entries")
        exit()


input_fields: dict = load_save.LoadJson("fields.json")
_check_len(input_fields, 0, "fields.json")
raw_fields: tuple[raw_field.RawField] = raw_field.load_raw_entries(input_fields)
_check_len(raw_fields, 0, "raw fields list")

input_config_files: dict = load_save.LoadJson("config_classes.json")
_check_len(input_config_files, 0, "config_classes.json")
raw_config_files: tuple[raw_config_file.RawConfigFile] = raw_config_file.load_raw_config_files(input_config_files)
_check_len(raw_config_files, 0, "raw config classes list")

files: tuple[file.File] = gen_all.gen(raw_fields, raw_config_files)

for f in files:
    load_save.Save(_global_export_path, _constants_export_dir, f)
