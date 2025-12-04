#pragma once

#include <array>
#include <vector>
#include <cmath>

namespace cpptools::framework::math::backend::serial {

	// Frobenius norm 范数 ||A-B||_F
	template<typename T, size_t M, size_t N>
	double get_frobenius_norm_distance(T(&matrixA)[M][N], T(&matrixB)[M][N]) {
		double distance = 0.0;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++) {
				double d = double(matrixA[i][j]) - double(matrixB[i][j]);
				distance += d * d;
			}
		return sqrt(distance);
	}

}