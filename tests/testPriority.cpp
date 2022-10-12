#include <iostream>
#include "log4shib/Priority.hh"

using namespace log4shib;

int main(int argc, char** argv) {
    
    std::cout << "priority debug(700): " << Priority::getPriorityName(700) << std::endl;
    std::cout << "priority debug(700): " << Priority::getPriorityValue("DEBUG") << std::endl;
    std::cout << "priority debug(700): " << Priority::getPriorityValue("700") << std::endl;
    try {
	std::cout << "priority debug(700): " << Priority::getPriorityValue("700arghh") << std::endl;
    } catch(std::invalid_argument& e) {
	std::cout << "caught " << e.what() << std::endl;
    }
    return 0;
}
