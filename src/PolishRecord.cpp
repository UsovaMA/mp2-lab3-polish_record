#include "PolishRecord.h"
#include "Stack.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdexcept>

CNode* Add(CNode* CurNode, char* data) {
  CNode* Node = new CNode;
  Node->data = data;
  Node->next = 0;
  CurNode->next = Node;
  return Node;
}

bool Polish::IsTrueNumber(char a) {
  return (((a >= '0') && (a <= '9')) || ((a >= 'a') && (a <= 'z')));
}

bool Polish::IsTrueSymbol(char a) {
  return ((a == '+') || (a == '-') || (a == '*') || (a == '/') ||
    (a == '^') || (a == '|') || (a == '(') || (a == ')') || (a == ' '));
}

int Polish::priority(char c) {
  switch (c) {
    case '(': return 0;
    case '|': return 0;
    case '+': return 1;
    case '-': return 1;
    case '_': return 1;  // унарный минус
    case '*': return 2;
    case '/': return 2;
    case '^': return 3;
  }
}

void Polish::AddVar(char c, int v) {
  Variable* tmp = vars;
  bool f = false;
  while (tmp) {
    if (c == tmp->ch) {
      f = true;
      break;
    }
    tmp = tmp->next;
  }
  if (f) {
    tmp->val = v;  // изменяет значение существующей переменной
  } else {
    Variable* newvar = new Variable;  // добавляет новую переменную
    newvar->ch = c;
    newvar->val = v;
    newvar->next = vars;
    vars = newvar;
  }
}

CNode* Polish::partition(char* expression) {
  bool status;
  CNode* partition = new CNode;
  CNode* cur = partition;
  char * str = new char[10];
  int len = 0, halfpart = 0;
  char* c;

  if (!expression[0])
    throw std::logic_error("String is empty\n");

  int slen = strlen(expression);
  char *exp = new char[slen + 2];
  exp = strcpy(exp, expression);
  exp[slen] = ' ';
  exp[slen + 1] = 0;

  if (IsTrueNumber(exp[0]))
    status = 1;
  else
    status = 0;

  for (int i = 0; exp[i] != 0; i++) {
    c = new char(exp[i]);
    if (status) {
      if (IsTrueNumber(*c) || ((*c == '.') && (!halfpart))) {
        if (*c == '.')
          halfpart = 1;
        str[len] = *c;
        len++;
        delete c;
      } else {
        if (!IsTrueSymbol(*c))
          throw std::logic_error("Wrong expression\n");
        str[len] = 0;
        cur = Add(cur, str);
        status = 0;
        str = new char[10];
        len = 0;
        halfpart = 0;
        if (*c != ' ')
          cur = Add(cur, c);
        continue;
      }
    }
    if (!status) {
      if (IsTrueNumber(*c)) {
        str[len] = *c;
        len++;
        status = 1;
        delete c;
      } else {
        if (!IsTrueSymbol(*c))
          throw std::logic_error("Wrong expression\n");
        if (*c != ' ') {
          cur = Add(cur, c);
        }
      }
    }
  }
  delete[]exp;
  partition = partition->next;
  return partition;
}

