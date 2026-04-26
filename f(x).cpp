#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string fx;
ll idx;
double x;
const double EPS = 1e-9;

char cur() {
    if (idx < (ll)fx.length()) return fx[idx];
    return -1;
}

char nxt() {
    if (idx < (ll)fx.length()) return fx[idx++];
    return -1;
}

double addsub();
double muldiv();
double power();

double factor() {
    double res = 0;

    if ((cur() >= '0' && cur() <= '9') || cur() == '.') {
        string num;
        while ((cur() >= '0' && cur() <= '9') || cur() == '.') {
            num += nxt();
        }
        res = stod(num);
    }
    else if (cur() == 'x' || cur() == 'X') {
        nxt();
        res = x;
    }
    else if (cur() == '(') {
        nxt();
        res = addsub();
        if (cur() == ')') nxt();
    }
    else if (cur() == '-') {
        nxt();
        return -factor();
    }

    while (true) {
        if (cur() == '(' || cur() == 'x' || cur() == 'X' ||
            (cur() >= '0' && cur() <= '9')) {
            res *= factor();
        } else break;
    }

    return res;
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
        if (op == '*') {
            res *= power();
        } else {
            double d = power();
            if (abs(d) < EPS) throw runtime_error("Division by zero");
            res /= d;
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
    double step = 0.001;
    bool ok = false;

    for (double i = l; i <= r; i += step) {
        double f1 = f(i);

        if (abs(f1) < EPS) {
            double ans = i;
            if (abs(ans - round(ans)) < 1e-6)
                cout << "\nX = " << (ll)round(ans) << "\n";
            else
                cout << "\nX ~ " << fixed << setprecision(10) << ans << "\n";
            return 0;
        }

        double f2 = f(i + step);
        if (f1 * f2 < 0) {
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

    for (ll i = 0; i < 200; i++) {
        double mid = (l + r) / 2.0;
        double fm = f(mid);

        if (abs(fm) < EPS) {
            l = r = mid;
            break;
        }

        if (f(l) * fm < 0)
            r = mid;
        else
            l = mid;
    }

    double ans = (l + r) / 2.0;
    if (abs(ans - round(ans)) < 1e-6) cout << "\nX = " << (ll)round(ans) << "\n";
    else cout << "\nX ~ " << fixed << setprecision(10) << ans << "\n";
    cout << "\nPress Enter to exit...";
    cin.ignore();
    cin.get();
}
