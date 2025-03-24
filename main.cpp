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

    int maintenance() const {
        return (capacity * 5) + (costMoney / 10);
    }
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
    //destructor
    ~Buildings() {
        //std::cout<<"The building was destroyed";
    }
    //getter
    const std::string& getType() const {
        return type;
    }

    int getCapacity() const {
        return capacity;
    }

    /*void setCapacity(int capacity) {
        if (capacity > 0)
            this->capacity = capacity;
    }*/

    int getcostMoney() const {
        return this->costMoney;
    }

    int getcostMaterials() const {
        return this->costMaterials;
    }

    /*void dailyProduction(int& money, int& materials) {
        if (type == "factory") {
            money += capacity * 2;
            materials += materials / 10;
        }
    }*/

    friend std::ostream& operator<<(std::ostream& os, const Buildings& building) {
        os << "Building Type: " << building.type << ", Capacity: " << building.capacity
           << ", Cost: " << building.costMoney << "$ and " << building.costMaterials << " materials";
        return os;
    }

    void showMaintenance() const {
        std::cout<<"Maintenance for "<<type<<": "<< maintenance()<<"$ per month"<<std::endl;
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
    explicit Resources(int money = 10000,int materials = 0) {
        this->money = money;
        this->materials = materials;
    }

    int getMoney() const {
        return this->money;
    }

    /*void setMoney(int money) {
        this->money = money;
    }*/

    int getMaterials() const {
        return this->materials;
    }

    bool sufficientResources(int nmoney, int nmaterials) const {
        return this->money >= nmoney && this->materials >= nmaterials;
    }
    void setMaterials(int newmaterials) {
        this->materials = newmaterials;
    }

    bool consumeResources(int cmoney, int cmaterials) {
        if (sufficientResources(cmoney, cmaterials)) {
            this->money -= cmoney;
            this->materials -= cmaterials;
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

    int totalMaintenance() const {
        int total = 0;
        for (const auto* const building : buildings) {
            total += (building->getCapacity() * 5) + (building->getcostMoney() / 10);
        }
        return total;
    }

    void checkCityStatus() const {
        if (population == 0) {
            std::cout << "Warning: Your city is empty! Build more houses to attract people." << std::endl;
        }
        if (resources.getMoney() < 500) {
            std::cout << "Warning: Low funds! Manage your resources wisely." << std::endl;
        }
    }
public:
    explicit City(const std::string& name, int population=0, const Resources& resources= Resources()) {
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

    /*std::string getName() const {
        return name;
    }*/

    /*int getPopulation() const {
        return population;
    }
*/
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

        if (building->getType() == "factory") {
            std::cout<<"A factory was built"<<std::endl;
        }

        checkCityStatus();
        return true;
    }

    void displayCityInfo() const {
        std::cout << "=== Town " << name << " ===" << std::endl;
        std::cout << "Populaton: " << population << std::endl;
        std::cout <<"Resources: " << resources << std::endl;
        std::cout << "Number of buildings: " << buildings.size() << std::endl;
        std::cout << "Total monthly maintenance: " << totalMaintenance() << "$" << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const City& city) {
        os << "City: " << city.name << ", Population: " << city.population
           << ", Resources: " << city.resources << ", Buildings: " << city.buildings.size();
        return os;
    }
};
int main() {
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
        std::cout << "4. Show maintenace"<<std::endl;
        std::cout << "0. Exit" << std::endl;

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
            case 4:
                std::cout << "Building Maintenance Costs:" << std::endl;
                for (const auto* building : myCity.getBuildings()) {
                    building->showMaintenance();
                }
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
