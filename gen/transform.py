import copy
import os


def jinja2_ord(ch):
    return ord(ch[0])


def enum_type(t):
    tmap = {"char": "byte",
            "uint8": "byte",
            "int16": "short",
            "uint16": "ushort",
            "int32": "int",
            "uint32": "uint"
            }
    return tmap[t["encoding_type"]]


def cs_type(t):
    # print(t)
    if t["type"] == "simple":
        tmap = {"uint8": "byte",
                "uint16": "Int16",
                "uint32": "UInt32",
                "uint64": "UInt64",
                "int8": "sbyte",
                "int16": "Int16",
                "int32": "Int32",
                "int64": "Int64",
                "float": "Single",
                "double": "Double",
                "char": "string"}
        return tmap[t["primitive_type"]]
    elif t["type"] == "composite":
        return t["name"] + "Type"
    elif t["type"] == "enum":
        return t["name"]
    return "Undefined"


def c_type(t):
    # print(t)
    if t["type"] == "simple":
        tmap = {"uint8": "uint8_t",
                "uint16": "uint16_t",
                "uint32": "uint32_t",
                "uint64": "uint64_t",
                "int8": "int8_t",
                "int16": "int16_t",
                "int32": "int32_t",
                "int64": "int64_t",
                "float": "float",
                "double": "double",
                "char": "char"}
        return tmap[t["primitive_type"]]
    elif t["type"] == "composite":
        return t["name"] + "Type"
    elif t["type"] == "enum":
        return t["name"]
    return "Undefined"


def c_type_decl(t):
    # print(t)
    if t["type"] == "simple":
        tmap = {"uint8": "uint8_t",
                "uint16": "uint16_t",
                "uint32": "uint32_t",
                "uint64": "uint64_t",
                "int8": "int8_t",
                "int16": "int16_t",
                "int32": "int32_t",
                "int64": "int64_t",
                "float": "float",
                "double": "double",
                "char": "char"}
        if t["primitive_type"] == "char" and t["length"] > 1:
            return "xroad_str_t"
        else:
            return tmap[t["primitive_type"]]
    elif t["type"] == "composite":
        return t["name"] + "Type"
    elif t["type"] == "enum":
        return t["name"]
    return "Undefined"



def has_optional(m):
    return has_optional_impl(m["fields"])


def has_optional_impl(fields):
    for f in fields:
        tp = f["type"]
        if "presence" in tp and tp["presence"] == "optional":
            return True
    return False


def has_groups(m):
    for f in m["fields"]:
        tp = f["type"]
        if tp["type"] == "group":
            return True
    return False


def has_data(m):
    for f in m["fields"]:
        tp = f["type"]
        if tp["type"] == "data":
            return True
    return False


def basename(f):
    return os.path.splitext(f)[0]


def pypack_fmt(t):
    if t["type"] == "simple":
        tmap = {"uint8": "B",
                "uint16": "H",
                "uint32": "I",
                "uint64": "Q",
                "int8": "b",
                "int16": "h",
                "int32": "i",
                "int64": "q",
                "float": "f",
                "double": "d"}
        if t["primitive_type"] == "char":
            return "{}s".format(t["length"])
        else:
            return tmap[t["primitive_type"]]
    return "c"


def get_type_size(t):
    if t["presence"] == "constant":
        return 0
    if t["primitive_type"] in ["uint8", "int8"]:
        return 1
    elif t["primitive_type"] in ["uint16", "int16"]:
        return 2
    elif t["primitive_type"] in ["uint32", "int32", "float"]:
        return 4
    elif t["primitive_type"] in ["uint64", "int64", "double"]:
        return 8
    elif "length" in t:
        return t["length"]


def get_type_null_value(t):
    tmap = {"int8": "SBE_INT8_NULL",
            "uint8": "SBE_UINT8_NULL",
            "int16": "SBE_INT16_NULL",
            "uint16": "SBE_UINT16_NULL",
            "int32": "SBE_INT32_NULL",
            "uint32": "SBE_UINT32_NULL",
            "int64": "SBE_INT64_NULL",
            "uint64": "SBE_UINT64_NULL",
            "float": "SBE_FLOAT_NULL",
            "double": "SBE_DOUBLE_NULL"}
    return tmap[t["primitive_type"]]


