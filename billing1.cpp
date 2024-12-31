#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

class shopping
{
private:
    int pcode;         
    float price;       
    float dis;        
    std::string pname; 

public:
    void menu();          
    void administrator(); 
    void buyer();         
    void viewList();      
    void add();           
    void edit();          
    void rem();           
    void list();         
    void receipt();       
};

void shopping::menu()
{
    int choice;
    std::string email;
    std::string password;

    while (true)
    {
        std::cout << "\t\t\t\t____________________________________" << std::endl;
        std::cout << "\t\t\t\t        Supermarket Main Menu       " << std::endl;
        std::cout << "\t\t\t\t____________________________________" << std::endl;
        std::cout << "\t\t\t\t         1) Administrator           " << std::endl;
        std::cout << "\t\t\t\t         2) Buyer                   " << std::endl;
        std::cout << "\t\t\t\t         3) Exit                    " << std::endl;
        std::cout << "\n\t\t\t Please select: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::cout << "\t\t\t Please login!" << std::endl;
            std::cout << "\t\t\t Enter email: ";
            std::cin >> email;
            std::cout << "\t\t\t Enter password: ";
            std::cin >> password;

            if (email == "!@#" && password == "!@#")
            {
                administrator();
            }
            else
            {
                std::cout << "\t\t\t Invalid email or password." << std::endl;
            }
            break;

        case 2:
            buyer();
            break;

        case 3:
            std::cout << "\t\t\t Thank you for visiting!" << std::endl;
            exit(0);
            break;

        default:
            std::cout << "\t\t\t Please select a valid option." << std::endl;
        }
    }
}

void shopping::administrator()
{
    int choice;
    while (true)
    {
        std::cout << "\n\n\n\t\t\t Administrator Menu         " << std::endl;
        std::cout << "\t\t\t__________________________________" << std::endl;
        std::cout << "\t\t\t       1) Add a product           " << std::endl;
        std::cout << "\t\t\t       2) Modify the product      " << std::endl;
        std::cout << "\t\t\t       3) Delete the product      " << std::endl;
        std::cout << "\t\t\t       4) View product list       " << std::endl;
        std::cout << "\t\t\t       5) Back into main menu     " << std::endl;

        std::cout << "\n\t\t\t Please select: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            add();
            break;
        case 2:
            edit();
            break;
        case 3:
            rem();
            break;
        case 4:
            viewList();
            break;
        case 5:
            menu();
            break;

        default:
            std::cout << "\t\t\t Please select a valid option." << std::endl;
            break;
        }
    }
}

void shopping::buyer()
{
    int choice;
    while (true)
    {
        std::cout << "\t\t\t      Buyer Menu    " << std::endl;
        std::cout << "\t\t\t____________________" << std::endl;
        std::cout << "                     " << std::endl;
        std::cout << "\t\t\t 1) Buy product" << std::endl;
        std::cout << "\t\t\t 2) View product list" << std::endl;
        std::cout << "\t\t\t 3) Go back    " << std::endl;

        std::cout << "\n\t\t\t Please select: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            receipt();
            break;
        case 2:
            viewList();
            break;
        case 3:
            menu();
            break;

        default:
            std::cout << "\t\t\t Please select a valid option." << std::endl;
            break;
        }
    }
}

