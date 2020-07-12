// MUST ADD STOCK FIRST IN ORDER TO MAKE A FOOD //
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <iomanip>
using namespace std;


class stock{
protected:
    string stockName;
    int numStock;
    int minStock;
    
public:
    void searchStock(int x);
    void displayStock();
    
    // FUNCTIONS NEEDED FOR FOOD CLASS //
    void showName();
    void warnStock();
        
    void addStock();
    void deleteStock();
    void emptyStock();
    
    void editStock();
    void reStock();
    void subtStock();
    
    void saveStock();
    void loadStock();
};

list<stock> listOfStock;
list<stock>::iterator it1;


// STOCK //
void stock::searchStock(int input){
    it1 = listOfStock.begin();
    
    for (int i = 1; i < input; i++){
        ++it1;
    }
}

void stock::displayStock(){
    int x = 1;
    if(listOfStock.size() == 0){
        cout << "No stock items added yet." << endl;
    }
    else{
        for (it1 = listOfStock.begin(); it1 != listOfStock.end(); ++it1){
            cout << x << ". "<< it1->stockName << ": " << it1->numStock << endl;
            x++;
        }
    }
    cout << endl;
}

void stock::showName(){
    cout << it1->stockName << endl;
}

void stock::warnStock(){
    if(it1->numStock <= it1->minStock){
        cout << "WARNING " << it1->stockName << " IS LOW ON STOCK." << endl;
    }
    else{
    }
}



//

void stock::addStock(){
    string name;
    int input;
    stock ex;
    
    cout << "What item would you like to add to your stock?" << endl;
    cin >> name;
    ex.stockName = name;
    
    cout << "What is the minimum stock levels for " << ex.stockName << endl;
    cin >> input;
    ex.minStock = input;
    
    cout << "How much " << ex.stockName << " do you have in inventory?" << endl;
    cin >> input;
    ex.numStock = input;
    
    cout << ex.stockName << " has been added with " << ex.numStock << " in inventory." << endl;
    
    cout << endl;
    listOfStock.push_back(ex);
}

void stock::deleteStock(){
    int input;
    
    do{
        cout << "Which stock item would you like to delete?" << endl;
        cout << "Enter [-1] to view options." << endl;
        cin >> input;
    
        if(input == -1){
            displayStock();
        }
        else if(input > listOfStock.size()){
            cout << "Invalid Option." << endl;
            cout << endl;
        }
        
        else {
            searchStock(input);
            cout << it1->stockName << " deleted." << endl;
            listOfStock.erase(it1);
            cout << endl;
            break;
        }
    }
    while(true);
}

void stock::emptyStock(){
    stockName = "";
    numStock = 0;
    minStock = 0;
}


void stock::editStock(){
    string name;
    int x;
    int input;
    int input2;
    
    do{
        cout << "Which stock item would you like to edit?" << endl;
        cout << "Enter [-1] to view options." << endl;
        cin >> input;
    
        if(input == -1){
            displayStock();
        }
        else if(input > listOfStock.size()){
            cout << "Invalid Option." << endl;
        }
        
        else{
            searchStock(input);
            
            cout << "What would you like to edit about " << it1->stockName << "?" << endl;
            cout << "[1] Name" << endl;
            cout << "[2] Minimum Stock Level" << endl;
            cin >> input2;
            
            switch (input2) {
                case 1:
                    cout << "What would you like to change the name to?" << endl;
                    cin >> name;
                    it1->stockName = name;
                    cout << "Name changed to " << it1->stockName << "." << endl;
                    break;
                
                case 2:
                    cout << "What would you like to change the minimum stock level to?" << endl;
                    cin >> x;
                    it1->minStock = x;
                    cout << it1->stockName << " minimum stock level now " << it1->minStock << "." << endl;
                    break;
                    
                default:
                    cout << "Invalid Option." << endl;
                    
            }
            
            break;
        }
    }
    while(true);
}

