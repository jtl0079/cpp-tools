#pragma once

#include <array>
#include <vector>
#include <cmath>
#include <cpptools/framework/copy.hpp>
#include <cpptools/framework/print.hpp>
#include <cpptools/framework/filler.hpp>
#include <cpptools/framework/math/backend/serial/serial.hpp>

namespace cpptools::framework::math::backend::serial {


	// 单向量 L2 Norm（正确）
	template<typename T, size_t N>
	double getL2Norm(const T(&vec)[N]) {
		return std::sqrt(get_dot(vec, vec));   // dot(vec, vec)
	}

	template<typename T, size_t N, typename... Vecs>
	double getL2Norm(const T(&first)[N], const Vecs(&... vecs)[N]) {
		return std::sqrt(get_dot(first, vecs...));
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
	template<typename T, typename Q, typename R, size_t M, size_t N>
	void qrdecomposition_mgs(const T(&matrixA)[M][N], Q (&matrixQ)[M][N], R (&matrixR)[M][N]) {
		namespace cfcb_serial = cpptools::framework::copy::backend::serial;
		namespace cfp = cpptools::framework::print;
		namespace cffb_serial = cpptools::framework::filler::backend::serial;

		T A_copy[M][N];
		cfcb_serial::copy(matrixA, A_copy);	
		cffb_serial::fill_zero(matrixQ, matrixR);

		for (int k = 0; k < N; k++) {
			// 计算第 k 列的 2-范数
			// L2Norm = |U|
			double rkk = 0;
			for (int i = 0; i < M; i++) rkk += A_copy[i][k] * A_copy[i][k];
			rkk = sqrt(rkk);
			matrixR[k][k] = rkk;

			// 如果列全零，跳过
			if (rkk == 0.0) continue;

			// 归一化生成 Q 的列
			for (int i = 0; i < M; i++) matrixQ[i][k] = A_copy[i][k] / rkk;

			// 对后续列正交化
			for (int j = k + 1; j < N; j++) {
				double rkj = 0.0;
				for (int i = 0; i < M; i++) rkj += matrixQ[i][k] * A_copy[i][j];
				matrixR[k][j] = rkj;
				for (int i = 0; i < M; i++) A_copy[i][j] -= rkj * matrixQ[i][k];
			}
		}
	}


	// -----------------------------
	// 上三角回代求解 R x = y
	// return x
	// -----------------------------
	template<typename T>
	std::vector<T> get_upper_triangular_back_substitution(
		std::vector<std::vector<T>> R,
		std::vector<T> y
	) {
		using namespace std;

		int n = R.size();
		vector<T> x(n, T{});
		for (int i = n - 1; i >= 0; --i) {
			double s = y[i];
			for (int j = i + 1; j < n; j++) s -= R[i][j] * x[j];
			if (fabs(R[i][i]) < 1e-15) {
				// 奇异或接近零对角线
				x[i] = 0.0;
			}
			else x[i] = s / R[i][i];
		}
		return x;
	}



	// Ax = b
	// return x

	/*
	template<typename T, size_t M, size_t N>
	std::array<T, N> solveByQR(const T(&A)[M][N], const T(&b)[M])
	{
		T Q[M][N];
		T R[N][N];

		// 1. QR decomposition
		qrdecomposition_mgs(A, Q, R);

		// 2. Compute y = Qᵀ * b
		T Qt[M][N];
		transpose(Q, Qt); // 你需要写一个 transpose()
		auto y = multiplyMatrixVector(Qt, b);

		// 3. Solve R x = y
		std::vector<T> y_vec(y.begin(), y.end());
		std::vector<std::vector<T>> R_vectorized = R;
		auto x_vec = get_upper_triangular_back_substitution(R_vectorized, y_vec);

		// 4. return x
		std::array<T, N> x{};
		for (size_t i = 0; i < N; i++) x[i] = x_vec[i];
		return x;
	}
	*/

	template<typename T, size_t M, size_t N>
	void solveByQR(const T(&A)[M][N], const T(&b)[M], T (&result_a)[N])
	{
		T Q[M][N];
		T R[N][N];

		// 1. QR decomposition
		qrdecomposition_mgs(A, Q, R);

		// 2. Compute y = Qᵀ * b
		T Qt[M][N];
		transpose(Q, Qt);

	}

}


/*
     a1, a2, a3
    [  ,   ,   ]
A = [  ,   ,   ]
    [  ,   ,   ]

     q1, q2, q3
    [  ,   ,   ]
Q = [  ,   ,   ] q2 = u2 / |u2|
    [  ,   ,   ] q3 = u3 / |u3|


	[r11, r12, r13]      [|a1|, q1a2, q1a3]
R = [   , r22, r23]  R = [    , |u2|, q2a3]
	[   ,    , r33]      [    ,     , |u3|]

	 u1, u2, u3
    [  ,   ,   ] 
U = [  ,   ,   ]  u2 = a2 - r12q1
    [  ,   ,   ]  u3 = a3 - r13q1 - r23q2
 */