void shopping::viewList()
{
    std::fstream data;
    data.open("database.txt", std::ios::in);

    if (!data)
    {
        std::cout << "\n\n\t No products available in the inventory.\n";
        return;
    }

    std::cout << "\n\n\t\t\t Product List \n";
    std::cout << "______________________________________________________\n";
    std::cout << "ProNo\t\tName\t\tPrice\t\tDiscount\n";
    std::cout << "______________________________________________________\n";

    data >> pcode >> pname >> price >> dis;
    while (!data.eof())
    {
        std::cout << pcode << "\t\t" << pname << "\t\t" << price << "\t\t" << dis << "%\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shopping::add()
{
    std::fstream data;
    int c;
    float p, d;
    std::string n;
    bool exists = false;

    std::cout << "\n\n\n\t\t\t Add new product" << std::endl;
    std::cout << "\n\t\t\t Product code of the product: ";
    std::cin >> pcode;
    std::cout << "\n\n\t Name of the product: ";
    std::cin.ignore();
    std::getline(std::cin, pname);
    std::cout << "\n\n\t Price of the product: ";
    std::cin >> price;
    std::cout << "\n\n\t Discount on product: ";
    std::cin >> dis;

    data.open("database.txt", std::ios::in);
    if (data)
    {
        data >> c >> n >> p >> d;
        while (!data.eof())
        {
            if (c == pcode)
            {
                exists = true;
                break;
            }
            data >> c >> n >> p >> d;
        }
        data.close();
    }

    if (exists)
    {
        std::cout << "\n\n\t Product code already exists. Try again." << std::endl;
        return;
    }

    data.open("database.txt", std::ios::app);
    data << pcode << " " << pname << " " << price << " " << dis << std::endl;
    data.close();

    std::cout << "\n\n\t\t Record inserted." << std::endl;
}

void shopping::edit()
{
    std::fstream data, temp;
    int pkey, c;
    float p, d;
    std::string n;
    bool found = false;

    std::cout << "\n\n\t\t\t Modify the record " << std::endl;
    std::cout << "\n\n\t\t\t Enter product code: ";
    std::cin >> pkey;

    data.open("database.txt", std::ios::in);
    temp.open("temp.txt", std::ios::out);

    if (!data)
    {
        std::cout << "\n\n\t File does not exist." << std::endl;
        return;
    }

    data >> pcode >> pname >> price >> dis;
    while (!data.eof())
    {
        if (pcode == pkey)
        {
            std::cout << "\n\t\t Product new code: ";
            std::cin >> c;
            std::cout << "\n\t\t Name of the product: ";
            std::cin.ignore();
            std::getline(std::cin, n);
            std::cout << "\n\t\t New price: ";
            std::cin >> p;
            std::cout << "\n\t\t New discount: ";
            std::cin >> d;
            temp << c << " " << n << " " << p << " " << d << std::endl;
            std::cout << "\n\t\t Record edited." << std::endl;
            found = true;
        }
        else
        {
            temp << pcode << " " << pname << " " << price << " " << dis << std::endl;
        }
        data >> pcode >> pname >> price >> dis;
    }

    data.close();
    temp.close();

    remove("database.txt");
    rename("temp.txt", "database.txt");

    if (!found)
    {
        std::cout << "\n\t\t Product not found." << std::endl;
    }
}

void shopping::rem()
{
    std::fstream data, temp;
    int pkey;
    bool found = false;

    std::cout << "\n\n\t\t\t Delete a product" << std::endl;
    std::cout << "\n\n\t\t\t Enter product code: ";
    std::cin >> pkey;

    data.open("database.txt", std::ios::in);
    temp.open("temp.txt", std::ios::out);

    if (!data)
    {
        std::cout << "\n\n\t File does not exist." << std::endl;
        return;
    }

    data >> pcode >> pname >> price >> dis;
    while (!data.eof())
    {
        if (pcode == pkey)
        {
            std::cout << "\n\t\t Product deleted successfully." << std::endl;
            found = true;
        }
        else
        {
            temp << pcode << " " << pname << " " << price << " " << dis << std::endl;
        }
        data >> pcode >> pname >> price >> dis;
    }

    data.close();
    temp.close();

    remove("database.txt");
    rename("temp.txt", "database.txt");

    if (!found)
    {
        std::cout << "\n\t\t Product not found." << std::endl;
    }
}

void shopping::list()
{
    std::fstream data;
    data.open("database.txt", std::ios::in);
    if (!data)
    {
        std::cout << "\n\n\t No products in the inventory." << std::endl;
        return;
    }

    std::cout << "\n\n_____________________________________________________\n";
    std::cout << "ProNo\t\tName\t\tPrice\n";
    std::cout << "_____________________________________________________\n";
    data >> pcode >> pname >> price >> dis;
    while (!data.eof())
    {
        std::cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shopping::receipt()
{
    std::fstream data;
    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount = 0, dis = 0, total = 0;

    std::cout << "\n\n\t\t\t RECEIPT " << std::endl;
    data.open("database.txt", std::ios::in);
    if (!data)
    {
        std::cout << "\n\n\t No products in the inventory." << std::endl;
        return;
    }
    data.close();

    list();

    std::cout << "\n_____________________________________\n";
    std::cout << "\n|                                      |\n";
    std::cout << "\n        Please place your order         \n";
    std::cout << "\n|                                      |\n";
    std::cout << "\n_____________________________________\n";

    do
    {
        std::cout << "\n\nEnter Product code: ";
        std::cin >> arrc[c];
        std::cout << "\n\nEnter the product quantity: ";
        std::cin >> arrq[c];
        c++;
        std::cout << "\n\nDo you want to buy another product? (y/n): ";
        std::cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    std::cout << "\n\n\t\t\t________________________RECEIPT____________________\n";
    std::cout << "Product No\t Product Name \t Product Quantity \t Price \t Amount \t Amount with discount\n";

    for (int i = 0; i < c; i++)
    {
        data.open("database.txt", std::ios::in);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pcode == arrc[i])
            {
                amount = price * arrq[i];
                dis = amount - (amount * dis / 100);
                total += dis;
                std::cout << "\n"
                          << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t\t" << dis;
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
    }
    std::cout << "\n\n____________________________________________________";
    std::cout << "\n Total Amount: " << total;
    std::cout << "\n\n____________________________________________________";
}

int main()
{
    shopping s;
    s.menu();
    return 0;
}
