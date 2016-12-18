#ifndef __POLISHRECORD_H__
#define __POLISHRECORD_H__

struct CNode {                     // список строк
  char* data;
  CNode *next;
};

CNode* Add(CNode*, char*);

struct Variable {                  // переменные
  char ch;
  double val;
  Variable* next;
};

class Polish {
  Variable* vars;                  // переменные
  int priority(char);              // приоритет операций
  CNode* partition(char*);         // разбиение выражения на части
  bool IsTrueNumber(char);         // проверка корректности ввода
  bool IsTrueSymbol(char);
 public:
  void AddVar(char, int);          // добавляет (изменяет) переменную
  char* ConvertToPolish(char*);    // преобразование в польскую запись
  double Calculator(char*);        // вычисляет выражение
};
#endif  // __POLISHRECORD_H__
