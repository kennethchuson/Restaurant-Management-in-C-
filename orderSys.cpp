
//customer interface.

#include <iostream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include <numeric>
#include <cassert>
#include <vector>

using namespace std;

//-----------------------------------------------------------------------Linked list--------------------------------------------------------------------

//DLS List for combinational order data

//Create a node struct for the store, store_ID, store_cost, store_time, and store_KitchenID. Then we need next pointer and previous pointer to make a chain to assemble the doubly linked list.
struct node {
    string node_store;
    string node_store_ID;
    int node_store_cost;
    int node_store_time;
    int node_store_KitchenID;
    node *next;
    node *prev;
};

//Doubly linked list class
class DLS_list {
    
private:
    //to keep on track using first and last pointers. So this pointers tells which node goes first and which goes last.
    node *first;
    node *last;
public:
    //start with the nullptr bu using constructor. This works with starting create a node in the first place of a doubly linked list.
    DLS_list() {
        first = nullptr;
        last = nullptr;
    }
    //add data that store from the node.
    void add_list(int z, string x, int y, string w, int t) {
        node *n = new node;
        n->node_store_KitchenID = z;
        n->node_store = x;
        n->node_store_cost = y;
        n->node_store_ID = w;
        n->node_store_time = t;
        n->next = nullptr;
        n->prev = nullptr;
        
        //Check if the first is nullptr, then assign that node onto the first and last.
        if (first == nullptr) {
            first = last = n;
        }
        //Otherwise, go to the next iteration of a node to check if the previous node is actually exist. If you have more than 1 node.
        else {
            last->next = n;
            n->prev = last;
            last = n;
        }
    }
    //delete data from the node
    bool delete_list(string w) {
        node *curr = first;
        
        //Check if curr is not equals to pointer and if your current node what you actually deleted of what you looking for, then do the break statement.
        while (curr != nullptr) {
            if (curr->node_store_ID == w) {
                break;
            }
            //move of to the next of the curr.
            curr = curr->next;
        }
        
        //if curr is nullptr, then it does not function anything, so it returns to true.
        if (curr == nullptr) {
            return false;
        }
        //otherwise, if curr is in the first, then the first assigns to the next curr pointer.
        else {
            if (curr == first) {
                first = curr->next;
                //if first is not a nullptr. Then the first of a previous pointer is nullptr.
                if (first != nullptr) {
                    first->prev = nullptr;
                }
                //otherwise, the last will be a nullptr
                else {
                    last = nullptr;
                }
            }
            //check if the curr is last. Then, the last that assigns to curr using previous pointer and make a nullptr.
            else if (curr == last) {
                last = curr->prev;
                last->next = nullptr;
            }
            //if not, the curr next and previous pointer assigns to curr previous pointer. And the curr previous and points to the next and assigns the curr points the next pointer.
            else {
                curr->next->prev = curr->prev;
                curr->prev->next = curr->next;
            }
            //delete that curr of what you looking for.
            delete curr;
            
            //make a true if it works.
            return true;
        }
    }
    
    //remove all order and start the empty doubly linked list.
    void clear_list() {
        
        first = nullptr;
        last = nullptr;
        
    }
    
    //print the node on the list
    void print(ostream &out) {
        out << "Kitchen ID " << setw(25) << "ID" << setw(17) << "Items" << setw(13) << "Cost" << setw(14) << "Time" <<  endl;
        for (node *curr = first ; curr != nullptr; curr = curr->next) {
            out << curr->node_store_KitchenID << setw(25) << curr->node_store_ID << setw(17) << curr->node_store << setw(10) << "$" << curr->node_store_cost <<".00" << setw(10) << curr->node_store_time <<  endl;
        }
        out << setw(75) << "-----------          ----------" << endl;
        out << setw(52) << " Total:   $" << Total_Cost() << ".00" << setw(15) << "Total Time: " << Total_Time() << " minutes" <<  endl;
        
        //check if the code is way too big.
        if (Total_Cost() > 100) {
            out << setw(25) << "Looks like the cost is getting bigger!" << endl;
        }
    }
    
