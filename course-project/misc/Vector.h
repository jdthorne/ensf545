
#ifndef VECTOR_H
#define VECTOR_H

#include <QString>

/**
 ******************************************************************************
 *
 *                   Vector
 *
 *  This class represents a 3-Vector.  It encapsulates the x, y, z positions,
 *  and contains tons of useful helpers.
 *
 ******************************************************************************
 */
class Vector
{

public:
   Vector();
   Vector(double x, double y, double z);
   Vector(float coords[]);

public: // Accessors
   double x() const;
   double y() const;
   double z() const;

public: // Operators
   Vector& operator+= (const Vector& rhs);
   Vector operator+ (const Vector& rhs) const;
   Vector operator- (const Vector& rhs) const;

   double largestElement() const;

   Vector cross(const Vector& rhs) const;
   double dot(const Vector& rhs) const;

   void normalize();

   Vector inverse() const;
   Vector normalized() const;

   Vector reflected(const Vector normal) const;

   Vector multiplyElementsBy(const Vector& rhs) const;

   QString toString() const;

   Vector boundedToMagnitude(double maxMagnitude) const;

   double magnitude() const;
   double distanceTo(const Vector rhs) const;

   static const Vector interpolate(Vector v1, Vector v2, double t);

private:
   double x_;
   double y_;
   double z_;
};

#define printVec(vec) qPrintable(vec.toString())

Vector operator*(const Vector& vector, double scalar);
Vector operator*(double scalar, const Vector& vector);
Vector operator/(const Vector& vector, double scalar);

#endif
