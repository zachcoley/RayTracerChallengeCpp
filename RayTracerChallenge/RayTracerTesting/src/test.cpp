﻿#include "pch.h"
#include <cmath>
#include <vector>
#include <memory>
#include "utils.cpp"
#include "mock-tuple.cpp"
#include "tuple.cpp"
#include "point.cpp"
#include "vector.cpp"
#include "color.cpp"
#include "canvas.cpp"
#include "matrix2.cpp"
#include "matrix3.cpp"
#include "matrix4.cpp"
#include "ray.cpp"
#include "object.cpp"
#include "shape.cpp"
#include "sphere.cpp"
#include "intersection.cpp"
#include "hit.cpp"
#include "material.cpp"
#include "light-source.cpp"
#include "point-light.cpp"
#include "world.cpp"
#include "engine.cpp"
#include "camera.cpp"
#include "mock-shape.cpp"
#include "plane.cpp"
#include "colors.cpp"
#include "pattern.cpp"
#include "mock-pattern.cpp"
#include "stripe-pattern.cpp"
#include "gradient-pattern.cpp"
#include "ring-pattern.cpp"
#include "checker-pattern.cpp"
#include "cube.cpp"
#include "cylinder.cpp"
#include "cone.cpp"
#include "group.cpp"
#include "materials.cpp"
#include "bounding-box.cpp"
#include "triangle.cpp"
#include "obj-parser.cpp"
#include "smooth-triangle.cpp"
#include "csg.cpp"

#pragma region UtilsTests
TEST(UtilsTests, ClampToZero) {
	EXPECT_FLOAT_EQ(utils::clamp(-1.5f, 0.0f, 1.0f), 0.0f);
}

TEST(UtilsTests, ClampToOne) {
	EXPECT_FLOAT_EQ(utils::clamp(1.5f, 0.0f, 1.0f), 1.0f);
}

TEST(UtilsTests, SwapFloatValues) {
	float a = 5.1f;
	float b = 6.3f;
	utils::swap(a, b);
	EXPECT_FLOAT_EQ(a, 6.3f);
	EXPECT_FLOAT_EQ(b, 5.1f);
}

TEST(UtilsTests, SwapIntegerValues) {
	int a = 4;
	int b = 3;
	utils::swap(a, b);
	EXPECT_EQ(a, 3);
	EXPECT_EQ(b, 4);
}

TEST(UtilsTests, SwapDoubleValues) {
	double a = 7.4;
	double b = 8.6;
	utils::swap(a, b);
	EXPECT_DOUBLE_EQ(a, 8.6);
	EXPECT_DOUBLE_EQ(b, 7.4);
}

TEST(UtilsTests, SwapIntersectionValues) {
	Sphere* s1 = new Sphere("Sphere1");
	Shape* s2 = new Sphere("Sphere2");
	Intersection i1(1.0f, s1);
	Intersection i2(2.0f, s2);
	Intersection::swap(i1, i2);
	EXPECT_FLOAT_EQ(i1.GetTime(), 2.0f);
	EXPECT_TRUE((*i1.GetObject()) == (*s2));
	EXPECT_FLOAT_EQ(i2.GetTime(), 1.0f);
	EXPECT_TRUE((*i2.GetObject()) == (*s1));
}

TEST(UtilsTests, ArrayContainsAValue) {
	std::string arr[] = { "apple", "banana", "pear" };
	EXPECT_TRUE(utils::contains(arr, "pear"));
}

TEST(UtilsTests, ArrayDoesNotContainAValue) {
	std::string arr[] = { "apple", "banana", "pear" };
	EXPECT_FALSE(utils::contains(arr, "orange"));
}

TEST(UtilsTests, VectorOfBoolsWhenOneBoolIsTrue) {
	std::vector<bool> bools = { false, false, true };
	EXPECT_TRUE(utils::at_least_one_true(bools));
}

TEST(UtilsTests, VectorOfBoolsWhenManyBoolsAreTrue) {
	std::vector<bool> bools = { false, true, false, true };
	EXPECT_TRUE(utils::at_least_one_true(bools));
}

TEST(UtilsTests, VectorOfBoolsWhenNoBoolsAreTrue) {
	std::vector<bool> bools = { false, false, false };
	EXPECT_FALSE(utils::at_least_one_true(bools));
}

TEST(UtilsTests, remove_all_whitespace_removes_absolutely_any_whitespace_in_a_string) {
	std::string str1 = "H e l l o";
	std::string str2 = "    Hello    ";
	EXPECT_EQ(utils::remove_all_whitespace(str1), "Hello");
	EXPECT_EQ(utils::remove_all_whitespace(str2), "Hello");
}

TEST(UtilsTests, remove_leading_whitespace_removes_only_leading_whitespace_in_a_string) {
	std::string str1 = "    H e l l o";
	std::string str2 = "    Hello    ";
	EXPECT_EQ(utils::remove_leading_whitespace(str1), "H e l l o");
	EXPECT_EQ(utils::remove_leading_whitespace(str2), "Hello    ");
}

TEST(UtilsTests, remove_trailing_whitespace_removes_only_trailing_whitespace_in_a_string) {
	std::string str1 = "H e l l o    ";
	std::string str2 = "    Hello    ";
	EXPECT_EQ(utils::remove_trailing_whitespace(str1), "H e l l o");
	EXPECT_EQ(utils::remove_trailing_whitespace(str2), "    Hello");
}

TEST(UtilsTests, remove_leading_and_trailing_whitespace_removes_only_leading_and_trailing_whitespace_in_a_string) {
	std::string str1 = "    H e l l o    ";
	std::string str2 = "    Hello    ";
	EXPECT_EQ(utils::remove_leading_and_trailing_whitespace(str1), "H e l l o");
	EXPECT_EQ(utils::remove_leading_and_trailing_whitespace(str2), "Hello");
}

TEST(UtilsTests, create_equal_whitespace_in_a_string) {
	std::string str = "H  e   l   l     o";
	EXPECT_EQ(utils::create_equal_whitespace(str), "H e l l o");
}

TEST(UtilsTests, checking_a_file_name_without_a_period) {
	std::string file_name = "test";
	utils::FileNameCheck actual_check = utils::check_file_name(file_name, utils::FileExtensions::PPM);
	EXPECT_EQ(actual_check.file_name, "");
	EXPECT_TRUE(actual_check.err.occured);
	EXPECT_EQ(actual_check.err.msg, "Error: Filename 'test' does not contain period '.' or required extension.");
}

TEST(UtilsTests, checking_a_file_name_with_a_period_and_invalid_extension) {
	std::string file_name = "test.txt";
	utils::FileNameCheck actual_check = utils::check_file_name(file_name, utils::FileExtensions::PPM);
	EXPECT_EQ(actual_check.file_name, "");
	EXPECT_TRUE(actual_check.err.occured);
	EXPECT_EQ(actual_check.err.msg, "Error: Filename 'test.txt' does not contain correct extension '.ppm'.");
}

TEST(UtilsTests, checking_a_file_name_with_a_period_and_valid_extension) {
	std::string file_name = "test.ppm";
	utils::FileNameCheck actual_check = utils::check_file_name(file_name, utils::FileExtensions::PPM);
	EXPECT_EQ(actual_check.file_name, "test.ppm");
	EXPECT_FALSE(actual_check.err.occured);
	EXPECT_EQ(actual_check.err.msg, "");
}

TEST(UtilsTests, splittng_a_string) {
	std::string sentence = "The quick brown fox";
	std::vector<std::string> expected_segments = { "The", "quick", "brown", "fox" };
	utils::SplitStringResult split_result = utils::split_string(sentence, ' ');
	ASSERT_EQ(split_result.segments.size(), expected_segments.size());
	ASSERT_FALSE(split_result.failed);

	for (int idx = 0; idx < expected_segments.size(); idx++)
	{
		SCOPED_TRACE(idx); //write to the console in which iteration the error occurred
		ASSERT_EQ(split_result.segments[idx], expected_segments[idx]);
	}
}

TEST(UtilsTests, splittng_a_string_with_a_non_existent_delimiter) {
	std::string sentence = "The-quick-brown-fox";
	std::vector<std::string> expected_segments = { "The", "quick", "brown", "fox" };
	utils::SplitStringResult split_result = utils::split_string(sentence, ' ');
	ASSERT_EQ(split_result.segments.size(), 0);
	ASSERT_TRUE(split_result.failed);
}

TEST(UtilsTests, converting_an_empty_string_to_an_number_return_unknown) {
	std::string str = "";
	utils::Number num = utils::string_to_number(str);
	EXPECT_EQ(num.type, utils::NumberType::UNKNOWN);
}

TEST(UtilsTests, converting_a_string_word_to_an_number_returns_unknown) {
	std::string str = "dog";
	utils::Number num = utils::string_to_number(str);
	EXPECT_EQ(num.type, utils::NumberType::UNKNOWN);
}

TEST(UtilsTests, converting_a_string_to_a_positive_integer) {
	std::string str = "45";
	utils::Number num = utils::string_to_number(str);
	EXPECT_EQ(num.type, utils::NumberType::INT);
	EXPECT_EQ(num.int_value, 45);
	EXPECT_EQ(num.float_value, 0.0f);
}

TEST(UtilsTests, converting_a_string_to_a_positive_float) {
	std::string str = "4.5000";
	utils::Number num = utils::string_to_number(str);
	EXPECT_EQ(num.type, utils::NumberType::FLOAT);
	EXPECT_EQ(num.int_value, 0);
	EXPECT_EQ(num.float_value, 4.5f);
}
#pragma endregion

#pragma region Chapter1Tests
TEST(Chapter1_tests, A_tuple_with_w_as_1_is_a_point) {
	MockTuple a(4.3f, -4.2f, 3.1f, 1.0f);
	EXPECT_FLOAT_EQ(a[0], 4.3f);
	EXPECT_FLOAT_EQ(a[1], -4.2f);
	EXPECT_FLOAT_EQ(a[2], 3.1f);
	EXPECT_FLOAT_EQ(a[3], 1.0f);
	EXPECT_TRUE(a.IsPoint());
	EXPECT_FALSE(a.IsVector());
}

TEST(Chapter1_tests, A_tuple_with_w_as_0_is_a_vector) {
	MockTuple a(4.3f, -4.2f, 3.1f, 0.0f);
	EXPECT_FLOAT_EQ(a[0], 4.3f);
	EXPECT_FLOAT_EQ(a[1], -4.2f);
	EXPECT_FLOAT_EQ(a[2], 3.1f);
	EXPECT_FLOAT_EQ(a[3], 0.0f);
	EXPECT_FALSE(a.IsPoint());
	EXPECT_TRUE(a.IsVector());
}

TEST(Chapter1_tests, Create_a_point) {
	Point p(4, -4, 3);
	EXPECT_TRUE(p == MockTuple(4, -4, 3, 1));
}

TEST(Chapter1_tests, Create_a_vector) {
	Vector v(4, -4, 3);
	EXPECT_TRUE(v == MockTuple(4, -4, 3, 0));
}

TEST(Chapter1_tests, Adding_two_tuples) {
	MockTuple a1(3, -2, 5, 1);
	MockTuple a2(-2, 3, 1, 0);
	EXPECT_TRUE(a1 + a2 == MockTuple(1, 1, 6, 1));
}

TEST(Chapter1_tests, Subtracting_two_points) {
	Point p1(3, 2, 1);
	Point p2(5, 6, 7);
	EXPECT_TRUE(p1 - p2 == Vector(-2, -4, -6));
}

TEST(Chapter1_tests, Subtracting_a_vector_from_a_point) {
	Point p(3, 2, 1);
	Vector v(5, 6, 7);
	EXPECT_TRUE(p - v == Point(-2, -4, -6));
}

TEST(Chapter1_tests, Subtracting_two_vectors) {
	Vector v1(3, 2, 1);
	Vector v2(5, 6, 7);
	EXPECT_TRUE(v1 - v2 == Vector(-2, -4, -6));
}

TEST(Chapter1_tests, Subtracting_a_vector_from_the_zero_vector) {
	Vector zero(0, 0, 0);
	Vector v(1, -2, 3);
	EXPECT_TRUE(zero - v == Vector(-1, 2, -3));
}

TEST(Chapter1_tests, Negating_a_Tuple) {
	MockTuple a(1, -2, 3, -4);
	EXPECT_TRUE(-a == MockTuple(-1, 2, -3, 4));
}

TEST(Chapter1_tests, Multiplying_a_tuple_by_a_scalar) {
	MockTuple a(1, -2, 3, -4);
	EXPECT_TRUE(a * 3.5f == MockTuple(3.5f, -7, 10.5f, -14));
}

TEST(Chapter1_tests, Multiplying_a_tuple_by_a_fraction) {
	MockTuple a(1, -2, 3, -4);
	EXPECT_TRUE(a * 0.5f == MockTuple(0.5f, -1, 1.5f, -2));
}

TEST(Chapter1_tests, Dividing_a_tuple_by_a_scalar) {
	MockTuple a(1, -2, 3, -4);
	EXPECT_TRUE(a / 2 == MockTuple(0.5f, -1, 1.5f, -2));
}

TEST(Chapter1_tests, Computing_the_magnitude_of_vector_1_0_0) {
	Vector v(1, 0, 0);
	EXPECT_FLOAT_EQ(v.magnitude(), 1);
}

TEST(Chapter1_tests, Computing_the_magnitude_of_vector_0_1_0) {
	Vector v(0, 1, 0);
	EXPECT_FLOAT_EQ(v.magnitude(), 1);
}

TEST(Chapter1_tests, Computing_the_magnitude_of_vector_0_0_1) {
	Vector v(0, 0, 1);
	EXPECT_FLOAT_EQ(v.magnitude(), 1);
}

TEST(Chapter1_tests, Computing_the_magnitude_of_vector_1_2_3) {
	Vector v(1, 2, 3);
	EXPECT_FLOAT_EQ(v.magnitude(), (float)sqrt(14));
}

TEST(Chapter1_tests, Computing_the_magnitude_of_negated_vector_1_2_3) {
	Vector v(-1, -2, -3);
	EXPECT_FLOAT_EQ(v.magnitude(), (float)sqrt(14));
}

TEST(Chapter1_tests, Normalizing_vector_4_0_0_gives_1_0_0) {
	Vector v(4, 0, 0);
	EXPECT_TRUE(v.normalize() == Vector(1, 0, 0));
}

TEST(Chapter1_tests, Normalizing_vector_1_2_3) {
	Vector v(1, 2, 3);
	EXPECT_TRUE(v.normalize() == Vector(0.26726f, 0.53452f, 0.80178f));
}

TEST(Chapter1_tests, The_magnitude_of_a_normalized_vector) {
	Vector v(1, 2, 3);
	Vector norm = v.normalize();
	EXPECT_TRUE(utils::equal(norm.magnitude(), 1.0f));
}

TEST(Chapter1_tests, The_dot_product_of_two_vectors) {
	Vector a(1, 2, 3);
	Vector b(2, 3, 4);
	EXPECT_FLOAT_EQ(a.dot(b), 20);
}

TEST(Chapter1_tests, The_cross_product_of_two_vectors) {
	Vector a(1, 2, 3);
	Vector b(2, 3, 4);
	EXPECT_TRUE(a.cross(b) == Vector(-1, 2, -1));
	EXPECT_TRUE(b.cross(a) == Vector(1, -2, 1));
}
#pragma endregion

#pragma region Chapter2Tests
TEST(Chapter2_tests, Colors_are_red_green_blue_tuples) {
	Color c(-0.5f, 0.4f, 1.7f);
	EXPECT_FLOAT_EQ(c[0], -0.5f);
	EXPECT_FLOAT_EQ(c[1], 0.4f);
	EXPECT_FLOAT_EQ(c[2], 1.7f);
}

TEST(Chapter2_tests, Adding_colors) {
	Color c1(0.9f, 0.6f, 0.75f);
	Color c2(0.7f, 0.1f, 0.25f);
	EXPECT_TRUE(c1 + c2 == Color(1.6f, 0.7f, 1.0f));
}

