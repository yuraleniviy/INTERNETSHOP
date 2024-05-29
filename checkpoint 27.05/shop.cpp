#include <iostream>
#include <fstream>
using namespace std;

//                          ALL DECLARATIONS
//CLASS
class product {
    private:
        string name;
        string descr;
    public:
        int cost;
        static inline product * arr[100]; // for writing
        static inline int i = 0; //counter i
        int t; // type
        product(int cost, string name, string descr);
        product(){}
        ~product(){};
        virtual void input();
        virtual void print();
        virtual void read(int readcount, fstream & file);
};

class furniture : public product{
    private:
        string material;
        string color; 
        int size_x;
        int size_y;
    public:
        furniture():product(){}
        furniture (int cost, string name, string descr, string material, string color, int size_x, int size_y);
        virtual ~furniture(){};
        virtual void input();
        virtual void print();
};

class clothes : public product {
    private:
        string gender;
        string size;
    public:
        clothes() : product(){}
        clothes(int cost, string name, string descr, string gender, string size);
        virtual ~clothes(){};
        virtual void print();
        virtual void input();
};

class shirt : public clothes {
    private:
        string color;
        string material;
    public:
        shirt (int cost, string name, string descr, string gender, string size, string color, string material);
        shirt(): clothes(){};
        virtual ~shirt(){}
        virtual void input();
        virtual void print();
        virtual void read(int readcount, fstream & file);
};

class belt : public clothes {
    private:
        string color;
        string isDouble;
    public:
        belt (int cost, string name, string descr, string gender, string size, string color, string isDouble);
        belt(): clothes() {};
        virtual ~belt(){};
        virtual void input();
        virtual void print();
        virtual void read(int readcount, fstream & file);
};

class chair : public furniture {
    private:
        bool isBack;
        bool isSoft;
    public:
        chair(int cost, string name, string descr, string material, string color, int size_x, int size_y, bool isBack, bool isSoft);
        chair():furniture(){}
        virtual ~chair(){};
        virtual void input();
        virtual void print();
        virtual void read(int readcount, fstream & file);
};

class table : public furniture {
    private:
        bool isMutable;
    public:
        table (int cost, string name, string descr, string material, string color, int size_x, int size_y, bool isMutable);
        table():furniture(){};
        virtual void input();
        virtual ~table(){};
        virtual void print();
        virtual void read(int readcount, fstream & file);
};

class busket {
public:
    static inline product * cart[100];
    static inline int numofThings = 0;
    static inline int totalcost = 0;
    busket(){};
    ~busket(){};
    void printThings();
    void printTotalCost();
    void addThings();
    void removeThings();
};

//GLOBAL VARIABLES
string adress = "D:\\ProgramFiles\\VSCode\\INTERNET SHOP\\INTERNET SHOP - working\\basket.bin";
busket maincart;
int readcount = 0;

//OUT-OF-CLASS FUNCTIONS
void inputstr(string line){
    fstream file;
    file.open(adress, ios::app | ios::binary);
    const char* charArray = line.c_str();
    int size = line.size() + 1;
    file.write(reinterpret_cast<const char*>(&size), sizeof(size));
    file.write(charArray,size);
    file.close();
}
string outputstr(fstream & file){
    int sizeread;
    file.read(reinterpret_cast<char*>(&sizeread), sizeof(sizeread));
    char* buffer = new char[sizeread];
    file.read(buffer,sizeread); // reading the array
    string line(buffer); //convertion srom array of char to srting
    delete[] buffer;
    return line;
}
void addtostorage(){
    for (int k=0; k<product::i; k++){
        (*product::arr[k]).input();
    }
}
void AfterProductsMenu(){
    int AfterProductsMenu_choose = 0;
    while (AfterProductsMenu_choose!=3){
        cout<<endl;
        cout<<"|   CHOOSE   |"<<endl;
        cout<<"1. Open Cart"<<endl;
        cout<<"2. Add to Cart"<<endl;
        cout<<"3. Go Back"<<endl<<endl;
        cout<<"Enter: ";
        cin>>AfterProductsMenu_choose;
        switch(AfterProductsMenu_choose){
            case 1:{
                maincart.printThings();
                break;
            }
            case 2:{
                maincart.addThings();
                break;
            }
            default: break;
        }
    }
}

