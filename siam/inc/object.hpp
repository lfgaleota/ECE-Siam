#ifndef _ECE_SIAM_OBJECT_HPP_
	#define _ECE_SIAM_OBJECT_HPP_

	#include <vector>
	#include <string>
	#include "matrixs/direction.hpp"
	#include "objects/types/type.hpp"

	namespace Siam { //in the namespace Siam

		class Object { //mother class Object
			protected:
				std::string m_nom;
				float m_force;
				Siam::Matrixs::Direction m_direction;

			public:
				Object(); //default constructor
				Object( std::string nom, float force, Siam::Matrixs::Direction direction = Siam::Matrixs::Direction::Left ); //overload constructor
				virtual ~Object();

				float getForce(); //read access to strength of object

				Siam::Matrixs::Direction getDirection() const; //read access to direction of the object
				void setDirection( Siam::Matrixs::Direction direction ); //write access to direction of the object

				virtual Siam::Objects::Types::Type getType(); //gets type of object --> useful because classes will inherit of object
		};

	}
#endif
