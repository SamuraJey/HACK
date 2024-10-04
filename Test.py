from Algo import *
import time

with open("random_strings.txt", 'r') as file:
    input = file.read().split()


rsults =[]
start = time.time()
for IFC_uid in input:
    # print(IFC_uid)
    rsults.append(algorithm(IFC_uid))
duration = (time.time() - start)*10**6

with open("python_result.txt", 'w') as file:
    file.write('\n'.join(map(lambda pair: f'{pair[0]}\n{bin(int(pair[1], base=16))[2:].rjust(22, '0')} -> {pair[1]}', zip(input, rsults))))
    file.write(f"\ntest duration: {duration:.4f}ns\ntime per string: {duration/len(input):.10f}ns")
