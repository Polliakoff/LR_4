#pragma once
#include "func.h"

class truba_type
{
private:
	int id;
	static int sId;
public:		

	//параметры
	std::string name;
	double length;
	double diameter;
	bool in_servise = false;	
    int connected = 0;
    double weight;
    double prop_sbosobn;
    double current_potok = 0;


	//методы
	void vvod();
	void edit();
	int get_id() const;
    void load(std::string load_string);
	truba_type();

};

std::ostream& operator<<(std::ostream&, const truba_type&);
std::ofstream& operator<<(std::ofstream&, const truba_type&);

