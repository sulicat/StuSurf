#ifndef TEST_H
#define TEST_H

#include "common.h"
#include <iostream>

class Test : public Base{
public:
	Test(){
		std::cout << "helow\n";
	}

	void render(){
		std::cout << "renderign TEST\n"; 
	}
};


#endif