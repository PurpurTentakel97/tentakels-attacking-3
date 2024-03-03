#
# Purpur Tentakel
# 02.03.2024
#

import json


def LoadJson(path: str) -> dict:
    with open(path, 'r') as f:
        data: dict = json.load(f)

    return data
