#include <QtGlobal>

#include <Vector.h>
#include <cmath>

Vector::Vector()
   : x_(0.0)
   , y_(0.0)
   , z_(0.0)
{
}

Vector::Vector(double x_, double y_, double z_)
   : x_(x_)
   , y_(y_)
   , z_(z_)
{
}

Vector::Vector(float coords[])
   : x_(coords[0])
   , y_(coords[1])
   , z_(coords[2])
{
}

/**
 ******************************************************************************
 *
 *                   Add another vector to this one
 *
 ******************************************************************************
 */
Vector& Vector::operator += (const Vector& rhs)
{
   x_ += rhs.x_;
   y_ += rhs.y_;
   z_ += rhs.z_;

   return *this;
}

/**
 ******************************************************************************
 *
 *                   Add two vectors
 *
 ******************************************************************************
 */
Vector Vector::operator + (const Vector& rhs) const
{
   Vector result = *this;
   result += rhs;

   return result;
}

/**
 ******************************************************************************
 *
 *                   Subtract two vectors
 *
 ******************************************************************************
 */
Vector Vector::operator - (const Vector& rhs) const
{
   return Vector(x_ - rhs.x_, y_ - rhs.y_, z_ - rhs.z_);
}

/**
 ******************************************************************************
 *
 *                   Return the largest individual element
 *
 ******************************************************************************
 */
double Vector::largestElement() const
{
   return qMax(qMax(x_, y_), z_);
}

/**
 ******************************************************************************
 *
 *                   Cross product
 *
 ******************************************************************************
 */
Vector Vector::cross(const Vector& rhs) const
{
   const Vector& one = *this;
   const Vector& two = rhs;

   return Vector( (one.y_ * two.z_) - (two.y_ * one.z_),
                  (one.z_ * two.x_) - (two.z_ * one.x_),
                  (one.x_ * two.y_) - (two.x_ * one.y_) );
}

/**
 ******************************************************************************
 *
 *                   Dot product
 *
 ******************************************************************************
 */
double Vector::dot(const Vector& rhs) const
{
   return (x_*rhs.x_) + (y_*rhs.y_) + (z_*rhs.z_);
}

/**
 ******************************************************************************
 *
 *                   Return vector magnitude
 *
 ******************************************************************************
 */
double Vector::magnitude() const
{
   return sqrt(x_*x_ + y_*y_ + z_*z_);
}

/**
 ******************************************************************************
 *
 *                   Return a normalized vector (i.e. magnitude = 1)
 *
 ******************************************************************************
 */
Vector Vector::normalized() const
{
   double scale = magnitude();
   double x = x_ / scale;
   double y = y_ / scale;
   double z = z_ / scale;

   return Vector(x, y, z);
}

/**
 ******************************************************************************
 *
 *                   Multiply by a scalar
 *
 ******************************************************************************
 */
Vector operator*(const Vector& vector, double scalar)
{
   return Vector(vector.x() * scalar, vector.y() * scalar, vector.z() * scalar);
}
Vector operator*(double scalar, const Vector& vector)
{
   return Vector(vector.x() * scalar, vector.y() * scalar, vector.z() * scalar);
}

/**
 ******************************************************************************
 *
 *                   Divide by a scalar
 *
 ******************************************************************************
 */
Vector operator/(const Vector& vector, double scalar)
{
   return Vector(vector.x() / scalar, vector.y() / scalar, vector.z() / scalar);
}

/**
 ******************************************************************************
 *
 *                   Return a string representation (for debugging)
 *
 ******************************************************************************
 */
QString Vector::toString() const
{
   return QString::number(x_, 'f', 6) + " " + QString::number(y_, 'f', 6) + " " + QString::number(z_, 'f', 6);
}

/**
 ******************************************************************************
 *
 *                   Calculate the inverse of this vector
 *
 ******************************************************************************
 */
Vector Vector::inverse() const
{
   return Vector(1.0/x_, 1.0/y_, 1.0/z_);
}

/**
 ******************************************************************************
 *
 *                   Multiply element-wise
 *
 ******************************************************************************
 */
Vector Vector::multiplyElementsBy(const Vector& rhs) const
{
   return Vector(x_*rhs.x_, y_*rhs.y_, z_*rhs.z_);
}

/**
 ******************************************************************************
 *
 *                   Bound to a maximum magnitude
 *
 ******************************************************************************
 */
Vector Vector::boundedToMagnitude(double maxMagnitude) const
{
   double currentMagnitude = this->magnitude();
   if (currentMagnitude < maxMagnitude)
   {
      return *this;
   }

   double scale = currentMagnitude / maxMagnitude;
   return (*this) * (1.0/scale);
}

/**
 ******************************************************************************
 *
 *                   Calculate the distance between vectors
 *
 ******************************************************************************
 */
double Vector::distanceTo(const Vector rhs) const
{
   return (*this - rhs).magnitude();
}

/**
 ******************************************************************************
 *
 *                   Interpolate two vectors by a scaling factor
 *
 ******************************************************************************
 */
const Vector Vector::interpolate(Vector v1, Vector v2, double t)
{
   return (v1 * t) + (v2 * (1.0 - t));
}

/**
 ******************************************************************************
 *
 *                   Accessors
 *
 ******************************************************************************
 */
double Vector::x() const
{
   return x_;
}

double Vector::y() const
{
   return y_;
}

double Vector::z() const
{
   return z_;
}

/**
 ******************************************************************************
 *
 *                   Reflection
 *
 ******************************************************************************
 */
Vector Vector::reflected(const Vector normal) const
{
   return *this - ((2 * this->dot(normal)) * normal);
}
