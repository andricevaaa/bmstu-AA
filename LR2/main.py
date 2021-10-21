from algorithms import *
from in_mtx import *
from get_time import *

import numpy as np

def menu():
    choice = 1
    while choice:
        print("Menu: ")
        print("1 - multiply matrix") 
        print("2 - measure time")
        print("0 - exit \n")

        choice = int(input("Choice: "))
        print("")

        if choice == 1:
            mtx1, mtx2 = get_mtx()
            print("Standart multiplication: \n", np.matrix(standart_multiplication(mtx1, mtx2)))
            print("")
            print("Vinograd multiplication: \n", np.matrix(vinograd_multiplication(mtx1, mtx2)))
            print("")
            print("Vinograd optimized multiplication: \n", np.matrix(vinograd_opt_multiplication(mtx1, mtx2)))
        elif choice == 2:
                get_time()
        print("")

if __name__ == "__main__":
    menu()