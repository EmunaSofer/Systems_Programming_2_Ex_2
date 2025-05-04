//emuna002@gmail.com
#include "SquareMat.hpp"
#include <cmath>  // בשביל std::fmod באופרטוק מודולו 

namespace matlib {


// --- בנאים ---
SquareMat::SquareMat(size_t n)
{
    size = n;
    data = new double*[n];  // הקצאת מערך ראשי של pointers
    for (size_t i = 0; i < n; ++i) {
        data[i] = new double[n]();  // הקצאת מערך נוסף לכל שורה ומאתחלים ל-0
    }
}

SquareMat::SquareMat(const double** input, size_t n)
{
    size = n;
    data = new double*[n];  // הקצאת מערך ראשי של pointers
    for (size_t i = 0; i < n; ++i) {
        data[i] = new double[n];
        for (size_t j = 0; j < n; ++j) {
            data[i][j] = input[i][j];  // העתקת הנתונים
        }
    }
}

SquareMat::SquareMat(const SquareMat& other) {
    size = other.size;
    data = new double*[size];
    for (size_t i = 0; i < size; ++i) {
        data[i] = new double[size];
        for (size_t j = 0; j < size; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}

SquareMat& SquareMat::operator=(const SquareMat& other) {
    if (this == &other) {
        return *this;  // אם מדובר בהעתקה של אותו אובייקט, אין צורך לפעול.
    }

    // שחרור זיכרון קודם
    for (size_t i = 0; i < size; ++i) {
        delete[] data[i];
    }
    delete[] data;

    // העתקת נתונים
    size = other.size;
    data = new double*[size];
    for (size_t i = 0; i < size; ++i) {
        data[i] = new double[size];
        for (size_t j = 0; j < size; ++j) {
            data[i][j] = other.data[i][j];
        }
    }

    return *this;
}

// --- שחרור זכרון ---
SquareMat::~SquareMat() {
    for (size_t i = 0; i < size; ++i) {
        delete[] data[i];  // מחיקת כל שורה
    }
    delete[] data;  // מחיקת מערך השורות
}


// --- פונקציות עזר ---

// הפונקציה בודקת אם למטריצה הנוכח ולמטריצה שנמסרה כפרמטר יש את אותו הגודל, כלומר אם מספר השורות והעמודות שלהן זהה
void SquareMat::validateSameSize(const SquareMat& other) const
{
    if (this->size != other.size) {
        throw std::invalid_argument("המטריצות לא באותו גודל");
    }
}

// מחשב את הדטרמיננטה של המטריצה
double SquareMat::determinantRecursive(double** mat, size_t n) const
{
    if (n == 1) {
        return mat[0][0];  // דטרמיננטה של מטריצה 1x1
    }

    if (n == 2) {
        // דטרמיננטה של מטריצה 2x2
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }

    double det = 0.0;
    for (size_t j = 0; j < n; ++j) {
        // יצירת מטריצת משנה
        double** submatrix = new double*[n-1];  // הקצאת זיכרון למטריצת משנה
        for (size_t i = 0; i < n - 1; ++i) {
            submatrix[i] = new double[n - 1];  // הקצאת זיכרון לכל שורה במטריצה
        }

        // בניית מטריצת משנה
        for (size_t i = 1; i < n; ++i) {
            size_t submatrix_col = 0;
            for (size_t j_sub = 0; j_sub < n; ++j_sub) {
                if (j_sub != j) {
                    submatrix[i - 1][submatrix_col++] = mat[i][j_sub];
                }
            }
        }

        // חישוב הדטרמיננטה רקורסיבית עם סימן (-1)^j
        det += ((j % 2 == 0 ? 1 : -1) * mat[0][j] * determinantRecursive(submatrix, n - 1));

        // שחרור זיכרון של מטריצת המשנה
        for (size_t i = 0; i < n - 1; ++i) {
            delete[] submatrix[i];
        }
        delete[] submatrix;
    }

    return det;
}


// --- פעולות מתמטיות ---

// אופרטור חיבור בין 2 מטריצות  
SquareMat SquareMat::operator+(const SquareMat& other) const 
{
    validateSameSize(other);
    SquareMat result(size);  // המטריצה שמחזירים
    for (size_t i = 0; i < size; ++i) 
    {
        for (size_t j = 0; j < size; ++j) 
        {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

// אופרטור חיסור בין 2 מטריצות
SquareMat SquareMat::operator-(const SquareMat& other) const 
{
    validateSameSize(other);
    SquareMat result(size);  // המטריצה שמחזירים
    for (size_t i = 0; i < size; ++i) 
    {
        for (size_t j = 0; j < size; ++j) 
        {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }
    return result;
}

// אופרטור כפל בין שתי מטריצות 
SquareMat SquareMat::operator*(const SquareMat& other) const 
{
    validateSameSize(other);
    SquareMat result(size);  // המטריצה שמחזירים
    for (size_t i = 0; i < size; ++i) 
    {
        for (size_t j = 0; j < size; ++j) 
        {
            for (size_t k = 0; k < size; ++k) 
            {
                result.data[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }
    return result;
}

// כפל כאשר הסקלאר במצד ימין 
SquareMat SquareMat::operator*(double scalar) const 
{
    SquareMat result(size);  // המטריצה שמחזירים
    for (size_t i = 0; i < size; ++i) 
    {
        for (size_t j = 0; j < size; ++j) 
        {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}

// הכפלה כאשר הסקלאר מופיע מצד שמאל
SquareMat operator*(double scalar, const SquareMat& mat) 
{
    return mat * scalar;
}

// כפל איברי
SquareMat SquareMat::operator%(const SquareMat& other) const 
{
    validateSameSize(other);  // בודק שאותו גודל
    SquareMat result(size);   // המטריצה שמחזירים   

    for (size_t i = 0; i < size; ++i) 
    {
        for (size_t j = 0; j < size; ++j) 
        {
            result.data[i][j] = data[i][j] * other.data[i][j]; // כפל איברי
        }
    }

    return result;
}

// מבצע מודולו על כל האיברים במטריצה
SquareMat SquareMat::operator%(int scalar) const 
{
    SquareMat result(size);  // המטריצה אחרי המודולו
    
    for (size_t i = 0; i < size; ++i) 
    {
        for (size_t j = 0; j < size; ++j) 
        {
            result.data[i][j] = std::fmod(data[i][j], scalar); // מודולו של double עם int
        }
    }

    return result;
}

// חילוק המטריצה 
SquareMat SquareMat::operator/(double scalar) const 
{
    if (scalar == 0) {
        throw std::invalid_argument("לא ניתן לחלק באפס");
    }
    SquareMat result(size);
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            result.data[i][j] = data[i][j] / scalar;
        }
    }
    return result;
}

// אופרטור חזקה 
SquareMat SquareMat::operator^(int power) const 
{
    if (power < 0) {
        throw std::invalid_argument("לא ניתן להעלות בחזקה שלילית בלי מטריצה הפוכה");
    }

    SquareMat result(size); // המטריצה שאני מחזירה 
    // אתחול ל־Identity matrix (מטריצת יחידה)
    for (size_t i = 0; i < size; ++i) {
        result.data[i][i] = 1.0;
    }

    if (power == 0) {
        return result; // מטריצה בחזקת אפס היא מטריצת יחידה
    }

    SquareMat base = *this;
    while (power > 0) {
        if (power % 2 == 1) {
            result = result * base;
        }
        base = base * base;
        power /= 2;
    }

    return result;
}

// חיסור אונארי
SquareMat SquareMat::operator-() const 
{
    SquareMat result(size); // המטריצה שמחזירים
    for (size_t i = 0; i < size; ++i) 
    {
        for (size_t j = 0; j < size; ++j) 
        {
            result.data[i][j] = -data[i][j];
        }
    }
    return result;
}

// הגדלה ב1 על כל האיברים במטריצה
SquareMat& SquareMat::operator++() 
{
    for (size_t i = 0; i < size; ++i) 
    {
        for (size_t j = 0; j < size; ++j) 
        {
            ++data[i][j];
        }
    }
    return *this;
}

// החסרה ב1 את כל האיברים במטריצה
SquareMat& SquareMat::operator--() 
{
    for (size_t i = 0; i < size; ++i) 
    {
        for (size_t j = 0; j < size; ++j) 
        {
            --data[i][j];
        }
    }
    return *this;
}

// שחלוף של המטריצה 
SquareMat SquareMat::operator~() const 
{
    SquareMat result(size);  // המטריצה שמחירים    
    for (size_t i = 0; i < size; ++i) 
    {
        for (size_t j = 0; j < size; ++j) 
        {
            result.data[j][i] = data[i][j];  // שורות ועמודות מתחלפות
        }
    }
    return result; 
}

// חישוב דטרמיננטה של המטריצה הנוכחית
double SquareMat::operator!() const 
{
    return determinantRecursive(data, size);  // שימוש בפונקציה של הדטרמיננטה
}


// גישה לאיברים
double* SquareMat::operator[](size_t index) 
{
    if (index >= size) {
        throw std::out_of_range("Index out of range");  // זריקת חריגה אם האינדקס לא תקין
    }
    return data[index];  // מחזיר מצביע לשורה במטריצה
}

// גישה לשורה במטריצה בצורה קבועה
const double* SquareMat::operator[](size_t index) const 
{
    if (index >= size) {
        throw std::out_of_range("Index out of range");  // זריקת חריגה אם האינדקס לא תקין
    }
    return data[index];  // מחזיר מצביע לשורה במטריצה בצורה קבועה
}


// --- השוואות ---
bool SquareMat::operator==(const SquareMat& other) const 
{
    if (size != other.size) 
    {
        return false;
    }
    for (size_t i = 0; i < size; ++i) 
    {
        for (size_t j = 0; j < size; ++j) 
        {
            if (data[i][j] != other.data[i][j]) 
            {
                return false;
            }
        }
    }
    return true;
}

bool SquareMat::operator!=(const SquareMat& other) const 
{
    return !(*this == other);
}

bool SquareMat::operator<(const SquareMat& other) const
{
    double sumThis = 0, sumOther = 0;
    for (size_t i = 0; i < size; ++i) 
    {
        for (size_t j = 0; j < size; ++j) 
        {
            sumThis += data[i][j];
            sumOther += other.data[i][j];
        }
    }
    return sumThis < sumOther;
}

bool SquareMat::operator>(const SquareMat& other) const
{
    return other < *this;
}

bool SquareMat::operator<=(const SquareMat& other) const
{
    return !(other < *this);
}

bool SquareMat::operator>=(const SquareMat& other) const
{
    return !(*this < other);
}

// --- השמה משולבת ---
SquareMat& SquareMat::operator+=(const SquareMat& other) 
{
    if (size != other.size) {
        throw std::invalid_argument("Matrices must have the same size for addition.");
    }

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            data[i][j] += other.data[i][j];
        }
    }
    return *this;  // מחזירים את המטריצה המעודכנת
}

SquareMat& SquareMat::operator-=(const SquareMat& other) 
{
    if (size != other.size) {
        throw std::invalid_argument("Matrices must have the same size for subtraction.");
    }

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            data[i][j] -= other.data[i][j];
        }
    }
    return *this;  // מחזירים את המטריצה המעודכנת
}

SquareMat& SquareMat::operator*=(const SquareMat& other) 
{
    if (size != other.size) {
        throw std::invalid_argument("Matrices must have the same size for multiplication.");
    }

    SquareMat result(size);  // ניצור מטריצה חדשה לאחסון התוצאה
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            result[i][j] = 0;
            for (size_t k = 0; k < size; ++k) {
                result[i][j] += data[i][k] * other.data[k][j];
            }
        }
    }

    *this = result;  // נעדכן את המטריצה הנוכחית עם התוצאה
    return *this;
}

SquareMat& SquareMat::operator*=(double scalar) 
{
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            data[i][j] *= scalar;
        }
    }
    return *this;  // מחזירים את המטריצה המעודכנת
}

SquareMat& SquareMat::operator%=(const SquareMat& other) 
{
    if (size != other.size) {
        throw std::invalid_argument("Matrices must have the same size for modulo.");
    }

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            data[i][j] = static_cast<int>(data[i][j]) % static_cast<int>(other.data[i][j]);
        }
    }
    return *this;  // מחזירים את המטריצה המעודכנת
}

SquareMat& SquareMat::operator%=(int scalar) 
{
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            data[i][j] = static_cast<int>(data[i][j]) % scalar;
        }
    }
    return *this;  // מחזירים את המטריצה המעודכנת
}

SquareMat& SquareMat::operator/=(double scalar) 
{
    if (scalar == 0) {
        throw std::invalid_argument("Cannot divide by zero.");
    }

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            data[i][j] /= scalar;
        }
    }
    return *this;  // מחזירים את המטריצה המעודכנת
}

// --- פלט ---
std::ostream& operator<<(std::ostream& os, const SquareMat& mat)
{
    for (size_t i = 0; i < mat.size; ++i) {
        for (size_t j = 0; j < mat.size; ++j) {
            os << mat.data[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}


} // namespace matlib
