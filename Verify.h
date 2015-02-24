#ifndef _VERIFY_H
#define _VERIFY_H

#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <vector>
#include <functional>
#include <string>
#include <ostream>


struct Test {
    std::string name;
    std::string expected;
    std::function<void()> routine;
};

struct TestGroup {
    std::string name;
    std::vector<Test> tests;
};

class Verify {
public:
    Verify();
    ~Verify();
    void test(std::string name, std::vector<Test> *tests);
    void run();
private:
    std::string readBuf();
    std::vector<TestGroup> groups;
    std::stringstream buffer;
    std::streambuf *old;
};

#endif // _VERIFY_H
