#include <vector>
#include <string>
#include <iostream>
#include "Verify.h"
using namespace std;

int main() {
    Verify v;

    string s = "test";
    v.test("String tests", new vector<Test> ({
           {
               "output", "test", [&s]{ cout << s; }
           },
           {
               "length", "4", [&s]{ cout << s.length(); }
           },
           {
               "length (should fail)", "5", [&s]{ cout << s.length(); }
           },
           {
               "Exception thrown (should fail)", "1", []{ throw new exception; }
           }
    }));

    v.run();
}


