#!/usr/bin/env python3

from lxml import etree
import os.path
import sys
import getopt
import jinja2
import importlib
import pprint
import logging
import ast


def print_usage():
    print("Usage: gen.py -p <prot_descr> -x <xsd_schema> -r <transform_file> -t <template_file> -o <output_file> \n"
          "          -f <use_force> -e <env>\n" \
            "  prot_descr     - file with protocol description in xml format\n" \
            "  xsd_schema     - xsd schema for validation of protocol description file\n" \
            "  transform_file - python module, which is used for xml transformation\n" \
            "  template_file  - template file for code generation\n" \
            "  output_file    - file there new code will be generated\n" \
            "  env            - environment variables in python dict format (e.g. \"[{'var_name': 'value'}, ...]\")\n" \
            "  use_force      - force generation")


def is_generation_needed(schema, impl):
    return os.path.getmtime(schema) > os.path.getmtime(impl)


def validate(xmlparser, xmlfilename):
    with open(xmlfilename, "r") as f:
        return etree.fromstring(f.read(), xmlparser)


def dictlist(node):
    res = {}
    res[node.tag] = []
    xmltodict(node, res[node.tag])
    reply = {}
    reply[node.tag] = {'value': res[node.tag], 'attribs': node.attrib}
    return reply


def xmltodict(node, res):
    rep = {}

    if len(node):
        # n = 0
        for n in list(node):
            if n.tag is etree.Comment:
                continue
            rep[node.tag] = []
            value = xmltodict(n, rep[node.tag])
            if len(n):
                value = {'value': rep[node.tag], 'attributes': n.attrib}
                res.append({n.tag: value})
            else:
                res.append(rep[node.tag][0])
    else:
        value = {}
        value = {'value': node.text, 'attributes': node.attrib}
        res.append({node.tag: value})


def main(argc, argv):

    if argc < 9:
        print_usage()
        sys.exit(2)

    proto_file = ''
    schema_file = ''
    template_file = ''
    output_file = ''
    transform_file = ''
    forced_gen = False
    env = []

    try:
        opts, args = getopt.getopt(argv, "fp:x:r:t:o:e:", ["proto=", "schema=", "transform=", "template=", "output=", "env="])
    except getopt.GetoptError:
        print_usage()
        sys.exit(2)

    for opt, arg in opts:
        if opt == '-p':
            proto_file = arg
        if opt == '-x':
            schema_file = arg
        if opt == '-r':
            transform_file = arg
        if opt == '-t':
            template_file = arg
        if opt == '-o':
            output_file = arg
        if opt == '-f':
            forced_gen = True
        if opt == '-e':
            env = ast.literal_eval(arg)

    if (transform_file == ""):
        logging.error("no transformation module provided")
        print_usage()
        sys.exit(2)

    if not forced_gen and os.path.isfile(output_file) \
        and not is_generation_needed(proto_file, output_file) \
        and not is_generation_needed(template_file, output_file) \
        and not is_generation_needed(transform_file, output_file) \
        and not is_generation_needed(os.path.abspath(__file__), output_file):
            logging.info("no generation required for {0}".format(output_file))
            return

    os.path.join(os.path.dirname(schema_file))
    schema = etree.XMLSchema(file=schema_file, attribute_defaults=True)
    xmlparser = etree.XMLParser(schema=schema)
    proto_data = validate(xmlparser, proto_file)
    if proto_data is False:
        logging.error("{0} is not validated".format(proto_file))
        return

    sys.path.append(os.path.dirname(transform_file))
    # print("\n{0}\n".format(os.path.basename(transform_file)))
    tmod = importlib.import_module(os.path.basename(transform_file).split(".")[0])

    tmpl_loader = jinja2.FileSystemLoader(searchpath=os.path.dirname(template_file))
    tmpl_env = jinja2.Environment(loader=tmpl_loader, lstrip_blocks=True, trim_blocks=True)
    (tmpl_vars, tmpl_env) = tmod.transform(proto_data, schema, tmpl_env)
    tmpl_vars["env"] = env

    # print(json.dumps(tmpl_vars, sort_keys=True, indent=4))

    tmpl_file = tmpl_env.get_template(os.path.basename(template_file))
    for elem in proto_data.getiterator():
        if not hasattr(elem.tag, 'find'):
            continue  # (1)
        i = elem.tag.find('}')
        if i >= 0:
            elem.tag = elem.tag[i+1:]

    tmpl_file.stream(tmpl_vars).dump(output_file)
    # pp = pprint.PrettyPrinter(indent=4)
    # pp.pprint(tmpl_vars)

    logging.info("generated {0}".format(output_file))

if __name__ == "__main__":
    logging.basicConfig(format="%(levelname)s %(message)s")
    logging.getLogger().setLevel(logging.NOTSET)
    try:
        main(len(sys.argv), sys.argv[1:])
    except Exception as e:
        logging.exception("{0} failed".format(" ".join(sys.argv)))


# vim:et:sts=4:sw=4
