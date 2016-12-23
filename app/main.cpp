#include "PolishRecord.h"
#include <string.h>
#include <stdio.h>
#include <stdexcept>
#include <clocale>
#include <iostream>

int main() {
  using namespace std;
  Polish Expression;
  char expression[100];
  double res;
  int var, v, j = 0, p = 0, ch = 0;
  int f = 1, stop = 0;
  char* current;
  setlocale(LC_ALL, "Russian");
  while (f != 0) {
    printf("Выберете вид выражения, с которым будем работать:\n1) численное выражение;\n2) выражение с переменными;\n0) выход из программы.\n");
    scanf("%d", &v);
    switch (v) {
    case 1:
      printf("Введите выражение:\n");
      scanf("%s", expression);
      try
      {
        current = Expression.ConvertToPolish(expression);
        res = Expression.Calculator(current);
        printf("Значение выражения равно %f\n", res);

      }
      catch (std::logic_error &e) {
        cout << e.what() << endl;
        f = 1;
        stop = 1;
      }
      break;
    case 2:
      j = 0;
      printf("Введите выражение (переменные a,b,c, ...):\n");
      scanf("%s", expression);
      try
      {
        current = Expression.ConvertToPolish(expression);
        printf("Введите число переменных.\n");
        scanf("%d", &j);
        for (int i = 0; i < j; ++i) {
          printf("Введите значение переменной %c = ", ('a' + i));
          scanf("%d", &ch);
          Expression.AddVar(('a' + i), ch);
        }
        res = Expression.Calculator(current);
        printf("Значение выражения равно %f\n", res);
      }
      catch (std::logic_error &e) {
        cout << e.what() << endl;
        f = 1;
        stop = 1;
      }
      break;
    case 0:
      f = 0;
      stop = 1;
      break;
    default:
      printf("Ошибка ввода. Нет такого пункта меню. До свидания.\n");
    }
    
    if (stop == 0) {
      printf("Далее:\n1) показать польскую запись;\n2) ввести новое выражение;\n0) выход из программы.\n");
      scanf("%d", &var);
      switch (var) {
      case 1:
        printf("Польская запись: ");
        for (int i = 0; i < strlen(current); ++i)
          printf("%c", current[i]);
        printf("\n");
        break;
      case 2:
        f = 1;
        break;
      case 0:
        f = 0;
        break;
      default:
        printf("Ошибка ввода. Нет такого пункта меню. До свидания.\n");
        f = 0;
      }
    }
    stop = 0;
  }
}
