#include <iostream>
#include <vector>
#include <string>

//#include <Helper.h>
class Buildings {
private:
    std::string type;
    int capacity;
    int costMoney;
    int costMaterials;
public:
    //constructor de initializare
    Buildings(const std::string& type, int capacity, int costMoney, int costMaterials) {
        //std::cout<<"Cladirea de tipul "<<type<<" a fost construita"<<" cu capacitatea de "<<capacity;
        this->type = type;
        this->capacity = capacity;
        this->costMoney = costMoney;
        this->costMaterials = costMaterials;
    }
    //constructor de copiere
    Buildings(const Buildings& other) {
        this->type = other.type;
        this->capacity = other.capacity;
        this->costMoney = other.costMoney;
        this->costMaterials = other.costMaterials;
        //std::cout << "Cladirea de tipul " << type << "  a fost copiata";
    }
    //operator=
    Buildings& operator=(const Buildings& other) {
        if (this != &other) {
            this->type=other.type;
            this->capacity=other.capacity;
            this->costMoney = other.costMoney;
            this->costMaterials = other.costMaterials;
            std::cout<<"Cladirea de tipul "<< type << " a fost atribuita";
        }
        return *this;
    }
    //deconstructor
    ~Buildings() {
        std::cout<<"Cladirea a fost demolata";
    }
    //getter
    std::string getType() const {
        return type;
    }

    int getCapacity() const {
        return capacity;
    }

    void setCapacity(int capacity) {
        if (capacity > 0)
            this->capacity = capacity;
    }

    int getcostMoney() const {
        return costMoney;
    }

    int getcostMaterials() const {
        return costMaterials;
    }

    void dailyProduction(int& money, int& materials) {
        if (type == "factory") {
            money += capacity * 2;
            materials += materials / 10;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Buildings& building) {
        os << "Building Type: " << building.type << ", Capacity: " << building.capacity
           << ", Cost: " << building.costMoney << "$ and " << building.costMaterials << " materials";
        return os;
    }
};
/*class Map {
private:
    int height;
    int width;
public:
    Map(int height, int width) {
        this->height = height;
        this->width = width;
    }
};*/
class Resources {
private:
    int money;
    int materials;
public:
    Resources(int money = 10000,int materials = 0) {
        this->money = money;
        this->materials = materials;
    }

    int getMoney() const {
        return money;
    }

    void setMoney(int money) {
        this->money = money;
    }

    int getMaterials() const {
        return materials;
    }

    bool sufficientResources(int money, int materials) const {
        return this->money >= money && this->materials >= materials;
    }
    void setMaterials(int materials) {
        this->materials = materials;
    }

    bool consumeResources(int money, int materials) {
        if (sufficientResources(money, materials)) {
            this->money -= money;
            this->materials -= materials;
            return true;
        }
        return false;
    }
    friend std::ostream& operator<<(std::ostream& os, const Resources& resources) {
        os << "Resources: " << resources.money << "$ money, "
           << resources.materials << " materials";
        return os;
    }
};
class City {
private:
    std::string name;
    int population;
    Resources resources;
    std::vector<Buildings*> buildings;
public:
    City(const std::string name, int population=0, const Resources& resources= Resources()) {
        this->name = name;
        this->population = population;
        this->resources = resources;
    }

    ~City() {
        for (Buildings* building : buildings) {
            delete building;
        }
    }

    Resources& getResources() {
        return resources;
    }

    std::string getName() const {
        return name;
    }

    int getPopulation() const {
        return population;
    }

    const std::vector<Buildings*>& getBuildings() const {
        return buildings;
    }

    bool addBuilding(Buildings* building) {
        if (!resources.consumeResources(building->getcostMoney(),building->getcostMaterials())) {
            std::cout<<"You don't have enough resources"<<std::endl;
            delete building;
            return false;
        }

        buildings.push_back(building);

        if (building->getType() == "house") {
            population += building->getCapacity();
            std::cout<<"Population increased by "<<building->getCapacity()<<" people"<<std::endl;
        }

        return true;
    }

