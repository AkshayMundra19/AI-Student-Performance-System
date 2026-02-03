#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class StudentAI {
    double w1, w2, w3, bias;

public:
    StudentAI() {
        w1 = w2 = w3 = bias = 0.0;
    }

    void train(vector<double>& a,
               vector<double>& i,
               vector<double>& as,
               vector<double>& fs,
               int epochs,
               double lr) {

        int n = a.size();

        for (int e = 0; e < epochs; e++) {
            double dw1 = 0, dw2 = 0, dw3 = 0, db = 0;

            for (int k = 0; k < n; k++) {
                double pred = w1*a[k] + w2*i[k] + w3*as[k] + bias;
                double err = pred - fs[k];

                dw1 += err * a[k];
                dw2 += err * i[k];
                dw3 += err * as[k];
                db  += err;
            }

            w1 -= lr * dw1 / n;
            w2 -= lr * dw2 / n;
            w3 -= lr * dw3 / n;
            bias -= lr * db / n;
        }
    }

    double predict(double a, double i, double as) {
        return w1*a + w2*i + w3*as + bias;
    }
};

string grade(double s) {
    if (s >= 85) return "A";
    if (s >= 70) return "B";
    if (s >= 55) return "C";
    return "D";
}

string resultStatus(double s) {
    return (s >= 50) ? "PASS" : "FAIL";
}

double riskScore(double a, double i) {
    double r = 100;
    if (a < 75) r -= (75 - a);
    if (i < 60) r -= (60 - i);
    if (r < 0) r = 0;
    return r;
}

int main() {
    StudentAI ai;

    vector<double> attendance = {78,85,90,60,55,88,72,95,40,67,80,92,58,76,83};
    vector<double> internals  = {70,80,88,50,45,85,65,92,35,60,75,90,48,70,78};
    vector<double> assignments= {72,78,85,55,50,88,68,94,45,65,77,91,52,73,80};
    vector<double> finalScore = {74,82,90,55,50,88,70,95,45,63,78,92,52,75,82};

    ai.train(attendance, internals, assignments, finalScore, 2000, 0.0001);

    int ch;
    do {
        cout << "\n=== AI STUDENT PERFORMANCE SYSTEM ===\n";
        cout << "1. Predict Performance\n";
        cout << "2. Exit\n";
        cout << "Choice: ";
        cin >> ch;

        if (ch == 1) {
            double a, i, as;
            cout << "Attendance: ";
            cin >> a;
            cout << "Internal Marks: ";
            cin >> i;
            cout << "Assignment Score: ";
            cin >> as;

            double p = ai.predict(a, i, as);

            cout << "\nPredicted Score: " << p << endl;
            cout << "Grade: " << grade(p) << endl;
            cout << "Result: " << resultStatus(p) << endl;
            cout << "Risk Score: " << riskScore(a, i) << "/100\n";
        }
    } while (ch != 2);

    return 0;
}
