#pragma once


namespace cpptools::framework::math::backend::serial {


	// -----------------------------
	// 上三角回代求解 R x = y
	// return x
	// -----------------------------
	template<class Matrix, class VectorY, class VectorX>
	void upper_triangular_back_substitution(
		const Matrix& R,
		const VectorY& y,
		VectorX& x
	) {
		namespace traits = cpptools::core::traits;

		const size_t n = traits::size(R);
		using T = std::decay_t<decltype(y[0])>;

		// --- Dimension check ---
		if (traits::size(y) != n)
			throw std::runtime_error("Dimension mismatch: y length != n");
		if (traits::size(x) != n)
			throw std::runtime_error("Dimension mismatch: x length != n");

		// --- Back substitution ---
		for (int i = int(n) - 1; i >= 0; --i) {

			T s = y[i];

			for (size_t j = i + 1; j < n; ++j)
				s -= R[i][j] * x[j];

			T diag = R[i][i];

			if constexpr (std::is_floating_point_v<T>) {
				// 浮点数奇异判断
				if (std::abs(diag) < T(1e-15))
					x[i] = T{}; // 接近奇异
				else
					x[i] = s / diag;
			}
			else {
				// 非浮点类型（例如 int）
				if (diag == T{})
					x[i] = T{};
				else
					x[i] = s / diag;
			}
		}
	}




}
