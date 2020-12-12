#pragma once
#include "func.h"

class KS_type
{
private:
	int id;
	static int sId;
public:

	//параметры
    std::string name;
	int workshop_number;
	int working_workshops;
	double effectiveness=0;

	//методы	
	void vvod();
	void edit();
	int get_id() const;
    void load(std::string load_string);
	KS_type();

};

std::ostream& operator<<(std::ostream&, const KS_type&);
std::ofstream& operator<<(std::ofstream&, const KS_type&);