TEST(Chapter2_tests, Subtracting_colors) {
	Color c1(0.9f, 0.6f, 0.75f);
	Color c2(0.7f, 0.1f, 0.25f);
	EXPECT_TRUE(c1 - c2 == Color(0.2, 0.5, 0.5));
}

TEST(Chapter2_tests, Multiplying_a_color_by_a_scalar) {
	Color c1(0.2f, 0.3f, 0.4f);
	EXPECT_TRUE(c1 * 2.0f == Color(0.4f, 0.6f, 0.8f));
}

TEST(Chapter2_tests, Multiplying_colors) {
	Color c1(1.0f, 0.2f, 0.4f);
	Color c2(0.9f, 1.0f, 0.1f);
	EXPECT_TRUE(c1 * c2 == Color(0.9f, 0.2f, 0.04f));
}

TEST(Chapter2_tests, Creating_a_canvas) {
	Canvas c(10, 20);
	for (int y = 0; y < c.GetHeight(); y++) {
		for (int x = 0; x < c.GetWidth(); x++) {
			ASSERT_TRUE(c.PixelAt(x, y) == Color(0, 0, 0));
		}
	}
}

TEST(Chapter2_tests, Writing_pixels_to_a_canvas) {
	Canvas c(10, 20);
	Color red(1, 0, 0);
	c.WritePixel(2, 3, red);
	EXPECT_TRUE(c.PixelAt(2, 3) == red);
}

TEST(Chapter2_tests, Constructing_the_PPM_header) {
	Canvas c(5, 3);
	std::string ppm = c.ExportAsPPM("test.ppm");
	std::vector<std::string> ppm_lines = utils::split_lines(ppm);
	EXPECT_EQ(ppm_lines[0], "P3");
	EXPECT_EQ(ppm_lines[1], "5 3");
	EXPECT_EQ(ppm_lines[2], "255");
}

TEST(Chapter2_tests, Constructing_the_PPM_pixel_data) {
	Canvas c(5, 3);
	Color c1(1.5f, 0, 0);
	Color c2(0, 0.5f, 0);
	Color c3(-0.5f, 0, 1);
	c.WritePixel(0, 0, c1);
	c.WritePixel(2, 1, c2);
	c.WritePixel(4, 2, c3);
	std::string ppm = c.ExportAsPPM("test.ppm");
	std::vector<std::string> ppm_lines = utils::split_lines(ppm);
	EXPECT_EQ(ppm_lines[3], "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0");
	EXPECT_EQ(ppm_lines[4], "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0");
	EXPECT_EQ(ppm_lines[5], "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255");
}

TEST(Chapter2_tests, Splitting_long_lines_in_PPM_files) {
	Canvas c(10, 2);
	for (int y = 0; y < c.GetHeight(); y++) {
		for (int x = 0; x < c.GetWidth(); x++) {
			c.WritePixel(x, y, Color(1, 0.8f, 0.6f));
		}
	}
	std::string ppm = c.ExportAsPPM("test.ppm");
	std::vector<std::string> ppm_lines = utils::split_lines(ppm);
	EXPECT_EQ(ppm_lines[3], "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
	EXPECT_EQ(ppm_lines[4], "153 255 204 153 255 204 153 255 204 153 255 204 153");
	EXPECT_EQ(ppm_lines[5], "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204");
	EXPECT_EQ(ppm_lines[6], "153 255 204 153 255 204 153 255 204 153 255 204 153");
}

TEST(Chapter2_tests, PPM_files_are_terminated_by_a_newline_character) {
	Canvas c(5, 3);
	std::string ppm = c.ExportAsPPM("test.ppm");
	EXPECT_EQ(ppm[ppm.size() - 1], '\n');
}
#pragma endregion

#pragma region Chapter3Tests
TEST(Chapter3_tests, Constructing_and_inspecting_a_4x4_matrix) {
	Matrix4 M(1, 2, 3, 4,
		5.5f, 6.5f, 7.5f, 8.5f,
		9, 10, 11, 12,
		13.5f, 14.5f, 15.5f, 16.5f);
	EXPECT_FLOAT_EQ(M(0, 0), 1);
	EXPECT_FLOAT_EQ(M(0, 3), 4);
	EXPECT_FLOAT_EQ(M(1, 0), 5.5f);
	EXPECT_FLOAT_EQ(M(1, 2), 7.5f);
	EXPECT_FLOAT_EQ(M(2, 2), 11);
	EXPECT_FLOAT_EQ(M(3, 0), 13.5f);
	EXPECT_FLOAT_EQ(M(3, 2), 15.5f);
}

TEST(Chapter3_tests, A_2x2_matrix_ought_to_be_representable) {
	Matrix2 M(-3, 5,
						1, -2);
	EXPECT_FLOAT_EQ(M(0, 0), -3);
	EXPECT_FLOAT_EQ(M(0, 1), 5);
	EXPECT_FLOAT_EQ(M(1, 0), 1);
	EXPECT_FLOAT_EQ(M(1, 1), -2);
}

TEST(Chapter3_tests, A_3x3_matrix_ought_to_be_representable) {
	Matrix3 M(-3, 5, 0,
						1, -2, -7,
						0, 1, 1);
	EXPECT_FLOAT_EQ(M(0, 0), -3);
	EXPECT_FLOAT_EQ(M(1, 1), -2);
	EXPECT_FLOAT_EQ(M(2, 2), 1);
}

TEST(Chapter3_tests, Matrix_equality_with_identical_matrices) {
	Matrix4 A(1, 2, 3, 4,
						5, 6, 7, 8,
						9, 8, 7, 6,
						5, 4, 3, 2);

	Matrix4 B(1, 2, 3, 4,
						5, 6, 7, 8,
						9, 8, 7, 6,
						5, 4, 3, 2);
	EXPECT_TRUE(A == B);
}

TEST(Chapter3_tests, Matrix_equality_with_different_matrices) {
	Matrix4 A(1, 2, 3, 4,
						5, 6, 7, 8,
						9, 8, 7, 6,
						5, 4, 3, 2);

	Matrix4 B(2, 3, 4, 5,
						6, 7, 8, 9,
						8, 7, 6, 5,
						4, 3, 2, 1);
	EXPECT_TRUE(A != B);
}

TEST(Chapter3_tests, Multiplying_two_matrices) {
	Matrix4 A(1, 2, 3, 4,
						5, 6, 7, 8,
						9, 8, 7, 6,
						5, 4, 3, 2);

	Matrix4 B(-2, 1, 2, 3,
						3, 2, 1, -1,
						4, 3, 6, 5,
						1, 2, 7, 8);
	Matrix4 C = A * B;
	EXPECT_TRUE(C == Matrix4(20, 22, 50, 48,
													 44, 54, 114, 108,
													 40, 58, 110, 102,
													 16, 26, 46, 42));
}

TEST(Chapter3_tests, A_matrix_multiplied_by_a_tuple) {
	Matrix4 A(1, 2, 3, 4,
						2, 4, 4, 2,
						8, 6, 4, 1,
						0, 0, 0, 1);
	MockTuple b(1, 2, 3, 1);
	MockTuple c = A * b;
	EXPECT_TRUE(c == MockTuple(18, 24, 33, 1));
}

TEST(Chapter3_tests, Multiplying_a_matrix_by_the_identity_matrix) {
	Matrix4 A(0, 1, 2, 4,
						1, 2, 4, 8,
						2, 4, 8, 16,
						4, 8, 16, 32);
	Matrix4 identity_matrix = Matrix4().identity();
	EXPECT_TRUE(A * identity_matrix == A);
}

TEST(Chapter3_tests, Multiplying_the_identity_matrix_by_a_tuple) {
	MockTuple a(1, 2, 3, 4);
	Matrix4 identity_matrix = Matrix4().identity();
	EXPECT_TRUE(identity_matrix * a == a);
}

TEST(Chapter3_tests, Transposing_a_matrix) {
	Matrix4 A(0, 9, 3, 0,
		9, 8, 0, 8,
		1, 8, 5, 3,
		0, 0, 5, 8);
	EXPECT_TRUE(A.transpose() == Matrix4(0, 9, 1, 0,
																			 9, 8, 8, 0,
																			 3, 0, 5, 5,
																			 0, 8, 3, 8));
}

TEST(Chapter3_tests, Transposing_the_identity_matrix) {
	Matrix4 identity_matrix = Matrix4().identity();
	Matrix4 A = identity_matrix.transpose();
	EXPECT_TRUE(A == identity_matrix);
}

TEST(Chapter3_tests, Calculating_the_determinant_of_a_2x2_matrix) {
	Matrix2 A(1, 5, -3, 2);
	EXPECT_FLOAT_EQ(A.determinant(), 17);
}

TEST(Chapter3_tests, A_submatrix_of_a_3x3_matrix_is_a_2x2_matrix) {
	Matrix3 A(1, 5, 0,
						-3, 2, 7,
						0, 6, -3);
	EXPECT_TRUE(A.submatrix(0, 2) == Matrix2(-3, 2,
																					0, 6));
}

TEST(Chapter3_tests, A_submatrix_of_a_4x4_matrix_is_a_3x3_matrix) {
	Matrix4 A(-6, 1, 1, 6,
						-8, 5, 8, 6,
						-1, 0, 8, 2,
						-7, 1, -1, 1);
	EXPECT_TRUE(A.submatrix(2, 1) == Matrix3(-6, 1, 6,
		-8, 8, 6,
		-7, -1, 1));
}

TEST(Chapter3_tests, Calculating_a_minor_of_a_3x3_matrix) {
	Matrix3 A(3, 5, 0,
						2, -1, -7,
						6, -1, 5);
	Matrix2 B = A.submatrix(1, 0);
	EXPECT_FLOAT_EQ(B.determinant(), 25);
	EXPECT_FLOAT_EQ(A.minor(1, 0), 25);
}

TEST(Chapter3_tests, Calculating_a_cofactor_of_a_3x3_matrix) {
	Matrix3 A(3, 5, 0,
						2, -1, -7,
						6, -1, 5);
	EXPECT_FLOAT_EQ(A.minor(0, 0), -12);
	EXPECT_FLOAT_EQ(A.cofactor(0, 0), -12);
	EXPECT_FLOAT_EQ(A.minor(1, 0), 25);
	EXPECT_FLOAT_EQ(A.cofactor(1, 0), -25);
}

TEST(Chapter3_tests, Calculating_the_determinant_of_a_3x3_matrix) {
	Matrix3 A(1, 2, 6,
						-5, 8, -4,
						2, 6, 4);
	EXPECT_FLOAT_EQ(A.cofactor(0, 0), 56);
	EXPECT_FLOAT_EQ(A.cofactor(0, 1), 12);
	EXPECT_FLOAT_EQ(A.cofactor(0, 2), -46);
	EXPECT_FLOAT_EQ(A.determinant(), -196);
}

TEST(Chapter3_tests, Calculating_the_determinant_of_a_4x4_matrix) {
	Matrix4 A(-2, -8, 3, 5,
						-3, 1, 7, 3,
						1, 2, -9, 6,
						-6, 7, 7, -9);
	EXPECT_FLOAT_EQ(A.cofactor(0, 0), 690);
	EXPECT_FLOAT_EQ(A.cofactor(0, 1), 447);
	EXPECT_FLOAT_EQ(A.cofactor(0, 2), 210);
	EXPECT_FLOAT_EQ(A.cofactor(0, 3), 51);
	EXPECT_FLOAT_EQ(A.determinant(), -4071);
}

TEST(Chapter3_tests, Testing_an_invertible_matrix_for_invertibility) {
	Matrix4 A(6, 4, 4, 4,
						5, 5, 7, 6,
						4, -9, 3, -7,
						9, 1, 7, -6);
	EXPECT_FLOAT_EQ(A.determinant(), -2120);
	EXPECT_TRUE(A.invertible());
}

TEST(Chapter3_tests, Testing_an_noninvertible_matrix_for_invertibility) {
	Matrix4 A(-4, 2, -2, -3,
						9, 6, 2, 6,
						0, -5, 1, -5,
						0, 0, 0, 0);
	EXPECT_FLOAT_EQ(A.determinant(), 0);
	EXPECT_FALSE(A.invertible());
}

TEST(Chapter3_tests, Calculating_the_inverse_of_a_matrix) {
	Matrix4 A(-5, 2, 6, -8,
						1, -5, 1, 8,
						7, 7, -6, -7,
						1, -3, 7, 4);

	Matrix4 B = A.inverse();
	EXPECT_FLOAT_EQ(A.determinant(), 532);
	EXPECT_FLOAT_EQ(A.cofactor(2, 3), -160);
	EXPECT_FLOAT_EQ(B(3, 2), -160.0f / 532.0f);
	EXPECT_FLOAT_EQ(A.cofactor(3, 2), 105);
	EXPECT_FLOAT_EQ(B(2, 3), 105.0f / 532.0f);
	EXPECT_TRUE(B == Matrix4(0.21805f, 0.45113f, 0.24060f, -0.04511f,
													-0.80827f, -1.45677f, -0.44361f, 0.52068f,
													-0.07895f, -0.22368f, -0.05263f, 0.19737f,
													-0.52256f, -0.81391f, -0.30075f, 0.30639f));
}

TEST(Chapter3_tests, Calculating_the_inverse_of_another_matrix) {
	Matrix4 A(8, -5, 9, 2,
						7, 5, 6, 1,
						-6, 0, 9, 6,
						-3, 0, -9, -4);
	EXPECT_TRUE(A.inverse() == Matrix4(-0.15385f, -0.15385f, -0.28205f, -0.53846f,
																		 -0.07692f, 0.12308f, 0.02564f, 0.03077f,
																		  0.35897f, 0.35897f, 0.43590f, 0.92308f,
																		 -0.69231f, -0.69231f, -0.76923f, -1.92308f));
}

TEST(Chapter3_tests, Calculating_the_inverse_of_a_third_matrix) {
	Matrix4 A(9, 3, 0, 9,
						-5, -2, -6, -3,
						-4, 9, 6, 4,
						-7, 6, 6, 2);
	EXPECT_TRUE(A.inverse() == Matrix4(-0.04074f, -0.07778f, 0.14444f, -0.22222f,
																		 -0.07778f, 0.03333f, 0.36667f, -0.33333f,
																		 -0.02901f, -0.14630f, -0.10926f, 0.12963f,
																		  0.17778f, 0.06667f, -0.26667f, 0.33333f));
}

TEST(Chapter3_tests, Multiplying_a_product_by_its_inverse) {
	Matrix4 A(3, -9, 7, 3,
						3, -8, 2, -9,
						-4, 4, 4, 1,
						-6, 5, -1, 1);

	Matrix4 B(8, 2, 2, 2,
						3, -1, 7, 0,
						7, 0, 5, 4,
						6, -2, 0, 5);

	Matrix4 C = A * B;
	EXPECT_TRUE(C * B.inverse() == A);
}
#pragma endregion

#pragma region Chapter4Tests
TEST(Chapter4_tests, Multiplying_by_a_translation_matrix) {
	Matrix4 transform = Matrix4().translation(5, -3, 2);
	Point p(-3, 4, 5);
	EXPECT_TRUE(transform * p == Point(2, 1, 7));
}

TEST(Chapter4_tests, Multiplying_by_the_inverse_of_a_translation_matrix) {
	Matrix4 transform = Matrix4().translation(5, -3, 2);
	Matrix4 ivn = transform.inverse();
	Point p(-3, 4, 5);
	EXPECT_TRUE(ivn * p == Point(-8, 7, 3));
}

TEST(Chapter4_tests, Translation_does_not_affect_vectors) {
	Matrix4 transform = Matrix4().translation(5, -3, 2);
	Vector v(-3, 4, 5);
	EXPECT_TRUE(transform * v == v);
}

TEST(Chapter4_tests, A_scaling_matrix_applied_to_a_point) {
	Matrix4 transform = Matrix4().scaling(2, 3, 4);
	Point p(-4, 6, 8);
	EXPECT_TRUE(transform * p == Point(-8, 18, 32));
}

TEST(Chapter4_tests, A_scaling_matrix_applied_to_a_vector) {
	Matrix4 transform = Matrix4().scaling(2, 3, 4);
	Vector v(-4, 6, 8);
	EXPECT_TRUE(transform * v == Vector(-8, 18, 32));
}

TEST(Chapter4_tests, Multiplying_by_the_inverse_of_a_scaling_matrix) {
	Matrix4 transform = Matrix4().scaling(2, 3, 4);
	Matrix4 inv = transform.inverse();
	Vector v(-4, 6, 8);
	EXPECT_TRUE(inv * v == Vector(-2, 2, 2));
}

TEST(Chapter4_tests, Reflection_is_scaling_by_a_negative_value) {
	Matrix4 transform = Matrix4().scaling(-1, 1, 1);
	Point p(2, 3, 4);
	EXPECT_TRUE(transform * p == Point(-2, 3, 4));
}

TEST(Chapter4_tests, Rotating_a_point_around_the_x_axis) {
	Point p(0, 1, 0);
	Matrix4 half_quarter = Matrix4().rotation_x(utils::kPI / 4.0f);
	Matrix4 full_quarter = Matrix4().rotation_x(utils::kPI / 2.0f);
	EXPECT_TRUE(half_quarter * p == Point(0, sqrt(2) / 2, sqrt(2) / 2));
	EXPECT_TRUE(full_quarter * p == Point(0, 0, 1));
}

TEST(Chapter4_tests, The_inverse_of_an_x_rotation_rotates_in_the_opposite_direction) {
	Point p(0, 1, 0);
	Matrix4 half_quarter = Matrix4().rotation_x(utils::kPI / 4.0f);
	Matrix4 inv = half_quarter.inverse();
	EXPECT_TRUE(inv * p == Point(0, sqrt(2) / 2, -sqrt(2) / 2));
}

TEST(Chapter4_tests, Rotating_a_point_around_the_y_axis) {
	Point p(0, 0, 1);
	Matrix4 half_quarter = Matrix4().rotation_y(utils::kPI / 4.0f);
	Matrix4 full_quarter = Matrix4().rotation_y(utils::kPI / 2.0f);
	EXPECT_TRUE(half_quarter * p == Point(sqrt(2) / 2, 0, sqrt(2) / 2));
	EXPECT_TRUE(full_quarter * p == Point(1, 0, 0));
}

TEST(Chapter4_tests, Rotating_a_point_around_the_z_axis) {
	Point p(0, 1, 0);
	Matrix4 half_quarter = Matrix4().rotation_z(utils::kPI / 4.0f);
	Matrix4 full_quarter = Matrix4().rotation_z(utils::kPI / 2.0f);
	EXPECT_TRUE(half_quarter * p == Point(-sqrt(2) / 2, sqrt(2) / 2, 0));
	EXPECT_TRUE(full_quarter * p == Point(-1, 0, 0));
}

TEST(Chapter4_tests, Shearing_transformation_moves_x_in_proportion_to_y) {
	Matrix4 transform = Matrix4().shearing(1, 0, 0, 0, 0, 0);
	Point p(2, 3, 4);
	EXPECT_TRUE(transform * p == Point(5, 3, 4));
}

TEST(Chapter4_tests, Shearing_transformation_moves_x_in_proportion_to_z) {
	Matrix4 transform = Matrix4().shearing(0, 1, 0, 0, 0, 0);
	Point p(2, 3, 4);
	EXPECT_TRUE(transform * p == Point(6, 3, 4));
}

TEST(Chapter4_tests, Shearing_transformation_moves_y_in_proportion_to_x) {
	Matrix4 transform = Matrix4().shearing(0, 0, 1, 0, 0, 0);
	Point p(2, 3, 4);
	EXPECT_TRUE(transform * p == Point(2, 5, 4));
}

TEST(Chapter4_tests, Shearing_transformation_moves_y_in_proportion_to_z) {
	Matrix4 transform = Matrix4().shearing(0, 0, 0, 1, 0, 0);
	Point p(2, 3, 4);
	EXPECT_TRUE(transform * p == Point(2, 7, 4));
}

TEST(Chapter4_tests, Shearing_transformation_moves_z_in_proportion_to_x) {
	Matrix4 transform = Matrix4().shearing(0, 0, 0, 0, 1, 0);
	Point p(2, 3, 4);
	EXPECT_TRUE(transform * p == Point(2, 3, 6));
}

TEST(Chapter4_tests, Shearing_transformation_moves_z_in_proportion_to_y) {
	Matrix4 transform = Matrix4().shearing(0, 0, 0, 0, 0, 1);
	Point p(2, 3, 4);
	EXPECT_TRUE(transform * p == Point(2, 3, 7));
}

TEST(Chapter4_tests, Individual_transformations_are_applied_in_sequence) {
	Point p(1, 0, 1);
	Matrix4 A = Matrix4().rotation_x(utils::kPI / 2.0f);
	Matrix4 B = Matrix4().scaling(5, 5, 5);
	Matrix4 C = Matrix4().translation(10, 5, 7);

	// Apply rotation first
	Point p2 = A * p;
	EXPECT_TRUE(p2 == Point(1, -1, 0));
	// then apply scaling
	Point p3 = B * p2;
	EXPECT_TRUE(p3 == Point(5, -5, 0));
	// then apply translation
	Point p4 = C * p3;
	EXPECT_TRUE(p4 == Point(15, 0, 7));
}

TEST(Chapter4_tests, Chained_transformations_must_be_applied_in_reverse_order) {
	Point p(1, 0, 1);
	Matrix4 A = Matrix4().rotation_x(utils::kPI / 2.0f);
	Matrix4 B = Matrix4().scaling(5, 5, 5);
	Matrix4 C = Matrix4().translation(10, 5, 7);

	Matrix4 T = C * B * A;
	EXPECT_TRUE(T * p == Point(15, 0, 7));
}

TEST(Chapter4_tests, Chained_function_transformations_must_be_applied_in_reverse_order) {
	Point p(1, 0, 1);
	Matrix4 T = Matrix4().translation(10, 5, 7).scaling(5, 5, 5).rotation_x(utils::kPI / 2.0f);
	EXPECT_TRUE(T * p == Point(15, 0, 7));
}
#pragma endregion

#pragma region Chapter5Tests
TEST(Chapter5_tests, Creating_and_querying_a_ray) {
	Point origin(1, 2, 3);
	Vector direction(4, 5, 6);
	Ray r(origin, direction);
	EXPECT_TRUE(r.GetOrigin() == origin);
	EXPECT_TRUE(r.GetDirection() == direction);
}

TEST(Chapter5_tests, Computing_a_point_from_a_distance) {
	Ray r(Point(2, 3, 4), Vector(1, 0, 0));
	EXPECT_TRUE(r.position(0) == Point(2, 3, 4));
	EXPECT_TRUE(r.position(1) == Point(3, 3, 4));
	EXPECT_TRUE(r.position(-1) == Point(1, 3, 4));
	EXPECT_TRUE(r.position(2.5f) == Point(4.5f, 3, 4));
}

TEST(Chapter9_tests, A_ray_intersects_a_sphere_at_two_points) {
	Ray r(Point(0, 0, -5), Vector(0, 0, 1));
	Sphere s("Sphere");
	std::vector<Intersection> xs = s.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs.size(), 2);
	EXPECT_FLOAT_EQ(xs[0].GetTime(), 4.0f);
	EXPECT_FLOAT_EQ(xs[1].GetTime(), 6.0f);
}

