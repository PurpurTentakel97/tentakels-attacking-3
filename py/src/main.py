#
# Purpur Tentakel
# 02.03.2024
#

import load_save
import raw_field
import raw_config_file
import gen_config_casses
import file

input_fields: dict = load_save.LoadJson("fields.json")
raw_fields: tuple[raw_field.RawField] = raw_field.load_raw_entries(input_fields)

input_config_files: dict = load_save.LoadJson("config_classes.json")
raw_config_files: tuple[raw_config_file.RawConfigFile] = raw_config_file.load_raw_config_files(input_config_files)

files: tuple[file] = gen_config_casses.gen(raw_fields, raw_config_files)

for f in files:
    print(f.dump())
