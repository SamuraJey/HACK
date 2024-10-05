from Algo import *
import time
from multiprocessing import Pool

def process_line(IFC_uid):
    algorithm(IFC_uid)

if __name__ == "__main__":
    with open("test/test_data_2gb.txt", 'r') as file:
        inp = file.read().split()

    start = time.perf_counter()
    
    with Pool() as pool:
        pool.map(process_line, inp)
    
    duration = (time.perf_counter() - start)

    with open("python/time_python_2gb.txt", 'w') as file:
        file.write(f"iterations: {len(inp)}\ntest duration: {duration:.4f}s\ntime per string: {duration/len(inp)*10**9:.10f}ns")
