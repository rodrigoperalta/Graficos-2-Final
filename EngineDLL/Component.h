#pragma once
#include "Exports.h"
#include <string>


class ENGINEDLL_API Component{
protected:
	std::string name;

public:	
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;	
	std::string GetName() { return name; }
};