#include <iostream>
using namespace std;

int inver_modulo(int a, int mod)
{
    a %= mod;
    for (int i = 1; i < mod; i++)
    {
        if ((a * i) % mod == 1)
        {
            return i;
        }
    }
}

int modulo(int a, int mod)
{
    if (a > 0)
        return a % mod;
    else if (a < 0)
        return mod + (a % mod);
    else
        return 0;
}

typedef struct point
{
    int x, y;
} point_t;

point_t doub(point_t p, int mod, int a)
{
    int s;
    point_t ans = {.x = 0, .y = 0};
    if (p.x == 0 && p.y == 0)
        return ans;
    else
    {
        s = modulo(modulo((3 * p.x * p.x) + a, mod) * inver_modulo(2 * p.y, mod), mod);
        cout << "del: " << s << endl;
        ans.x = modulo((s * s) - (2 * p.x), mod);
        ans.y = modulo((s * (p.x - ans.x)) - p.y, mod);
    }
    return ans;
}

point_t add(point_t p, point_t q, int mod, int a)
{
    int s;
    point_t ans = {.x = 0, .y = 0};
    if (p.x == 0 && p.y == 0)
        return q;
    else if (q.x == 0 && q.y == 0)
        return p;
    else if (p.x == q.x && p.y != q.y)
        return ans;
    else if (p.x == q.x && p.y == q.y)
        return doub(p, mod, a);
    else
    {
        s = modulo(modulo(q.y - p.y, mod) * inver_modulo(q.x - p.x, mod), mod);
        cout << "del: " << s << endl;
        ans.x = modulo((s * s) - p.x - q.x, mod);
        ans.y = modulo(s * (p.x - ans.x) - p.y, mod);
    }
    return ans;
}

// point_t multiply(point_t p,int scalar,int mod,int a)
// {
//     if(scalar==2)
//         return doub(p,mod,a);
//     return add(multiply(p,scalar-1,mod,a),p,mod);
// }
int main()
{
    int n, a, b, mod;
    cout << "ENter the Curve a,b and prime number:";
    cin >> a >> b >> mod;

    point p, q, ans;
    cout << "Enter the points to add:";
    cin >> p.x >> p.y >> q.x >> q.y;

    ans = add(p, q, mod, a);

    cout << "Addition is:(" << ans.x << "," << ans.y << ")\n";

    cout << "Enter the scalar quantity:";
    int scalar;
    cin >> scalar;
    // ans=multiply(p,scalar,mod,a);
    ans = p;
    cout << ans.x << " " << ans.y << endl;
    for (int i = 0; i < scalar - 1; i++)
    {
        ans = add(ans, p, mod, a);
        cout << "(" << ans.x << "," << ans.y << ")\n";
    }
    cout << "Multiplication is:(" << ans.x << "," << ans.y << ")\n";
}