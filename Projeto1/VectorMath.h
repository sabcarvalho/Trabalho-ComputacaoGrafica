#ifndef VECTORMATH_H
#define VECTORMATH_H

struct Vector3 {
    double x, y, z;
};

Vector3 produtoVetorial(Vector3 u, Vector3 v);

Vector3 normalizar(Vector3 v);

#endif
