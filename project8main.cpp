



#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const string fileclientsname = "clients.txt";
const string fileusername = "Users.txt";


struct stclient {
    string accountnumber;
    string pincode;
    string name;
    string phone;
    string accountbalance;
    bool markfordelete = false;
    bool markforupdate = false;
    bool markfordeposit = false;
    bool maarkforwithdraw = false;
};

struct stadmin {
    string username;
    string password;
    string permisionresult;
    bool marktodelete = false;
    bool markforupdate = false;

};


stadmin currentuser;



enum enchoice { showclient = 1, addnewclient = 2, deleteclient = 3, updateclient = 4, findclient = 5, trans = 6 , manageusers = 7, exitt = 8 };
enum entrans { deposit = 1, withddraw = 2, totalbalancies = 3, mainmenuee = 4 };
enum enmanageusers { listusers = 1, addnewuserr = 2, deleteuserrr = 3, updateuserr = 4, finduserr = 5, mainmenueee = 6 };
enum enMainMenuePermissions {eAll = -1, plistClients = 1, pAddNewClient = 2, pDeleteClient = 4,pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64};



bool updateuserrecordbyusername(string);
bool deleteuserbyusername(string);
bool markclientfordeletebyaccountnumber(string, stclient&);
bool checkclientuserfoundforupdate(string, stadmin&);
bool finduserbyaccountnumber(string, stadmin&);
bool checkaccesspermision(enMainMenuePermissions);
bool markuserfordelete(string, stadmin&);
bool validuser(string, int);

void deleteuserscreen();
void showmanageusersMenue();
void loginscreen();
void mainmenuescreen();
void ShowAccessDeniedMessage();
void addnewuserrr();
void deleteuserr();
void performtheuseroption(enmanageusers);
void printinfouser(stadmin);
void findclientscreen();
void printinfoclient(stclient);
void transactionmenue();
void GoBackToTransactionsMenue();
void updateuser();
void finduserscreen();
void updateuserscreen();
void performtheuseroption(enmanageusers);
void printinfouser(stadmin);



string userrecord(stadmin);

stadmin convertlinetorecorduser(string, string);

vector<string> splituserinfo(string, string);
vector<stclient> saveclientdatetofile(string);
vector<stadmin> saveadmindatetofile(string);
vector<stclient> loadclientdatafromfile(string = fileclientsname);
vector<stadmin> loaduserdatafromfile(string = fileusername);
vector<stadmin> updateuserdatetofile();

vector<stclient> vclients;
vector<stadmin> vadmins;


void GoBackToTransactionsMenue()
{
    cout << "\n\nPress any key to go back to Transactions Menue...";
    system("pause>0");
    transactionmenue();
}

bool findclientbyaccountnumber(string accountnumber, stclient& client) {
    vclients = loadclientdatafromfile(fileclientsname);
    for (stclient& c : vclients) {
        if (c.accountnumber == accountnumber) {
            client = c;
            return true;
        }
    }
    return false;
}

void PrintUserRecordLine(stadmin User)
{

    cout << "| " << setw(15) << left << User.username;
    cout << "| " << setw(10) << left << User.password;
    cout << "| " << setw(40) << left << User.permisionresult;
}
void ShowAllUsersScreen()
{



    cout << "\n\t\t\t\t\tUsers List (" << vadmins.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "User Name";
    cout << "| " << left << setw(10) << "Password";
    cout << "| " << left << setw(40) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vadmins.size() == 0)
        cout << "\t\t\t\tNo Users Available In the System!";
    else

        for (stadmin& user : vadmins)
        {

            PrintUserRecordLine(user);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}

void PrintClientRecord(stclient client) {
    cout << "| " << setw(15) << left << client.accountnumber;
    cout << "| " << setw(10) << left << client.pincode;
    cout << "| " << setw(40) << left << client.name;
    cout << "| " << setw(12) << left << client.phone;
    cout << "| " << setw(12) << left << client.accountbalance;
}
void Printallclientsdata() {



    cout << "\n\t\t\t\t\tClient List (" << vclients.size() << ")Client(s).";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stclient& Client : vclients) {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}
