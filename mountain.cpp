#include "object.h"
#include "mountain.h"

using namespace std;
using namespace Siam;
using namespace Siam::Objects;

Mountain::Mountain()
		: Object() {

}

Mountain::Mountain( string nom, float force )
		: Object( nom, force ) {

}