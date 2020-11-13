#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <vector>
#include <fstream>
#include <set>

#include "RBTree.h"
#include "AVLTree.h"

double average(std::vector<double>& vector, int size){
    sort(vector.begin(), vector.end());
    int step = size/4;
    double average = 0;
    for(int i = step; i <= size - step; ++i){
        average += vector[i];
    }
    average /= (size - 2*step + 1);
    return average;
}

double get_time()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
}

int rand_uns(int min, int max)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_int_distribution<int> d(min, max);
    return d(e);
}

int main(){

    RBTree tree;
    std::ofstream outfile("RB.txt");

    auto data_for_export = new double[1000][4];
    std::vector<double> insert_statistic;
    std::vector<double> find_statistic;
    std::vector<double> del_statistic;
    auto indexes = new int[100];
    double insert, find, del;
    std::vector<int> test;
    int num;

    //заполняем для начала чем-нибудь до размера 1000
    for(int j = 0; j < 1000; ++j){
        num = rand_uns(1, 100000000);
        tree.insert(num);
        test.push_back(num);
    }

    int n = 1000;

    for(int i = 0; i < 1000; ++i){

        double start = 0, finish = 0;
        int index;

        if(!(i%10))
            std::cout << "Illusion of work: " << i/10 << "%" << std::endl;
        //Проводим 1000 измерений
        for(int p = 0; p < 1000; ++p){
            //del
            index = rand_uns(0, test.size() - 1);

            start = get_time();
            tree.delete_elem(test[index]);
            finish = get_time();

            del_statistic.push_back(finish - start);
            test.erase(test.begin() + index);

            //возвращаем кол-во элементов к началу
            num = rand_uns(1, 100000000);
            tree.insert(num);
            test.push_back(num);

            //find
            index = rand_uns(0, test.size() - 1);

            start = get_time();
            tree.find(test[index]);
            finish = get_time();

            find_statistic.push_back(finish - start);

            //insert
            num = rand_uns(1, 100000000);

            start = get_time();
            tree.insert(num); //в произволное место rand_uns(0, j) число rand_uns(100, 1000000);
            finish = get_time();

            insert_statistic.push_back(finish - start);

            //возвращаем кол-во элементов к началу
            num = rand_uns(1, 100000000);
            tree.insert(num);
            test.push_back(num);
        }

        //Выбираем среднее для каждого пункта
        insert = average(insert_statistic, insert_statistic.size());
        find = average(find_statistic, find_statistic.size());
        del = average(del_statistic, del_statistic.size());

        insert_statistic.clear();
        find_statistic.clear();
        del_statistic.clear();

        data_for_export[i][0] = n;
        data_for_export[i][1] = insert;
        data_for_export[i][2] = find;
        data_for_export[i][3] = del;

        //Корректируем дерево
        index = rand_uns(0, test.size() - 1);
        tree.delete_elem(test[index]);

        n += 1000;

        for(int j = 0; j < 1000; ++j){
            num = rand_uns(1, 100000000);
            tree.insert(num);
            test.push_back(num);
        }

    }

    //экспорт в питон
    for(int i = 0; i < 1000; ++i){
        for(int j = 0; j < 4; ++j){
            outfile << data_for_export[i][j] << " ";
        }
        outfile << std::endl;
    }
    outfile.close();
    delete [] data_for_export;
    delete [] indexes;

    return 0;
}
