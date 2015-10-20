#include "Drawable.h"
#include "defs.h"
#include <iostream>


Drawable::Drawable() : direction(-1) {
    this->m2w.makeIdentity();
}

Drawable::~Drawable() {
    //
}

void Drawable::toggleDirection() {
    direction = -direction;
}

void Drawable::spin(GLfloat deg) {
    // Relative to model space
    Vector3 disp = m2w.getTranslate();
    m2w = (Matrix4().makeRotateY(direction * deg) * m2w).setTranslate(disp);
}

void Drawable::orbit(GLfloat deg) {
    // Relative to world space
    m2w = Matrix4().makeRotateZ(deg) * m2w;
}

void Drawable::translateX(GLfloat units) {
    // Relative to world space
    m2w = Matrix4().makeTranslate(units, 0.f, 0.f) * m2w;
}

void Drawable::translateY(GLfloat units) {
    // Relative to world space
    m2w = Matrix4().makeTranslate(0.f, units, 0.f) * m2w;
}

void Drawable::translateZ(GLfloat units) {
    // Relative to world space
    m2w = Matrix4().makeTranslate(0.f, 0.f, units) * m2w;
}

void Drawable::scale(GLfloat a, GLfloat b, GLfloat c) {
    // Relative to model space
    Vector3 disp = m2w.getTranslate();
    m2w = (Matrix4().makeScale(a, b, c) * m2w).setTranslate(disp);
}

void Drawable::reset() {
    this->m2w.makeIdentity();
}

void Drawable::draw() {
    std::cout << "Warning: draw() is not implemented" << std::endl;
}

void Drawable::update() {
    std::cout << "Warning: update() is not implemented" << std::endl;
}
