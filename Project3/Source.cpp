#include <iostream>

double f(double x, double y) {
    return (y / std::pow(cos(x), 2));
}
// Схема алгоритма м.Рунге-Кутты 4 порядка
double RK4(double xi, double yi, double h0, int m) {
    double h = h0 / m;
    double x = xi;
    double y = yi;
    double k1, k2, k3, k4;
    for (int j = 1; j <= m; j++) {
        k1 = f(x, y);
        k2 = f((x + h / 2), (y + h * k1 / 2));
        k3 = f((x + h / 2), (y + h * k2 / 2));
        k4 = f((x + h), (y + h * k3));
        y = (y + (h / 6) * (k1 + (2 * k2) + (2 * k3) + k4));
        x = (xi + j * h);
    }
    return y; // Вычесленное знач. функции в точке xi+h0
}
// Схема ал-ма реш-я ОДУ с автом-им выбором шага, обеспеч-го заданную точность
void Runge(double x0, double y0, double h0, double b, double E) {
    std::cout << "x0\t\ty0" << std::endl;
    std::cout << x0 << "\t\t" << y0 << std::endl;

    int n = ((b - x0) / h0);
    double d = E * ((2<<4) - 1);
    
        for(int i = 1; i <= n; i++) {
            int m = 1;
            double y1, y = RK4(x0, y0, h0, m);

            do{
                y1 = y;
                m *= 2;
                y = RK4(x0, y0, h0, m);
            } while (abs(y-y1) >= d);
            
            x0 += h0;
            y0 = y;

            std::cout << x0 << "\t\t" << y0 << std::endl;
        }
}

void main(){
    double x0 = 0, y0 = 1, h0 = 0.1, a = 0, b = 0.4, E = 0.0001;
    Runge(x0, y0, h0, b, E);
    system("pause");
}