TEST(Chapter9_tests, A_ray_intersects_a_sphere_at_a_tangent) {
	Ray r(Point(0, 1, -5), Vector(0, 0, 1));
	Sphere s("Sphere");
	std::vector<Intersection> xs = s.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs.size(), 2);
	EXPECT_FLOAT_EQ(xs[0].GetTime(), 5.0f);
	EXPECT_FLOAT_EQ(xs[1].GetTime(), 5.0f);
}

TEST(Chapter9_tests, A_ray_misses_a_sphere) {
	Ray r(Point(0, 2, -5), Vector(0, 0, 1));
	Sphere s("Sphere");
	std::vector<Intersection> xs = s.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs.size(), 0);
}

TEST(Chapter9_tests, A_ray_originates_inside_a_sphere) {
	Ray r(Point(0, 0, 0), Vector(0, 0, 1));
	Sphere s("Sphere");
	std::vector<Intersection> xs = s.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs.size(), 2);
	EXPECT_FLOAT_EQ(xs[0].GetTime(), -1.0f);
	EXPECT_FLOAT_EQ(xs[1].GetTime(), 1.0f);
}

TEST(Chapter9_tests, A_sphere_is_behind_a_ray) {
	Ray r(Point(0, 0, 5), Vector(0, 0, 1));
	Sphere s("Sphere");
	std::vector<Intersection> xs = s.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs.size(), 2);
	EXPECT_FLOAT_EQ(xs[0].GetTime(), -6.0f);
	EXPECT_FLOAT_EQ(xs[1].GetTime(), -4.0f);
}

TEST(Chapter5_tests, An_intersection_encapsulates_time_and_object) {
	Sphere* s = new Sphere("Sphere");
	Intersection i(3.5f, s);
	EXPECT_FLOAT_EQ(i.GetTime(), 3.5f);
	EXPECT_TRUE((*i.GetObject()) == (*s));
}

TEST(Chapter5_tests, Aggregating_intersections) {
	Sphere* s = new Sphere("Sphere");
	Intersection i1(1, s);
	Intersection i2(2, s);
	std::vector<Intersection> xs = Intersection::intersections({ i1, i2 });
	EXPECT_EQ(xs.size(), 2);
	EXPECT_FLOAT_EQ(xs[0].GetTime(), 1.0f);
	EXPECT_FLOAT_EQ(xs[1].GetTime(), 2.0f);
}

//TEST(Chapter5_tests, Intersect_sets_the_object_on_the_intersection) {
//	Ray r(Point(0, 0, -5), Vector(0, 0, 1));
//	Sphere s;
//	std::vector<float> xs = r.intersect(s);
//	EXPECT_EQ(xs.size(), 2);
//	EXPECT_TRUE(xs[0].GetObject() == s);
//	EXPECT_TRUE(xs[1].GetObject() == s);
//}

TEST(Chapter5_tests, The_hit_when_all_intersections_have_positive_time) {
	Sphere* s = new Sphere("Sphere");
	Intersection i1(1, s);
	Intersection i2(2, s);
	std::vector<Intersection> xs = Intersection::intersections({ i2, i1 });
	Hit h = Hit::hit(xs);
	EXPECT_TRUE(h.i == i1);
}

TEST(Chapter5_tests, The_hit_when_some_intersections_have_negative_time) {
	Sphere* s = new Sphere("Sphere");
	Intersection i1(-1, s);
	Intersection i2(1, s);
	std::vector<Intersection> xs = Intersection::intersections({ i2, i1 });
	Hit h = Hit::hit(xs);
	EXPECT_TRUE(h.i == i2);
}

TEST(Chapter5_tests, The_hit_when_all_intersections_have_negative_time) {
	Sphere* s = new Sphere("Sphere");
	Intersection i1(-2, s);
	Intersection i2(-1, s);
	std::vector<Intersection> xs = Intersection::intersections({ i2, i1 });
	Hit h = Hit::hit(xs);
	EXPECT_TRUE(h.result == HitResult::NO_HIT);
}

TEST(Chapter5_tests, The_hit_is_always_the_lowest_nonnegative_intersection) {
	Sphere* s = new Sphere("Sphere");
	Intersection i1(5, s);
	Intersection i2(7, s);
	Intersection i3(-3, s);
	Intersection i4(2, s);
	std::vector<Intersection> xs = Intersection::intersections({ i1, i2, i3, i4 });
	Hit h = Hit::hit(xs);
	EXPECT_TRUE(h.i == i4);
}

TEST(Chapter5_tests, Translating_a_ray) {
	Ray r(Point(1, 2, 3), Vector(0, 1, 0));
	Matrix4 m = Matrix4().translation(3, 4, 5);
	Ray r2 = r.transform(m);
	EXPECT_TRUE(r2.GetOrigin() == Point(4, 6, 8));
	EXPECT_TRUE(r2.GetDirection() == Vector(0, 1, 0));
}

TEST(Chapter5_tests, Scaling_a_ray) {
	Ray r(Point(1, 2, 3), Vector(0, 1, 0));
	Matrix4 m = Matrix4().scaling(2, 3, 4);
	Ray r2 = r.transform(m);
	EXPECT_TRUE(r2.GetOrigin() == Point(2, 6, 12));
	EXPECT_TRUE(r2.GetDirection() == Vector(0, 3, 0));
}

TEST(Chapter9_tests, The_default_transformation) {
	MockShape s("Shape");
	EXPECT_TRUE(s.GetTransform() == Matrix4().identity());
}

TEST(Chapter9_tests, Assigning_a_transformation) {
	MockShape s("Shape");
	s.SetTransform(Matrix4().translation(2, 3, 4));
	EXPECT_TRUE(s.GetTransform() == Matrix4().translation(2, 3, 4));
}

TEST(Chapter9_tests, Intersecting_a_scaled_shape_with_a_ray) {
	Ray r(Point(0, 0, -5), Vector(0, 0, 1));
	MockShape s("Shape");
	s.SetTransform(Matrix4().scaling(2, 2, 2));
	std::vector<Intersection> xs = r.intersect(&s);
	EXPECT_TRUE(s.GetSavedRay().origin == Point(0, 0, -2.5));
	EXPECT_TRUE(s.GetSavedRay().direction == Vector(0, 0, 0.5));
}

TEST(Chapter9_tests, Intersecting_a_translated_shape_with_a_ray) {
	Ray r(Point(0, 0, -5), Vector(0, 0, 1));
	MockShape s("Shape");
	s.SetTransform(Matrix4().translation(5, 0, 0));
	std::vector<Intersection> xs = r.intersect(&s);
	EXPECT_TRUE(s.GetSavedRay().origin == Point(-5, 0, -5));
	EXPECT_TRUE(s.GetSavedRay().direction == Vector(0, 0, 1));
}
#pragma endregion

#pragma region Chapter6Tests
TEST(Chapter9_tests, The_normal_on_a_sphere_at_a_point_on_the_x_axis) {
	Sphere s("Sphere");
	Vector n = s.local_normal_at(Point(1, 0, 0));
	EXPECT_TRUE(n == Vector(1, 0, 0));
}

TEST(Chapter9_tests, The_normal_on_a_sphere_at_a_point_on_the_y_axis) {
	Sphere s("Sphere");
	Vector n = s.local_normal_at(Point(0, 1, 0));
	EXPECT_TRUE(n == Vector(0, 1, 0));
}

TEST(Chapter9_tests, The_normal_on_a_sphere_at_a_point_on_the_z_axis) {
	Sphere s("Sphere");
	Vector n = s.local_normal_at(Point(0, 0, 1));
	EXPECT_TRUE(n == Vector(0, 0, 1));
}

