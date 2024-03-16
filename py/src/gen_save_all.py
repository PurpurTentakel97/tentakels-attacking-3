#
# Purpur Tentakel
# 16.03.2024
#

import file
import raw_field
import raw_file
import gen_save_classes


def gen(fields: tuple[raw_field.RawSaveField], files: tuple[raw_file.RawFile]) -> tuple[file.File]:
    generated: list = list()
    generated.extend(gen_save_classes.gen(fields, files))
    return tuple(generated)
