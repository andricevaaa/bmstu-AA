def standart_multiplication(mtx1, mtx2):
    if len(mtx2) != len(mtx1[0]):
        print("Size error!")
        return -1
    else:
        n = len(mtx1)
        q = len(mtx2[0])
        m = len(mtx1[0])
        mtx3 = [[0] * q for i in range(n)]

        for i in range(0, n):
            for j in range(0, q):
                for k in range(0, m):
                    mtx3[i][j] = mtx3[i][j] + mtx1[i][k] * mtx2[k][j]
    return mtx3


def vinograd_multiplication(mtx1, mtx2):
    if len(mtx2) != len(mtx1[0]):
        print("Size error!")
        return -1
    else:
        m = len(mtx1)
        n = len(mtx1[0])
        q = len(mtx2[0])
        mtx3 = [[0] * q for i in range(m)]

        row = [0] * m
        for i in range(0, m):
            for j in range(0, n // 2, 1):
                row[i] = row[i] + mtx1[i][2 * j] * mtx1[i][2 * j + 1]

        col = [0] * q
        for j in range(0, q):
            for i in range(0, n // 2, 1):
                col[j] = col[j] + mtx2[2 * i][j] * mtx2[2 * i + 1][j]

        for i in range(0, m):
            for j in range(0, q):
                mtx3[i][j] = -row[i] - col[j]
                for k in range(0, n // 2, 1):
                    mtx3[i][j] = mtx3[i][j] + (mtx1[i][2 * k + 1] + mtx2[2 * k][j]) * (mtx1[i][2 * k] + mtx2[2 * k + 1][j])

        if n % 2 == 1:
            for i in range(0, m):
                for j in range(0, q):
                    mtx3[i][j] = mtx3[i][j] + mtx1[i][n - 1] * mtx2[n - 1][j]

    return mtx3


def vinograd_opt_multiplication(mtx1, mtx2):
    if len(mtx2) != len(mtx1[0]):
        print("Size error!")
        return -1
    else:
        m = len(mtx1)
        n = len(mtx1[0])
        q = len(mtx2[0])
        mtx3 = [[0] * q for i in range(m)]

        row = [0] * m
        for i in range(0, m):
            for j in range(1, n, 2):
                row[i] -= mtx1[i][j] * mtx1[i][j - 1]

        col = [0] * q
        for j in range(0, q):
            for i in range(1, n, 2):
                col[j] -= mtx2[i][j] * mtx2[i - 1][j]

        flag = n % 2
        for i in range(0, m):
            for j in range(0, q):
                mtx3[i][j] = row[i] + col[j]
                for k in range(1, n, 2):
                    mtx3[i][j] += (mtx1[i][k - 1] + mtx2[k][j]) * (mtx1[i][k] + mtx2[k - 1][j])
                if (flag):
                    mtx3[i][j] += mtx1[i][n - 1] * mtx2[n - 1][j]
    return mtx3