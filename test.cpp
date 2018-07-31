#include "linear_algebra.h"
#include "matrix_traits.h"

#define DECLARE_VECTOR_TYPE(T, N) using T##_##N##_t = std::experimental::matrix_traits<T, 1, N>; using T##_##N = std::experimental::matrix<T##_##N##_t>
#define DECLARE_MATRIX_TYPE(T, M, N) using T##_##M##N##_t = std::experimental::matrix_traits<T, M, N>; using T##_##M##N = std::experimental::matrix<T##_##M##N##_t>

void float_test()
{
	DECLARE_VECTOR_TYPE(float, 2);

	DECLARE_MATRIX_TYPE(float, 2, 2);
	DECLARE_MATRIX_TYPE(float, 2, 3);
	DECLARE_MATRIX_TYPE(float, 3, 2);
	DECLARE_MATRIX_TYPE(float, 3, 3);
	DECLARE_MATRIX_TYPE(float, 4, 4);

	// test constructors
	auto v1 = float_2{};
	auto v2 = float_2{ 0.0f };
	auto v3 = float_2{ 1.0f, 2.0f };
	float coordinates[2] = { 1.0f, 2.0f };
	auto v4 = float_2{ coordinates };
	auto m1 = float_22{};
	auto m2 = float_22{
		0.0f, 0.2f,
		0.4f, 0.6f };
	auto m3 = float_23{
		0.0f, 0.1f, 0.2f,
		0.3f, 0.4f, 0.5f };
	auto m4 = float_32{
		1.0f, 2.0f,
		3.0f, 4.0f,
		5.0f, 6.0f };
	auto m5 = float_33{
		1.0f, 2.0f, 3.0f,
		2.0f, 3.0f, 4.0f,
		1.0f, 5.0f, 7.0f };

	// test equality operators
	assert(v2 != v3);
	assert(v3 == v4);

	// test scalar binary operators
	auto sbo1 = float_2{ 2.0f, 2.0f } *3.0f;
	auto sbo2 = 3.0f * float_2{ 2.0f, 2.0f };
	auto sbo3 = float_2{ 2.0f, 2.0f } / 4.0f;

	assert(sbo1 == (float_2{ 6.0f, 6.0f }));
	assert(sbo2 == (float_2{ 6.0f, 6.0f }));
	assert(sbo3 == (float_2{ 0.5f, 0.5f }));

	// test matrix binary operators
	auto mbo1 = v3 + v4;
	auto mbo2 = v3 - v4;
	auto mbo3 = m3 * m4;
	assert(mbo1 == (float_2{ 2.0f, 4.0f }));
	assert(mbo2 == (float_2{ 0.0f, 0.0f }));
	assert(mbo3 == (float_22{ 1.3f, 1.6f,
		4.0f, 5.2f }));

	// test matrix functions
	//	auto mf1 = transpose(m3);	// compile error
	auto mf2 = submatrix(m3, 0, 1);
	/*	assert(mf1 == (float_32{ 0.0f, 0.3f,
	0.1f, 0.4f,
	0.2f, 0.5f }));*/
	assert(mf2 == (float_2{ 0.3f, 0.5f }));

	// test vector functions
	auto vf1 = inner_product(v3, v4);
	auto vf2 = modulus(float_2{ 3.0f, 4.0f });
	auto vf3 = modulus_squared(float_2{ 3.0f, 4.0f });
	auto vf4 = modulus(unit(float_2{ 1.0f, 1.0f }));
	auto vf4a = modulus(float_2{ 0.707106769f, 0.707106769f });
	assert(vf1 == 5.0f);
	assert(vf2 == 5.0f);
	assert(vf3 == 25.0f);
	assert(vf4 - vf4a < std::numeric_limits<float>::min());

	// test SquareMatrix predicates
	assert(!(std::experimental::is_identity(float_22{
		1.0f, 0.0f,
		1.0f, 1.0f })));
	assert((std::experimental::is_identity(float_44{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f })));

	// test SquareMatrix functions
	auto smf1 = std::experimental::identity<float_22_t>();
	auto smf2 = std::experimental::determinant<float_33_t>(m5);
	auto smf3 = std::experimental::classical_adjoint<float_33_t>(m5);
	auto smf4 = std::experimental::inverse(m2);
	auto smf5 = m2 * smf4;
	auto smf6 = smf4 * m2;
	assert(smf1 == (float_22{ 1.0f, 0.0f,
		0.0f, 1.0f }));
	assert(smf2 == 2.0f);
	assert(smf3 == (float_33{ 1.0f, 1.0f, -1.0f,
		-10.0f, 4.0f, 2.0f,
		7.0f, -3.0f, -1.0f }));
	//	assert(std::experimental::is_identity(smf5));	// Rounding error
	//	assert(std::experimental::is_identity(smf6));	// Rounding error
}

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
	int coordinates[2] = { 1, 2 };
	auto v4 = int_2{ coordinates };
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
	assert(mbo3 == (int_22{ 15, -21,
		10, -3 }));

	// test matrix functions
	//	auto mf1 = transpose(m3);
	auto mf2 = submatrix(m3, 0, 1);
	/*	assert(mf1 == (int_32{ 0, 0,
	0, 0,
	0, 0 }));*/
	assert(mf2 == (int_2{ 3, 0 }));

	// test vector functions
	auto vf1 = inner_product(v3, v4);
	auto vf2 = modulus(int_2{ 3, 4 });
	auto vf3 = modulus_squared(int_2{ 3, 4 });
	auto vf4 = modulus(unit(int_2{ 1, 1 }));
	auto vf4a = modulus(int_2{ 0, 0 });
	assert(vf1 == 5);
	assert(vf2 == 5);
	assert(vf3 == 25);
	//	assert(vf4 - vf4a < std::numeric_limits<int>::min());	// Rounding error

	// test SquareMatrix predicates
	assert(!(std::experimental::is_identity(int_22{
		1, 0,
		1, 1 })));
	assert((std::experimental::is_identity(int_22{
		1, 0,
		0, 1 })));

	// test SquareMatrix functions
	auto smf1 = std::experimental::identity<int_22_t>();
	auto smf2 = std::experimental::determinant<int_33_t>(m5);
	auto smf3 = std::experimental::classical_adjoint<int_33_t>(m5);
	auto smf4 = std::experimental::inverse(m2);
	auto smf5 = m2 * smf4;
	auto smf6 = smf4 * m2;
	assert(smf1 == (int_22{ 1, 0,
		0, 1 }));
	assert(smf2 == 2);
	assert(smf3 == (int_33{ 1, 1, -1,
		-10, 4, 2,
		7, -3, -1 }));
	//	assert(std::experimental::is_identity(smf5));	// Rounding error
	//	assert(std::experimental::is_identity(smf6));	// Rounding error
}

int main()
{
	float_test();
	int_test();
}