stclient ReadNewClient() {
    stclient Client;
    cout << "Enter Account Number? ";
    getline(cin >> ws, Client.accountnumber);
    while (findclientbyaccountnumber(Client.accountnumber, Client)) {
        cout << "this account number is found in system \n\n";
        cout << "enter another account number : ";
        getline(cin >> ws, Client.accountnumber);
    }
    cout << "\nEnter PinCode? ";
    getline(cin, Client.pincode);
    cout << "\nEnter Name? ";
    getline(cin, Client.name);
    cout << "\nEnter Phone? ";
    getline(cin, Client.phone);
    cout << "\nEnter AccountBalance? ";
    cin >> Client.accountbalance;
    cout << "\nthe client is added successfully \n";
    return Client;
}
string joinvectorstring(vector<string> v, string sperator) {
    string tot = "";
    for (string& b : v) {
        tot = tot + b + sperator;
    }
    return tot.substr(0, tot.length() - sperator.length());
}
string clientrecord(stclient client) {
    vector<string> v;
    v.push_back(client.accountnumber);
    v.push_back(client.pincode);
    v.push_back(client.name);
    v.push_back(client.phone);
    v.push_back(client.accountbalance);
    string recordline = joinvectorstring(v, "//");
    return recordline;
}
void adddatalinetofile(string namefile, string stDataLine) {
    fstream MyFile;
    MyFile.open(namefile,ios::out | ios::app);
    if (MyFile.is_open()) {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}
void addnewclientscreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n\n";
}
void addnewclientt() {
    addnewclientscreen();
    stclient client;
    client = ReadNewClient();
    vclients.push_back(client);
    string name = clientrecord(client);
    adddatalinetofile(fileclientsname, name);
}
vector <string> spliit(string name, string delim) {
    vector<string> n;
    string sword;
    int pos = 0;
    while ((pos = name.find(delim)) != std::string::npos) {
        sword = name.substr(0, pos);
        if (sword != "") {
            n.push_back(sword);
        }
        name.erase(0, pos + delim.length());
    }
    if (name != "") {
        n.push_back(name);
    }
    return n;
}
stclient convertlinetorecord(string line, string sperator = "//") {
    vector <string> v = spliit(line, sperator);
    stclient client;
    client.accountnumber = v[0];
    client.pincode = v[1];
    client.name = v[2];
    client.phone = v[3];
    client.accountbalance = v[4];
    return client;
}
vector<stclient> loadclientdatafromfile(string Filename) {
    vclients.clear();
    fstream MyFile;
    MyFile.open(Filename, ios::in);
    if (MyFile.is_open()) {
        string line;
        stclient client;
        while (getline(MyFile, line)) {
            client = convertlinetorecord(line, "//");
            vclients.push_back(client);
        }
        MyFile.close();
    }
    return vclients;
}
bool markclientfordeletebyaccountnumber(string accountnumber , stclient &client) {
    for (stclient& c : vclients) {
        if (c.accountnumber == accountnumber) {
            c.markfordelete = true;
            client = c;
            return true;
        }
    }
    return false;
}
vector <stclient> saveclientdatetofile(string filename) {
    fstream myfile;
    myfile.open(filename, ios::out);
    string dataline;
    if (myfile.is_open()) {
        for (stclient& c : vclients) {
            if (c.markfordelete == false) {
                dataline = clientrecord(c);
                myfile << dataline << endl;
            }
        }
        myfile.close();
    }
    return vclients;
}
bool deleteuserbyusername(string username) {
    stadmin user;
    char Answer = 'n';
    if (finduserbyaccountnumber(username, user)) {
        printinfouser(user);
        cout << "\n\nAre you sure you want delete this user? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            markuserfordelete(username, user);
            saveadmindatetofile(fileusername);
            vadmins = loaduserdatafromfile(fileusername);
            cout << "\n\nuser Deleted Successfully.";
            return true;
        }
    }
    else {
        cout << "\nuser with userame :  (" << username << ") is Not Found!";
        return false;
    }
    return false;
}
void deletescreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n\n";
}
void deleteclientt() {

    stclient client;
    char answer = 'n';
    deletescreen();
    string accountnumber;
    cout << "enter the account number : ";
    cin >> accountnumber;
    if (markclientfordeletebyaccountnumber(accountnumber,client)) {
        printinfoclient(client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> answer;
        if (answer == 'Y' || answer == 'y') {

            saveclientdatetofile(fileclientsname);
            vclients = loadclientdatafromfile();
            cout << "\n\nclient Deleted Successfully.";

        }
  

    }
    else {
        cout << "there is no account number with ( " << accountnumber << " ) : " << endl;
    }
   
}
vector <stclient> updateclientdatetofile() {
    fstream myfile;
    myfile.open(fileclientsname, ios::out);
    string dataline;
    if (myfile.is_open()) {
        for (stclient& c : vclients) {
            if (c.markforupdate == true) {
                cout << "\nEnter PinCode? ";
                getline(cin >> ws, c.pincode);
                cout << "\nEnter Name? ";
                getline(cin, c.name);
                cout << "\nEnter Phone? ";
                getline(cin, c.phone);
                cout << "\nEnter AccountBalance? ";
                cin >> c.accountbalance;
                dataline = clientrecord(c);
                myfile << dataline << endl;
            }
            else {
                dataline = clientrecord(c);
                myfile << dataline << endl;
            }
        }
        myfile.close();
    }
    return vclients;
}
bool markclientforupdatebyaccountnumber(string accountnumber) {
    for (stclient& c : vclients) {
        if (c.accountnumber == accountnumber) {
            c.markforupdate = true;
            return true;
        }
    }
    return false;
}
void updateshowscreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";
}
bool updaterecordbyaccountnumber(string accountnumber) {
    stclient client;
    char Answer = 'n';
    if (findclientbyaccountnumber(accountnumber, client)) {
        printinfoclient(client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            markclientforupdatebyaccountnumber(accountnumber);
            updateclientdatetofile();
            cout << "\n\nClient updated Successfully.";
            return true;
        }
    }
    else {
        cout << "\nClient with Account Number (" << accountnumber << ") is Not Found!";
        return false;
    }
    return false;
}
void GoBackToMainMenue() {
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    mainmenuescreen();
}
void GoBacktomanageusers() {
    cout << "\n\nPress any key to go back to manage users menue...";
    system("pause>0");
    showmanageusersMenue();
}
void findclienttt() {

    findclientscreen();
    string accountnumber;
    cout << "enter acountnumber  : ";
    cin >> accountnumber;
    stclient client;
    if (findclientbyaccountnumber(accountnumber, client)) {
        printinfoclient(client);
    }
    else {
        cout << "there is no one with this acount number : " << accountnumber << endl;
    }

}
void UpdateClientt() {

    updateshowscreen();

    string accountnumber;

    cout << "\nenter acount number to update : ";
    cin >> accountnumber;

    updaterecordbyaccountnumber(accountnumber);

}
void perfromtheoption(enchoice choice) {

    vclients = loadclientdatafromfile();
    vadmins = loaduserdatafromfile();

    switch (choice) {
    case enchoice::showclient:
        system("cls");
        
        if (checkaccesspermision(enMainMenuePermissions::plistClients)) {
            Printallclientsdata();
        }
        else {

            ShowAccessDeniedMessage();
        }
  
        GoBackToMainMenue();
        break;
    case enchoice::addnewclient:
        system("cls");
        if (checkaccesspermision(enMainMenuePermissions::pAddNewClient)) {
            addnewclientt();
        }
        else {
            ShowAccessDeniedMessage();
        }
     
        GoBackToMainMenue();
        break;
    case enchoice::deleteclient:

        system("cls");
        if (checkaccesspermision(enMainMenuePermissions::pDeleteClient)) {

            deleteclientt();
            
        }
        else {

            ShowAccessDeniedMessage();
        }
        GoBackToMainMenue();
        break;
    case enchoice::updateclient:
        system("cls");
        if (checkaccesspermision(enMainMenuePermissions::pUpdateClients)) {

            UpdateClientt();
        }
        else {
            ShowAccessDeniedMessage();
        }
        GoBackToMainMenue();

        break;
    case enchoice::findclient:
        system("cls");
        if (checkaccesspermision(enMainMenuePermissions::pFindClient)) {
            findclienttt();
        }
        else {
            ShowAccessDeniedMessage();
        }
        GoBackToMainMenue();
        break;
    case enchoice::trans:
        system("cls");
        if (checkaccesspermision(enMainMenuePermissions::pTranactions)) {
            transactionmenue();
            mainmenuescreen();
        }
        else {
            ShowAccessDeniedMessage();
        }
        GoBackToMainMenue();
        break;
    case enchoice::manageusers:
        system("cls");
        if (checkaccesspermision(enMainMenuePermissions::pManageUsers)) {
            showmanageusersMenue();
        }
        else {
            ShowAccessDeniedMessage();
        }
        GoBackToMainMenue();
        break;
    case enchoice::exitt:
        system("cls");
        loginscreen();
    }
}
enchoice readyourchoice() {
    cout << "Choose what do you want to do? [1 to 8] : ";
    int num = 0;
    cin >> num;
    return (enchoice)num;
}
enmanageusers readyourchoicelist() {
    cout << "Choose what do you want to do? [1 to 6] : ";
    int num = 0;
    cin >> num;
    return (enmanageusers)num;
}
entrans readyourtranscation() {
    cout << "Choose what do you want to do? [1 to 4] : ";
    int num = 0;
    cin >> num;
    return (entrans)num;
}
void depositscreen() {
    cout << "------------------------------------------------\n";
    cout << "               deposit screen                   \n";
    cout << "------------------------------------------------\n";
}
void withdrawscreen() {
    cout << "------------------------------------------------\n";
    cout << "               withdraw screen                  \n";
    cout << "------------------------------------------------\n";
}
void printinfoclient(stclient c) {
    cout << "\nthe following are the client details : \n";
    cout << "----------------------------------------\n";
    cout << "Account number  : " << c.accountnumber << endl;
    cout << "pin code        : " << c.pincode << endl;
    cout << "Name            : " << c.name << endl;
    cout << "phone           : " << c.phone << endl;
    cout << "Account balance : " << c.accountbalance << endl;
    cout << "----------------------------------------\n";
}








