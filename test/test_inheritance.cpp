#include <stdio.h>
#include <iostream>



class PARENT{
public:
	int type;

	PARENT(){ std::cout << "making parent \n"; }

	virtual void print_dog(){
		std::cout << "dog \n";
	}


};




class CHILD_OWL : public PARENT{
public:
	int type;
	int x;

	CHILD_OWL(){
		x = 2;
		std::cout << "making OWL " << x << "  " << type << "\n";
	}

	void print_dog(){
		std::cout << "OWL OWL\n";	
	}

	void wow(){
		std::cout << "wooooooooooooooooooooooooooooooooow " << type << "\n";	
	}

};

int main( int argc, char * * argv ){
	

	PARENT * * p = new PARENT*[4];

	CHILD_OWL * c1 = new CHILD_OWL();
	p[0] = c1;

	c1->type = 5;
	c1->wow();



//	c1->print_dog();

/*	PARENT * p1 = new PARENT();
	p[2] = p1;
	p[3] = p1;
*/

	std::cout << "\n\n";


//	for( int i = 0; i < 4; i++ ){
//		p[i]->print_dog();
//
//	}

	return 0;
}