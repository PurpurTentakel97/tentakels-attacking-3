#
# Purpur Tentakel
# 02.03.2024
#

import raw_field
import raw_config_file
import helper
import file
import enums


def _gen_top(entry: raw_field.RawField, indent: int) -> str:
    text: str = f"{helper.indent(indent)}class {entry.constants_class} final {helper.left_bracket}\n"
    text += f"{helper.indent(indent)}public:\n"
    text += f"{helper.indent(indent + 1)}friend struct {helper.config_io_name};\n\n"
    text += f"{helper.indent(indent)}private:\n"
    return text


def _gen_mid(indent: int) -> str:
    return f"\n{helper.indent(indent)}public:\n"


def _gen_bottom(indent: int) -> str:
    return f"{helper.indent(indent)}{helper.right_bracket};\n"


def _gen_class_strings(entries: tuple[raw_field.RawField], indent: int) -> dict[str, str]:
    # {"class_name": {
    #   "header": "",
    #   "fields" : "",
    #   "getter" : "",
    #   "setter" : "",
    # };
    classes: dict = dict()
    for entry in entries:
        if not entry.is_config:
            continue

        if entry.constants_class not in classes:
            classes[entry.constants_class] = dict()
            classes[entry.constants_class]["header"] = _gen_top(entry, indent)

        if "fields" not in classes[entry.constants_class]:
            classes[entry.constants_class]["fields"] = str()
        classes[entry.constants_class]["fields"] += entry.dump_field(indent + 1)

        if "getter" not in classes[entry.constants_class]:
            classes[entry.constants_class]["getter"] = str()
        classes[entry.constants_class]["getter"] += entry.dump_getter(indent + 1)

        if "setter" not in classes[entry.constants_class]:
            classes[entry.constants_class]["setter"] = str()
        classes[entry.constants_class]["setter"] += entry.dump_setter(indent + 1)

    output: dict[str, str] = dict()
    for class_ in classes:
        single_entry: dict = classes[class_]
        o: str = single_entry["header"]
        o += single_entry["fields"]
        o += _gen_mid(indent)
        o += single_entry["getter"] + '\n'
        o += single_entry["setter"]
        o += _gen_bottom(indent)
        output[class_] = o

    return output


def gen(entries: tuple[raw_field.RawField], classes: tuple[raw_config_file.RawConfigFile]) -> tuple[file.File]:
    strings: dict[str, str] = _gen_class_strings(entries, 1)
    files: list[file.File] = list()

    for s in strings:
        raw_file: raw_config_file.RawConfigFile = raw_config_file.raw_file_from_name(s, classes)
        f: file.File = file.File(raw_file.full_name(), enums.FileType.HEADER, raw_file.includes, raw_file.namespace,
                                 strings[s])
        files.append(f)

    return tuple(files)
