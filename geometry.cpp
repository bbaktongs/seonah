// -- utilities
int sgn(ll x){ return (x > 0) - (x < 0); }
const int quad[3][3] = {
                //     |
    {4, 3, 2},  //   4-3-2
    {5, 0, 1},  // --5-+-1--
    {6, 7, 8}   //   6-7-8
                //     |
};

// -- point
struct pt{ 
    ll x, y, q;
    pt() { x = 0, y = 0; q = 0; }
    pt(ll px, ll py) { x = px; y = py; q = quad[1-sgn(y)][1+sgn(x)]; }
}; const pt O = {0, 0};

// -- point functions
ll hypot(pt p) { return p.x*p.x + p.y*p.y; }
ll distsq(pt p1, pt p2) { return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y); }
int ccw(pt p1, pt p2, pt p3){
    ll c1 = p1.x*p2.y + p2.x*p3.y + p3.x*p1.y;
    ll c2 = p1.y*p2.x + p2.y*p3.x + p3.y*p1.x;
    return sgn(c1 - c2);
}
pt turn180(pt p) { return pt(-p.x, -p.y); };
// -- point operators
pt operator + (pt l, pt r){ return pt(l.x + r.x, l.y + r.y); }
pt operator - (pt l, pt r){ return pt(l.x - r.x, l.y - r.y); }
ll operator * (pt l, pt r){ return (ll)l.x * r.x + (ll)l.y * r.y; }
ll operator / (pt l, pt r){ return (ll)l.x * r.y - (ll)l.y * r.y; } // ccw of two points
bool operator < (pt l, pt r) { return make_pair(l.x, l.y) < make_pair(r.x, r.y); }
bool operator > (pt l, pt r) { return make_pair(l.x, l.y) > make_pair(r.x, r.y); }
bool operator <= (pt l, pt r) { return make_pair(l.x, l.y) <= make_pair(r.x, r.y); }
bool operator >= (pt l, pt r) { return make_pair(l.x, l.y) >= make_pair(r.x, r.y); }
bool operator == (pt l, pt r) { return make_pair(l.x, l.y) == make_pair(r.x, r.y); }
bool operator != (pt l, pt r) { return make_pair(l.x, l.y) != make_pair(r.x, r.y); }

// -- line segment
struct line{
    pt p1, p2; 
    ll a, b, c;
    line(pt a, pt b) { p1 = a; p2 = b; }
    line(ll v1, ll v2, ll v3) { a = v1, b = v2, c = v3; }
};

// -- line segment functions
int ccw(line l1, line l2){
    pt p1 = l1.p1, p2 = l1.p2, p3 = l2.p2-l1.p2;
    return ccw(p1, p2, p3);
}
ll lensq(line l){
    return distsq(l.p1, l.p2);
}
int intersect(line l1, line l2){
    // 0 = no intersection | 1 = mid-line
    // 2 = endpoint | 3 = infinitely many
    pt p1 = l1.p1, p2 = l1.p2, p3 = l2.p1, p4 = l2.p2;
    int c123 = ccw(p1, p2, p3), c124 = ccw(p1, p2, p4);
    int c341 = ccw(p3, p4, p1), c342 = ccw(p3, p4, p2);
    if (c123 == 0 && c124 == 0){
        if (p1 > p2){ swap(p1, p2); } if (p3 > p4){ swap(p3, p4); }
        if (p2 < p3 || p4 < p1){ return 0; }
        if (p2 == p3 || p4 == p1){ return 2; }
        return 3;
    }
    int c12 = c123*c124, c34 = c341*c342;
    if (c12 > 0 || c34 > 0){ return 0; }
    if (c12 == 0 || c34 == 0){ return 2; }
    return 1;
}
bool point_on_line(pt p, line l, bool constrain){
    return ccw(l.p1, p, l.p2) == 0
    && (constrain ? min(l.p1, l.p2) <= p && p <= max(l.p1, l.p2) : 1);
}

// -- -- algorithms -- --
// -- polarsort (credits to:cgiosy)
void polarsort( vector<pt>&P, int N ) { // min y, ccw, respect to origin
    auto m=partition(P.begin(), P.begin()+N, [&](pt p) { return p < O; });
    sort(P.begin(), m, [&](pt a, pt b) { return ccw(O, a, b)<0; });
    sort(m, P.begin()+N, [&](pt a, pt b) { return ccw(O, a, b)<0; });
}
// -- polarsort / respect to min point / ccw, cw is boolean / I'm not sure if this actually is polar sort
void ccwsort( vector<pt>&P, pt p0, bool counter ) {
    sort(P.begin(), P.end(), [&p0, &counter](const pt& p1, const pt& p2) {
        int dir = ccw(p0, p1, p2);
        if (dir == 0)
            return distsq(p0, p1) < distsq(p0, p2);
        return (counter ? dir > 0 : dir < 0);
    });
}
// -- convex hull // min x, min y, coillinear = include collinear, ccw = counter
vector<pt> convex_hull(vector<pt>&P, int N, bool collinear, bool counter) { 
    pt p0 = *min_element(P.begin(), P.end(), [](pt p1, pt p2) {
        return make_pair(p1.x, p1.y) < make_pair(p2.x, p2.y);
    });
    ccwsort(P, p0, counter);

    if (collinear) {
        int i = N - 1;
        while (i >= 0 && !ccw(p0, P[i], P.back())) i--;
        reverse(P.begin()+i+1, P.end());
    }

    vector<pt>ret;
    for (int i = 0; i < N; i++) {
        while (ret.size() >= 2) {
            int dir = ccw(ret[ret.size()-2], ret.back(), P[i]);
            if(!(dir == 1 || (collinear && dir == 0))) ret.pop_back();
            else break;
        }
        ret.push_back(P[i]);
    }
    if (!collinear && ret.size() == 2 && ret[0] == ret[1]) ret.pop_back();
    return ret;
}
// -- point in convex polygon // 0 = outside, 1 = inside, 2 = on line
int inside_convex(vector<pt>&P, int N, pt p){
    int st = 1, ed = N - 1; while(st+1 <= ed-1){
        int mid = (st + ed)/2;
        if(ccw(P[0], P[mid], p) == 1){
            st = mid;
        }
        else ed = mid;
    } pt p1 = P[0], p2 = P[st], p3 = P[st+1];
    int r12 = ccw(p1, p2, p), r23 = ccw(p2, p3, p), r31 = ccw(p3, p1, p);
    if(r12 < 0 || r23 < 0 || r31 < 0) return 0;
    else{
        if(r23 == 0 || r12 == 0 && st == 1 || r31 == 0 && st == N-2){
            return 2;
        }
        else return 1;
    }
}
// -- rotating calipers -- (maxdistsq)
ll calipers(vector<pt>&P, int N){
    int j = 0; ll ret = 0;
    for (int i = 0; i < N; i++){
        while (j < N){
            int ip = (i+1) % N, jp = (j+1) % N;
            pt l = P[ip] - P[i]; pt r = P[jp] - P[j];
            if (ccw(O, l, r) < 0){ break; }
            ret = max(ret, distsq(P[i], P[j])); j += 1;
        } if (j < N){ ret = max(ret, distsq(P[i], P[j])); }
    }
    return ret;
}
