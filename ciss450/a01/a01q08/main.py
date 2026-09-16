# File :
# Author:

# matrix function here
def matrix(n, s, seperator=','):
    s = s.split(seperator)
    i = 0
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

# f function here
def f(xs):
    ret = []
    prev = xs[0]
    xs = xs[1:]
    for node in xs:
        ret.append([prev, node])
        prev = node

    return ret

# g function here
def g(xs):
    ret = [xs[0][0]]
    xs = xs[1:]
    for x in xs:
        ret.append(x[1])
        prev = x
    return ret

if __name__ == '__main__':
    option = int(input())
    if option == 1: # test f
        s = input() # enter "a,b,c,d,e" (without double-quotes)
        xs = s.split(",") # xs is ["a", "b", "c", "d", "e"]
        print(f(xs))
    else: # test g
        s = input() # enter "a,b,b,c,c,d,d,e" (without double-quotes)
        xs = matrix(2, s) # xs is [["a","b"],["b","c"],["c", "d"],["d", "e"]]
        print(g(xs))
