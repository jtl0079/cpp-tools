#pragma once



namespace cpptools::framework::math::backend::serial {


	template<typename T, size_t M, size_t N>
	std::array<T, M> get_multiply_matrix_vector(const T(&matrix)[M][N], const  T(&vec)[N]) {
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
}