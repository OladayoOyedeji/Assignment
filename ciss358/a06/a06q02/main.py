INVALID = -1

def M(n, P, cut_cost):
    # table[i] = maximum total value for rod length i
    table = [INVALID] * (n + 1)
    table[0] = 0

    # action[i] = list of cut lengths that can be taken to achieve table[i]
    # (i.e., sticky notes)
    action = [[] for _ in range(n + 1)]

    # Build table[] and action[] bottom-up
    for i in range(1, n + 1):
        best = INVALID
        best_actions = []

        for cut in range(1, i + 1):
            val = table[i - cut] + P[cut]
            if cut != i: # cut == i means not cutting because it's the same length, so this is saying "only substract cut cost when making a cut"
                val -= cut_cost
            if val > best:
                best = val
                best_actions = [cut]
            elif val == best:
                best_actions.append(cut)

        table[i] = best
        action[i] = best_actions

    # build optimal cuttings bottom-up
    # cuttings[i] = set of tuples, each tuple is one optimal cutting for length 
    cuttings = [set() for _ in range(n + 1)]
    cuttings[0].add(())  # base case
    for i in range(1, n + 1):
        cur = set()
        for cut in action[i]:
            for tail in cuttings[i - cut]: # i - cut represents remaining rod length after making a cut of size cut from a rod of length i
                # keep each cutting in ascending order
                if len(tail) == 0 or cut <= tail[0]:
                    cur.add((cut,) + tail)
        cuttings[i] = cur

    # dictionary order across cuttings
    all_optimal_cuttings = [t for t in sorted(cuttings[n])]

    return table[n], all_optimal_cuttings


def main():
    P = [0, 1, 3, 4, 5, 6, 6, 9, 10, 11, 12, 13, 14]

    for n in range(0, 12):
        revenue, all_opt_cuttings = M(n, P, 1)
        print(f"{n}: revenue={revenue}, cuts={all_opt_cuttings}")


if __name__ == "__main__":
    main()
