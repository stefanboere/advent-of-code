from enum import Enum

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


class Direction(Enum):
    Forward = 1
    Up = 2
    Down = 3

def ex02_parse(ln):
    (x,y) = ln.split(' ', 1)
    directions={
        "forward" : Direction.Forward,
        "up": Direction.Up,
        "down": Direction.Down
    }
    return (directions.get(x), int(y))

def ex02a_work(xs):
    depth = 0;
    hor = 0;
    for (dir, x) in xs:
        if dir == Direction.Forward:
            hor = hor + x
        elif dir == Direction.Up:
            depth = depth - x
        elif dir == Direction.Down:
            depth = depth + x
    return depth * hor

def ex02b_work(xs):
    depth = 0;
    hor = 0;
    aim = 0
    for (dir, x) in xs:
        if dir == Direction.Forward:
            depth = depth + x * aim
            hor = hor + x
        elif dir == Direction.Up:
            aim = aim - x
        elif dir == Direction.Down:
            aim = aim + x
    return depth * hor


def ex02():
    with open('../input/02', 'r') as fd:
        inp = list(map(ex02_parse, fd.read().splitlines()));
        print("Day 02:", ex02a_work(inp), ex02b_work(inp))

ex02()

