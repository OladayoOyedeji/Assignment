import math

x = input()
z = input()

copy, replace, delete, insert, twiddle, kill = map(int, input().split())

def edit_distance(x, z, i, j):
    if i < 0 or j < 0:
        return math.inf
    if i == 0 and j == 0:
        if x[i] == z[j]:
            return min(copy, (insert + delete))
        else:
            return min(replace, (insert + delete))
    elif i == 0:
        return edit_distance(x, z, i, j-1) + insert
    elif j == 0:
        return edit_distance(x, z, i-1, j) + delete
    else:
        D1 = math.inf
        D2 = math.inf
        kill_now = 0
        if x[i-1] == z[j] and x[i] == z[j-1]:
            print(x[i-1], z[j-1], x[i], z[j])
            D1 = edit_distance(x, z, i-2, j-2) + twiddle
        if x[i] == z[j]:
            D2 = edit_distance(x, z, i-1, j-1) + copy
        else:
            D2 = edit_distance(x, z, i-1, j-1) + replace
        return min(D1, D2, edit_distance(x, z, i, j-1) + insert, \
                   edit_distance(x, z, i-1, j) + delete) # + kill_now

j = len(z)-1
for i in range(len(x)):
    print("i: ", i, "min_dist", edit_distance(x, z, i, j))
