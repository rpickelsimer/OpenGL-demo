#pragma once
#include <iostream>
class Stages
{

public:
	Stages();
	~Stages();

	void pentagon(float);
	void trapezoid(float);
	void triangle(float);
	void cube(float);
	void fog();
	void text(std::string, int, int);
	void lighting(float);
};

