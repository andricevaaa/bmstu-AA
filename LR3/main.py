from in_func import *
from sorts import *
from measure_time import *

def menu():
    choice = 1
    while choice:
        print("Menu: ")
        print("1 - sort list") 
        print("2 - measure time")
        print("0 - exit \n")

        choice = int(input("Choice: "))
        print("")

        if choice == 1:
            arr1, arr2, arr3 = get_list()
            print("Bubble sort: ", bubble(arr1))
            print("")
            print("Insertion sort: ", insertion(arr2))
            print("")
            print("Quick sort: ", quick(arr3))
        elif choice == 2:
                get_time()
        print("")

if __name__ == "__main__":
    menu()