/**
 * Author: kobor
 * Date: 2024-04-12
 * License: CC0
 * Description: Computes the intersection points of 3 spheres.
 * Status: not tested
 */
#pragma once

#include "Point3D.h"

using P = Point3D<D>;
vector<P> trilaterate(P a, P b, P c, D p, D q, D r) {
	b = b - a, c = c - a;
	P e_x = b.unit(); D i = e_x.dot(c);
	P e_y = (c - e_x * i).unit(), e_z = e_x.cross(e_y);
	D d = b.dist(), j = e_y.dot(c);
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