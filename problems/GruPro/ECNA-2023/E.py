def valid(s):
    last = 'X'
    if s[-1] != 'O':
        return False

    for c in s:
        if c != 'E' and c != 'O':
            return False
        if (c == last and last == 'O'):
            return False
        last = c

    return True


def bexp(a, p):
    if p == 0:
        return 1
    else:
        b = bexp(a, p // 2)
        if p % 2 == 0:
            return b * b
        else:
            return a * (b * b)


def main():
    powers = [0]
    cur = 1
    for i in range(48):
        powers.append(cur)
        cur *= 2

    s = input()
    if (not valid(s)):
        print("INVALID")
        return
    x, y, z = 0, 1, 1
    s = s[:-1]
    for c in s[::-1]:
        if c == 'O':
            y = y + bexp(3, z)
            z += 1
        else:
            x += 1
            y *= 2

    cur = bexp(2, x)
    z3 = bexp(3, z)
    # (2^(2k + x) - y) <= 3^z * 2^47
    # and z <= 50 and y <= 50 so 2^2k <= 2^147 + 50 <= 2^148  ==> k <= 75
    for k in range(0, 75 + 1):
        if (cur % z3) == (y % z3) and (((cur - y) // z3) not in powers):
            print((cur - y) // z3)
            return
        cur *= 4
    
main()
