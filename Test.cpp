//emuna002@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.hpp"  // עדכון נתיב ל-SquareMat.h שלך
#include <stdexcept>

using namespace matlib;

TEST_CASE("SquareMat constructor and size") {
    // יצירת מטריצה בגודל 3
    SquareMat mat(3);

    CHECK(mat[0][0] == 0);
    CHECK(mat[1][1] == 0);
    CHECK(mat[2][2] == 0);
}

TEST_CASE("Addition operator (+)") {
    SquareMat mat1(2);
    SquareMat mat2(2);
    
    mat1[0][0] = 1; mat1[0][1] = 2;
    mat1[1][0] = 3; mat1[1][1] = 4;

    mat2[0][0] = 5; mat2[0][1] = 6;
    mat2[1][0] = 7; mat2[1][1] = 8;

    SquareMat result = mat1 + mat2;

    CHECK(result[0][0] == 6);
    CHECK(result[0][1] == 8);
    CHECK(result[1][0] == 10);
    CHECK(result[1][1] == 12);
}

TEST_CASE("Subtraction operator (-)") {
    SquareMat mat1(2);
    SquareMat mat2(2);
    
    mat1[0][0] = 5; mat1[0][1] = 6;
    mat1[1][0] = 7; mat1[1][1] = 8;

    mat2[0][0] = 1; mat2[0][1] = 2;
    mat2[1][0] = 3; mat2[1][1] = 4;

    SquareMat result = mat1 - mat2;

    CHECK(result[0][0] == 4);
    CHECK(result[0][1] == 4);
    CHECK(result[1][0] == 4);
    CHECK(result[1][1] == 4);
}

TEST_CASE("Unary minus operator (-)") {
    SquareMat mat(2);
    
    mat[0][0] = 1; mat[0][1] = 2;
    mat[1][0] = 3; mat[1][1] = 4;

    SquareMat result = -mat;

    CHECK(result[0][0] == -1);
    CHECK(result[0][1] == -2);
    CHECK(result[1][0] == -3);
    CHECK(result[1][1] == -4);
}

TEST_CASE("Multiplication operator (*)") {
    SquareMat mat1(2);
    SquareMat mat2(2);
    
    mat1[0][0] = 1; mat1[0][1] = 2;
    mat1[1][0] = 3; mat1[1][1] = 4;

    mat2[0][0] = 5; mat2[0][1] = 6;
    mat2[1][0] = 7; mat2[1][1] = 8;

    SquareMat result = mat1 * mat2;

    CHECK(result[0][0] == 19);  // 1*5 + 2*7
    CHECK(result[0][1] == 22);  // 1*6 + 2*8
    CHECK(result[1][0] == 43);  // 3*5 + 4*7
    CHECK(result[1][1] == 50);  // 3*6 + 4*8
}

TEST_CASE("Scalar multiplication") {
    SquareMat mat(2);
    
    mat[0][0] = 1; mat[0][1] = 2;
    mat[1][0] = 3; mat[1][1] = 4;

    SquareMat result = mat * 2;

    CHECK(result[0][0] == 2);
    CHECK(result[0][1] == 4);
    CHECK(result[1][0] == 6);
    CHECK(result[1][1] == 8);
}

TEST_CASE("Scalar modulo operator") {
    SquareMat mat(2);
    
    mat[0][0] = 5; mat[0][1] = 8;
    mat[1][0] = 9; mat[1][1] = 11;

    SquareMat result = mat % 3;

    CHECK(result[0][0] == 2);  // 5 % 3
    CHECK(result[0][1] == 2);  // 8 % 3
    CHECK(result[1][0] == 0);  // 9 % 3
    CHECK(result[1][1] == 2);  // 11 % 3
}

TEST_CASE("Matrix transpose (~)") {
    SquareMat mat(2);
    
    mat[0][0] = 1; mat[0][1] = 2;
    mat[1][0] = 3; mat[1][1] = 4;

    SquareMat result = ~mat;

    CHECK(result[0][0] == 1);
    CHECK(result[1][0] == 2);
    CHECK(result[0][1] == 3);
    CHECK(result[1][1] == 4);
}

TEST_CASE("Matrix equality operator (==)") {
    SquareMat mat1(2);
    SquareMat mat2(2);

    mat1[0][0] = 1; mat1[0][1] = 2;
    mat1[1][0] = 3; mat1[1][1] = 4;

    mat2[0][0] = 1; mat2[0][1] = 2;
    mat2[1][0] = 3; mat2[1][1] = 4;

    CHECK(mat1 == mat2);
}

TEST_CASE("Matrix inequality operator (!=)") {
    SquareMat mat1(2);
    SquareMat mat2(2);

    mat1[0][0] = 1; mat1[0][1] = 2;
    mat1[1][0] = 3; mat1[1][1] = 4;

    mat2[0][0] = 5; mat2[0][1] = 6;
    mat2[1][0] = 7; mat2[1][1] = 8;

    CHECK(mat1 != mat2);
}

TEST_CASE("Matrix determinant") {
    SquareMat mat(2);
    
    mat[0][0] = 1; mat[0][1] = 2;
    mat[1][0] = 3; mat[1][1] = 4;

    CHECK(mat.operator!() == -2);  // הנחה שיש מתודה בשם determinant()
}

TEST_CASE("Matrix size mismatch exception") {
    SquareMat mat1(2);
    SquareMat mat2(3);  // מטריצה בגודל שונה

    // חיבור בין מטריצות בגודל שונה יזרוק חריגה
    CHECK_THROWS_AS(mat1 + mat2, std::invalid_argument);
}

TEST_CASE("Accessing out-of-bound index") {
    SquareMat mat(2);

    // ניסיון לגשת לאינדקס מחוץ לטווח
    CHECK_THROWS_AS(mat[3][3], std::out_of_range);
}
