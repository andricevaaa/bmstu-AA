#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "matrix.h"
#include <ctime>
#include <utility>
#include <chrono>
using namespace std;

using namespace std::chrono;

//рекурсивный алгоритм полного обхода
static int ss(0);
void brute_force(Matrix &D, vector<int> &min_path, int &min_d, vector<int> &cur_path, vector<bool> &visited, int &cur_len);

pair<int, vector<int> > brute_force_find(Matrix D)
{
    int n = D.rows();
    vector<bool> visited(n, 0);
    vector<int> cur_path;
    vector<int> min_path;
    int cur_len = 0;
    int min_path_len = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        cur_path.clear();
        cur_path.push_back(i);
        fill(visited.begin(), visited.end(), 0);
        visited[i] = 1;
        cur_len = 0;
        brute_force(D, min_path, min_path_len, cur_path, visited, cur_len);
    }
    return pair<int, vector<int>>(min_path_len, min_path);
}


void brute_force(Matrix &D, vector<int> &min_path, int &min_d, vector<int> &cur_path, vector<bool> &visited, int &cur_len) {
    size_t M = D.cols();
    if (cur_path.size() == M) {
        ss++;
        int tmp = D[cur_path.back()][cur_path[0]];
        if (cur_len + tmp < min_d)
        {
            min_path = cur_path;
            min_d = cur_len + tmp;
        }
        return;
    }
    for (size_t i = 0; i < M; i++) {
        if (!visited[i])
        {
           int tmp = D[cur_path.back()][i];
           if (cur_len + tmp > min_d)
               continue;
           cur_len += tmp;
           cur_path.push_back(i);
           visited[i] = 1;
           brute_force(D, min_path, min_d, cur_path, visited, cur_len);
           visited[i] = 0;
           cur_path.pop_back();
           cur_len -= tmp;
        }
    }
}

// Муравьиный алгоритм
pair<int, vector<int>> AntAlgorithm(Matrix D, const int Tmax, const double alpha, const double ro){
    const int teta_beg = 10;
    const int teta_min = 5;
    const size_t M = D.cols(); //количество вершин
    const double Q = D.avg() * M; //примерное значение длины пути
    const double betta = 1 - alpha;

    Matrix Attr(M, M); //присваивание видимости
    for (size_t i = 0; i < D.rows(); i++){
        for (size_t j = 0; j < D.cols(); j++) {
            double tmp = 1/D[i][j];
            Attr[i][j] = tmp;
            Attr[j][i] = tmp;
        }
    }

    Matrix Teta(M, M, teta_beg); //феромоны
    Matrix Delta_Teta(M, M); //феромоны на текущем шаге

    int Lmin = -1; //длина кратчайшего маршрута
    vector<int> Lp; // кратчайший маршрут
    vector<double> P(M, 0.0); //вероятности

    double random_res;
    // цикл по времени жизни колонии
    for (int t = 0; t < Tmax; t++) {
        Delta_Teta.zero();
        //цикл по всем муравьям
        for (size_t k = 0; k < M; k++) {
            vector<int> cur_path;
            cur_path.push_back(k);
            int cur_path_length = 0;
            int i = k;
            //строим маршрут
            while (cur_path.size() < M) {
                vector<int> not_visited;
                // поиск всех непосещенных вершин
                bool nv = true;
                for (size_t i = 0; i < M; i++) {
                    nv = true;
                    for (size_t j = 0; j < cur_path.size(); j++) {
                        if ((int)i == cur_path[j]) nv = false;
                    }
                    if (nv)
                        not_visited.push_back(i);
                }

                for (size_t j = 0; j < M ; j++){
                    P[j] = 0.0;
                }
                // посчитаем вероятности
                for (size_t j = 0; j < not_visited.size(); j++) {
                    if (D[i][not_visited[j]]) {
                        double sum = 0;
                        for (auto n: not_visited) {
                            sum += pow(Teta[i][n], alpha) * pow(Attr[i][n], betta);
                        }
                        P[j] = pow(Teta[i][not_visited[j]], alpha) * pow(Attr[i][not_visited[j]], betta)/sum;
                    }
                    else {
                        P[j] = 0;
                    }
                }
                //бросается случайное число для выбора муравья
                random_res  = (rand() % 100) / 100.0;
                // подсчитаем куда мы попали
                int best_p = 0;
                double sum_p = 0;
                for (size_t s = 0; s < M; s++) {
                    sum_p += P[s];
                    if(random_res < sum_p)
                    {
                        best_p = s;
                        break;
                    }
                }
                // добавим новый город в путь
                int new_town = not_visited[best_p];
                cur_path.push_back(new_town);
                cur_path_length += D[i][new_town];

                //обновим феромон на ребре
                Delta_Teta[i][new_town] += Q/cur_path_length;

                i = new_town; // дальше продолжим путь из этого города
                not_visited.erase(not_visited.begin()+best_p);
            }
            // конец построения маршрута
            // осталось только добавить путь от последнего города к начальному
            // это завершит цикл
            cur_path_length += D[cur_path[cur_path.size()-1]][k];
            // проверим не каратчайший ли это путь
            if (Lmin == -1 || cur_path_length < Lmin){
                Lmin = cur_path_length;
                Lp = cur_path;
            }
        }
        // конец цикла по муравьям
        //теперь чатсь феромона должна испариться
        for (size_t ii = 0; ii < M; ii++) {
            for (size_t jj = 0; jj < M; jj++) {
                Teta[ii][jj] = Teta[ii][jj] * (1.0 - ro) + Delta_Teta[ii][jj];
                if (Teta[ii][jj] < teta_min){
                    Teta[ii][jj] = teta_min;
                }
            }
        }
    }
    // конец цикла по времени
    return pair<int, vector<int>>(Lmin, Lp);
}

