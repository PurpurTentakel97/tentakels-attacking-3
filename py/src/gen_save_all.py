#
# Purpur Tentakel
# 16.03.2024
#

import file
import raw_field
import raw_file
import gen_save_classes
import gen_save_enum
import gen_save_io


def gen(fields: tuple[raw_field.RawSaveField], files: tuple[raw_file.RawFile]) -> tuple[file.File]:
    generated: list = list()
    generated.extend(gen_save_classes.gen(fields, files))
    generated.extend(gen_save_enum.gen(fields, files))
    generated.extend(gen_save_io.gen(fields, files))
    return tuple(generated)
