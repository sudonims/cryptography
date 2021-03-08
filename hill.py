import numpy as np
n = int(input("Enter key 2 (2x2) or 3(3x3)"))

char_dec = lambda n: ord(n) - 97

key = [list(map(char_dec, input().split())) for i in range(n)]

n1 = int(input("Enter no rows in plain text"))
print("Input plain")

plain = [list(map(char_dec, input().split())) for i in range(n1)]

print()
encrypt = np.dot(key, plain) % 26
for i in encrypt:
    for j in i:
        print(chr(j + 97), end=" ")
    print()
print("encrypted", encrypt)

print("Use same to decrypt or use new matrix (0/1)")
a = int(input())

if (a == 1):
    encrypt = encrypt
else:
    encrypt = [list(map(char_dec, input().split())) for i in range(n)]
determinant = int(np.ceil(np.linalg.det(key))) if int(
    np.ceil(np.linalg.det(key))) > 0 else int(np.ceil(np.linalg.det(key))) + 26
determinant %= 26
inv_d = pow(int(determinant), -1, 26)
print("det", determinant, "Multiplicative inverse of determintant", inv_d)

adj_key = np.linalg.inv(key) * np.linalg.det(key)

for i in range(len(adj_key)):
    for j in range(len(adj_key[i])):
        adj_key[i][j] = int(round(adj_key[i][j]))
# adj_key = np.array(adj_key, dtype=int)
print("after cofactor and transpose then moddulo 26", adj_key)
adj_key %= 26
print(adj_key)
adj_key = adj_key * inv_d
print("after multiply inv_det then modulo 26", adj_key)
adj_key = adj_key % 26
print(adj_key)

decrypt = np.dot(adj_key, encrypt) % 26

for i in range(len(decrypt)):
    for j in range(len(decrypt[i])):
        decrypt[i][j] = round(decrypt[i][j])
print(decrypt)
