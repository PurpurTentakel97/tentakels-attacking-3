#
# Purpur Tentakel
# 02.03.2024
#

import json
import enums
import file
import os


def LoadJson(path: str) -> dict:
    enums.my_print(enums.PrintType.LOAD, path)
    with open(path, 'r') as f:
        try:
            data: dict = json.load(f)
        except json.JSONDecodeError as e:
            enums.my_print(enums.PrintType.ERROR, str(e))
            return dict()
    return data


def Save(p: str, f: file.File) -> None:
    my_path: str = p if f.type_ == enums.FileType.SOURCE else os.path.join(p, "include", p)
    if not os.path.isdir(my_path):
        os.makedirs(my_path)
        enums.my_print(enums.PrintType.GENERATE, f"path: {my_path}")

    name: str = f.name + enums.file_extension_lookup[f.type_]
    with open(os.path.join(my_path, name), 'w') as output:
        output.write(f.dump())

    enums.my_print(enums.PrintType.GENERATE, f"file: {os.path.join(my_path, name)}")
