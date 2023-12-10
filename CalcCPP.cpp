/*
  Грамматика  для  ввода : 
Инструкция : 
    declkey
    Выражение 
    Вывод 
    Выход 
        declkey:
            # 
                #:
                    name = Терм
                           name:
                            Строка(имя переменной)
        Вывод : 
            ;
        Выход : 
            exit
        Выражение : 
            Терм 
            Выражение  +   Терм 
            Выражение  -  Терм 
                Терм: 
                    Первичное_выражение 
                    Терм ^ первичное выражение
                    Терм   *   Первичное_выражение 
                    Терм  /  Первичное_выражение 
                    Терм   %  Первичное_ выражение 
                        Первичное_выражение : 
                            Число 
                            (Выражение   ) 
                            ~ Первичное_выражение
                            -  Первичное_выражение 
                            +   Первичное_выражение 
                                Число : 
                                    Ли терал_с_пла вающей_точкой 
Ввод  из  потока   cin   через  Token  stream  с  именем  ts. 
*/ 


#include "Token_stream.h"
#include "std_lib_facilities.h"
#include "Roman.h"
#include <cstring>
#include <cmath>
#include <iostream>
#include <math.h>


struct Variable  // структура для работы с переменными и встроенными
                 // константами

{
  string name;
  double value;

  Variable(string n, double v) : name{n}, value{v} {}
};

bool roman_state = false;

vector<Variable> var_table;


double get_value (string s)  // возвращает значение переменной с именем s
{
  for (Variable v : var_table)
    if (v.name == s)
      return v.value;

  error("get: undefined name ", s);
}

void set_value (string s, double d)  // присваивает обьекту s значение d
{
  for (Variable v : var_table)
  {
    if (v.name == s)
    {
      v.value = d;
      return;
    }
  }

  error("set: undefined name ", s);
}

bool is_declared (string s)  // есть ли переменная в векторе var_table
{
  for (Variable v : var_table)
    if (v.name == s)
      return true;

  return false;
}

double
define_name (string var,
             double val)  // добавить пару (var,val) в векттор var_table
{
  if (is_declared(var))//проверка уникальности элемента
    error(var, " declared twice");

  var_table.push_back(Variable{var, val});

  return val;
}

Token_stream ts;

double expression ();

double primary ()  // функция обрабатывает числа и скобки
{
  Token t = ts.get();
  switch (t.kind)
  {
  case '('://высчитывает выражение находящееся в скобках
  {
    double d = expression();
    t = ts.get();
    if (t.kind != ')')
      error("')' expected");
    return d;
  }
  case '~':
  {
    double d = primary();
    if (d < 0)
    {
      error("~: num < 0");
    }

    return sqrt(d);
  }
  case '-':
    return -primary();
  case '+':
    return +primary();
  case number:
    return t.value;

  case name:
    return get_value(t.name);

  default:
    error("primary expected");
  }
}

double term ()  // функция работает со знаками *, ^, % и /, необходима чтобы эти операции выполнялись в приоритете
{
  double left = primary();
  while (true)
  {
    Token t = ts.get();

    switch (t.kind)
    {
    case '*':
      left *= primary();
      break;

    case '/':
    {
      double d = primary();
      if (d == 0)
        error("divide by zero");
      left /= d;
      break;
    }

    case logg:
    {
      double d = primary();
      if (d<0 || left<0 || left==1)
      {
        error("loge: wrong arg");
      }

      return log(d)/log(left);
    }

    case '^':
    {
      double d = primary();
      if (d == round(d))
      {
        left = pow(left, d);
      }
      else
      {
        error("^: double argument");
      }
        
      break;
    }
    case '%':
    {
      double d = primary();
      if (d == 0)
        error("%: divide by zero");
      left = fmod(left, d);
      t = ts.get();
      break;
    }

    default:
      ts.putback(t);
      return left;
    }
  }
}

double expression ()  // функция работает с плюсами и минусами
{
  double left = term();

  while (true)
  {
    Token t = ts.get();

    switch (t.kind)
    {
    case '+':
      left += term(); 
      break;

    case '-':
      left -= term();
      break;

    default:
      ts.putback(t);
      return left;
    }
  }
}

double declaration ()  // проверяет,что после let находится имя=выражение
                       // обьявляет переменную с именем и начальным
// значением заданным выражением
{
  Token t = ts.get();
  if (t.kind != name)
    error("name expected in declaration");
  string var_name = t.name;

  Token t2 = ts.get();
  if (t2.kind != '=')
    error("= missing in declaration of ", var_name);

  double d = expression();
  define_name(var_name, d);
  return d;
}

double statement ()  // позволяет добавить инфтукцию "let"
{
  Token t = ts.get();
  switch (t.kind)
  {
  
  case sinn:
    return sin(primary());
  case cosin:
    return cos(primary());
  case roman:
    {
      int d = primary();
      if (d<=0)
        error("cannot transform to roman numbers");
      roman_state=true;
      return d;
      //return primary();
    }
  case let:
    return declaration(); // обработка let
  default:
    ts.putback(t);
    return expression();
  }
}

void clean_up_mess () { ts.ignore(print); }

void calculate ()  // считывает выражение отправляет на обработку
{
  while (cin)  //(true$sin)
    try
    {
      cout << prompt;
      Token t = ts.get();
      while (t.kind == print)
        t = ts.get();
      

      ts.putback(t);
      double ans=statement();
      if (roman_state){
        cout << result << ChangeToRIm(ans) << endl;
      }
      else{cout << result << ans << endl;}
    }
    catch (exception& e)  //(runtime$exetion)
    {
      cerr << e.what() << endl;
      clean_up_mess();
    }
}

int main ()  // определяет зарезервированные константы
             // вызывает метод calculate и обрабатывает ошибки
try
{
  define_name("pi", 3.141592653589793);
  define_name("k", 1000);  // создали
  define_name("e", 2.718281828459045);

  calculate();
}
catch (exception& e)
{
  cerr << "exception: " << e.what() << endl;
  return 1;
}
catch (...)
{
  cerr << "Oops, unknown exception" << endl;
  return 2;
}