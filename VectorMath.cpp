#include "VectorMath.h"
#include <math.h>

Vector3 produtoVetorial(Vector3 u, Vector3 v){
    Vector3 resultado {
        (double) u.y*v.z - u.z*v.y,
        (double) u.z*v.x - u.x*v.z,
        (double) u.x*v.y - u.y*v.x
    };
    return resultado;
}

Vector3 normalizar(Vector3 v) {
    float norma = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (norma > 0.0f) {
        Vector3 resultado{
            v.x / norma,
            v.y / norma,
            v.z / norma
        };
        return resultado;
    }
    return v;
}