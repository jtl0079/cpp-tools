#pragma once

#include<iostream>
#include<omp.h>
#include<vector>

namespace OpenMPTools {


    template<typename T>
    T sum(const std::vector<T>& v)
    {
        using namespace std;
        int n = v.size();
        const T* ptr = v.data();
        T sum = T();

#pragma omp parallel for reduction(+:sum) schedule(static)
        for (int i = 0; i < n; i++) {
            sum += ptr[i];            
        }

        
        return sum;
    }


}

