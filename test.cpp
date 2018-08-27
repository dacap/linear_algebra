#include "matrix_storage.h"
#include "matrix_traits.h"
#include "linear_algebra.h"

#define TEST_INT
#define TEST_FLOAT
//#define TEST_COMPLEX

//#define DECLARE_VECTOR_TYPE(T, N) using T##_##N##_t = std::experimental::la::matrix_traits<std::experimental::la::fixed_size_matrix<T, 1, N>>; using T##_##N = std::experimental::la::matrix<T##_##N##_t>
//#define DECLARE_MATRIX_TYPE(T, M, N) using T##_##M##N##_t = std::experimental::la::matrix_traits<std::experimental::la::fixed_size_matrix<T, M, N>>; using T##_##M##N = std::experimental::la::matrix<T##_##M##N##_t>

using namespace std::experimental::la;

#if defined TEST_COMPLEX
#include <complex>
void complex_test()
{
    using cf = std::complex<float>;
    
    DECLARE_VECTOR_TYPE(cf, 2);
    
    DECLARE_MATRIX_TYPE(cf, 2, 2);
    DECLARE_MATRIX_TYPE(cf, 2, 3);
    DECLARE_MATRIX_TYPE(cf, 3, 2);
    DECLARE_MATRIX_TYPE(cf, 3, 3);
    
    // test constructors
    auto v1 = cf_2{};
    auto v2 = cf_2{ 0.0f };
    auto v3 = cf_2{ 1.0f, 2.0f };
    auto v4 = cf_2{ { 1.0f, 0.0f },{ 2.0f, 1.0f } };
    auto m1 = cf_22{};
    auto m2 = cf_22{
        0.0f, 0.2f,
        0.4f, 0.6f };
    auto m3 = cf_23{
        0.0f, 0.1f, 0.2f,
        0.3f, 0.4f, 0.5f };
    auto m4 = cf_32{
        1.0f, 2.0f,
        3.0f, 4.0f,
        5.0f, 6.0f };
    auto m5 = cf_33{
        1.0f, 2.0f, 3.0f,
        2.0f, 3.0f, 4.0f,
        1.0f, 5.0f, 7.0f };
    
    // test equality operators
    assert(v2 != v3);
    assert(v3 == v4);
    
    // test scalar binary operators
    auto sbo1 = cf_2{ 2.0f, 2.0f } *3.0f;
    auto sbo2 = 3.0f * cf_2{ 2.0f, 2.0f };
    auto sbo3 = cf_2{ 2.0f, 2.0f } / 4.0f;
    
    assert(sbo1 == (cf_2{ 6.0f, 6.0f }));
    assert(sbo2 == (cf_2{ 6.0f, 6.0f }));
    assert(sbo3 == (cf_2{ 0.5f, 0.5f }));
    
    // test matrix binary operators
    auto mbo1 = v3 + v4;
    auto mbo2 = v3 - v4;
    auto mbo3 = m3 * m4;
    assert(mbo1 == (cf_2{ 2.0f, 4.0f }));
    assert(mbo2 == (cf_2{ 0.0f, 0.0f }));
    assert(mbo3 == (cf_22{ 1.3f, 1.6f,
        4.0f, 5.2f }));
    
    // test matrix functions
    auto mf1 = transpose(m3);
    auto mf2 = submatrix(m3, 0, 1);
    assert(mf1 == (cf_32{ 0.0f, 0.3f,
        0.1f, 0.4f,
        0.2f, 0.5f }));
    assert(mf2 == (cf_2{ 0.3f, 0.5f }));
    
    // test vector functions
    auto vf1 = inner_product(v3, v4);
    auto vf2 = modulus(cf_2{ 3.0f, 4.0f });
    auto vf3 = modulus_squared(cf_2{ 3.0f, 4.0f });
    auto vf4 = modulus(unit(cf_2{ 1.0f, 1.0f }));
    auto vf4a = modulus(cf_2{ 0.707106769f, 0.707106769f });
    assert(vf1 == 5.0f);
    assert(vf2 == 5.0f);
    assert(vf3 == 25.0f);
    //    assert(vf4 - vf4a < std::numeric_limits<float>::min());
    
    // test SquareMatrix predicates
    assert(!(is_identity(cf_22{
        1.0f, 0.0f,
        1.0f, 1.0f })));
    assert((is_identity(cf_22{
        1.0f, 0.0f,
        0.0f, 1.0f })));
    
    // test SquareMatrix functions
    auto smf1 = identity<cf_22_t>();
    auto smf2 = determinant<cf_33_t>(m5);
    auto smf3 = classical_adjoint<cf_33_t>(m5);
    auto smf4 = inverse(m2);
    auto smf5 = m2 * smf4;
    auto smf6 = smf4 * m2;
    assert(smf1 == (cf_22{ 1.0f, 0.0f,
        0.0f, 1.0f }));
    assert(smf2 == 2.0f);
    assert(smf3 == (cf_33{ 1.0f, 1.0f, -1.0f,
        -10.0f, 4.0f, 2.0f,
        7.0f, -3.0f, -1.0f }));
    //    assert(is_identity(smf5));    // Rounding error
    //    assert(is_identity(smf6));    // Rounding error
}
#endif

