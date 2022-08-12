#include <iostream>
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std;
int maxToolinFile = 50;
void PrintAllTools() {
    // This Function is used to read from the product.txt file and then display all the info about the tools available.
    ifstream file("Products.txt");
    char data[47];
    if(file.is_open())
    { 
        system("Color 06");
        cout << "<-------------------------------------------->" << endl;
        while (!file.eof())
        {
            file.getline(data, 47);
            if (strncmp(&data[5], "                              ", 30) != 0)
            {
                cout << data << endl;
            }
        }
        cout << "<-------------------------------------------->" << endl;
    }
    file.close();
}
void SearchForTools() {
    // This Function will be used to search and display the specific products (Tools) stored in the product.txt file by asking for the ID of Tools.
    system("Color 30");
    ifstream Searchfile("Products.txt"); //opening the file for searching
    char search_term[30];
    cin.ignore();
    cout << "Enter the Name of Tool to search from Inventory: ";
    cin.getline(search_term, 30);
    if (search_term[0] >= 'a' && search_term[0] <= 'z')
    {
        search_term[0] = search_term[0] - 32;
    }
    char record[47];
    bool first = false;
    bool second = false;
    while (!Searchfile.eof())
    {
        int s = 0;
        char word1[30] = { NULL };
        char word2[30] = { NULL };
        int k = 0;
        char fdata[47] = { NULL };
        Searchfile.getline(record, 47); //saving the record of every item one by one from file in record array.
        for (int r = 5;; r++)
        {
            if (record[r] == ' ' && record[r + 1] == ' ')
            {
                break;
            }
            fdata[k] = record[r]; //Extracting the name of Tool
            k++;
        }
        for (int i = 0; i < 30; i++)
        {
            s = i;
            if (fdata[i] == ' ') {

                break;
            }
            word1[i] = fdata[i]; //saving the first word of tool name in Word1 array
        }
        int h = 0;
        ++s;
        for (s;; s++)
        {
            if (fdata[s] == '\0')
            {
                break;
            }
            word2[h] = fdata[s]; //saving the second word of tool name in word2 array
            h++;
        }
        if (strncmp(search_term, word1, strlen(search_term)) == 0)
        {
            first = true;
            cout << record << endl;  //Displaying that item if it's in the file
        }
        else if (first == false)
        {
            if (strncmp(search_term, word2, strlen(search_term)) == 0)
            {
                second = true;
                cout << record << endl; //Displaying that item if it's in the file and if we are in here it means that first word in tool name was not matched but the seocnd one matched with searched term
            }
        }
    }
    if (first == false && second == false)
    {
        //No match was found in the file
        cout << "No Match Found" << endl;
    }

}
void AddNewTool() {
    // By calling this function, user can add and store the information about new tools in the product.txt file.
    // This function will also check that if we want to add new item then there will be a blank space for storing it in that location otherwise it will print some type of error or meesage.
    system("Color CF");
    fstream file("Products.txt", ios::in | ios::out);
    long long id;
    char name[30]; //Name of new Product
    int qty; // Quantity of new product
    int price; // Price of new Product
    char ref[30];
    int oldId; //for helping purposes in code you can see that in code
    int maxId = 0; //for helping purposes in code you can see that in code
    int i = 1;
    while (!file.eof())
    {
        file.seekg(47 * i);
        file >> oldId;
        i++;
        if (oldId > maxId)
        {
            maxId = oldId;
            //Finding the product with max product_id 
        }
    }
    maxToolinFile = maxId;
    file.close();
    cout << "Enter the ID of New Tools(from 1 to " <<maxId <<"): ";
    cin >> id;
    
    if (id > maxId or id < 0){

        cout << "The ID number you entered is exceeded the limit (Enter the ID again from 1 to " << maxId << ")..\n\n";
        AddNewTool();
    }
    else {

        file.open("Products.txt");
        file.seekg((47 * id) + 5); //Jumping at the specific position with some calculations here 47 is the length of one single record
        /*Multiplying 47 by id will point towards the exact line number at which we want to add new product and adding 5 to it will start pointing at the name of the tool.*/
        file.getline(ref, 30); //storing the name of tool in ref array for comparisons
        file.close();
        file.open("Products.txt");
        if (strncmp(ref, "                            ",28) == 0)//checking if the record at which we are going to insert new product info is empty or not
        {
            cin.ignore();
            cout << "Please enter the name of the Tools: ";
            cin.getline(name, 30);
            file.seekp((47 * id) + 5);//saving the name of tool in file
            file << left << setw(30) << name;
            cout << "Please Enter the Quantity of this Tools: ";
            cin >> qty;
            file.seekp((47 * id) + 35);
            file << left << setw(5) << qty; // saving the quantity of new tool in file
            cout << "Please enter the price of this Tools (in PKR): ";
            cin >> price;
            file.seekp((47 * id) + 40);
            file << left << setw(5) << price; //saving the price of new tool in file
            cout << "\n\nData Entered Succeessfully...\n\n" << endl;
            cout << "This is now, Updated Inventory: \n" << endl;
           
            file.close();
            PrintAllTools();//Just printing the new list of tool after adding new tool in the file records
        }
        else {
            //If program reaches here it means that a product with this id is already stored in file
            cout << "Oops!" << endl;
            for (int i = 0;; i++)
            {
                if (ref[i] == ' ' and ref[i + 1] == ' ')
                {
                    break;
                }
                cout << ref[i];
            }
            cout << ", with ID number " << id << " already exists in your inventory." << endl;
            file.close();
            return;
        }
    }
        
}
void UpdateTheToolsInventory() {
    // This function is used to update the existing items in the products.txt file.
    // If user tends to update a record which is not present in the file then it must display an Error or message related to it.
    PrintAllTools();
    cout << "\n\nSelect the ID of Tool to edit it's record.\n" << endl;
    fstream updatedFile("Products.txt", ios::in | ios::out);
    int newQty, newPrice; ///new quantity and price of tool
    long long id;
    cin >> id; // Tool id to search it in file
    char name_ref[30];
    updatedFile.seekg((47 * id) + 5);
    updatedFile.read(name_ref, 30);
    if (id > 0 || id <= maxToolinFile)
    {
        if (strncmp(name_ref, "                              ", 29) == 0)
        {
            cout << "Oops! there's no such record saved. Please Enter the ID again..." << endl;
            UpdateTheToolsInventory();
            updatedFile.close();
            return;
        }
        else {
            cin.ignore();
            cout << "Please Enter the New Quantity this Tools: ";
            cin >> newQty;
            cout << "Please Enter the New price of this Tools (in PKR): ";
            cin >> newPrice;

            updatedFile.ignore();
            //saving the new quantity and price in text file
            updatedFile.seekp((47 * id) + 35);
            updatedFile << left << setw(5) << newQty;
            updatedFile.seekp((47 * id) + 40);
            updatedFile << left << setw(5) << newPrice;

            updatedFile.flush();
            updatedFile.close();
            cout << "\n\nRecord Modified Succeessfully...\n\n" << endl;
            cout << "This is now, The Updated Inventory: \n" << endl;
            cout << "<-------------------------------------------->" << endl;
            PrintAllTools();
            cout << "<-------------------------------------------->" << endl;
        }
    }
    else {
        cout << "The ID number you entered is exceeded the limit of total products(You can add new Tool)";
        Sleep(2000);
        AddNewTool();
    }

}
void DeleteTools() {
    // This Function will ask for ID of tool and then delete the corresponding data from product.txt file.
    // This function will also check if there's a data of any tool and then delete otherwise, it will show an error or message.
    cout << "<-------------------------------------------->" << endl;
    PrintAllTools();
    cout << "<-------------------------------------------->" << endl;
    fstream file("Products.txt", ios::in|ios::out);
    int id;
    char record[30];
    cout << "\nEnter the ID of tool from inventory displayed above to delete from inventory: " << endl;
    cin >> id; //id of tool which the user wants to delete
    cin.ignore();
    file.seekg((47 * id) + 5);
    file.getline(record, 30);
    file.close();
    if (strncmp(record, "                            ", 28) == 0)
    {
        cout << "\nOops! This record is already empty so, no need to delete this record...\n" << endl;
        file.close();
        return;
    }
    else {
        //If the tool exists in the file then we can simply replace it with empty space to the sake of simplicity
        file.open("Products.txt");
        file.seekp((47 * id) + 5);
        file << left << setw(30) << "";
        file.seekp((47 * id) + 35);
        file << left << setw(5) << "";
        file.seekp((47 * id) + 40);
        file << left << setw(5) << "";
        file.close();
        cout << "Tool's record deleted successfully, here's the updated inventory: " << endl;
        PrintAllTools();
    }
    
}
void SoldTools() {
    //This Function will maintain the sales.txt file...
    //Whenever customers buy something, user can use this function to update his sales.txt file with relevent information... 
    /*This feature will help the admins to maintain their sales and it will also give some insights to admins about their store*/
    system("Color E5");
    int choice;
    cout << "Enter 1 to update your Sales Record or 2 to print your sales history.\n" << endl;
    cin >> choice;
    fstream Pfile("Products.txt", ios::out | ios::in);
    fstream Sfile("Sales.txt", ios::out | ios::in | ios::app);
    if (choice == 1)
    {
        PrintAllTools();
       
        int id, quantity, unitPrice, profit;
        char Pname[30]; //name of tool from products file 
        int Pprice; // price of tool from products file
        int Pqty; // qty of tool from products file
        int Sqty; //quantity of tool sold 
        cout << "\n\nEnter the ID of Tool from the menu above: ";
        cin >> id;

        Pfile.seekg((47 * id) + 35);
        Pfile >> Pqty;
        Pfile.seekg((47 * id) + 40);
        Pfile >> Pprice;
        cin.ignore();
        Pfile.seekg((47 * id) + 5);
        Pfile.getline(Pname, 30);
       
        Pfile.close();
        cout << "Enter the quantity of (";
        for (int i = 0;; i++)
        {
            if (Pname[i] == ' ' and Pname[i + 1] == ' ')
            {
                break;
            }
            cout << Pname[i];
        }
        cout << ") you sold to the customers: ";
        cin >> Sqty;
        if (Sqty > Pqty)
        {
            //Checking if the sold quantity is greater than the actual quantity in stock
            cout << "ERROR! Quantity you entered exceeded the actual quantity of that tool in your inventory.\n" << endl;
        }
        else {
            //Sfile << left << setw(5) << "ID" << setw(30) << "Tool Name" << setw(10) << "Price/e" << setw(10) << "Qty." << setw(12) << "Total Sale" << setw(25) << "Sold At" << endl;
           //storing the information of sold tool in sales file
            Sfile << left << setw(5) << id << setw(30) << Pname << setw(10) << Pprice << setw(10) << Sqty << setw(12) << Pprice * Sqty;
            time_t trf = time(NULL);
            tm* timeref = localtime(&trf);
            Sfile << setw(2) << (timeref->tm_mday) << setw(1) << "/" << setw(1) << (timeref->tm_mon) + 1 << setw(1) << "/" << setw(2) << (timeref->tm_year) + 1900 << setw(2) << "--";
            Sfile << setw(2) << (timeref->tm_hour) << setw(1) << ':' << setw(2) << (timeref->tm_min) << setw(1) << ':' << setw(2) << (timeref->tm_sec) << endl;
            //storing the Time and date at which the product was sold by admins
            cout << "\n\n----------> Records Updated Successfully! <----------\n" << endl;
            if (Pqty-Sqty == 0) {
                //If a product is out of stock after that transaction than we can display out of stock message
                for (int i = 0;; i++)
                {
                    if (Pname[i] == ' ' and Pname[i + 1] == ' ')
                    {
                        break;
                    }
                    cout << Pname[i];
                }
                cout << " is now Out of Stock!" << endl;
                cout << "If you want to delete this item from your inventory, you can call the Delete Function.\n" << endl;
            }
            else if ((Pqty - Sqty) > 0) {
                //And now after updating the sales file now this will update the products file by subtracting the sold and in_stock quantity.
                Pfile.open("Products.txt");
                Pfile.seekp((47 * id) + 35);
                Pfile <<left<< setw(5) << Pqty - Sqty;
                cout << "\nThe records in Products File also updated.\n" << endl;
                Pfile.close();
            }
        }
    }   
    else if (choice == 2)
    {
        ifstream Sfile("Sales.txt");
        char data[1000];
        while (!Sfile.eof())
        {
            Sfile.getline(data, 1000, '\n');
            cout << data << endl;

        }
        Sfile.close();
        //Calculating the total Sale Uptill now
        ifstream Total("Sales.txt");
        cin.ignore();
        int prices;
        int i = 1;
        char nameBreak[30];
        int totalprice = 0;
        while (!Total.eof())
        {
            Total.seekg((88 * i) + 55);
            Total >> prices;
            i++;
            totalprice = totalprice + prices;

        }
        cout << "\n\t\t\t\tYour total sale uptill now is: " << totalprice - prices << '\n';
        Total.close();
        //Checking the Items which was purchased most (quantity wise, you can change it to price wise also).
        fstream MaxQty("Sales.txt", ios::in | ios::out);
        int saleqty;
        int is = 1;
        char Maxname[30];
        int maxqty = 0;
        while (!MaxQty.eof())
        {
            MaxQty.seekg((88 * is) + 45);
            MaxQty >> saleqty;
            if (saleqty > maxqty)
            {
                MaxQty.close();
                maxqty = saleqty;
                MaxQty.open("Sales.txt");
                MaxQty.seekg((88 * is) + 5);
                MaxQty.getline(Maxname, 30);
                MaxQty.close();
                MaxQty.open("Sales.txt");
            }
            is++;
        }
        cout << "\t\t\t\t--->MOST SOLD ITEM<---\n\t\t\t\tName: ";
        for (int q = 0;; q++)
        {
            if (Maxname[q] == ' ' && Maxname[q + 1] == ' ')
            {
                break;
            }
            cout << Maxname[q];
        }
        cout << "\n\t\t\t\tQuantity: " << maxqty << '\n';
        MaxQty.close();
    }
    else if (choice != 1 and choice != 2) //Checking if user enters the wrong number. 
    {
        cout << "ERROR!\nYou entered the wrong number.\n" << endl;
        cout << "Try Again...\n\n";
        SoldTools();
    }




    Pfile.close();
    Sfile.close();

}
//void tools() {
//    ofstream file("Products.txt");
//    char toolname[30];
//    int id;
//    int price;
//    int quantity;
//    file << left << setw(5) << "ID";
//    file << left << setw(30) << "Tool Name";
//    file << left << setw(5) << "Qty";
//    file << left << setw(5) << "Price" << endl;
//    int i = 0;
//    for(int i=1; i<=17;i++)
//    {
//        if (file.is_open())
//        {
//         
//            cout << "Name: ";
//            cin.getline(toolname, 30);
//            
//            cout << "Quantity: ";
//            cin >> quantity;
//            
//            cout << "Price: ";
//            cin >> price;
//            cin.ignore();
//            file << left << setw(5) << i;
//            file << left << setw(30) << toolname;
//            file << left << setw(5) << quantity;
//            file << left << setw(5) << price << endl;
//        }
//        
//    }
//}
void ExtraRecords()
{
    system("Color AF");
    ifstream Pfile("Products.txt");
    int oldId;
    int maxId = 0;
    int i = 1;
    while (!Pfile.eof())
    {
        Pfile.seekg(47 * i);
        Pfile >> oldId;
        i++;
        if (oldId > maxId)
        {
            maxId = oldId;
        }
    }
    Pfile.close();
    cout << "Currently, your file contains " << maxId << " records.\n" << endl;
    int newrecords;
    cout << "Enter the number of records you want to increase: ";
    cin >> newrecords;
    int choice;
    cout << "Your total number of records will be " << maxId + newrecords << " \nIf you are sure,\nPress\t1\tElse\t2" << endl;
    cin >> choice;
    if (choice == 1)
    {
        maxId++;
        fstream AppFile("Products.txt", ios::in|ios::out|ios::app);
        for (int s = 1; s <= newrecords; s++)
        {
            if (s == 1)
            {
                AppFile << endl;
            }
            AppFile << left << setw(5) << maxId;
            AppFile << left << setw(30) << "";
            AppFile << left << setw(5) << "";
            AppFile << left << setw(5) << "";
            maxId++;
            if (s < newrecords)
            {
                AppFile << endl;
            }
        }
        cout <<'\n'<< newrecords << " extra records successfully added in your inventory file. Now you can add " << newrecords << " more tools in your inventory.\n\n" << endl;
    }
    else if (choice == 2)
    {
        cout << "No records are added." << endl;
    }
    else if (choice != 1 && choice != 2)
    {
        cout << "ERROR!\nYou entered the wrong number, Please try again." << endl;
        return;
    }
    
}
void desc()
{
    //This Function will Print all of the read me first Instructions for First-Time Users...
    system("Color CF");
    ifstream file("Description.txt");
    char data[1000];
    int d = 0;
    while (!file.eof())
    {
        if (d == 0) { //Just fancy loading effect ;)
            cout << "Please wait the file is loading";
            Sleep(1000);
            cout << '.';
            Sleep(1000);
            cout << '.';
            Sleep(1000);
            cout << '.' << endl;
        }
        file.getline(data, 1000);
        cout << data << endl;
        d++;
        if (d == 5)
        {
            Sleep(1000);
            cout << "Loading.";
            Sleep(1000);
            cout << '.';
            Sleep(1000);
            cout << '.';
            Sleep(1000);
            cout << '.';
            Sleep(1000);
            cout << '.' << endl;
        }
        if (d == 18)
        {
            Sleep(1000);
            cout << "Loading.";
            Sleep(1000);
            cout << '.';
            Sleep(1000);
            cout << '.';
            Sleep(1000);
            cout << '.';
            Sleep(1000);
            cout << '.' << endl;
        }
    }
    cout << "\n-------------->End of the Description File<--------------\n" << endl;
    file.close();
}
int logincheck() {
    char AdminAccount[] = "admin@tsms";
    char AdminPass[] = "golden99";
    char UserAccount1[] = "user01tsms";
    char UserPass1[] = "user01";
    char UserAccount2[] = "user02tsms";
    char UserPass2[] = "user02";
    /*Up above are the dummy logins for testing demonstrations, but you can increase the number
    of Admins and Users but for that you have to create more arrays or their usernames and respective passwords.
    But as this is a very basic implementation, you can also use Vectors/Strings/ArrayOfString/Maps/HashMaps to
    store data of multiple users and admin.
    */
    char loginacc[20];
    char loginpass[20];
    int adminreturn;
    int userreturn;
    int wrong;
    cout << "Enter Your Login ID: ";
    cin.getline(loginacc, 20);
    cout << "Enter Your Login Password: ";
    cin.getline(loginpass, 20);
    for (int i = 0;; i++)
    {
        /*Converting each character in login account and password to lowercase for simpler and efficient comparison of data stored
        already and the new login credentials*/
        if (loginacc[i] >= 'A' && loginacc[i] <= 'Z')
        {
            loginacc[i] = loginacc[i] + 32;
        }
        if (loginpass[i] >= 'A' && loginpass[i] <= 'Z')
        {
            loginpass[i] = loginpass[i] + 32;
        }
        if (loginpass[i] == '\0')
        {
            break;
        }
    }
    //Comparing if the current typed Account and Password is matching with any admin login credentails stored.
    if (strncmp(AdminAccount, loginacc, strlen(AdminAccount)) == 0 && strncmp(AdminPass, loginpass, strlen(AdminPass)) == 0) //Checking the Admin's login ID and Password.
    {

        adminreturn = 1;
        cout << "\nLoged In successfully.\n" << endl;
        return adminreturn;

    }
    else if ((strncmp(UserAccount1, loginacc, strlen(UserAccount1)) == 0 && strncmp(UserPass1, loginpass, strlen(UserPass1)) == 0) || (strncmp(UserAccount2, loginacc, strlen(UserAccount2)) == 0 && strncmp(UserPass2, loginpass, strlen(UserPass2)) == 0))//Checking the Users' login ID and Password.
    {
        //Comparing if the current typed Account and Password is matching with any user login credentails stored.
        userreturn = 2;
        cout << "\nLoged In successfully.\n" << endl;
        return userreturn;
    }
    else {
        return wrong = 3;
    }
}
void WelcomeDisplay() {
    /*This will be displayed only first time on the execution of this program*/
    cout << endl;
    cout << "\t\t\t\t  ooooooooooooooooooooooooooooooooooooooooooooooooooooooooo" << endl;
    cout << "\t\t\t\t  =========================================================" << endl;
    cout << "\t\t\t\t||                                                         ||" << endl;
    cout << "\t\t\t\t||       Welcome to the Tools Shop Management System       ||" << endl;
    cout << "\t\t\t\t||                                                         ||" << endl;
    cout << "\t\t\t\t  =========================================================" << endl;
    cout << "\t\t\t\t  ooooooooooooooooooooooooooooooooooooooooooooooooooooooooo\n\n\n" << endl;

}
void AdminOptionDisplay() {
    /*This is the options menu for designed for Admins only which means that following option/features are available to admins only
    not the the simple users...
    */
    cout << "\n\n";
    cout << "\t\t\t\t\t      ||\\  /||  ||===  ||\\  ||  ||   ||" << endl;
    cout << "\t\t\t\t\t      || \\/ ||  ||===  || \\ ||  ||   ||" << endl;
    cout << "\t\t\t\t\t      ||    ||  ||===  ||  \\||  ||___||\n" << endl;
    cout << "\t\t\t\t =============================================================" << endl;
    cout << "\t\t\t\t| PLEASE ENTER THE OPTION TO SELECT:                          |" << endl;
    cout << "\t\t\t\t| [ A ]\tTo Add New Tool.                                      |" << endl;
    cout << "\t\t\t\t| [ U ]\tTo Update Tool Inventory.                             |" << endl;
    cout << "\t\t\t\t| [ P ]\tTo Print all Tools.                                   |" << endl;
    cout << "\t\t\t\t| [ D ]\tTo Delete a Tool.                                     |" << endl;
    cout << "\t\t\t\t| [ S ]\tTo Search for tools.                                  |" << endl;
    cout << "\t\t\t\t| [ Z ]\tTo Add sold tools to maintain your sales file.        |" << endl;
    cout << "\t\t\t\t| [ R ]\tTo Print all Read me First Instructions.              |" << endl;
    cout << "\t\t\t\t| [ E ]\tTo Add extra records in your inventory file.          |" << endl;
    cout << "\t\t\t\t| [ X ]\tTo Log Out from the program.                          |" << endl;
    cout << "\t\t\t\t =============================================================\n\n" << endl;
}
void UserOptionDisplay() {
    /*This options menu is desinged for Users only, it has lesser options/features as comapred to admins menu because
    admins and users have different roles, so differnet features...*/
    cout << "\n\n";
    cout << "\t\t\t\t\t      ||\\  /||  ||===  ||\\  ||  ||   ||" << endl;
    cout << "\t\t\t\t\t      || \\/ ||  ||===  || \\ ||  ||   ||" << endl;
    cout << "\t\t\t\t\t      ||    ||  ||===  ||  \\||  ||___||\n" << endl;
    cout << "\t\t\t\t =============================================================" << endl;
    cout << "\t\t\t\t| PLEASE ENTER THE OPTION TO SELECT:                          |" << endl;
    cout << "\t\t\t\t| [ P ]\tTo Print all Tools.                                   |" << endl;
    cout << "\t\t\t\t| [ S ]\tTo Search for tools.                                  |" << endl;
    cout << "\t\t\t\t| [ R ]\tTo Print all Read me First Instructions.              |" << endl;
    cout << "\t\t\t\t| [ X ]\tTo Log Out from the program.                          |" << endl;
    cout << "\t\t\t\t =============================================================\n\n" << endl;
}
void ToolShopManagementSystem() {
    system("Color 7C");
    // In this int main() function, we will display the Command Choices Menu for user to choose and test any mentioned Function.
    // Then User will give input the commands like:
        // 'A' or 'a'for AddNewTool(),
        // 'P' or 'p' for PrintAllTools(),
        // 'S' or 's' for SearchForTools(),
        // 'U' or 'u' for UpdateTheToolsInventory(),
        // 'D' or 'd' for DeleteTools(),
        // 'Z' or 'z' for SoldTools(),
        // 'X' or 'x' to Exit or Terminate from the program......
    // Whenever user successfully performs any task, The screen will be cleared, and the Command Choices Menu will appear again to perform anytask further.
    WelcomeDisplay();
    char Menu_Choice; //This will store the Key pressed by users/admins and will do the operations accordingly
    int g = logincheck(); //storing the Login ID
    system("cls");
    if (g == 1 /*  1 is for admins the login check function will return 1 if someone is logged in as Admin   */)
    {
        while (true)
        {
            AdminOptionDisplay();
            cout << "->If you are using this program very first time.\n-->So, i would highly recommend you to select R from the Menu to take a look at 'Read Me First' instructions...\n" << endl;
            cout << right << "You are currently logged in as Admin\n\n" << endl;
            cout << "Please Enter the option from the Menu above and press Enter: ";
            cin >> Menu_Choice;
            if (Menu_Choice == 'A' || Menu_Choice == 'a')  //Checking the user's input and calling the respective function...
            {
                AddNewTool();
                system("pause");
                system("cls");
            }
            else if (Menu_Choice == 'Z' || Menu_Choice == 'z')
            {
                SoldTools();
                system("pause");
                system("cls");
            }
            else if (Menu_Choice == 'D' || Menu_Choice == 'd')
            {
                DeleteTools();
                system("pause");
                system("cls");
            }
            else if (Menu_Choice == 'U' || Menu_Choice == 'u')
            {
                UpdateTheToolsInventory();
                system("pause");
                system("cls");
            }
            else if (Menu_Choice == 's' || Menu_Choice == 'S')
            {
                SearchForTools();
                system("pause");
                system("cls");
            }
            else if (Menu_Choice == 'P' || Menu_Choice == 'p')
            {
                PrintAllTools();
                system("pause");
                system("cls");
            }
            else if (Menu_Choice == 'R' || Menu_Choice == 'r')
            {
                desc();
                system("pause");
                system("cls");
            }
            else if (Menu_Choice == 'E' || Menu_Choice == 'e')
            {
                ExtraRecords();
                system("pause");
                system("cls");
            }
            else if (Menu_Choice == 'X' || Menu_Choice == 'x')
            {
                Sleep(1200);
                cout << "Loged out Successfully." << endl;
                return ;
            }
            else {
                cout << "Incorrec Choice.\nPlease try again..." << endl;
                system("pause");
                system("cls");
                continue;
            }

        }
    }
    else if (g == 2  /*  2 is for Users the login check function will return 2 if someone is logged in as User   */) {
        cin.ignore();
        while (true)
        {
            UserOptionDisplay();
            cout << "->If you are using this program very first time.\n-->So, i would highly recommend you to select R from the Menu to take a look at 'Read Me First' instructions...\n" << endl;
            cout << right << "You are currently logged in Users Mode.\n\n" << endl;
            cout << "Please Enter the option from the Menu above and press Enter: ";

            cin >> Menu_Choice;
            if (Menu_Choice == 's' || Menu_Choice == 'S')
            {
                SearchForTools();
                system("pause");
                system("cls");
            }
            else if (Menu_Choice == 'P' || Menu_Choice == 'p')
            {
                PrintAllTools();
                system("pause");
                system("cls");
            }
            else if (Menu_Choice == 'R' || Menu_Choice == 'r')
            {
                desc();
                system("pause");
                system("cls");
            }
            else if (Menu_Choice == 'X' || Menu_Choice == 'x')
            {
                Sleep(1200);
                cout << "Loged out Successfully." << endl;
                return ;
            }
            else {
                cout << "Incorrec Choice.\nPlease try again..." << endl;
                system("pause");
                system("cls");
                continue;
            }
        }
    }
    else if (g == 3)
    {
        cout << "Your Login Credentials are wrong!\n" << endl;
        return;
    }
}
int main()
{
    /*Calling the Main Function for the tool shop management system */
    ToolShopManagementSystem();
}
//Ending Here :)