TEST(Chapter9_tests, The_normal_on_a_sphere_at_a_nonaxial_point) {
	Sphere s("Sphere");
	Vector n = s.local_normal_at(Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
	EXPECT_TRUE(n == Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
}

TEST(Chapter9_tests, The_normal_is_a_normalized_vector) {
	Sphere s("Sphere");
	Vector n = s.local_normal_at(Point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
	EXPECT_TRUE(n == n.normalize());
}

TEST(Chapter9_tests, Computing_the_normal_on_a_translated_shape) {
	MockShape s("Shape");
	s.SetTransform(Matrix4().translation(0, 1, 0));
	Vector n = s.normal_at(Point(0, 1.70711f, -0.70711f));
	EXPECT_TRUE(n == Vector(0, 0.70711f, -0.70711f));
}

TEST(Chapter9_tests, Computing_the_normal_on_a_transformed_shape) {
	MockShape s("Shape");
	Matrix4 m = Matrix4().scaling(1, 0.5f, 1) * Matrix4().rotation_z(utils::kPI / 5.0f);
	s.SetTransform(m);
	Vector n = s.normal_at(Point(0, sqrt(2) / 2, -sqrt(2) / 2));
	EXPECT_TRUE(n == Vector(0, 0.97014f, -0.24254f));
}

TEST(Chapter6_tests, Reflecting_a_vector_approaching_at_45_degrees) {
	Vector v(1, -1, 0);
	Vector n(0, 1, 0);
	Vector r = v.reflect(n);
	EXPECT_TRUE(r == Vector(1, 1, 0));
}

TEST(Chapter6_tests, Reflecting_a_vector_off_a_slanted_surface) {
	Vector v(0, -1, 0);
	Vector n(sqrt(2) / 2, sqrt(2) / 2, 0);
	Vector r = v.reflect(n);
	EXPECT_TRUE(r == Vector(1, 0, 0));
}

TEST(Chapter6_tests, A_point_light_has_a_position_and_intensity) {
	Color intensity(1, 1, 1);
	Point position(0, 0, 0);
	PointLight light("PointLight", position, intensity);
	EXPECT_TRUE(light.GetPosition() == position);
	EXPECT_TRUE(light.GetIntensity() == intensity);
}

TEST(Chapter6_tests, The_default_material) {
	Material m;
	EXPECT_TRUE(m.GetColor() == Color(1, 1, 1));
	EXPECT_FLOAT_EQ(m.GetAmbient(), 0.1f);
	EXPECT_FLOAT_EQ(m.GetDiffuse(), 0.9f);
	EXPECT_FLOAT_EQ(m.GetSpecular(), 0.9f);
	EXPECT_FLOAT_EQ(m.GetShininess(), 200.0f);
}

TEST(Chapter9_tests, The_default_material) {
	MockShape s("Shape");
	Material m = s.GetMaterial();
	EXPECT_TRUE(m == Material());
}

TEST(Chapter9_tests, Assigning_a_material) {
	MockShape s("Shape");
	Material m;
	m.SetAmbient(1);
	s.SetMaterial(m);
	EXPECT_TRUE(s.GetMaterial() == m);
}

TEST(Chapter6_tests, Lighting_with_the_eye_between_the_light_and_the_surface) {
	Sphere object("Sphere");
	Material m;
	Point position(0, 0, 0);
	Vector evev(0, 0, -1);
	Vector normalv(0, 0, -1);
	PointLight light("PointLight", Point(0, 0, -10), Color(1, 1, 1));
	bool in_shadow = false;
	Color result = Engine::lighting(m, &object, light, position, evev, normalv, in_shadow);
	EXPECT_TRUE(result == Color(1.9f, 1.9f, 1.9f));
}

TEST(Chapter6_tests, Lighting_with_the_eye_between_light_and_surface_eye_offset_45_degrees) {
	Sphere object("Sphere");
	Material m;
	Point position(0, 0, 0);
	Vector evev(0, sqrt(2) / 2, -sqrt(2) / 2);
	Vector normalv(0, 0, -1);
	PointLight light("PointLight", Point(0, 0, -10), Color(1, 1, 1));
	bool in_shadow = false;
	Color result = Engine::lighting(m, &object, light, position, evev, normalv, in_shadow);
	EXPECT_TRUE(result == Color(1.0f, 1.0f, 1.0f));
}

TEST(Chapter6_tests, Lighting_with_eye_opposite_surface_light_offset_45_degrees) {
	Sphere object("Sphere");
	Material m;
	Point position(0, 0, 0);
	Vector evev(0, 0, -1);
	Vector normalv(0, 0, -1);
	PointLight light("PointLight", Point(0, 10, -10), Color(1, 1, 1));
	bool in_shadow = false;
	Color result = Engine::lighting(m, &object, light, position, evev, normalv, in_shadow);
	EXPECT_TRUE(result == Color(0.7364f, 0.7364f, 0.7364f));
}

TEST(Chapter6_tests, Lighting_with_eye_in_the_path_of_the_reflection_vector) {
	Sphere object("Sphere");
	Material m;
	Point position(0, 0, 0);
	Vector evev(0, -sqrt(2) / 2, -sqrt(2) / 2);
	Vector normalv(0, 0, -1);
	PointLight light("PointLight", Point(0, 10, -10), Color(1, 1, 1));
	bool in_shadow = false;
	Color result = Engine::lighting(m, &object, light, position, evev, normalv, in_shadow);
	EXPECT_TRUE(result.round(4) == Color(1.6364f, 1.6364f, 1.6364f));
}

TEST(Chapter6_tests, Lighting_with_the_light_behind_the_surface) {
	Sphere object("Sphere");
	Material m;
	Point position(0, 0, 0);
	Vector evev(0, 0, -1);
	Vector normalv(0, 0, -1);
	PointLight light("PointLight", Point(0, 0, 10), Color(1, 1, 1));
	bool in_shadow = true;
	Color result = Engine::lighting(m, &object, light, position, evev, normalv, in_shadow);
	EXPECT_TRUE(result == Color(0.1f, 0.1f, 0.1f));
}
#pragma endregion

#pragma region Chapter7Tests
TEST(Chapter7_tests, Creating_a_world) {
	World w;
	EXPECT_EQ(w.GetObjectCount(), 0);
	EXPECT_TRUE(w.ContainsLightSource() == false);
}

TEST(Chapter7_tests, The_default_world) {
	PointLight light("PointLight1", Point(-10, 10, -10), Color(1, 1, 1));
	Sphere s1("Sphere1");
	Material m;
	m.SetColor(Color(0.8f, 1.0f, 0.6f));
	m.SetDiffuse(0.7f);
	m.SetSpecular(0.2f);
	s1.SetMaterial(m);
	Sphere s2("Sphere2");
	s2.SetTransform(Matrix4().scaling(0.5f, 0.5f, 0.5f));

	World w(WorldType::DEFAULT);
	EXPECT_TRUE((*w.GetLights()[0]) == light);
	EXPECT_TRUE(w.ContainsObject(&s1));
	EXPECT_TRUE(w.ContainsObject(&s2));
}

TEST(Chapter7_tests, Intersect_a_world_with_a_ray) {
	World w(WorldType::DEFAULT);
	Ray r(Point(0, 0, -5), Vector(0, 0, 1));
	std::vector<Intersection> xs = r.intersect(w);
	EXPECT_EQ(xs.size(), 4);
	EXPECT_FLOAT_EQ(xs[0].GetTime(), 4.0f);
	EXPECT_FLOAT_EQ(xs[1].GetTime(), 4.5f);
	EXPECT_FLOAT_EQ(xs[2].GetTime(), 5.5f);
	EXPECT_FLOAT_EQ(xs[3].GetTime(), 6.0f);
}

TEST(Chapter7_tests, Precomputing_the_state_of_an_intersection) {
	Ray r(Point(0, 0, -5), Vector(0, 0, 1));
	Sphere* shape = new Sphere("Sphere");
	Intersection i(4, shape);
	Engine::Computation comps = Engine::prepare_computations(i, r);
	EXPECT_FLOAT_EQ(comps.time, i.GetTime());
	EXPECT_TRUE(comps.object == i.GetObject());
	EXPECT_TRUE(comps.point == Point(0, 0, -1));
	EXPECT_TRUE(comps.eyev == Vector(0, 0, -1));
	EXPECT_TRUE(comps.normalv == Vector(0, 0, -1));
}

TEST(Chapter7_tests, The_hit_when_a_intersection_occurs_on_the_outside) {
	Ray r(Point(0, 0, -5), Vector(0, 0, 1));
	Sphere* shape = new Sphere("Sphere");
	Intersection i(4, shape);
	Engine::Computation comps = Engine::prepare_computations(i, r);
	EXPECT_FALSE(comps.inside);
}

TEST(Chapter7_tests, The_hit_when_a_intersection_occurs_on_the_inside) {
	Ray r(Point(0, 0, 0), Vector(0, 0, 1));
	Sphere* shape = new Sphere("Sphere");
	Intersection i(1, shape);
	Engine::Computation comps = Engine::prepare_computations(i, r);
	EXPECT_TRUE(comps.point == Point(0, 0, 1));
	EXPECT_TRUE(comps.eyev == Vector(0, 0, -1));
	EXPECT_TRUE(comps.inside);
	EXPECT_TRUE(comps.normalv == Vector(0, 0, -1)); // normal would have been (0, 0, 1), but is inverted!
}

TEST(Chapter7_tests, Shading_an_intersection) {
	World w(WorldType::DEFAULT);
	Ray r(Point(0, 0, -5), Vector(0, 0, 1));
	Shape* shape = w.GetShapes()[0];
	Intersection i(4, shape);
	Engine::Computation comps = Engine::prepare_computations(i, r);
	Color c = Engine::shade_hit(w, comps);
	EXPECT_TRUE(c == Color(0.38066f, 0.47583f, 0.2855f));
}

TEST(Chapter7_tests, Shading_an_intersection_from_the_inside) {
	World w(WorldType::DEFAULT);
	// Get the default light
	PointLight* light = (PointLight*)w.GetLights()[0];
	// remove the default light and add a new light
	w.DeleteObject("PointLight1");
	EXPECT_FALSE(w.ContainsLightSource());
	w.AddObject(new PointLight("PointLight1", Point(0, 0.25f, 0), Color(1, 1, 1)));

	Ray r(Point(0, 0, 0), Vector(0, 0, 1));
	Shape* shape = w.GetShapes()[1];
	Intersection i(0.5f, shape);
	Engine::Computation comps = Engine::prepare_computations(i, r);
	Color c = Engine::shade_hit(w, comps);
	EXPECT_TRUE(c == Color(0.90498f, 0.90498f, 0.90498f));
}

TEST(Chapter7_tests, The_color_when_a_ray_misses) {
	World w(WorldType::DEFAULT);
	Ray r(Point(0, 0, -5), Vector(0, 1, 0));
	Color c = Engine::color_at(w, r);
	EXPECT_TRUE(c == Color(0, 0, 0));
}

TEST(Chapter7_tests, The_color_when_a_ray_hits) {
	World w(WorldType::DEFAULT);
	Ray r(Point(0, 0, -5), Vector(0, 0, 1));
	Color c = Engine::color_at(w, r);
	EXPECT_TRUE(c == Color(0.38066f, 0.47583f, 0.2855f));
}

TEST(Chapter7_tests, The_color_with_an_intersection_behind_the_ray) {
	World w(WorldType::DEFAULT);
	Shape* outer = w.GetShapes()[0];
	outer->GetMaterial().SetAmbient(1);
	Shape* inner = w.GetShapes()[1];
	inner->GetMaterial().SetAmbient(1);
	Ray r(Point(0, 0, 0.75f), Vector(0, 0, -1));
	Color c = Engine::color_at(w, r);
	EXPECT_TRUE(c == inner->GetMaterial().GetColor());
}

TEST(Chapter7_tests, The_transformation_matrix_for_the_default_orientation) {
	Matrix4 identity_matrix = Matrix4().identity();
	Point from(0, 0, 0);
	Point to(0, 0, -1);
	Vector up(0, 1, 0);
	Matrix4 t = Matrix4().view_transform(from, to, up);
	EXPECT_TRUE(t == identity_matrix);
}

TEST(Chapter7_tests, A_view_transformation_matrix_looking_in_positive_z_direction) {
	Point from(0, 0, 0);
	Point to(0, 0, 1);
	Vector up(0, 1, 0);
	Matrix4 t = Matrix4().view_transform(from, to, up);
	EXPECT_TRUE(t == Matrix4().scaling(-1, 1, -1));
}

TEST(Chapter7_tests, The_view_transformation_moves_the_world) {
	Point from(0, 0, 8);
	Point to(0, 0, 1);
	Vector up(0, 1, 0);
	Matrix4 t = Matrix4().view_transform(from, to, up);
	EXPECT_TRUE(t == Matrix4().translation(0, 0, -8));
}

TEST(Chapter7_tests, An_arbitrary_view_transformation) {
	Point from(1, 3, 2);
	Point to(4, -2, 8);
	Vector up(1, 1, 0);
	Matrix4 t = Matrix4().view_transform(from, to, up);
	EXPECT_TRUE(t == Matrix4(-0.50709f, 0.50709f,  0.67612f, -2.36643f,
														0.76772f, 0.60609f,  0.12122f, -2.82843f,
													 -0.35857f, 0.59761f, -0.71714f,  0.00000f,
														0.00000f, 0.00000f,  0.00000f,  1.00000f));
}

TEST(Chapter7_tests, Constructing_a_camera) {
	int hsize = 160;
	int vsize = 120;
	float field_of_view = utils::kPI / 2.0f;
	Camera c("Camera", hsize, vsize, field_of_view);
	EXPECT_EQ(c.GetHorizontalSize(), 160);
	EXPECT_EQ(c.GetVerticalSize(), 120);
	EXPECT_TRUE(utils::equal(c.GetFieldOfView(), utils::kPI / 2.0f));
	Matrix4 identity_matrix = Matrix4().identity();
	EXPECT_TRUE(c.GetTransform() == identity_matrix);
}

TEST(Chapter7_tests, The_pixel_size_for_a_horizontal_canvas) {
	Camera c("Camera", 200, 125, utils::kPI / 2.0f);
	EXPECT_FLOAT_EQ(c.GetPixelSize(), 0.01f);
}

TEST(Chapter7_tests, The_pixel_size_for_a_vertical_canvas) {
	Camera c("Camera", 125, 200, utils::kPI / 2.0f);
	EXPECT_FLOAT_EQ(c.GetPixelSize(), 0.01f);
}

TEST(Chapter7_tests, Constructing_a_ray_through_the_center_of_the_canvas) {
	Camera c("Camera", 201, 101, utils::kPI / 2.0f);
	Ray r = Engine::ray_for_pixel(c, 100, 50);
	EXPECT_TRUE(r.GetOrigin() == Point(0, 0, 0));
	EXPECT_TRUE(r.GetDirection() == Vector(0, 0, -1));
}

TEST(Chapter7_tests, Constructing_a_ray_through_a_corner_of_the_canvas) {
	Camera c("Camera", 201, 101, utils::kPI / 2.0f);
	Ray r = Engine::ray_for_pixel(c, 0, 0);
	EXPECT_TRUE(r.GetOrigin() == Point(0, 0, 0));
	EXPECT_TRUE(r.GetDirection() == Vector(0.66519f, 0.33259f, -0.66851f));
}

TEST(Chapter7_tests, Constructing_a_ray_when_the_camera_is_transformed) {
	Camera c("Camera", 201, 101, utils::kPI / 2.0f);
	c.SetTransform(Matrix4().rotation_y(utils::kPI / 4.0f) * Matrix4().translation(0, -2, 5));
	Ray r = Engine::ray_for_pixel(c, 100, 50);
	EXPECT_TRUE(r.GetOrigin() == Point(0, 2, -5));
	EXPECT_TRUE(r.GetDirection() == Vector(sqrt(2) / 2, 0, -sqrt(2) / 2));
}

TEST(Chapter7_tests, Rendering_a_world_with_a_camera) {
	World w(WorldType::DEFAULT);
	Camera c("Camera", 11, 11, utils::kPI / 2.0f);
	Point from(0, 0, -5);
	Point to(0, 0, 0);
	Vector up(0, 1, 0);
	c.SetTransform(Matrix4().view_transform(from, to, up));
	Canvas image = Engine::render(c, w);
	EXPECT_TRUE(image.PixelAt(5, 5) == Color(0.38066f, 0.47583f, 0.2855f));
}
#pragma endregion

#pragma region Chapter8Tests
TEST(Chapter8_tests, Lighting_with_the_surface_in_shadow) {
	Sphere object("Sphere");
	Material m;
	Point position(0, 0, 0);
	Vector evev(0, 0, -1);
	Vector normalv(0, 0, -1);
	PointLight light("PointLight", Point(0, 0, -10), Color(1, 1, 1));
	bool in_shadow = true;
	Color result = Engine::lighting(m, &object,  light, position, evev, normalv, in_shadow);
	EXPECT_TRUE(result == Color(0.1f, 0.1f, 0.1f));
}

TEST(Chapter8_tests, There_is_no_shadow_when_nothing_is_collinear_with_point_and_light) {
	World w(WorldType::DEFAULT);
	Point p(0, 10, 0);
	EXPECT_FALSE(Engine::is_shadowed(w, p));
}

TEST(Chapter8_tests, The_shadow_when_an_object_is_between_the_point_and_the_light) {
	World w(WorldType::DEFAULT);
	Point p(10, -10, 10);
	EXPECT_TRUE(Engine::is_shadowed(w, p));
}

TEST(Chapter8_tests, There_is_no_shadow_when_an_object_is_behind_the_light) {
	World w(WorldType::DEFAULT);
	Point p(-20, 20, -20);
	EXPECT_FALSE(Engine::is_shadowed(w, p));
}

TEST(Chapter8_tests, There_is_no_shadow_when_an_object_is_behind_the_point) {
	World w(WorldType::DEFAULT);
	Point p(-2, 2, -2);
	EXPECT_FALSE(Engine::is_shadowed(w, p));
}

TEST(Chapter8_tests, shade_hit_is_given_an_intersection_in_shadow) {
	World w(WorldType::EMPTY);
	PointLight light("PointLight1", Point(0, 0, -10), Color(1.0f, 1.0f, 1.0f));
	w.AddObject(&light);
	Sphere* s1 = new Sphere("Sphere1");
	w.AddObject(s1);
	Sphere* s2 = new Sphere("Sphere2", Matrix4().translation(0, 0, 10));
	w.AddObject(s2);
	Ray r(Point(0, 0, 5), Vector(0, 0, 1));
	Intersection i(4, s2);
	Engine::Computation comps = Engine::prepare_computations(i, r);
	Color c = Engine::shade_hit(w, comps);
	EXPECT_TRUE(c == Color(0.1f, 0.1f, 0.1f));
}

TEST(Chapter8_tests, The_hit_should_offset_the_point) {
	Ray r(Point(0, 0, -5), Vector(0, 0, 1));
	Sphere* shape = new Sphere("Sphere", Matrix4().translation(0, 0, 1));
	Intersection i(5, shape);
	Engine::Computation comps = Engine::prepare_computations(i, r);
	EXPECT_LT(comps.over_point[2], -utils::kEPSILON / 2);
	EXPECT_GT(comps.point[2], comps.over_point[2]);
}
#pragma endregion

#pragma region Chapter9Tests
TEST(Chapter9_tests, A_sphere_is_a_shape) {
	Sphere s("Sphere");
	EXPECT_TRUE(utils::instance_of<Shape>(&s));
}

TEST(Chapter9_tests, The_normal_of_a_plane_is_constant_everywhere) {
	Plane p("Plane");
	Vector n1 = p.local_normal_at(Point(0, 0, 0));
	Vector n2 = p.local_normal_at(Point(10, 0, -10));
	Vector n3 = p.local_normal_at(Point(-5, 0, 150));
	EXPECT_TRUE(n1 == Vector(0, 1, 0));
	EXPECT_TRUE(n2 == Vector(0, 1, 0));
	EXPECT_TRUE(n3 == Vector(0, 1, 0));
}

TEST(Chapter9_tests, Intersect_with_a_ray_parallel_to_the_plane) {
	Plane p("Plane");
	Ray r(Point(0, 10, 0), Vector(0, 0, 1));
	std::vector<Intersection> xs = p.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs.size(), 0);
}

TEST(Chapter9_tests, Intersect_a_plane_with_a_coplanar_ray) {
	Plane p("Plane");
	Ray r(Point(0, 0, 0), Vector(0, 0, 1));
	std::vector<Intersection> xs = p.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs.size(), 0);
}

TEST(Chapter9_tests, A_ray_intersecting_a_plane_from_above) {
	Plane p("Plane");
	Ray r(Point(0, 1, 0), Vector(0, -1, 0));
	std::vector<Intersection> xs = p.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs.size(), 1);
	EXPECT_FLOAT_EQ(xs[0].GetTime(), 1.0f);
	EXPECT_TRUE((*xs[0].GetObject()) == p);
}