void print_res(pair<int, vector<int>> results){
    cout << "\nMin path length = " << results.first << ";\nMin path is: ";
    for (int i = 0; i < results.second.size(); i++) {
        cout << results.second[i] << " ";
    }
    cout <<" \n";
}

int main()
{

//    setbuf(stdout, NULL);
//    Matrix M(12, 12);
//    M.make_rand();
//    M.print();

//    double **ptr;
//    ptr = new double*[1000];//создание
//    for(int i = 0; i < 1000; i++)
//        ptr[i]=new double[4];

//    pair<int, vector<int>> results = brute_force_find(M);
//    int ideal_len = results.first;

//    int i = 0;
//    int best1, best2;
//    for (double ro = 0; ro <= 1; ro += 0.25)
//    {
//        for (double alpha = 0; alpha <= 1; alpha += 0.25)
//        {
//            for (int t = 10; t <= 330; t+= 40)
//            {
//                double dif = 0;
//                for (auto i = 0; i < 2; i++)
//                {
//                    pair<int, vector<int>> results = AntAlgorithm(M, t, alpha, ro);
//                    if (i == 1)
//                        best1 = abs(results.first - ideal_len);
//                    else
//                        best2 = abs(results.first - ideal_len);
//                }
//                dif = best1;
//                if (best2 < best1)
//                    dif = best2;
//                printf("%3f, %3f, %5d, %3f\n", ro, alpha, t, dif);
//                ptr[i][0] = ro; ptr[i][1] = alpha; ptr[i][2] = t; ptr[i][3] = dif;
//                i++;
//            }

//        }
//    }

//    for(int i = 0; i < 999; i++){
//        for(int j = i + 1; j < 1000; j++){
//            if (ptr[i][3] > ptr[j][3]){
//                double *tmp =new double[4];
//                tmp = ptr[i];
//                ptr[i] = ptr[j];
//                ptr[j] = tmp;
//            }
//        }
//    }

//    for(int i = 0; i < 1000; i++){
//        for(int j = 0; j < 4; j++){
//            printf("%f ", ptr[i][j]);
//        }
//        printf("\n");
//    }


//    FILE *f = fopen("time.txt", "w");
//    fprintf(f,"%5s,%10s,%10s,%10s\n", "N" , "1", "2", "-");
//    printf("%5s,%10s,%10s,%10s\n", "N" , "1", "2", "-");
//    std::clock_t time = 0;
//    int repeat = 10;
//    int start = 2;
//    int end = 14;
//    int step = 1;
//    high_resolution_clock::time_point t1, t2;

//    for (int i = start; i < end; i+=step)
//    {
//        fprintf(f, "%5d,", i);
//        printf("%5d,", i);
//        Matrix M(i,i);
//        M.make_rand();
//        //M.print();

//        time = 0;
//        for (int j = 0; j < repeat ; j++)
//        {
//            std::clock_t start = std::clock();
//            t1 = high_resolution_clock::now();
//            pair<int, vector<int>> results = brute_force_find(M);
//            t2 = high_resolution_clock::now();
//            std::clock_t end = std::clock();
////            time += end - start;
//            time += duration_cast<microseconds>(t2 - t1).count();
//            //printf("brute_force ");
//            //print_res(results);
//        }
//        printf("%10d,", time/repeat);
//        fprintf(f,"%10d,", time/repeat);
//        time = 0;
//        for (int j = 0; j < repeat ; j++)
//        {
//            std::clock_t start = std::clock();
//            t1 = high_resolution_clock::now();
//            pair<int, vector<int>> results = AntAlgorithm(M, 350, 0.75, 0.25);
//            t2 = high_resolution_clock::now();
//            std::clock_t end = std::clock();
//            time += duration_cast<microseconds>(t2 - t1).count();
////            time += end-start;
//            //printf("Ant ");
//            //print_res(results);
//        }
//        printf("%10d\n", time/repeat);
//        fprintf(f,"%10d\n", time/repeat);
//    }

//    double m[] = {0,1,1,1, 1,
//                 1,0,1,1, 1,
//                 1,1,0,2, 1,
//                 1,1,2,0, 1,
//                 1,1,1,1, 0};
//    double m [] = {0, 2, 1, 2,
//                  2, 0, 2, 3,
//                  1, 2, 0, 2,
//                  2, 3, 2, 0};

    double m [] = {0, 3, 4, 5, 6, 0, 7, 8, 9,
                  3, 0, 2, 0, 3, 1, 8, 2, 0,
                  4, 2, 0, 0, 2, 0, 8, 2, 0,
                  5, 0, 0, 0, 6, 3, 0, 2, 0,
                  6,3,2,6,0,8,1,2,0,
                  0,1,0,3,8,0,9,2,4,
                  7,8,8,0,1,9,0,5,5,
                  8,2,2,2,2,2,5,0,0,
                  9,0,0,0,0,4,5,0,0};

//    Matrix mat(9, 9);
//    mat.fill_array(m);
//    mat.print();

    Matrix mat(3, 3);
    mat.make_rand();
    mat.print();


    pair<int, vector<int>> results = brute_force_find(mat);

    printf("\n=== Brute force algorithm ===");
    print_res(results);
    pair<int, vector<int>> res = AntAlgorithm(mat, 350, 0.75, 0.25);

    printf("\n=== Ant algorithm ===");
    print_res(res);


    return 0;
}
