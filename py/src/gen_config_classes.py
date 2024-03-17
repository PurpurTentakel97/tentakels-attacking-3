#
# Purpur Tentakel
# 02.03.2024
#

import raw_field
import raw_file
import helper
import file
import enums


def _gen_top(entry: raw_field.RawField, indent: int) -> str:
    text: str = f"{helper.indent(indent)}class {entry.class_name} final {{\n"
    text += f"{helper.indent(indent)}public:\n"
    text += f"{helper.indent(indent + 1)}friend struct {helper.config_io_name};\n"
    text += f"{helper.indent(indent + 1)}friend struct app::AppContext;\n\n"
    text += f"{helper.indent(indent)}private:\n"
    return text


def _gen_mid(indent: int) -> str:
    return f"\n{helper.indent(indent)}public:\n"


def _gen_bottom(indent: int) -> str:
    return f"{helper.indent(indent)}}};\n"


def _gen_class_strings(entries: tuple[raw_field.RawField], indent: int) -> dict[str, str]:
    classes: dict = dict()
    for entry in entries:
        if entry.class_name not in classes:
            classes[entry.class_name] = dict()
            classes[entry.class_name]["header"] = _gen_top(entry, indent)

        if "fields" not in classes[entry.class_name]:
            classes[entry.class_name]["fields"] = str()
        classes[entry.class_name]["fields"] += entry.dump_field(indent + 1)

        if "getter" not in classes[entry.class_name]:
            classes[entry.class_name]["getter"] = str()
        classes[entry.class_name]["getter"] += entry.dump_getter(indent + 1)

        if "setter" not in classes[entry.class_name]:
            classes[entry.class_name]["setter"] = str()
        classes[entry.class_name]["setter"] += entry.dump_setter(indent + 1)

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


def gen(entries: tuple[raw_field.RawField], classes: tuple[raw_file.RawFile]) -> tuple[file.File]:
    strings: dict[str, str] = _gen_class_strings(entries, 1)
    files: list[file.File] = list()

    for s in strings:
        r_f: raw_file.RawFile = raw_file.raw_file_from_name(s, classes)
        f: file.File = file.File(r_f.full_name(), enums.FileType.HEADER, r_f.includes,
                                 r_f.forward_declarations, r_f.namespace, strings[s])
        files.append(f)

    return tuple(files)
