#pragma once 

// NOT GOOD

// struct CoordX{
//     double value;
//     explicit CoordX(double x) : value(x) {};
// };

// struct CoordY{
//     double value;
//     explicit CoordY(double y) : value(y) {};
// };

// struct CoordZ{
//     double value;
//     explicit CoordZ(double z) : value(z) {};
// };

// struct Vector3D
// {
//     CoordX x;
//     CoordY y;
//     CoordZ z;
// };

// struct Mass
// {
//     double value;
//     explicit Mass(double m) : value(m) {};
// };

/*

inside main:

Vector3D p1 = {
    .x = CoordX(2.3)
    eccetera
}

*/

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
    double value
    public:
        explicit Units(double val = 0.0) : value(val){}

        double value() const {return value}

        Units<m,d,t>& operator+=(const Units<m,d,t> &rhs){
            value += rhs.value;
            return *this;
        }

        Units<m,d,t>& operator*=(double rhs){
            value *= rh
        }
};











