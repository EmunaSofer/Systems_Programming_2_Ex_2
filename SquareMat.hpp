//emuna002@gmail.com
#pragma once
#include <iostream>
#include <stdexcept>

namespace matlib {

class SquareMat {
private:
    double** data;  // מערך דו-ממדי של נתונים
    size_t size;    // גודל המטריצה (n עבור מטריצה nxn)

    void validateSameSize(const SquareMat& other) const;
    double determinantRecursive(double** mat, size_t n) const;

public:
    // בנאים
    SquareMat(size_t n);  // בנאי ברירת מחדל - יוצרת מטריצה ריקה (0x0)
    SquareMat(const double** input,  size_t n);  // בנאי עם מערך קלט
     // הבנאי המעתיק
     SquareMat(const SquareMat& other);
     // המפעיל המשובץ
     SquareMat& operator=(const SquareMat& other);

    // פעולות מתמטיות
    SquareMat operator+(const SquareMat& other) const;
    SquareMat operator-(const SquareMat& other) const;
    SquareMat operator*(const SquareMat& other) const;
    SquareMat operator*(double scalar) const;
    friend SquareMat operator*(double scalar, const SquareMat& mat);
    SquareMat operator%(const SquareMat& other) const;
    SquareMat operator%(int scalar) const;
    SquareMat operator/(double scalar) const;
    SquareMat operator^(int power) const;

    // אופרטורים מיוחדים
    SquareMat operator-() const;
    SquareMat& operator++(); // pre
    SquareMat& operator--();
    SquareMat operator~() const; // הפיכה
    double operator!() const; // דטרמיננטה

    // גישה לאיברים
    double* operator[](size_t index);
    const double* operator[](size_t index) const;

    // השוואות
    bool operator==(const SquareMat& other) const;
    bool operator!=(const SquareMat& other) const;
    bool operator<(const SquareMat& other) const;
    bool operator<=(const SquareMat& other) const;
    bool operator>(const SquareMat& other) const;
    bool operator>=(const SquareMat& other) const;

    // השמה משולבת
    SquareMat& operator+=(const SquareMat& other);
    SquareMat& operator-=(const SquareMat& other);
    SquareMat& operator*=(const SquareMat& other);
    SquareMat& operator*=(double scalar);
    SquareMat& operator%=(const SquareMat& other);
    SquareMat& operator%=(int scalar);
    SquareMat& operator/=(double scalar);

    // פלט
    friend std::ostream& operator<<(std::ostream& os, const SquareMat& mat);

    // מנגנון לשחרור זיכרון
    ~SquareMat();  // Destructor לשחרור זיכרון שהוקצה דינמית
};

} // namespace matlib