TEST(Chapter9_tests, A_ray_intersecting_a_plane_from_below) {
	Plane p("Plane");
	Ray r(Point(0, -1, 0), Vector(0, 1, 0));
	std::vector<Intersection> xs = p.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs.size(), 1);
	EXPECT_FLOAT_EQ(xs[0].GetTime(), 1.0f);
	EXPECT_TRUE((*xs[0].GetObject()) == p);
}
#pragma endregion

#pragma region Chapter10Tests
TEST(Chapter10_tests, Color_constants_black_and_white_exist) {
	EXPECT_TRUE(Colors::Black == Color(0, 0, 0));
	EXPECT_TRUE(Colors::White == Color(1, 1, 1));
}

TEST(Chapter10_tests, Creating_a_stripe_pattern) {
	StripePattern pattern = StripePattern(Colors::White, Colors::Black);
	auto a_variant = pattern.GetA();
	auto b_variant = pattern.GetB();
	Color colorA = (*(std::get_if<Color>(&a_variant)));
	Color colorB = (*(std::get_if<Color>(&b_variant)));
	EXPECT_TRUE(colorA == Colors::White);
	EXPECT_TRUE(colorB == Colors::Black);
}

TEST(Chapter10_tests, A_stripe_pattern_is_constant_in_y) {
	StripePattern pattern = StripePattern(Colors::White, Colors::Black);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 0, 0)) == Colors::White);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 1, 0)) == Colors::White);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 2, 0)) == Colors::White);
}

TEST(Chapter10_tests, A_stripe_pattern_is_constant_in_z) {
	StripePattern pattern = StripePattern(Colors::White, Colors::Black);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 0, 0)) == Colors::White);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 0, 1)) == Colors::White);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 0, 2)) == Colors::White);
}

TEST(Chapter10_tests, A_stripe_pattern_alternates_in_x) {
	StripePattern pattern = StripePattern(Colors::White, Colors::Black);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 0, 0)) == Colors::White);
	EXPECT_TRUE(pattern.pattern_at(Point(0.9, 0, 0)) == Colors::White);
	EXPECT_TRUE(pattern.pattern_at(Point(1, 0, 0)) == Colors::Black);
	EXPECT_TRUE(pattern.pattern_at(Point(-0.1, 0, 0)) == Colors::Black);
	EXPECT_TRUE(pattern.pattern_at(Point(-1, 0, 0)) == Colors::Black);
	EXPECT_TRUE(pattern.pattern_at(Point(-1.1, 0, 0)) == Colors::White);
}

TEST(Chapter10_tests, Lighting_with_a_pattern_applied) {
	Sphere object("Sphere");
	Material m;
	StripePattern p = StripePattern(Color(1, 1, 1), Color(0, 0, 0));
	m.SetPattern(&p);
	m.SetAmbient(1);
	m.SetDiffuse(0);
	m.SetSpecular(0);
	Vector eyev = Vector(0, 0, -1);
	Vector normalv = Vector(0, 0, -1);
	PointLight light = PointLight("PointLight", Point(0, 0, -10), Color(1, 1, 1));
	Color c1 = Engine::lighting(m, &object, light, Point(0.9, 0, 0), eyev, normalv, false);
	Color c2 = Engine::lighting(m, &object, light, Point(1.1, 0, 0), eyev, normalv, false);
	EXPECT_TRUE(c1 == Color(1, 1, 1));
	EXPECT_TRUE(c2 == Color(0, 0, 0));
}

TEST(Chapter10_tests, A_pattern_on_a_material_is_optional) {
	Material m;
	EXPECT_TRUE(m.GetPattern() == nullptr);
}

TEST(Chapter10_tests, A_material_can_be_given_a_pattern) {
	Material m;
	StripePattern pattern = StripePattern(Color(1, 1, 1), Color(0, 0, 0));
	m.SetPattern(&pattern);
	EXPECT_TRUE((*m.GetPattern()) == pattern);
}

TEST(Chapter10_tests, Stripes_with_an_object_transformation) {
	Sphere object("Sphere");
	object.SetTransform(Matrix4().scaling(2, 2, 2));
	StripePattern pattern = StripePattern(Colors::White, Colors::Black);
	Color c = pattern.pattern_at_object(&object, Point(1.5, 0, 0));
	EXPECT_TRUE(c == Colors::White);
}

TEST(Chapter10_tests, Stripes_with_a_pattern_transformation) {
	Sphere object("Sphere");
	StripePattern pattern = StripePattern(Colors::White, Colors::Black);
	pattern.SetTransform(Matrix4().scaling(2, 2, 2));
	Color c = pattern.pattern_at_object(&object, Point(1.5, 0, 0));
	EXPECT_TRUE(c == Colors::White);
}

TEST(Chapter10_tests, Stripes_with_both_an_object_and_a_pattern_transformation) {
	Sphere object("Sphere");
	object.SetTransform(Matrix4().scaling(2, 2, 2));
	StripePattern pattern = StripePattern(Colors::White, Colors::Black);
	pattern.SetTransform(Matrix4().translation(0.5, 0, 0));
	Color c = pattern.pattern_at_object(&object, Point(2.5, 0, 0));
	EXPECT_TRUE(c == Colors::White);
}

TEST(Chapter10_tests, The_default_pattern_transformation) {
	MockPattern pattern;
	EXPECT_TRUE(pattern.GetTransform() == Matrix4().identity());
}

TEST(Chapter10_tests, Assigning_a_pattern_transformation) {
	MockPattern pattern;
	pattern.SetTransform(Matrix4().translation(1, 2, 3));
	EXPECT_TRUE(pattern.GetTransform() == Matrix4().translation(1, 2, 3));
}

TEST(Chapter10_tests, A_gradient_linearly_interpolates_between_colors) {
	GradientPattern pattern = GradientPattern(Colors::White, Colors::Black);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 0, 0)) == Colors::White);
	EXPECT_TRUE(pattern.pattern_at(Point(0.25, 0, 0)) == Color(0.75, 0.75, 0.75));
	EXPECT_TRUE(pattern.pattern_at(Point(0.5, 0, 0)) == Color(0.5, 0.5, 0.5));
	EXPECT_TRUE(pattern.pattern_at(Point(0.75, 0, 0)) == Color(0.25, 0.25, 0.25));
}

TEST(Chapter10_tests, A_ring_should_extend_in_both_x_and_z) {
	RingPattern pattern = RingPattern(Colors::White, Colors::Black);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 0, 0)) == Colors::White);
	EXPECT_TRUE(pattern.pattern_at(Point(1, 0, 0)) == Colors::Black);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 0, 1)) == Colors::Black);
	// 0.708 = just slightly more than √2/2
	EXPECT_TRUE(pattern.pattern_at(Point(0.708, 0, 0.708)) == Colors::Black);
}

TEST(Chapter10_tests, A_checker_should_repeat_in_x) {
	CheckerPattern pattern = CheckerPattern(Colors::White, Colors::Black);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 0, 0)) == Colors::White);
	EXPECT_TRUE(pattern.pattern_at(Point(0.99, 0, 0)) == Colors::White);
	EXPECT_TRUE(pattern.pattern_at(Point(1.01, 0, 0)) == Colors::Black);
}

TEST(Chapter10_tests, A_checker_should_repeat_in_y) {
	CheckerPattern pattern = CheckerPattern(Colors::White, Colors::Black);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 0, 0)) == Colors::White);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 0.99, 0)) == Colors::White);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 1.01, 0)) == Colors::Black);
}

TEST(Chapter10_tests, A_checker_should_repeat_in_z) {
	CheckerPattern pattern = CheckerPattern(Colors::White, Colors::Black);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 0, 0)) == Colors::White);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 0, 0.99)) == Colors::White);
	EXPECT_TRUE(pattern.pattern_at(Point(0, 0, 1.01)) == Colors::Black);
}

TEST(Chapter10_tests, Dividing_a_color_by_a_value) {
	Color c = Color(1, 2, 3);
	c = c / 2;
	EXPECT_TRUE(c == Color(0.5, 1, 1.5));
}
#pragma endregion

#pragma region Chapter11Tests
TEST(Chapter11_tests, Reflectivity_for_the_default_material) {
	Material m;
	EXPECT_FLOAT_EQ(m.GetReflectivity(), 0.0f);
}

