#pragma once

#include <omp.h>
#include <cpptools/core/traits.hpp>
#include <cpptools/framework/math/backend/openmp/upper_triangular_back_substitution.h>
#include <cpptools/framework/math/backend/openmp/multiply_matrix_vector.h>
#include <cpptools/framework/math/backend/openmp/qrdecomposition_mgs.h>
#include <cpptools/framework/math/backend/openmp/transpose.h>


namespace cpptools::framework::math::backend::openmp {




    // -------------------------------------
    // Solve Ax = b using QR (Generic)
    // Accepts any array type
    // -------------------------------------
    template<class MatA, class VecB, class VecX>
    void solve_linear_by_decomposition_qr_mgs(const MatA& A, const VecB& b, VecX& x_result)
    {
        namespace traits = cpptools::core::traits;
        const size_t M = traits::size(A);
        const size_t N = traits::size(A[0]);

        // Q: M×N
        // R: N×N
        std::vector<std::vector<std::decay_t<decltype(A[0][0])>>> Q(M, std::vector<std::decay_t<decltype(A[0][0])>>(N));
        std::vector<std::vector<std::decay_t<decltype(A[0][0])>>> R(N, std::vector<std::decay_t<decltype(A[0][0])>>(N));

        // 1. QR
        qrdecomposition_mgs(A, Q, R);

        // 2. y = Qᵀ b
        std::vector<std::vector<std::decay_t<decltype(A[0][0])>>> Qt(N, std::vector<std::decay_t<decltype(A[0][0])>>(M));
        std::vector<std::decay_t<decltype(A[0][0])>> y(N);

        transpose(Q, Qt);
        multiply_matrix_vector(Qt, b, y);

        // 3. Solve R x = y
        upper_triangular_back_substitution(R, y, x_result);
    }
}
