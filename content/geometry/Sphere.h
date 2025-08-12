/**
 * Author: Olaf Surgut
 * Date: 2025-07-29
 * License: CC0
 * Source: God
 * Description: Sphere primitives
 * Status: not tested
 */

#include "Point3D.h"

D sphericalDistance(D f1, D t1, D f2, D t2, D radius) {
	D dx = sin(t2)*cos(f2) - sin(t1)*cos(f1);
	D dy = sin(t2)*sin(f2) - sin(t1)*sin(f1);
	D dz = cos(t2) - cos(t1);
	D d = sqrt(dx*dx + dy*dy + dz*dz);
	return radius*2*asin(d/2);
}

vector<P> trilaterate(P a, P b, P c, D p, D q, D r) {
	b = b - a, c = c - a;
	P e_x = unit(b); D i = dot(e_x, c);
	P e_y = unit(c - e_x * i), e_z = det(e_x, e_y);
	D d = len(b), j = dot(e_y,c);
	D x = (p * p - q * q + d * d) / 2 / d;
	D y = (p * p - r * r - 2 * i * x + i * i + j * j) / 2 / j;
	D z2 = p * p - x * x - y * y;
	const D EPS = 1e-8;	// take care!
	if(z2 < -EPS) return {};
	D z = sqrt(fmax(z2, 0));
	P sol = a + e_x * x + e_y * y;
	if(z2 < EPS) return {sol};	
	return {sol - e_z * z, sol + e_z * z};
}