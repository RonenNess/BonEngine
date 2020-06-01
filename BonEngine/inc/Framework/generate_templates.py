def generate_file(base_file_name, target_file_name, typename, from_classname, to_classname, other_classname):
    code = open(base_file_name, 'r').read()
    code = code.replace("__T__", typename)
    code = code.replace("other_" + from_classname, other_classname)
    code = code.replace(from_classname, to_classname)
    open(target_file_name, "w").write(code)

generate_file("__Point.h", "PointF.h", "float", "_Point_", "PointF", "PointI")
generate_file("__Point.h", "PointI.h", "int", "_Point_", "PointI", "PointF")
generate_file("__Rectangle.h", "RectangleF.h", "float", "_Rectangle_", "RectangleF", "RectangleI")
generate_file("__Rectangle.h", "RectangleI.h", "int", "_Rectangle_", "RectangleI", "RectangleF")