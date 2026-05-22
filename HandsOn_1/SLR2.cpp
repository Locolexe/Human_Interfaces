#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class LinearRegression {
private:
    vector<double> x1, x2, y;
    double B0, B1, B2;

public:

    LinearRegression() {

        addData(41.9, 29.1, 251.3);
        addData(43.4, 29.3, 251.3);
        addData(43.9, 29.5, 248.3);
        addData(44.5, 29.7, 267.5);
        addData(47.3, 29.9, 273.0);
        addData(47.5, 30.3, 276.5);
        addData(47.9, 30.5, 270.3);
        addData(50.2, 30.7, 274.9);
        addData(52.8, 30.8, 285.0);
        addData(53.2, 30.9, 290.0);
        addData(56.7, 31.5, 297.0);
        addData(57.0, 31.7, 302.5);
        addData(63.5, 31.9, 304.5);
        addData(65.3, 32.0, 309.3);
        addData(71.1, 32.1, 321.7);
        addData(77.0, 32.5, 330.7);
        addData(77.8, 32.9, 349.0);
    }

    void addData(double a, double b, double c) {
        x1.push_back(a);
        x2.push_back(b);
        y.push_back(c);
    }

    void fit() {

        int n = x1.size();

        double sumX1 = 0, sumX2 = 0, sumY = 0;
        double sumX1X1 = 0, sumX2X2 = 0, sumX1X2 = 0;
        double sumX1Y = 0, sumX2Y = 0;

        for (int i = 0; i < n; i++) {

            sumX1 += x1[i];
            sumX2 += x2[i];
            sumY += y[i];

            sumX1X1 += x1[i] * x1[i];
            sumX2X2 += x2[i] * x2[i];
            sumX1X2 += x1[i] * x2[i];

            sumX1Y += x1[i] * y[i];
            sumX2Y += x2[i] * y[i];
        }

        double A[3][4] = {
            {(double)n, sumX1, sumX2, sumY},
            {sumX1, sumX1X1, sumX1X2, sumX1Y},
            {sumX2, sumX1X2, sumX2X2, sumX2Y}
        };

        // Eliminación Gaussiana

        for (int i = 0; i < 3; i++) {

            double pivot = A[i][i];

            for (int j = 0; j < 4; j++) {
                A[i][j] /= pivot;
            }

            for (int k = 0; k < 3; k++) {

                if (k != i) {

                    double factor = A[k][i];

                    for (int j = 0; j < 4; j++) {
                        A[k][j] -= factor * A[i][j];
                    }
                }
            }
        }

        // Parámetros óptimos

        B0 = A[0][3];
        B1 = A[1][3];
        B2 = A[2][3];
    }

    void printEquation() {

        cout << fixed << setprecision(6);

        cout << "========================================" << endl;
        cout << " ECUACION DE REGRESION LINEAL MULTIPLE" << endl;
        cout << "========================================" << endl;

        cout << "Yield = "
             << B0
             << " + (" << B1 << ")*x1"
             << " + (" << B2 << ")*x2"
             << endl;

        cout << endl;
    }

    double predict(double newX1, double newX2) {
        return B0 + (B1 * newX1) + (B2 * newX2);
    }

    void simulateExperiments() {

        cout << "========================================" << endl;
        cout << " SIMULACION DE NUEVOS EXPERIMENTOS" << endl;
        cout << "========================================" << endl;

        double experiments[5][2] = {
            {45.0, 29.8},
            {49.5, 30.4},
            {58.2, 31.4},
            {68.0, 32.2},
            {75.0, 32.7}
        };

        for (int i = 0; i < 5; i++) {

            double x1Value = experiments[i][0];
            double x2Value = experiments[i][1];

            double predictedYield = predict(x1Value, x2Value);

            cout << "Experimento " << (i + 1) << endl;
            cout << "x1 = " << x1Value << endl;
            cout << "x2 = " << x2Value << endl;
            cout << "Yield Predicho = "
                 << predictedYield << endl;

            cout << "----------------------------------------"
                 << endl;
        }
    }
};

int main() {

    LinearRegression model;

    model.fit();

    model.printEquation();

    model.simulateExperiments();

    return 0;
}