def ex01_work(xs, offset):
    count = 0
    for i in range(len(xs)-offset):
        prev = xs[i]
        next = xs[i+offset]
        if(prev < next):
            count = count + 1
    return count

def ex01():
    with open('../input/01', 'r') as fd:
        inp = list(map(lambda x: int(x), fd.read().splitlines()));
        print("Day 01:", ex01_work(inp, 1), ex01_work(inp, 3))

ex01();
