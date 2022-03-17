from sorts import *
from time import process_time
import random

def generate_list(n):
    arr = [random.random() for x in range(n)]
    return arr

def measure_time(function, n):
    arr = generate_list(n)
    t1 = process_time() 
    function(arr)
    t2 = process_time() 
    return t2 - t1

def get_time():
    n = 1000
    print("Size of array: ", n)
    print("Bubble sort: ", "{0:.10f}".format(measure_time(bubble, n)))
    print("Inserion sort: ", "{0:.10f}".format(measure_time(insertion, n)))
    print("Quick sort: ", "{0:.10f}".format(measure_time(quick, n)))