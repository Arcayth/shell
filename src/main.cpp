#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;
namespace fs = filesystem;

enum CMD {
    EXIT,
    ECHO,
    TYPE,
    PWD,
    CD,
    UNKNOWN,
};

CMD command_parser(string cmd) {
    if (cmd == "exit")
        return EXIT;
    if (cmd == "echo")
        return ECHO;
    if (cmd == "type")
        return TYPE;
    if (cmd == "pwd")
        return PWD;
    if (cmd == "cd")
        return CD;

    return UNKNOWN;
}

void handle_exit() { exit(0); }

void handle_echo(const string input) {
    // 5 is the lenght of "echo "
    string cmd = input.substr(5);
    cout << cmd << endl;
}

vector<string> split(string input, const string delimiter) {
    vector<string> tokens;
    string token;
    size_t pos = 0;

    while ((pos = input.find(delimiter)) != string::npos) {
        token = input.substr(0, pos);
        tokens.push_back(token);
        input.erase(0, pos + delimiter.length());
    }
    tokens.push_back(input);

    return tokens;
}

bool check_path(string path, string cmd) {
    string cmd_path = path + "/" + cmd;
    if (fs::exists(cmd_path)) {
        return true;
    }
    return false;
}

tuple<string, bool> get_path(string cmd) {
    char *path = getenv("PATH");
    vector<string> paths = split(path, ":");
    bool is_valid_path;
    for (int i = 0; i < paths.size(); i++) {
        if (check_path(paths[i], cmd)) {
            string path = paths[i] + "/" + cmd;
            return make_tuple(path, true);
        }
    }
    return make_tuple("", false);
}

void handle_type(string input) {
    // 5 is the lenght of "type "
    string cmd = input.substr(5);

    switch (command_parser(cmd)) {
        case EXIT:
        case ECHO:
        case TYPE:
        case PWD:
        case CD:
            cout << cmd << " is a shell builtin\n";
            break;
        case UNKNOWN:
            string path;
            bool found = false;
            tie(path, found) = get_path(cmd);
            if (found) {
                cout << cmd + " is " + path << endl;
                break;
            } else {
                cout << cmd << ": not found\n";
                break;
            }
    }
}

void handle_unknown(string input) {
    vector<string> args = split(input, " ");
    string path;
    bool found = false;
    tie(path, found) = get_path(args[0]);

    if (found) {
        string command = "exec " + args[0] + " " + args[1];
        system(command.c_str());
    } else {
        cout << input << ": command not found\n";
    }
}

void handle_pwd() {
    cout << fs::current_path().c_str() << endl;
}

void handle_cd(string input) {
    vector<string> args= split(input, " ");
    string path = args[1];
    try {
        if (args[1] == "~"){
            char* path = getenv("HOME");
            fs::current_path(path);
        } else {
            fs::current_path(args[1]);
        }
    } catch (const fs::__cxx11::filesystem_error _) {
        cerr << "cd: " + args[1] + ": No such file or directory" << endl;
    }
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

            case PWD:
                handle_pwd();
                break;

            case CD:
                handle_cd(input);
                break;

            case UNKNOWN:
                handle_unknown(input);
                break;
        }
    }
}
