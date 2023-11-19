#pragma once
using namespace std;
#include <string>
#include<iostream>
#include <stdlib.h>
#include <time.h>

class Animal//Ќе можем создавать  обьекты абстрактного класса 
{
private:
	char* name;
public:
	Animal(const char* n)
	{
		name = new char[strlen(n) + 1];
		strcpy_s(name, strlen(n) + 1, n);
	}
	~Animal()
	{
		cout << "Destructor for Animal" << name;
		delete[]name;
	}
	virtual void Eat(Animal* prey) = 0;
	virtual int GetPower() = 0;
	virtual string toString() = 0;
	virtual bool isHerbivore() = 0;
	const char* GetName()
	{
		return name;
	}
};


class Herbivore : public Animal
{
	int weight;
	int maxWeight;
	bool isAlive = true;
public:
	Herbivore(const char* name, int weight, int maxWeight) : Animal(name), weight(weight), maxWeight(maxWeight) {}
	int GetWeight()
	{
		return weight;
	}
	int GetPower() {
		return weight;
	}
	string toString()
	{
		string result = GetName();
		result += ": weight=" + to_string(weight) + ", is alive=" + to_string(isAlive);
		return result;
	}
	virtual void Eat(Animal* prey)
	{
		cout  << endl << GetName() << " tries to eat...";
		if (!isAlive) {
			cout << " but too dead to eat :((";
			return;
		}

		int newWeight = weight + 10;
		if (newWeight <= maxWeight) {
			weight = newWeight;
		}
		else {
			weight = maxWeight;
		}
		cout << " and now has weight " << weight;
	}
	bool isHerbivore() {
		return true;
	}

};

class Bison : public Herbivore {
public:
	Bison() : Herbivore("Bison", 500, 800) {}
};

class Wildebeest : public Herbivore {
public:
	Wildebeest() : Herbivore("Wildebeest", 200, 300) {}
};


class Carnivore : public Animal
{
	int power;
public:
	Carnivore(const char* name, int power) : Animal(name), power(power) {}
	int GetPower()
	{
		return power;
	}
	string toString()
	{
		string result = GetName();
		result += ": power=" + to_string(power);
		return result;
	}
	virtual void Eat(Animal* prey) {
		cout << endl << GetName() << " tries to eat...";
		if (prey == 0) {
			cout << "but not found :(";
		}
		else {
			cout << " " << prey->GetName();
		}

		if (power > prey->GetPower()) {
			power += 10;
		}
		else {
			power -= 10;
		}
		cout << " and now has power " << power;
	}

	bool isHerbivore() {
		return false;
	}


};

class Wolf : public Carnivore {
public:
	Wolf() : Carnivore("Wolf", 350) {}
};

class Lion : public Carnivore {
public:
	Lion() : Carnivore("Lion", 550) {}
};


class Population
{
	Animal* animal;//ссылка(адрес(число)) на какое животного
	int count;
public:
	Population() = default;
	Population(Animal* animal, int count) :animal(animal), count(count) {}
	string toString()
	{
		string result = "Population: ";
		result += animal->GetName();
		result += " count=" + to_string(count);
		return result;
	}
	Animal* getAnimal() {
		return animal;
	}
	int getCount() {
		return count;
	}
	void setCount(int count) {
		this->count = count;
	}
};


class Continent
{
protected:
	Population* fauna = 0;
	int faunaSize = 0;
	int maxSize;
	char* name;
public:
	Continent(const char* n)  {
		name = new char[strlen(n) + 1];
		strcpy_s(name, strlen(n) + 1, n);
		maxSize = 10;
		fauna = new Population[10];
	}
	//~Continent() {
	//	cout << "Destructor for Continent " << name;
	//	delete[] name;
	//	delete[] fauna;
	//}
	virtual ~Continent() {
		delete[] fauna;
	}

	virtual void initFauna() = 0;

