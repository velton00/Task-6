#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include "func.h"
// функция находит абсциссу точки пересечения двух функций на определенном интервале методом деления отрезка пополам
float root(float (f)(float), float (g)(float), float a, float b, float eps1) {
    float fa = f(a), fb = f(b), ga = g(a), gb = g(b);
    float c, fc, gc;
    int count = 0;
    while (b - a > eps1) {
        c = (a + b) / 2;
        fc = f(c);
        gc = g(c);
        if ((fa - ga) * (fc - gc) <= 0) {
            b = c;
            fb = fc;
            gb = gc;
            count++;
        } else {
            a = c;
            fa = fc;
            ga = gc;
            count++;
        }
    }
    printf("Count of iterations: %d  \t Root: %.3f\n", count, (a+b)/2);
    return (a + b) / 2;
}
// Функция находит значение определенного интеграла с помощью Формулы Симпсона(парабол)от функции на определенном отрезке
float integral(float (f)(float), float a, float b, float eps2) {
    int n = 2;  // начальное количество разбиений отрезка [a, b]
    float h = (b-a)/n;  // шаг разбиения
    float I1, I2;  // значения интеграла на предыдущем и текущем шагах
    I2 = h/3 * (f(a) + 4*f(a+h) + f(b));  // вычисляем интеграл на первом шаге
    do {
        I1 = I2;  // сохраняем значение интеграла на предыдущем шаге
        n *= 2;  // увеличиваем количество разбиений в два раза
        h /= 2;  // уменьшаем шаг разбиения в два раза
        I2 = 0;
        for (int i = 0; i <= n-2; i += 2) {  // вычисляем сумму четных значений функций f(x)
            I2 += f(a + i*h) + 4*f(a + (i+1)*h) + f(a + (i+2)*h);
        }
        I2 *= h/3;  // умножаем сумму на h/3
    } while (fabs(I2 - I1) > eps2);  // повторяем, пока разница между значениями интеграла на текущем и предыдущем шагах больше eps2
    return I2;  // возвращаем вычисленное значение интеграла с заданной точностью eps2
}
// Функция, опиcывающая действия программы, при ключе -h (help - список доступных ключей)
void print_h(){
    printf("==============================HELP==============================\n"
           "This program searches for the area of a figure bounded by perceived curves.\n"
           "1) Use key -f to look at functions;\n"
           "2) Use key -i (num of func) (a) (b) to find Riemann's integral on [a, b];\n"
           "3) Use key -m to look at main task solution;\n"
           "================================================================\n");
}
// Функция, опиcывающая действия программы, при ключе -f (список функций)
void print_f(){
    printf("==============================FUNC==============================\n"
           "1) exp(x)+2\n"
           "2) -2*x+8\n"
           "3) -5/x\n"
           "================================================================\n");
}
// Функция, опиcывающая действия программы, при ключе -i (Нахождение интеграла от определенных функций на заданном пользователем интервале)
void i_a_to_b(char num, float a, float b, float eps2){
    switch (num) {
        case '1':
            printf("Integral from %.3f to %.3f is: %.3f\n", a, b, integral(f1, a, b, eps2));
            break;
        case '2':
            printf("Integral from %.3f to %.3f is: %.3f\n", a, b, integral(f2, a, b, eps2));
            break;
        case '3':
            printf("Integral from %.3f to %.3f is: %.3f\n", a, b, integral(f3, a, b, eps2));
            break;
        default: break;
    }
}
// Функция выполняет основную задачу - поиск площади фигуры, ограниченной кривыми
void m_task(float a1, float b1, float a2, float b2, float a3, float b3, float eps1, float eps2){
    float root1, root2, root3, S;
    printf("f1 and f3: \t");
    root1 = root(f3, f1, a1, b1, eps1); // x1
    printf("f2 and f3: \t");
    root2 = root(f3, f2, a2, b2, eps1);  // x2
    printf("f1 and f2: \t");
    root3 = root(f2, f1, a3, b3, eps1);  // x3
    S = integral(f3, root1, root2, eps2) + integral(f2, root2, root3, eps2) - integral(f1, root1, root3, eps2);
    printf("\n");
    printf("The area of the figure: %.3f\n", S);
}

int main(int argc, char * argv[]){
    int rez = 0;
    char num;
    float a, b;
    float eps = 0.001;
    float  eps1 = eps/10;
    float  eps2 = eps/100;
    float a1 = -3.0, b1 = -2.0, a2 = -1.0, b2 = -0.25, a3 = 1.0, b3 = 2.0;
    while((rez = getopt(argc, argv, "hftmi:"))!= - 1){
        switch (rez) {
            case 'h' :
                print_h();
                break;
            case 'f':
                print_f();
                break;
            case 'i':
                num = (char)argv[optind-1][0];
                a = (float)atof(argv[optind]);
                b = (float)atof(argv[++optind]);
                i_a_to_b(num, a, b, eps2);
                break;
            case 'm':
                m_task(a1, b1, a2, b2, a3, b3, eps1, eps2);
                break;
            default: break;
        }

    }
    return 0;
}
