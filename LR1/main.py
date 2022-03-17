#Realisation of four algorithms: levenstein using recursion, levenstein using recursion with cache,
#levenstein-damau using recursion and levenstein-damau without recursion (using matrix)

from by_hand import *
from get_time import *

choice = 1

while choice:
    print("Menu: ")
    print("1 - enter by hand") 
    print("2 - compare time ")
    print("0 - exit \n")

    choice = int(input("Choice: "))
    print("")

    if choice == 1:
        by_hand()
    elif choice == 2:
        get_time()