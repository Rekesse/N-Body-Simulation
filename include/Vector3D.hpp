template <typename T> struct Vector3D {
  T x;
  T y;
  T z;

  Vector3D<T> &operator+=(const Vector3D<T> &rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;

    return *this;
  }

  Vector3D<T> &operator-=(const Vector3D<T> &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;

    return *this;
  }
};

template <typename T>
const Vector3D<T> operator+(const Vector3D<T> &lhs, const Vector3D<T> &rhs) {
  Vector3D<T> result(lhs);

  return result += rhs;
}

template <typename T>
const Vector3D<T> operator-(const Vector3D<T> &lhs, const Vector3D<T> &rhs) {
  Vector3D<T> result(lhs);

  return result -= rhs;
}

template <typename T, typename U>
auto operator/(const Vector3D<T> &vec, const U &scalar) {
  // 1. We ask the compiler what type results when i divide T by U
  using ResultType = decltype(vec.x / scalar);

  return Vector3D<ResultType>{
      .x = vec.x / scalar, .y = vec.y / scalar, .z = vec.z / scalar};
}

template <typename T, typename U>
auto operator*(const Vector3D<T> &vec, const U &scalar) {
  using ResultType = decltype(vec.x * scalar);
  return Vector3D<ResultType>{
      .x = vec.x * scalar, .y = vec.y * scalar, .z = vec.z * scalar};
}

template <typename T1, typename T2>
auto dot_product(const Vector3D<T1> &lhs, const Vector3D<T2> &rhs) {
  return (lhs.x * rhs.x) + (lhs.y * rhs.y) + (lhs.z * rhs.z);
}

template <typename T1, typename T2>
auto cross_product(const Vector3D<T1> &lhs, const Vector3D<T2> &rhs) {
  using ResultType = decltype(lhs.x * rhs.x);

  return Vector3D<ResultType>{.x = (lhs.y * rhs.z) - (lhs.z * rhs.y),
                              .y = (lhs.z * rhs.x) - (lhs.x * rhs.z),
                              .z = (lhs.x * rhs.y) - (lhs.y * rhs.x)};
}

template <typename T> auto squared_norm(const Vector3D<T> &vec) {
  return (vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z);
}