#ifndef _ECE_SIAM_EXCEPTIONS_HPP_
	#define _ECE_SIAM_EXCEPTIONS_HPP_

	#include <stdexcept>
	#include <string>

	namespace Siam {
		namespace exceptions { //exeptions inclusions
			#include "invalid_move"
			#include "invalid_object_type"
			#include "stack_empty"
			#include "stack_full"
			#include "exit_game"
			#include "cancel_action"
		}
	}
#endif
