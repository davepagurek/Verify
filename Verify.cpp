#include "Verify.h"
#include <iomanip>

Verify::Verify() {
    //Begin rerouting stdout to a buffer
    old = std::cout.rdbuf(buffer.rdbuf());
}

Verify::~Verify() {
    std::cout.rdbuf( old );
}

std::string Verify::readBuf() {
    std::string s = buffer.str();
    buffer.str(std::string());
    return s;
}

void Verify::test(std::string name, std::vector<Test> *tests) {
    groups.push_back({name, *tests});
}

void Verify::run() {
    int errors = 0;
    for (std::vector<TestGroup>::iterator group = groups.begin(); group < groups.end(); group++) {
        std::cerr << group->name << std::endl;

        for (int i=0; i<45; i++) std::cerr << char(205);
        std::cerr << std::endl;

        int passed = 0;
        for (std::vector<Test>::iterator test = group->tests.begin(); test < group->tests.end(); test++) {
            std::cerr << std::setw(20) << std::left << test->name;
            test->routine();
            std::string actual = readBuf();
            if (test->expected == actual) {
                std::cerr << "Passed" << std::endl;
                passed++;
            } else {
                std::cerr << "Failed" << std::endl;
                std::cerr << std::setw(20) << " " << " --- Expected:  " << test->expected << std::endl;
                std::cerr << std::setw(20) << " " << " --- Got:       " << actual << std::endl;
            }
        }

        for (int i=0; i<45; i++) std::cerr << char(196);
        std::cerr << std::endl;

        std::cerr << std::setw(20) << " " << "Passed " << passed << "/" << group->tests.size() << " tests";
        std::cerr << std::endl << std::endl;

        if (passed < group->tests.size()) errors++;
    }
    for (int i=0; i<45; i++) std::cerr << char(205);
    std::cerr << std::endl << std::endl;

    std::cerr << "There were errors in " << errors << " test group" << (errors==1?"":"s") << "." << (errors==0?" Congrats!":"") << std::endl;
}
