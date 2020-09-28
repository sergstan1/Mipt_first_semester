#include <stdio.h>
#include <math.h>
#include <assert.h>


const int CASQE_INFINITY_SOLUTIONS = -1;
double Eps = 1e-6;


//--------------------------------------------------
//! Tests Count_and_solve_quadratic_equation
//--------------------------------------------------


void Test_Count_and_solve_quadratic_equation(void);


//--------------------------------------------------
//! Compare input with zero with certain accuracy
//!
//! @param[in] a what we compare
//!
//! @return 1(True = 0) or 0(False != 0)
//!
//! @note accuracy = 10^(-6)
//--------------------------------------------------


bool Iszero(double a);


//--------------------------------------------------
//! Solves a quadratic equation ax^2 + bx + c
//!
//! @param[in] a quadratic coefficent
//! @param[in] b linear coefficent
//! @param[in] c free coefficent
//! @param[out] x1 first solution
//! @param[out] x2 second solution
//!
//! @return number of routes
//!
//! @note in case infinite routes,
//!               returns CASQE_INFINITY_SOLUTIONS.
//--------------------------------------------------


int Count_and_solve_quadratic_equation(double a, double b, double c, double* x1, double* x2);


//--------------------------------------------------
//! Compares result of expression with True
//! 
//! @param[in] name name of test
//! @param[in] expression what we compare
//! 
//! @return true or false
//--------------------------------------------------


bool Test_function(const char* name, int expression);


//--------------------------------------------------
//! Check, that input is correct
//!
//! @param[in] result  number of correct inputs
//! @param[in] a what we scan
//! @param[in] b what we scan
//! @param[in] c what we scan
//!
//! @return void
//--------------------------------------------------


void Check_scanf(int result, double* a, double* b, double* c);