char* Polish::ConvertToPolish(char* exp) {
  vars = 0;
  char* result = new char[strlen(exp) * 2];
  char last_element = ' ';
  int pos = 0, mod = 0, bracket_was = 0, module_was = 0;
  CNode* parsed = partition(exp);
  Stack<char> stack;

  if (parsed == 0)
    throw std::logic_error("Wrong expression\n");

  while (parsed) {
    char* element = parsed->data;
    if (IsTrueNumber(*element)) {
      for (int i = 0; element[i] != 0; i++, pos++)
        result[pos] = element[i];
      result[pos] = ' ';
      pos++;
    } else {
      switch (*element) {
      case '(':
        stack.push(*element);
        bracket_was = 1;
        break;
      case '|':
        if (!pos || mod || (IsTrueSymbol(last_element)
          && (last_element != '|'))) {
          stack.push(*element);
          if (parsed->next)
            if (*parsed->next->data == '|')
              mod = 1;
            else
              mod = 0;
          module_was = 1;
        } else {
          while (stack.gettop() != '|') {
            result[pos] = stack.gettop();
            pos++;
            result[pos] = ' ';
            pos++;
            stack.pop();
          }
          result[pos] = '|';
          pos++;
          result[pos] = ' ';
          pos++;
          stack.pop();
          module_was = 0;
        }
        break;
      case ')':
        if (stack.gettop() == '(')
          throw std::logic_error("Wrong expression\n");
        if (bracket_was) {
          while (stack.gettop() != '(') {
            result[pos] = stack.gettop();
            pos++;
            result[pos] = ' ';
            pos++;
            stack.pop();
          }
        }
        else
          throw std::logic_error("Wrong expression\n");
        stack.pop();
        break;
      default:
        while (!stack.empty()) {
          if ((priority(*element)) <= priority(stack.gettop())) {
            result[pos] = stack.gettop();
            pos++;
            result[pos] = ' ';
            pos++;
            stack.pop();
          }
          else
            break;
        }
        if (*element == '-') {
          if (!pos) {
            stack.push('_');
          } else {
            if ((last_element == '|') && (module_was))
              stack.push('_');
            else
              if (!stack.empty()) {
                if (last_element == '(')
                  stack.push('_');
                else
                  stack.push(*element);
              }
              else
                stack.push(*element);
          }
        }
        else
          stack.push(*element);
      }
    }
    parsed = parsed->next;
    last_element = *element;
  }
  while (!stack.empty()) {
    if ((stack.gettop() != '(') && (stack.gettop() != '|')) {
      result[pos] = stack.gettop();
      pos++;
      result[pos] = ' ';
      pos++;
    }
    else
      throw std::logic_error("Wrong expression\n");
    stack.pop();
  }
  result[pos] = 0;
  return result;
}

double Polish::Calculator(char* PolRec) {
  int k = 0;
  if (!PolRec)
    throw std::logic_error("Wrong expression\n");

  int len = strlen(PolRec), numlen;
  Variable* buf;
  Stack<double> stack;
  char* num;
  double a, b;

  for (int i = 0; i < len; i++) {
    if ((PolRec[i] >= 'a') && (PolRec[i] <= 'z')) {
      buf = vars;
      while (buf) {
        if (buf->ch == PolRec[i])
          break;
        buf = buf->next;
      }
      if (!buf)
        throw std::logic_error("Variables are not declared\n");
      stack.push(buf->val);
      i++;
    }
    else
      if ((PolRec[i] >= '0') && (PolRec[i] <= '9')) {
        num = new char[10];
        numlen = 0;
        while (PolRec[i] != ' ') {
          if ((PolRec[i] >= 'a') && (PolRec[i] <= 'z'))
            throw std::logic_error("Wrong expression\n");
          num[numlen] = PolRec[i];
          numlen++;
          i++;
        }
        num[numlen] = 0;
        double p = 0.0;
        int e = 0;
        int c;
        while (((c = *num++) != 0) && (c != '.')) {
          p = p*10.0 + (c - '0');
        }
        if (c == '.') {
          while ((c = *num++) != 0) {
            p = p*10.0 + (c - '0');
            e = e - 1;
          }
        }
        while (e < 0) {
           p = p/10.0;
           e++;
        }
        stack.push(p);
      }
      else
        if (!stack.empty()) {
          b = stack.gettop();
          stack.pop();
          if ((PolRec[i] != '|') && (PolRec[i] != '_')) {
            if (!stack.empty()) {
              a = stack.gettop();
              stack.pop();
            }
            else
              throw std::logic_error("Wrong expression\n");
          }
          switch (PolRec[i]) {
          case '+':
            stack.push(a + b);
            break;
          case '-':
            stack.push(a - b);
            break;
          case '*':
            stack.push(a * b);
            break;
          case '/':
            stack.push(a / b);
            break;
          case '^':
            stack.push(pow(a, b));
            break;
          case '|':
            stack.push(abs(b));
            break;
          case '_':
            stack.push(-b);
            break;
          default:
            throw std::logic_error("Wrong expression\n");
          }
          i++;
        }
        else
          throw std::logic_error("Wrong expression\n");
  }
  double result = stack.gettop();
  stack.pop();
  if (stack.empty())
    return result;
  else
     throw std::logic_error("Wrong expression\n");
}
