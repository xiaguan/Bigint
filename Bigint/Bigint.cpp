#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct bigint {
    vector<int> int_rev;

    bigint(const string& s) {
        for (int i = s.size() - 1; i >= 0; i--) {
            int_rev.push_back(s[i] - '0');
        }
    }

    bigint operator+(const bigint& b) {
        int l = max(this->int_rev.size(), b.int_rev.size()) - 1;
        bigint result("0");
        result.int_rev.insert(int_rev.begin(), l + 2, 0);
        cout << "1";
        for (int i = 0; i <= l; i++) {
            cout << "2";
            int sum = this->int_rev[l] + b.int_rev[l];
            if (sum > 9) {
                result.int_rev[i] += sum % 10;
                result.int_rev[i + 1] += 1;
            }
            else {
                result.int_rev[i] += sum;
            }
        }
        return result;
    }

};
ostream& operator<<(ostream& out, const bigint& s) {
    int i = s.int_rev.size() - 1;
    for (; i >= 0; i--) {
        if (!s.int_rev[i]) break;
    }
    for (; i >= 0; i--) {
        out << s.int_rev[i];
    }
    return out;
}

int main() {
    bigint a("123");
    bigint b("1");
    return 0;
}