void stock::reStock(){
    int input;
    int x;
    
    do{
        cout << "Which stock item would you like to restock?" << endl;
        cout << "Enter [-1] to view options" << endl;
        cin >> input;
        
        if(input == -1){
            displayStock();
        }
        else if(input > listOfStock.size()){
            cout << "Invalid Option." << endl;
        }
        else{
            cout << "What would you like to change the stock level to?" << endl;
            cin >> x;
            it1->numStock = x;
            cout << it1->stockName << " stock level now " << it1->numStock << "." << endl;
            break;
        }
    }
    while(true);
}

void stock::subtStock(){
    it1->numStock = it1->numStock - 1;
}


void stock::saveStock(){
    ofstream mySave;
    mySave.open("stock.txt");
    int x = 1;
    
    for (it1 = listOfStock.begin(); it1 != listOfStock.end(); ++it1){
        // If it's the last item of the list, it doesn't end with an endline otherwise there will be an error loading. //
        if(x == listOfStock.size()){
            mySave << it1->stockName << endl;
            mySave << it1->minStock << endl;
            mySave << it1->numStock;
        }
        else{
            mySave << it1->stockName << endl;
            mySave << it1->minStock << endl;
            mySave << it1->numStock << endl;
        }
        x++;
    }
    mySave.close();
}

void stock::loadStock(){
    ifstream myLoad;
    myLoad.open("stock.txt");
    stock ex;
    string line;
    int num;

    if (myLoad.is_open()) {
        while (!myLoad.eof()) {
            myLoad >> line;
            ex.stockName = line;
            
            myLoad >> num;
            ex.minStock = num;
            
            myLoad >> num;
            ex.numStock = num;
            
            listOfStock.push_back(ex);
        }
    }
    myLoad.close();
}

// END STOCK //




class food
{
    friend class stock;
    
protected:
    string foodName;

    int numIng;
    int ing1;
    int ing2;
    int ing3;
    int ing4;

public:
    food(){
        foodName = "";
        ing1 = 0;
        ing2 = 0;
        ing3 = 0;
        ing4 = 0;
    };
    
    void string_avoidance();
    void searchFood(int x);
    void displayFoods();
    
    void addFood();
    void deleteFood();
    void editFood();
    void emptyFood();
    
    void showIngs();
    void displayIng();
    void editIng();
    void deleteIng();
    void subtIng();
    
    void saveFood();
    void loadFood();
};

list<food> listOfFood;
list<food>::iterator it2;

// FOOD //

