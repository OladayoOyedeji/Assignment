import math

m, n = input().split()
m = int(m)
n = int(n)
color_photo = []

for i in range(m):
    lst = []
    for j in range(n):
        i = float(input())
        lst.append(i)
    
    color_photo.append(lst)

print(color_photo[m-1][n-1])
# j = 0
# for lst in color_photo:
#     print(j)
#     for i in lst:
#         print(i, end=" ")
#     print()
#     j = j + 1


min_ = math.inf
j = 0
table_lookup = []
for i in range(m):
    lst = []
    for j in range(n):
        lst.append(-1)
    
    table_lookup.append(lst)
    
def M(i, k):
    global color_photo
    if (i in [-1, n]):
        return math.inf
    if (k == m):
        return 0
    print()
    print(i, k, n, m, "m-k:", m-k)
    print()
    # for lst in color_photo:
    #     for j in lst:
    #         print(j, end=" ")
    #     print()
    if table_lookup[i+1][k+1] == -1:
        table_lookup[i+1][k+1] = M(i+1, k+1)
    if table_lookup[i][k+1] == -1:
        table_lookup[i][k+1] = M(i, k+1)
    if table_lookup[i-1][k+1] == -1:
        table_lookup[i-1][k+1] = M(i-1, k+1)
        
    return min(table_lookup[i+1][k+1], table_lookup[i][k+1], table_lookup[i-1][k+1]) + color_photo[k][i]



    
for i in range(n):
    if (table_lookup[i][1] == -1):
        table_lookup[i][1] = M(i, 1)
    M_ = color_photo[0][i] + table_lookup[i][1]
    print(M_)
    j = j+1
    if (M_ < min_):
        min_ = M_

print(min_)

for i in range(m-1, -1, -1):
    for j in range(n-1, -1, -1):
        x, y, z = 0, 0, 0
        table_lookup[i][j] = min(M_helper(i-1,j+1,table_lookup))
