#pragma once

template <int m, int d, int t> class Units {
private:
  double m_value;

public:
  explicit Units(double val = 0.0) : m_value(val) {}

  double value() const { return m_value; }
  double &value() { return m_value; }

  Units<m, d, t> &operator+=(const Units<m, d, t> &rhs) {
    /*
    Code written within a class’s methods has
    unrestricted access to the private members of any instance belonging to that
    exact same class.
    */
    m_value += rhs.m_value;
    return *this;
  }

  Units<m, d, t> &operator-=(const Units<m, d, t> &rhs) {
    m_value -= rhs.m_value;
    return *this;
  }

  Units<m, d, t> &operator*=(double rhs) {
    m_value *= rhs;
    return *this;
  }
};

template <int m, int d, int t>
const Units<m, d, t> operator+(const Units<m, d, t> &lhs,
                               const Units<m, d, t> &rhs) {
  // we cant modify lhs and rhs, so we create another temporary class with the
  // same argument as lhs
  Units<m, d, t> result(lhs);
  // we can pass as an argument just lhs and not lhs.value() cause of Copy
  // Constructor (?)
  return result += rhs;
}

template <int m, int d, int t>
const Units<m, d, t> operator-(const Units<m, d, t> &lhs,
                               const Units<m, d, t> &rhs) {
  // we cant modify lhs and rhs, so we create another temporary class with the
  // same argument as lhs
  Units<m, d, t> result(lhs);
  // we can pass as an argument just lhs and not lhs.value() cause of Copy
  // Constructor (?)
  return result -= rhs;
}

template <int m, int d, int t>
Units<m, d, t> operator*(const Units<m, d, t> &lhs, double rhs) {
  Units<m, d, t> results(lhs);
  return results *= rhs;
}

template <int m, int d, int t>
Units<m, d, t> operator*(double lhs, const Units<m, d, t> &rhs) {
  Units<m, d, t> results(rhs);
  return results *= lhs;
}

template <int m1, int d1, int t1, int m2, int d2, int t2>
Units<m1 + m2, d1 + d2, t1 + t2> operator*(const Units<m1, d1, t1> &lhs,
                                           const Units<m2, d2, t2> &rhs) {
  typedef Units<m1 + m2, d1 + d2, t1 + t2> ResultType;
  // here im forced to use .value cause we are creatig a new Units
  return ResultType(lhs.value() * rhs.value());
}

template <int m1, int d1, int t1, int m2, int d2, int t2>
Units<m1 - m2, d1 - d2, t1 - t2> operator/(const Units<m1, d1, t1> &lhs,
                                           const Units<m2, d2, t2> &rhs) {
  typedef Units<m1 - m2, d1 - d2, t1 - t2> ResultType;
  // here im forced to use .value cause we are creatig a new Units
  return ResultType(lhs.value() / rhs.value());
}

/*
===========================================================================
WHY I REMOVED 'const' FROM THE RETURN TYPES OF UNITS OPERATORS
===========================================================================

THE BUG IN OUR CODE:
1. In `Units.hpp`, i originally had:
   template <...>
   const Units<...> operator*(const Units<...>& lhs, double rhs);

2. In `Vector3D.hpp`, i multiply a Vector by a scalar using `decltype`:
   using ResultType = decltype(vec.x * scalar);
   // vec.x is 'Distance', scalar is 'double'

3. WHAT WENT WRONG:
   Because the operator in `Units.hpp` explicitly returned a `const Units`,
   `decltype` faithfully captured that exact type.
   Instead of deducing `ResultType` as `Force` (a modifiable unit),
   it deduced it as `const Force`.

4. THE COMPILATION ERROR ("No viable overloaded '='"):
   When i evaluated `Ftot / d` (Force divided by Distance), it returned
   a `const` scalar.
   When i multiplied the vector `delta_pos` by this scalar, `decltype`
   made the resulting vector's components `const`.
   Finally, i tried to assign this result to a normal, modifiable
   variable: `force = ...`
   The compiler stopped us: you cannot assign a Vector made of
   `const` components to a Vector made of modifiable components.

THE FIX:
By removing the `const` from the return type in `Units.hpp`, `decltype`
now deduces a clean, non-const `Units` object. This allows normal
variable assignments and enables the compiler to use efficient move
constructors under the hood.
*/