void mainmenuescreen() {


    system("cls");
    cout << "===========================================\n";
    cout << "\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.  \n";
    cout << "\t[6] Transactions. \n";
    cout << "\t[7] manage users \n";
    cout << "\t[8] Exit.\n";
    cout << "===========================================\n";
    perfromtheoption(readyourchoice());

}





void loginscreen() {

    vclients = loadclientdatafromfile(fileclientsname);
    vadmins = loaduserdatafromfile(fileusername);



    cout << "-----------------------------\n";
    cout << "         login screen        \n";
    cout << "_____________________________\n\n";


    stadmin user;

    string username;
    int password;

    cout << "enter username ? ";
    cin >> username;
    cout << "enter password ? ";
    cin >> password;

    while (!validuser(username, password)) {

        cout << "\ninvalid username or password \n\n";
        cout << "enter username ? ";
        cin >> username;
        cout << "enter password ? ";
        cin >> password;

    }

    mainmenuescreen();

}


bool validuser(string username, int password) {


    for (int i = 0; i < vadmins.size(); i++) {



        if (vadmins[i].username == username && stoi(vadmins[i].password) == password) {

            currentuser = vadmins[i];

            return true;
        }


    }



    return false;

}



void showmanageusersMenue() {

    loaduserdatafromfile(fileusername);
    system("cls");
    cout << "===========================================\n";
    cout << "\tManage users Menu Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List users.\n";
    cout << "\t[2] Add New user.\n";
    cout << "\t[3] Delete user.\n";
    cout << "\t[4] Update user.\n";
    cout << "\t[5] Find user.  \n";
    cout << "\t[6] Main menu. \n";
    cout << "===========================================\n";

    performtheuseroption(readyourchoicelist());

}



