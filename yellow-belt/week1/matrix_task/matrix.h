//
// Created by alexa on 12.11.2021.
//

#ifndef WEEK1_MATRIX_H
#define WEEK1_MATRIX_H


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <tuple>

using namespace std;

class Matrix {
public:

	Matrix(int row_number, int col_number) {
		Reset(row_number, col_number);
	}

	Matrix() : col_num(0), row_num(0) {}

	void Reset(int new_row_number, int new_col_number) {
		CheckBoundsNonNegative(new_col_number, new_row_number);
		col_num = new_col_number;
		row_num = new_row_number;
		FillMatrixWithZeros();
	}

	int At(int row, int col) const {
		CheckInBounds(row, col);
		int ind = row * col_num + col;
		return content[ind];
	}

	int &At(int row, int col) {
		CheckInBounds(row, col);
		int ind = row * col_num + col;
		return content[ind];
	}

	int GetNumRows() const {
		return row_num;
	}

	int GetNumColumns() const {
		return col_num;
	}

private:
	int col_num;
	int row_num;
	vector<int> content;

	void FillMatrixWithZeros() {
		content = vector<int>(col_num * row_num, 0);
	}

	static void CheckBoundsNonNegative(int col, int row) {
		if (col < 0) {
			throw out_of_range("Column number should be non-negative but was" + to_string(col));
		}

		if (row < 0) {
			throw out_of_range("Row number should be non-negative but was" + to_string(row));
		}
	}

	void CheckInBounds(int row, int col) const {
		CheckBoundsNonNegative(col, row);
		if (col >= col_num) {
			throw out_of_range("Column number should be less than " + to_string(col_num) + "but was" + to_string(col));
		}

		if (row >= row_num) {
			throw out_of_range("Row number should be less than " + to_string(row_num) + "but was" + to_string(row));
		}
	}
};

string GetFirstNonEmptyLine(istream& stream) {
	string str;
	while (getline(stream, str) && str.empty()) {}
	return str;
}

void ReadMatrixRowContent(istream &stream, Matrix &matrix, int row, int num_columns) {
	for (int colInd = 0; colInd < num_columns; colInd++) {
		int el;
		stream >> el;
		matrix.At(row, colInd) = el;
	}
}

void ReadMatrixRow(istream &stream, Matrix &matrix, int row) {
	string row_str;
	getline(stream, row_str);
	int num_columns = matrix.GetNumColumns();
	istringstream ss(row_str);
	ReadMatrixRowContent(ss, matrix, row, num_columns);
}

istream &operator>>(istream &stream, Matrix &matrix) {
	string input_line = GetFirstNonEmptyLine(stream);
	int row_count, col_count;

	istringstream ss(input_line);
	ss >> row_count >> col_count;

	matrix = Matrix(row_count, col_count);
	for (int rowInd = 0; rowInd < row_count; rowInd++) {
		ReadMatrixRow(stream, matrix, rowInd);
	}

	return stream;
}

ostream &operator<<(ostream &stream, const Matrix &matrix) {
	stream << matrix.GetNumRows() << ' ' << matrix.GetNumColumns() << endl;

	for (int rowInd = 0; rowInd < matrix.GetNumRows(); rowInd++) {
		for (int colInd = 0; colInd < matrix.GetNumColumns() - 1; colInd++) {
			stream << matrix.At(rowInd, colInd) << ' ';
		}
		if (matrix.GetNumColumns() > 1) {
			stream << matrix.At(rowInd, matrix.GetNumColumns() - 1);
		}
		stream << endl;
	}

	return stream;
}

bool operator==(const Matrix &lhs, const Matrix &rhs) {
	auto[left_num_rows, left_num_cols] = make_tuple(lhs.GetNumRows(), lhs.GetNumColumns());
	auto[right_num_rows, right_num_cols] = make_tuple(rhs.GetNumRows(), rhs.GetNumColumns());

	if (left_num_rows * left_num_cols == 0 && right_num_rows * right_num_cols == 0) {
		return true;
	}

	if ((left_num_rows != right_num_rows) || (left_num_cols != right_num_cols)) {
		return false;
	}

	for (int rowInd = 0; rowInd < left_num_rows; ++rowInd) {
		for (int colInd = 0; colInd < left_num_cols; ++colInd) {
			if (lhs.At(rowInd, colInd) != rhs.At(rowInd, colInd)) {
				return false;
			}
		}
	}

	return true;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
	auto[num_rows, num_cols] = make_tuple(lhs.GetNumRows(), lhs.GetNumColumns());
	auto[right_num_rows, right_num_cols] = make_tuple(rhs.GetNumRows(), rhs.GetNumColumns());

	if (num_rows * num_cols == 0 && right_num_rows * right_num_cols == 0) {
		return lhs;
	}

	if ((num_rows != right_num_rows) || (num_cols != right_num_cols)) {
		throw invalid_argument("Attempted to add matrices of different sizes");
	}

	Matrix res(num_rows, num_cols);
	for (int rowInd = 0; rowInd < num_rows; ++rowInd) {
		for (int colInd = 0; colInd < num_cols; ++colInd) {
			res.At(rowInd, colInd) = lhs.At(rowInd, colInd) + rhs.At(rowInd, colInd);
		}
	}

	return res;
}


#endif //WEEK1_MATRIX_H
