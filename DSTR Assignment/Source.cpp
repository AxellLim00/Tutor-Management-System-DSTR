#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>

using namespace std;

struct date {
	int date, month, year;
};//Strcuture for keeping a date format
struct tutor {
	char name[50] = {}, address[150] = {}, tcName[50] = {}, sName[50] = {};// 'tc' is Tuition Center, 's' is Subject.
	string iD, phone, tcCode, sCode;
	double hpr;
	int rating;
	date dJoin, dTerminate;// 'd' is Date.
	tutor* next = nullptr, * prev = nullptr;
} * head, * pointer, * headSearch, * tail; // main tutor structure node
struct sortedTutor {
	tutor* info;
	sortedTutor * next = nullptr, * prev = nullptr;
}* headSort, * tailSort, *pointerSort; // only used for sorting, temporary linked list

void mainmenu();
void error();
void add();
void edit();
bool contin();
void delet();
void display();
void searchCriteria();
bool searchTutor(string);
tutor* searchResult(string);
void readFile();
void saveFile();
void searchID();
void searchRating();
void sort(char);


int main()
{
	head = tail = NULL;
	readFile();
	mainmenu();
	return 0;
}// initial start, read file first then to main menu

void mainmenu() {
	string mm;
	cout << "Welcome to eXcel Tuition Centre Tutor System" << endl
		<< "\t(a) Display Tutor List" << endl << "\t(b) Add Tutor" << endl
		<< "\t(c) Modify Tutor Info" << endl << "\t(d) Delete Tutor Info/Terminate Tutor"
		<< endl << "\t(x) Exit" << endl << "Choose the letter to the next menu : ";
	cin >> mm;
	mm[0] = tolower(mm[0]);// capital input included

	if (mm == "a") {
		system("CLS");
		sort('o'); //initial sort which is default how the linked is, start from head of the master linked list
		pointerSort = headSort;// initializing the pointer or current soreted Tutor
		display();
	}
	else if (mm == "b") {
		system("CLS");
		add();
	}
	else if (mm == "c") {
		system("CLS");
		edit();
	}
	else if (mm == "d") {
		system("CLS");
		delet();
	}
	else if (mm == "x") {
		system("CLS");
		saveFile();// saving file
		cout << "Thank your for using eXcel Tuition Centre Tutor System" << endl;
		system("PAUSE");
		exit(0);//exit program
	}
	else {
		error();
		mainmenu();
	}
}

void error() {
	cout << "\n\nINPUT INVALID, please read the instructions";
	system("PAUSE");
	system("CLS");
}// makes it easier to print error message

void add() {
	tutor newTutor;
	cout << "Enter the following Information of the new Tutor (0 to go back to Main Menu): " << endl << "Name\t\t\t: ";
	cin.ignore();
	cin.getline(newTutor.name, sizeof(newTutor.name));
	if (newTutor.name[0] == '0') {
		system("PAUSE");
		system("CLS");
		mainmenu();
	}
	else {
		time_t present = time(NULL);
		tm* local = localtime(&present);// geting local time
		newTutor.dJoin.year = local->tm_year + 1900;// year starts from 1900 and above
		newTutor.dJoin.month = local->tm_mon + 1;//month starts from 0
		newTutor.dJoin.date = local->tm_mday;
		newTutor.dTerminate.year = 0;
		newTutor.dTerminate.month = 0;
		newTutor.dTerminate.date = 0;// initializing no terminate date since, you just add him or her
		cout << "Hourly Pay Rate\t\t: ";
		cin >> newTutor.hpr;
		cout << "Phone\t\t\t: ";
		cin >> newTutor.phone;
		cout << "Address\t\t\t: ";
		cin.ignore();
		cin.getline(newTutor.address, sizeof(newTutor.address));
		cout << "Tuition Centre Code\t: ";
		cin >> newTutor.tcCode;
		cout << "Tuition Centre Name\t: ";
		cin.ignore();
		cin.getline(newTutor.tcName, sizeof(newTutor.tcName));
		cout << "Subject Code\t\t: ";
		cin >> newTutor.sCode;
		cout << "Subject Name\t\t: ";
		cin.ignore();
		cin.getline(newTutor.sName, sizeof(newTutor.sName));
		newTutor.next = NULL;
		cout << "Rating\t\t\t: ";
		cin >> newTutor.rating;

		string month, date, hour, min, sec;// this process is to create a ID based on the time created
		if (newTutor.dJoin.month < 10)
			month = "0" + to_string(newTutor.dJoin.month);
		else
			month = to_string(newTutor.dJoin.month);
		if (newTutor.dJoin.date < 10)
			date = "0" + to_string(newTutor.dJoin.date);
		else
			date = to_string(newTutor.dJoin.date);
		if (local->tm_hour < 10)
			hour = "0" + to_string(local->tm_hour);
		else
			hour = to_string(local->tm_hour);
		if (local->tm_min < 10)
			min = "0" + to_string(local->tm_min);
		else
			min = to_string(local->tm_min);
		if (local->tm_sec < 10)
			sec = "0" + to_string(local->tm_sec);
		else
			sec = to_string(local->tm_sec);

		newTutor.iD = to_string(newTutor.dJoin.year) + month + date + hour + min + sec;
		newTutor.next = head;// adding to Linked List
		if (head != NULL)
			head->prev = &newTutor;
		head = &newTutor;
		newTutor.prev = NULL;
	}
	cout << endl << "Tutor Added Successfully" << endl;
	system("PAUSE");
	system("CLS");
	mainmenu();//back to main menu 
}

