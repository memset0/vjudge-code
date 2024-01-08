def get_attr_number(node):
    sum = len(node.attrib)
    for child in node:
        sum += get_attr_number(child)
    return sum