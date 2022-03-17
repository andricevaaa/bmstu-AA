def get_mtx():
    print("Input first matrix: \n")
    mtx1 = read_matrix()
    print("")
    print("Input second matrix: \n")
    mtx2 = read_matrix()
    print("")
    return mtx1, mtx2

def read_matrix():
    row_num = int(input("Input number of rows: "))
    column_num = int(input("Input number of columns: "))
    print("")
    mtx = []
    for i in range(row_num):
        arr = list(int(i) for i in input("Input row: ").split())
        if (len(arr) != column_num):
            print("Не все столбцы заполнены! Ошибка!")
            i -= 1
        else:
            mtx.append(arr)
    return mtx