void food::string_avoidance(){
    cout << "------------WARNING-------------"<< endl;
    cout << " * String or Char is not allowed here * "<< endl;
    cout << "--------------------------------" << endl;
    cout << "Please re-enter a choice." << endl << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void food::searchFood(int input){
    it2 = listOfFood.begin();
    
    for (int i = 1; i < input; i++){
        ++it2;
    }
}

void food::displayFoods(){
    int x = 1;
    if(listOfFood.size() == 0){
        cout << "No food items added yet." << endl;
    }
    else{
        for (it2 = listOfFood.begin(); it2 != listOfFood.end(); ++it2){
            cout << x << ". "<< it2->foodName << endl;
            x++;
        }
    }
    cout << endl;
}



void food::addFood(){
    string name;
    int input;
    int input2;
    food ex;
    stock ea;
    
    cout << "What food would you like to add?" << endl;
    cin >> name;
    ex.foodName = name;
   
    do{
        cout << "How many ingredients are needed to make this?" << endl;
        if (!(cin >> input)){
            string_avoidance();
        }
        else{
            ex.numIng = input;
            break;
        }
    }
    while(true);

    
    while(input != 0){
        cout << "What ingredients are needed to make this?" << endl;
        cout << "Enter [-1] to view options." << endl;
        cout << "Enter [-2] to add later/finished." << endl;
        cin >> input2;
        if (input2 == -1){
            ea.displayStock();
        }
        else if (input2 == -2){
            input = 0;
        }
        else if (input2 > listOfStock.size()){
            cout << "Invalid Option." << endl;
        }
        
        else if (ex.ing1 == 0){
            ex.ing1 = input2;
            cout << endl;
            input--;
        }
        else if (ex.ing2 == 0){
            ex.ing2 = input2;
            cout << endl;
            input--;
        }
        else if (ex.ing3 == 0){
            ex.ing3 = input2;
            cout << endl;
            input--;
        }
        else if (ex.ing4 == 0){
            ex.ing4 = input2;
            cout << endl;
            input--;
        }
    };

    cout << endl;
    listOfFood.push_back(ex);
}

void food::deleteFood(){
    int input;
    
    do{
        cout << "Which food item would you like to delete?" << endl;
        cout << "Enter [-1] to view options." << endl;
        cin >> input;
    
        if(input == -1){
            displayFoods();
            }
        else if(input > listOfFood.size()){
            cout << "Invalid Option." << endl;
            cout << endl;
        }
        else{
            searchFood(input);
            cout << it2->foodName << " deleted." << endl;
            listOfFood.erase(it2);
            cout << endl;
            break;
        }
    }
    while(true);
}

void food::editFood(){
    int input;
    string name;
    do{
        cout << "Which food item would you like to edit?" << endl;
        cout << "Enter [-1] to view options." << endl;
        cin >> input;
        
        if(input == -1){
            displayFoods();
            }
        else if(input > listOfFood.size()){
            cout << "Invalid Option." << endl;
            cout << endl;
        }
        
        else{
            searchFood(input);
            cout << "What would you like to edit about " << it2->foodName << "?" << endl;
            cout << "[1] Name" << endl;
            cout << "[2] Ingredients" << endl;
            cin >> input;
            
            if(input == 1){
                cout << "What would you like the name to be?" << endl;
                cin >> name;
                it2->foodName = name;
                cout << "Name changed to " << it2->foodName << "." << endl;
                break;
            }
            else if(input == 2){
                editIng();
                break;
            }
            else{
                cout << "Invalid Option." << endl << endl;
            }
        }
    }
    while(true);
}

void food::emptyFood(){
    foodName = "";
    numIng = 0;
    ing1 = 0;
    ing2 = 0;
    ing3 = 0;
    ing4 = 0;
}


void food::showIngs(){
    stock ex;
    if(it2->numIng == 0){
        cout << "No ingredients found for " << it2->foodName << "." << endl;
    }
    
    else{
        cout << it2->foodName << " ingredients:" << endl;

        // please change if you find/know a better way LOL //

        int y = 1;
        if (it2->ing1 != 0){
            int x = it2->ing1;
            
            ex.searchStock(x);
            cout << y << ". ";
            ex.showName();
            y++;
            
            if (it2->ing2 != 0){
                x = it2->ing2;
                
                ex.searchStock(x);
                cout << y << ". ";
                ex.showName();
                y++;
                
                if (it2->ing3 != 0){
                    x = it2->ing3;
                    
                    ex.searchStock(x);
                    cout << y << ". ";
                    ex.showName();
                    y++;
                    
                    if (it2->ing4 != 0){
                        x = it2->ing4;
                        
                        ex.searchStock(x);
                        cout << y << ". ";
                        ex.showName();
                        y++;
                    }
                }
            }
        }
    }
    cout << endl;
}

void food::displayIng(){
    int input;
    
    do{
        cout << "Which food item would you like to view the ingredients for?" << endl;
        cout << "Enter [-1] to view options." << endl;
        cin >> input;
        
        if(input == -1){
            displayFoods();
        }
        else if(input > listOfFood.size()){
            cout << "Invalid Option." << endl;
            cout << endl;
            break;
        }
        else{
            searchFood(input);
            showIngs();
            break;
        }
    }
    while(true);
}

void food::editIng(){
    int input;
    stock ex;
    do{
        cout << "Which food item would you like to edit the ingredients for?" << endl;
        cout << "Enter [-1] to view options." << endl;
        cin >> input;
        
        if(input == -1){
            displayFoods();
        }
        else if(input > listOfFood.size()){
            cout << "Invalid Option." << endl;
            cout << endl;
            break;
        }
        
        else{
            searchFood(input);
            
            cout << "Which ingredient would you like to edit for " << it2->foodName << "?" << endl;
            showIngs();
            int input2;
            cin >> input2;

            // STARTS MODIFICATION OF INGREDIENT //
            do{
                cout << "What would you like to change it to?" << endl;
                cout << "Enter [-1] to view options." << endl;
                cout << "Enter [-2] to add later/finished." << endl;
                int ing;
                cin >> ing;
                
                if (ing == -1){
                    ex.displayStock();
                }
                else if (ing == -2){
                    break;
                }
                
                else{
                    switch(input2){
                        case 0:
                            it2->ing1 = ing;
                            break;
                            
                        case 1:
                            it2->ing2 = ing;
                            break;
                            
                        case 2:
                            it2->ing3 = ing;
                            break;
                            
                        case 3:
                            it2->ing4 = ing;
                            break;
                    }
                    break;
                }
            }
            while(true);
            break;
        }
    }
    while(true);
}

void food::deleteIng(){
    int input;
    
    do{
        cout << "Which food item would you like to delete the ingredient for?" << endl;
        cout << "Enter [-1] to view options." << endl;
        cin >> input;
        
        if(input == -1){
            displayFoods();
        }
        else if(input > listOfFood.size()){
            cout << "Invalid option" << endl;
            cout << endl;
            break;
        }
        
        else{
            searchFood(input);
            
            cout << "Which ingredient would you like to delete?" << endl;
            showIngs();
            int input2;
            cin >> input2;
           
            switch(input2){
                case 0:
                    it2->ing1 = it2->ing2;
                    it2->ing2 = it2->ing3;
                    it2->ing3 = it2->ing4;
                    it2->ing4 = 0;
                    break;
                   
                case 1:
                    it2->ing2 = it2->ing3;
                    it2->ing3 = it2->ing4;
                    it2->ing4 = 0;
                    break;
                   
                case 2:
                    it2->ing3 = it2->ing4;
                    it2->ing4 = 0;
                    break;
                   
                case 3:
                    it2->ing4 = 0;
                    break;
           }
           break;
        }
    }
    while(true);
}

// NEED SEARCH FOOD FIRST //
void food::subtIng(){
    stock ex;
    
    if(it2->ing1 != 0){
        int x = it2->ing1;
        ex.searchStock(x);
        ex.subtStock();
        ex.warnStock();
        
        if(it2->ing2 != 0){
            x = it2->ing2;
            ex.searchStock(x);
            ex.subtStock();
            ex.warnStock();
            
            if(it2->ing3 != 0){
                x = it2->ing3;
                ex.searchStock(x);
                ex.subtStock();
                ex.warnStock();
                
                if(it2->ing4 != 0){
                    x = it2->ing4;
                    ex.searchStock(x);
                    ex.subtStock();
                    ex.warnStock();
                }
            }
        }
    }
    
}

void food::saveFood(){
    ofstream mySave;
    mySave.open("food.txt");
    int x = 1;
    
    for (it2 = listOfFood.begin(); it2 != listOfFood.end(); ++it2){
        // If it's the last item of the list, it doesn't end with an endline otherwise there will be an error loading. //
        if(x == listOfFood.size()){
            mySave << it2->foodName << endl;
            mySave << it2->numIng << endl;
            mySave << it2->ing1 << endl;
            mySave << it2->ing2 << endl;
            mySave << it2->ing3 << endl;
            mySave << it2->ing4;
        }
        else{
            mySave << it2->foodName << endl;
            mySave << it2->numIng << endl;
            mySave << it2->ing1 << endl;
            mySave << it2->ing2 << endl;
            mySave << it2->ing3 << endl;
            mySave << it2->ing4 << endl;
        }
        x++;
    }
    mySave.close();
}

void food::loadFood(){
    ifstream myLoad;
    myLoad.open("food.txt");
    food ex;
    string line;
    int num;

    if (myLoad.is_open()) {
        while (!myLoad.eof()) {
            myLoad >> line;
            ex.foodName = line;
            
            myLoad >> num;
            ex.numIng = num;
            
            myLoad >> num;
            ex.ing1 = num;
            
            myLoad >> num;
            ex.ing2 = num;
            
            myLoad >> num;
            ex.ing3 = num;
            
            myLoad >> num;
            ex.ing4 = num;
            listOfFood.push_back(ex);
        }
    }
    myLoad.close();
}

// END FOOD CLASS //


class kitchenSystem{
    friend class stock;
    friend class food;
private:

public:
    void displayStatus();
    void displayOrders();
};


void kitchenSystem::displayStatus(){
    int input;
    
    do{
        cout << "IN PROGRESS" << endl;
        cout << "Enter [1] to make current order ready." << endl;
        //cout << timer << endl;
        cin >> input;
    }
    while (input != 1);
    //pop from queue and .changeStatus on customer interface ???//
    cout << "ORDER READY" << endl;
    //.updateCustomer
}



void kitchenSystem::displayOrders() {
    ifstream myReadFile;
    myReadFile.open("store_order_system.txt");
    //memory management store
    char output[1000000];
    
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> output;
            cout << output << endl;
        }
    }
    myReadFile.close();

    // SUBTRACT FOOD FUNC //
    ifstream stockFile;
    stockFile.open("idnum.txt");
    int x;
    food foods;

    if(stockFile.is_open()){
        while(!stockFile.eof()){
            stockFile >> x;
            foods.searchFood(x);
            foods.subtIng();
        }
    }
    stockFile.close();
}


