# -*- coding: utf-8 -*-


def x(xx):
    xxx = xx[0]
    xxxx = [0]
    xxxxx = len(xx)
    while xxx not in set(xxxx) and xxx < xxxxx:
        xxxx.append(xxx)
        xxx = xx[xxx]

    return len(xxxx[xxxx.index(xxx):])



if __name__ == '__main__':
    assert x([1, 2, 1]) == 2
    assert x([1, 2, 0]) == 3
    assert x([2, 4, 1, 10, 7, 8, 1, 8, 3, 0, 1]) == 6