void finduserrrr() {

    finduserscreen();
    string username;
    cout << "Enter username  : ";
    cin >> username;
    stadmin user;

    if (finduserbyaccountnumber(username, user)) {
        cout << endl;
        printinfouser(user);
    }
    else {
        cout << "there is no user with this account number : " << username << endl;
    }

}

void printinfouser(stadmin c) {


    cout << "the following are the user details : \n";
    cout << "----------------------------------------\n";
    cout << "user name          : " << c.username << endl;
    cout << "password           : " << c.password << endl;
    cout << "permissions        : " << c.permisionresult << endl;
    cout << "----------------------------------------\n";


}



vector<stadmin> loaduserdatafromfile(string Filename) {

    vadmins.clear();

    fstream MyFile;
    MyFile.open(Filename, ios::in);
    while (MyFile.is_open()) {

        string line;
        stadmin user;

        while (getline(MyFile, line)) {

            user = convertlinetorecorduser(line, "//");
            vadmins.push_back(user);

        }

        MyFile.close();
    }


    return vadmins;

}




stadmin convertlinetorecorduser(string line, string sperator = "//") {

       vector <string> v = splituserinfo(line, sperator);
       stadmin user;

        user.username = v[0];
        user.password = v[1];
        user.permisionresult = v[2];



        return user;

}

 