void edit() {
	char choice;
	string TutorID;
	tutor* tutorEdit = new tutor;

	cout << "Enter TutorID to edit ('x' to go back to main menu): ";
	cin >> TutorID;

	if (TutorID != "x") {
		if (searchTutor(TutorID)) {
			tutorEdit = searchResult(TutorID);
			cout <<"\nWhich info to edit?" << endl << "(a) Phone\n(b) Address\n(x) Back to menu" << endl 
				<< "Choose the letter : ";
			cin >> choice;
			choice = tolower(choice);

			switch (choice) {
			case 'a':
				cout << "New Phone : ";
				cin >> tutorEdit->phone;

				break;
			case 'b':
				cout << "New Address : ";
				cin.ignore();
				cin.getline(tutorEdit->address, sizeof(tutorEdit->address));

				break;
			case 'x':// to go back to main menu
				system("CLS");
				mainmenu();

				break;
			default:
				error();
				edit();
				break;
			}

			if (contin()) {// ask if the user wants to edit anything else
				system("CLS");
				edit();
			}
			else {
				system("CLS");
				mainmenu();
			}
		}
		else {
			cout << "Tutor not found, please make sure the ID is correct";
			system("PAUSE");
			system("CLS");
			edit();
		}
	}
	else {
		system("CLS");
		mainmenu();
	}
}

bool contin() {
	char cont;
	cout << "\nDo you wish to go further?(y/n) : ";
	cin >> cont;
	cont = tolower(cont);

	switch (cont)
	{
	case 'y':
		return true;
		break;
	case 'n':
		system("CLS");
		return false;
		break;
	default:
		error();
		contin();
		break;
	}
}// ask if the user wants to continue function

