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
    USIZE_STATIC_CONSTEXPR = 5,
    FLOAT = 6,
    PROBABILITY = 7,


field_type_lookup: dict[CppType, str] = {
    CppType.USIZE: "utl::usize",
    CppType.STRING: "std::string",
    CppType.STRING_STATIC_CONST: "static inline std::string const",
    CppType.BOOL: "bool",
    CppType.USIZE_STATIC_CONSTEXPR: "static inline utl::usize constexpr",
    CppType.FLOAT: "float",
    CppType.PROBABILITY : "utl::Probability",
}
passed_type_lookup: dict[CppType, str] = {
    CppType.USIZE: "utl::usize const",
    CppType.STRING: "std::string const&",
    CppType.STRING_STATIC_CONST: "std::string const&",
    CppType.BOOL: "bool const",
    CppType.USIZE_STATIC_CONSTEXPR: "utl::usize const",
    CppType.FLOAT: "float const",
    CppType.PROBABILITY : "utl::Probability const",
}
return_type_lookup: dict[CppType, str] = {
    CppType.USIZE: "utl::usize",
    CppType.STRING: "std::string",
    CppType.STRING_STATIC_CONST: "std::string",
    CppType.BOOL: "bool",
    CppType.USIZE_STATIC_CONSTEXPR: "utl::usize",
    CppType.FLOAT: "float",
    CppType.PROBABILITY : "utl::Probability",
}
load_function_lookup: dict[CppType, str] = {
    CppType.USIZE: "LoadUSize",
    CppType.STRING: "LoadString",
    CppType.STRING_STATIC_CONST: "LoadString",
    CppType.BOOL: "LoadBool",
    CppType.USIZE_STATIC_CONSTEXPR: "LoadUSize",
    CppType.FLOAT: "LoadFloat",
    CppType.PROBABILITY : "LoadUSize",
}
load_type_lookup:dict[CppType, str] = {
    CppType.USIZE: "utl::usize",
    CppType.STRING: "std::string",
    CppType.STRING_STATIC_CONST: "std::string",
    CppType.BOOL: "bool",
    CppType.USIZE_STATIC_CONSTEXPR: "utl::usize",
    CppType.FLOAT: "float",
    CppType.PROBABILITY : "utl::usize",
}


def print_enum(type_):
    for entry in type_:
        my_print(PrintType.INFO, f"{entry.name} : {entry.value}")