TEST(Chapter11_tests, Precomputing_the_reflection_vector) {
	Plane shape("Plane");
	Ray r = Ray(Point(0, 1, -1), Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	Intersection i(sqrt(2), &shape);
	Engine::Computation comps = Engine::prepare_computations(i, r);
	EXPECT_TRUE(comps.reflectv == Vector(0, sqrt(2) / 2, sqrt(2) / 2));
}

TEST(Chapter11_tests, The_reflected_color_for_a_nonreflective_material) {
	World w = World(WorldType::DEFAULT);
	Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
	Shape* shape = w.GetShapes()[1];
	shape->GetMaterial().SetAmbient(1);
	Intersection i(1, shape);
	Engine::Computation comps = Engine::prepare_computations(i, r);
	Color color = Engine::reflected_color(w, comps);
	EXPECT_TRUE(color == Color(0, 0, 0));
}

TEST(Chapter11_tests, The_reflected_color_for_a_reflective_material) {
	World w = World(WorldType::DEFAULT);
	Plane shape = Plane("Plane", Material().SetReflectivity(0.5f), Matrix4().translation(0, -1, 0));
	w.AddObject(&shape);
	Ray r = Ray(Point(0, 0, -3), Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	Intersection i(sqrt(2), &shape);
	Engine::Computation comps = Engine::prepare_computations(i, r);
	Color color = Engine::reflected_color(w, comps);
	EXPECT_TRUE(color == Color(0.19032, 0.2379, 0.14274));
}

TEST(Chapter11_tests, The_shade_hit_function_with_a_reflective_material) {
	World w = World(WorldType::DEFAULT);
	Plane shape = Plane("Plane", Material().SetReflectivity(0.5f), Matrix4().translation(0, -1, 0));
	w.AddObject(&shape);
	Ray r = Ray(Point(0, 0, -3), Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	Intersection i(sqrt(2), &shape);
	Engine::Computation comps = Engine::prepare_computations(i, r);
	Color color = Engine::shade_hit(w, comps);
	EXPECT_TRUE(color == Color(0.87677, 0.92436, 0.82918));
}

TEST(Chapter11_tests, The_color_at_function_with_mutually_reflective_surfaces) {
	World w = World(WorldType::EMPTY);
	PointLight light = PointLight("PointLight1", Point(0, 0, 0), Color(1, 1, 1));
	w.AddObject(&light);
	Plane lower = Plane("Plane1", Material().SetReflectivity(1.0f), Matrix4().translation(0, -1, 0));
	w.AddObject(&lower);
	Plane upper = Plane("Plane2", Material().SetReflectivity(1.0f), Matrix4().translation(0, 1, 0));
	w.AddObject(&upper);
	Ray r = Ray(Point(0, 0, 0), Vector(0, 1, 0));
	EXPECT_NO_THROW(Engine::color_at(w, r), testing::ExitedWithCode(0), "Success");
}

TEST(Chapter11_tests, The_reflected_color_at_the_maximum_recursive_depth) {
	World w = World(WorldType::DEFAULT);
	Plane shape = Plane("Plane", Material().SetReflectivity(0.5f), Matrix4().translation(0, -1, 0));
	w.AddObject(&shape);
	Ray r = Ray(Point(0, 0, -3), Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	Intersection i(sqrt(2), &shape);
	Engine::Computation comps = Engine::prepare_computations(i, r);
	Color color = Engine::reflected_color(w, comps, 0);
	EXPECT_TRUE(color == Color(0, 0, 0));
}

TEST(Chapter11_tests, Transparency_and_Refractive_Index_for_the_default_material) {
	Material m;
	EXPECT_FLOAT_EQ(m.GetTransparency(), 0.0f);
	EXPECT_FLOAT_EQ(m.GetRefractiveIndex(), 1.0f);
}

TEST(Chapter11_tests, A_helper_for_producing_a_sphere_with_a_glassy_material) {
	Sphere s = Sphere::glass_sphere("Glass_sphere");
	EXPECT_FLOAT_EQ(s.GetMaterial().GetTransparency(), 1.0f);
	EXPECT_FLOAT_EQ(s.GetMaterial().GetRefractiveIndex(), 1.5f);
}

TEST(Chapter11_tests, Finding_n1_and_n2_at_various_intersections) {
	float n1_values[] = { 1.0f, 1.5f, 2.0f, 2.5f, 2.5f, 1.5f };
	float n2_values[] = { 1.5f, 2.0f, 2.5f, 2.5f, 1.5f, 1.0f };

	Sphere A = Sphere::glass_sphere("Glass_sphere1");
	A.SetTransform(Matrix4().scaling(2, 2, 2));
	A.GetMaterial().SetRefractiveIndex(1.5f);

	Sphere B = Sphere::glass_sphere("Glass_sphere2");
	B.SetTransform(Matrix4().translation(0, 0, -0.25f));
	B.GetMaterial().SetRefractiveIndex(2.0f);

	Sphere C = Sphere::glass_sphere("Glass_sphere3");
	C.SetTransform(Matrix4().translation(0, 0, 0.25f));
	C.GetMaterial().SetRefractiveIndex(2.5f);

	Ray r = Ray(Point(0, 0, -4), Vector(0, 0, 1));
	std::vector<Intersection> xs = Intersection::intersections({
		Intersection(2,			&A),
		Intersection(2.75f, &B),
		Intersection(3.25f, &C),
		Intersection(4.75f, &B),
		Intersection(5.25f, &C),
		Intersection(6,			&A)
	});

	for (int index = 0; index <= 5; index++) {
		Engine::Computation comps = Engine::prepare_computations(xs[index], r, xs);
		ASSERT_FLOAT_EQ(comps.n1, n1_values[index]);
		ASSERT_FLOAT_EQ(comps.n2, n2_values[index]);
	}
}

TEST(Chapter11_tests, The_under_point_is_offset_below_the_surface) {
	Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
	Sphere shape = Sphere::glass_sphere("Glass_sphere");
	shape.SetTransform(Matrix4().translation(0, 0, 1.0f));
	Intersection i(5, &shape);
	std::vector<Intersection> xs = Intersection::intersections({ i });
	Engine::Computation comps = Engine::prepare_computations(i, r, xs);
	EXPECT_GT(comps.under_point[2], utils::kEPSILON / 2);
	EXPECT_LT(comps.point[2], comps.under_point[2]);
}

TEST(Chapter11_tests, The_refracted_color_with_an_opaque_surface) {
	World w(WorldType::DEFAULT);
	Shape* shape = w.GetShapes()[0];
	Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
	std::vector<Intersection> xs = Intersection::intersections({
		Intersection(4, shape),
		Intersection(6, shape)
	});
	Engine::Computation comps = Engine::prepare_computations(xs[0], r, xs);
	Color c = Engine::refracted_color(w, comps, 5);
	EXPECT_TRUE(c == Color(0, 0, 0));
}

TEST(Chapter11_tests, The_refracted_color_at_the_maximum_recursive_depth) {
	World w(WorldType::DEFAULT);
	Shape* shape = w.GetShapes()[0];
	shape->GetMaterial().SetTransparency(1.0f).SetRefractiveIndex(1.5f);
	Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
	std::vector<Intersection> xs = Intersection::intersections({
		Intersection(4, shape),
		Intersection(6, shape)
	});
	Engine::Computation comps = Engine::prepare_computations(xs[0], r, xs);
	Color c = Engine::refracted_color(w, comps, 0);
	EXPECT_TRUE(c == Color(0, 0, 0));
}

TEST(Chapter11_tests, The_refracted_color_under_total_internal_reflection) {
	World w(WorldType::DEFAULT);
	Shape* shape = w.GetShapes()[0];
	shape->GetMaterial().SetTransparency(1.0f).SetRefractiveIndex(1.5f);
	Ray r = Ray(Point(0, 0, sqrt(2) / 2), Vector(0, 1, 0));
	std::vector<Intersection> xs = Intersection::intersections({
		Intersection(-sqrt(2) / 2, shape),
		Intersection(sqrt(2) / 2, shape)
	});
	// using xs[1] here not xs[0] as we are now inside the sphere so use the second intersection
	Engine::Computation comps = Engine::prepare_computations(xs[1], r, xs);
	Color c = Engine::refracted_color(w, comps, 5);
	EXPECT_TRUE(c == Color(0, 0, 0));
}

TEST(Chapter11_tests, The_refracted_color_with_a_refracted_ray) {
	World w(WorldType::DEFAULT);
	Shape* A = w.GetShapes()[0];
	MockPattern pattern;
	A->GetMaterial().SetAmbient(1.0f).SetPattern(&pattern);
	Shape* B = w.GetShapes()[1];
	B->GetMaterial().SetTransparency(1.0f).SetRefractiveIndex(1.5f);
	Ray r = Ray(Point(0, 0, 0.1), Vector(0, 1, 0));
	std::vector<Intersection> xs = Intersection::intersections({
		Intersection(-0.9899f, A),
		Intersection(-0.4899f, B),
		Intersection(0.4899f, B),
		Intersection(0.9899f, A),
	});
	Engine::Computation comps = Engine::prepare_computations(xs[2], r, xs);
	Color c = Engine::refracted_color(w, comps, 5);
	EXPECT_TRUE(c == Color(0, 0.99888f, 0.04725f));
}

TEST(Chapter11_tests, The_shade_hit_function_with_a_transparent_material) {
	World w(WorldType::DEFAULT);
	Plane floor = Plane("floor", Material().SetTransparency(0.5f).SetRefractiveIndex(1.5f), Matrix4().translation(0, -1, 0));
	w.AddObject(&floor);
	Sphere ball = Sphere("ball", Material().SetColor(Color(1, 0, 0)).SetAmbient(0.5f), Matrix4().translation(0, -3.5f, -0.5f));
	w.AddObject(&ball);
	Ray r = Ray(Point(0, 0, -3), Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	std::vector<Intersection> xs = Intersection::intersections({ Intersection(sqrt(2), &floor) });
	Engine::Computation comps = Engine::prepare_computations(xs[0], r, xs);
	Color c = Engine::shade_hit(w, comps, 5);
	EXPECT_TRUE(c == Color(0.93642f, 0.68642f, 0.68642f));
}

TEST(Chapter11_tests, The_schlick_approximation_under_total_internal_reflection) {
	Sphere shape = Sphere::glass_sphere("Glass_sphere");
	Ray r = Ray(Point(0, 0, sqrt(2) / 2), Vector(0, 1, 0));
	std::vector<Intersection> xs = Intersection::intersections({
		Intersection(-sqrt(2) / 2, &shape),
		Intersection(sqrt(2) / 2, &shape)
	});
	Engine::Computation comps = Engine::prepare_computations(xs[1], r, xs);
	float reflectance = Engine::schlick(comps);
	EXPECT_FLOAT_EQ(reflectance, 1.0f);
}

TEST(Chapter11_tests, The_schlick_approximation_with_a_perpendicular_viewing_angle) {
	Sphere shape = Sphere::glass_sphere("Glass_sphere");
	Ray r = Ray(Point(0, 0, 0), Vector(0, 1, 0));
	std::vector<Intersection> xs = Intersection::intersections({
		Intersection(-1, &shape),
		Intersection(1, &shape)
		});
	Engine::Computation comps = Engine::prepare_computations(xs[1], r, xs);
	float reflectance = Engine::schlick(comps);
	EXPECT_FLOAT_EQ(reflectance, 0.04f);
}

TEST(Chapter11_tests, The_schlick_approximation_with_a_small_angle_and_n2_greater_than_n1) {
	Sphere shape = Sphere::glass_sphere("Glass_sphere");
	Ray r = Ray(Point(0, 0.99f, -2), Vector(0, 0, 1));
	std::vector<Intersection> xs = Intersection::intersections({ Intersection(1.8589f, &shape) });
	Engine::Computation comps = Engine::prepare_computations(xs[0], r, xs);
	float reflectance = Engine::schlick(comps);
	EXPECT_TRUE(utils::equal(reflectance, 0.48873)); // Double not float so no 'f'
}

TEST(Chapter11_tests, The_shade_hit_function_with_a_reflective_transparent_material) {
	World w(WorldType::DEFAULT);
	Ray r = Ray(Point(0, 0, -3), Vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	Plane floor = Plane("floor", Material().SetReflectivity(0.5f).SetTransparency(0.5f).SetRefractiveIndex(1.5f), Matrix4().translation(0, -1, 0));
	w.AddObject(&floor);
	Sphere ball = Sphere("ball", Material().SetColor(Color(1, 0, 0)).SetAmbient(0.5f), Matrix4().translation(0, -3.5f, -0.5f));
	w.AddObject(&ball);
	std::vector<Intersection> xs = Intersection::intersections({ Intersection(sqrt(2), &floor) });
	Engine::Computation comps = Engine::prepare_computations(xs[0], r, xs);
	Color c = Engine::shade_hit(w, comps, 5);
	EXPECT_TRUE(c == Color(0.93391f, 0.69643f, 0.69243f));
}
#pragma endregion

#pragma region Chapter12Tests
TEST(Chapter12_tests, A_ray_intersects_a_cube) {
	struct CubeFace {
		CubeFace(const Point& origin, const Vector& direction, float t1, float t2) {
			this->origin = origin;
			this->direction = direction;
			this->t1 = t1;
			this->t2 = t2;
		}
		Point origin;
		Vector direction;
		float t1, t2;
	};

	std::vector<CubeFace> faces = { 
		CubeFace(Point(5, 0.5f, 0), Vector(-1, 0, 0), 4, 6),		// +x
		CubeFace(Point(-5, 0.5f, 0), Vector(1, 0, 0), 4, 6),		// -x
		CubeFace(Point(0.5f, 5, 0), Vector(0, -1, 0), 4, 6),		// +y
		CubeFace(Point(0.5f, -5, 0), Vector(0, 1, 0), 4, 6),		// -y
		CubeFace(Point(0.5f, 0, 5), Vector(0, 0, -1), 4, 6),		// +z
		CubeFace(Point(0.5f, 0, -5), Vector(0, 0, 1), 4, 6),		// -z
		CubeFace(Point(0, 0.5f, 0), Vector(0, 0, 1), -1, 1)			// inside
	};

	for (auto face : faces)
	{
		Cube c("Cube");
		Ray r(face.origin, face.direction);
		std::vector<Intersection> xs = c.local_intersect(r.to_ray_struct());
		ASSERT_EQ(xs.size(), 2);
		ASSERT_EQ(xs[0].GetTime(), face.t1);
		ASSERT_EQ(xs[1].GetTime(), face.t2);
	}
}

TEST(Chapter12_tests, A_ray_misses_a_cube) {
	std::vector<Ray> rays = {
		Ray(Point(-2, 0, 0), Vector(0.2673f, 0.5345f, 0.8018f)),
		Ray(Point(0, -2, 0), Vector(0.8018f, 0.2673f, 0.5345f)),
		Ray(Point(0, 0, -2), Vector(0.5345f, 0.8018f, 0.2673f)),
		Ray(Point(2, 0, 2), Vector(0, 0, -1)),
		Ray(Point(0, 2, 2), Vector(0, -1, 0)),
		Ray(Point(2, 2, 0), Vector(-1, 0, 0)),
		Ray(Point(0, 0, 2), Vector(0, 0, 1))
	};

	for (auto ray : rays)
	{
		Cube c("Cube");
		std::vector<Intersection> xs = c.local_intersect(ray.to_ray_struct());
		ASSERT_EQ(xs.size(), 0);
	}
}

TEST(Chapter12_tests, The_normal_on_the_surface_of_a_cube) {
	struct PointNormalPair {
		PointNormalPair(const Point& point, const Vector& normal) {
			this->point = point;
			this->normal = normal;
		}
		Point point;
		Vector normal;
	};

	std::vector<PointNormalPair> pairs = {
		PointNormalPair(Point(1, 0.5f, -0.8f), Vector(1, 0, 0)),
		PointNormalPair(Point(-1, -0.2f, 0.9f), Vector(-1, 0, 0)),
		PointNormalPair(Point(-0.4f, 1, -0.1f), Vector(0, 1, 0)),
		PointNormalPair(Point(0.3f, -1, -0.7f), Vector(0, -1, 0)),
		PointNormalPair(Point(-0.6f, 0.3, 1), Vector(0, 0, 1)),
		PointNormalPair(Point(0.4f, 0.4f, -1), Vector(0, 0, -1)),
		PointNormalPair(Point(1, 1, 1), Vector(1, 0, 0)),
		PointNormalPair(Point(-1, -1, -1), Vector(-1, 0, 0))
	};

	for (auto pair : pairs)
	{
		Cube c("Cube");
		Vector normal = c.local_normal_at(pair.point);
		ASSERT_TRUE(normal == pair.normal);
	}
}
#pragma endregion

#pragma region Chapter13Tests
TEST(Chapter13_tests, A_ray_misses_a_cylinder) {
	std::vector<Ray> rays = {
		Ray(Point(1, 0, 0), Vector(0, 1, 0)),
		Ray(Point(0, 0, 0), Vector(0, 1, 0)),
		Ray(Point(0, 0, -5), Vector(1, 1, 1)),
	};

	for (auto ray : rays) {
		Cylinder cyl("Cylinder");
		Vector direction = ray.GetDirection().normalize();
		Ray r(ray.GetOrigin(), direction);
		std::vector<Intersection> xs = cyl.local_intersect(r.to_ray_struct());
		ASSERT_EQ(xs.size(), 0);
	}
}

TEST(Chapter13_tests, A_ray_strikes_a_cylinder) {
	struct CylinderIntersect {
		CylinderIntersect(const Point& origin, const Vector& direction, float t0, float t1) {
			this->origin = origin;
			this->direction = direction;
			this->t0 = t0;
			this->t1 = t1;
		}
		Point origin;
		Vector direction;
		float t0, t1;
	};

	std::vector<CylinderIntersect> examples = {
		CylinderIntersect(Point(1, 0, -5), Vector(0, 0, 1), 5, 5),
		CylinderIntersect(Point(0, 0, -5), Vector(0, 0, 1), 4, 6),
		CylinderIntersect(Point(0.5f, 0, -5), Vector(0.1f, 1, 1), 6.80798f, 7.08872f)
	};

	for (auto example : examples) {
		Cylinder cyl("Cylinder");
		Vector direction = example.direction.normalize();
		Ray r(example.origin, direction);
		std::vector<Intersection> xs = cyl.local_intersect(r.to_ray_struct());
		ASSERT_EQ(xs.size(), 2);
		ASSERT_TRUE(utils::equal(xs[0].GetTime(), example.t0));
		ASSERT_TRUE(utils::equal(xs[1].GetTime(), example.t1));
	}
}

TEST(Chapter13_tests, Normal_vector_on_a_cylinder) {
	struct PointNormalPair {
		PointNormalPair(const Point& point, const Vector& normal) {
			this->point = point;
			this->normal = normal;
		}
		Point point;
		Vector normal;
	};

	std::vector<PointNormalPair> pairs = {
		PointNormalPair(Point(1, 0, 0), Vector(1, 0, 0)),
		PointNormalPair(Point(0, 5, -1), Vector(0, 0, -1)),
		PointNormalPair(Point(0, -2, 1), Vector(0, 0, 1)),
		PointNormalPair(Point(-1, 1, 0), Vector(-1, 0, 0))
	};

	for (auto pair : pairs) {
		Cylinder cyl("Cylinder");
		Vector n = cyl.local_normal_at(pair.point);
		ASSERT_TRUE(n == pair.normal);
	}
}

TEST(Chapter13_tests, The_default_minimum_and_maximum_for_a_cylinder) {
	Cylinder cyl("Cylinder");
	EXPECT_FLOAT_EQ(cyl.GetMinimum(), -utils::kINFINITY);
	EXPECT_FLOAT_EQ(cyl.GetMaximum(), utils::kINFINITY);
}

TEST(Chapter13_tests, Intersecting_a_constrained_cylinder) {
	struct PointDirectionCountPair {
		PointDirectionCountPair(const Point& point, const Vector& direction, const int& count) {
			this->point = point;
			this->direction = direction;
			this->count = count;
		}
		Point point;
		Vector direction;
		int count;
	};

	std::vector<PointDirectionCountPair> examples = {
		PointDirectionCountPair(Point(0, 1.5f, 0), Vector(0.1f, 1, 0), 0),
		PointDirectionCountPair(Point(0, 3, -5), Vector(0, 0, 1), 0),
		PointDirectionCountPair(Point(0, 0, -5), Vector(0, 0, 1), 0),
		PointDirectionCountPair(Point(0, 2, -5), Vector(0, 0, 1), 0),
		PointDirectionCountPair(Point(0, 1, -5), Vector(0, 0, 1), 0),
		PointDirectionCountPair(Point(0, 1.5f, -2), Vector(0, 0, 1), 2)
	};

	for (auto example : examples) {
		Cylinder cyl("Cylinder", 1, 2);
		Vector direction = example.direction.normalize();
		Ray r(example.point, direction);
		std::vector<Intersection> xs = cyl.local_intersect(r.to_ray_struct());
		ASSERT_EQ(xs.size(), example.count);
	}
}

TEST(Chapter13_tests, The_default_closed_value_for_a_cylinder) {
	Cylinder cyl("Cylinder");
	EXPECT_FALSE(cyl.GetClosed());
}

TEST(Chapter13_tests, Intersecting_the_caps_of_a_closed_cylinder) {
	struct PointDirectionCountPair {
		PointDirectionCountPair(const Point& point, const Vector& direction, const int& count) {
			this->point = point;
			this->direction = direction;
			this->count = count;
		}
		Point point;
		Vector direction;
		int count;
	};

	std::vector<PointDirectionCountPair> examples = {
		PointDirectionCountPair(Point(0, 3, 0), Vector(0, -1, 0), 2),
		PointDirectionCountPair(Point(0, 3, -2), Vector(0, -1, 2), 2),
		PointDirectionCountPair(Point(0, 4, -2), Vector(0, -1, 1), 2), // corner case
		PointDirectionCountPair(Point(0, 0, -2), Vector(0, 1, 2), 2),
		PointDirectionCountPair(Point(0, -1, -2), Vector(0, 1, 1), 2) // corner case
	};

	for (auto example : examples) {
		Cylinder cyl("Cylinder", 1, 2, true);
		Vector direction = example.direction.normalize();
		Ray r(example.point, direction);
		std::vector<Intersection> xs = cyl.local_intersect(r.to_ray_struct());
		ASSERT_EQ(xs.size(), example.count);
	}
}

TEST(Chapter13_tests, The_normal_vector_on_a_cylinders_end_caps) {
	struct PointNormalPair {
		PointNormalPair(const Point& point, const Vector& normal) {
			this->point = point;
			this->normal = normal;
		}
		Point point;
		Vector normal;
	};

	std::vector<PointNormalPair> pairs = {
		PointNormalPair(Point(0, 1, 0), Vector(0, -1, 0)),
		PointNormalPair(Point(0.5f, 1, 0), Vector(0, -1, 0)),
		PointNormalPair(Point(0, 1, 0.5f), Vector(0, -1, 0)),
		PointNormalPair(Point(0, 2, 0), Vector(0, 1, 0)),
		PointNormalPair(Point(0.5f, 2, 0), Vector(0, 1, 0)),
		PointNormalPair(Point(0, 2, 0.5f), Vector(0, 1, 0))
	};

	for (auto pair : pairs) {
		Cylinder cyl("Cylinder", 1, 2, true);
		Vector n = cyl.local_normal_at(pair.point);
		ASSERT_TRUE(n == pair.normal);
	}
}

TEST(Chapter13_tests, Intersecting_a_cone_with_a_ray) {
	struct ConeIntersect {
		ConeIntersect(const Point& origin, const Vector& direction, float t0, float t1) {
			this->origin = origin;
			this->direction = direction;
			this->t0 = t0;
			this->t1 = t1;
		}
		Point origin;
		Vector direction;
		float t0, t1;
	};

	std::vector<ConeIntersect> examples = {
		ConeIntersect(Point(0, 0, -5), Vector(0, 0, 1), 5, 5),
		ConeIntersect(Point(0, 0, -5), Vector(1, 1, 1), 8.66025f, 8.66025f),
		ConeIntersect(Point(1, 1, -5.0f), Vector(-0.5f, -1, 1), 4.55006f, 49.44994f)
	};

	for (auto example : examples) {
		Cone shape("Cone");
		Vector direction = example.direction.normalize();
		Ray r(example.origin, direction);
		std::vector<Intersection> xs = shape.local_intersect(r.to_ray_struct());
		ASSERT_EQ(xs.size(), 2);
		ASSERT_TRUE(utils::equal(xs[0].GetTime(), example.t0));
		ASSERT_TRUE(utils::equal(xs[1].GetTime(), example.t1));
	}
}

TEST(Chapter13_tests, Intersecting_a_cone_with_a_ray_parallel_to_one_of_its_halves) {
	Cone shape("Cone");
	Vector direction = Vector(0, 1, 1).normalize();
	Ray r(Point(0, 0, -1), direction);
	std::vector<Intersection> xs = shape.local_intersect(r.to_ray_struct());
	ASSERT_EQ(xs.size(), 1);
	ASSERT_TRUE(utils::equal(xs[0].GetTime(), 0.35355f));
}

TEST(Chapter13_tests, Intersecting_a_cones_end_caps) {
	struct PointDirectionCountPair {
		PointDirectionCountPair(const Point& point, const Vector& direction, const int& count) {
			this->point = point;
			this->direction = direction;
			this->count = count;
		}
		Point point;
		Vector direction;
		int count;
	};

	std::vector<PointDirectionCountPair> examples = {
		PointDirectionCountPair(Point(0, 0, -5), Vector(0, 1, 0), 0),
		PointDirectionCountPair(Point(0, 0, -0.25f), Vector(0, 1, 1), 2),
		PointDirectionCountPair(Point(0, 0, -0.25f), Vector(0, 1, 0), 4)
	};

	Cone shape("Cone", -0.5f, 0.5f, true);

	for (auto example : examples) {
		Vector direction = example.direction.normalize();
		Ray r(example.point, direction);
		std::vector<Intersection> xs = shape.local_intersect(r.to_ray_struct());
		ASSERT_EQ(xs.size(), example.count);
	}
}

TEST(Chapter13_tests, Computing_the_normal_vector_on_a_cone) {
	struct PointNormalPair {
		PointNormalPair(const Point& point, const Vector& normal) {
			this->point = point;
			this->normal = normal;
		}
		Point point;
		Vector normal;
	};

	std::vector<PointNormalPair> pairs = {
		PointNormalPair(Point(0, 0, 0), Vector(0, 0, 0)),
		PointNormalPair(Point(1, 1, 1), Vector(1, -sqrt(2), 1)),
		PointNormalPair(Point(-1, -1, 0), Vector(-1, 1, 0))
	};

	Cone shape("Cone");

	for (auto pair : pairs) {
		Vector n = shape.local_normal_at(pair.point);
		ASSERT_TRUE(n == pair.normal);
	}
}
#pragma endregion

#pragma region Chapter14Tests
TEST(Chapter14_tests, Creating_a_new_group) {
	Group g("Group");
	EXPECT_TRUE(g.GetTransform() == Matrix4().identity());
	EXPECT_TRUE(g.isEmpty());
}

TEST(Chapter14_tests, A_shape_has_a_parent_attribute) {
	MockShape s("Shape");
	EXPECT_TRUE(s.GetParent() == nullptr);
}

TEST(Chapter14_tests, Adding_a_child_to_a_group) {
	Group* g = new Group("Group");
	MockShape* s = new MockShape("Shape");
	g->AddChild(s);
	EXPECT_FALSE(g->isEmpty());
	EXPECT_TRUE(g->ContainsChild(s));
	EXPECT_TRUE(s->GetParent() == g);
	EXPECT_TRUE(s->HasParent());
}

TEST(Chapter14_tests, Intersecting_a_ray_with_an_empty_group) {
	Group g("Group");
	Ray r(Point(0, 0, 0), Vector(0, 0, 1));
	std::vector<Intersection> xs = g.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs.size(), 0);
}

TEST(Chapter14_tests, Intersecting_a_ray_with_a_nonempty_group) {
	Group g("Group");
	Sphere s1("Sphere1");
	Sphere s2("Sphere2");
	s2.SetTransform(Matrix4().translation(0, 0, -3));
	Sphere s3("Sphere3");
	s3.SetTransform(Matrix4().translation(5, 0, 0));
	g.AddChild(&s1);
	g.AddChild(&s2);
	g.AddChild(&s3);
	Ray r(Point(0, 0, -5), Vector(0, 0, 1));
	std::vector<Intersection> xs = g.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs.size(), 4);
	EXPECT_TRUE((*xs[0].GetObject()) == s2);
	EXPECT_TRUE((*xs[1].GetObject()) == s2);
	EXPECT_TRUE((*xs[2].GetObject()) == s1);
	EXPECT_TRUE((*xs[3].GetObject()) == s1);
}

TEST(Chapter14_tests, Intersecting_a_transformed_group) {
	Group g("Group");
	g.SetTransform(Matrix4().scaling(2, 2, 2));
	Sphere s("Sphere");
	s.SetTransform(Matrix4().translation(5, 0, 0));
	g.AddChild(&s);
	Ray r(Point(10, 0, -10), Vector(0, 0, 1));
	std::vector<Intersection> xs = g.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs.size(), 2);
}

TEST(Chapter14_tests, Converting_a_point_from_world_to_object_space) {
	Group g1("Group1");
	g1.SetTransform(Matrix4().rotation_y(utils::kPI / 2));
	Group g2("Group2");
	g2.SetTransform(Matrix4().scaling(2, 2, 2));
	g1.AddChild(&g2);
	Sphere s("Sphere");
	s.SetTransform(Matrix4().translation(5, 0, 0));
	g2.AddChild(&s);
	Point p = Shape::world_to_object(&s, Point(-2, 0, -10));
	EXPECT_TRUE(p == Point(0, 0, -1));
}

TEST(Chapter14_tests, Converting_a_normal_from_object_to_world_space) {
	Group g1("Group1");
	g1.SetTransform(Matrix4().rotation_y(utils::kPI / 2));
	Group g2("Group2");
	g2.SetTransform(Matrix4().scaling(1, 2, 3));
	g1.AddChild(&g2);
	Sphere s("Sphere");
	s.SetTransform(Matrix4().translation(5, 0, 0));
	g2.AddChild(&s);
	Vector n = Shape::normal_to_world(&s, Vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
	EXPECT_TRUE(n == Vector(0.2857f, 0.4286f, -0.8571f));
}

TEST(Chapter14_tests, Finding_the_normal_on_a_child_object) {
	Group g1("Group1");
	g1.SetTransform(Matrix4().rotation_y(utils::kPI / 2));
	Group g2("Group2");
	g2.SetTransform(Matrix4().scaling(1, 2, 3));
	g1.AddChild(&g2);
	Sphere s("Sphere");
	s.SetTransform(Matrix4().translation(5, 0, 0));
	g2.AddChild(&s);
	Vector n = s.normal_at(Point(1.7321f, 1.1547f, -5.5774f));
	EXPECT_EQ(n, Vector(0.2857f, 0.4286f, -0.8571f));
}

TEST(Chapter14_tests, Comparing_identical_bounds) {
	BoundingBox b1 = BoundingBox(Point(-1, 0, -1), Point(1, 0, 1));
	BoundingBox b2 = BoundingBox(Point(-1, 0, -1), Point(1, 0, 1));
	EXPECT_TRUE(b1.equal(b2, true));
}

TEST(Chapter14_tests, Merging_two_bounds_yields_the_biggest_bounding_box) {
	BoundingBox b1 = BoundingBox(Point(-1, 0, -1), Point(1, 0, 1));
	BoundingBox b2 = BoundingBox(Point(-utils::kINFINITY, -1, 0), Point(utils::kINFINITY, 1, 0));
	b1.merge(b2);
	EXPECT_TRUE(b1.equal(BoundingBox(Point(-utils::kINFINITY, -1, -1), Point(utils::kINFINITY, 1, 1)), false));
}

TEST(Chapter14_tests, Rotation_by_45_degrees_yields_updated_bounds) {
	BoundingBox b = BoundingBox(Point(-1, -1, -1), Point(1, 1, 1));
	b.transform(Matrix4().rotation_y(utils::kPI / 4));
	EXPECT_TRUE(b.equal(BoundingBox(Point(-sqrt(2), -1, -sqrt(2)), Point(sqrt(2), 1, sqrt(2))), true));
}

TEST(Chapter14_tests, A_child_inherits_a_parents_material) {
	Group g1("Group1");
	Material m = Materials::TransparentYellow;
	g1.SetMaterial(m);
	Group g2("Group2");
	g1.AddChild(&g2);
	Sphere s("Sphere");
	g2.AddChild(&s);
	EXPECT_TRUE(g2.GetMaterial() == m);
	EXPECT_TRUE(s.GetMaterial() == m);
}
#pragma endregion

#pragma region Chapter15Tests
TEST(Chapter15_tests, Constructing_a_triangle) {
	Point p1(0, 1, 0);
	Point p2(-1, 0, 0);
	Point p3(1, 0, 0);
	Triangle t(p1, p2, p3);

	EXPECT_EQ(t.GetP1(), p1);
	EXPECT_EQ(t.GetP2(), p2);
	EXPECT_EQ(t.GetP3(), p3);
	EXPECT_EQ(t.GetE1(), Vector(-1, -1, 0));
	EXPECT_EQ(t.GetE2(), Vector(1, -1, 0));
	EXPECT_EQ(t.GetNormal(), Vector(0, 0, -1));
}

TEST(Chapter15_tests, Finding_the_normal_on_a_triangle) {
	Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));

	Vector n1 = t.local_normal_at(Point(0, 0.5f, 0));
	Vector n2 = t.local_normal_at(Point(-0.5f, 0.75f, 0));
	Vector n3 = t.local_normal_at(Point(0.5f, 0.25f, 0));

	EXPECT_EQ(n1, t.GetNormal());
	EXPECT_EQ(n2, t.GetNormal());
	EXPECT_EQ(n3, t.GetNormal());
}

TEST(Chapter15_tests, Intersecting_a_ray_parallel_to_a_triangle) {
	Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));

	Ray r = Ray(Point(0, -1, -2), Vector(0, 1, 0));

	std::vector<Intersection> xs = t.local_intersect(r.to_ray_struct());

	EXPECT_EQ(xs.size(), 0);
}