void delet() {
	string TutorID;
	char choice;
	tutor* tutorDelete{};
	//choose to terminate or delete from file text
	cout << "Would you Like to (a) Terminate Tutor or (b) Delete Info from Database : ";
	cin >> choice;
	choice = tolower(choice);
	if (choice != 'a' && choice != 'b') {
		error();
		delet();
	}

	cout << "Enter TutorID to delete ('x' to go back to main menu): ";
	cin >> TutorID;

	if (TutorID != "x") {
		if (searchTutor(TutorID)) {
			tutorDelete = searchResult(TutorID);// get tutor info
			cout << "Name\t\t\t: " << tutorDelete->name << endl << "Date Joined\t\t: " << tutorDelete->dJoin.date <<
				"-" << tutorDelete->dJoin.month << "-" << tutorDelete->dJoin.year << endl << "Date Terminated\t\t: ";
			if (tutorDelete->dTerminate.year == NULL)// showing the tutor info
				cout << "NULL" << endl;
			else
				cout << tutorDelete->dTerminate.date << "-" << tutorDelete->dTerminate.month << "-" <<
				tutorDelete->dTerminate.year << endl;
			cout << "Hourly Pay Rate\t\t: " << tutorDelete->hpr << endl << "Phone\t\t\t: " << tutorDelete->phone <<
				endl << "Address\t\t\t: " << tutorDelete->address << endl << "Tuition Centre Code\t: " << tutorDelete->tcCode <<
				endl << "Tuition Centre Name\t: " << tutorDelete->tcName << endl << "Subject Code\t\t: " << tutorDelete->sCode <<
				endl << "Subject Name\t\t: " << tutorDelete->sName << endl << "Rating\t\t\t: ";
			if (tutorDelete->rating == NULL)
				cout << "No Rating at the moment" << endl;
			else {
				cout << tutorDelete->rating << endl;
			}
			if (contin()) {//asking if they are sure
				time_t present = time(NULL);
				tm* local = localtime(&present);// this is local time for the terminate option
				switch (choice) {
				case 'a'://if terminate
					if (tutorDelete->dTerminate.year != NULL) {
						cout << "Tutor has already been Terminated";
						system("PAUSE");
					}
					else {// just add the date from the local time
						tutorDelete->dTerminate.year = local->tm_year + 1900;
						tutorDelete->dTerminate.month = local->tm_mon + 1;
						tutorDelete->dTerminate.date = local->tm_mday;
						cout << "\nTutor has been Successfully Terminated\n";
						system("PAUSE");
						system("CLS");
						mainmenu();
					}
				case 'b'://if delete
					if (tutorDelete->dTerminate.year != 0) {
						tm timeTerminate;
						timeTerminate.tm_year = tutorDelete->dTerminate.year - 1900;//can't get past here
						timeTerminate.tm_mon = tutorDelete->dTerminate.month - 1;
						timeTerminate.tm_mday = tutorDelete->dTerminate.date;
						timeTerminate.tm_hour = 0;
						timeTerminate.tm_min = 0;
						timeTerminate.tm_sec = 0;
						time_t Terminate = mktime(&timeTerminate);// get time difference to now
						double days = round(difftime(present, Terminate) / (24.0 * 60 * 60));
						if (days < 180) {//check for 6 months
							cout << "\nTutor can only be deleted after 6 months (180 days)\n";
							system("PAUSE");
						}
						else {
							if (tutorDelete->prev == NULL) {
								head = tutorDelete->next;
								tutorDelete->next->prev = NULL;
								delete tutorDelete;
							}
							else if (tutorDelete->next == NULL) {
								tutorDelete->prev->next = NULL;
								delete tutorDelete;
							}
							else {
								tutorDelete->prev->next = tutorDelete->next;
								tutorDelete->next->prev = tutorDelete->prev;
								delete tutorDelete;
							}
							cout << "\nTutor has been successfully deleted\n";
							system("PAUSE");
						}
					}
					else {
						cout << "\nTutor has Not been terminated, please Terminate the tutor and Wait 6 Months to Delete\n";
						system("PAUSE");
					}
				}
			}
		}
		else {
			cout << "\nTutor not found, please make sure the ID is correct\n";
			system("PAUSE");
		}
		
	}
	else {
		system("CLS");
		mainmenu();
	}
	system("CLS");
	delet();
}

