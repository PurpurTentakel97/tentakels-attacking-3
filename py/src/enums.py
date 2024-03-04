#
# Purpur Tentakel
# 02.03.2024
#

from enum import IntEnum, Enum


class PrintType(Enum):
    INFO = "INFO"
    ERROR = "ERROR"
    LOAD = "LOAD"
    GENERATE = "GENERATE"
    FINISHED = "FINISHED"


def my_print(type_: PrintType, message: str) -> None:
    print(f"{type_.value} | {message}")


class FileType(IntEnum):
    HEADER = 1
    SOURCE = 2


file_extension_lookup: dict[FileType, str] = {
    FileType.HEADER: ".hpp",
    FileType.SOURCE: ".cpp",
}


class CppType(IntEnum):
    USIZE = 1,
    STRING = 2,
    STRING_STATIC_CONST = 3,
    BOOL = 4,


field_type_lookup: dict[CppType, str] = {
    CppType.USIZE: "utl::usize",
    CppType.STRING: "std::string",
    CppType.STRING_STATIC_CONST: "static inline std::string const",
    CppType.BOOL: "bool",
}
passed_type_lookup: dict[CppType, str] = {
    CppType.USIZE: "utl::usize const",
    CppType.STRING: "std::string const&",
    CppType.STRING_STATIC_CONST: "std::string const&",
    CppType.BOOL: "bool const",
}
return_type_lookup: dict[CppType, str] = {
    CppType.USIZE: "utl::usize",
    CppType.STRING: "std::string",
    CppType.STRING_STATIC_CONST: "std::string",
    CppType.BOOL: "bool",
}


def print_enum(type_):
    for entry in type_:
        my_print(PrintType.INFO, f"{entry.name} : {entry.value}")