TEST(Chapter15_tests, A_ray_misses_the_p1_p3_edge) {
	Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));

	Ray r = Ray(Point(1, 1, -2), Vector(0, 0, 1));

	std::vector<Intersection> xs = t.local_intersect(r.to_ray_struct());

	EXPECT_EQ(xs.size(), 0);
}

TEST(Chapter15_tests, A_ray_misses_the_p1_p2_edge) {
	Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));

	Ray r = Ray(Point(-1, 1, -2), Vector(0, 0, 1));

	std::vector<Intersection> xs = t.local_intersect(r.to_ray_struct());

	EXPECT_EQ(xs.size(), 0);
}

TEST(Chapter15_tests, A_ray_misses_the_p2_p3_edge) {
	Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));

	Ray r = Ray(Point(0, -1, -2), Vector(0, 0, 1));

	std::vector<Intersection> xs = t.local_intersect(r.to_ray_struct());

	EXPECT_EQ(xs.size(), 0);
}

TEST(Chapter15_tests, A_ray_strikes_a_triangle) {
	Triangle t(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));

	Ray r = Ray(Point(0, 0.5, -2), Vector(0, 0, 1));

	std::vector<Intersection> xs = t.local_intersect(r.to_ray_struct());

	EXPECT_EQ(xs.size(), 1);
	EXPECT_EQ(xs[0].GetTime(), 2);
}
TEST(Chapter15_tests, Parser_ignores_unrecognized_lines) {
	ObjParser parser = ObjParser("C:\\Users\\zachc\\source\\repos\\RayTracerChallengeCpp\\RayTracerChallenge\\ConRayTracer\\test_obj_files\\gibberish.obj");
	EXPECT_EQ(parser.GetLinesIgnored(), 5);
}

