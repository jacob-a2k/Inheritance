
#include <iostream>

class Passat {
	std::string name;
	double engine;
	char* colour;
	virtual std::ostream& print(std::ostream& output) const {
		return output << "(" << getName() << ", " << getEngine() << "tdi " << getColour() << ")\n";
	}
public:
	Passat(std::string n, double e,const char* c) : name(n), engine(e) {
		int size = std::strlen(c);
		colour = new char[size + 1];
		memcpy(colour, c, size);
		colour[size] = 0;
	}
	Passat(const Passat& passat) : Passat(passat.name, passat.engine, passat.colour) {}
	Passat& operator=(const Passat& passat) {
		name = passat.name;
		engine = passat.engine;
		delete [] colour;
		int size = std::strlen(passat.colour);
		colour = new char[size + 1];
		memcpy(colour, passat.colour, size);
		colour[size] = 0;

		return *this;
	}
	std::string getName() const {
		return name;
	}
	double getEngine() const {
		return engine;
	}
	char* getColour() const {
		return colour;
	}
	friend std::ostream& operator<<(std::ostream& output, const Passat& car);
};
std::ostream& operator<<(std::ostream& output, const Passat& passat) {
	return passat.print(output);
}

class PassatFL : public Passat {
	int speed;
	std::ostream& print(std::ostream& output) const {
		return output << "(" << getName() << ", " << getEngine() << "tdi, " << getColour() << ", " << getSpeed() << "km/h)\n";
	}
public:
	PassatFL(std::string n, double e, const char* c, int s) : Passat(n, e, c), speed(s) {}
	PassatFL(const Passat& passat, int s) : Passat(passat), speed(s) {}
	PassatFL(const PassatFL& passatFL) : PassatFL(passatFL, speed) {}
	PassatFL& operator=(const PassatFL& passatFL) {
		this->Passat::operator=(passatFL);
		this->speed = passatFL.speed;
		return *this;
	}
	int getSpeed() const {
		return speed;
	}
	friend std::ostream& operator<<(std::ostream& output, const PassatFL& passatFL);
};
std::ostream& operator<<(std::ostream& output, const PassatFL& passatFL) {
	return passatFL.print(output);
}
int main()
{
	Passat b5("Passat b5", 1.9,"Czarny");
	std::cout << b5 << "\n";
	PassatFL b5fl("Passat b5fl", 2.0,"Zielony", 210);
	std::cout << b5fl << "\n";

	Passat* car[3];
	car[0] = new Passat("kombi", 2.0,"Szary");
	car[1] = new PassatFL("sedan", 1.8,"Czerwony", 150);
	car[2] = new Passat("hatchback", 2.6,"Srebrny");

	car[1] = car[2];

	std::cout << std::endl;
	for (int i = 0; i < 3; i++) {
		std::cout << *car[i] << "\n";
	}
}