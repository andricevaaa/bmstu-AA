from algorithms import *
from time import process_time
import random

def generate_mtx(n):
    mtx = [[random.random() for x in range(n)] for y in range(n)]
    return mtx

def measure_time(function, n):
    mtx1 = generate_mtx(n)
    mtx2 = generate_mtx(n)
    t1 = process_time() 
    function(mtx1, mtx2)
    t2 = process_time() 
    return t2 - t1

def get_time():
    n = 300
    print("Size of matrix: ", n)
    print("Standard multiplication: ", "{0:.6f}".format(measure_time(standart_multiplication, n)))
    print("Vinograd multiplication: ", "{0:.6f}".format(measure_time(vinograd_multiplication, n)))
    print("Vinograd optimized multiplication: ", "{0:.6f}".format(measure_time(vinograd_opt_multiplication, n)))