// случайным образом заполняется матрица (2х3)
// в массив сохраняется сумма четных эл-тов каждой строки

#include <vector>
#include <iostream>
#include <random>

// === матрица ===
//     1 2 3
//     7 5 8
// ===============

int main(int argc, char *argv[])
{
    std::vector<std::vector<int>> matrix;       // 1
    int num;                                    // 2
    int rng = 10;                               // 3
    int n = 2;                                  // 4
	int m = 3  									// 5

    for (int i = 0; i < n; i++)              	// 6
    {
        std::vector<int> row;                   // 7
        for (int j = 0; j < m; j++)          	// 8
        {
            num = rand() % rng;                 // 9
            row.push_back(num);                 // 10
        }
        matrix.push_back(row);                  // 11
    }
	
	std::vector<int> v_sum;       				// 12
    for (int i = 0; i < n; i++)              	// 13
    {
		int sum = 0;                         	// 14
        for (int j = 0; j < m; j++)             // 15
        {
			if (!(matrix[i][j] % 2))            // 16            
				sum += matrix[i][j];            // 17
        }
		v_sum.push_back(sum);                   // 18
    }   
    return 0;
}