// drinks //
// subtract func from file from order sys //
int main() {
    stock ex;
    food foods;
    kitchenSystem kitchen;
    
    int input;
    int sub;
    
    ex.loadStock();
    foods.loadFood();
    do{
        cout << setw(52) << " *  DEFAULT MENU   * " << endl;
        cout << "[0] Kitchen System Order" << setw(16) << "[1] Add Food" << setw(34) << "[2] Display Food" << endl;
        cout << setw(42) << "[11] Add Stock" << setw(34) << "[22] Display Stock" << endl << endl;
        cout << "[3] Delete Food" << setw(36) << "[4] Display Ingredients" << setw(22) << "[5] Modify Food" << endl;
        cout << "[33] Delete Stock" << setw(45) << setw(58) << "[55] Modify Stock" << endl;
        cout << setw(71) << "[555] Restock" << endl << endl;
        cout << "[6] Delete Ingredient" << setw(15) << "[7] Exit" << endl;
        cout << setw(41) << "[77] Subtract" << endl;
        cout << setw(38) << "[777] Save" << endl;
        cin >> input;
        cout << endl;
        
        switch (input) {
            case 0:
                kitchen.displayOrders();
                break;
                
            case 1:
                foods.addFood();
                foods.emptyFood();
                break;
                
            case 11:
                ex.addStock();
                ex.emptyStock();
                break;
                
            case 2:
                foods.displayFoods();
                break;
                
            case 22:
                ex.displayStock();
                break;
                
            case 3:
                foods.deleteFood();
                break;
                
            case 33:
                ex.deleteStock();
                break;
            
            case 4:
                foods.displayIng();
                break;
            
            case 5:
                foods.editFood();
                break;
                
            case 55:
                ex.editStock();
                break;
            
            case 555:
                ex.reStock();
                break;
                
            case 6:
                foods.deleteIng();
                break;
                
            case 7:
                break;
                
            case 77:
                cout << "Which food would you like to subtract?" << endl;
                cin >> sub;
                foods.searchFood(sub);
                foods.subtIng();
                break;
            
            case 777:
                cout << "Saved." << endl;
                ex.saveStock();
                foods.saveFood();
                break;
                
            default:
                cout << "Select Valid Option." << endl;
                break;
        }
    }
    while(input != 7);
}

// Which stock item(s) does this food use?

//searchstock
//subting


