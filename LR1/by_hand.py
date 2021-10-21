from algorithms import *

def by_hand():
    str1 = str(input("Input first string: "))
    str2 = str(input("Input second string: "))
    len1 = len(str1)
    len2 = len(str2)
    print("")
    print("Levenstein using recursion:", lev_recursion(str1, str2, len1, len2))
    print("Levenstein using recursion witch cache:",  rec_lev_cache(str1, str2, len1, len2))
    print("Levenstein-Damau using recursion:", lev_damau_recursion(str1, str2, len1, len2))
    print("Levenstein-Damau method without using recursion (using matrix):",  lev_damau_matrix(str1, str2, len1, len2))
    print("")
    