//CONSTRUCTORS
product::product(int cost, string name, string descr){
        this->t = 0;
        this->cost = cost;
        this->name = name;
        this->descr = descr;
        arr[i] = this;
        i++;
    }
furniture::furniture (int cost, string name, string descr, string material, string color, int size_x, int size_y) : product (cost, name, descr){
        this->material = material;
        this->color = color;
        this->size_x = size_x;
        this->size_y = size_y;
    }
clothes::clothes(int cost, string name, string descr, string gender, string size) : product (cost, name, descr){
        this->gender = gender;
        this->size = size;
        this->t=10;
}
shirt::shirt (int cost, string name, string descr, string gender, string size, string color, string material) : clothes (cost, name, descr, gender, size){
        this->color = color;
        this->material = material;
        this->t = 11;
    }
belt::belt (int cost, string name, string descr, string gender, string size, string color, string isDouble) : clothes (cost, name, descr, gender, size){
        this->color = color;
        this->isDouble = isDouble;
        this->t=12;
}
chair::chair(int cost, string name, string descr, string material, string color, int size_x, int size_y, bool isBack, bool isSoft) : furniture (cost, name, descr, material, color, size_x, size_y){
    this->isBack = isBack;
    this->isSoft = isSoft;
    this->t = 21;
}
table::table (int cost, string name, string descr, string material, string color, int size_x, int size_y, bool isMutable) : furniture (cost, name, descr, material, color, size_x, size_y){
    this->isMutable = isMutable;
    this->t = 22;
}

//PRINT
void product::print() {
    cout<<"Name: "<<this->name<<endl;
    cout<<"Price: "<<this->cost<<endl;
    cout<<"Description: "<<this->descr<<endl;
}
void furniture::print(){
    product::print();
    cout<<"Material: "<< this->material <<endl;
    cout<<"Color: "<< this->color <<endl;
    cout<<"Length: "<< this->size_x <<endl;
    cout<<"Width: "<< this->size_y <<endl;
}
void clothes::print(){
            product::print();
            cout<<"Sex: "<<this->gender<<endl;
            cout<<"Size: "<<this->size<<endl;
} 
void shirt::print(){
            clothes::print();
            cout<<"Color: "<< this->color <<endl;
            cout<<"Material: "<< this->material <<endl;
} 
void belt::print(){
    clothes::print();
    cout<<"Color: "<< this->color <<endl;
    cout<<"Is double: "<< this->isDouble <<endl;
} 
void chair::print(){
    furniture::print();
    cout<<"Back: "<< this->isBack <<endl;
    cout<<"Soft: "<< this->isSoft <<endl;
} 
void table::print(){
    furniture::print();
    cout<<"Mutable: "<< this->isMutable <<endl;
} 

