#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
  Ball( Velocity v, Point cen, double r, Color col, double m = 1. ) :
    _velosity( v ),
    _center( cen ),
    _radius( r ),
    _color( col ),
    _mass( m )
  {};

  void setVelocity( const Velocity & velocity );
  Velocity getVelocity() const;
  void draw( Painter & painter ) const;
  void setCenter( const Point & center );
  Point getCenter() const;
  double getRadius() const;
  double getMass() const;
private:
  Velocity _velosity;
  Point  _center;
  double _radius;
  Color _color;
  double _mass;
};
