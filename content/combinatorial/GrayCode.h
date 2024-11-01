/**
 * Author: UJ Lib
 * Description: Gray code: $\text{gray}(0),\dots, \text{gray}(2^n-1)$ - permutation
 * in which each two consecutive (cyclically) numbers.
 * differ in exactly one bit.
 * Status: Stress-tested
 */
#pragma once

using ull = unsigned long long;
ull gray(ull i) { return i^i>>1; }
ull invg(ull i) { // i=invg(gray(i))=gray(invg(i))
	i^=i>>1; i^=i>>2; i^=i>>4;
	i^=i>>8; i^=i>>16; i^=i>>32; return i;
}
