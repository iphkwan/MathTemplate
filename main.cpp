#include <iostream>
#include <cstdio>
#include <string.h>
#include <cmath>
using namespace std;
#define INF 0x7ffffff7
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
        printf("a * x + b * y = %lld = %lld * %lld + %lld * %lld\n", a, a, x, b, y);
        return a;
    }
    LL d = extendGCD(b, a % b, x, y);
    LL t = x;
    x = y;
    y = t - a / b * y;
    printf("a = %lld, b = %lld, x = %lld, y = %lld\n", a, b, x, y);
    printf("a * x + b * y = %lld = %lld * %lld + %lld * %lld\n", d, a, x, b, y);
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

LL s1[123][123], s2[123][123];
/* Stirling1
* s(n, k) = 0 (k < 0 or n < k),
* s(n, n) = 1 (n >= 0)
* s(n, 0) = 0 (n >= 1)
* s(n, k) = s(n-1, k-1) - (n-1)*s(n-1, k), n >= 1, k >= 1
*/
LL S1(int n, int k) {
    if (s1[n][k] != -INF)
        return s1[n][k];
    LL res;
    if (k < 0 || n < k)
        res = 0;
    else if (n == k && n >= 0)
        res = 1;
    else if (k == 0 && n >= 1)
        res = 0;
    else
        res = S1(n-1, k-1) - (LL)(n - 1) * S1(n-1, k);
    s1[n][k] = res;
    printf("s(%d, %d) = %lld\n", n, k, res);
    return res;
}

/* Stirling2
* S(n, k) = 0 (k < 0 or n < k),
* S(n, n) = 1 (n >= 0)
* S(n, 0) = 0 (n >= 1)
* S(n, k) = S(n-1, k-1) + k * S(n-1, k), n >= 1, k >= 1
*/
LL S2(int n, int k) {
    if (s2[n][k] != -INF)
        return s2[n][k];
    LL res;
    if (k < 0 || n < k)
        res = 0;
    else if (n == k && n >= 0)
        res = 1;
    else if (k == 0 && n >= 1)
        res = 0;
    else
        res = S2(n-1, k-1) + (LL)k * S2(n-1, k);
    s2[n][k] = res;
    printf("s(%d, %d) = %lld\n", n, k, res);
    return res;
}

//calculate a^b mod n, n*n should not greater than long long
LL binaryFastMod(LL a, LL b, LL n) {
    a %= n;
    LL t = a, ans = 1;
    while(b) {
        if (b & 1) {
            ans = (ans * t) % n;
            //cout << "ans = " << ans << endl;
        }
        t = (t * t) % n;
        b >>= 1;
    }
    return ans;
}

int main() {
    printf("Hello MathTemplate!!!\n");
    /*LL b[3], w[3];
    for(int i = 0; i < 3; i++)
        cin >> b[i] >> w[i];
    CRT(b, w, 3);*/

    //cout << eular(91295) << endl;

    /*LL x, y;
    extendGCD(1387, -162, x, y);*/

    /*for (int i = 0; i < 123; i++)
        for (int j = 0; j < 123; j++)
            s1[i][j] = s2[i][j] = -INF;
    //cout << S1(6, 4) << endl;
    cout << S2(6, 4) << endl;*/

    cout << binaryFastMod(8, 1234, 13) << endl;
    return 0;
}