vector <string> splituserinfo(string name, string delim = "//") {

    vector<string> n;
    string sword;
    int pos = 0;

    while ((pos = name.find(delim)) != std::string::npos) {

        sword = name.substr(0, pos);

        if (sword != "") {
            n.push_back(sword);
        }

        name.erase(0, pos + delim.length());


    }



    if (name != "") {
        n.push_back(name);
    }

    return n;

}



bool  finduserbyaccountnumber(string username, stadmin& user) {

    vadmins = loaduserdatafromfile();



    for (stadmin& c : vadmins) {

        if (c.username == username) {
            user = c;
            return true;
        }

    }
    return false;

}


vector <stadmin> saveuserdatetofile(string fileusers = fileusername) {
    fstream myfile;
    myfile.open(fileusers, ios::out | ios::app);

    string dataline;

    if (myfile.is_open()) {


        for (stadmin& c : vadmins) {

            if (c.marktodelete == false) {

                dataline = userrecord(c);

                myfile << dataline << endl;

            }


        }


        myfile.close();

    }

    return vadmins;
}



string userrecord(stadmin user) {




    string recordline = user.username + "//" + user.password + "//" + user.permisionresult;


    return recordline;


}


void performtheuseroption(enmanageusers choice) {



    switch (choice) {

    case enmanageusers::listusers:
        system("cls");
        ShowAllUsersScreen();
        GoBacktomanageusers();
        break;
    case enmanageusers::addnewuserr:

        system("cls");
        addnewuserrr();
        GoBacktomanageusers();
        break;
    case enmanageusers::deleteuserrr:

        system("cls");
        deleteuserr();
        GoBacktomanageusers();
        break;
    case enmanageusers::updateuserr:
        system("cls");
        updateuser();
        GoBacktomanageusers();
        break;
    case enmanageusers::finduserr:
        system("cls");
        finduserrrr();
        GoBacktomanageusers();
        break;

    case enmanageusers::mainmenueee:

        mainmenuescreen();
        break;
    }

}



void addnewuserscreen() {

    cout << "\n-----------------------------------\n";
    cout << "\tAdd New users Screen";
    cout << "\n-----------------------------------\n";

}

bool checkclientuserfound(string username) {

    for (stadmin& c : vadmins) {

        if (c.username == username) {


            return true;
        }


    }

    return false;
}


void  askpermissions(stadmin& user) {

    char c;


    cout << "\nDo you want to give full access? y/n? ";
    cin >> c;

    if (c == 'y' || c == 'Y')
    {
        user.permisionresult = to_string(-1);
    
    }

    else {



        cout << "do you want to give access to : \n\n";




        cout << "show client list ? Y/N ? ";
        cin >> c;

        int result = 0;

        if (c == 'y' || c == 'Y') {


            result = result + enMainMenuePermissions::plistClients;
        }


        cout << "\nadd client list ? Y/N ? ";
        cin >> c;

        if (c == 'y' || c == 'Y') {


            result = result + enMainMenuePermissions::pAddNewClient;
        }

        cout << "\ndelete client list ? Y/N ? ";
        cin >> c;

        if (c == 'y' || c == 'Y') {


            result = result + enMainMenuePermissions::pDeleteClient;
        }

        cout << "\nupdate client list ? Y/N ? ";
        cin >> c;

        if (c == 'y' || c == 'Y') {


            result = result + enMainMenuePermissions::pUpdateClients;
        }

        cout << "\nfind client list ? Y/N ? ";
        cin >> c;

        if (c == 'y' || c == 'Y') {


            result = result + enMainMenuePermissions::pFindClient;
        }

        cout << "\ntranscations ? Y/N ? ";
        cin >> c;

        if (c == 'y' || c == 'Y') {

            result = result + enMainMenuePermissions::pTranactions;
        }



        cout << "\nmanage users ? Y/N ? ";

        cin >> c;


        if (c == 'y' || c == 'Y') {


            result = result + enMainMenuePermissions::pManageUsers;

        }

        user.permisionresult = to_string(result);


    }


}

