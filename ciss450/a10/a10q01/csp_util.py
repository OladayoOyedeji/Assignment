def evaluate(c, assignment):
    """
    Example:
    evaluate("A != B", [('A', 1), ('B', 2)]) -> True
    """
    for var, val in assignment:
        if isinstance(val, str):
            val = "'%s'" % val
        exec("%s = %s" % (var, val))
    return eval(c)


def evaluate2(c, assignment):
    """
    Example:
    evaluate2("A != B", [('A', 1), ('B', 2)]) -> True
    evaluate2("A != B", [('A', 1)]) -> True
    evaluate2("A != B", [('A', 1), ('C', 1)]) -> True
    """
    try:
        return evaluate(c, assignment)
    except NameError:
        return True


def is_consistent(csp, assignment):
    """
    Returns true if assignment is consistent, i.e., does not
    violate any constraint in the csp.
    """
    for c in csp.constraint.values():
        if evaluate2(c, assignment) == False:
            return False
    return True
