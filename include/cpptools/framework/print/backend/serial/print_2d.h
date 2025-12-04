#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>

namespace cpptools::framework::print::backend::serial {

    // 获取单个元素转 string 的长度
    template<typename T>
    size_t element_width(const T& v) {
        std::ostringstream oss;
        oss << v;
        return oss.str().size();
    }


    template<typename T, size_t M, size_t N>
    void print_2d(const T(&t)[M][N], const std::string& delimiter = ", ")
    {
        using namespace std;

        for (size_t i = 0; i < M; ++i) {

            cout << t[i][0];

            for (size_t j = 1; j < N; ++j)
                cout << delimiter << t[i][j];

            if (i + 1 < M)
                cout << "\n";
        }
    }




    template<typename T, size_t M, size_t N>
    void print_2d_pretty(const T(&arr)[M][N])
    {
        using namespace std;

        // 1) 找到最长元素长度
        size_t width = 0;
        for (size_t i = 0; i < M; ++i)
            for (size_t j = 0; j < N; ++j)
                width = std::max(width, element_width(arr[i][j]));

        // 2) 打印每一行
        for (size_t i = 0; i < M; ++i) {

            cout << "[ ";

            for (size_t j = 0; j < N; ++j) {

                // 输出自动对齐的元素
                cout << setw(width) << arr[i][j];

                if (j + 1 < N)
                    cout << ", ";
            }

            cout << " ]\n";
        }
    }
}


