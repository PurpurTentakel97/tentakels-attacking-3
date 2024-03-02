#
# Purpur Tentakel
# 02.03.2024
#

import field
import enums

f: field.Field = field.Field("m_", "my_value", enums.CppType.STRING, "v0.1.5.7")
f2: field.Field = field.Field("m_", "my_other_value", enums.CppType.STRING_STATIC_CONST, "v0.1.5.7")
f3: field.Field = field.Field("m_", "my_third_value", enums.CppType.BOOL, "false")

print(f.dump_field(1))
print(f.dump_getter(1))
print(f.dump_setter(1))

print(f2.dump_field(1))
print(f2.dump_getter(1))
print(f2.dump_setter(1))

print(f3.dump_field(1))
print(f3.dump_getter(1))
print(f3.dump_setter(1))
