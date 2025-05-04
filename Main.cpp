//emuna002@gmail.com
#include <iostream>
#include "SquareMat.h"

int main() {
    using namespace matlib;

    // יצירת מטריצות לדוגמה
    SquareMat mat1(3); // מטריצה בגודל 3x3
    SquareMat mat2(3); // מטריצה נוספת בגודל 3x3

    // מילוי המטריצות בערכים (לצורך הדוגמה)
    double data1[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    double data2[3][3] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};

    // העתקת הערכים למטריצות
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j) {
            mat1[i][j] = data1[i][j];
            mat2[i][j] = data2[i][j];
        }

    // הדפסת המטריצות
    std::cout << "mat1:\n" << mat1;
    std::cout << "mat2:\n" << mat2;

    // פעולות על המטריצות
    SquareMat resultAdd = mat1 + mat2;
    std::cout << "mat1 + mat2:\n" << resultAdd;

    SquareMat resultMult = mat1 * mat2;
    std::cout << "mat1 * mat2:\n" << resultMult;

    // שימוש באופרטורים משולבים
    mat1 += mat2;
    std::cout << "mat1 += mat2:\n" << mat1;

    mat1 *= 2.0;
    std::cout << "mat1 *= 2:\n" << mat1;

    // טסטים נוספים
    std::cout << "Determinant of mat1: " << !mat1 << std::endl;

    // הדפסת מטריצה לאחר שימוש באופרטור הפיכה (~)
    SquareMat invMat = ~mat1;
    std::cout << "Inverse of mat1:\n" << invMat;

    return 0;
}
