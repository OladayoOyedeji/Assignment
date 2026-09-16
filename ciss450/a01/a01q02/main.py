# File :
# Author:
def move(direction=None, m=None):
    # To be completed
    i = 0
    ret = []
    while i < len(m):
        if m[i] == ' ':
            if direction == 'left':
                ret = m[:i-1] + [' '] + [m[i-1]] + m[i+1:]
                
            elif direction == 'right':
                ret = m[:i] + [m[i + 1]] + [' '] + m[i+2:]
            else:
                raise ValueError("ERROR in move: invalid direction %s" % direction)
            break
        i += 1
    return ret
    
if __name__ == '__main__':
    direction = input() # for instance enter "right" (without quotes)
    s = input() # for instance enter "0342 8" (without quotes)
    m = list(s)
    print(move(direction=direction, m=m))
