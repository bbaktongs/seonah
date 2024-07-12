struct Line{
    ll m, c;
    ld stx = 0.0;
    bool operator<(Line l) const { return stx < l.stx; }
};

ld cx(Line l1,Line l2) {
    return (ld)(1.0) * (ld)(l2.c-l1.c)/(l1.m-l2.m);
}

vector<Line>li;

// https://www.acmicpc.net/source/75555998
