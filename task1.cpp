// task1_file_management.cpp
#include <iostream>
#include <fstream>
using namespace std;

void writeToFile(const string& filename) {
    ofstream out(filename);
    out << "This is a new file.\n";
    out.close();
}

void appendToFile(const string& filename) {
    ofstream out(filename, ios::app);
    out << "Appending this line.\n";
    out.close();
}

void readFile(const string& filename) {
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        cout << line << endl;
    }
    in.close();
}

int main() {
    string filename = "file.txt";
    writeToFile(filename);
    appendToFile(filename);
    cout << "Reading file contents:\n";
    readFile(filename);
    return 0;
}