#if defined TEST_FLOAT
void float_test()
{
    using namespace std::experimental::la;
    auto v1 = matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{};
    auto v2 = matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 0.0f };
    auto v3 = matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 1.0f, 2.0f };
    auto v4 = matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 1.0f, 2.0f };
    auto m1 = matrix<matrix_traits<fixed_size_matrix<float, 2, 2>>>{};
    auto m2 = matrix<matrix_traits<fixed_size_matrix<float, 2, 2>>>{
        0.0f, 0.2f,
        0.4f, 0.6f };
    auto m3 = matrix<matrix_traits<fixed_size_matrix<float, 2, 3>>>{
        0.0f, 0.1f, 0.2f,
        0.3f, 0.4f, 0.5f };
    auto m4 = matrix<matrix_traits<fixed_size_matrix<float, 3, 2>>>{
        1.0f, 2.0f,
        3.0f, 4.0f,
        5.0f, 6.0f };
    auto m5 = matrix<matrix_traits<fixed_size_matrix<float, 3, 3>>>{
        1.0f, 2.0f, 3.0f,
        2.0f, 3.0f, 4.0f,
        1.0f, 5.0f, 7.0f };
    
    // test accessors
    assert(m3(1, 2) == 0.5f);
    
    // test equality operators
    assert(v2 != v3);
    assert(v3 == v4);
    
    // test scalar binary operators
    auto sbo1 = matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 2.0f, 2.0f } *3.0f;
    auto sbo2 = 3.0f * matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 2.0f, 2.0f };
    auto sbo3 = matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 2.0f, 2.0f } / 4.0f;
    
    assert(sbo1 == (matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 6.0f, 6.0f }));
    assert(sbo2 == (matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 6.0f, 6.0f }));
    assert(sbo3 == (matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 0.5f, 0.5f }));
    
    // test matrix binary operators
    auto mbo1 = v3 + v4;
    auto mbo2 = v3 - v4;
    auto mbo3 = m3 * m4;
    assert(mbo1 == (matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 2.0f, 4.0f }));
    assert(mbo2 == (matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 0.0f, 0.0f }));
    assert(mbo3 == (matrix<matrix_traits<fixed_size_matrix<float, 2, 2>>>{ 1.3f, 1.6f,
        4.0f, 5.2f }));
    
    // test matrix functions
    auto mf1 = transpose(m3);
    auto mf2 = submatrix(m3, 0, 1);
    assert(mf1 == (decltype(mf1){ 0.0f, 0.3f,
        0.1f, 0.4f,
        0.2f, 0.5f }));
    assert(mf2 == (decltype(mf2){ 0.3f, 0.5f }));
    
    // test vector functions
    auto vf1 = inner_product(v3, v4);
    auto vf2 = modulus(matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 3.0f, 4.0f });
    auto vf3 = modulus_squared(matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 3.0f, 4.0f });
    auto vf4 = modulus(unit(matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 1.0f, 1.0f }));
    auto vf4a = modulus(matrix<matrix_traits<fixed_size_matrix<float, 1, 2>>>{ 0.707106769f, 0.707106769f });
    assert(vf1 == 5.0f);
    assert(vf2 == 5.0f);
    assert(vf3 == 25.0f);
    assert(vf4 - vf4a < std::numeric_limits<float>::min());
    
    // test SquareMatrix predicates
    assert(!(is_identity(matrix<matrix_traits<fixed_size_matrix<float, 2, 2>>>{
        1.0f, 0.0f,
        1.0f, 1.0f })));
    assert((is_identity(matrix<matrix_traits<fixed_size_matrix<float, 2, 2>>>{
        1.0f, 0.0f,
        0.0f, 1.0f })));
    assert((is_invertible(matrix<matrix_traits<fixed_size_matrix<float, 2, 2>>>(m2))));
    
    // test SquareMatrix functions
    auto smf1 = identity<matrix_traits<fixed_size_matrix<float, 2, 2>>>();
    auto smf2 = determinant<matrix_traits<fixed_size_matrix<float, 3, 3>>>(m5);
    auto smf3 = classical_adjoint<matrix_traits<fixed_size_matrix<float, 3, 3>>>(m5);
    auto smf4 = inverse(m2);
    auto smf5 = m2 * smf4;
    auto smf6 = smf4 * m2;
    assert(smf1 == (matrix<matrix_traits<fixed_size_matrix<float, 2, 2>>>{ 1.0f, 0.0f,
        0.0f, 1.0f }));
    assert(smf2 == 2.0f);
    assert(smf3 == (matrix<matrix_traits<fixed_size_matrix<float, 3, 3>>>{ 1.0f, 1.0f, -1.0f,
        -10.0f, 4.0f, 2.0f,
        7.0f, -3.0f, -1.0f }));
    assert(is_identity(smf5));    // Rounding error
    assert(is_identity(smf6));    // Rounding error
}
#endif

