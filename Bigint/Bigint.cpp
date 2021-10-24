#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct bigint {
    vector<int> int_rev;
    bool is_zhen = true;
    bigint() { this->int_rev.push_back(0); };
    bigint(const string& s) {
        for (int i = s.size() - 1; i >= 0; i--) {
            int_rev.push_back(s[i] - '0');
        }
    }
    bigint(const int& s) {
        *this = bigint(to_string(s));
    }
    int size() const {
        return this->int_rev.size();
    }
    void const printbigint();
    void chulin() {
        int i = this->int_rev.size() - 1;
        for (;; i--) {
            if (this->int_rev[i]) break;
            else {
                if (this->size() > 1) {
                    this->int_rev.erase(int_rev.end() - 1);
                }
                else {
                    break;
                }
            }
        }
    }

    void jinwei() {
        int i = this->int_rev.size() - 1;
        for (int j = 0; j <= i; j++) {
            if (this->int_rev[j] > 9) {
                if (j == i) {
                    break;
                }
                else {
                    this->int_rev[j + 1] += this->int_rev[j] / 10;
                }
                this->int_rev[j] %= 10;
            }
        }
    }
    bigint operator=(const bigint& b) {
        this->int_rev.clear();
        this->int_rev.insert(this->int_rev.begin(), b.int_rev.begin(), b.int_rev.end());
        return *this;
    }
    bool operator>(const bigint& b) {
        if (this->size() > b.size()) {
            return true;
        }
        else if (this->size() == b.size()) {
            int n = this->size() - 1;
            bool result = false;
            for (; n >= 0; n--) {
                if (this->int_rev[n] > b.int_rev[n]) {
                    result = true; break;
                }
                else if (this->int_rev[n] < b.int_rev[n]) {
                    return false;
                }
            }
            return result;
        }
        else {
            return false;
        }
    }

    bool operator>=(const bigint& b) {
        if (this->size() > b.size()) {
            return true;
        }
        else if (this->size() == b.size()) {
            int n = this->size() - 1;
            for (; n >= 0; n--) {
                if (this->int_rev[n] > b.int_rev[n]) {
                    return true;
                }
                else if (this->int_rev[n] < b.int_rev[n]) {
                    return false;
                }
                if (n == 0) { return true; }
            }
            return false;
        }
        else {
            return false;
        }
    }
    bigint operator-(const bigint& b) {
        bigint big, small, result;
        if (*this >= b) {
            big = *this; small = b;
        }
        else {
            result.int_rev[0] = -1;
            return result;
        }
        for (int b = 0; b <= small.size() - 1; b++) {
            if (big.int_rev[b] < small.int_rev[b]) {
                big.int_rev[b] += 10;
                big.int_rev[b + 1]--;
            }
            big.int_rev[b] -= small.int_rev[b];
        }
        big.chulin();
        return big;
    }
    bigint operator+(const bigint& b) {

        int l = max(this->int_rev.size(), b.int_rev.size()) - 1;
        int n = min(this->int_rev.size(), b.int_rev.size()) - 1;
        bigint result;
        result.int_rev.insert(result.int_rev.begin(), l + 2, 0);
        int i = 0;
        for (; i <= n; i++) {
            int sum = this->int_rev[i] + b.int_rev[i];
            if (sum > 9) {
                result.int_rev[i] += sum % 10;
                result.int_rev[i + 1] += 1;
            }
            else result.int_rev[i] += sum;
        }
        for (; i <= l; i++) {
            if (i > this->int_rev.size() - 1) result.int_rev[i] = b.int_rev[i];
            else  result.int_rev[i] = this->int_rev[i];
        }
        if (result.int_rev[l + 1] == 0) result.int_rev.erase(result.int_rev.end() - 1);
        return result;
    }
    bigint operator*(const bigint& b) {
        bigint result, big, small;
        if (this->int_rev.size() > b.int_rev.size()) { big = *this; small = b; }
        else { big = b; small = *this; }
        result.int_rev.insert(result.int_rev.begin(), big.int_rev.size() + small.int_rev.size(), 0);
        for (int i = 0; i <= small.int_rev.size() - 1; i++) {
            for (int j = 0; j <= big.int_rev.size() - 1; j++) {
                int sum = small.int_rev[i] * big.int_rev[j];
                result.int_rev[j + i] += sum;
            }
        }
        result.jinwei();
        result.chulin();
        return result;
    }

    bigint operator/(const bigint& s) {
        bigint result;
        if (*this > s) {
        }
        else {
            cout << " the result of / <1";
        }
        result.int_rev.insert(result.int_rev.begin(), this->size(), 0);
        int x = this->size() - s.size();
        bigint temp = s;
        for (; x >= 0; x--) {
            temp.int_rev.insert(temp.int_rev.begin(), x, 0);
            for (int j = 9; j >= 0; j--) {
                if ((*this - temp * j) >= 0) {
                    *this = *this - temp * j;
                    result.int_rev[x] += j;
                }
            }
            temp = s;
        }
        result.jinwei();
        result.chulin();
        return result;
    }

};
ostream& operator<<(ostream& out, const bigint& s) {
    if (s.size() == 0) {
        out << "error";
    }
    else {
        for (int i = s.int_rev.size() - 1; i >= 0; i--) {
            out << s.int_rev[i];
        }
    }
    return out;
}
void const bigint::printbigint() {
    cout << *this << endl;
}

int main() {
    bigint a("987654321");
    bigint b(33);
    cout << a / b << endl;
    return 0;
}