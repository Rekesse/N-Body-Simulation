template<typename T>
struct Vector3D
{
    T x;
    T y;
    T z;

    Vector3D<T> operator+(const Vector3D<T>& rhs){
        return Vector3D<T>{
            .x = x + rhs.x,
            .y = y + rhs.y, 
            .z = z + rhs.z
        };
    }
};
