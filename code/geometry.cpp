#include <bits/stdc++.h>
using namespace std;
#define ALL(x) x.begin(), x.end()
#define rep(i, n) for (int i = 0; i < (n); i++)
#define debug(v)          \
    cout << #v << ":";    \
    for (auto x : v)      \
    {                     \
        cout << x << ' '; \
    }                     \
    cout << endl;
#define INF 1000000000
#define mod 1000000007
using ll = long long;
const ll LINF = 1001002003004005006ll;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
// ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
template <class T>
bool chmax(T &a, const T &b)
{
    if (a < b)
    {
        a = b;
        return true;
    }
    return false;
}
template <class T>
bool chmin(T &a, const T &b)
{
    if (b < a)
    {
        a = b;
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////
using Real = double;
using Point = complex<Real>;
const Real EPS = 1e-10;
const Real pi = acosl(-1);
//入出力補助
istream &operator>>(istream &is, Point &p)
{
    Real a, b;
    is >> a >> b;
    p = Point(a, b);
    return is;
}
ostream &operator<<(ostream &os, Point &p)
{
    return os << fixed << setprecision(12) << p.real() << ' ' << p.imag();
}

inline bool eq(Real a, Real b)
{
    return fabs(a - b) < EPS;
}
Point operator*(const Point &p, const Real &d)
{
    return Point(real(p) * d, imag(p) * d);
}
struct Line
{
    Point p1, p2;
    Line() = default;
    Line(Point p1, Point p2) : p1(p1), p2(p2) {}

    //Ax + By = C
    Line(Real A, Real B, Real C)
    {
        if (eq(A, 0))
            p1 = Point(0, C / B), p2 = Point(1, C / B);
        else if (eq(B, 0))
            p1 = Point(C / A, 0), p2 = Point(C / A, 1);
        else
            p1 = Point(0, C / B), p2 = Point(C / A, 0);
    }
};
struct Segment : Line
{
    Segment() = default;
    Segment(Point p1, Point p2) : Line(p1, p2) {}
};
struct Circle
{
    Point center;
    Real r;
    Circle() = default;
    Circle(Point center, Real r) : center(center), r(r) {}
};
/////////////////////////////////////////////////////////

// 点 p を反時計回りに theta 回転
Point rotate(Real theta, const Point &p)
{
    return Point(cos(theta) * p.real() - sin(theta) * p.imag(), sin(theta) * p.real() + cos(theta) * p.imag());
}

Real radian_to_degree(Real r)
{
    return r * 180.0 / pi;
}

Real degree_to_radian(Real d)
{
    return d * pi / 180.0;
}

//三角形の面積，サラスの公式
Real area_triangle(Point a, Point b, Point c)
{
    Point x = b - a, y = c - a;
    return fabs(x.real() * y.imag() - x.imag() * y.real()) / 2;
}

//v
//外積
Real cross(Point a, Point b)
{
    return real(a) * imag(b) - imag(a) * real(b);
}
//v
//内積
Real dot(Point a, Point b)
{
    return real(a) * real(b) + imag(a) * imag(b);
}

//v
//平行判定，外積0かをみる
bool parallel(Line a, Line b)
{
    return eq(cross(a.p1 - a.p2, b.p1 - b.p2), 0.0);
}
//v
//垂直判定，内積0かをみる
bool orthogonal(Line a, Line b)
{
    return eq(dot(a.p1 - a.p2, b.p1 - b.p2), 0.0);
}

//v
//正射影，pからlに下した垂線の足を求める
Point projection(Line l, Point p)
{
    //ベクトルl上のどの位置に垂線の足が来るか求める
    Real k = dot(l.p1 - l.p2, p - l.p1) / norm(l.p1 - l.p2);
    return l.p1 + (l.p1 - l.p2) * k;
}
Point projection(Segment l, Point p)
{
    Real k = dot(l.p1 - l.p2, p - l.p1) / norm(l.p1 - l.p2);
    return l.p1 + (l.p1 - l.p2) * k;
}

//v
//反射，直線lに関し点pと線対称な点を返す
Point reflection(Line l, Point p)
{
    Point h = projection(l, p);
    return (p + (h - p) + (h - p));
}
Point reflection(Segment l, Point p)
{
    Point h = projection(l, p);
    return (p + (h - p) + (h - p));
}

//二点間の距離
Real dis(Point a, Point b)
{
    return abs(a - b);
}
//点と直線の距離
Real dis(Line l, Point p)
{
    return abs(p - projection(l, p));
}

//v
//COUNTER CLOCKWISE，返す値は↓を参照
//https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/all/CGL_1_C
int ccw(Point a, Point b, Point c)
{
    b -= a;
    c -= a;
    if (cross(b, c) > EPS)
        return 1; //COUNTER CLOCKWISE
    else if (cross(b, c) < -EPS)
        return -1; //CLOCKWISE
    else if (dot(b, c) < 0)
        return 2; //c--a--b ONLINE BACK
    else if (norm(b) < norm(c))
        return -2; //a--b--c ONLINE FRONT
    else
        return 0; //a--c--b ON SEGMENT
}

//v
//3点が作る三角形の外心
//面積0の三角形を渡すと分母に面積があるので壊れるかも
Point circumcenter(Point A, Point B, Point C)
{
    Real S = area_triangle(A, B, C);
    Real a = dis(B, C), b = dis(A, C), c = dis(A, B);
    return A * (a * a * (b * b + c * c - a * a) / (16 * S * S)) + B * (b * b * (c * c + a * a - b * b) / (16 * S * S)) + C * (c * c * (a * a + b * b - c * c) / (16 * S * S));
}

//交差判定
//直線状に乗るか
bool intersect(Line l, Point p)
{
    return abs(ccw(l.p1, l.p2, p)) != 1;
}
//直線の交差判定，外積
bool intersect(Line l1, Line l2)
{
    return abs(cross(l1.p2 - l1.p1, l2.p2 - l2.p1)) > EPS or
           abs(cross(l1.p2 - l1.p1, l2.p2 - l1.p1)) < EPS;
}
//線分に点が乗るかの判定，ccw
bool intersect(Segment s, Point p)
{
    return ccw(s.p1, s.p2, p) == 0;
}
//直線と線分の交差判定
bool intersect(Line l, Segment s)
{
    return cross(l.p2 - l.p1, s.p1 - l.p1) * cross(l.p2 - l.p1, s.p2 - l.p1) < EPS;
}
//円と直線の交差判定
bool intersect(Circle c, Line l)
{
    return dis(l, c.center) <= c.r + EPS;
}
//円上かどうか，内部かどうかではない
bool intersect(Circle c, Point p)
{
    return abs(abs(p - c.center) - c.r) < EPS;
}
//v
//線分と線分の交差判定
bool intersect(Segment s, Segment t)
{
    return ccw(s.p1, s.p2, t.p1) * ccw(s.p1, s.p2, t.p2) <= 0 and
           ccw(t.p1, t.p2, s.p1) * ccw(t.p1, t.p2, s.p2) <= 0;
}
//線分と円の交差判定，交点の個数を返す
int intersect(Circle c, Segment l)
{
    Point h = projection(l, c.center);
    //直線まるっと円の外側
    if (norm(h - c.center) - c.r * c.r > EPS)
        return 0;
    Real d1 = abs(c.center - l.p1), d2 = abs(c.center - l.p2);
    //線分が円内
    if (d1 < c.r + EPS and d2 < c.r + EPS)
        return 0;
    if ((d1 < c.r - EPS and d2 > c.r + EPS) or (d2 < c.r - EPS and d1 > c.r + EPS))
        return 1;
    //円の外部にまるまるはみ出ていないか
    if (dot(l.p1 - h, l.p2 - h) < 0)
        return 2;
    return 0;
}
//円と円の位置関係，共通接線の個数を返す
int intersect(Circle c1, Circle c2)
{
    if (c1.r < c2.r)
        swap(c1, c2);
    Real d = abs(c1.center - c2.center);
    //2円が離れている
    if (c1.r + c2.r < d)
        return 4;
    //2円が外接する
    if (eq(c1.r + c2.r, d))
        return 3;
    //2円が交わる
    if (c1.r - c2.r < d)
        return 2;
    //円が内接する
    if (eq(c1.r - c2.r, d))
        return 1;
    //内包
    return 0;
}

//交点
//線分の交点はintersectをチェックしてokなら直線の交点をやる
//intersectをチェックすること
//v
Point crosspoint(Line l, Line m)
{
    Real A = cross(m.p2 - m.p1, m.p1 - l.p1);
    Real B = cross(m.p2 - m.p1, l.p2 - l.p1);
    if (eq(A, 0) and eq(B, 0))
        return l.p1;
    if (eq(B, 0))
        throw "NAI";
    return l.p1 + A / B * (l.p2 - l.p1);
}
Point crosspoint(Segment l, Segment m)
{
    return crosspoint(Line(l), Line(m));
}
vector<Point> crosspoint(Circle c, Line l)
{
    vector<Point> ret;
    Point h = projection(l, c.center);
    Real d = sqrt(c.r * c.r - norm(h - c.center));
    Point e = (l.p2 - l.p1) * (1 / abs(l.p2 - l.p1));
    if (c.r * c.r + EPS < norm(h - c.center))
        return ret;
    if (eq(dis(l, c.center), c.r))
    {
        ret.push_back(h);
        return ret;
    }
    ret.push_back(h + e * d);
    ret.push_back(h - e * d);
    return ret;
}
//要verify，
vector<Point> crosspoint(Circle c, Segment s)
{
    Line l = Line(s.p1, s.p2);
    int ko = intersect(c, s);
    if (ko == 2)
        return crosspoint(c, l);
    vector<Point> ret;
    if (ko == 0)
        return ret;
    ret = crosspoint(c, l);
    if (ret.size() == 1)
        return ret;
    vector<Point> rret;
    //交点で挟める方を返す
    if (dot(s.p1 - ret[0], s.p2 - ret[0]) < 0)
        rret.push_back(ret[0]);
    else
        rret.push_back(ret[1]);
    return rret;
}
//v
vector<Point> crosspoint(Circle c1, Circle c2)
{
    vector<Point> ret;
    int isec = intersect(c1, c2);
    if (isec == 0 or isec == 4)
        return ret;
    Real d = abs(c1.center - c2.center);
    Real a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    Real t = atan2(c2.center.imag() - c1.center.imag(), c2.center.real() - c1.center.real());
    ret.push_back(c1.center + Point(cos(t + a) * c1.r, sin(t + a) * c1.r));
    ret.push_back(c1.center + Point(cos(t - a) * c1.r, sin(t - a) * c1.r));
    return ret;
}

//v
//点pから引いた円cの接線の接点を返す
vector<Point> tangent(Circle c, Point p)
{
    return crosspoint(c, Circle(p, sqrt(norm(c.center - p) - c.r * c.r)));
}
//v
//二円の共通接線，Lineの2点は接点を表す
vector<Line> tangent(Circle c1, Circle c2)
{
    vector<Line> ret;
    if (c1.r < c2.r)
        swap(c1, c2);
    Real g = norm(c1.center - c2.center);
    //中心が一致するならない
    if (eq(g, 0))
        return ret;
    Point u = (c2.center - c1.center) / sqrt(g);
    Point v = rotate(pi * 0.5, u);
    for (int s : {-1, 1})
    {
        Real h = (c1.r + s * c2.r) / sqrt(g);
        if (eq(1 - h * h, 0))
        {
            ret.push_back(Line(c1.center + u * c1.r, c1.center + (u + v) * c1.r));
        }
        else if (1 - h * h > 0)
        {
            Point uu = u * h, vv = v * sqrt(1 - h * h);
            ret.push_back(Line(c1.center + (uu + vv) * c1.r, c2.center - (uu + vv) * c2.r * s));
            ret.push_back(Line(c1.center + (uu - vv) * c1.r, c2.center - (uu - vv) * c2.r * s));
        }
    }
    return ret;
}

//v
//最小包含円を返す　計算量は期待値O(n)
Circle MinimumBoundingCircle(vector<Point> v)
{
    int n = v.size();

    //ランダムシャッフル．いぢわるされたくないもんだ
    mt19937 mt(time(0));
    shuffle(v.begin(), v.end(), mt);
    Circle ret(0, 0);
    //2点で円を作る
    auto make_circle2 = [&](Point a, Point b) {
        return Circle((a + b) * 0.5, dis(a, b) / 2);
    };
    //3点で円を作る
    auto make_circle3 = [&](Point A, Point B, Point C) {
        Point cent = circumcenter(A, B, C);
        return Circle(cent, dis(cent, A));
    };
    auto isIn = [&](Point a) {
        return dis(ret.center, a) < ret.r + EPS;
    };

    ret = make_circle2(v[0], v[1]);
    for (int i = 2; i < n; i++)
    {
        //v[i]が円に入っていないなら
        if (!isIn(v[i]))
        {
            //円内にないなら点v[i]は必ず円周上に来る
            ret = make_circle2(v[0], v[i]);
            for (int j = 1; j < i; j++)
            {
                if (!isIn(v[j]))
                {
                    //この時iとjが円周上を考える
                    ret = make_circle2(v[i], v[j]);
                    //最後の1点の決定
                    for (int k = 0; k < j; k++)
                    {
                        if (!isIn(v[k]))
                        {
                            ret = make_circle3(v[i], v[j], v[k]);
                        }
                    }
                }
            }
        }
    }
    return ret;
}
//ABC022Big Bang
Real closest_pair(vector<Point> ps)
{
    sort(ALL(ps), [&](Point a, Point b) {
        return real(a) < real(b);
    });

    function<Real(int, int)> rec = [&](int l, int r) {
        if (r - l <= 1)
            return 1e18;
        int m = (l + r) / 2;
        Real x = real(ps[m]);
        Real ret = min(rec(l, m), rec(m, r));
        inplace_merge(begin(ps) + l, begin(ps) + m, begin(ps) + r, [&](Point a, Point b) {
            return imag(a) < imag(b);
        });
        // 分割を跨いで最小距離があるか調べる
        vector<Point> b;
        for (int i = l; i < r; i++)
        {
            if (abs(real(ps[i]) - x) >= ret)
                continue;
            for (int j = (int)b.size() - 1; j >= 0; j--)
            {
                if (abs(imag(ps[i] - b[j])) >= ret)
                    break;
                ret = min(ret, abs(ps[i] - b[j]));
            }
            b.push_back(ps[i]);
        }
        return ret;
    };
    return rec(0, (int)ps.size());
}

//垂直二等分線
Line getPerpendicularBisector(Point a, Point b)
{
    double cx = (a.real() + b.real()) / 2.0;
    double cy = (a.imag() + b.imag()) / 2.0;
    Point p = Point(cx + (a.imag() - b.imag()), cy + (b.real() - a.real()));
    return Line(Point(cx, cy), p);
}

//多角形の面積
double area_of_polygons(vector<Point> v)
{
    double res = 0;
    int n = v.size();
    rep(i, n)
    {
        int idx = i;
        int idx2 = (i + 1) % n;
        res += 0.5 * (v[idx2].real() - v[idx].real()) * (v[idx2].imag() + v[idx].imag());
    }
    return res;
}
/*
幾何メモ
atan(y):y=tan(x)となるxを計算
atan2(x,y):(x,y)の偏角
*/
signed main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);

    cout << fixed << setprecision(12);

    Real a, b, h, m;
    cin >> a >> b >> h >> m;

    Real ra = 2 * pi * (60 * h + m) / 720.0;
    Real rb = 2 * pi * m / 60.0;

    double xa = a * cos(ra), ya = a * sin(ra);
    double xb = b * cos(rb), yb = b * sin(rb);

    cout << sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb)) << endl;

    return 0;
}
