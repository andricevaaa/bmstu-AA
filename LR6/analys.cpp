
// Муравьиный алгоритм
pair<int, vector<int>> AntAlgorithm(Matrix D, const int Tmax, const double alpha, const double ro){
    const int teta_beg = 10;
    const int teta_min = 5;
    const size_t M = D.cols(); //количество вершин
    const double Q = D.avg() * M; //примерное значение длины пути
    const double betta = 1 - alpha;

    Matrix Attr(M, M); //присваивание видимости                                      // ЦИКЛ 9 - ПОСЧИТААААААТЬ !!!!
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
    for (int t = 0; t < Tmax; t++) {                                                    // ЦИКЛ 8
        Delta_Teta.zero();
        //цикл по всем муравьям
        for (size_t k = 0; k < M; k++) {                                                // ЦИКЛ 6
            vector<int> cur_path;
            cur_path.push_back(k);
            int cur_path_length = 0;
            int i = k;
            //строим маршрут
            while (cur_path.size() < M) {                                               // ЦИКЛ 5
                vector<int> not_visited;
                // поиск всех непосещенных вершин
                bool nv = true;
                for (size_t i = 0; i < M; i++) {                                        // ЦИКЛ 1
                    nv = true;
                    for (size_t j = 0; j < cur_path.size(); j++) {
                        if ((int)i == cur_path[j]) nv = false;
                    }
                    if (nv)
                        not_visited.push_back(i);
                }

                for (size_t j = 0; j < M ; j++){                                         // ЦИКЛ 2
                    P[j] = 0.0;
                }
                // посчитаем вероятности
                for (size_t j = 0; j < not_visited.size(); j++) {                        	// ЦИКЛ 3
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
                for (size_t s = 0; s < M; s++) {                                             // ЦИКЛ 4
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
        for (size_t ii = 0; ii < M; ii++) {                                                 // ЦИКЛ 7
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
