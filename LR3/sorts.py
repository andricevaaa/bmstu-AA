def bubble(arr):
    for i in range(len(arr)):
        for j in range(len(arr)-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

def insertion(arr):
    for i in range(len(arr)):
        current = arr[i]
        j = i
        while (arr[j-1] > current) and (j > 0):
            arr[j] = arr[j-1]
            j = j - 1
        arr[j] = current
    return arr

def quick(arr):
    if len(arr) <= 1:
        return arr
    else:
        q = arr[0]
        s_nums = []
        m_nums = []
        e_nums = []
        for n in arr:
            if n < q:
                s_nums.append(n)
            elif n > q:
                m_nums.append(n)
            else:
                e_nums.append(n)
        return quick(s_nums) + e_nums + quick(m_nums)