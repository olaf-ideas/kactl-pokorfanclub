/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-11
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Circumcircle
 * Description:\\
\begin{minipage}{75mm}
The circumcirle of a triangle is the circle intersecting all three vertices. ccRadius returns the radius of the circle going through points A, B and C and ccCenter returns the center of the same circle.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-2mm}
\includegraphics[width=\textwidth]{content/geometry/circumcircle}
\end{minipage}
 * Status: tested
 */
#pragma once

#include "Point.h"

typedef Point<double> P;
double ccRadius(const P& A, const P& B, const P& C) {
	return (B-A).dist()*(C-B).dist()*(A-C).dist()/
			abs((B-A).cross(C-A))/2;
}
P ccCenter(const P& A, const P& B, const P& C) {
	P b = C-A, c = B-A;
	return A + (b*c.dist2()-c*b.dist2()).perp()/b.cross(c)/2;
}

Pt inCenter( Pt &A,  Pt &B,  Pt &C) {
	double a = norm(B-C), b = norm(C-A), c = norm(A-B);
	return (A * a + B * b + C * c) / (a + b + c);
}
Pt circumCenter( Pt &a,  Pt &b,  Pt &c) {
	Pt bb = b - a, cc = c - a;
	double db=norm2(bb), dc=norm2(cc), d=2*(bb ^ cc);
	return a-Pt(bb.Y*dc-cc.Y*db, cc.X*db-bb.X*dc) / d;
}
Pt othroCenter( Pt &a,  Pt &b,  Pt &c) {
	Pt ba = b - a, ca = c - a, bc = b - c;
	double Y = ba.Y * ca.Y * bc.Y,
	  A = ca.X * ba.Y - ba.X * ca.Y,
	  x0= (Y+ca.X*ba.Y*b.X-ba.X*ca.Y*c.X) / A,
	  y0= -ba.X * (x0 - c.X) / ba.Y + ca.Y;
	return Pt(x0, y0);
}