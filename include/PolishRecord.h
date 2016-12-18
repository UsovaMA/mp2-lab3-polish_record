#ifndef __POLISHRECORD_H__
#define __POLISHRECORD_H__

struct CNode {                     // ������ �����
  char* data;
  CNode *next;
};

CNode* Add(CNode*, char*);

struct Variable {                  // ����������
  char ch;
  double val;
  Variable* next;
};

class Polish {
  Variable* vars;                  // ����������
  int priority(char);              // ��������� ��������
  CNode* partition(char*);         // ��������� ��������� �� �����
  bool IsTrueNumber(char);         // �������� ������������ �����
  bool IsTrueSymbol(char);
 public:
  void AddVar(char, int);          // ��������� (��������) ����������
  char* ConvertToPolish(char*);    // �������������� � �������� ������
  double Calculator(char*);        // ��������� ���������
};
#endif  // __POLISHRECORD_H__
