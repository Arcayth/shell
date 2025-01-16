#include <cstdlib>
#include <iostream>

using namespace std;

enum CMD {
    EXIT,
    ECHO,
    UNKNOWN,
};

CMD command_parser(string input){
    string cmd = input.substr(0, input.find(" "));
    if (cmd == "exit") return EXIT;
    if (cmd == "echo") return ECHO;

    return UNKNOWN;
}

void handle_exit() {
    exit(0);
}

void handle_echo(string input) {
    string args = input.substr(input.find("echo "));
    cout << args << endl;
}

void handle_unknown(string input) {
    string cmd = input.substr(0, input.find(" "));
    cout << cmd << ": command not found\n";
}

int main() {
    // Flush after every std::cout / std:cerr
    cout << unitbuf;
    cerr << unitbuf;

    string input;

    while (true) {
        cout << "$ ";
        getline(cin, input);
        CMD cmd = command_parser(input);

        switch (cmd) {
            case EXIT: handle_exit();
            case ECHO: handle_echo(input);
            case UNKNOWN: handle_unknown(input);
        }

    }
}