stadmin readnewuser() {


    stadmin user;
    cout << "enter username : ";
    cin >> user.username;
    while (checkclientuserfound(user.username)) {

        cout << "the username of [ " << user.username << " ] : is already exsit \n";
        cout << "enter another username : ";
        cin >> user.username;

    }
    cout << "\nEnter password : ";
    cin >> user.password;

     askpermissions(user);

    return user;

}

void addnewuserrr() {

    char k;
    addnewuserscreen();

    do {
   
        cout << "\nAdding new user : \n\n";

        stadmin user;
        user = readnewuser();
        vadmins.push_back(user);
        string name = userrecord(user);
        adddatalinetofile(fileusername, name);



        cout << "\nuser added successfully , do you want to add more users ? Y/N ? ";
        cin >> k;

    } while (k == 'Y' || k == 'y');

}



void deleteuserscreen() {


    cout << "\n-----------------------------------\n";
    cout << "\tDelete users Screen";
    cout << "\n-----------------------------------\n\n";

}

void finduserscreen() {


    cout << "\n-----------------------------------\n";
    cout << "\tfind users Screen";
    cout << "\n-----------------------------------\n\n";

}

void findclientscreen() {


    cout << "\n-----------------------------------\n";
    cout << "\tFind client Screen";
    cout << "\n-----------------------------------\n\n";

}




vector <stadmin> saveadmindatetofile(string filename) {
    fstream myfile;
    myfile.open(filename, ios::out);

    string dataline;

    if (myfile.is_open()) {


        for (stadmin& c : vadmins) {

            if (c.marktodelete == false) {

                dataline = userrecord(c);

                myfile << dataline << endl;

            }



        }


        myfile.close();

    }



    return vadmins;



}



bool checkclientuserfoundforupdate(string username, stadmin& user) {

    for (stadmin& c : vadmins) {

        if (c.username == username) {
            c.markforupdate = true;
            user = c;
            return true;
        }


    }

    return false;
}

bool markuserfordelete(string username, stadmin &user) {

    for (stadmin& c : vadmins) {

        if (c.username == username) {

            c.marktodelete = true;
            user = c;
            return true;

        }


    }

    return false;

}



void deleteuserr() {


    deleteuserscreen();
    string username;
    cout << "please enter username : ";
    cin >> username;
    cout << endl;
    if (username == "Admin") {
        cout << "you can not delete this user , please contact your admin \n\n";

    }
    else {

        deleteuserbyusername(username);

    }


}

void updateuserscreen() {

    cout << "\n-----------------------------------\n";
    cout << "\tUpdate User Info Screen";
    cout << "\n-----------------------------------\n\n";
}

vector <stadmin> updateuserdatetofile() {

    fstream myfile;
    myfile.open(fileusername, ios::out);
    string dataline;

    if (myfile.is_open()) {


        for (stadmin& c : vadmins) {

            if (c.markforupdate == true) {

                cout << "\nenter password : ";
                cin >> c.password;
                askpermissions(c);
                dataline = userrecord(c);

                myfile << dataline << endl;

            }
            else {

                dataline = userrecord(c);
                myfile << dataline << endl;

            }


        }

        myfile.close();

    }

    return vadmins;
}


bool updateuserrecordbyusername(string username) {


    stadmin user;
    char Answer = 'n';

    if (checkclientuserfoundforupdate(username, user))
    {

        cout << endl;
        printinfouser(user);
        cout << "\n\nAre you sure you want update this client? y/n ? ";

        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            vadmins = updateuserdatetofile();
            cout << "\n\nuser updated Successfully.";


        }


        return true;

    }
    else {

        cout << "\nUser with Username (" << username << ") is Not Found!";

        return false;

    }


}

void updateuser() {


    updateuserscreen();

    string username;
    cout << "Enter username to update : ";
    cin >> username;
    updateuserrecordbyusername(username);

}



