#include "Matrix.h"
#include <iostream>

//Matrix empty constructor
Matrix::Matrix() {
    row_num = 0; 
    col_num = 0;
    arrPointer = 0; 
}
//Matrix constructor when fill with two unsigned int and double
Matrix::Matrix(unsigned int row_count, unsigned int col_count, double fill) {
    row_num = row_count;
    col_num = col_count;
    //creating the pointer and initializing values within the 2D array
    arrPointer = new double*[row_num];
    for(int i = 0; i < row_num; i++) {
        arrPointer[i] = new double[col_num];
        for(int j = 0; j < col_num; j++) {
            arrPointer[i][j] = fill;
        }
    }

}
//copy constructor
Matrix::Matrix(const Matrix& t) {
    row_num = t.num_rows();
    col_num = t.num_cols();
    //copy the value from Matrix t and put it into this Matrix
    arrPointer = new double*[row_num];
    for(int i = 0; i < row_num; i++) {
        arrPointer[i] = new double[col_num];
        for(int j = 0; j < col_num; j++) {
            t.get(i,j,arrPointer[i][j]);
        }
    }
}

//destructor 
Matrix::~Matrix() {
    //loop through and delete the row arrays within the 2D array
    for(unsigned int i = 0; i < row_num; i++) {
        delete [] arrPointer[i];
    }
    delete [] arrPointer;
}

//return the number of rows
unsigned int Matrix::num_rows() const {
    return row_num;
}

//return the number of columns
unsigned int Matrix::num_cols() const {
    return col_num;
}

//Takes in 2 unsigned int and one double reference
//return true if the row and column are within the bound of Matrix
//else return false
bool Matrix::get(unsigned int row, unsigned int column, double& store) const {
    //checks the bound and store the value into the double
    if(row < row_num && column < col_num) {
        store = arrPointer[row][column];
        return true;
    }
    return false;
}

//Takes in two unsigned int and a double store
//return true if the row and column are within the bound of Matrix
//else return false
bool Matrix::set(unsigned int row, unsigned int column, double store) const {
    //check bounds
    if(row < row_num && column < col_num) {
        //set the value of arrPointer[row][column] to store
        arrPointer[row][column] = store;
        return true;
    }
    return false;
}

//takes in a double mutliple
//multiply all instances within arrPointer with multiple
void Matrix::multiply_by_coefficient(double multiple) {
    for(int row = 0; row < row_num; row++) {
        for(int column = 0; column < col_num; column++) {
            arrPointer[row][column] = (arrPointer[row][column] * multiple);
        }
    }
}

//takes in a source row, target row
//return true if the rows are within bounds
//else false;
bool Matrix::swap_row(unsigned int source_row, unsigned int target_row) const {
    //check bounds
    if(source_row < row_num && target_row < row_num) {
        //swapping the rows
        for(int i = 0; i < col_num; i++) {
            double placeHold = arrPointer[source_row][i];
            arrPointer[source_row][i] = arrPointer[target_row][i];
            arrPointer[target_row][i] = placeHold;
        }
        return true;
    }
    return false;
}

//switching the row and column of the matrix
void Matrix::transpose() {
    //creating a new double** for storing the now changed Matrix
    double** temp = new double*[col_num];
    //creating the new format for the matrix and inserting values.
    for(int row = 0; row < col_num; row++) {
        temp[row] = new double[row_num];
        for(int col = 0; col < row_num; col++) {
            temp[row][col] = arrPointer[col][row];
        }
    }
    int tempRow = row_num;
    int tempCol = col_num;
    //clean up the memory, deleting the arrPointer
    clear();
    row_num = tempCol;
    col_num = tempRow;
    arrPointer = temp;
}

//takes in a Matrix reference object and add the current Matrix with the Matrix object
//return true if in bound
//else false
bool Matrix::add(Matrix& B) {
    //check bounds
    if(row_num == B.row_num && col_num == B.col_num) {
        //interate through the Matrix and just add the two values at that part
        for(int row = 0; row < row_num; row++) {
            for(int col = 0; col < col_num; col++) {
                set(row, col, (arrPointer[row][col] + B.arrPointer[row][col]));
            }
        }
        return true;
    }
    return false;
}

//takes in a Matrix reference object and subtract the curr Matrix with the Matrix object
//return true if in bound
//else false
bool Matrix::subtract(Matrix& B) { 
    //check bounds
    if(row_num == B.row_num && col_num == B.col_num) {
        //iterate through to get the each value of the matrix to subtract them.
        for(int row = 0; row < row_num; row++) {
            for(int col = 0; col < col_num; col++) {
                set(row, col, (arrPointer[row][col] - B.arrPointer[row][col]));
            }
        }
        return true;
    }
    return false;
}

//deallocating memories but let the object still exist
void Matrix::clear() {
    for(int i = 0; i < row_num; i++) {
        delete [] arrPointer[i];
    }
    delete [] arrPointer;
    row_num = 0;
    col_num = 0;
}

//operator << that print out the Matrix
std::ostream& operator << (std::ostream& out, const Matrix& m) {
    unsigned int rowNum = m.num_rows();
    unsigned int colNum = m.num_cols();
    double output =0;
    //formatting of the first line
    out << "\n"<<rowNum << " x " << colNum << " matrix: \n";
    out << "[ ";
    for(int row = 0; row < rowNum; row++) {
        //adding spaces for formatting since the first row has "[ "
        if(row!= 0) {out<< "  ";}
        //getting the values in the Matrix and put it in out
        for(int column = 0; column < colNum; column++) {
            m.get(row, column, output);
            out << output << " ";
        }
        //skip a line for formatting
        if(row != rowNum-1) {out << "\n";}
    }
    out << "]\n";
    return out;
}

