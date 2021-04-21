print("Enter prime, a, b")

p = int(input())
a = int(input())
b = int(input())

Y = []
print("Y\tY^2\tY^2%{}".format(p))
for i in range(p):
    Y.append((i**2) % p)
    print("{}\t{}\t{}".format(i, i**2, (i**2) % p))

print("X\tX^3+{}X+{}\tX Val mod {}\n Y val 1\t Y val 2".format(a, b, p))
for i in range(p):
    tmp0 = ((i**3) + (a * i) + b)
    tmp1 = tmp0 % p
    if (tmp1 in Y):
        tmp = [j for j in range(p) if Y[j] == tmp1]
        print("{}\t{}\t{}\t{}\t{}".format(i, tmp0, tmp1, tmp[0], tmp[1]))
    else:
        print("{}\t{}\t{}\t{}\t{}".format(i, tmp0, tmp1, "NA", "NA"))