	void addPopulation(Population* newFauna)
	{
		if (faunaSize == maxSize) {
			Population* newFaunaArray = new Population[faunaSize + 10];
			for (int i = 0; i < faunaSize; i++)
			{
				newFaunaArray[i] = fauna[i];
			}
			delete[] fauna;
			fauna = newFaunaArray;
			faunaSize += 10;
		}
		fauna[faunaSize] = *newFauna;
		faunaSize++;
//		newFauna->getAnimal()->setContinent(this);
	}


	void Print() {
		cout << endl << "Fauna of " << name << ':' << endl;
		for (int i = 0; i < faunaSize; i++) {
			cout << "    " << fauna[i].toString() << endl;
		}
	}

	int getFaunaSize() {
		return faunaSize;
	}

	Population getFauna(int index) {
		return fauna[index];
	}

	char* getName() {
		return name;
	}


};

class America : public Continent {
public:
	America() : Continent("America") {}

	void initFauna() {
//		cout << "ENTER initFauna";

		Wolf* wolf = new Wolf();
		Population* wolfPop = new Population(wolf, 3);
		addPopulation(wolfPop);

		Bison* bison = new Bison();
		Population* bisonPop = new Population(bison, 2);
		addPopulation(bisonPop);

		Wildebeest* gnu = new Wildebeest();
		Population* gnuPop = new Population(gnu, 1);
		addPopulation(gnuPop);


//		cout << "EXIT initFauna";
	}
};

class Africa : public Continent {
public:
	Africa() : Continent("Africa") {}

	void initFauna() {
		//		cout << "ENTER initFauna";

		Lion* lion = new Lion();
		Population* lionPop = new Population(lion, 3);
		addPopulation(lionPop);

		
		Wolf* wolf = new Wolf();
		Population* wolfPop = new Population(wolf, 1);
		addPopulation(wolfPop);

		Wildebeest* gnu = new Wildebeest();
		Population* gnuPop = new Population(gnu, 4);
		addPopulation(gnuPop);


		//		cout << "EXIT initFauna";
	}
};

class AnimalWorld
{
	int day = 0;
	Continent* continents[2];
	int continetsSize = 2;

public:
	void initContinents() {
		America* america = new America();
		america->initFauna();
//		america->Print();
		continents[0] = america;

		Africa* africa = new Africa();
		africa->initFauna();
//		africa->Print();
		continents[1] = africa;
	}
	
	void PrintContinents() {
		for (int i = 0; i < continetsSize; i++) {
			continents[i]->Print();
		}
	}

	void passDay() {
		cout << endl << "Day " << day << " begins";
		CarnivoreNutrition();
		HerbivoreNutrition();
		PrintContinents();
		day++;
	}
	
	void HerbivoreNutrition() {
		for (int j = 0; j < continetsSize; j++) {
			Continent* c = continents[j];
			cout << endl<< "Herbivore events on continent " << c->getName() << ':';
			for (int i = 0; i < c->getFaunaSize(); i++) {
				Population p = c->getFauna(i);
				if (p.getCount() > 0 && p.getAnimal()->isHerbivore()) {
					p.getAnimal()->Eat(nullptr);
				}
			}
		}
	}
	
	void CarnivoreNutrition() {
		for (int j = 0; j < continetsSize; j++) {
			Continent* c = continents[j];
			cout << endl << "Carnivore events on continent " << c->getName() << ':';
			for (int i = 0; i < c->getFaunaSize(); i++) {
				Population p = c->getFauna(i);
				if (p.getCount() > 0 && !p.getAnimal()->isHerbivore()) {
					Population* prey = findPrey(c);
					if (prey != 0 && prey->getCount() > 0) {
						p.getAnimal()->Eat(prey->getAnimal());
						if (prey->getCount() > 0) {
							//cout << "-------------- count";
							prey->setCount(prey->getCount() - 1);
						}					
					}
				}
			}
		}

	}
	
	Population* findPrey(Continent* c) {
		for (int i = 0; i < c->getFaunaSize(); i++) {
			Population p = c->getFauna(i);
			if (p.getCount() > 0 && p.getAnimal()->isHerbivore()) {
				return &p;
			}
		}
		return nullptr;
	}
};