def lookup_type_with_semantic(semantic_name, types):
    for t in types:
        if t['semanticType'] == semantic_name:
            return t
    return None;


def mk_simple_type(elem):
    presence = elem.get("presence")
    simple_type = {"type": "simple", "name": elem.get("name"), "primitive_type": elem.get("primitiveType"),
                   "semanticType": elem.get("semanticType"),
                   "description": elem.get("description"), "presence": "required" if not presence else presence}
    if elem.text:
        simple_type["value"] = elem.text.strip()
    if "length" in elem.attrib:
        simple_type["length"] = int(elem.get("length"))
    if simple_type["presence"] == "optional":
        if "nullValue" in elem.attrib:
            simple_type["null_value"] = elem.get("nullValue")
        else:
            simple_type["null_value"] = get_type_null_value(simple_type)
    simple_type["size"] = get_type_size(simple_type)
    return simple_type


def transform(xml, xsd, env):
    env.filters["cs_type"] = cs_type
    env.filters["c_type"] = c_type
    env.filters["c_type_decl"] = c_type_decl
    env.filters["enum_type"] = enum_type
    env.filters["pypack_fmt"] = pypack_fmt
    env.filters["ord"] = jinja2_ord
    env.filters["basename"] = basename
    env.filters["has_optional"] = has_optional
    env.filters["has_groups"] = has_groups
    env.filters["has_data"] = has_data

    res = {"types": [], "messages": [], "groups": []}

    types = {"uint8":  {"type": "simple", "name": "uint8",  "primitive_type": "uint8", "size": 1, "length": 1, "presence": "required"},
             "uint16": {"type": "simple", "name": "uint16", "primitive_type": "uint16", "size": 2, "length": 1, "presence": "required"},
             "uint32": {"type": "simple", "name": "uint32", "primitive_type": "uint32", "size": 4, "length": 1, "presence": "required"},
             "uint64": {"type": "simple", "name": "uint64", "primitive_type": "uint64", "size": 8, "length": 1, "presence": "required"},
             "int8":   {"type": "simple", "name": "int8",  "primitive_type": "int8", "size": 1, "length": 1, "presence": "required"},
             "int16":  {"type": "simple", "name": "int16", "primitive_type": "int16", "size": 2, "length": 1, "presence": "required"},
             "int32":  {"type": "simple", "name": "int32", "primitive_type": "int32", "size": 4, "length": 1, "presence": "required"},
             "int64":  {"type": "simple", "name": "int64", "primitive_type": "int64", "size": 8, "length": 1, "presence": "required"},
             "float":  {"type": "simple", "name": "float", "primitive_type": "float", "size": 4, "length": 1, "presence": "required"},
             "double": {"type": "simple", "name": "double", "primitive_type": "double", "size": 8, "length": 1, "presence": "required"},
             "char":   {"type": "simple", "name": "char", "primitive_type": "char", "size": 1, "length": 1, "presence": "required"},
             "groupSizeEncoding": {"type": "builtin", "name": "groupSizeEncoding", "size": 4},
             "group": {"type": "group", "name": "group"},
             "data": {"type": "data", "name": "data"}}

    res["schema_id"] = xml.get("id")
    res["version"] = xml.get("version")
    res["package"] = xml.get("package")

    for child in xml:
        if child.tag == "types":
            process_types(child, types, res, None)
        elif child.tag == "{http://fixprotocol.io/sbe/rc4}message":
            msg = {"name": child.get("name"), "id": child.get("id"), "description": child.get("description", default=""),
                   "fields": []}
            offset = process_fields(res, types, msg, 0, child)
            msg["size"] = offset
            res["messages"].append(msg)
    return (res, env)