    //put curr into the text file.
    void printID(ofstream &out){
        for (node *curr = first ; curr != nullptr; curr = curr->next) {
            // If it's the last item on list, doesn't end line or else error loading //
            if(curr->next == nullptr){
                out << curr->node_store_KitchenID;
            }
            else{
                out << curr->node_store_KitchenID << endl;
            }
        }
    }
    
    //total order cost algorithm
    int Total_Cost() {
        int sum = 0;
        for (node *curr = first; curr != nullptr; curr = curr->next) {
            int list_cost =  curr->node_store_cost;
            sum += list_cost;
        }
        return sum;
    }
    
    //total time algorithm
    int Total_Time() {
        int sum = 0;
        for (node *curr = first; curr != nullptr; curr = curr->next) {
            int list_time = curr->node_store_time;
            sum += list_time;
        }
        return sum;
    }
    
    
    
};


class customer_interface {
    
protected:
    
    //Categorical order data
    //store food list
    string store_food_entree_one;
    string store_food_sides_one;
    
    //store drink list
    string store_drink_alcoholic_one;
    string store_drink_nonalcoholic_one;
    
    //store food data
    int store_food_entree_one_data;
    int store_food_sides_one_data;
    
    //store drink data
    int store_drink_alcoholic_one_data;
    int store_drink_nonalcoholic_one_data;
    
    //Combinational order data for DLS list
    int dollar_cost;
    string item_for_list;
    int dollar_cost_store;
    string item_for_list_store;
    string ID_item_for_list_store;
    string ID_item_for_list;
    int time_store;
    int ID_item_for_kitchenSys_store;
    
    //promo (Discount offers) variables
    bool promo_accept;
    bool promo_view;
    
    bool promo_accept_2;
    bool promo_view_2;
    
   
    
    
    
public:
    
    
    DLS_list l;
    
    
    //this will appear the default menu using start function.
    void start() {
        int choose_category;
        bool again = true;
        cout << setw(29) << " *  DEFAULT MENU   * " << endl;
        cout << "[0] Display Menu" << setw(22) << "[4] Display Order" << endl;
        cout << "[1] Add Food " << setw(24) << "[5] Submit Order" << endl;
        cout << "[2] Add Drink " << setw(22) << "[6] Clear Order" << endl;
        cout << "[3] Remove Order " << setw(24) << "[7] See Promo Orders" << endl;
        cout << endl;
        cout << "Enter Option: ";
        
        //check if you accept the promo offers
        if (promo_view == true) {
            cout << endl;
            cout << "Promo Message: Go to [Add Food] -> [Entrees] -> [CheeseBurger]" << endl;
            cout << "               Go to [Add Food] -> [Sides] -> [French Fries]" << endl;
            cout << "               Go to [Add Drink] -> [NonAlcoholic] -> [Grape Soda]" << endl;
        }
        
        if (promo_view_2 == true) {
            cout << endl;
            cout << "Promo Message: (Do 3 times) Go to [Add Drink] -> [Alcoholic] -> [Beer]" << endl;
        }
        
        //Enter option using switch statement.
        while (again == true) {
            while (!(cin >> choose_category)) {
                cout << endl;
                string_avoidance();
            }
            if (choose_category == 0) {
                cout << endl;
                showMenu();
                again = false;
            }
            else if (choose_category == 1 ) {
                cout << endl;
                Food();
                again = false;
            }
            else if (choose_category == 2) {
                cout << endl;
                Drink();
                again = false;
            }
            else if (choose_category == 3) {
                cout << endl;
                Remove_Order();
                again = false;
            }
            else if (choose_category == 4) {
                cout << endl;
                Display_Order();
                again = false;
            }
            else if (choose_category == 5) {
                cout << endl;
                Submit_order();
                again = false;
            }
            else if (choose_category == 6) {
                cout << endl;
                clear_it();
                again = false;
            }
            else if (choose_category == 7) {
                cout << endl;
                Promo();
                again = false;
            }
            else {
                cout << "Please select an existing option." << endl;
                again = true;
            }
            
        }
        
        
    }
    