void display() {
	char choice, listOrder;
	//showing tutor info
	cout << "ID\t\t\t: " << pointerSort->info->iD << "\nName\t\t\t: " << pointerSort->info->name << "\nDate Joined\t\t: " << pointerSort->info->dJoin.date <<
		"-" << pointerSort->info->dJoin.month << "-" << pointerSort->info->dJoin.year << "\nDate Terminated\t\t: ";
	if (pointerSort->info->dTerminate.year != NULL)
		cout << pointerSort->info->dTerminate.date << "-" << pointerSort->info->dTerminate.month << "-" <<
		pointerSort->info->dTerminate.year << endl;
	else
		cout << "NULL\n";
	cout << "Hourly Pay Rate\t\t: " << pointerSort->info->hpr << "\nPhone\t\t\t: " << pointerSort->info->phone << 
		"\nAddress\t\t\t: " << pointerSort->info->address << "\nTuition Centre Code\t: " << pointerSort->info->tcCode <<
		"\nTuition Centre Name\t: " << pointerSort->info->tcName << "\nSubject Code\t\t: " << pointerSort->info->sCode <<
		"\nSubject Name\t\t: " << pointerSort->info->sName << "\nRating\t\t\t: ";
	if (pointerSort->info->rating == NULL)
		cout << "No Rating at the moment" << endl << endl;
	else {
		cout << pointerSort->info->rating << endl << endl;
	}
	//option 1 to do with the list
	cout << "Choose what to do : \n(a) Sort the list\n(b) Search Tutor Info/Detail\n(x) Go back to main menu\n(<) Previous\t(>) Next\nYour Choice : ";
	cin >> choice;
	choice = tolower(choice);
	switch (choice)
	{
	case 'a'://to sort
		cout << endl << "Which Order :\n(a) Tutor iD\n(b) Tutor Hourly Pay Rate\n(c) Tutor Overall Performance (Rating)\n Order : ";
		cin >> listOrder;
		listOrder = tolower(listOrder);
		if (listOrder != 'a' && listOrder != 'b' && listOrder != 'c') {
			error();
			display();
			break;
		}
		else {
			system("CLS");
			sort(listOrder);
			pointerSort = headSort;
			display();
			break;
		}
	case 'b'://to search
		system("CLS");
		searchCriteria();
		break;
	case 'x':
		system("CLS");
		mainmenu();
		break;
	case '<':
		if (pointerSort->prev == NULL) {
			cout << endl << "This is the First Tutor in the List.";
			system("PAUSE");
		}
		else {
			pointerSort = pointerSort->prev;
		}
		system("CLS");
		display();
		break;
	case '>':
		if (pointerSort->next == NULL) {
			cout << endl << "This is the Last Tutor in the List.";
			system("PAUSE");
		}
		else {
			pointerSort = pointerSort->next;
		}
		system("CLS");
		display();
		break;
	default:
		error();
		display();
	}
}

void sort(char order) {
	pointerSort = NULL;
	headSort = NULL;

	switch (order)
	{
	case 'a':// according to tutor ID
		pointer = head;
		while (pointer != NULL) {
			sortedTutor* sorted = new sortedTutor;
			sorted->next = sorted->prev = NULL;
			sorted->info = pointer;
			if (headSort == NULL) {
				headSort = tailSort = sorted;
			}
			else {
				sorted->next = headSort;
				headSort = sorted;
				sorted->next->prev = sorted;
			}
			pointer = pointer->next;
		}
		break;

	case 'b':// sort by Hour rate
		pointer = head;
		while (pointer != NULL) {
			sortedTutor* sorted = new sortedTutor;
			sorted->next = sorted->prev = NULL;
			sorted->info = pointer;
			if (headSort == NULL) 
				headSort = tailSort = sorted;
			else {
				pointerSort = headSort;
				while (pointerSort != NULL) {
					if (pointer->hpr <= pointerSort->info->hpr) {
						if (pointerSort == headSort) {
							headSort = sorted;
							sorted->next = pointerSort;
							pointerSort->prev = sorted;
						}
						else {
							sorted->next = pointerSort;
							sorted->prev = pointerSort->prev;
							pointerSort->prev = sorted;
							sorted->prev->next = sorted;
						}
						break;
					}
					pointerSort = pointerSort->next;
				}
				if (pointerSort == NULL) {
					sorted->next = NULL;
					sorted->prev = tailSort;
					tailSort->next = sorted;
					tailSort = sorted;
				}
			}
			pointer = pointer->next;
		}
		break;

	case 'c':// sort by rating
		pointer = head;
		while (pointer != NULL) {
			sortedTutor* sorted = new sortedTutor;
			sorted->next = sorted->prev = NULL;
			sorted->info = pointer;
			if (headSort == NULL)
				headSort = tailSort = sorted;
			else {
				pointerSort = headSort;
				while (pointerSort != NULL) {
					if (pointer->rating <= pointerSort->info->rating) {
						if (pointerSort == headSort) {
							headSort = sorted;
							sorted->next = pointerSort;
							pointerSort->prev = sorted;
						}
						else {
							sorted->next = pointerSort;
							sorted->prev = pointerSort->prev;
							pointerSort->prev = sorted;
							sorted->prev->next = sorted;
						}
						break;
					}
					pointerSort = pointerSort->next;
				}
				if (pointerSort == NULL) {
					sorted->next = NULL;
					sorted->prev = tailSort;
					tailSort->next = sorted;
					tailSort = sorted;
				}
			}
			pointer = pointer->next;
		}
		break;

	case 'o':// default by the master linked list, just reversed tutorID
		pointer = tail;
		while (pointer != NULL){
			sortedTutor* sorted = new sortedTutor;
			sorted->next = sorted->prev = NULL;
			sorted->info = pointer;
			if (headSort == NULL) {
				headSort = tailSort = sorted;
			}
			else{
				sorted->next = headSort;
				headSort = sorted;
				sorted->next->prev = sorted;
			}
			pointer = pointer->prev;
		}
		break;

	default:
		cout << "error order in sort function does not exist";
		system("PAUSE");
		system("CLS");
		mainmenu();
		break;
	}
}

