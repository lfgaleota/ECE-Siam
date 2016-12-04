#include "../inc/object.hpp"
#include "../inc/objects/mountain.hpp"

//access via the namespaces
using namespace std;
using namespace Siam;
using namespace Siam::Objects;

Mountain::Mountain() //default constructor
		: Object() {

}

Mountain::Mountain( string nom, float force ) //overload constructor
		: Object( nom, force ) {

}

Types::Type Mountain::getType() const { //read access to type
	return Types::Type::Mountain;
}
