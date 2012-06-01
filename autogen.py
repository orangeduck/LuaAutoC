import sys
import re

if len(sys.argv) != 2:
    print "Usage: python autogen.py <header.h>"
    
f = open(sys.argv[1])
text = f.read()
text = text.replace("\r","").replace("\n","")
f.close()

typedefs = re.findall(r"typedef struct \{.*?\} \w+;", text)
funcdefs = re.findall(r"[\w\*]+ \w+\(.*?\);", text)

print ""

for typedef in typedefs:
    match = re.search(r"typedef struct \{(.*)\} (\w+);", typedef);
    inner, ctype = match.groups()
    decl = inner.split(";")
    pairs = []
    for d in decl:
        in_match = re.search(r"\s*([\w\*]+)\s*(\w+)\s*", d)
        if in_match is not None: pairs.append(in_match.groups())
    print "lua_autostruct_add(%s);" % ctype
    for p in pairs: print "lua_autostruct_addmember(%s, %s, %s);" % (ctype, p[1], p[0])
    print ""

for funcdef in funcdefs:
    match = re.search("([\w\*]+) (\w+)\((.*?)\);", funcdef);
    ctype, fname, args = match.groups()
    pairs = []
    for a in args.split(","):
        in_match = re.search(r"\s*([\w\*]+)\s*(\w+)\s*", a)
        if in_match is not None: pairs.append(in_match.groups())
    voidstring = ""
    if ctype == "void": voidstring = "_void"
    fstring = "lua_autofunc_add_args%i%s(%s, %s" % (len(pairs), voidstring, fname, ctype)
    for p in pairs: fstring += ", %s" % p[0]
    fstring += ");"
    print fstring
    
print ""
