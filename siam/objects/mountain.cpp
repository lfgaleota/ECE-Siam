#include "../inc/object.hpp"
#include "../inc/objects/mountain.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Objects;

Mountain::Mountain() //default constructor
		: Object() {

}

Mountain::Mountain( string nom, float force ) //overload constructor
		: Object( nom, force ) {

}

Types::Type Mountain::getType() { //read access to type
	return Types::Type::Mountain;
}
