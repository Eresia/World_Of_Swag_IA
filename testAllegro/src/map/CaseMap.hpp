#ifndef CASE_MAP
#define CASE_MAP

	#include <iostream>
	#include <string>
	#include <vector>
	#include <algorithm>
	#include "object/ObjectMap.hpp"
	#include "object/TypeObject.hpp"
	#include "Material.hpp"
	#include "../usefull/Usefull.hpp"
	#include "../exception/BadMapObjectException.hpp"

	class CaseMap{

	private:
		std::vector<ObjectMap> objects;
		Material material;

	public:
	    CaseMap();
		void setMaterial(Material material);
		void addObject(TypeObject object);
		void removeObject(ObjectMap object);
	};

#endif
