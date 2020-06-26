#include<iostream>
#include<time.h>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAX = 100000000;

int N = 0;
int minFactor[MAX];
void SoE() {
    minFactor[0] = minFactor[1] = -1;
    for (int i = 2; i <= N; i++)
        minFactor[i] = i;
    //에라토스테네스의 체를 수행
    int sqrtN = int(sqrt(N));
    for (int i = 2; i <= sqrtN; i++) {
        if (minFactor[i] == i) {
            for (int j = i * i; j <= N; j += i) {
                if (minFactor[j] == j) {
                    minFactor[j] = i;
                }
            }
        }
    }
}

//소인수분해
vector<int> factor() {
    vector<int> result;
    int copy = N;
    while (copy > 1) {
        result.push_back(minFactor[copy]);
        copy /= minFactor[copy];
    }
    return result;
}

int p = 0;
int q = 0;
int i = 0;
int n = 0;
int t = 0;
int flag = 0;
int e[100], d[100], temp[100], m[100], en[100];
char message[100];

// Well Random Number Generator 
// F. Panneton, P. L'Ecuyer and M. Matsumoto, "Improved Long-Period Generators Based on Linear Recurrences Modulo 2", submitted to ACM TOMS.
namespace WELL512 {
    unsigned long state[16];
    unsigned int index = 0;

    void init(unsigned long seed) {
        for (int i = 0; i < 16; ++i) {
            state[i] = seed;
        }
    }

    unsigned long WELL512GN() {
        unsigned long a, b, c, d;
        a = state[index];
        c = state[(index + 13) & 15];
        b = a ^ c ^ (a << 16) ^ (c << 15);
        c = state[(index + 9) & 15];
        c ^= (c >> 11);
        a = state[index] = b ^ c;
        d = a ^ ((a << 5) & 0xDA442D20UL);
        index = (index + 15) & 15;
        a = state[index];
        state[index] = a ^ b ^ d ^ (a << 2) ^ (b << 18) ^ (c << 28);
        return state[index];
    }

    int segment(int start, int end) {
        return int(WELL512GN() % end) + start;
    }
}

// 소수 판별
bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if ((n % i) == 0) {
            return false;
        }
    }
    return true;
}

int cd(int x) {
    int k = 1;
    while(1) {
        k = k + t;
        if (k % x == 0)
            return(k / x);
    }
}

void ce() {
    int k;
    k = 0;
    for (i = 2; i < t; i++) {
        if (t % i == 0) {
            continue;
        }
        flag = isPrime(i);
        if(flag == 1 && i != p && i != q) {
            e[k] = i;
            flag = cd(e[k]);
            if(flag > 0) {
                d[k] = flag;
                k++;
            }
            if (k == 99) {
                break;
            }
        }
    }
}

// 암호화
void encryption() {
    int pt = 0;
    int ct = 0;
    int k = 0;
    int len = 0;;
    int key = e[0];
    i = 0;
    len = strlen(message);

    while(i != len) {
        pt = m[i];
        pt = pt - 96;
        k = 1;

        for (int f = 0; f < key; f++) {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }

    en[i] = -1;
    cout << "암호화" << endl;

    for (i = 0; en[i] != -1; i++) {
        cout << (char)en[i];
    }
    cout << endl;
}

// 복호화
void decryption() {
    int pt = 0;
    int ct = 0;
    int k = 0;
    int key = d[0];
    i = 0;
    while(en[i] != -1) {
        ct = temp[i];
        k = 1;
        for (int f = 0; f < key; f++) {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        m[i] = pt;
        i++;
    }
    m[i] = -1;
    cout << "복호화" << endl;

    for (i = 0; m[i] != -1; i++) {
        cout << (char)m[i];
    }
    cout << endl;
}

int main() 
{
    WELL512::init((unsigned long)time(NULL));

    cout << "Number p :";
    while(1) {
        p = WELL512::segment(2, 100000); // 난수 구간 지정
        if (isPrime(p)) {
            cout << p << endl;
            break;
        }
    }

    cout << "Number q :";
    while(1) {
        q = WELL512::segment(2, 100000); // 난수 구간 지정
        if (isPrime(q) && q != p) {
            cout << q << endl;
            break;
        }
    }

    cout << "# 평문 입력" << endl;

    cin >> message;

    for (i = 0; message[i] != NULL; i++) {
        m[i] = message[i];
    }
    n = p * q;
    t = (p - 1) * (q - 1);
    
    ce();
    encryption();
    decryption();

    cout << "# 소인수분해" << endl;
    clock_t start, end;
    start = clock();
    while (1) {
        N = n;
        cout << N << " = ";
        SoE();
        vector<int> result;
        result = factor();
        for (int i = 0; i < result.size() - 1; i++) {
            cout << result[i] << " * ";
        }
        cout << result[result.size() - 1];
        break;
    }
    end = clock();
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "\n# 수행시간 : " << time;
}