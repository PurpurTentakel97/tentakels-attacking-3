#
# Purpur Tentakel
# 02.03.2024
#

import file
import raw_field
import raw_file
import gen_config_classes
import gen_config_enum
import gen_config_io


def gen(fields: tuple[raw_field.RawField], config: tuple[raw_file.RawFile]) -> tuple[file.File]:
    generated: list = list()
    generated.extend(gen_config_classes.gen(fields, config))
    generated.extend(gen_config_enum.gen(fields, config))
    generated.extend(gen_config_io.gen(fields, config))
    return tuple(generated)
