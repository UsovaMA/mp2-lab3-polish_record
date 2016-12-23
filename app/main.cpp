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
    printf("�������� ��� ���������, � ������� ����� ��������:\n1) ��������� ���������;\n2) ��������� � �����������;\n0) ����� �� ���������.\n");
    scanf("%d", &v);
    switch (v) {
    case 1:
      printf("������� ���������:\n");
      scanf("%s", expression);
      try
      {
        current = Expression.ConvertToPolish(expression);
        res = Expression.Calculator(current);
        printf("�������� ��������� ����� %f\n", res);

      }
      catch (std::logic_error &e) {
        cout << e.what() << endl;
        f = 1;
        stop = 1;
      }
      break;
    case 2:
      j = 0;
      printf("������� ��������� (���������� a,b,c, ...):\n");
      scanf("%s", expression);
      try
      {
        current = Expression.ConvertToPolish(expression);
        printf("������� ����� ����������.\n");
        scanf("%d", &j);
        for (int i = 0; i < j; ++i) {
          printf("������� �������� ���������� %c = ", ('a' + i));
          scanf("%d", &ch);
          Expression.AddVar(('a' + i), ch);
        }
        res = Expression.Calculator(current);
        printf("�������� ��������� ����� %f\n", res);
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
      printf("������ �����. ��� ������ ������ ����. �� ��������.\n");
    }
    
    if (stop == 0) {
      printf("�����:\n1) �������� �������� ������;\n2) ������ ����� ���������;\n0) ����� �� ���������.\n");
      scanf("%d", &var);
      switch (var) {
      case 1:
        printf("�������� ������: ");
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
        printf("������ �����. ��� ������ ������ ����. �� ��������.\n");
        f = 0;
      }
    }
    stop = 0;
  }
}
