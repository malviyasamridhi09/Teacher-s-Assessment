#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<int> toBinaryArray(int num, int size);
vector<int> twosComplement(vector<int> bin);
vector<int> add(vector<int> A, vector<int> M);
vector<int> subtract(vector<int> A, vector<int> M);
void rightShift(vector<int> &A, vector<int> &Q, int &Q1);
int getFinalDecimal(vector<int> A, vector<int> Q);

void boothAlgorithm(int multiplicand, int multiplier) {
    int n = log2(max(abs(multiplicand), abs(multiplier))) + 2; // Bits required
    int count = n; // Number of iterations

    vector<int> M = toBinaryArray(multiplicand, n);
    vector<int> Q = toBinaryArray(multiplier, n);
    vector<int> A(n, 0); // A initialized to 0
    int Q1 = 0; // Q-1 bit

    cout << "\nInitial Values:\n";
    cout << "A: "; for (int bit : A) cout << bit; cout << " Q: ";
    for (int bit : Q) cout << bit; cout << " Q-1: " << Q1 << endl;

    // Booth's Algorithm Execution
    while (count > 0) {
        int q0 = Q[Q.size() - 1];

        if (q0 == 1 && Q1 == 0) {
            A = subtract(A, M);
        } else if (q0 == 0 && Q1 == 1) {
            A = add(A, M);
        }

        rightShift(A, Q, Q1);
        count--;

        cout << "A: ";
        for (int bit : A) cout << bit;
        cout << " Q: ";
        for (int bit : Q) cout << bit;
        cout << " Q-1: " << Q1 << endl;
    }

    cout << "\nFinal result: " << getFinalDecimal(A, Q) << endl;
}

vector<int> toBinaryArray(int num, int size) {
    vector<int> binary(size, 0);
    int temp = abs(num);

    for (int i = size - 1; i >= 0; i--) {
        binary[i] = temp % 2;
        temp /= 2;
    }

    if (num < 0) {
        binary = twosComplement(binary);
    }
    return binary;
}

vector<int> twosComplement(vector<int> bin) {
    int carry = 1;
    for (int i = bin.size() - 1; i >= 0; i--) {
        bin[i] = bin[i] ^ 1; // Flip bits
    }
    for (int i = bin.size() - 1; i >= 0; i--) {
        int sum = bin[i] + carry;
        bin[i] = sum % 2;
        carry = sum / 2;
    }
    return bin;
}

vector<int> add(vector<int> A, vector<int> M) {
    int carry = 0;
    for (int i = A.size() - 1; i >= 0; i--) {
        int sum = A[i] + M[i] + carry;
        A[i] = sum % 2;
        carry = sum / 2;
    }
    return A;
}

vector<int> subtract(vector<int> A, vector<int> M) {
    return add(A, twosComplement(M));
}

void rightShift(vector<int> &A, vector<int> &Q, int &Q1) {
    Q1 = Q[Q.size() - 1];
    int lastA = A[0]; // Preserve sign bit

    // Shift Q
    for (int i = Q.size() - 1; i > 0; i--) {
        Q[i] = Q[i - 1];
    }
    Q[0] = A[A.size() - 1];

    // Shift A
    for (int i = A.size() - 1; i > 0; i--) {
        A[i] = A[i - 1];
    }
    A[0] = lastA; // Maintain sign bit
}

int getFinalDecimal(vector<int> A, vector<int> Q) {
    int res = 0, factor = 1;
    vector<int> combined(A.size() + Q.size());

    copy(A.begin(), A.end(), combined.begin());
    copy(Q.begin(), Q.end(), combined.begin() + A.size());
    bool isNegative = combined[0] == 1;

    if (isNegative) {
        combined = twosComplement(combined);
    }

    for (int i = combined.size() - 1; i >= 0; i--) {
        res += combined[i] * factor;
        factor *= 2;
    }
    return isNegative ? -res : res;
}

int main() {
    int multiplicand, multiplier;
    cout << "Enter multiplicand (M): ";
    cin >> multiplicand;
    cout << "Enter multiplier (Q): ";
    cin >> multiplier;

    boothAlgorithm(multiplicand, multiplier);

    return 0;
}