    void displayCityInfo() const {
        std::cout << "=== Town " << name << " ===" << std::endl;
        std::cout << "Populaton: " << population << std::endl;
        std::cout <<"Resources: " << resources << std::endl;
        std::cout << "Number of buildings: " << buildings.size() << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const City& city) {
        os << "City: " << city.name << ", Population: " << city.population
           << ", Resources: " << city.resources << ", Buildings: " << city.buildings.size();
        return os;
    }
};
int main() {
    /*std::cout << "Hello, world!\n";
    std::array<int, 100> v{};
    int nr;
    std::cout << "Introduceți nr: ";*/
    /////////////////////////////////////////////////////////////////////////
    /// Observație: dacă aveți nevoie să citiți date de intrare de la tastatură,
    /// dați exemple de date de intrare folosind fișierul tastatura.txt
    /// Trebuie să aveți în fișierul tastatura.txt suficiente date de intrare
    /// (în formatul impus de voi) astfel încât execuția programului să se încheie.
    /// De asemenea, trebuie să adăugați în acest fișier date de intrare
    /// pentru cât mai multe ramuri de execuție.
    /// Dorim să facem acest lucru pentru a automatiza testarea codului, fără să
    /// mai pierdem timp de fiecare dată să introducem de la zero aceleași date de intrare.
    ///
    /// Pe GitHub Actions (bife), fișierul tastatura.txt este folosit
    /// pentru a simula date introduse de la tastatură.
    /// Bifele verifică dacă programul are erori de compilare, erori de memorie și memory leaks.
    ///
    /// Dacă nu puneți în tastatura.txt suficiente date de intrare, îmi rezerv dreptul să vă
    /// testez codul cu ce date de intrare am chef și să nu pun notă dacă găsesc vreun bug.
    /// Impun această cerință ca să învățați să faceți un demo și să arătați părțile din
    /// program care merg (și să le evitați pe cele care nu merg).
    ///
    /////////////////////////////////////////////////////////////////////////
    /*std::cin >> nr;
    /////////////////////////////////////////////////////////////////////////
    for(int i = 0; i < nr; ++i) {
        std::cout << "v[" << i << "] = ";
        std::cin >> v[i];
    }
    std::cout << "\n\n";
    std::cout << "Am citit de la tastatură " << nr << " elemente:\n";
    for(int i = 0; i < nr; ++i) {
        std::cout << "- " << v[i] << "\n";
    }
    ///////////////////////////////////////////////////////////////////////////
    /// Pentru date citite din fișier, NU folosiți tastatura.txt. Creați-vă voi
    /// alt fișier propriu cu ce alt nume doriți.
    /// Exemplu:
    /// std::ifstream fis("date.txt");
    /// for(int i = 0; i < nr2; ++i)
    ///     fis >> v2[i];
    ///
    ///////////////////////////////////////////////////////////////////////////
    ///                Exemplu de utilizare cod generat                     ///
    ///////////////////////////////////////////////////////////////////////////
    Helper helper;
    helper.help();
    ///////////////////////////////////////////////////////////////////////////*/
    /*Buildings f1("factory",50);
    std::cout<<std::endl;
    f1.setCapacity(-5);
    std::cout<<f1.getCapacity();
    std::cout<<std::endl;*/
    std::string cityName;
    std::cout<<"Introduce your city name: ";
    std::getline(std::cin,cityName);
    City myCity(cityName);
    std::cout<<"Welcome in "<<cityName<<" town"<<std::endl;
    std::cout<<"Your budget is currently "<<myCity.getResources().getMoney()<<"$"<<std::endl;
    std::cout<<"You have "<<myCity.getResources().getMaterials()<<" materials"<<std::endl;

    bool firstBuilding = true;
    bool gameRunning = true;

    while (gameRunning) {
        std::cout << "\n=== MENU ===" << std::endl;
        if (firstBuilding) {
            std::cout<<"Build your first house to populate the city!"<<std::endl;
            std::cout<<"In order to do that you'll have to buy some materials"<<std::endl;
        }

        std::cout << "1. Buy materials" << std::endl;
        std::cout << "2. Build" << std::endl;
        std::cout << "3. Show city info" << std::endl;
        std::cout << "0. Iesire" << std::endl;

        int choice;
        std::cout<<"Enter your choice: ";
        std::cin>>choice;

        switch (choice) {
            case 1:
                //std::cout<<"In order to buy materials you need 100$"<<std::endl;
                    //std::cout<<"You have "<<myCity.getResources().getMoney()<<"$"<<std::endl;
                        if (myCity.getResources().getMoney() >= 100) {
                            myCity.getResources().consumeResources(100,0);
                            myCity.getResources().setMaterials(myCity.getResources().getMaterials()+100);
                            std::cout<<"You bought 100 materials";
                        }
                        else {
                            std::cout<<"You don't have enough money";
                        }
                break;
            case 2: {
                std::cout << "1. House ($100, 50 materials)\n"
                          << "2. Factory ($200, 100 materials)\n"
                          << "0. Back\n"
                          << "Enter your choice: ";
                int buildingChoice;
                std::cin >> buildingChoice;
                if (buildingChoice == 1 || buildingChoice == 2) {
                        Buildings* newBuilding = (buildingChoice == 1)
                                                ? new Buildings("house", 10, 100, 50)
                                                : new Buildings("factory", 200, 200, 100);

                    bool success = myCity.addBuilding(newBuilding);
                    if (success && firstBuilding && buildingChoice == 1) {
                        firstBuilding = false;
                        std::cout << "Congratulations! You built your first house.\n";
                    }
                } else if (buildingChoice != 0) {
                    std::cout << "Invalid option.\n";
                }
                break;
            }
            case 3:
                myCity.displayCityInfo();
                break;
            case 0:
                std::cout<<"Goodbye! Thank you for playing the game"<<std::endl;
                gameRunning = false;
                break;
            default:
                std::cout<<"Invalid choice"<<std::endl;
                }
            }
            return 0;
        }
