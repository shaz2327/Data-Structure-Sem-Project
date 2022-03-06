#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct node
{
	string candidatename;
	string party_request;
	string consti;
	node* next;
};
node *f , *r,  * tp, *prev;

fstream constituencies("constituencies.txt", ios::out | ios::in);
fstream party_names("partynames.txt", ios::out | ios::in);
fstream party_username("usernames.txt", ios::out| ios::in);
fstream party_password("passwords.txt", ios::out| ios::in);
fstream candid_names("candid_names.txt", ios::out | ios::in);
fstream candid_party("candid_party.txt", ios::out | ios::in);
fstream candid_consti("candid_constituency", ios::out | ios::in);
fstream voter_cnic("voter cnic.txt", ios::out| ios::in);
fstream voter_password("voter password.txt", ios::out | ios::in);
fstream voter_constituency("voter constituency.txt", ios::out | ios::in);
static int count = 0;
string party_name;

void displayConstituency()
{
	constituencies.open("constituencies.txt");
	string get_file;
	while (getline(constituencies, get_file))
	cout << get_file << endl;

}


void voter_regist()
{
    // Proccess for voter registeration

    string cnic,password,consti;

    cout << "\n\nEnter unique CNIC number\n";
    cin.ignore();
    getline(cin, cnic);

    string get_file;
    bool flag = false;

    while (getline(voter_cnic, get_file))
    {
        if (get_file.compare(cnic) == 0)
        {
            flag = true;
            break;
        }
    }

    if (flag == true)
    {
    cout << "\nCNIC already exists, please enter your own \n";
    }
    else
    {
        ofstream voter_cnic("voter cnic.txt", ios::app);
        voter_cnic << cnic << endl;
        voter_cnic.close();
    }

    // Now for the password
    cout << "Your CNIC has been approved now please enter a safe password for your account login\n";
    cin >> password;
    ofstream voter_password("voter password.txt", ios::app);
    voter_password << password<<endl;
    voter_password.close();

    //Now for the constituency
    displayConstituency();
    cout << "\n Please choose the constituency you belong to and enter it to be registered on it's premises\n";
        cin >> consti;
        ofstream voter_constituency("voter constituency.txt", ios::app);
        voter_constituency << consti << endl;
        voter_constituency.close();
}

void reg_independent_candid()
{
	
	string candidatename;
	string party = "independent";
	string consti;
	string constituency;

	                                              //Registering an independent candidate

    // Proccess for party candidate's name and enqueue his request

	cout << "\nEnter independent candidate's name : ";
	cin.ignore();
	getline(cin, candidatename);

	//proccess for party candidate's constituency

	cout << "\nWhich constituency would you like to register in ? :\n";
	while (getline(constituencies,constituency))
	{
	cout << constituency << endl;
	}
	constituencies.close();
	cout << "\n";
	getline(cin, consti);
	cout<<"\nYou have been successfully registered as a candidate\n ";
	
	int counter = 0; string symbol;
	ifstream indcandid_symbols("indcandidsymbols.txt");  //symbols file opened
	while (counter <= count)  //skipping line to alotting corresponding symbol with count variable
	{
		getline(indcandid_symbols, symbol);
		if (counter == count)
		{
			cout << "\nYour party symbol is : \n" << symbol;
		}
		counter = counter + 1;
	}
	count = count + 1;
	indcandid_symbols.close();

	ofstream candid_names("candid_names.txt", ios::app);
	ofstream candid_party("candid_party.txt", ios::app);
	ofstream candid_consti("candid_constituency", ios::app);

	candid_names << candidatename;
	candid_party << party;
	candid_consti << consti;
	candid_names.close();
	candid_party.close();
	candid_consti.close();
	
}



