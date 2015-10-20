#include "Matrix4.h"
#include "defs.h"
#include <iomanip>
#include <Math.h>

Matrix4::Matrix4() {
    for( int i=0; i < 4; ++i ) {
        for( int j=0; j < 4; ++j) {
            m[i][j] = 0;
        }
    }
}

Matrix4::Matrix4(const GLfloat (&el)[4][4]) {
    for( int i=0; i < 4; ++i ) {
        for( int j=0; j < 4; ++j) {
            m[i][j] = el[i][j];
        }
    }
}

GLfloat* Matrix4::getPointer() {
    return &m[0][0];
}

/* ==== */

Matrix4 Matrix4::operator*(const Matrix4& mt) const {
    Matrix4 t = Matrix4();
    for( int r = 0; r < 4; ++r ) {
        for( int c = 0; c < 4; ++c) {
            t.m[r][c] = m[r][0]*mt.m[0][c] + m[r][1]*mt.m[1][c] + m[r][2]*mt.m[2][c] + m[r][3]*mt.m[3][c];
        }
    }
    return t;
}

//Big loss of precision, will maybe have to use fractions
Vector4 Matrix4::operator*(const Vector4& v) const {
    Vector4 t = Vector4();
    t.x = m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z + m[0][3]*v.w;
    t.y = m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z + m[1][3]*v.w;
    t.z = m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z + m[2][3]*v.w;
    t.w = m[3][0]*v.x + m[3][1]*v.y + m[3][2]*v.z + m[3][3]*v.w;
    return t;
    
}

Matrix4& Matrix4::operator=(const Matrix4& mat) {
    if (this != &mat) {
        for (int i=0; i<4; ++i) {
            for (int j=0; j<4; ++j) {
                m[i][j] = mat.m[i][j];
            }
        }
    }
    return *this;
}

/* ==== */

Matrix4& Matrix4::makeIdentity() {
    for( int i=0; i < 4; ++i ) {
        for( int j=0; j < 4; ++j) {
            m[i][j] = (GLfloat)(i == j);
        }
    }
    return *this;
}

Matrix4& Matrix4::makeTranspose() {
    for (int i=0; i<4; ++i) {
        for (int j=i; j<4; ++j) {
            if( i == j) continue;
            GLfloat t = m[j][i];
            m[j][i] = m[i][j];
            m[i][j] = t;
        }
    }
    return *this;
}

Matrix4& Matrix4::makeRotateX(GLfloat deg) {
    deg = deg / 180.0 * M_PI;
    makeIdentity();
    m[1][1] = cos(deg);
    m[1][2] = -sin(deg);
    m[2][1] = sin(deg);
    m[2][2] = cos(deg);
    return *this;
}

Matrix4& Matrix4::makeRotateY(GLfloat deg) {
    deg = deg / 180.0 * M_PI;  // convert from degrees to radians
    makeIdentity();
    m[0][0] = cos(deg);
    m[0][2] = sin(deg);
    m[2][0] = -sin(deg);
    m[2][2] = cos(deg);
    return *this;
}

Matrix4& Matrix4::makeRotateZ(GLfloat deg) {
    deg = deg / 180.0 * M_PI;
    makeIdentity();
    m[0][0] = cos(deg);
    m[0][1] = -sin(deg);
    m[1][0] = sin(deg);
    m[1][1] = cos(deg);
    return *this;
}

Matrix4& Matrix4::makeRotate(GLfloat deg, Vector3 a) {
    makeIdentity();
    a.normalize();
    deg = deg / 180.0 * M_PI;
    
    m[0][0] = 1 + (a.x * a.x - 1) * (1 - cos(deg));
    m[0][1] = -a.z * sin(deg) + a.x * a.y * (1 - cos(deg));
    m[0][2] = a.y * sin(deg) + a.x * a.z * (1 - cos(deg));
    
    m[1][0] = a.z * sin(deg) +  a.x * a.y * (1 - cos(deg));
    m[1][1] = 1 + (a.y * a.y - 1) * (1 - cos(deg));
    m[1][2] = -a.x * sin(deg) + a.y * a.z * (1 - cos(deg));
    
    m[2][0] = -a.y * sin(deg) + a.z * a.x * (1 - cos(deg));
    m[2][1] = a.x * sin(deg) + a.z * a.y * (1 - cos(deg));
    m[2][2] = 1 + (a.z * a.z - 1) * (1 - cos(deg));
    
    return *this;
}

/* ==== */

Matrix4& Matrix4::makeScale(GLfloat x, GLfloat y, GLfloat z) {
    makeIdentity();
    m[0][0] = x;
    m[1][1] = y;
    m[2][2] = z;
    return *this;
}

Matrix4& Matrix4::makeScale(const Vector3& v) {
    makeIdentity();
    m[0][0] = v.x;
    m[1][1] = v.y;
    m[2][2] = v.z;
    return *this;
}

Matrix4& Matrix4::makeTranslate(GLfloat x, GLfloat y, GLfloat z) {
    makeIdentity();
    m[0][3] = x;
    m[1][3] = y;
    m[2][3] = z;
    return *this;
}

Matrix4& Matrix4::makeTranslate(const Vector3& v) {
    makeIdentity();
    m[0][3] = v.x;
    m[1][3] = v.y;
    m[2][3] = v.z;
    return *this;
}
Matrix4& Matrix4::setTranslate(const Vector3& v) {
    m[0][3] = v.x;
    m[1][3] = v.y;
    m[2][3] = v.z;
    m[3][3] = 1;
    return *this;
}
Vector3 Matrix4::getTranslate() const {
    return Vector3(m[0][3], m[1][3], m[2][3]);
}

/* ==== */

Matrix4 Matrix4::identity() {
    return Matrix4({
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    });
}

Matrix4 Matrix4::transpose(const Matrix4& mt) {
    return Matrix4({
        {mt.m[0][0],mt.m[1][0],mt.m[2][0],mt.m[3][0]},
        {mt.m[0][1],mt.m[1][1],mt.m[2][1],mt.m[3][1]},
        {mt.m[0][2],mt.m[1][2],mt.m[2][2],mt.m[3][2]},
        {mt.m[0][3],mt.m[1][3],mt.m[2][3],mt.m[3][3]}
    });
}

/* ==== */

void Matrix4::print(std::string comment) {
    std::cout << std::endl << "\tMAT4: " << comment << std::endl << std::endl << this;
}

std::ostream& operator<<(std::ostream& o, const Matrix4& mt) {
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            std::cout << std::setw(6) << std::setfill(' ') << std::setprecision(2) << mt.m[r][c];
        }
        std::cout << std::endl << std::endl;
    }
    return o;
}