#include "Ball.hpp"
#include <cmath>

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
  _velosity = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    return _velosity;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
  painter.draw( _center, _radius, _color );
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
  _center = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    return _center;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    return _radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    return _mass;
}
