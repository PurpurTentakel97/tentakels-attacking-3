#
# Purpur Tentakel
# 02.03.2024
#

import json


def LoadJson() -> dict:
    with open("fields.json", 'r') as f:
        data: dict = json.load(f)

    return data
