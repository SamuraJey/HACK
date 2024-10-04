from Algo import *

with open("test/test_data.txt", 'r') as file, open("test/test_answers.txt", 'r') as file2:
    inp = file.read().split()
    ans = file2.read().split()

errors = []
for i in range(len(inp)):
    if ans[i] != algorithm(inp[i]):
        errors.append((ans[i], inp[i]))


with open("python/errors.txt", 'w') as file:
    if not errors:
        file.write("correct")
    else:
        file.write(f'errors found: {len(errors)}\n')
        for i in errors:
            file.write(f"{i[0]} {i[1]}")
    #file.write('\n'.join(map(lambda pair: f'{pair[0]}\n{bin(int(pair[1], base=16))[2:].rjust(22, '0')} -> {pair[1]}', zip(inp, results))))