#if defined TEST_INT
void int_test()
{
    DECLARE_VECTOR_TYPE(int, 2);
    
    DECLARE_MATRIX_TYPE(int, 2, 2);
    DECLARE_MATRIX_TYPE(int, 2, 3);
    DECLARE_MATRIX_TYPE(int, 3, 2);
    DECLARE_MATRIX_TYPE(int, 3, 3);
    
    // test constructors
    auto v1 = int_2{};
    auto v2 = int_2{ 0 };
    auto v3 = int_2{ 1, 2 };
    auto v4 = int_2{ 1, 2 };
    auto m1 = int_22{};
    auto m2 = int_22{
        0, 2,
        4, 6 };
    auto m3 = int_23{
        1, -2, -5,
        3, 4, 0 };
    auto m4 = int_32{
        2, -1,
        1, 0,
        -3, 4 };
    auto m5 = int_33{
        1, 2, 3,
        2, 3, 4,
        1, 5, 7 };
    
    // test accessors
    assert(m3(1, 2) == 0);
    
    // test equality operators
    assert(v2 != v3);
    assert(v3 == v4);
    
    // test scalar binary operators
    auto sbo1 = int_2{ 2, 2 } *3;
    auto sbo2 = 3 * int_2{ 2, 2 };
    auto sbo3 = int_2{ 4, 4 } / 2;
    
    assert(sbo1 == (int_2{ 6, 6 }));
    assert(sbo2 == (int_2{ 6, 6 }));
    assert(sbo3 == (int_2{ 2, 2 }));
    
    // test matrix binary operators
    auto mbo1 = v3 + v4;
    auto mbo2 = v3 - v4;
    auto mbo3 = m3 * m4;
    assert(mbo1 == (int_2{ 2, 4 }));
    assert(mbo2 == (int_2{ 0, 0 }));
    assert(mbo3 == (decltype(mbo3){ 15, -21,
        10, -3 }));
    
    // test matrix functions
    auto mf1 = transpose(m3);
    auto mf2 = submatrix(m3, 0, 1);
    assert(mf1 == (decltype(mf1){ 1, 3,
        -2, 4,
        -5, 0 }));
    assert(mf2 == (decltype(mf2){ 3, 0 }));
    
    // test vector functions
    auto vf1 = inner_product(v3, v4);
    auto vf2 = modulus(int_2{ 3, 4 });
    auto vf3 = modulus_squared(int_2{ 3, 4 });
    auto vf4 = modulus(unit(int_2{ 1, 1 }));
    auto vf4a = modulus(int_2{ 0, 0 });
    assert(vf1 == 5);
    assert(vf2 == 5);
    assert(vf3 == 25);
    //    assert(vf4 - vf4a < std::numeric_limits<int>::min());    // Rounding error
    
    // test SquareMatrix predicates
    assert(!(is_identity(int_22{
        1, 0,
        1, 1 })));
    assert((is_identity(int_22{
        1, 0,
        0, 1 })));
    
    // test SquareMatrix functions
    auto smf1 = identity<int_22_t>();
    auto smf2 = determinant<int_33_t>(m5);
    auto smf3 = classical_adjoint<int_33_t>(m5);
    auto smf4 = inverse(m2);
    auto smf5 = m2 * smf4;
    auto smf6 = smf4 * m2;
    assert(smf1 == (int_22{ 1, 0,
        0, 1 }));
    assert(smf2 == 2);
    assert(smf3 == (decltype(smf3){ 1, 1, -1,
        -10, 4, 2,
        7, -3, -1 }));
    //    assert(is_identity(smf5));    // Rounding error
    //    assert(is_identity(smf6));    // Rounding error
}
#endif

int main()
{
#if defined TEST_COMPLEX
    complex_test();
#endif
#if defined TEST_FLOAT
    float_test();
#endif
#if defined TEST_INT
    int_test();
#endif
}
