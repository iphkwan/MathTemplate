#include <iostream>
#include <cstdio>
#include <string.h>
#include <cmath>
using namespace std;

typedef long long LL;

//C(n, r)
LL com(LL n, LL r) {
    if (n - r > r)
        r = n - r;
    LL i, j, s = 1;
    for (i = 0, j = 1; i < r; ++i) {
        s *= (n - i);
        for ( ; j <= r && s % j == 0; ++j)
            s /= j;
    }
    return s;
}

LL gcd(LL a, LL b) {
    return (b == 0) ? a : gcd(b, a % b);
}

// calculate x, y, which gcd(a, b) = a * x + b * y
LL extendGCD(LL a, LL b, LL &x, LL &y) {
    if (b == 0) {
        x = 1, y = 0;
        printf("a = %lld, b = %lld, x = %lld, y = %lld\n", a, b, x, y);
        return a;
    }
    LL d = extendGCD(b, a % b, x, y);
    LL t = x;
    x = y;
    y = t - a / b * y;
    printf("a = %lld, b = %lld, x = %lld, y = %lld\n", a, b, x, y);
    return d;
}

/*
 * a = b[0](mod w[0]), ... , a = b[k-1](mod w[k-1]);
 * calculate a
 * Notice: gcd(w[i], w[j]) == 1, for all of i != j
 */
LL CRT(LL b[], LL w[], int k) {
    LL d, x, y, m, tmp, a = 0, n = 1;
    cout << "x = Ai(mod Ni)\n";
    for (int i = 0; i < k; i++) {
        n *= w[i];
        printf("x = %lld (mod %lld)\n", b[i], w[i]);
    }
    cout << "Total N = " << n << endl;
    cout << "Ci = t * N / Ni, t * (N / Ni) = 1(mod Ni)\n";
    cout << "ans = sum(Ai * Ci) % N\n";
    for (int i = 0; i < k; i++) {
        m = n / w[i];
        d = extendGCD(w[i], m, x, y);
        tmp = y * m;
        printf("t = %lld, C%d = %lld\n", y, i, tmp);
        a = (a + tmp * b[i]) % n;
    }
    if (a < 0)
        a += n;
    printf("ans = %lld\n", a);
    return a;
}

LL eular(LL x) {
    LL i, res = x;
    for (i = 2; i < (LL)sqrt(x * 1.0) + 1; i++)
        if (x % i == 0) {
            res = res / i * (i - 1);
            while (x % i == 0)
                x /= i;
        }
    if (x > 1)
        res = res / x * (x - 1);
    return res;
}

int main() {
    printf("Hello MathTemplate!!!\n");
    /*LL b[3], w[3];
    for(int i = 0; i < 3; i++)
        cin >> b[i] >> w[i];
    CRT(b, w, 3);*/
    cout << eular(997) << endl;
    return 0;
}
