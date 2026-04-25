#include <bits/stdc++.h>
using namespace std;

string fx;
int idx;
double x;

char cur() {
    if (idx < fx.length()) return fx[idx];
    return -1;
}

char nxt() {
    if (idx < fx.length()) return fx[idx++];
    return -1;
}

double addsub();
double muldiv();
double power();

double factor() {
    if ((cur() >= '0' && cur() <= '9') || cur() == '.') {
        string num;
        while ((cur() >= '0' && cur() <= '9') || cur() == '.') {
            num += nxt();
        }
        return stod(num);
    }
    else if (cur() == 'x' || cur() == 'X') {
        nxt();
        return x;
    }
    else if (cur() == '(') {
        nxt();
        double res = addsub();
        if (cur() == ')') nxt();
        return res;
    }
    else if (cur() == '-') {
        nxt();
        return -factor();
    }
    return 0;
}

double power() {
    double res = factor();
    while (cur() == '^') {
        nxt();
        res = pow(res, factor());
    }
    return res;
}

double muldiv() {
    double res = power();
    while (cur() == '*' || cur() == '/') {
        char op = nxt();
        if (op == '*') res *= power();
        else {
            double d = power();
            if (d != 0) res /= d;
        }
    }
    return res;
}

double addsub() {
    double res = muldiv();
    while (cur() == '+' || cur() == '-') {
        char op = nxt();
        if (op == '+') res += muldiv();
        else res -= muldiv();
    }
    return res;
}

double f(double v) {
    x = v;
    idx = 0;
    return addsub();
}

int main() {
    cout << "=============================\n";
    cout << "   Equation Solver\n";
    cout << "=============================\n\n";

    cout << "Enter equation = 0\n> ";
    getline(cin, fx);

    cout << "Enter range (l r)\n> ";
    double l, r;
    cin >> l >> r;

    string t;
    for (char c : fx) if (c != ' ') t += c;
    fx = t;

    double step = 1.0;
    bool ok = false;

    for (double i = l; i < r; i += step) {
        double f1 = f(i);
        double f2 = f(i + step);
        if (f1 * f2 <= 0) {
            l = i;
            r = i + step;
            ok = true;
            break;
        }
    }

    if (!ok) {
        cout << "\nNo root in this range\n";
        return 0;
    }

    double fl = f(l);

    for (int i = 0; i < 100; i++) {
        double mid = (l + r) / 2.0;
        double fm = f(mid);
        if (fm == 0) {
            l = r = mid;
            break;
        }
        if (fl * fm < 0) {
            r = mid;
        } else {
            l = mid;
            fl = fm;
        }
    }

    cout << "\nX ~ " << (l + r) / 2.0 << "\n";
}
