/**
 * Author: Krzychuo
 * Date: 2025-02-18
 * License: CC0
 * Source: Original
 * Description: Container for segments [l,r], merges segments if intersecting
 * Time: O(\log N)
 * Status: stress-tested
 */
#pragma once

struct SegmentContainer : set<pii> {
    void upd(int l, int r, int add=1) {
        auto it = lower_bound(mp(l, -M));
        if (it != begin()) it = prev(it);
        if (it != end() && it->st < l-add) it = next(it); // remove add if (1,3),(4,6) != (1,6)
        while (it != end()){
            if (it->st > r+add) break; // remove add if (1,3),(4,6) != (1,6)
            pii p = *it;
            erase(it);
            if (add) {
                l = min(l, it->st);
                r = max(r, it->nd);
            }
            else {
                if (p.st <= l-1) emplace(p.st, l-1); 
                if (r+1 <= p.nd) emplace(r+1, p.nd);
            }
            it = upper_bound(p);
        }
        if (add) emplace(l,r);
    }
};