//READ
void product::read(int readcount, fstream & file){ 
        arr[readcount] = new product();
        file.read(reinterpret_cast<char*>(&arr[readcount]->cost), sizeof(int));
        outputstr(file); //name
        outputstr(file); //descr
}
void shirt::read(int readcount, fstream & file){
        int t_cost;
        file.read(reinterpret_cast<char*>(&t_cost), sizeof(int));
        string t_name;
        string t_descr;
        string t_gender;
        string t_size;
        string t_color;
        string t_material;
        // cout << "shirt read" << endl;
        t_name = outputstr(file);
        t_descr = outputstr(file);
        t_gender  = outputstr(file);
        t_size = outputstr(file);
        t_color = outputstr(file);
        t_material = outputstr(file);
        arr[readcount] = new shirt(t_cost, t_name, t_descr, t_gender, t_size, t_color, t_material);
}
void belt::read(int readcount, fstream & file){
    int t_cost;
    file.read(reinterpret_cast<char*>(&t_cost), sizeof(int));
    string t_name;
    string t_descr;
    string t_gender;
    string t_size;
    string t_color;
    string is_double;
    // cout << "belt read" << endl;
    t_name = outputstr(file);
    t_descr = outputstr(file);
    t_gender  = outputstr(file);
    t_size = outputstr(file);
    t_color = outputstr(file);
    is_double = outputstr(file);
    arr[readcount] = new belt(t_cost, t_name, t_descr, t_gender, t_size, t_color, is_double);
}
void chair::read(int readcount, fstream & file){
    int t_cost;
    file.read(reinterpret_cast<char*>(&t_cost), sizeof(int));
    string t_name;
    string t_descr;
    string t_material;
    string t_color;
    t_name = outputstr(file);
    t_descr = outputstr(file);
    t_material = outputstr(file);
    t_color = outputstr(file);
    int t_size_x;
    file.read(reinterpret_cast<char*>(&t_size_x), sizeof(int));
    int t_size_y;
    file.read(reinterpret_cast<char*>(&t_size_y), sizeof(int));
    bool t_is_back;
    file.read(reinterpret_cast<char*>(&t_is_back), sizeof(bool));
    bool t_is_soft;
    file.read(reinterpret_cast<char*>(&t_is_soft), sizeof(bool));
    arr[readcount] = new chair(t_cost, t_name, t_descr, t_material, t_color, t_size_x, t_size_y, t_is_back, t_is_soft) ;
}
void table::read(int readcount, fstream & file){
    int t_cost;
    file.read(reinterpret_cast<char*>(&t_cost), sizeof(int));
    string t_name;
    string t_descr;
    string t_material;
    string t_color;
    //cout << "table read" << endl;
    t_name = outputstr(file);
    t_descr = outputstr(file);
    t_material = outputstr(file);
    t_color = outputstr(file);
    int t_size_x;
    file.read(reinterpret_cast<char*>(&t_size_x), sizeof(int));
    int t_size_y;
    file.read(reinterpret_cast<char*>(&t_size_y), sizeof(int));
    bool t_is_mutable;
    file.read(reinterpret_cast<char*>(&t_is_mutable), sizeof(bool));
    arr[readcount] = new table(t_cost, t_name, t_descr, t_material, t_color, t_size_x, t_size_y, t_is_mutable) ;
}

//INPUT
void product::input(){
    fstream file;
    file.open(adress, ios::app | ios::binary);
    file.write(reinterpret_cast<char*>(&this->t),sizeof(int));
    file.write(reinterpret_cast<char*>(&this->cost),sizeof(int));
    file.close();
    inputstr(this->name);
    inputstr(this->descr);
}
void furniture::input(){
    if (t<=20) {t = 20;};
    product::input();
    fstream file;
    inputstr(this->material);
    inputstr(this->color);
    file.open(adress, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "OPENING FAILURE" << endl;
    }
    else {
        file.write(reinterpret_cast<char*>(&this->size_x),sizeof(int));
        file.write(reinterpret_cast<char*>(&this->size_y),sizeof(int));
    }
    file.close();
}
void clothes::input(){
    if (this->t<=10) {this->t = 10;};
    product::input();
    inputstr(this->gender);
    inputstr(this->size);
}
void shirt::input(){
    clothes::input();
    inputstr(this->color);
    inputstr(this->material);
}
void belt::input(){
    clothes::input();
    inputstr(this->color);
    inputstr(this->isDouble);
}
void chair::input(){
    furniture::input();
    fstream file;
    file.open(adress, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "OPENING FAILURE" << endl;
    }
    else {
        file.write(reinterpret_cast<char*>(&this->isBack),sizeof(bool));
        file.write(reinterpret_cast<char*>(&this->isSoft),sizeof(bool));
    }
    file.close();
}
void table::input(){
    furniture::input();
    fstream file;
    file.open(adress, ios::app | ios::binary);
    if (!file.is_open()) {
        cout << "OPENING FAILURE" << endl;
    }
    else {
        file.write(reinterpret_cast<char*>(&this->isMutable),sizeof(bool));
    }
    file.close();
}

