#
# Purpur Tentakel
# 02.03.2024
#

import json
import enums


def LoadJson(path: str) -> dict:
    enums.my_print(enums.PrintType.LOAD, path)
    with open(path, 'r') as f:
        data: dict = json.load(f)
    return data
