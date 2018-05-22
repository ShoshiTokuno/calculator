#include <iostream>
#include <vector>

std::vector<char> getline()
{
  std::vector<char> str;
  do
  {
    str.push_back(getchar());
  } while (str.back() != '\n');
  str.pop_back();
  return str;
}

bool symbol(char character)
{
  if (character == '+' || character == '-' || character == '*' || character == '/' || character == '(' || character == ')')
  {
    return true;
  }
  else 
  {
    return false;
  }
}

bool operators(char character)
{
  if (character == '+' || character == '-' || character == '*' || character == '/')
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool error_check(std::vector<std::vector<char>> str)
{
  bool decision = true;
  if (str[0][0] != '(' || str[str.size() - 1][0] != ')')
  {
    decision = false;
  }
  for (int line = 0; line < str.size() - 1; line++)
  {
    if ((str[line][0] != '(' && operators(str[line + 1][0]) == true) || (str[line][0] == '(' && operators(str[line + 1][0]) == false) || (str[line + 1][0] == ')' && (str[line][0] == '(' || operators(str[line][0]) == true)))
    {
      decision = false;
    }
  }
  return decision;
}

std::vector<std::vector<char>> tokenize(std::vector<char> str)
{
  std::vector<char> str_line;
  std::vector<std::vector<char>> token;
  str_line.push_back(str[0]);
  token.push_back(str_line);
  str_line.clear();
  for (int index = 1; index < str.size(); index++)
  {
    if (str[index] == ' ')
    {
      if (symbol(str[index - 1]) == true) {}
      else
      {
        token.push_back(str_line);
        str_line.clear();
      }
    }
    else if (symbol(str[index]))
    {
      if (str[index - 1] == ' ' || symbol(str[index - 1]) == true)
      {
	str_line.push_back(str[index]);
	token.push_back(str_line);
	str_line.clear();
      }
      else
      {
	token.push_back(str_line);
	str_line.clear();
	str_line.push_back(str[index]);
	token.push_back(str_line);
	str_line.clear();
      }
    }
    else
    {
      str_line.push_back(str[index]);
    }
  }
  return token;
}

double to_number(std::vector<char> str, int size)
{
  int digit = 1;
  double number = 0;
  for (int buffer = 0; buffer < size; buffer++)
  {
    number = number + (str[size - buffer - 1] - '0') * digit;
    digit = digit * 10;
  }
  return number;
}

double calculate(std::vector<std::vector<char>> token, std::vector<double> number, int first_line, int end_line)
{
  double answer_number = number[first_line + 2];
  switch(token[first_line + 1][0])
  {
  case '+':
    for (int index = first_line + 3; index < end_line; index++)
    {
      answer_number = answer_number + number[index];
    }
    break;
  case '-':
    for (int index = first_line + 3; index < end_line; index++)
    {
      answer_number = answer_number - number[index];
    }
    break;
  case '*':
    for (int index = first_line + 3; index < end_line; index++)
    {
      answer_number = answer_number * number[index];
    }
    break;
  case '/':
    for (int index = first_line + 3; index < end_line; index++)
    {
      answer_number = answer_number / number[index];
    }
    break;
  }
  return answer_number;
}

void answer(std::vector<std::vector<char>> token, int first_line, std::vector<double>& number, int& end_line)
{
  int index_end;
  for (int line = first_line; line < token.size(); line++)
  {
    number.push_back(to_number(token[line], token[line].size()));
    if (line != first_line && token[line][0] == '(')
    {
      number.pop_back();
      answer(token, line, number, index_end);
      token.erase(token.begin() + line + 1, token.begin() + index_end + 1);
    }
    else if (token[line][0] == ')')
    {
      number[first_line] = calculate(token, number, first_line, line);
      number.erase(number.begin() + first_line + 1, number.begin() + line + 1);
      end_line = line;
      break;
    }
  }
}

int main()
{
  std::vector<char> str = getline();
  std::vector<std::vector<char>> token = tokenize(str);
  std::vector<double> number;
  int hoge;
  if (error_check(token))
   {
    answer(token, 0, number, hoge);
    std::cout << number[0] << std::endl;
   }
   else
   {
     std::cout << "error" << std::endl;
   }
  return 0;
}