TEST(Chapter15_tests, Parsing_vertex_records) {
	ObjParser parser = ObjParser("C:\\Users\\zachc\\source\\repos\\RayTracerChallengeCpp\\RayTracerChallenge\\ConRayTracer\\test_obj_files\\vertex_records.obj");

	EXPECT_EQ(parser.GetLinesIgnored(), 0);
	EXPECT_EQ(parser.GetVertices()[0], Point(-1, 1, 0));
	EXPECT_EQ(parser.GetVertices()[1], Point(-1, 0.5f, 0));
	EXPECT_EQ(parser.GetVertices()[2], Point(1, 0, 0));
	EXPECT_EQ(parser.GetVertices()[3], Point(1, 1, 0));
}

TEST(Chapter15_tests, Parsing_triangle_faces) {
	ObjParser parser = ObjParser("C:\\Users\\zachc\\source\\repos\\RayTracerChallengeCpp\\RayTracerChallenge\\ConRayTracer\\test_obj_files\\triangle_faces.obj");
	Group* g = parser.GetDefaultGroup();
	Triangle t1 = *(Triangle*)g->GetChildren()[0];
	Triangle t2 = *(Triangle*)g->GetChildren()[1];

	EXPECT_EQ(parser.GetLinesIgnored(), 0);
	EXPECT_EQ(t1.GetP1(), parser.GetVertices()[0]);
	EXPECT_EQ(t1.GetP2(), parser.GetVertices()[1]);
	EXPECT_EQ(t1.GetP3(), parser.GetVertices()[2]);
	EXPECT_EQ(t2.GetP1(), parser.GetVertices()[0]);
	EXPECT_EQ(t2.GetP2(), parser.GetVertices()[2]);
	EXPECT_EQ(t2.GetP3(), parser.GetVertices()[3]);
}

TEST(Chapter15_tests, Triangulating_polygons) {
	ObjParser parser = ObjParser("C:\\Users\\zachc\\source\\repos\\RayTracerChallengeCpp\\RayTracerChallenge\\ConRayTracer\\test_obj_files\\triangulating_polygons.obj");
	Group* g = parser.GetDefaultGroup();
	Triangle t1 = *(Triangle*)g->GetChildren()[0];
	Triangle t2 = *(Triangle*)g->GetChildren()[1];
	Triangle t3 = *(Triangle*)g->GetChildren()[2];

	EXPECT_EQ(parser.GetLinesIgnored(), 0);
	EXPECT_EQ(t1.GetP1(), parser.GetVertices()[0]);
	EXPECT_EQ(t1.GetP2(), parser.GetVertices()[1]);
	EXPECT_EQ(t1.GetP3(), parser.GetVertices()[2]);
	EXPECT_EQ(t2.GetP1(), parser.GetVertices()[0]);
	EXPECT_EQ(t2.GetP2(), parser.GetVertices()[2]);
	EXPECT_EQ(t2.GetP3(), parser.GetVertices()[3]);
	EXPECT_EQ(t3.GetP1(), parser.GetVertices()[0]);
	EXPECT_EQ(t3.GetP2(), parser.GetVertices()[3]);
	EXPECT_EQ(t3.GetP3(), parser.GetVertices()[4]);
}

TEST(Chapter15_tests, Triangles_in_groups) {
	ObjParser parser = ObjParser("C:\\Users\\zachc\\source\\repos\\RayTracerChallengeCpp\\RayTracerChallenge\\ConRayTracer\\test_obj_files\\triangles.obj");
	Group* g1 = parser.GetGroupByName("FirstGroup");
	Group* g2 = parser.GetGroupByName("SecondGroup");
	Triangle t1 = *(Triangle*)g1->GetChildren()[0];
	Triangle t2 = *(Triangle*)g2->GetChildren()[0];

	EXPECT_EQ(parser.GetLinesIgnored(), 0);
	EXPECT_EQ(t1.GetP1(), parser.GetVertices()[0]);
	EXPECT_EQ(t1.GetP2(), parser.GetVertices()[1]);
	EXPECT_EQ(t1.GetP3(), parser.GetVertices()[2]);
	EXPECT_EQ(t2.GetP1(), parser.GetVertices()[0]);
	EXPECT_EQ(t2.GetP2(), parser.GetVertices()[2]);
	EXPECT_EQ(t2.GetP3(), parser.GetVertices()[3]);
}

TEST(Chapter15_tests, Converting_a_OBJ_file_to_a_group) {
	ObjParser parser = ObjParser("C:\\Users\\zachc\\source\\repos\\RayTracerChallengeCpp\\RayTracerChallenge\\ConRayTracer\\test_obj_files\\triangles.obj");
	Group* g = new Group();
	parser.ConvertToSceneGroup(g);

	EXPECT_TRUE(g->ContainsChildWithName("FirstGroup"));
	EXPECT_TRUE(g->ContainsChildWithName("SecondGroup"));
}

TEST(Chapter15_tests, Parsing_a_large_OBJ_file) {
	ObjParser parser = ObjParser("C:\\Users\\zachc\\source\\repos\\RayTracerChallengeCpp\\RayTracerChallenge\\ConRayTracer\\obj_files\\teapot_low.obj");
	EXPECT_EQ(parser.GetVertices().size(), 137);
	EXPECT_EQ(parser.GetTriangleCount(), 240);
}

TEST(Chapter15_tests, Constructing_a_smooth_triangle) {
	Point p1 = Point(0, 1, 0);
	Point p2 = Point(-1, 0, 0);
	Point p3 = Point(1, 0, 0);
	Vector n1 = Vector(0, 1, 0);
	Vector n2 = Vector(-1, 0, 0);
	Vector n3 = Vector(1, 0, 0);
	SmoothTriangle tri = SmoothTriangle(p1, p2, p3, n1, n2, n3);

	EXPECT_EQ(tri.GetP1(), p1);
	EXPECT_EQ(tri.GetP2(), p2);
	EXPECT_EQ(tri.GetP3(), p3);
	EXPECT_EQ(tri.GetN1(), n1);
	EXPECT_EQ(tri.GetN2(), n2);
	EXPECT_EQ(tri.GetN3(), n3);
}

TEST(Chapter15_tests, An_intersection_encapsulates_u_and_v) {
	Triangle s(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
	Intersection i = Intersection(3.5f, &s);
	i.SetU(0.2f);
	i.SetV(0.4f);
	EXPECT_EQ(i.GetU(), 0.2f);
	EXPECT_EQ(i.GetV(), 0.4f);
}

TEST(Chapter15_tests, An_intersection_with_a_smooth_triangle_stores_u_and_v) {
	Point p1 = Point(0, 1, 0);
	Point p2 = Point(-1, 0, 0);
	Point p3 = Point(1, 0, 0);
	Vector n1 = Vector(0, 1, 0);
	Vector n2 = Vector(-1, 0, 0);
	Vector n3 = Vector(1, 0, 0);
	SmoothTriangle tri = SmoothTriangle(p1, p2, p3, n1, n2, n3);
	Ray r = Ray(Point(-0.2, 0.3, -2), Vector(0, 0, 1));
	std::vector<Intersection> xs = tri.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs[0].GetU(), 0.45f);
	EXPECT_EQ(xs[0].GetV(), 0.25f);
}

TEST(Chapter15_tests, A_smooth_triangle_uses_u_and_v_to_interpolate_the_normal) {
	Point p1 = Point(0, 1, 0);
	Point p2 = Point(-1, 0, 0);
	Point p3 = Point(1, 0, 0);
	Vector n1 = Vector(0, 1, 0);
	Vector n2 = Vector(-1, 0, 0);
	Vector n3 = Vector(1, 0, 0);
	SmoothTriangle tri = SmoothTriangle(p1, p2, p3, n1, n2, n3);
	Intersection i = Intersection(1, &tri, 0.45f, 0.25f);
	Vector n = tri.normal_at(Point(0, 0, 0), i);
	EXPECT_EQ(n, Vector(-0.5547f, 0.83205f, 0.0f));
}

TEST(Chapter15_tests, Preparing_the_normal_on_a_smooth_triangle) {
	Point p1 = Point(0, 1, 0);
	Point p2 = Point(-1, 0, 0);
	Point p3 = Point(1, 0, 0);
	Vector n1 = Vector(0, 1, 0);
	Vector n2 = Vector(-1, 0, 0);
	Vector n3 = Vector(1, 0, 0);
	SmoothTriangle tri = SmoothTriangle(p1, p2, p3, n1, n2, n3);
	Intersection i = Intersection(1, &tri, 0.45f, 0.25f);
	Ray r = Ray(Point(-0.2, 0.3, -2), Vector(0, 0, 1));
	std::vector<Intersection> xs = Intersection::intersections({ i });
	Engine::Computation comps = Engine::prepare_computations(i, r, xs);
	EXPECT_EQ(comps.normalv, Vector(-0.5547f, 0.83205f, 0.0f));
}

TEST(Chapter15_tests, Parsing_vertex_normal_records) {
	ObjParser parser = ObjParser("C:\\Users\\zachc\\source\\repos\\RayTracerChallengeCpp\\RayTracerChallenge\\ConRayTracer\\test_obj_files\\vertex_normal_records.obj");

	EXPECT_EQ(parser.GetLinesIgnored(), 0);
	EXPECT_EQ(parser.GetNormals()[0], Vector(0, 0, 1));
	EXPECT_EQ(parser.GetNormals()[1], Vector(0.707f, 0, -0.707f));
	EXPECT_EQ(parser.GetNormals()[2], Vector(1, 2, 3));
}

TEST(Chapter15_tests, Faces_with_normals) {
	ObjParser parser = ObjParser("C:\\Users\\zachc\\source\\repos\\RayTracerChallengeCpp\\RayTracerChallenge\\ConRayTracer\\test_obj_files\\faces_with_normals.obj", ShadingType::SMOOTH);
	Group* g = parser.GetDefaultGroup();
	SmoothTriangle t1 = *(SmoothTriangle*)g->GetChildren()[0];
	SmoothTriangle t2 = *(SmoothTriangle*)g->GetChildren()[1];
	EXPECT_EQ(parser.GetLinesIgnored(), 0);
	EXPECT_EQ(t1.GetP1(), parser.GetVertices()[0]);
	EXPECT_EQ(t1.GetP2(), parser.GetVertices()[1]);
	EXPECT_EQ(t1.GetP3(), parser.GetVertices()[2]);
	EXPECT_EQ(t1.GetN1(), parser.GetNormals()[2]);
	EXPECT_EQ(t1.GetN2(), parser.GetNormals()[0]);
	EXPECT_EQ(t1.GetN3(), parser.GetNormals()[1]);
	EXPECT_TRUE(t2 == t1);
}
#pragma endregion

#pragma region Chapter16Tests
TEST(Chapter16_tests, A_CSG_is_created_with_an_operation_and_two_shapes) {
	Sphere s1;
	Cube s2;
	CSG c = CSG(Operation::UNION, &s1, &s2);
	EXPECT_EQ(c.GetOperation(), Operation::UNION);
	EXPECT_TRUE(*c.GetLeft() == s1);
	EXPECT_TRUE(*c.GetRight() == s2);
	EXPECT_TRUE(*s1.GetParent() == c);
	EXPECT_TRUE(*s2.GetParent() == c);
}

TEST(Chapter16_tests, Evaluating_the_rule_for_a_CSG_operation) {
	struct TruthTableEntry {
		Operation op;
		bool lhit;
		bool inl;
		bool inr;
		bool result;
	};

	std::vector<TruthTableEntry> truth_table = {
		{ Operation::UNION, true, true, true, false },
		{ Operation::UNION, true, true, false, true },
		{ Operation::UNION, true, false, true, false },
		{ Operation::UNION, true, false, false, true },
		{ Operation::UNION, false, true, true, false },
		{ Operation::UNION, false, true, false, false },
		{ Operation::UNION, false, false, true, true },
		{ Operation::UNION, false, false, false, true },
		{ Operation::INTERSECTION, true, true, true, true },
		{ Operation::INTERSECTION, true, true, false, false },
		{ Operation::INTERSECTION, true, false, true, true },
		{ Operation::INTERSECTION, true, false, false, false },
		{ Operation::INTERSECTION, false, true, true, true },
		{ Operation::INTERSECTION, false, true, false, true },
		{ Operation::INTERSECTION, false, false, true, false },
		{ Operation::INTERSECTION, false, false, false, false },
		{ Operation::DIFFERENCE, true, true, true, false },
		{ Operation::DIFFERENCE, true, true, false, true },
		{ Operation::DIFFERENCE, true, false, true, false },
		{ Operation::DIFFERENCE, true, false, false, true },
		{ Operation::DIFFERENCE, false, true, true, true },
		{ Operation::DIFFERENCE, false, true, false, true },
		{ Operation::DIFFERENCE, false, false, true, false },
		{ Operation::DIFFERENCE, false, false, false, false }
	};

	for (const auto& [op, lhit, inl, inr, result] : truth_table) {
		bool actual_result = CSG::intersection_allowed(op, lhit, inl, inr);
		ASSERT_EQ(result, actual_result);
	}
}

TEST(Chapter16_tests, Filtering_a_list_of_intersections) {
	struct CSGIntersectionExample {
		Operation op;
		int x0;
		int x1;
	};

	std::vector<CSGIntersectionExample> examples = {
		{ Operation::UNION, 0, 3 },
		{ Operation::INTERSECTION, 1, 2 },
		{ Operation::DIFFERENCE, 0, 1 }
	};

	Sphere s1;
	Cube s2;

	for (const auto& [op, x0, x1] : examples) {
		CSG c = CSG(op, &s1, &s2);
		std::vector<Intersection> xs = Intersection::intersections({
			Intersection(1, &s1),
			Intersection(2, &s2),
			Intersection(3, &s1),
			Intersection(4, &s2),
		});
		std::vector<Intersection> result = c.filter_intersections(xs);
		EXPECT_EQ(result.size(), 2);
		EXPECT_TRUE(result[0] == xs[x0]);
		EXPECT_TRUE(result[1] == xs[x1]);
	}
}

TEST(Chapter16_tests, A_ray_misses_a_CSG_object) {
	Sphere s1;
	Cube s2;
	CSG c = CSG(Operation::UNION, &s1, &s2);
	Ray r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
	std::vector<Intersection> xs = c.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs.size(), 0);
}

TEST(Chapter16_tests, A_ray_hits_a_CSG_object) {
	Sphere s1;
	Cube s2;
	s2.SetTransform(Matrix4().translation(0, 0, 0.5));
	CSG c = CSG(Operation::UNION, &s1, &s2);
	Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
	std::vector<Intersection> xs = c.local_intersect(r.to_ray_struct());
	EXPECT_EQ(xs.size(), 2);
	EXPECT_EQ(xs[0].GetTime(), 4);
	EXPECT_TRUE(*xs[0].GetObject() == s1);
	EXPECT_EQ(xs[1].GetTime(), 6.5f);
	EXPECT_TRUE(*xs[1].GetObject() == s2);
}
#pragma endregion
