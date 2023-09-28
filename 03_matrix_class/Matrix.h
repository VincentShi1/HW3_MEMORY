#include <iostream>
#ifndef _Matrix_h
#define _Matrix_h

class Matrix {
public:
    //Constructor
    Matrix(unsigned int row_count, unsigned int col_count, double fill);
    Matrix();
    Matrix(const Matrix &t); // object shit
    ~Matrix();
    //Add a destructor

    unsigned int num_rows() const;
    unsigned int num_cols() const;
    //SIMPLE MATRIX OPERATIONS
    bool get(unsigned int row, unsigned int column, double& store) const; //
    bool set(unsigned int row, unsigned int column, double store) const; //
    void clear(); //? maybe need the column too with for loop
    void multiply_by_coefficient(double multiple);
    bool swap_row(unsigned int source_row, unsigned int target_row) const;
    void transpose();
    bool add(Matrix& B);
    bool subtract(Matrix& B);
    bool operator==(const Matrix& B) const;
    bool operator!=(const Matrix& B) const;
    void operator=(const Matrix& B);
    //HARDER MATRIX
    double* get_row(unsigned int numRow);
    double* get_col(unsigned int numCol);
    Matrix* quarter();

private:
    unsigned int row_num, col_num;
    double** arrPointer;

};

std::ostream& operator << (std::ostream& out, const Matrix& m);

#endif