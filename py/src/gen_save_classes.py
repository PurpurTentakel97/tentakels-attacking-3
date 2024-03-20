#
# Purpur Tentakel
# 16.03.2024
#

import raw_field
import raw_file
import file
import helper
import enums


def _gen_top(entry: raw_field.RawSaveField, indent: int) -> str:
    text: str = f"{helper.indent(indent)}class {entry.class_name} final {{\n"
    text += f"{helper.indent(indent)}private:\n"
    return text


def _gen_bottom(indent: int) -> str:
    return f"{helper.indent(indent)}}};\n"


def _gen_class_strings(fields: tuple[raw_field.RawSaveField], files: tuple[raw_file.RawFile], indent: int) -> dict[
    str, str]:
    classes: dict = dict()
    for field in fields:
        if field.class_name not in classes:
            classes[field.class_name] = dict()
            classes[field.class_name]["header"] = _gen_top(field, indent)

        if "fields" not in classes[field.class_name]:
            classes[field.class_name]["fields"] = str()
        classes[field.class_name]["fields"] += field.dump_field(indent + 1)

        if "getter" not in classes[field.class_name]:
            classes[field.class_name]["getter"] = str()
        classes[field.class_name]["getter"] += field.dump_getter(indent + 1)

        if "setter" not in classes[field.class_name]:
            classes[field.class_name]["setter"] = str()
        classes[field.class_name]["setter"] += field.dump_setter(indent + 1)

    output: dict[str, str] = dict()
    for class_ in classes:
        single_entry: dict = classes[class_]
        o: str = single_entry["header"]
        o += single_entry["fields"]
        o += f"\n{helper.indent(indent)}public:\n"
        o += single_entry["getter"] + '\n'
        o += single_entry["setter"]
        o += _gen_bottom(indent)
        output[class_] = o

    return output


def gen(fields: tuple[raw_field.RawSaveField], files: tuple[raw_file.RawFile]) -> tuple[file.File]:
    class_strings: dict[str, str] = _gen_class_strings(fields, files, 1)
    final_files: list[file.File] = list()

    for s in class_strings:
        r_f: raw_file.RawFile = raw_file.raw_file_from_name(s, files)
        f: file.File = file.File(r_f.full_name(), r_f.type_, r_f.includes, r_f.forward_declarations, r_f.namespace,
                                 class_strings[s])
        final_files.append(f)

    return tuple(final_files)
