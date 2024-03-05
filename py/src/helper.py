#
# Purpur Tentakel
# 02.03.2024
#

from datetime import datetime
import enums

header: str = f"""//
// Purpur Tentakel
// {datetime.now().strftime("%d.%m.%Y")}
// This is a generated file. Do not edit this file.
//\n\n"""

pragma: str = "#pragma once\n\n"

left_bracket: str = "{"
right_bracket: str = "}"

config_enum_name: str = "G_ConfigEnum"
config_switch_function_name: str = "CToS"

config_io_name: str = "G_ConfigIO"


def indent(i: int) -> str:
    return ' ' * (i * 4)


def needs_constants_setter(type_: enums.CppType) -> bool:
    t: tuple[enums.CppType, ...] = (
        enums.CppType.USIZE,
        enums.CppType.STRING,
        enums.CppType.BOOL
    )
    return type_ in t


def no_config_load(type_: enums.CppType) -> bool:
    t: tuple[enums.CppType, ...] = (
        enums.CppType.STRING_STATIC_CONST,
    )

    return type_ in t


def needs_quotes(type_: enums.CppType) -> bool:
    return type_ in [enums.CppType.STRING, enums.CppType.STRING_STATIC_CONST]
