def L(i,j):
    if i >= j:
        if (i==j):
            return 1
        else:
            return 0
    else:
        return max(L(i+1,j-1)+2*(s[i] == s[j]), L(i,j-1), L(i+1,j))
