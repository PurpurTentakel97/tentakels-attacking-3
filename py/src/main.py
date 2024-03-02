#
# Purpur Tentakel
# 02.03.2024
#

import field
import LoadSave
import raw_entry

input_: dict = LoadSave.LoadJson()
entries: tuple[raw_entry.RawEntry] = raw_entry.load_raw_entries(input_)

for entry in entries:
    f: field.Field = field.Field(entry.prefix, entry.name, entry.type_, entry.value)

    print(f.dump_field(1))
    print(f.dump_getter(1))
    print(f.dump_setter(1))

    print(f"case ENUM::{entry.name.upper()}: return \"{entry.name.lower()}\";")
