#include <cstdlib>
#include <iostream>

using namespace std;

int main() {
    // Flush after every std::cout / std:cerr
    cout << unitbuf;
    cerr << unitbuf;

    string input;

    while (true) {
        cout << "$ ";

        getline(cin, input);
        string cmd = input.substr(0, input.find(" "));
        if (cmd == "exit") {
            exit(0);
        }

        cout << input << ": command not found\n";
    }
}