void reg_party_candid ()
{
	string constituency;

    //Registering a party candidate
    

    // Proccess for party candidate's name and enqueue his request
	
	r = new node;
	cout << "\nEnter party candidate's name : ";
	cin.ignore();
	getline(cin, r->candidatename);
	
	 // proccess for party candidate's party
    
    cout<<"Which party would you like to be registered on ? : \n";
    string line;
    while(getline(party_names, line))
    cout << line << endl;
	party_names.close();
	cout<<"\n";
	getline(cin, r->party_request);
	
	//proccess for party candidate's constituency
	
    cout<<"\nWhich constituency would you like to register in ? :\n";
   	while(getline(constituencies,constituency))
	{
    cout<<constituency<<endl;
	}
	constituencies.close();
	cout<<"\n";
	getline(cin, r->consti);
	f->next=r;
	r->next=NULL;
}


void requests()  //approve or disapprove requests as a queue
{
	int p;
	string party_name;
	
	cout<<"What is your party's name\n";
	cin>>party_name;
	
		cout<<"Remaining requests"<<endl;
		for ( tp = f; tp != NULL; tp = tp->next)
	{
		if(tp->party_request == party_name)
	{
	cout << "Candidate name : " << tp->candidatename << endl;
    cout<<"press 1 to approve or press 2 to disapprove  : ";
	cin>>p;
	if(p==1)
	{
	cout << "approved candidate is " << tp->candidatename << endl;
	
	// to be registered at the end, once party approves

    ofstream candid_names("candid_names.txt", ios::app);
	ofstream candid_party("candid_party.txt", ios::app);
	ofstream candid_consti("candid_constituency", ios::app);
	
	candid_names<< tp->candidatename << endl;
	candid_party<< tp->party_request << endl;
	candid_consti << tp->consti << endl;
	candid_names.close();
	candid_party.close();
	candid_consti.close();
	}
	
	if(p==2)
	cout << "disapproved candidate is " << tp->candidatename << endl;
	
	for(prev=f; prev->next != tp->next; prev=prev->next)
{
	if(prev->next==tp)
	{
	prev->next=tp->next;
	tp->next=NULL;
    break;
	}
}
	}
	}
	
}

void party_login()
{
	static int count = 0;
	int option;
	string  get_file, username, password;
	bool flag = false;
	cout << "\nWhat is your party name ?\n";
	getline(cin, party_name);

	while (getline(party_names, get_file)) // loop to check wether party name already exists or not in the party_names file
	{
		if (get_file.compare(party_name) == 0)
		{
			flag = true;
			break;
		}
		count = count + 1;
	}

	// When party name is checked that it exits, time to enter the password
	if (flag == true)
	{
		cout << "\nParty name exists, please enter username\n";
		cin >> username;

		int counter = 0; flag = false;
		while (counter <= count)  //skipping lines to check username
		{
			getline(party_username, get_file);
			if (counter == count)
			{
				if(username==get_file)
				flag = true;
			}
			counter = counter + 1;
		}
		count = count + 1;
		party_username.close();

		// When username is approved then time for the password
		if (flag == true)
		{
			cout << "\nNow please enter the password for the username\n";
			cin >> password;

			counter = 0; flag = false;
			while (counter <= count)  //skipping lines to check username
			{
				getline(party_password, get_file);
				if (counter == count)
				{
					if (password == get_file)
						flag = true;
				}
				counter = counter + 1;
			}
			count = count + 1;
			party_password.close();

			cout << "\nWhat would you like to do ?\n";
			cout << "(1) Approve/reject request of ticket \n(2)Check results of voting is done\n";
			cin >> option;

			if (option == 1)
				requests();
			/*if (option ==2)
			vote results function(); later to be added
			*/	
		}
    }

	else
	{
		cout << "Party does not exist, redirecting you to the main menu\n";
	}
}


