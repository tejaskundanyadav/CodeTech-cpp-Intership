// task2_compression_tool.cpp
#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
using namespace std;

string runLengthEncode(const string& input) {
    string output = "";
    int count = 1;
    for (size_t i = 1; i <= input.length(); ++i) {
        if (i < input.length() && input[i] == input[i-1]) {
            count++;
        } else {
            output += input[i-1] + to_string(count);
            count = 1;
        }
    }
    return output;
}

void compressChunk(const string& input, string& output) {
    output = runLengthEncode(input);
}

int main() {
    string filename = "input.txt";
    ifstream in(filename);
    string content((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    string part1 = content.substr(0, content.size()/2);
    string part2 = content.substr(content.size()/2);

    string comp1, comp2;
    thread t1(compressChunk, ref(part1), ref(comp1));
    thread t2(compressChunk, ref(part2), ref(comp2));
    t1.join(); t2.join();

    ofstream out("compressed.txt");
    out << comp1 + comp2;
    out.close();

    cout << "File compressed successfully.\n";
    return 0;
}
