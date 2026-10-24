N = int(input())
board = [[' '] * N for _ in range(N)]
solution = []

def attacking_pairs(m):
    count = 0
    for i in range(len(m)):
        for j in range(len(m)):
            if m[i][j] == 'Q':
                print("position:", i, j,  m[i][j])
                count += horiz_ap(m, i, j) + vert_ap(m, i, j) + diag_ap(m, i, j)
    print(count)
    return count

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
    
    for k in range(0, n):
        if m[i][k] == 'Q':
            count += 1
    print("horizontal:", count)
    return count

def vert_ap(m, i, j):
    n = len(m)
    count = 0

    for k in range(0, n):
        if m[k][j] == 'Q':
            count += 1
    print("vertical:", count)
    return count

def diag_ap(m, i, j):
    n = len(m)
    count = 0
    # for k, l in zip(range(i+1, n), range(j+1, n)):
    #     if (k < n and l < n):
    #         if m[k][l] == 'Q':
    #             count += 1
    #     else:
    #         break

    print(i, j, n, list(range(i-1, -1, -1)), list(range(j-1, -1, -1)))
    for k, l in zip(range(i-1, -1, -1), range(j-1, -1, -1)):
        print("pos: ", k, l, m[k][l])
        if (k >= 0 and l >= 0):
            if m[k][l] == 'Q':
                count += 1
        else:
            break

    # for k, l in zip(range(i+1, n), range(j-1, n, -1)):
    #     if k >= 0 and l < n:
    #         if m[k][l] == 'Q':
    #             count += 1
    #         else:
    #             break
    for k, l in zip(range(i-1, -1, -1), range(j+1, n)):
        print("pos: ", k, l, m[k][l])
        if k < n and l >= 0:
            if m[k][l] == 'Q':
                count += 1
            else:
                break
    print("diagonal:", count)
    return count

def attacking_pairs(m, i, j):
    count = 0
    print("position:", i, j,  m[i][j])
    count += horiz_ap(m, i, j) + vert_ap(m, i, j) + diag_ap(m, i, j)
    return count

def safe(row, col):
    return attacking_pairs(board, row, col) == 0

def solve(row):
    if row == N:
        solution.append(board.copy())
        return True
    for col in range(N):
        if safe(row, col):
            board[row][col] = 'Q'
            if solve(row + 1):
                solution.append(board.copy())
                return True
            board[row][col] = ' '
    return False


def fchc(board, i, j, maxtries=None):
    N = len(board)

    if maxtries == None:
        maxtries = N

    best_h = attacking_pairs(board, i, j)

    old_h = best_h
    good_board = [board]

    for i in range(maxtries):
        tpoints = points
        new_h = None
        new_board = None

        i, j = sorted(random.sample(range(N-1), 2))
        new_board = successor(board, i, j)

        if new_points != None:
            new_h = obj(new_board)

        if new_h != None:
            if new_h < best_h:
                best_h = new_h
                good_board = [new_board]
            elif new_h == best_h:
                good_board.append(new_board)
    if best_h != 0:
        return False
    else:
        return random.choice(sorted(good_board))

for i in range(N):
    solve(i)
# def
# print_board(solution)

def print_board(board):
    for i in board:
        for j in i:
            print('|',j, end='')
        print('|')
        for j in i:
            print('+-', end=' ')
        print('+')
    print()

for board in solution:
    print_board(board)