void register_party()
{
	string name;
	string symbol;
	string username;
	string password;
	string get_file;
	bool flag = false;

	// Proccess for party name 

	cout << "\n\nEnter unique party name\n";
	cin.ignore();
	getline(cin, name);


	while (getline(party_names, get_file)) // loop to check wether party name already exists or not in the party_names file
	{
		if (get_file.compare(name) == 0)
		{
			flag = true;
			break;
		}
	}

	if (flag == true)
	{
		cout << "\nParty name already exists, try another one\n";
		int e;
		cout << "To return to main menu, enter a number : ";
		cin >> e;
	}
	else
	{
		ofstream party_names("partynames.txt", ios::app);
		party_names << name ;
		cout << "Your Party name has been registered\n";
		party_names.close();
	}


	ifstream party_symbols("symbols.txt");   //symbols file opened

	int counter = 0;
	while (counter <= count)  //skipping line to alotting corresponding symbol with count variable
	{
		getline(party_symbols, symbol);
		if (counter == count)
		{
			cout << "\nYour party symbol is : \n" << symbol;
		}
		counter = counter + 1;
	}
	count = count + 1;
	party_symbols.close();



	// Proccess for username 

	cout << "\n\nEnter unique party username\n";
	cin.ignore();
	getline(cin, username);

	ofstream party_username("usernames.txt", ios::app);
	party_username << username ;
	party_username.close();


	// Proccess for password 

	cout << "Enter unique party password\n";
	cin.ignore();
	getline(cin, password);

	ofstream party_password("passwords.txt", ios::app);
	party_password << password ;
	party_password.close();
	
	cout<<"\n Your party has been registered\n";
}

void registerConstituency()
{
	// Proccess for constituency
	string consti;
	cout << "\n\nEnter unique constituency\n";
	cin.ignore();
	getline(cin, consti);

	string get_file;
	bool flag = false;

	while (getline(constituencies, get_file))
	{
		if (get_file.compare(consti) == 0)
		{
			flag = true;
			break;
		}
	}

	if (flag == true)
	{
		cout << "\nConstituency already exists, try another one\n";
		int e;
		cout << "To return to main menu, enter a number : ";
		cin >> e;
	}
	else
	{
		ofstream constituencies("constituencies.txt", ios::app);
		constituencies << consti << endl;
		cout << "Your Constituency has been registered\n";
		constituencies.close();
	}
}

void updateOrDelete()
{
	string deleteline;
	string line;

	ofstream temp("temp.txt", ios::app);
	cout << "Which constituency do you want to remove? \n";
	cin >> deleteline;

	while (getline(constituencies, line))
	{
		if (line != deleteline)
		{
			temp << line << endl;
		}
	}

	temp.close();
	constituencies.close();
	remove("constituencies.txt");
	rename("temp.txt", "constituencies.txt");
}


void menu()
{
    cout << "Select an option:" << endl << endl;
	cout << "1) Register a national assembly constituency (e.g. NA-1)\n";
	cout << "2) List all constituencies\n" ;
	cout << "3) Update/Delete Constituencies \n" ;
	cout << "4) Register a political party\n" ; 
	cout << "5) Register as a party candidate\n" ; 
	cout << "6) Register as an independent candidate\n"; 
	cout << "7) Register as a voter\n"; 
	cout << "8) Login the party portal\n"; 
	cout << "9) Exit Election Commission Login\n\n";
	int option;
	cout << "option: "; cin >> option;

	system("CLS");
	switch (option) {
	case 1:
		registerConstituency();
		break;

	case 2:
		displayConstituency();
		break;
	case 3:
		updateOrDelete();
		break;

	case 4:
		register_party();
		break;
	
	case 5:
	    reg_party_candid ();	
	    break;
	    
    case 6:
    	reg_independent_candid();
    	break;
    	
    case 7:
    	voter_regist();
    	break;
	    
	case 8: 
	party_login();	 
		 	
    case 9: // EXIT 
    	break;
    
	default:// Invalid option
		cout << "INVALID OPTION!!" << endl;
		break;
	}
}



int main()
{


	// THE PROGRAM'S LOGIN SYSTEM WITH USERNAME AND PASSWORD OF "admin"
	string elec_user = "admin";
	string elec_pass = "admin";
	string enter_user, enter_pass;
    cout << "\t\t\t\t\tWELCOME TO THE ELECTIONS OF 2020\n\n Please enter the username and password to perform one of the operations of the election\n\n";
	cin >> enter_user;
	cin >> enter_pass;
	if (enter_user != elec_user || enter_pass != elec_pass)
	{
		cout << "\nWrong username or password entered, please try again \n";
	}
	else
	for(;;)
{	
	menu();
	
	int exit;
	cout<<"\nPress any number to go to main menu\n";
	cin>>exit;
	system("CLS");
}
}
