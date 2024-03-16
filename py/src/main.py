#
# Purpur Tentakel
# 02.03.2024
#

import load_save
import raw_field
import raw_file
import gen_config_all
import file
import enums

_global_export_path: str = "../../src/"
_constants_export_dir: str = "constants"
_save_export_dir: str = "app"


def _check_len(to_check, length: int, name: str) -> None:
    if len(to_check) == length:
        enums.my_print(enums.PrintType.ERROR, f"{name} has no entries")
        exit()


def _load_and_gen_config() -> tuple[file.File]:
    input_fields: dict = load_save.LoadJson("config_fields.json")
    _check_len(input_fields, 0, "config_fields.json")
    raw_fields: tuple[raw_field.RawField] = raw_field.load_raw_config_entries(input_fields)
    _check_len(raw_fields, 0, "raw fields list")

    input_files: dict = load_save.LoadJson("config_classes.json")
    _check_len(input_files, 0, "config_classes.json")
    raw_files: tuple[raw_file.RawFile] = raw_file.load_raw_config_files(input_files)
    _check_len(raw_files, 0, "raw config classes list")

    return gen_config_all.gen(raw_fields, raw_files)


def _load_and_gen_save() -> tuple[file.File]:
    input_fields: dict = load_save.LoadJson("save_fields.json")
    _check_len(input_fields, 0, "save_fields.json")
    raw_fields: tuple[raw_field.RawSaveField] = raw_field.load_raw_save_entries(input_fields)
    _check_len(raw_fields, 0, "raw save field list")

    input_files: dict = load_save.LoadJson("save_classes.json")
    _check_len(input_files, 0, "save_classes.json")
    raw_files: tuple[raw_file.RawFile] = raw_file.load_raw_save_load_files(input_files)
    _check_len(raw_files, 0, "raw save classes list")

    return tuple()


config_files: tuple[file.File] = _load_and_gen_config()
save_files: tuple[file.File] = _load_and_gen_save()

for f in config_files:
    load_save.Save(_global_export_path, _constants_export_dir, f)
