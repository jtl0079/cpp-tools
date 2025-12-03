#pragma once

#include <array>
#include <cpptools/framework/copy.hpp>
#include <cpptools/framework/print.hpp>
namespace cpptools::framework::math::backend::serial {

	template<typename T, size_t N, size_t N2>
	T getDot(T(&t)[N], T(&t2)[N2]) {
		static_assert(N == N2, "[cpptools::framework::math::backend::serial::getDot()] Vectors must be same length");
		T dot{};

		for (size_t i = 0; i < N; i++) { dot += t[i] * t2[i]; }
		return dot;
	}

	template<typename T, size_t N, size_t N2>
	double getL2Norm(T(&t)[N], T(&t2)[N2]) {
		return sqrt(getDot(t, t2));
	}



	// Frobenius 范数 ||A-B||_F
	template<typename T, size_t M, size_t N>
	double getFrobeniusNormDistance(T(&matrixA)[M][N], T(&matrixB)[M][N]) {
		double distance = 0.0;
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++) {
				double d = double(matrixA[i][j]) - double(matrixB[i][j]);
				distance += d * d;
			}
		return sqrt(distance);
	}



	template<typename T, size_t M, size_t N>
	std::array<T, M> getMultiplyMatrixVector(const T(&matrix)[M][N], const  T(&vec)[N]) {
		using namespace std;
		array<T, M> y{};  // 结果长度 M
		for (size_t i = 0; i < M; ++i) {
			T tmp{};
			for (size_t j = 0; j < N; ++j) {
				tmp += matrix[i][j] * vec[j];
			}
			y[i] = tmp;
		}
		return y;
	}


	template<typename T, size_t M, size_t N, size_t P>
	void multiplyMatrix(T(&A)[M][N], T(&B)[N][P], T(&result)[M][P]) {
		// clean
		for (size_t i = 0; i < M; ++i)
			for (size_t j = 0; j < P; ++j)
				result[i][j] = 0;

		// input 
		for (size_t i = 0; i < M; ++i) {
			for (size_t k = 0; k < N; ++k) {
				T v = A[i][k];
				for (size_t j = 0; j < P; ++j) {
					result[i][j] += v * B[k][j];
				}
			}
		}
	}


	// -----------------------------
	// Modified Gram-Schmidt QR Decomposition
	// A = QR
	// A: m x n, m >= n
	// result: Q (m x n), R (n x n)
	// -----------------------------
	template<typename T, size_t M, size_t N>
	void qrDecomposition_mgs(const T(&matrixA)[M][N], T(&matrixQ)[M][N], T(&matrixR)[M][N]) {
		namespace cfcb_serial = cpptools::framework::copy::backend::serial;
		namespace cfp = cpptools::framework::print;

		T A_copy[M][N];
		cfcb_serial::copy(matrixA, A_copy);

		cfp::print(A_copy);
	}


}