def get_list():
    print("Input array: ")
    arr1 = list(int(i) for i in input().split())
    arr2 = arr1.copy()
    arr3 = arr1.copy()
    return arr1, arr2, arr3
