def floatrange(a, b=None, c=1):
    if b == None:
        b = a
        a = 0.0
    ret = []
    while (a < b):
        ret.append(a)
        a += c
    return ret

if __name__ == '__main__':
    a = float(input())
    b = input() # enter "" (w/o quotes) for default b and c
    c = input() # enter "" (w/o quotes) for default c
    if b == '':
        print(floatrange(a))
    else:
        b = float(b)
        if c == '':
            print(floatrange(a, b))
        else:
            c = float(c)
            print(floatrange(a, b, c))
