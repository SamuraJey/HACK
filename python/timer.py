from Algo import *
import time

with open("test/test_data.txt", 'r') as file:
    inp = file.read().split()

start = time.time()
for IFC_uid in inp:
    algorithm(IFC_uid)
duration = (time.time() - start)

with open("python/time.txt", 'w') as file:
    file.write(f"iterations: {len(inp)}\ntest duration: {duration:.4f}s\ntime per string: {duration/len(inp)*10**9:.10f}ns")
