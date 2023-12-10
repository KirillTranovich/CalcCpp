#include "Token_stream.h"
#include "Roman.h"



void Token_stream::putback(Token t)
{
  if (full)
    error("putback() into a full buffer");

  buffer = t;
  full = true;
}



Token Token_stream::get()  // обрабатывает полученный символ как токен
{
  if (full)
  {
    full = false;
    return buffer;
  }

  char ch;
  cin >> ch;

  switch (ch)
  {
  case declkey:
    return Token{let};
  case '(':
  
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
  case '^':
  case '~':
  case print:
  case '=':
    return Token{ch};
  case '.':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  {
    cin.putback(ch);
    double val;
    cin >> val;
    return Token{number, val};
  }
  default:  // проверка коректности имени введенной переменной
    if (isalpha(ch))
    {
      string s;
      s += ch;
      while (cin.get(ch) && (isalpha(ch) || isdigit(ch))){
        s += ch;
      }
      cin.putback(ch);
    
      if(IsValidRoman(s))
      {
        return Token{number, ChangeToInt(s)};
      }

      if (s == "log"){return Token(logg);}
      if (s == "sin"){return Token(sinn);}
      if (s == "roman"){return Token(roman);}
      if (s == "cos"){return Token(cosin);}
        
      if (s == quit)
        exit(0);

      return Token{name, s};
    }
    error("Bad token");
  }
}

void Token_stream::ignore(char c)  // c represents the kind of Token
{
  if (full && c == buffer.kind)
  {
    full = false;
    return;
  }
  full = false;

  char ch{0};
  while (cin >> ch)
    if (ch == c)
      return;
}

