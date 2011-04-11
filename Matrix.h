/* 
 * File:   Matrix.h
 * Author: jk
 *
 * Created on 15. August 2010, 18:13
 */

#ifndef MATRIX_H
#define	MATRIX_H

#include <inttypes.h>

#include "AbstractTest.h"

class Matrix {

    static const uint8_t MATRIX_FORWARD_ELIMINATION;
    static const uint8_t MATRIX_BACKWARD_ELIMINATION;

public:
    Matrix();
    ~Matrix();
    
    typedef unsigned char BitSequence;

    static int computeRank(int M, int Q, BitSequence **matrix);
    static void perform_elementary_row_operations(int flag, int i, int M, int Q, BitSequence **A);
    static int find_unit_element_and_swap(int flag, int i, int M, int Q, BitSequence **A);
    static int swap_rows(int i, int index, int Q, BitSequence **A);
    static int determine_rank(int m, int M, int Q, BitSequence **A);
    static BitSequence** create_matrix(int M, int Q);
    static void display_matrix(int M, int Q, BitSequence **m);
    static void def_matrix(int M, int Q, BitSequence **m,int k, AbstractTest *dataSrc);
    static void delete_matrix(int M, BitSequence **matrix);

private:

};

#endif	/* MATRIX_H */