//BUSKET FUNCTIONS
void busket::addThings(){
    int position;
    cout<<"Enter position you want to add: ";
    cin>>position;
    cart[numofThings]=product::arr[position-1];
    totalcost+=cart[numofThings]->cost;
    switch(cart[numofThings]->t){
        case 11:{cout<<" SHIRT added successfully!!"<<endl;break;}
        case 12:{cout<<" BELT added successfully!!"<<endl;break;}
        case 21:{cout<<" CHAIR added successfully!!"<<endl;break;}
        case 22:{cout<<" TABLE added successfully!!"<<endl;break;}
    }
    numofThings++;
    //system("pause");
};
void busket::printThings(){
    if (numofThings==0){
        cout<<"No items in YOUR CART. You should add first!!"<<endl;
    }
    else{
        cout<<"|    Your Cart    |"<<endl<<endl;
        for (int k=0; k<numofThings; k++){
            if (cart[k]->t!=0){
                switch(cart[k]->t){
                    case 11:{cout<<k+1<<") SHIRT----------------------"<<endl;break;}
                    case 12:{cout<<k+1<<") BELT----------------------"<<endl;break;}
                    case 21:{cout<<k+1<<") CHAIR----------------------"<<endl;break;}
                    case 22:{cout<<k+1<<") TABLE----------------------"<<endl;break;}
                }
                cart[k]->print();
                cout<<endl;
            }
        }
            maincart.printTotalCost();
            cout<<endl;
            int removeORnot;
            cout<<"If you want to remove something, ENTER 7. If not - any other number: ";
            cin>>removeORnot;
            if (removeORnot==7) {maincart.removeThings();};
    }
    system("pause");
};
void busket::printTotalCost(){
    cout<<endl;
    cout<<"TOTAL: $"<< totalcost << endl;
};
void busket::removeThings(){
    int position;
    cout<<"Enter position you want to remove: ";
    cin>>position;
    totalcost-=cart[position-1]->cost;
    switch(cart[position-1]->t){
        case 11:{cout<<" SHIRT removed successfully!!"<<endl;break;}
        case 12:{cout<<" BELT removed successfully!!"<<endl;break;}
        case 21:{cout<<" CHAIR removed successfully!!"<<endl;break;}
        case 22:{cout<<" TABLE removed successfully!!"<<endl;break;}
    }
    //numofThings--;
    cart[position-1]->t=0; //set t=0 to check if its deleted from cart
    //system("pause");
};

