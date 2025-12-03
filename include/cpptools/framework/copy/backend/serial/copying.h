#pragma once


namespace cpptools::framework::copy::backend::serial {

	template<typename T, size_t M, size_t N>
	void copy(const T(&t)[M][N],T (&dest)[M][N]) {
		for (size_t i = 0; i < M; ++i)
			for (size_t j = 0; j < N; ++j)
				dest[i][j] = t[i][j];
	}
}