#include "../inc/object.hpp"
#include "../inc/objects/mountain.hpp"

using namespace std;
using namespace Siam;
using namespace Siam::Objects;

Mountain::Mountain()
		: Object() {

}

Mountain::Mountain( string nom, float force )
		: Object( nom, force ) {

}

Types::Type Mountain::getType() {
	return Types::Type::Mountain;
}