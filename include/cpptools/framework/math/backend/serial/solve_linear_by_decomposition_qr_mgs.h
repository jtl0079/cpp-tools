#pragma once


namespace cpptools::framework::math::backend::serial {

    // -----------------------------
    // Ax = b
    // return x
    // -----------------------------
    template<class MatA, class VecB, class VecX>
    void solve_linear_by_decomposition_qr_mgs(const MatA& A, const VecB& b, VecX& x_result)
    {
        namespace traits = cpptools::core::traits;

        const size_t M = traits::size(A);
        const size_t N = traits::size(A[0]);

        // Dimension check
        if (traits::size(b) != M || traits::size(x_result) != N) {
            throw std::runtime_error("Dimension mismatch in solveByQR");
        }

        using T = std::remove_cv_t<std::remove_reference_t<decltype(A[0][0])>>;

        // Allocate Q, R
        std::vector<std::vector<T>> Q(M, std::vector<T>(N));
        std::vector<std::vector<T>> R(N, std::vector<T>(N));

        // 1. QR decomposition
        decomposition_qr_mgs(A, Q, R);

        // 2. Compute y = Qᵀ * b
        std::vector<std::vector<T>> Qt(N, std::vector<T>(M));
        std::vector<T> y(N);

        transpose(Q, Qt);
        multiply_matrix_vector(Qt, b, y);

        // 3. Solve Rx = y
        upper_triangular_back_substitution(R, y, x_result);
    }


}