void searchCriteria() {
	char search;
	cout << "Which will you search by :\n(a) Tutor ID\n(b) Overall Performance (Rating)\n(x) Back to Previous Menu\n(m) Back to Main Menu\nSearch Option : ";
	cin >> search;
	search = tolower(search);
	switch (search)
	{
	case 'a':// return only one, by ID
		system("CLS");
		searchID();
		system("PAUSE");
		system("CLS");
		searchCriteria();
		break;
	case 'b'://will search the rating and show all with the same rating
		system("CLS");
		searchRating();
		system("PAUSE");
		system("CLS");
		searchCriteria();
		break;
	case 'x':
		system("CLS");
		display();
		break;
	case 'm':
		system("CLS");
		mainmenu();
		break;
	default:
		error();
		searchCriteria();
		break;
	}
}

void searchID() {
	string id;
	tutor* searchresult{};
	cout << endl << "Enter the Tutor ID to show more info(0 to go back, -1 to Main Menu)\t: ";
	cin >> id;
	if (id == "0") {
		system("PAUSE");
		system("CLS");
		searchCriteria();
	}
	else if (id == "-1") {
		system("PAUSE");
		system("CLS");
		mainmenu();
	}
	else if (searchTutor(id)) {
		searchresult = searchResult(id);// get tutor info
		cout << "\n\nName\t\t\t: " << searchresult->name << endl << "Date Joined\t\t: " << searchresult->dJoin.date <<
			"-" << searchresult->dJoin.month << "-" << searchresult->dJoin.year << endl << "Date Terminated\t\t: ";
		if (searchresult->dTerminate.year == NULL)//showing the info
			cout << "NULL\n";
		else
			cout << searchresult->dTerminate.date << "-" << searchresult->dTerminate.month << "-" <<
			searchresult->dTerminate.year << endl;
		cout << "Hourly Pay Rate\t\t: " << searchresult->hpr << endl << "Phone\t\t\t: " << searchresult->phone <<
			endl << "Address\t\t\t: " << searchresult->address << endl << "Tuition Centre Code\t: " << searchresult->tcCode <<
			endl << "Tuition Centre Name\t: " << searchresult->tcName << endl << "Subject Code\t\t: " << searchresult->sCode <<
			endl << "Subject Name\t\t: " << searchresult->sName << endl << "Rating\t\t\t: ";
		if (searchresult->rating == NULL)
			cout << "No Rating at the moment\n";
		else {
			cout << searchresult->rating << endl;
		}
	}
	else {
		cout << "Tutor ID doesn't exist in the database";
		system("PAUSE");
		system("CLS");
		searchCriteria();
	}
}

bool searchTutor(string id) {//checking if tutor exist
	pointer = head;
	while (pointer != NULL) {
		if (pointer->iD == id) {
			return true;
		}
		else {
			pointer = pointer->next;
		}
	}
	return false;
}

tutor* searchResult(string id) {// getting the tutor info
	pointer = head;
	while (pointer != NULL) {
		if (pointer->iD == id) {
			return pointer;
		}
		else {
			pointer = pointer->next;
		}
	}
}

