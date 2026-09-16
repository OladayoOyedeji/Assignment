# File   : main.py
# Author :

def matrix(n, s, seperator=','):
    
    s = s.split(seperator)
    
    i = 0
    j = 0
    ret = []
    l = []
    
    while len(s) != 0:
        if i == n:
            ret.append(l)
            l = []
            i = 0
        l.append(s[0])
        s = s[1:]
        i += 1
    ret.append(l)
    return ret

if __name__ == '__main__':
    n = int(input())
    s = input()

    seperator = input()

    if seperator == '':
        print(matrix(n=n, s=s))
    else:
        print(matrix(n=n, s=s, seperator=seperator))