    //make a promo function for discount price offers. If they want the discount.
    void Promo() {
        int accept;
        bool again = true;
        cout << "1.) Combine 1 Cheese Burger, 1 French Fries, & 1 Grape Soda!" << endl;
        cout << "The total will be $18.00, versus $26.00 without the promotion." << endl;
        cout << "[1] Accept Offer" << endl;
        cout << "[2] Decline Offer and Return to Main Menu" << endl;
        cout << endl;
        cout << "2.) Combine 3 Beers!" << endl;
        cout << "The total will be $15.00, versus $27.00 without the promotion." << endl;
        cout << "[3] Accept Offer" << endl;
        cout << "[4] Decline Offer and Return to Main Menu" << endl;
        cout << endl;
        cout << "Enter Option: ";
        while (again == true) {
            while (!(cin >> accept)) {
                cout << endl;
                string_avoidance();
            }
            if (accept == 1) {
                again = false;
                promo_accept = true;
                promo_view = true;
            }
            else if (accept == 2) {
                start();
                again = false;
                promo_accept = false;
            }
            else if (accept == 3) {
                again = false;
                promo_accept_2 = true;
                promo_view_2 = true;
            }
            else if (accept == 4) {
                start();
                again = false;
                promo_accept_2 = false;
            }
            else {
                cout << "Please select an existing option." << endl;
                again = true;
                promo_accept = false;
                promo_accept_2 = false;
            }
        }
        cout << endl;
        start();
    }
    
