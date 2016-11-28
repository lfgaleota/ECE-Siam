#ifndef _ECE_SIAM_EXCEPTIONS_HPP_
	#define _ECE_SIAM_EXCEPTIONS_HPP_

	#include <stdexcept>
	#include <string>

	namespace Siam {
		namespace exceptions {
			#include "invalid_move"
			#include "invalid_object_type"
			#include "stack_empty"
			#include "stack_full"
		}
	}
#endif
