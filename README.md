# Verify
Unit testing for C++

## Usage
### Creating and Running Tests

First, include Verify:
```C++
#include "Verify.h"
```

Create a new instance of Verify and run Verify like this:
```C++
Verify v;
//Add tests here
v.run();
```

Before running Verify, we need to create some tests. Tests are added using the following format:
```C++
v.test("Test group name", new vector<Test>({
    {"Test name", "expected", []{ cout << "test value"; }},
    {"Test name", "expected", []{ cout << "test value"; }},
    {"Test name", "expected", []{ cout << "test value"; }}
}));
```

Tests include a C++0x <a href="http://en.cppreference.com/w/cpp/language/lambda">lambda function</a> which sends a value to standard output, which Verify captures.

If you want your lambda function to access an outside variable to test on (which you probably do), you can do that like this:
```C++
int n = 1;
v.test("Test with outside variable", new vector<Test> ({
       { "Print a number", "1", [&n]{ cout << n; }}
}));
```

When compiling, <strong>add the `-std=c++0x` compiler flag</strong> so that lambda functions can be used.


### Example

```C++
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
               "fail", "5", [&s]{ cout << s.length(); }
           }
    }));

    v.run();
}
```

This gives the following output:
```
String tests
═══════════════════════════════════════════════════════
output                        Passed
length                        Passed
length (should fail)          Failed
                               --- Expected:  5
                               --- Got:       4
───────────────────────────────────────────────────────
                              Passed 2/3 tests

═══════════════════════════════════════════════════════

There were errors in 1 test group.
```