    //if the person that should not enter a string, then this will print out the warning without executing out of the program.
    void string_avoidance() {
        
        cout << "------------WARNING-------------"<< endl;
        cout << " * String or Char is not allowed here * "<< endl;
        cout << "--------------------------------" << endl;
        cout << "Please re-enter a choice." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    //if you want to clear your orders and redo them.
    void clear_it() {
        l.clear_list();
        cout << "Your order has been cleared!" << endl;
        start();
    }
    
    //show the menu display function.
    void showMenu() {
        string returnShowMenu;
        cout << setw(40) << " *  MENU   * " << endl;
        cout << setw(14) << "FOOD" << setw(41) << "DRINK";
        cout << endl;
        //cout << "--------------------------------------------------------------------";
        //cout << endl;
        cout << setw(16) << "[Entrees]" << setw(42) << "[Alcoholic]";
        cout << endl;
        cout << setw(22) << "* Cheese Burger - $12.00" << setw(31) << "* Beer - $9.00";
        cout << endl;
        cout << setw(21) << "* Ham Burger - $15.00" << setw(42) << "* Screwdriver - $15.00";
        cout << endl;
        cout << setw(22) << "* Chicken Sandwich - $14.00" << setw(39) << "* Lemonade Vodka - $10.00";
        cout << endl;
        cout << setw(22) << "* Chicken Nuggets - $9.00" << setw(42);
        cout << endl;
        cout << endl;
        cout << setw(14) << "[Sides]" << setw(46) << "[Non Alcoholic]";
        cout << endl;
        cout << setw(22) << "* French Fries - $6.00" << setw(38) << "* Cola Soda - $8.00";
        cout << endl;
        cout << setw(15) << "* Salad - $7.00" << setw(47) << "* Orange Soda - $9.00";
        cout << endl;
        cout << setw(19) << "* Macaroni - $11.00" << setw(42) << "* Grape Soda - $8.00";
        cout << endl;
        cout << setw(56) << "* Water - $4.00";
        cout << endl;
        cout << setw(59) << "* Lemonade - $5.00";
        cout << endl;
        //cout << "--------------------------------------------------------------------";
        cout << endl;
        start();
        
    }
    
    
    //show the restaurant title
    void showWelcome() {
        for (int i = 0; i < 40; i++) {
            cout << "-";
        }
        cout << endl;
        
        cout << "           THE BURGER SHOT           " << endl;
        
        
        for (int i = 0; i < 40; i++) {
            cout << "-";
        }
        cout << endl;
    }
    
    
    
    
    //food section
    void Food() {
        int choose_food_option;
        bool again = true;
        cout << "Food Options: " << endl;
        cout << "[1] Entrees " << endl;
        cout << "[2] Sides " << endl;
        cout << "[3] Return" << endl;
        cout << "Enter Option: ";
        
        
        //Use switch statement to decide if they want food entree or sides.
        while (again == true) {
            while (!(cin >> choose_food_option)) {
                cout << endl;
                string_avoidance();
            }
            switch (choose_food_option) {
                case 1:
                    Food_Entress();
                    again = false;
                case 2:
                    Food_Sides();
                    again = false;
                case 3:
                    start();
                    again = false;
                    break;
                default:
                    cout << "please select an existing option.." << endl;
                    again = true;
                    break;
            }
        }
    }
    
    
        
    //Food entree section
    void Food_Entress() {
        int choose_food_entree;
        bool again = true;
        int ID_forKitchen;
        cout << endl;
        cout << "Food Entrees: " << endl;
        cout << "[1] Cheese Burger " << endl;
        cout << "[2] Ham Burger" << endl;
        cout << "[3] Chicken Sandwich" << endl;
        cout << "[4] Chicken Nuggets" << endl;
        cout << "[5] Return " << endl;
        cout << "Enter Option: ";
        
        //assign string
        string food_name_entree;
        
        //data assign number order
        int food_data_entree;
        
        int food_data_entree_time;
        
        //use switch statement to choose your food entree.
        
        while (again == true) {
            while (!(cin >> choose_food_entree)) {
                cout << endl;
                string_avoidance();
            }
            switch (choose_food_entree) {
                case 1:
                    food_name_entree = "Cheese burger";
                    item_for_list = "Cheese burger";
                    ID_item_for_list = "FECB";
                    dollar_cost = 12;
                    food_data_entree = 1;
                    if (promo_accept == true) {
                        dollar_cost = 10;
                    }
                    food_data_entree_time = 2;
                    ID_forKitchen = 1;
                    again = false;
                    break;
                case 2:
                    food_name_entree = "Ham Burger";
                    item_for_list = "Ham Burger";
                    ID_item_for_list = "FEHB";
                    dollar_cost = 15;
                    food_data_entree = 2;
                    again = false;
                    food_data_entree_time = 2;
                    ID_forKitchen = 2;
                    break;
                case 3:
                    food_name_entree = "Chicken Sandwich";
                    item_for_list = "Chicken Sandwich";
                    ID_item_for_list = "FECS";
                    dollar_cost = 14;
                    food_data_entree = 3;
                    food_data_entree_time = 3;
                    ID_forKitchen = 3;
                    again = false;
                    break;
                case 4:
                    food_name_entree = "Chicken Nuggets";
                    item_for_list = "Chicken Nuggets";
                    ID_item_for_list = "FECN";
                    dollar_cost = 9;
                    food_data_entree = 4;
                    food_data_entree_time = 2;
                    ID_forKitchen = 4;
                    again = false;
                    break;
                case 5:
                    start();
                    again = false;
                default:
                    cout << "please select an existing items. " << endl;
                    again = true;
                    break;
            }
        }
        
        //this will communicate and send orders to the linked list.
        store_food_entree_one = food_name_entree;
        store_food_entree_one_data = food_data_entree;
        
        item_for_list_store = item_for_list;
        dollar_cost_store = dollar_cost;
        
        ID_item_for_list_store = ID_item_for_list;
        
        time_store = food_data_entree_time;
        
        ID_item_for_kitchenSys_store = ID_forKitchen;
        
        l.add_list(ID_item_for_kitchenSys_store, item_for_list_store, dollar_cost_store, ID_item_for_list_store, time_store);
        
        cout << endl;
        start();
        
    }
    
    //Food Sides section
    void Food_Sides() {
        int choose_food_sides;
        bool again = true;
        //assign string
        string food_name_sides;
        
        //data assign number order
        int food_data_sides;
        
        int food_data_sides_time;
        
        int ID_forKitchen;
        
        cout << endl;
        cout << "Food Sides: " << endl;
        cout << "[1] French Fries" << endl;
        cout << "[2] Salad " << endl;
        cout << "[3] Macaroni " << endl;
        cout << "[4] Return " << endl;
        cout << "Enter Option: ";
       
        
        //use switch statement to choose food sides
        
        while (again == true) {
            while (!(cin >> choose_food_sides)) {
                cout << endl;
                string_avoidance();
            }
            switch (choose_food_sides) {
                case 1:
                    food_name_sides = "French Fries";
                    item_for_list = "French Fries";
                    ID_item_for_list = "FSFF";
                    dollar_cost = 6;
                    food_data_sides = 5;
                    if (promo_accept == true) {
                        dollar_cost = 4;
                    }
                    food_data_sides_time = 1;
                    ID_forKitchen = 5;
                    again = false;
                    break;
                case 2:
                    food_name_sides = "Salad";
                    item_for_list = "Salad";
                    ID_item_for_list = "FSS";
                    dollar_cost = 7;
                    food_data_sides = 6;
                    food_data_sides_time = 1;
                    ID_forKitchen = 6;
                    again = false;
                    break;
                case 3:
                    food_name_sides =  "Macaroni";
                    item_for_list = "Macaroni";
                    ID_item_for_list = "FSM";
                    dollar_cost = 11;
                    food_data_sides = 7;
                    food_data_sides_time = 1;
                    ID_forKitchen = 7;
                    again = false;
                    break;
                case 4:
                    start();
                    again = false;
                default:
                    cout << "please select an existing items. " << endl;
                    again = true;
                    break;
            }
        }
        
        //this will communicate and send orders to the linked list.
        store_food_sides_one = food_name_sides;
        store_food_sides_one_data = food_data_sides;
        
        item_for_list_store = item_for_list;
        dollar_cost_store = dollar_cost;
        
        ID_item_for_list_store = ID_item_for_list;
        
        time_store = food_data_sides_time;
        
        ID_item_for_kitchenSys_store = ID_forKitchen;
        
        l.add_list(ID_item_for_kitchenSys_store, item_for_list, dollar_cost_store, ID_item_for_list_store, time_store);
        
        cout << endl;
        start();
        
    }
    //drink section
    void Drink() {
        int choose_food_option;
        bool again = true;
        cout << "Drink Option: " << endl;
        cout << "[1] Alcholoic " << endl;
        cout << "[2] NonAlcoholic " << endl;
        cout << "[3] Return" << endl;
        
       // cin >> choose_food_option;
        
        
        //choose either alcoholic or nonalcoholic
        while (again == true) {
            while (!(cin >> choose_food_option)) {
                cout << endl;
                string_avoidance();
            }
          switch (choose_food_option) {
            case 1:
                Drink_Alcoholic();
                again = false;
            case 2:
                Drink_Non_Alcoholic();
                  again = false;
            case 3:
                start();
                  again = false;
                break;
            default:
                cout << "please select an existing option.." << endl;
                  again = true;
                break;
            }
        }
        
               
    }
    
    //acoholic drink function
    void Drink_Alcoholic() {
        int choose_drink_aloholic;
        bool again = true;
        cout << "Alcoholic drink: " << endl;
        cout << "[1] Beer " << endl;
        cout << "[2] Screwdriver" << endl;
        cout << "[3] Lemonade Vodka" << endl;
        cout << "[4] Return " << endl;
        
        //assign string
        string drink_name_alcholic;
        
        //data assign number order
        int  drink_name_alcholic_data;
        
        int drink_name_alcholic_data_time;
        
        int ID_forKitchen;
        
       
        //decide what alchoholic drink you want
        while (again == true) {
            while (!(cin >> choose_drink_aloholic)) {
                cout << endl;
                string_avoidance();
            }
            switch (choose_drink_aloholic) {
                case 1:
                    drink_name_alcholic = "Beer";
                    item_for_list = "Beer";
                    ID_item_for_list = "AAB";
                    dollar_cost = 9;
                    drink_name_alcholic_data = 8;
                    again = false;
                    if (promo_accept_2 == true) {
                        dollar_cost = 5;
                    }
                    drink_name_alcholic_data_time = 2;
                    ID_forKitchen = 13;
                    break;
                case 2:
                    drink_name_alcholic = "Screwdriver";
                    item_for_list= "Screwdriver";
                    ID_item_for_list = "AAS";
                    dollar_cost = 15;
                    drink_name_alcholic_data = 9;
                    drink_name_alcholic_data_time = 1;
                    ID_forKitchen = 14;
                    again = false;
                    break;
                case 3:
                    drink_name_alcholic = "Lemonade Vodka";
                    item_for_list = "Lemonade Vodka";
                    ID_item_for_list = "AALV";
                    dollar_cost = 10;
                    drink_name_alcholic_data = 10;
                    drink_name_alcholic_data_time = 1;
                    ID_forKitchen = 15;
                    again = false;
                    break;
                case 4:
                    start();
                    again = false;
                    break;
                default:
                    cout << "please select an existing items. " << endl;
                    again = true;
                    break;
            }
        }
        
        //this will communicate and send orders to the linked list.
        store_drink_alcoholic_one = drink_name_alcholic;
        store_drink_alcoholic_one_data = drink_name_alcholic_data;
        
        item_for_list_store = item_for_list;
        dollar_cost_store = dollar_cost;
        
        ID_item_for_list_store = ID_item_for_list_store;
        
        time_store = drink_name_alcholic_data_time;
        
        ID_item_for_kitchenSys_store = ID_forKitchen;
        
        l.add_list(ID_item_for_kitchenSys_store, item_for_list, dollar_cost_store, ID_item_for_list_store, time_store);
        
        
        start();
    }
    
    //nonalcoholic drink function
    void Drink_Non_Alcoholic() {
        int choose_drink_nonalcoholic;
        bool again = true;
        int drink_name_nonalcoholic_data_time;
        
        cout << "nonAlcoholic drink: " << endl;
        cout << "[1] Cola Soda" << endl;
        cout << "[2] Orange Soda" << endl;
        cout << "[3] Grape Soda" << endl;
        cout << "[4] Water" << endl;
        cout << "[5] Lemonade" << endl;
        cout << "[6] return" << endl;
        
        //assign string
        string drink_name_nonalcoholic;
        
        //data assign number order
        int  drink_name_nonalcoholic_data;
        
        int ID_forKitchen;
        
       // cin >> choose_drink_nonalcoholic;
        
        //decide what nonalcoholic drink you want
        while (again == true) {
            while (!(cin >> choose_drink_nonalcoholic)) {
                cout << endl;
                string_avoidance();
            }
            switch (choose_drink_nonalcoholic) {
                case 1:
                    drink_name_nonalcoholic = "Cola Soda";
                    item_for_list = "Cola Soda";
                    ID_item_for_list = "ANCS";
                    dollar_cost = 8;
                    drink_name_nonalcoholic_data = 11;
                    again = false;
                    drink_name_nonalcoholic_data_time = 1;
                    ID_forKitchen = 8;
                    break;
                case 2:
                    drink_name_nonalcoholic = "Orange Soda";
                    item_for_list = "Orange Soda";
                    ID_item_for_list = "ANOS";
                    dollar_cost = 9;
                    drink_name_nonalcoholic_data = 12;
                    drink_name_nonalcoholic_data_time = 1;
                    ID_forKitchen = 9;
                    again = false;
                    break;
                case 3:
                    drink_name_nonalcoholic = "Grape Soda";
                    item_for_list = "Grape Soda";
                    ID_item_for_list = "ANGS";
                    dollar_cost = 8;
                    drink_name_nonalcoholic_data = 13;
                    if (promo_accept == true) {
                        dollar_cost = 4;
                    }
                    drink_name_nonalcoholic_data_time = 1;
                    ID_forKitchen = 10;
                    again = false;
                    break;
                case 4:
                    drink_name_nonalcoholic = "Water";
                    item_for_list = "Water";
                    ID_item_for_list = "ANW";
                    dollar_cost = 4;
                    drink_name_nonalcoholic_data = 14;
                    drink_name_nonalcoholic_data_time = 1;
                    ID_forKitchen = 11;
                    again = false;
                    break;
                case 5:
                    drink_name_nonalcoholic = "Lemonade";
                    item_for_list = "Lemonade";
                    ID_item_for_list = "ANL";
                    dollar_cost = 5;
                    drink_name_nonalcoholic_data = 15;
                    drink_name_nonalcoholic_data_time = 1;
                    ID_forKitchen = 12;
                    again = false;
                case 6:
                    start();
                    again = false;
                    break;
                default:
                    cout << "please select an existing items. " << endl;
                    again = true;
                    break;
            }
        }
        
        //this will communicate and send orders to the linked list.
        store_drink_nonalcoholic_one = drink_name_nonalcoholic;
        store_drink_nonalcoholic_one_data = drink_name_nonalcoholic_data;
        
        item_for_list_store = item_for_list;
        dollar_cost_store = dollar_cost;
        
        ID_item_for_list_store = ID_item_for_list;
        
        time_store = drink_name_nonalcoholic_data_time;
        
        ID_item_for_kitchenSys_store = ID_forKitchen;
        
        l.add_list(ID_item_for_kitchenSys_store, item_for_list, dollar_cost_store, ID_item_for_list_store, time_store);
        
        start();
    }
    
    //applicants to move which order do you want
    void Remove_Order() {
        string name_remove;
        cout << "Enter what ID to remove your order." << endl;
        cin >> name_remove;
        l.delete_list(name_remove);
        start();
    }
    
// TABLING SYSTEM //
// using vectors instead of linked lists, so we can directly access any point without iterating through the structure.

class Table {
public:
    int ID;
    int orders;
    Table(int number) {
        this->ID = number; // use 'this' to refer back to data member in class Table.
    }
};

vector<Table> table;

void addTable() {
    cout << "Which table would you like to sit at?" << endl;
    cout << "To add to an existing table, enter your original table number." << endl;
    int addTab;
    cin >> addTab;
    bool exists = false; // initialization
    for (int i = 0; i < table.size(); i++) {
        if (table[i].ID == addTab) { // if index of table ID already exists,
            table[i].orders++; // add order to this table
            exists = true;
            break;
        }
    }
    if (exists == false) { // if it doesn't exist,
        Table* a = new Table(addTab); // create a new table
    a->orders++; // add order to new table
    table.push_back(*a); // push back into vector
    }
    
    cout << endl;
    cout << "Table " << addTab << "'s Receipt:" << endl;
    Display_Order();
}

    //Submit that order to the kitchen System
    void Submit_order() {
        //Save order onto the text file.
        string file_name = "store_order_system.txt";
        ofstream out_file;
        out_file.open(file_name.c_str());
        l.print(out_file);
        out_file.close();
        
        // ADDED BY NATHAN //
        ofstream stock;
        stock.open("idnum.txt");
        l.printID(stock);
        stock.close();
        
        cout << "Saved to the " << file_name << endl;
        cout << "Your order is now sent to the Kitchen." << endl;
        cout << endl;
        
        cout << "Would you like your order for here, or to go?" << endl;
        cout << "[1] For Here" << endl;
        cout << "[2] To Go" << endl;
        int tableChoice;
        cin >> tableChoice;
        
        switch (tableChoice) {
            case 1: 
                addTable();
                break;
            case 2:
                Display_Order();
                cout << "Here is your order. Hope you enjoy your meal!" << endl;
                break;
        }
    }
    
    //Display your order. The Display from the Doubly Linked List
    void Display_Order() {
        l.print(cout);
        cout << endl;
        start();
    }
    
    
};




int main() {
    customer_interface c;
    
    c.showWelcome();
    
    c.start();
    
    return 0;
}