void searchRating() {
	int Rating;
	int count = 0;
	
	cout << "Insert Rating(1-5, 0 to go back, -1 to Main Menu)\t: ";
	cin >> Rating;
	if (Rating == 0) {
		system("PAUSE");
		system("CLS");
		searchCriteria();
	}
	else if (Rating == -1) {
		system("PAUSE");
		system("CLS");
		mainmenu();
	}
	else if (Rating < 0 || Rating > 5) {
		error();
		searchRating();
	}
	
	else {
		pointer = head;
		while (pointer != NULL) {
			if (pointer->rating == Rating) {
				if (count < 1) {//when searching, immediately print the result
					cout << "\n\nID\t\tName\t\tPhone\t\tSubject\t\tTuition Centre" << endl;
				}
				cout << pointer->iD << "\t" << pointer->name << "\t" << pointer->phone << "\t" << pointer->sName << "\t" << pointer->tcName << endl;
				count++;
			}
			pointer = pointer->next;
		}
		if (count == 0) {
			cout << "\n\nThere is no Tutor with this Rating";
			system("PAUSE");
			system("CLS");
			searchCriteria();
		}
	}
}

void readFile() {//reading file, from lecturer
	vector <string> record;
	ifstream fileToRead("listOfTutor.txt");
	while (fileToRead)
	{
		string s;
		if (!getline(fileToRead, s)) break;

		istringstream ss(s);

		while (ss)
		{
			string s;
			if (!getline(ss, s, ',')) break;
			record.push_back(s);
		}
	}

	fileToRead.close();
	int i = 0, size;
	head = NULL;
	tail = NULL;
	size = record.size();
	while (i < size) {
		if (i % 16 == 0) {
			pointer = head;

			tutor* newtutor = new tutor;

			newtutor->iD = record[i];

			fill_n(newtutor->name, sizeof(newtutor->name), NULL); //a problem with the name already filled with junk
			for (int j = 0; j < record[i + 1].size(); j++) {
				newtutor->name[j] = record[i + 1][j];
			}

			newtutor->dJoin.date = stoi(record[i + 2]);
			newtutor->dJoin.month = stoi(record[i + 3]);
			newtutor->dJoin.year = stoi(record[i + 4]);
			newtutor->dTerminate.date = stoi(record[i + 5]);
			newtutor->dTerminate.month = stoi(record[i + 6]);
			newtutor->dTerminate.year = stoi(record[i + 7]);
			newtutor->hpr = atof(record[i + 8].c_str());
			newtutor->phone = record[i + 9];

			fill_n(newtutor->address, sizeof(newtutor->address), NULL);
			for (int j = 0; j < record[i + 10].size(); j++) {
				newtutor->address[j] = record[i + 10][j];
			}

			newtutor->tcCode = record[i + 11];

			fill_n(newtutor->tcName, sizeof(newtutor->tcName), NULL);
			for (int j = 0; j < record[i + 12].size(); j++) {
				newtutor->tcName[j] = record[i + 12][j];
			}

			newtutor->sCode = record[i + 13];

			fill_n(newtutor->sName, sizeof(newtutor->sName), NULL);
			for (int j = 0; j < record[i + 14].size(); j++) {
				newtutor->sName[j] = record[i + 14][j];
			}

			newtutor->rating = stoi(record[i + 15]);
			newtutor->next = NULL;
			newtutor->prev = NULL;

			if (head == NULL)
			{
				head = newtutor;
				tail = newtutor;
			}
			else
			{
				newtutor->prev = tail;
				tail->next = newtutor;
			}
			tail = newtutor;
		}
		i = i + 16;
	}
}

void saveFile() {//save file from lecturer
	ofstream fileToWrtie("listOfTutor.txt");
	pointer = head;
	while (pointer != NULL)
	{
		fileToWrtie << pointer->iD << "," << pointer->name << "," << pointer->dJoin.date << "," << pointer->dJoin.month << "," 
			<< pointer->dJoin.year << "," << pointer->dTerminate.date << "," << pointer->dTerminate.month << ","
			<< pointer->dTerminate.year << "," << pointer->hpr << "," << pointer->phone << "," << pointer->address << "," 
			<< pointer->tcCode << "," << pointer->tcName << "," << pointer->sCode << "," << pointer->sName << "," 
			<< pointer->rating << endl;
		pointer = pointer->next;
	}

	fileToWrtie.close();
}