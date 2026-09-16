# File :
# Author:

def matrix(n, s, seperator=','):
    print(s)
    s = s.split(seperator)
    print(s)
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

def move2(direction, m, target=' '):
    # To be completed
    for i in range(len(m)):
        for j in range(len(m)):
            if m[i][j] == ' ':
                if direction == 'N':
                    if i - 1 >= 0:
                        m[i][j] = m[i-1][j]
                        m[i-1][j] = ' '
                elif direction == "S":
                    if i + 1 < n:
                        print(m[i+1][j], m[i][j])
                        m[i][j] = m[i+1][j]
                        m[i+1][j] = ' '
                elif direction == "W":
                    if j - 1 >= 0:
                        m[i][j] = m[i][j-1]
                        m[i][j-1] = ' '
                elif direction == "E":
                    if j + 1 < n:
                        m[i][j] = m[i][j+1]
                        m[i][j+1] = ' '
                break
    return m

if __name__ == '__main__':
    direction = input("Direction: ") # for instance enter "N" (w/o quotes)
    s = input("Board: ") # for instance enter "1,2,3,4,5,6,7, ,8" (w/o
                # quotes)
    n = int(input("size: ")) # for instance enter 3
    m = matrix(n, s)
    print(m)
    target = input("Target: ") # for instance enter " " (w/o quotes)
                     # Enter "" (w/o quotes) for default case.
                     
    if target == '':
        print(move2(direction=direction, m=m))
    else:
        print(move2(direction=direction, m=m, target=target))
