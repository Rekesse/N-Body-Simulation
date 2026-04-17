#pragma once 



/*
struct Vector3D{
    double x;
    double y;
    double z;
};

struct Position
{
    Vector3D position;
};

struct Velocity
{
    Vector3D velocity;
};

struct Force
{
    Vector3D force;
};

struct Mass
{
    double m;
};

==== EXAMPLE INSIDE MAIN ====

struct Planet
{
    Mass m;
    Position p;
    Velocity v;
};

Planet terra = {
    // 1. Inizializzazione della massa
    .m = Mass{.m = 5.97}, 
    
    // 2. Inizializzazione della Posizione (che contiene un Vector3D)
    .p = Position{
        .position = Vector3D{
            .x = 149.6,  // Nota: si usa la virgola, non il punto e virgola
            .y = 0.0,
            .z = 0.0
        }
    },
    
    // 3. Inizializzazione della Velocità
    .v = Velocity{
        .velocity = Vector3D{
            .x = 0.0,
            .y = 29.78,
            .z = 0.0
        }
    }
};
*/

template<int m, int d, int t>
class Units{
    private:
    double m_value;
    public:
        explicit Units(double val = 0.0) : m_value(val){}

        double value() const {return m_value;}
        double& value() {return m_value;}

        Units<m,d,t>& operator+=(const Units<m,d,t> &rhs){
            /*
            Code written within a class’s methods has 
            unrestricted access to the private members of any instance belonging to that exact same class.
            */
            m_value += rhs.m_value;
            return *this;
        }

        Units<m,d,t>& operator*=(double rhs){
            m_value *= rhs;
            return *this;
        }
};

template<int m, int d, int t> 
const Units<m,d,t> operator+(const Units<m,d,t>& lhs, const Units<m,d,t>& rhs){
    // we cant modify lhs and rhs, so we create another temporary class with the same argument as lhs
    Units<m,d,t> result(lhs);
    // we can pass as an argument just lhs and not lhs.value() cause of Copy Constructor (?)
    return result += rhs;
}

template<int m, int d, int t>
const Units<m,d,t> operator*(const Units<m,d,t>& lhs, double rhs){
    Units<m,d,t> results(lhs);
    return results *= rhs;
}

template<int m, int d, int t>
const Units<m,d,t> operator*(double lhs, const Units<m,d,t>& rhs){
    Units<m,d,t> results(rhs);
    return results *= lhs;
}

template<int m1, int d1, int t1, int m2, int d2, int t2>
const Units<m1+m2,d1+d2,t1+t2> operator*(const Units<m1,d1,t1>& lhs, const Units<m2,d2,t2>& rhs){
    typedef Units<m1+m2,d1+d2,t1+t2> ResultType;
    // here im forced to use .value cause we are creatig a new Units
    return ResultType(lhs.m_value() * rhs.m_value());
}

template<int m1, int d1, int t1, int m2, int d2, int t2>
const Units<m1+m2,d1+d2,t1+t2> operator/(const Units<m1,d1,t1>& lhs, const Units<m2,d2,t2>& rhs){
    typedef Units<m1-m2,d1-d2,t1-t2> ResultType;
    // here im forced to use .value cause we are creatig a new Units
    return ResultType(lhs.m_value() / rhs.m_value());
}








