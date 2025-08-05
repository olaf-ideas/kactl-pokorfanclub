/**
 * Author: Olaf Surgut
 * Date: 2025-07-13
 * License: CC0
 * Source: God
 * Description: Line primitives
 * Status: Tested of few tasks
 */
#pragma once

#include "Point.h"

P intersect(P a, P b, P c, P d) {
    return a+(b-a)*(det(c-a,d-c)/det(b-a,d-c)); }
D lineDist(P a, P b, P p) { return abs(det(a,b,p))/len(b-a); }
P project(P a, P b, P p) {
    return a+(b-a)*(dot(p-a,b-a)/dot(b-a,b-a)); }
P reflect(P a, P b, P p) { return project(a,b,p) * 2 - p; }