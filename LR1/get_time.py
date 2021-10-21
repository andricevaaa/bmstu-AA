from algorithms import *
from measure_time import *

def get_time():
    n = 100
    for i in range(5, 10):
        print("Length of string", i)
        print("Levenstein using recursion: ", "{0:.15f}".format(measure_time(lev_recursion, n, i)))
        print("Levenstein using recursion witch cache: ", "{0:.15f}".format(measure_time(rec_lev_cache, n, i)))
        print("Levenstein-Damau using recursion: ", "{0:.15f}".format(measure_time(lev_damau_recursion, n, i)))
        print("Levenstein-Damau method without using recursion (using matrix): ", "{0:.15f}".format(measure_time(lev_damau_matrix, n, i)))
