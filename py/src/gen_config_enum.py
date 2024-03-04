#
# Purpur Tentakel
# 02.03.2024
#
from typing import Tuple

import raw_field
import file
import enums
import include

_file_name: str = "G_ConfigEnum"


def _gen_source(fields: tuple[raw_field.RawField]) -> file.File:
    text: str = ""

    return file.File(_file_name, enums.FileType.SOURCE, [include.Include(_file_name, False)], "cst", text)


def _gen_header(fields: tuple[raw_field.RawField]) -> file.File:
    text: str = ""

    return file.File(_file_name, enums.FileType.HEADER, [], "cst", text)


def gen(fields: tuple[raw_field.RawField]) -> tuple[file.File, file.File]:
    return _gen_header(fields), _gen_source(fields)