//boolean operator == that works on Matrix object
//return true if the two objects are equal
//else false
bool Matrix::operator==(const Matrix& B) const {
    //check bounds, if not within bounds, return false
    if(row_num != B.row_num || col_num != B.col_num) {
        return false;
    }
    //iterate to get each value of Matrix and check if any of values
    //does not equal to Matrix object B's value
    //return false if not equal
    for(int row = 0; row < row_num; row++) {
        for(int column = 0; column < col_num; column++) {
            if(arrPointer[row][column] != B.arrPointer[row][column]) {
                return false;
            }
        }
    }
    return true;
}

//return true if two objects are not equal
//else false
bool Matrix::operator!=(const Matrix& B) const {
    //check bounds, return false if they are within
    if(row_num == B.row_num || col_num == B.col_num) {
        return false;
    }
    //iterate to get each value of the matrix
    //return false if the values are equal
    for(int row = 0; row < row_num; row++) {
        for(int column = 0; column < col_num; column++) {
            if(arrPointer[row][column] == B.arrPointer[row][column]) {
                return false;
            }
        }
    }
    return true;
}

//set the current Matrix equal to Matrix B
//copy the values over
void Matrix::operator=(const Matrix& B) {
    row_num = B.num_rows();
    col_num = B.num_cols();
    arrPointer = new double*[row_num];
    //iterate to transfer the values over
    for(int i = 0; i < row_num; i++) {
        arrPointer[i] = new double[col_num];
        for(int j = 0; j < col_num; j++) {
            B.get(i,j,arrPointer[i][j]);
        }
    }
}

//HARDER MATRIX OPERATIONS

//takes in unsigned int of number of row
//return a double pointer containing the row of the Matrix
double* Matrix::get_row(unsigned int numRow) {
    double* output = new double[col_num];
    //check the bounds
    if(numRow < row_num) {
        //iterate through to get the specified row 
        for(int col = 0; col < col_num; col++) {
            output[col] = arrPointer[numRow][col];
        }
    }
    else { 
        //not in bound
        output = NULL;
    }
    return output;
}

//takes in unsigned int of number of column
//return a double pointer containing the column of the Matrix
double* Matrix::get_col(unsigned int numCol) {
    double* output = new double[row_num];
    //check the bounds of column
    if(numCol < col_num){
        //iterate through to get the specified column
        for(unsigned row = 0; row < row_num; row++) {
            output[row] += arrPointer[row][numCol];
        }
    }
    else {
        //not in bound
        output = NULL;
    }
    return output;
}

//return a Matrix pointer
Matrix* Matrix::quarter() {
    Matrix* output = new Matrix[4];
    unsigned int rowMid = row_num/2;
    unsigned int colMid = col_num/2;

    //UL
    //if row_num is even, then use rowMid, if col_num is even, use colMid 
    //used to help with odd and even matrixes
    output[0]= Matrix(row_num%2==0 ? rowMid : rowMid+1, 
    col_num%2 ==0 ? colMid : colMid+1, 0); 
    //iterate and get the value of the Matrix at the upper left
    //set it into the Matrix object
    for(int row = 0; row < (row_num%2==0 ? rowMid : rowMid+1); row++) {
        for(int col = 0; col < (col_num%2 ==0 ? colMid : colMid+1); col++) {
            output[0].set(row, col, arrPointer[row][col]);
        }
        
    }

    //UR
    //if row_num is even, then use rowMid, if col_num is even, use colMid 
    //used to help with odd and even matrixes
    output[1] = Matrix(row_num%2 ==0? rowMid : rowMid+1, col_num%2==0 ? colMid : colMid+1, 0);
    //iterate and get the value of the Matrix at the upper right
    for(int row = 0; row < (row_num%2==0 ? rowMid : rowMid+1); row++) {
        for(int col = colMid; col < col_num; col++) {
            output[1].set(row, col - colMid, arrPointer[row][col]);
        }
    }

    //LL
    //if row_num is even, then use rowMid, if col_num is even, use colMid 
    //used to help with odd and even matrixes
    output[2]=Matrix(row_num%2 ==0? rowMid : rowMid+1, col_num%2 ==0? colMid : colMid+1, 0);
    //iterate and get the value of the Matrix at the lower left
    for(int row = rowMid; row < row_num; row++) {
        for(int col = 0; col < (col_num%2 ==0? colMid : colMid+1); col++ ){
            output[2].set(row-rowMid, col, arrPointer[row][col]);
        }
    }

    //LR
    //if row_num is even, then use rowMid, if col_num is even, use colMid 
    //used to help with odd and even matrixes
    output[3]=Matrix((row_num%2 ==0)? rowMid : rowMid+1, col_num%2 ==0 ? colMid : colMid+1, 0);
    //iterate and get the value of the Matrix at the lower right
    for(int row = rowMid; row < row_num; row++) {
        for(int col = colMid; col < col_num; col++) {
            output[3].set(row-rowMid, col-colMid, arrPointer[row][col]);
        }
    }
    return output;

} 


