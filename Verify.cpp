#include "Verify.h"

Verify::Verify() {
    //Begin rerouting stdout to a buffer
    old = std::cout.rdbuf(buffer.rdbuf());
}

Verify::~Verify() {
    std::cout.rdbuf( old );
}

std::string Verify::readBuf() {
    std::string s = buffer.str();
    buffer.clear();
    return s;
}

void Verify::test(std::string name, std::vector<Test> *tests) {
    groups.push_back({name, *tests});
}

void Verify::run() {
    for (std::vector<TestGroup>::iterator group = groups.begin(); group < groups.end(); group++) {

    }
}
