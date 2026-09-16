# File :
# Author:

# matrix function from earlier question here

# attacking_pairs function here
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

def horiz_ap(m, i, j):
    n = len(m)
    count = 0
    
    for k in range(j+1, n):
        if m[i][k] == 'Q':
            count += 1
    print("horizontal:", count)
    return count

def vert_ap(m, i, j):
    n = len(m)
    count = 0

    for k in range(i+1, n):
        if m[k][j] == 'Q':
            count += 1
    print("vertical:", count)
    return count

def diag_ap(m, i, j):
    n = len(m)
    count = 0

    for k, l in zip(range(i+1, n), range(j+1, n)):
        if (k < n and l < n):
            if m[k][l] == 'Q':
                count += 1
        else:
            break

    for k, l in zip(range(i+1, n), range(j-1, n, -1)):
        if k >= 0 and l < n:
            if m[k][l] == 'Q':
                count += 1
            else:
                break
    print("diagonal:", count)
    return count
    
def attacking_pairs(m):
    count = 0
    for i in range(len(m)):
        for j in range(len(m)):
            if m[i][j] == 'Q':
                print("position:", i, j,  m[i][j])
                count += horiz_ap(m, i, j) + vert_ap(m, i, j) + diag_ap(m, i, j)
    print(count)
    return count

if __name__ == '__main__':
    # For this:
    # +-+-+-+
    # |Q|Q| |
    # +-+-+-+
    # | | |Q|
    # +-+-+-+
    # | | | |
    # +-+-+-+
    s = input() # enter "Q,Q, , , ,Q, , , " (without double-quotes)
    n = int(input()) # enter 3
    m = matrix(n, s) # m is a 3-by-3 2D array
    print(m)
    print(attacking_pairs(m))
