# -*- coding: utf-8 -*-

"""
requirements: ply (Python Lex-Yacc)
"""

from ply import lex, yacc


class ParserError(Exception):
    pass


tokens = (
    "NULL",
    "BOOL",
    "NUMBER",
    "STRING",
)
literals = [',', ':', '[', ']', '{', '}']
t_ignore = ' \t'
t_NULL = r"\bnull\b"
t_STRING = r'"[^"]*"'


def t_newline(t):
    r""" \n+
    """
    t.lexer.lineno += len(t.value)


def t_error(t):
    raise ParserError('Illegal character "{}" at ({}, {})'.format(
        t.value[0], t.line, t.lexpos))


def t_BOOL(t):
    r""" \btrue\b | \bfalse\b
    """
    t.value = (t.value == "true")
    return t


def t_NUMBER(t):
    r""" \d+(e\d+)? | (0\.\d+(e\d+)? | [1-9]\d*\.\d+(e\d+)?)
    """
    val = t.value
    if '.' in val or 'e' in val:
        t.value = float(val)
    else:
        t.value = int(val)
    return t


lexer = lex.lex(debug=True)
valid = False


def p_object(p):
    """ object : '{' members '}'
               | '{' '}'
    """
    if len(p) == 4:
        p[0] = p[2]
    else:
        p[0] = {}
    global valid
    valid = True


def p_object_members(p):
    """ members : pair
                | pair ',' members
    """
    if len(p) == 2:
        p[0] = {p[1][0]: p[1][1]}
    elif len(p) == 4:
        p[0] = {p[1][0]: p[1][1]}
        p[0].update(p[3])
    global valid
    valid = False


def p_pair(p):
    """ pair : STRING ':' value
    """
    key = p[1]
    if key == 'null':
        key = None
    elif (not isinstance(key, (int, list, dict)) and
          key[0] == '"' and key[-1] == '"'):
        key = str(key[1: -1])
    p[0] = (key, p[3])
    global valid
    valid = False


def p_array(p):
    """ array : '[' elements ']'
              | '[' ']'
    """
    if len(p) == 4:
        p[0] = p[2]
    else:
        p[0] = []
    global valid
    valid = True


def p_array_elements(p):
    """ elements : value
                 | value ',' elements
    """
    if len(p) == 2:
        p[0] = [p[1]]
    elif len(p) == 4:
        p[0] = [p[1]] + p[3]
    global valid
    valid = False


def p_value(p):
    """ value : NULL
              | BOOL
              | NUMBER
              | STRING
              | array
              | object
    """
    value = p[1]
    if value == 'null':
        p[0] = None
    elif (not isinstance(value, (int, list, dict)) and
          value[0] == '"' and value[-1] == '"'):
        p[0] = str(value[1: -1])
    else:
        p[0] = value
    global valid
    valid = True


parser = yacc.yacc()


if __name__ == '__main__':
    import json

    def cmp(x, y):
        if isinstance(x, list):
            assert isinstance(y, list)
            for a, b in zip(x, y):
                cmp(a, b)
        elif isinstance(x, dict):
            assert isinstance(y, dict)
            for k, v in x.items():
                assert k in y
                cmp(v, y[k])
        else:
            assert not isinstance(y, (list, dict))
            assert x == y

    s = """
    {
        "a": 123,
        "b": 456,
        "hello": null,
        "arr": [1, "c", [4, "5"], {"d": "e"}, {}],
        "object": {
            "f": "fuck",
            "g": {"gg": ["ag", 33]},
            "h": []
        }
    }
    """
    result = parser.parse(s, debug=True)
    print(result)
    if valid:
        cmp(result, json.loads(s))
        print('SUCCESS')
