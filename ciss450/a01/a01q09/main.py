# File :
# Author:

def mergesort(xs, verbose=False):
    # Put merge function here
    def mergesort_(xs, start, end, t, verbose=False):
        # To be completed
        t = []
        if verbose:
            print(xs[start:end])
        def merge(xs, i0, i1, i2):
            t = []
            i = i0
            j = i1
            while i < i1 or j < i2:
                if i >= i1:
                    t.append(xs[j])
                    j += 1
                elif j >= i2:
                    t.append(xs[i])
                    i += 1
                elif xs[i] < xs[j]:
                    t.append(xs[i])
                    i += 1
                elif xs[i] > xs[j]:
                    t.append(xs[j])
                    j += 1
                else:
                    t.append(xs[i])
                    t.append(xs[j])
                    i += 1
                    j += 1
            # print("temporary array: ", t, xs[i0:i2])
            # print("merged array: ", xs[:i0] + t + xs[i2:], xs)
            return xs[:i0] + t + xs[i2:]
        if end - start < 2:
            return xs
        else:
            mid = (end - start) // 2 + start
            
            xs = mergesort_(xs, start, mid, t, verbose)
            xs = mergesort_(xs, mid, end, t, verbose)
            
            return merge(xs, start, mid, end)
        
            
    t = [] # temporary array
    n = len(xs)
    print(n)
    return mergesort_(xs, 0, n, t, verbose)
    
if __name__ == '__main__':
    s = input() # for instance enter "51,32,1,23,47" (w/o
                # quotes) to sort [51, 32, 1, 23, 47]
    xs = [int(_) for _ in s.split(',') if _ != '']
    print(xs)
    xs = mergesort(xs, verbose=True)
    print(xs)