int main(){
    int ShopMode;
    int AdminMode;
    int CustomerMode;
    while (ShopMode!=3){
        system("cls");
        cout<<"--- SHOP ---"<<endl;
        cout<<"1. ADMIN MODE"<<endl;
        cout<<"2. CUSTOMER MODE"<<endl;
        cout<<"3. Exit"<<endl<<endl;
        cout<<"Enter: ";
        cin>>ShopMode;
        fstream file;
        switch (ShopMode){
            //ADMIN MODE
            case 1:{ 
                AdminMode = 0;
                while (AdminMode!=5){
                    system("cls");
                    cout<<"|       ADMIN       |"<<endl<<endl;
                    cout<<"1. Add Shirt"<<endl;
                    cout<<"2. Add Belt"<<endl;
                    cout<<"3. Add Chair"<<endl;
                    cout<<"4. Add Table"<<endl;
                    cout<<"5. Save changes"<<endl<<endl<<"Enter: ";
                    cin>>AdminMode;
                    system("cls");
                    switch (AdminMode){
                        //add shirt
                        case 1:{
                            int cost_of_shirt;
                            string name_of_shirt;
                            string descr_of_shirt;
                            string sex_of_shirt;
                            string size_of_shirt;
                            string color_of_shirt; 
                            string material_of_shirt;
                            cout<<"---NEW SHIRT---"<< endl << "Name: ";
                            cin>>name_of_shirt;
                            cout<<"Price: ";
                            cin>>cost_of_shirt;
                            cout<<"Description: ";
                            cin>>descr_of_shirt;
                            cout<<"Sex: ";
                            cin>>sex_of_shirt;
                            cout<<"Size: ";
                            cin>>size_of_shirt;
                            cout<<"Color: ";
                            cin>>color_of_shirt;
                            cout<<"Material: ";
                            cin>>material_of_shirt;
                            product* t = new shirt(cost_of_shirt, name_of_shirt, descr_of_shirt, sex_of_shirt, size_of_shirt, color_of_shirt, material_of_shirt);
                            break;
                            delete(t);
                        }
                        //add belt
                        case 2:{
                            int cost_b;
                            string name_b;
                            string descr_b;
                            string sex_b;
                            string size_b;
                            string color_b; 
                            string is_double;
                            cout<<"---NEW BELT---"<< endl << "Name: ";
                            cin>>name_b;
                            cout<<"Price: ";
                            cin>>cost_b;
                            cout<<"Description: ";
                            cin>>descr_b;
                            cout<<"Sex: ";
                            cin>>sex_b;
                            cout<<"Size: ";
                            cin>>size_b;
                            cout<<"Color: ";
                            cin>>color_b;
                            cout<<"Is double (yes/no): ";
                            cin>>is_double;
                            product* t = new belt(cost_b, name_b, descr_b, sex_b, size_b, color_b, is_double);
                            break;
                            delete(t);
                        }
                        //add chair
                        case 3:{
                            int cost_c;
                            string name_c;
                            string descr_c;
                            string material_c;
                            string color_c;
                            int size_x_c;
                            int size_y_c;
                            bool is_back_c;
                            bool is_soft_c;
                            cout<<"---NEW CHAIR---"<< endl << "Name: ";
                            cin>>name_c;
                            cout<<"Price: ";
                            cin>>cost_c;
                            cout<<"Description: ";
                            cin>>descr_c;
                            cout<<"Material: ";
                            cin>>material_c;
                            cout<<"Color: ";
                            cin>>color_c;
                            cout<<"Length: ";
                            cin>>size_x_c;
                            cout<<"Width: ";
                            cin>>size_y_c;
                            cout<<"Back (0/1): ";
                            cin>>is_back_c;
                            cout<<"Soft (0/1): ";
                            cin>>is_soft_c;
                            product* t = new chair(cost_c, name_c, descr_c, material_c, color_c, size_x_c, size_y_c, is_back_c, is_soft_c);
                            break;
                            delete(t);
                        }
                        //add table
                        case 4:{
                            int cost_c;
                            string name_c;
                            string descr_c;
                            string material_c;
                            string color_c;
                            int size_x_c;
                            int size_y_c;
                            bool is_mutable_c;
                            cout<<"---NEW TABLE---"<< endl << "Name: ";
                            cin>>name_c;
                            cout<<"Price: ";
                            cin>>cost_c;
                            cout<<"Description: ";
                            cin>>descr_c;
                            cout<<"Material: ";
                            cin>>material_c;
                            cout<<"Color: ";
                            cin>>color_c;
                            cout<<"Length: ";
                            cin>>size_x_c;
                            cout<<"Width: ";
                            cin>>size_y_c;
                            cout<<"Mutable (0/1): ";
                            cin>>is_mutable_c;
                            product* t = new table(cost_c, name_c, descr_c, material_c, color_c, size_x_c, size_y_c, is_mutable_c);
                            break;
                            delete(t);
                        }
                        default: break;
                    }
                }
                // //clear the file every time when you save changes
                //     fstream file;
                //     file.open(adress, ios::out | ios::trunc);
                //     file.close();
                addtostorage();
                product::i = 0;
                break;
            }
             //CUSTOMER MODE
            case 2:{
                CustomerMode = 0;
                int readtype;
                while (CustomerMode!=4){
                    system("cls");
                    cout<<"|       CUSTOMER       |"<<endl<<endl;
                    cout<<"1. Clothes"<<endl;
                    cout<<"2. Furniture"<<endl;
                    cout<<"3. Cart"<<endl;
                    cout<<"4. Exit"<<endl<<endl;
                    cout<<"Enter: ";
                    cin>>CustomerMode;
                    system("cls");
                    switch (CustomerMode){
                        //Clothes
                        case 1:{
                            cout<<"|       CLOTHES       |"<<endl<<endl;
                            file.open(adress, ios::in | ios::binary);
                            while (file.read(reinterpret_cast<char*>(&readtype), sizeof(int))){
                                switch(readtype){
                                    //shirt - display
                                    case 11:{
                                        cout<<readcount+1<<")";
                                        cout<<" SHIRT----------------------"<<endl;
                                        product::arr[readcount] = new shirt();
                                        product::arr[readcount] -> read(readcount, file);
                                        product::arr[readcount] -> print();
                                        cout<<endl;
                                        readcount++;
                                        break;
                                    } 
                                    //belt - display
                                    case 12:{
                                        cout<<readcount+1<<")";
                                        cout<<" BELT----------------------"<<endl;
                                        product::arr[readcount] = new belt();
                                        product::arr[readcount] -> read(readcount, file);
                                        product::arr[readcount] -> print();
                                        cout<<endl;
                                        readcount++;
                                        break;
                                    }
                                    //chair - do not display
                                    case 21:{
                                        product::arr[readcount] = new chair();
                                        product::arr[readcount] -> read(readcount, file);
                                        delete(product::arr[readcount]);
                                        break;
                                    }
                                    //table - do not display
                                    case 22:{
                                        product::arr[readcount] = new table();
                                        product::arr[readcount] -> read(readcount, file);
                                        delete(product::arr[readcount]);
                                        break;
                                    }
                                    default:break;
                                }
                            }
                            AfterProductsMenu();
                            readcount = 0;
                            break;
                        }
                        //Furniture
                        case 2:{
                            cout<<"|       FURNITURE       |"<<endl<<endl;
                            file.open(adress, ios::in | ios::binary);
                            while (file.read(reinterpret_cast<char*>(&readtype), sizeof(int))){
                                switch(readtype){
                                    //chair - display
                                    case 21:{
                                        cout<<readcount+1<<")";
                                        cout<<" CHAIR----------------------"<<endl;
                                        product::arr[readcount] = new chair();
                                        product::arr[readcount] -> read(readcount, file);
                                        product::arr[readcount] -> print();
                                        cout<<endl;
                                        readcount++;
                                        break;
                                    }
                                    //table -  display
                                    case 22:{
                                        cout<<readcount+1<<")";
                                        cout<<" TABLE----------------------"<<endl;
                                        product::arr[readcount] = new table();
                                        product::arr[readcount] -> read(readcount, file);
                                        product::arr[readcount] -> print();
                                        cout<<endl;
                                        readcount++;
                                        break;
                                    }
                                    //shirt - do not display
                                    case 11:{
                                        product::arr[readcount] = new shirt();
                                        product::arr[readcount] -> read(readcount, file);
                                        delete(product::arr[readcount]);
                                        break;
                                    }
                                    //belt - do not display
                                    case 12:{
                                        product::arr[readcount] = new belt();
                                        product::arr[readcount] -> read(readcount, file);
                                        delete(product::arr[readcount]);
                                        break;
                                    }
                                    default: break;
                                }
                            }
                            AfterProductsMenu();
                            readcount = 0;
                            break;
                        }
                        //Cart
                        case 3:{
                            maincart.printThings();
                            break;
                        }
                        default:break;
                    }
                    file.close();
                    product::i = 0;
                }
            }
        }
    }
}