void askforwithdraw(stclient& c) {

    int withdraw = 0;
    cout << "enter the amount of withdraw : ";
    cin >> withdraw;

    while (withdraw > stoi(c.accountbalance)) {
        cout << "Amount exceeds the account balance , you can with draw up to [" << c.accountbalance << "]  \n\n";
        cout << "please enter another amount : ";
        cin >> withdraw;

    }
    char  ch;
    cout << "\nare you sure to perform this operation ? [Y/N]  : ";
    cin >> ch;


    if (ch == 'Y' || ch == 'y') {
        c.accountbalance = to_string(stoi(c.accountbalance) - withdraw);
        cout << "\n\nthe operation done successfully \n";

    }



}
vector <stclient> updateclientaccountbalancedeposit_withdraw(entrans choice, string accountnumber) {

    vclients = loadclientdatafromfile();



    for (stclient& c : vclients) {

        if (c.accountnumber == accountnumber && choice == entrans::deposit) {

            int deposit = 0;
            cout << "\nEnter the amount of deposit : ";
            cin >> deposit;
            char g;
            cout << "\nAre you sure to perform this operation ? [y/n] : ";
            cin >> g;
            if (g == 'Y' || g == 'y') {

                c.accountbalance = to_string(stoi(c.accountbalance) + deposit);
                cout << "\n\nthe operation done successfully \n";

            }





        }
        else if (c.accountnumber == accountnumber && choice == entrans::withddraw) {

            askforwithdraw(c);

        }



    }

    return vclients;
}
bool findclientdeposit_withdraw(string accountnumber, stclient& client, entrans t) {


    vector <stclient>vclients = loadclientdatafromfile(fileclientsname);

    for (stclient& c : vclients) {

        if (c.accountnumber == accountnumber) {
            if (t == entrans::deposit) {
                c.markfordeposit = true;
                client = c;
            }
            else if (t == entrans::withddraw) {
                c.maarkforwithdraw = true;
                client = c;
            }
            return true;
        }

    }
    return false;

}
void updateaccountbalance(entrans trans) {

    bool t = true;
    cout << "\n enter the account number ? ";
    string acountnum;
    while (t) {

        getline(cin>>ws,acountnum);
        stclient client;
        if (findclientdeposit_withdraw(acountnum, client, trans)) {

            printinfoclient(client);
            vclients = updateclientaccountbalancedeposit_withdraw(trans, acountnum);
            saveclientdatetofile(fileclientsname);
            t = false;

        }
        else {

            cout << "client with [ " << acountnum << " ] does not exist \n\n";
            cout << "please enter another account number : ";
        }

    }




}
void printbalancetable(stclient client) {

    cout << "| " << setw(15) << left << client.accountnumber;
    cout << "| " << setw(40) << left << client.name;
    cout << "| " << setw(12) << left << client.accountbalance;
}
void ShowTotalBalances()
{
    vclients = loadclientdatafromfile(fileclientsname);
    cout << "\n\t\t\t\t\tBalances List (" << vclients.size() << ")Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    double TotalBalances = 0;
    if (vclients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else
        for (stclient Client : vclients)
        {
            printbalancetable(Client);
            TotalBalances += stoi(Client.accountbalance);
            cout << endl;
        }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "\t\t\t\t\t Total Balances = " << TotalBalances;
}

void performtranscationoperation(entrans choice) {

    vclients = loadclientdatafromfile();

    switch (choice) {

    case entrans::deposit:

        system("cls");
        depositscreen();
        updateaccountbalance(choice);
        GoBackToTransactionsMenue();
        break;

    case entrans::withddraw:
        system("cls");
        withdrawscreen();
        updateaccountbalance(choice);
        GoBackToTransactionsMenue();
        break;


    case entrans::totalbalancies:
        system("cls");
        ShowTotalBalances();
        GoBackToTransactionsMenue();
        break;

    case entrans::mainmenuee:

       
        break;

    }


}
void transactionmenue() {

    system("cls");
    cout << "===========================================\n";
    cout << "\ttransactions Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] DEPOSIT.\n";
    cout << "\t[2] WITHDRAW.\n";
    cout << "\t[3] SHOW TOTAL BALANCIES.\n";
    cout << "\t[4] BACK TO MAIN MENUE.\n";
    cout << "===========================================\n";
    performtranscationoperation(readyourtranscation());



}





void ShowAccessDeniedMessage()
{
    cout << "\n------------------------------------\n";
    cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";
    cout << "\n------------------------------------\n";

}

bool checkaccesspermision(enMainMenuePermissions permission) {

    if (stoi(currentuser.permisionresult) == enMainMenuePermissions::eAll) {
        return true;
    }

    if ((stoi(currentuser.permisionresult) & permission) == permission) {
        return true;
    }

    return false;

}







int main() {



    loginscreen();

    return 0;
}
