#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

bool isNum(const string& s) {
    return !s.empty() && s.find_first_not_of("0123456789") == string::npos;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <input.tom> <output.cpp>" << endl;
        return 1;
    }

    string inputPath = argv[1];
    string outputPath = argv[2];

    ifstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open input file " << inputPath << endl;
        return 1;
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();
    string code = buffer.str();
    inputFile.close();

    stringstream ss(code);
    string cmd;
    vector<string> tokens;
    while (ss >> cmd) tokens.push_back(cmd);

    ofstream outFile(outputPath);
    if (!outFile.is_open()) {
        cerr << "Error: Could not create output file " << outputPath << endl;
        return 1;
    }

    // translate to c++
    outFile << "#include <iostream>\n#include <vector>\n\n";
    outFile << "int main() {\n";
    outFile << "    std::vector<int> tape(30000, 0);\n";
    outFile << "    int ptr = 0;\n\n";

    for (int i = 0; i < tokens.size(); ++i) {
        string t = tokens[i];
        string amt = "1";

        if (i + 1 < tokens.size() && isNum(tokens[i+1])) {
            amt = tokens[++i];
        }

        if (t == "inc")      outFile << "    tape[ptr] += " << amt << ";\n";
        else if (t == "dec") outFile << "    tape[ptr] -= " << amt << ";\n";
        else if (t == "right") outFile << "    ptr += " << amt << ";\n";
        else if (t == "left")  outFile << "    ptr -= " << amt << ";\n";
        else if (t == "print") outFile << "    std::cout << (char)tape[ptr];\n";
        else if (t == "out")   outFile << "    std::cout << tape[ptr] << \" \";\n";
        else if (t == "while") outFile << "    while (tape[ptr] != 0) {\n";
        else if (t == "repeat") {
            outFile << "    for (int i_" << i << " = 0; i_" << i << " < " << amt << "; ++i_" << i << ") {\n";
        }
        else if (t == "end")   outFile << "    }\n";
    }

    outFile << "\n    return 0;\n}";
    outFile.close();

    return 0;
}