def process_types(tag, types, res, comp_res):
    offset = 0
    for t in tag:
        if t.tag == "enum":
            enum_typ = {"type": "enum", "name": t.get("name"),
                        "encoding_type": t.get("encodingType"), "description": t.get("description", default=""),
                        "size": 1, "length": 1, "entries": []}
            for entry in t:
                if entry.tag == "validValue":
                    enum_typ["entries"].append({"name": entry.get("name"), "value": entry.text,
                                                "description": entry.get("description", default="")})
            res["types"].append(enum_typ)
            if comp_res:
                comp_res["types"].append(enum_typ)
            if not comp_res:
                types[enum_typ["name"]] = enum_typ
        elif t.tag == "type":
            simple_type = mk_simple_type(t)
            if comp_res:
                simple_type["offset"] = offset
                comp_res["types"].append(simple_type)
                offset += simple_type["size"]
            if not comp_res:
                types[simple_type["name"]] = simple_type
                res["types"].append(simple_type)
        elif t.tag == "ref":
            ref_type = {"type": "ref", "name": t.get("name"), "ref": copy.copy(types[t.get("type")])}
            if not comp_res:
                res["types"].append(ref_type)
            else:
                comp_res["types"].append(ref_type)
        elif t.tag == "composite":
            composite = {"type": "composite", "name": t.get("name"), "description": t.get("description", default=""),
                         "types": []}
            offset = process_types(t, types, res, composite)
            composite["size"] = offset
            types[composite["name"]] = composite
            res["types"].append(composite)
            if comp_res:
                comp_res["types"].append(composite)
    return offset

def make_field_from_type(msg, offset, fld_name, comp_type):
    for t in comp_type["types"]:
        if t["type"] in ["simple", "enum"]:
            field = {"name": "{}_{}".format(fld_name, t["name"]), "id": 0, "type": t,
                    "description": t.get("description", ""), "offset": offset}
            msg["fields"].append(field)
            offset += t["offset"]
        elif t["type"] == "ref":
            ref_type = t["ref"]
            if ref_type["type"] != "composite":
                field = {"name": "{}_{}".format(fld_name, t["name"]), "id": 0, "type": ref_type,
                        "description": ref_type.get("description", ""), "offset": offset}
                msg["fields"].append(field)
                offset += ref_type["size"]
            else:
                offset = make_field_from_type(msg, offset, "{}_{}".format(fld_name, t["name"]), ref_type)
        else:
            offset = make_field_from_type(msg, offset, fld_name, t)
    return offset

def process_fields(res, types, msg, offset, child):
    for f in child:
        if f.tag == "field":
            field_type = types[f.get("type")]
            if field_type["type"] in ["simple", "enum"]:
                field = {"name": f.get("name"), "id": f.get("id"), "type": field_type,
                        "description": f.get("description", default=""), "offset": offset, "presence": f.get("presence")}
                msg["fields"].append(field)
                offset += field_type["size"]
            else:
                offset = make_field_from_type(msg, offset, f.get("name"), field_type)
        if f.tag == "data":
            field_type = types["data"]
            comp_type = types[f.get("type")]
            length_type = lookup_type_with_semantic('Length', comp_type['types'])
            data_type = lookup_type_with_semantic('data', comp_type['types'])
            field = {"name": f.get("name"), "id": f.get("id"), "type": field_type,
                     "dimension_type": {"type": types[f.get("type")], "length_type": length_type, "data_type": data_type},
                     "description": f.get("description", default=""), "offset": offset}
            msg["fields"].append(field)
        if f.tag == "group":
            field_type = types["group"]
            group = {"name": f.get("name"), "dimension_type": f.get("dimensionType"), "parent": msg,
                     "description": f.get("description", default=""), "type": field_type, "offset": offset, "fields": []}
            msg["fields"].append(group)
            grp_offset = process_fields(res, types, group, 0, f)
            group["size"] = grp_offset
            res["groups"].append(group)
    return offset


# vim:et:sts=4:sw=4
