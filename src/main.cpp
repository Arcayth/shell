#include <cstdlib>
#include <iostream>

using namespace std;

enum CMD {
    EXIT,
    ECHO,
    TYPE,
    UNKNOWN,
};

CMD command_parser(string cmd){
    if (cmd == "exit") return EXIT;
    if (cmd == "echo") return ECHO;
    if (cmd == "type") return TYPE;

    return UNKNOWN;
}

void handle_exit() {
    exit(0);
}

void handle_echo(string input) {
    // 5 is the lenght of "echo "
    string args = input.substr(5);
    cout << args << endl;
}

void handle_type(string input) {
    // 5 is the lenght of "type "
    string args = input.substr(5);
    string cmd = args.substr(0, input.find(" "));

    switch (command_parser(cmd)) {
        case UNKNOWN:
            cout << cmd << ": not found:" << endl;
            break;
        default:
            cout << cmd << " is a shell builtin" << endl;
            break;
    }


    cout << cmd << ": command not found\n";
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
        string cmd = input.substr(0, input.find(" "));

        switch (command_parser(cmd)) {
            case EXIT:
                handle_exit();

            case ECHO:
                handle_echo(input);
                break;

            case TYPE:
                handle_type(input);
                break;

            case UNKNOWN:
                handle_unknown(input);
                break;
        }

    }
}
