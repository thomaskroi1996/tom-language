#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

// FIXED -> repeat x times
// CONDITIONAL -> while
enum LoopType { FIXED, CONDITIONAL };

// info about loop state
struct LoopState {
  LoopType type;
  int remaining;
  int startIndex;
};

// determine whether s is a number
bool isNumber(const string &s) {
  if (s.empty())
    return false;
  for (char const &c : s) {
    if (!isdigit(c))
      return false;
  }
  return true;
}

// basically just look ahead to see if next token is a number
// if so, increment i so that it wont give an error
// save tokens[i + 1] into amt var for amount of command calls
int get_amount(int i, const vector<string> &tokens) {
  int amt = 1;
  if (i + 1 < tokens.size() && isNumber(tokens[i + 1])) {
    amt = stoi(tokens[i + 1]);
    i++;
  }

  return amt;
}

// interpreter because i dont know how to write a compiler lol
void interpret(string code) {
  // vector of tokens
  vector<string> tokens;
  stringstream ss(code);
  string temp;
  while (ss >> temp) {
    tokens.push_back(temp);
  }

  vector<int> tape(30000, 0);
  int ptr = 0;

  stack<LoopState> loopStack;
  map<int, int> loopMap;
  stack<int> bracketStack;

  for (int i = 0; i < tokens.size(); ++i) {
    if (tokens[i] == "repeat" || tokens[i] == "while") {
      bracketStack.push(i);
    } else if (tokens[i] == "end") {
      int start = bracketStack.top();
      bracketStack.pop();
      loopMap[start] = i;
      loopMap[i] = start;
    }
  }

  for (int i = 0; i < tokens.size(); ++i) {
    string cmd = tokens[i];

    if (cmd == "inc")
      tape[ptr] += get_amount(i, tokens);
    else if (cmd == "dec")
      tape[ptr] -= get_amount(i, tokens);
    else if (cmd == "right")
      ptr += get_amount(i, tokens);
    else if (cmd == "left")
      ptr -= get_amount(i, tokens);
    else if (cmd == "print") {
      for (int j = 0; j < get_amount(i, tokens); ++j)
        cout << (char)tape[ptr] << flush;
    } else if (cmd == "repeat") {
      // for loop
      int n = get_amount(i, tokens);
      if (n > 0)
        loopStack.push({FIXED, n - 1, i});
      else
        i = loopMap[i - 1];
    } else if (cmd == "while") {
      // conditional loop
      if (tape[ptr] != 0)
        loopStack.push({CONDITIONAL, 0, i});
      else
        i = loopMap[i];
    } else if (cmd == "end") {
      if (loopStack.empty())
        continue;
      // get input from keyboard
      else if (cmd == "get") {
        char input;
        cin >> input;
        tape[ptr] = (int)input;
      } else if (cmd == "set") {
        if (i + 1 < (int)tokens.size() && isNumber(tokens[i + 1]))
          tape[ptr] = stoi(tokens[++i]);
      }
      // copy from one cell to another
      else if (cmd == "copy") {
        int offset = stoi(tokens[++i]);
        tape[ptr] = tape[ptr + offset];
      }
      // print literal number instead of ascii
      else if (cmd == "out")
        cout << tape[ptr] << " ";
      // print first few values from tape for debug
      else if (cmd == "dump") {
        cout << "\n debug ptr:" << ptr << " | ";
        for (int j = 0; j < 5; ++j)
          cout << "Cell " << j << ":" << tape[j] << " ";
        cout << endl;
      }

      LoopState &current = loopStack.top();
      if (current.type == FIXED) {
        if (current.remaining > 0) {
          current.remaining--;
          i = current.startIndex;
        } else {
          loopStack.pop();
        }
      } else if (current.type == CONDITIONAL) {
        if (tape[ptr] != 0) {
          i = current.startIndex;
        } else {
          loopStack.pop();
        }
      }
    }
  }
}

int main() {
  string hi = "inc 8 while right inc 9 left dec 1 end right print inc 33 print";
  string test = "inc 47 while print dec 1 end";
  string asterisk = "inc 42 repeat 5 print end";
  interpret(hi);
  std::cout << std::endl;
  interpret(test);
  std::cout << std::endl;
  interpret(asterisk);
  string biometrics = "set 178 right 1 set 70 right 1 set 29 dump";
  interpret(biometrics);
  return 0;
}
