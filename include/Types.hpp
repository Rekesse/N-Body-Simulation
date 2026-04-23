#pragma once
#include <Units.hpp>
#include <Vector3D.hpp>

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

using Time = Units<0, 0, 1>;
using Mass = Units<1, 0, 0>;
using Distance = Units<0, 1, 0>;
using Speed = Units<0, 1, -1>;
using Acceleration = Units<0, 1, -2>;
using Force = Units<1, 1, -2>;
using GraviConst = Units<-1, 3, -2>;
using SquaredDistance = Units<0, 2, 0>;
using Position3D = Vector3D<Distance>;
using Velocity3D = Vector3D<Speed>;
using Acceleration3D = Vector3D<Acceleration>;
using VForce = Vector3D<Force>;
