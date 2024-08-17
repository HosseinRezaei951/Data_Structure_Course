//Some of Definitions of AVL_Tree:

// Definition of RR rotaition
// ######################################
//   1                        
//	  \        RR			   2
//     2     =======>         / \
//      \                    1   3
//       3  
// #######################################

// Definition of LL rotaition
// ######################################
//        3                        
//	     /      LL			   2
//     2     =======>         / \
//    /                      1   3
//   1  
// #######################################

#include <conio.h>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <sstream>
#include <windows.h>
#include <string.h>
#include <string>
#include <fstream>
using namespace std;

//Globals:
long population = 0;
long reservation_number = 0;
long number_of_reserves = 0;
long number_of_flights = 0;
char* AdminUserName = "hossein951";
char* AdminPass = "5500";

//Global Functions:
bool Is_number(char);
int convert_char_to_int(char*);
struct date give_date();


struct date
{
	char year[5]="";
	char month[3]= "";
	char day[3]= "";
	char hour[3]= "";
	char minute[3]= "";
};

// USER AVL TREE :
// ##############################################################################################################################################
struct User
{
	char name[20];
	char family[20];
	char pass[20];
	char UserName[20];
	char NC[11]; //National Code

	struct User *LeftChild, *RightChild;
};

class UsersTree
{
	friend class Client;
	friend class Admin;
	
private:
	User* root;
	
public:
	//AVL TREE FUNCTIONS:
	UsersTree() { root = NULL; LoadData(); }
	void Delete_Tree(User* root);
	User* MinValueNode(User	*);
	User* Balance(User *); //Balancing UserTree
	int Height(User *); //Height of AVL Tree
	int Diff(User *); //Height Difference
	User *RR_rotation(User *); //Right-Right Rotation
	User *LL_rotation(User *); //Left-Left Rotation
	User *LR_rotation(User *); //Left-Right Rotation
	User *RL_rotation(User *); //Right-Left Rotation

	//METHOUS:
	bool Is_user(char*, char*, User*&); //Searching the Tree to find the user (if the user was in the tree return true else return false)
	void Inorder(User *); // Inorder Traversal of UsersTree(for printing all of the users)
	User* Delete_User(char*, char*, User *);// delete a user
	void Inorder2(User *,ofstream &);
	void LoadData();
	User* Insert(char*, char*, User *); //Insert Element into the tree(sign up)
	User* Insert2(char*, char*, char*, char*, char*, User *);//Insert Element into the tree(for loading Users_file)
	void SaveData();
}_UsersTree;

User* UsersTree::MinValueNode(User* node)
{
	User* current = node;
	while (current->LeftChild != NULL)
		current = current->LeftChild;
	return current;
}

void UsersTree::Delete_Tree(User* root)
{
	if (root != NULL)
	{
		Delete_Tree(root->LeftChild);
		Delete_Tree(root->RightChild);
		root = NULL;
		delete root;
	}
}

User* UsersTree::Delete_User(char* UserName, char* pass, User* root)
{
	if (root == NULL) // if empty tree 
		return NULL;  
	if (strcmp(UserName, root->UserName) == -1)
		root->LeftChild = Delete_User(UserName, pass, root->LeftChild);

	else if (strcmp(UserName, root->UserName) == 1)
		root->RightChild = Delete_User(UserName, pass, root->RightChild);
	
	// if key is same as root's key, then This is the node to be deleted
	else if (strcmp(UserName, root->UserName) == 0 && strcmp(pass, root->pass) == 0 )
	{
		// node with only one child or no child
		if ((root->LeftChild == NULL) || (root->RightChild == NULL))
		{
			User* temp = root->LeftChild ? root->LeftChild : root->RightChild;

			// No child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			// One child case
			else // Copy the contents of the non-empty child
			{
				strcpy_s(root->name, temp->name);
				strcpy_s(root->family, temp->family);
				strcpy_s(root->UserName, temp->UserName);
				strcpy_s(root->pass, temp->pass);
				strcpy_s(root->NC, temp->NC);
				root->LeftChild = temp->LeftChild;
				root->RightChild = temp->RightChild;
			}
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder successor (smallest in the right subtree)
			User* temp = MinValueNode(root->RightChild);

			// Copy the inorder successor's data to this node
			strcpy_s(root->name, temp->name);
			strcpy_s(root->family, temp->family);
			strcpy_s(root->UserName, temp->UserName);
			strcpy_s(root->pass, temp->pass);
			strcpy_s(root->NC, temp->NC);

			// Delete the inorder successor
			root->RightChild = Delete_User(temp->UserName, temp->pass, root->RightChild);
		}
	}

	// If the tree had only one node then return
	if (root == NULL)
		return NULL;
	root = Balance(root);
	return root;
}


bool UsersTree::Is_user(char* UserName, char* pass,User* &root)
{
	if (root == NULL)
		return false;
	if (strcmp(UserName, root->UserName) == -1)
		return Is_user(UserName, pass, root->LeftChild);

	else if (strcmp(UserName, root->UserName) == 1)
		return Is_user(UserName, pass, root->RightChild);
	else if (strcmp(UserName, root->UserName) == 0 && strcmp(pass, root->pass) == 0)
		return true;
}

void UsersTree::Inorder(User* root)
{
	if (root == NULL)
		return;
	Inorder(root->LeftChild);
	cout << endl;
	cout << "\n\tname: \t" << root->name;
	cout << "\n\tfamily: \t" << root->family;
	cout << "\n\tUserName: \t" << root->UserName;
	cout << "\n\tNational Code: \t" << root->NC << endl;
	Inorder(root->RightChild);
}

void UsersTree::Inorder2(User* root, ofstream &Users_file)
{
	if (root == NULL)
		return;
	Inorder2(root->LeftChild, Users_file);
	Users_file << root->name << " ";
	Users_file << root->family << " ";
	Users_file << root->pass << " ";
	Users_file << root->UserName << " ";
	Users_file << root->NC << endl;
	Inorder2(root->RightChild, Users_file);
}

void UsersTree::SaveData()
{
	ofstream Users_file;
	Users_file.open("files\\Users.txt");
	Users_file << population << endl;
	Inorder2(_UsersTree.root, Users_file);
}

void UsersTree::LoadData()
{
	ifstream Users_file;
	Users_file.open("files\\Users.txt");
	if (!Users_file) {
		cout << "Error in reading";
		_getch();
		exit(0);
	}
	int tmp_PP;				/* tmp_PP is temp population */
	Users_file >> tmp_PP;
	User temp;

	if (tmp_PP > 0)
	{
		for (int i = 0; i < tmp_PP; i++)
		{
			Users_file >> temp.name;
			Users_file >> temp.family;
			Users_file >> temp.pass;
			Users_file >> temp.UserName;
			Users_file >> temp.NC;
			root = Insert2(temp.name, temp.family, temp.pass, temp.UserName, temp.NC, root);
	}
		}
	
	population = population + tmp_PP;
	Users_file.close();
}

//Height of AVL Tree:
int UsersTree::Height(User *temp)
{
	int h = 0;
	if (temp != NULL)
	{
		int L_height = Height(temp->LeftChild);
		int R_height = Height(temp->RightChild);
		int max_height = max(L_height, R_height);
		h = max_height + 1;
	}
	return h;
}

//Height Difference:
int UsersTree::Diff(User *temp)
{
	int L_height = Height(temp->LeftChild);
	int R_height = Height(temp->RightChild);
	int B_factor = L_height - R_height;
	return B_factor;
}

//Right-Right Rotation:
User* UsersTree::RR_rotation(User* parent)
{
	User *temp;
	temp = parent->RightChild;
	parent->RightChild = temp->LeftChild;
	temp->LeftChild = parent;
	return temp;
}

//Left-Left Rotation:
User* UsersTree::LL_rotation(User* parent)
{
	User *temp;
	temp = parent->LeftChild;
	parent->LeftChild = temp->RightChild;
	temp->RightChild = parent;
	return temp;
}

//Left-Right Rotation:
User* UsersTree::LR_rotation(User* parent)
{
	User *temp;
	temp = parent->LeftChild;
	parent->LeftChild = RR_rotation(temp);
	return LL_rotation(parent);
}

//Right-Left Rotation:
User* UsersTree::RL_rotation(User* parent)
{
	User* temp;
	temp = parent->RightChild;
	parent->RightChild = LL_rotation(temp);
	return RR_rotation(parent);
}


//Balancing UserTree:
User* UsersTree::Balance(User *temp)
{
	int bal_factor = Diff(temp);
	if (bal_factor > 1)
	{
		if (Diff(temp->LeftChild) > 0)
			temp = LL_rotation(temp);
		else
			temp = LR_rotation(temp);
	}
	else if (bal_factor < -1)
	{
		if (Diff(temp->RightChild) > 0)
			temp = RL_rotation(temp);
		else
			temp = RR_rotation(temp);
	}
	return temp;
}

//Insert Element into the tree(for loading Users_file)
User* UsersTree::Insert2(char* name, char* family, char* pass, char* UserName, char* NC, User* root)
{

	if (root == NULL)
	{
		root = new User;

		strcpy_s(root->family, family);
		strcpy_s(root->name, name);
		strcpy_s(root->NC, NC);
		strcpy_s(root->UserName, UserName);
		strcpy_s(root->pass, pass);

		root->RightChild = NULL;
		root->LeftChild = NULL;
		return root;
	}
	else
	{
		int value = strcmp(UserName, root->UserName);
		if (value == -1)
		{
			root->LeftChild = Insert2(name, family, pass, UserName, NC, root->LeftChild);
			root = Balance(root);
		}

		else 
		{
			root->RightChild = Insert2(name, family, pass, UserName, NC, root->RightChild);
			root = Balance(root);
		}
	}
	return root;
}

//Insert Element into the tree(sign up)
User* UsersTree::Insert(char* family,char* name, User* root)
{
	char pass[20];
	char UserName[20];
	char NC[10]; //National Code

	if (root == NULL)
	{
		root = new User;
		strcpy_s(root->family, family);
		strcpy_s(root->name, name);

		// another things
		cout << "/n ==> plz enter your National Code: ";
		cin >> NC;
		cout << "/n ==> plz enter your UserName: ";
		cin >> UserName;
		cout << "/n ==> plz enter your Password: ";
		cin >> pass;
		strcpy_s(root->NC, NC);
		strcpy_s(root->UserName, UserName);
		strcpy_s(root->pass, pass);

		root->RightChild = NULL;
		root->LeftChild = NULL;
		return root;
	}
	else
	{
		int value = strcmp(UserName, root->UserName);
		if (value == -1)
		{
			root->LeftChild = Insert(family,name,root->LeftChild);
			root = Balance(root);
		}

		else 
		{
			root->RightChild = Insert(family, name, root->RightChild);
			root = Balance(root);
		}
	}
	return root;
}

// ##############################################################################################################################################

// ##############################################################################################################################################
struct node1
{
	char UserName[20];
	char family[20];
	node1 *next;
};

class LinkedList1 //LinkedList to store usernames in our system
{

private:
	node1 *head, *tail;
public:
	LinkedList1()
	{
		head = NULL;
		tail = NULL;
	}
	void createnode(char UserName[20], char family[20])
	{
		node1 *temp = new node1;
		strcpy_s(temp->UserName, UserName);
		strcpy_s(temp->family, family);
		temp->next = NULL;
		if (head == NULL)
		{
			head = temp;
			tail = temp;
			temp = NULL;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
	}
	char* search(char UserName[20])
	{
		node1 *temp = head;
		while (temp != NULL)
		{
			if (strcmp(temp->UserName, UserName) == 0)
			{
				return temp->family;
			}
			temp = temp->next;
		}
		return "there_is_not_!";

	}

};
// ##############################################################################################################################################

//FLIGHTS AVL TREE :
// ##############################################################################################################################################
struct Flight
{
	char FlightNumber[20];
	char AirLine[20];
	long Capacity;
	char Destination[20];
	struct date FlightDate;

	struct Flight *LeftChild, *RightChild;
};

class FlightsTree
{
	friend class Admin;
	friend class Client;
private:
	Flight* root;
	LinkedList1* WaitingList;
	
public:
	FlightsTree() { root = NULL; LoadData(); }
	Flight* MinValueNode(Flight *);
	void Find_all_flights_to(char*, Flight*, bool&); // Searching the avl tree to find all flights to same destination
	Flight* Delete_flight(char*, char*, char*, char*, char*, char*, char*, Flight *); // delete a flight
	bool Is_the_same_flight(char*, char*,long, char*, char*, char*, char*, char*, char*, Flight *&);
	void Inorder(Flight *); // Inorder Traversal of UsersTree(for printing all of the users)
	void Inorder2(Flight *, ofstream &);
	void LoadData();
	void SaveData();
	Flight* Balance(Flight *); //Balancing UserTree
	Flight* Insert2(char*, char*, long, char*, char*, char*, char*, char*, char*, Flight *);//Insert Element into the tree(for loading Flights_file)
	int Height(Flight *); //Height of AVL Tree
	int Diff(Flight *); //Height Difference
	Flight *RR_rotation(Flight *); //Right-Right Rotation
	Flight *LL_rotation(Flight *); //Left-Left Rotation
	Flight *LR_rotation(Flight *); //Left-Right Rotation
	Flight *RL_rotation(Flight *); //Right-Left Rotation
	void Delete_Tree(Flight *);
}_FlightsTree;

bool FlightsTree::Is_the_same_flight(char* FlightNumber, char* AirLine, long Capacity, char* Destination,
								char* year, char* month, char* day, char* hour, char* minute, Flight* &root)
{
	if (root == NULL)
		return false;
	if (strcmp(Destination, root->Destination) == -1)
		return Is_the_same_flight(FlightNumber, AirLine, Capacity, Destination,
			year, month, day, hour, minute, root->LeftChild);

	else if (strcmp(Destination, root->Destination) == 1)
		return Is_the_same_flight(FlightNumber, AirLine, Capacity, Destination,
			year, month, day, hour, minute, root->RightChild);

	else if ((strcmp(Destination, root->Destination) == 0 &&
		strcmp(AirLine, root->AirLine) == 0 &&
		Capacity == root->Capacity && root->Capacity != 0 &&
		strcmp(FlightNumber, root->FlightNumber) == 0 &&
		strcmp(year, root->FlightDate.year) == 0 &&
		strcmp(month, root->FlightDate.month) == 0 &&
		strcmp(day, root->FlightDate.day) == 0 &&
		strcmp(hour, root->FlightDate.hour) == 0 &&
		strcmp(minute, root->FlightDate.minute) == 0))
	{
		root->Capacity--;
		return true;
	}
		
}

Flight* FlightsTree::MinValueNode(Flight* node)
{
	Flight* current = node;
	while (current->LeftChild != NULL)
		current = current->LeftChild;
	return current;
}

void FlightsTree::Delete_Tree(Flight* root)
{
	if (root != NULL)
	{
		Delete_Tree(root->LeftChild);
		Delete_Tree(root->RightChild);
		delete root;
	}
}

Flight* FlightsTree::Delete_flight(char* FlightNumber, char* Destination,
									char* year, char* month, char* day, char* hour, char* minute,Flight* root)
{
	if (root == NULL) // if empty tree
		return NULL;   
	if (strcmp(Destination, root->Destination) == -1)
		root->LeftChild = Delete_flight(FlightNumber, Destination, year, month, day, hour, minute, root->LeftChild);
	else if(strcmp(Destination, root->Destination) == 1)
		root->RightChild = Delete_flight(FlightNumber, Destination, year, month, day, hour, minute, root->RightChild);
	
	// if key is same as root's key, then This is the node to be deleted
	else if (strcmp(Destination, root->Destination) == 0 &&
		strcmp(FlightNumber, root->FlightNumber) == 0 &&
		strcmp(year, root->FlightDate.year) == 0 &&
		strcmp(month, root->FlightDate.month) == 0 &&
		strcmp(hour, root->FlightDate.hour) == 0 &&
		strcmp(minute, root->FlightDate.minute) == 0)
	{
		// node with only one child or no child
		if ((root->LeftChild == NULL) || (root->RightChild == NULL))
		{
			Flight* temp = root->LeftChild ? root->LeftChild : root->RightChild;

			// No child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			// One child case
			else // Copy the contents of the non-empty child
			{
				strcpy_s(root->AirLine, temp->AirLine);
				root->Capacity=temp->Capacity;
				strcpy_s(root->Destination, temp->Destination);
				strcpy_s(root->FlightNumber, temp->FlightNumber);
				strcpy_s(root->FlightDate.year, temp->FlightDate.year);
				strcpy_s(root->FlightDate.month, temp->FlightDate.month);
				strcpy_s(root->FlightDate.day, temp->FlightDate.day);
				strcpy_s(root->FlightDate.hour, temp->FlightDate.hour);
				strcpy_s(root->FlightDate.minute, temp->FlightDate.minute);
				root->LeftChild = temp->LeftChild;
				root->RightChild = temp->RightChild;
			}
			free(temp);
		}
		else  
		{
			// node with two children: Get the inorder successor (smallest in the right subtree)
			Flight* temp = MinValueNode(root->RightChild);

			// Copy the inorder successor's data to this node
			strcpy_s(root->AirLine, temp->AirLine);
			root->Capacity = temp->Capacity;
			strcpy_s(root->Destination, temp->Destination);
			strcpy_s(root->FlightNumber, temp->FlightNumber);
			strcpy_s(root->FlightDate.year, temp->FlightDate.year);
			strcpy_s(root->FlightDate.month, temp->FlightDate.month);
			strcpy_s(root->FlightDate.day, temp->FlightDate.day);
			strcpy_s(root->FlightDate.hour, temp->FlightDate.hour);
			strcpy_s(root->FlightDate.minute, temp->FlightDate.minute);

			// Delete the inorder successor
			root->RightChild= Delete_flight(temp->FlightNumber, temp->Destination,
				temp->FlightDate.year, temp->FlightDate.month, temp->FlightDate.day, temp->FlightDate.hour, temp->FlightDate.minute, root->RightChild);
		}
	}

	// If the tree had only one node then return
	if (root == NULL)
		return NULL;
	root = Balance(root);
	return root;		
}


void FlightsTree::Find_all_flights_to(char* Destination,Flight* root,bool &result)
{
	if (root == NULL)
		return;
	Find_all_flights_to(Destination,root->LeftChild,result);
	if (strcmp(Destination,root->Destination)==0)
	{
		cout << endl;
		cout << "\n\tFlightNumber: \t" << root->FlightNumber;
		cout << "\n\tAirLine: \t" << root->AirLine;
		cout << "\n\tCapacity: \t" << root->Capacity;
		cout << "\n\tDestination: \t" << root->Destination;
		cout << "\n\tDate: \t" << root->FlightDate.year << "/" << root->FlightDate.month << "/" << root->FlightDate.day;
		cout << "\n\tTime: \t" << root->FlightDate.hour << ":" << root->FlightDate.minute << endl;
		if (result != true)
			result = true;
	}
	Find_all_flights_to(Destination, root->RightChild, result);
}

void FlightsTree::Inorder2(Flight* root, ofstream &Flights_file)
{
	if (root == NULL)
		return;
	Inorder2(root->LeftChild, Flights_file);
	Flights_file << root->FlightNumber << " ";
	Flights_file << root->AirLine << " ";
	Flights_file << root->Capacity << " ";
	Flights_file << root->Destination << " ";
	Flights_file << root->FlightDate.year << " ";
	Flights_file << root->FlightDate.month << " ";
	Flights_file << root->FlightDate.day << " ";
	Flights_file << root->FlightDate.hour << " ";
	Flights_file << root->FlightDate.minute << endl;
	Inorder2(root->RightChild, Flights_file);
}

void FlightsTree::Inorder(Flight* root)
{
	if (root == NULL)
		return;
	Inorder(root->LeftChild);
	cout << endl;
	cout << "\n\tFlightNumber: \t" << root->FlightNumber;
	cout << "\n\tAirLine: \t" << root->AirLine;
	cout << "\n\tCapacity: \t" << root->Capacity;
	cout << "\n\tDestination: \t" << root->Destination;
	cout << "\n\tDate: \t" << root->FlightDate.year << "/" << root->FlightDate.month << "/" << root->FlightDate.day;
	cout << "\n\tTime: \t" << root->FlightDate.hour << ":" << root->FlightDate.minute << endl;
	Inorder(root->RightChild);
}

void FlightsTree::SaveData()
{
	ofstream Flights_file;
	Flights_file.open("files\\Flights.txt");
	Flights_file << number_of_flights << endl;
	if (number_of_flights == 0)
	{
		Flights_file.close();
		return;
	}
	Inorder2(_FlightsTree.root, Flights_file);
	Flights_file.close();
}


void FlightsTree::LoadData()
{

	ifstream Flights_file;
	Flights_file.open("files\\Flights.txt");
	if (!Flights_file) {
		cout << "Error in reading";
		_getch();
		exit(0);
	}
	long tmp_PP;				/* tmp_PP is temp flights_number */
	Flights_file >> tmp_PP;
	Flight temp;

	if (tmp_PP > 0)
	{
		for (int i = 0; i < tmp_PP; i++)
		{
			Flights_file >> temp.FlightNumber;
			Flights_file >> temp.AirLine;
			Flights_file >> temp.Capacity;
			Flights_file >> temp.Destination;
			Flights_file >> temp.FlightDate.year;
			Flights_file >> temp.FlightDate.month;
			Flights_file >> temp.FlightDate.day;
			Flights_file >> temp.FlightDate.hour;
			Flights_file >> temp.FlightDate.minute;
			root = Insert2(temp.FlightNumber, temp.AirLine, temp.Capacity, temp.Destination,
				temp.FlightDate.year, temp.FlightDate.month, temp.FlightDate.day, temp.FlightDate.hour, temp.FlightDate.minute, root);
		}
	}
	number_of_flights = number_of_flights + tmp_PP;
	Flights_file.close();
}

//Height of AVL Tree:
int FlightsTree::Height(Flight *temp)
{
	int h = 0;
	if (temp != NULL)
	{
		int L_height = Height(temp->LeftChild);
		int R_height = Height(temp->RightChild);
		int max_height = max(L_height, R_height);
		h = max_height + 1;
	}
	return h;
}

//Height Difference:
int FlightsTree::Diff(Flight *temp)
{
	int L_height = Height(temp->LeftChild);
	int R_height = Height(temp->RightChild);
	int B_factor = L_height - R_height;
	return B_factor;
}

//Right-Right Rotation:
Flight* FlightsTree::RR_rotation(Flight* parent)
{
	Flight *temp;
	temp = parent->RightChild;
	parent->RightChild = temp->LeftChild;
	temp->LeftChild = parent;
	return temp;
}

//Left-Left Rotation:
Flight* FlightsTree::LL_rotation(Flight* parent)
{
	Flight *temp;
	temp = parent->LeftChild;
	parent->LeftChild = temp->RightChild;
	temp->RightChild = parent;
	return temp;
}

//Left-Right Rotation:
Flight* FlightsTree::LR_rotation(Flight* parent)
{
	Flight *temp;
	temp = parent->LeftChild;
	parent->LeftChild = RR_rotation(temp);
	return LL_rotation(parent);
}

//Right-Left Rotation:
Flight* FlightsTree::RL_rotation(Flight* parent)
{
	Flight* temp;
	temp = parent->RightChild;
	parent->RightChild = LL_rotation(temp);
	return RR_rotation(parent);
}


//Balancing UserTree:
Flight* FlightsTree::Balance(Flight *temp)
{
	int bal_factor = Diff(temp);
	if (bal_factor > 1)
	{
		if (Diff(temp->LeftChild) > 0)
			temp = LL_rotation(temp);
		else
			temp = LR_rotation(temp);
	}
	else if (bal_factor < -1)
	{
		if (Diff(temp->RightChild) > 0)
			temp = RL_rotation(temp);
		else
			temp = RR_rotation(temp);
	}
	return temp;
}

//Insert Element into the tree(for loading Users_file)
Flight* FlightsTree::Insert2(char* FlightNumber, char* AirLine, long Capacity, char* Destination,
							 char* year, char* month, char* day, char* hour, char* minute, Flight* root)
{

	if (root == NULL)
	{
		root = new Flight;

		strcpy_s(root->FlightNumber, FlightNumber);
		strcpy_s(root->AirLine, AirLine);
		root->Capacity = Capacity;
		strcpy_s(root->Destination, Destination);
		strcpy_s(root->FlightDate.year, year);
		strcpy_s(root->FlightDate.month, month);
		strcpy_s(root->FlightDate.day, day);
		strcpy_s(root->FlightDate.hour, hour);
		strcpy_s(root->FlightDate.minute, minute);

		root->RightChild = NULL;
		root->LeftChild = NULL;
		
		return root;
	}
	
	else if (strcmp(Destination, root->Destination) == -1)
		root->LeftChild = Insert2(FlightNumber, AirLine, Capacity, Destination, year, month, day, hour, minute, root->LeftChild);
	
	else 
		root->RightChild = Insert2(FlightNumber, AirLine, Capacity, Destination, year, month, day, hour, minute, root->RightChild);

	root = Balance(root);
	return root;
}

// ##############################################################################################################################################

//RESERVATION AVL TREE :
// ##############################################################################################################################################
struct Reservation
{
	long FlightNumber;
	char UserName[20];
	char FullName[40];
	long Res_Code;
	struct date Res_Date;

	struct Reservation *LeftChild, *RightChild;
	
};

class ReservesTree
{
	friend class Client;
	friend class Admin;
private:
	Reservation* root;
	
public:
	ReservesTree() { root = NULL; LoadData(); }
	void LoadData();
	void SaveData();
	void Inorder(Reservation *); // Inorder Traversal of UsersTree(for printing all of the users)
	void Inorder2(Reservation *, ofstream &);
	void Find_all_reserves_for(char*,long,Reservation *,bool &);
	void Show_all_reserves_for(long, Reservation*,bool &);
	void Show_user_reserves(char*, Reservation *, bool &);
	Reservation* Balance(Reservation *); //Balancing UserTree
	Reservation* Insert2(long FlightNumber, char* UserName, char* FullName, long Res_Code,
		char* year, char* month, char* day, char* hour, char* minute, Reservation* root);//Insert Element into the tree(for loading Users_file)
	Reservation* Delete_Reserve(long, long, Reservation*);
	Reservation* MinValueNode(Reservation*);
	bool Is_reserve(long, long, Reservation*);
	int Height(Reservation *); //Height of AVL Tree
	int Diff(Reservation *); //Height Difference
	Reservation *RR_rotation(Reservation *); //Right-Right Rotation
	Reservation *LL_rotation(Reservation *); //Left-Left Rotation
	Reservation *LR_rotation(Reservation *); //Left-Right Rotation
	Reservation *RL_rotation(Reservation *); //Right-Left Rotation

}_ReservesTree;

void ReservesTree::Show_all_reserves_for(long FlightNumber, Reservation* root, bool &result)
{
	if (root == NULL)
		return;
	Show_all_reserves_for(FlightNumber,root->LeftChild,result);
	if (FlightNumber == root->FlightNumber)
	{
		cout << endl;
		cout << "\n\tFlightNumber: \t" << root->FlightNumber;
		cout << "\n\tUserName: \t" << root->UserName;
		cout << "\n\tFullName: \t" << root->FullName;
		cout << "\n\tReservation Code: \t" << root->Res_Code;
		cout << "\n\tDate: \t" << root->Res_Date.year << "/" << root->Res_Date.month << "/" << root->Res_Date.day;
		cout << "\n\tTime: \t" << root->Res_Date.hour << ":" << root->Res_Date.minute << endl;
		if (result != true)
			result = true;
	}
	Show_all_reserves_for(FlightNumber, root->RightChild, result);
}

bool ReservesTree::Is_reserve(long FlightNumber, long Res_Code, Reservation* root)
{
	if (root == NULL)
		return false;
	if (Res_Code<root->Res_Code)
		return Is_reserve(FlightNumber, Res_Code, root->LeftChild);

	else if (Res_Code>root->Res_Code)
		return Is_reserve(FlightNumber, Res_Code, root->RightChild);
	else if (Res_Code == root->Res_Code && FlightNumber == root->FlightNumber)
		return true;

}

Reservation* ReservesTree::MinValueNode(Reservation* node)
{
	Reservation* current = node;
	while (current->LeftChild != NULL)
		current = current->LeftChild;
	return current;
}

Reservation* ReservesTree::Delete_Reserve(long FlightNumber, long Res_Code, Reservation* root)
{
	if (root == NULL) // if empty tree 
		return NULL;
	if (Res_Code < root->Res_Code)
		root->LeftChild = Delete_Reserve(FlightNumber, Res_Code, root->LeftChild);

	else if (Res_Code>root->Res_Code)
		root->RightChild = Delete_Reserve(FlightNumber, Res_Code, root->RightChild);

	// if key is same as root's key, then This is the node to be deleted
	else if (Res_Code == root->Res_Code && FlightNumber == root->FlightNumber)
	{
		// node with only one child or no child
		if ((root->LeftChild == NULL) || (root->RightChild == NULL))
		{
			Reservation* temp = root->LeftChild ? root->LeftChild : root->RightChild;

			// No child case
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			// One child case
			else // Copy the contents of the non-empty child
			{
				root->FlightNumber = temp->FlightNumber;
				strcpy_s(root->UserName, temp->UserName);
				strcpy_s(root->FullName, temp->FullName);
				root->Res_Code = temp->Res_Code;
				strcpy_s(root->Res_Date.year, temp->Res_Date.year);
				strcpy_s(root->Res_Date.month, temp->Res_Date.month);
				strcpy_s(root->Res_Date.day, temp->Res_Date.day);
				strcpy_s(root->Res_Date.hour, temp->Res_Date.hour);
				strcpy_s(root->Res_Date.minute, temp->Res_Date.minute);
				root->LeftChild = temp->LeftChild;
				root->RightChild = temp->RightChild;
			}
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder successor (smallest in the right subtree)
			Reservation* temp = MinValueNode(root->RightChild);

			// Copy the inorder successor's data to this node
			root->FlightNumber = temp->FlightNumber;
			strcpy_s(root->UserName, temp->UserName);
			strcpy_s(root->FullName, temp->FullName);
			root->Res_Code = temp->Res_Code;
			strcpy_s(root->Res_Date.year, temp->Res_Date.year);
			strcpy_s(root->Res_Date.month, temp->Res_Date.month);
			strcpy_s(root->Res_Date.day, temp->Res_Date.day);
			strcpy_s(root->Res_Date.hour, temp->Res_Date.hour);
			strcpy_s(root->Res_Date.minute, temp->Res_Date.minute);

			// Delete the inorder successor
			root->RightChild = Delete_Reserve(temp->FlightNumber, temp->Res_Code, root->RightChild);
		}
	}

	// If the tree had only one node then return
	if (root == NULL)
		return NULL;
	root = Balance(root);
	return root;
}

void ReservesTree::Show_user_reserves(char *UserName, Reservation* root, bool &result)
{
	if (root == NULL)
		return;
	Show_user_reserves(UserName, root->LeftChild, result);
	if (strcmp(UserName, root->UserName) == 0 )
	{
		cout << endl;
		cout << "\n\tFlightNumber: \t" << root->FlightNumber;
		cout << "\n\tUserName: \t" << root->UserName;
		cout << "\n\tFullName: \t" << root->FullName;
		cout << "\n\tReservation Code: \t" << root->Res_Code;
		cout << "\n\tDate: \t" << root->Res_Date.year << "/" << root->Res_Date.month << "/" << root->Res_Date.day;
		cout << "\n\tTime: \t" << root->Res_Date.hour << ":" << root->Res_Date.minute << endl;
		if (result != true)
			result = true;
	}
	Show_user_reserves(UserName, root->RightChild, result);
}

void ReservesTree::Find_all_reserves_for(char *UserName, long Res_code, Reservation* root, bool &result)
{
	if (root == NULL)
		return;
	Find_all_reserves_for(UserName, Res_code, root->LeftChild, result);
	if (strcmp(UserName, root->UserName) == 0 && Res_code==root->Res_Code )
	{
		cout << endl;
		cout << "\n\tFlightNumber: \t" << root->FlightNumber;
		cout << "\n\tUserName: \t" << root->UserName;
		cout << "\n\tFullName: \t" << root->FullName;
		cout << "\n\tReservation Code: \t" << root->Res_Code;
		cout << "\n\tDate: \t" << root->Res_Date.year << "/" << root->Res_Date.month << "/" << root->Res_Date.day;
		cout << "\n\tTime: \t" << root->Res_Date.hour << ":" << root->Res_Date.minute << endl;
		if (result != true)
			result = true;
	}
	Find_all_reserves_for(UserName, Res_code, root->RightChild, result);
}


void ReservesTree::Inorder2(Reservation* root, ofstream &Reserves_file)
{
	if (root == NULL)
		return;
	Inorder2(root->LeftChild, Reserves_file);
	Reserves_file << root->FlightNumber << " ";
	Reserves_file << root->UserName << " ";
	Reserves_file << root->FullName << " ";
	Reserves_file << root->Res_Code << " ";
	Reserves_file << root->Res_Date.year << " ";
	Reserves_file << root->Res_Date.month << " ";
	Reserves_file << root->Res_Date.day << " ";
	Reserves_file << root->Res_Date.hour << " ";
	Reserves_file << root->Res_Date.minute << endl;
	Inorder2(root->RightChild, Reserves_file);
}

void ReservesTree::Inorder(Reservation* root)

{
	if (root == NULL)
		return;
	Inorder(root->LeftChild);
	cout << endl;
	cout << "\n\tFlightNumber: \t" << root->FlightNumber;
	cout << "\n\tUserName: \t" << root->UserName;
	cout << "\n\tFullName: \t" << root->FullName;
	cout << "\n\tReservation Code: \t" << root->Res_Code;
	cout << "\n\tDate: \t" << root->Res_Date.year << "/" << root->Res_Date.month << "/" << root->Res_Date.day;
	cout << "\n\tTime: \t" << root->Res_Date.hour<<":"<<root->Res_Date.minute<<endl;
	Inorder(root->RightChild);
}

void ReservesTree::SaveData()
{
	ofstream Reserves_file;
	Reserves_file.open("files\\Reserves.txt");
	Reserves_file << number_of_reserves << endl;
	Inorder2(_ReservesTree.root, Reserves_file);
}

void ReservesTree::LoadData()
{

	ifstream Reserves_file;
	Reserves_file.open("files\\Reserves.txt");
	if (!Reserves_file) {
		cout << "Error in reading";
		_getch();
		exit(0);
	}
	int tmp_PP;				/* tmp_PP is temp number of reservations */
	Reserves_file >> tmp_PP;
	Reservation temp;

	if (tmp_PP > 0)
	{
		for (int i = 0; i < tmp_PP; i++)
		{
			Reserves_file >> temp.FlightNumber;
			Reserves_file >> temp.UserName;
			Reserves_file >> temp.FullName;
			Reserves_file >> temp.Res_Code;
			Reserves_file >> temp.Res_Date.year;
			Reserves_file >> temp.Res_Date.month;
			Reserves_file >> temp.Res_Date.day;
			Reserves_file >> temp.Res_Date.hour;
			Reserves_file >> temp.Res_Date.minute;
			root = Insert2(temp.FlightNumber, temp.UserName, temp.FullName, temp.Res_Code,
						   temp.Res_Date.year, temp.Res_Date.month, temp.Res_Date.day, temp.Res_Date.hour, temp.Res_Date.minute, root);
		}
	}
	number_of_reserves = number_of_reserves + tmp_PP;
	reservation_number = temp.Res_Code;
	Reserves_file.close();
}

//Height of AVL Tree:
int ReservesTree::Height(Reservation *temp)
{
	int h = 0;
	if (temp != NULL)
	{
		int L_height = Height(temp->LeftChild);
		int R_height = Height(temp->RightChild);
		int max_height = max(L_height, R_height);
		h = max_height + 1;
	}
	return h;
}

//Height Difference:
int ReservesTree::Diff(Reservation *temp)
{
	int L_height = Height(temp->LeftChild);
	int R_height = Height(temp->RightChild);
	int B_factor = L_height - R_height;
	return B_factor;
}

//Right-Right Rotation:
Reservation* ReservesTree::RR_rotation(Reservation* parent)
{
	Reservation *temp;
	temp = parent->RightChild;
	parent->RightChild = temp->LeftChild;
	temp->LeftChild = parent;
	return temp;
}

//Left-Left Rotation:
Reservation* ReservesTree::LL_rotation(Reservation* parent)
{
	Reservation *temp;
	temp = parent->LeftChild;
	parent->LeftChild = temp->RightChild;
	temp->RightChild = parent;
	return temp;
}

//Left-Right Rotation:
Reservation* ReservesTree::LR_rotation(Reservation* parent)
{
	Reservation *temp;
	temp = parent->LeftChild;
	parent->LeftChild = RR_rotation(temp);
	return LL_rotation(parent);
}

//Right-Left Rotation:
Reservation* ReservesTree::RL_rotation(Reservation* parent)
{
	Reservation* temp;
	temp = parent->RightChild;
	parent->RightChild = LL_rotation(temp);
	return RR_rotation(parent);
}


//Balancing UserTree:
Reservation* ReservesTree::Balance(Reservation* temp)
{
	int bal_factor = Diff(temp);
	if (bal_factor > 1)
	{
		if (Diff(temp->LeftChild) > 0)
			temp = LL_rotation(temp);
		else
			temp = LR_rotation(temp);
	}
	else if (bal_factor < -1)
	{
		if (Diff(temp->RightChild) > 0)
			temp = RL_rotation(temp);
		else
			temp = RR_rotation(temp);
	}
	return temp;
}

//Insert Element into the tree(for loading Users_file)
Reservation* ReservesTree::Insert2(long FlightNumber, char* UserName, char* FullName, long Res_Code,
								   char* year,char* month,char* day,char* hour,char* minute, Reservation* root)
{
	if (root == NULL)
	{
		root = new Reservation;

		root->FlightNumber = FlightNumber;
		strcpy_s(root->UserName, UserName);
		strcpy_s(root->FullName, FullName);
		root->Res_Code = Res_Code;
		strcpy_s(root->Res_Date.year, year);
		strcpy_s(root->Res_Date.month, month);
		strcpy_s(root->Res_Date.day, day);
		strcpy_s(root->Res_Date.hour, hour);
		strcpy_s(root->Res_Date.minute, minute);

		root->RightChild = NULL;
		root->LeftChild = NULL;
		return root;
	}
	else if(Res_Code<root->Res_Code)
		root->LeftChild = Insert2(FlightNumber, UserName, FullName, Res_Code, year, month, day, hour, minute, root->LeftChild);

	else 
		root->RightChild = Insert2(FlightNumber, UserName, FullName, Res_Code, year, month, day, hour, minute, root->RightChild);

	root = Balance(root);
	return root;
}

// ##############################################################################################################################################


// ##############################################################################################################################################

class Client
{
	friend class Admin;

public:
	void Sign_UP(char*, char*, char*, char*, char*);
	int Client_panel();
	void Unsubscribe();
	bool Show_your_reservations();
	bool Reserve_flight();
	bool Cancel_reservation();
	void Save_datas();

	bool Is_user(char*, char*);
};

bool Client::Show_your_reservations()
{
	char UserName[20];
	bool result = false;
	system("cls");
	cout << "\n ############################################################################# \n" << endl;
	cout << "\tShow your reservations: ";
	cout << "\n\tPlz enter your UserName: ";
	cin >> UserName;
	_ReservesTree.Show_user_reserves(UserName, _ReservesTree.root, result);
	if (result == true)
		return true;
	return false;
}

bool Client::Cancel_reservation()
{
	Reservation temp;
	bool Check_FlightNum = false;
	bool Check_Res_Code = false;
	char tmp_res[20];
	char tmp_flightnum[20];
	cout << "\n ############################################################################# \n" << endl;
	cout << "\tCancel reservation: ";
	cout << "\n\t ***** Plz enter reserve Informations ***** ";
	
	cout << "\n\tReservation Code: ";
	cin >> tmp_res;
	while(!Check_Res_Code)
	{
		if (strlen(tmp_res) != 5)
		{
			cout << "\n\t ***** Wrong ... Your Reservation Code must be five digit number Plz enter again  ***** ";
			cout << "\n\tReservation Code: ";
			cin >> tmp_res;
		}
		else
		{
			for (int i = 0; i < strlen(tmp_res); i++)
			{
				if (!Is_number(tmp_res[i]))
				{
					cout << "\n\t ***** Wrong ... Your Reservation Code must be five digit number Plz enter again  ***** ";
					cout << "\n\tReservation Code: ";
					cin >> tmp_res;
					break;
				}
			}
			Check_Res_Code = true;
			temp.Res_Code = convert_char_to_int(tmp_res);

		}
	}

	cout << "\n\tFlight Number: ";
	cin >> tmp_flightnum;
	while (!Check_FlightNum)
	{
		if (strlen(tmp_flightnum) != 4)
		{
			cout << "\n\t ***** Wrong ... Your FlightNumber must be four digit number Plz enter again  ***** ";
			cout << "\n\tFlight Number: ";
			cin >> tmp_flightnum;
		}
		else
		{
			for (int i = 0; i < strlen(tmp_flightnum); i++)
			{
				if (!Is_number(tmp_flightnum[i]))
				{
					cout << "\n\t ***** Wrong ... Your FlightNumber must be four digit number Plz enter again  ***** ";
					cout << "\n\tFlight Number: ";
					cin >> tmp_flightnum;
					break;
				}
			}
			Check_FlightNum = true;
			temp.FlightNumber = convert_char_to_int(tmp_flightnum);

		}
	}
	if (_ReservesTree.Is_reserve(temp.FlightNumber, temp.Res_Code, _ReservesTree.root) == true)
	{
		_ReservesTree.root = _ReservesTree.Delete_Reserve(temp.FlightNumber, temp.Res_Code, _ReservesTree.root);
		reservation_number--;
		number_of_reserves--;
		return true;
	}
	return false;
}

bool Client::Reserve_flight()
{
	Flight temp;
	bool Check_FlightNum = false;
	bool Check_Capacity = false;
	cout << "\n ############################################################################# \n" << endl;
	cout << "\tReserve flight: ";
	cout << "\n\t ***** Plz enter flight Informations ***** ";
	cout << "\n\tFlightNumber: ";
	cin >> temp.FlightNumber;
	while (!Check_FlightNum)
	{
		if (strlen(temp.FlightNumber) != 4)
		{
			cout << "\n\t ***** Wrong ... Your FlightNumber must be four digit number Plz enter again  ***** ";
			cout << "\n\tFlightNumber: ";
			cin >> temp.FlightNumber;
		}
		else
		{
			for (int i = 0; i < strlen(temp.FlightNumber); i++)
			{
				if (!Is_number(temp.FlightNumber[i]))
				{
					cout << "\n\t ***** Wrong ... Your FlightNumber must be four digit number Plz enter again  ***** ";
					cout << "\n\tFlightNumber: ";
					cin >> temp.FlightNumber;
					break;
				}
			}
			Check_FlightNum = true;

		}
	}
	cout << "\n\tAirLine: ";
	cin >> temp.AirLine;
	char tmp_Capacity[20];
	cout << "\n\tCapacity: ";

	cin >> tmp_Capacity;
	while (!Check_Capacity)
	{
		if (strlen(tmp_Capacity) > 3)
		{
			cout << "\n\t ***** Wrong ... Your Capacity can be Maximum of three digits number Plz enter again  ***** ";
			cout << "\n\tCapacity: ";
			cin >> tmp_Capacity;
		}
		else
		{
			for (int i = 0; i < strlen(tmp_Capacity); i++)
			{
				if (!Is_number(tmp_Capacity[i]))
				{
					cout << "\n\t ***** Wrong ... Your Capacity can be Maximum of three digits number Plz enter again  ***** ";
					cout << "\n\tCapacity: ";
					cin >> tmp_Capacity;
					break;
				}

			}
			temp.Capacity = convert_char_to_int(tmp_Capacity);
			Check_Capacity = true;

		}
	}
	cout << "\n\tDestination: ";
	cin >> temp.Destination;
	
	
	temp.FlightDate= give_date();
	if (_FlightsTree.Is_the_same_flight(temp.FlightNumber,temp.AirLine,temp.Capacity, temp.Destination,
		temp.FlightDate.year, temp.FlightDate.month, temp.FlightDate.day, temp.FlightDate.hour, temp.FlightDate.minute, _FlightsTree.root)==true)
	{
		char UserName[20];
		char FullName[40];
		date res_date;
		cout << "\n\t ***** OK ... now you shoudl complete your reserve informations ***** ";
		cout << "\n ############################################################################# \n" << endl;
		cout << "\n\t Plz enter your UserName: ";
		cin >> UserName;
		cout << "\n\t Plz enter your FullName: ";
		cin >> FullName;
		
		res_date = give_date();
		_ReservesTree.root = _ReservesTree.Insert2(convert_char_to_int(temp.FlightNumber), UserName, FullName, reservation_number + 1,
			res_date.year, res_date.month, res_date.day, res_date.hour, res_date.minute, _ReservesTree.root);

		number_of_reserves++;
		return true;
	}
	false;
}



bool Client::Is_user(char* UserName, char* Pass)
{
	
	if (_UsersTree.Is_user(UserName, Pass,_UsersTree.root)==true)
		return true;
	return false;
}

void Client::Unsubscribe()
{
	char UserName[20];
	char Pass[20];
	char Family[20];
	char Name[20];

	system("cls");
	cout << "\n ############################################################################# \n" << endl;
	cout << "\tUnsubscribe: "; 
	cout << "\n\tPlz enter your UserName: ";
	cin >> UserName;

	cout<< "\n\tPlz enter your PassWord: ";
	cin >> Pass;
	while (!Is_user(UserName,Pass))
	{
		cout << "\n\t ***** Wrong ... UserName or PassWord is incorrect Plz try again ***** ";
		cout << "\n\tPlz enter your UserName: ";
		cin >> UserName;
		cout << "\n\tPlz enter your PassWord: ";
		cin >> Pass;
	}
	_UsersTree.root = _UsersTree.Delete_User(UserName, Pass, _UsersTree.root);
	population--;
}

void Client::Save_datas()
{
	_UsersTree.SaveData();
	_FlightsTree.SaveData();
	_ReservesTree.SaveData();
}

void Client::Sign_UP(char* name,char* family,char* pass,char* UserName,char* NC)
{
	_UsersTree.root = _UsersTree.Insert2(name, family, pass, UserName, NC, _UsersTree.root);
}

int Client::Client_panel()
{
	int func;
	system("cls");
	cout << "\n ############################################################################# \n" << endl;
	cout << "\t Client panel: " << endl;
	cout << "\n\t (1) Unsubscribe" << endl;
	cout << "\t (2) Show all flights" << endl;
	cout << "\t (3) Show your reservations" << endl;
	cout << "\t (4) Find all flights to" << endl;
	cout << "\t (5) Reserve flight" << endl;
	cout << "\t (6) Cancel reservation" << endl;
	cout << "\t (7) Log out & back to menu" << endl;
	cout << "\t (0) quit & Log out !" << endl;
	cout << "\n\t Plz enter your function: ";
	cin >> func;
	return func;
}

class Admin
{

public:
	int Admin_panel();
	void Show_All_Users();
	bool Insert_flight();
	bool Show_all_reservations_for_flight();
	bool Check_someones_flight_to();
	void Show_all_flights();
	void Delete_flight();
	void Find_all_flights_to();
	void Save_datas();
};

bool Admin::Show_all_reservations_for_flight()
{
	char tmp_flightnum[20];
	long tmp_flightnumber = 0;
	bool result = false;
	bool Check_FlightNum = false;
	system("cls");
	cout << "\n ############################################################################# \n" << endl;
	cout << "\tShow all reservations for flight: ";
	cout << "\n\tFlight Number: ";
	cin >> tmp_flightnum;
	while (!Check_FlightNum)
	{
		if (strlen(tmp_flightnum) != 4)
		{
			cout << "\n\t ***** Wrong ... Your FlightNumber must be four digit number Plz enter again  ***** ";
			cout << "\n\tFlight Number: ";
			cin >> tmp_flightnum;
		}
		else
		{
			for (int i = 0; i < strlen(tmp_flightnum); i++)
			{
				if (!Is_number(tmp_flightnum[i]))
				{
					cout << "\n\t ***** Wrong ... Your FlightNumber must be four digit number Plz enter again  ***** ";
					cout << "\n\tFlight Number: ";
					cin >> tmp_flightnum;
					break;
				}
			}
			Check_FlightNum = true;
			tmp_flightnumber = convert_char_to_int(tmp_flightnum);

		}
	}
	_ReservesTree.Show_all_reserves_for(tmp_flightnumber, _ReservesTree.root, result);
	if (result == true)
		return true;
	return false;
}

bool Admin::Check_someones_flight_to()
{
	char UserName[20];
	char tmp_res[20];
	long tmp_reservation = 0;
	bool result = false;
	bool Check_Res_Code = false;
	system("cls");
	cout << "\n ############################################################################# \n" << endl;
	cout << "\tCheck someones flight to: ";
	cout << "\n\tPlz enter your UserName: ";
	cin >> UserName;
	cout << "\n\tReservation Code: ";
	cin >> tmp_res;
	while (!Check_Res_Code)
	{
		if (strlen(tmp_res) != 5)
		{
			cout << "\n\t ***** Wrong ... Your Reservation Code must be five digit number Plz enter again  ***** ";
			cout << "\n\tReservation Code: ";
			cin >> tmp_res;
		}
		else
		{
			for (int i = 0; i < strlen(tmp_res); i++)
			{
				if (!Is_number(tmp_res[i]))
				{
					cout << "\n\t ***** Wrong ... Your Reservation Code must be five digit number Plz enter again  ***** ";
					cout << "\n\tReservation Code: ";
					cin >> tmp_res;
					break;
				}
			}
			Check_Res_Code = true;
			tmp_reservation = convert_char_to_int(tmp_res);

		}
	}
	_ReservesTree.Find_all_reserves_for(UserName, tmp_reservation, _ReservesTree.root, result);
	if (result == true)
		return true;
	return false;
}

void Admin::Find_all_flights_to()
{
	
	char temp_destination[20];
	system("cls");
	cout << "\n ############################################################################# \n" << endl;
	cout << "\n\tPlz enter the Destination: ";
	cin >> temp_destination;
	bool result = false;
	_FlightsTree.Find_all_flights_to(temp_destination,_FlightsTree.root,result);
	if (result!=true)
	{
		cout << "\n\t ***** Wrong ... there is no flight with this destination ***** ";
		return;
	}
}
void Admin::Save_datas()
{
	_UsersTree.SaveData();
	

	_FlightsTree.SaveData();
	
	_ReservesTree.SaveData();
	
}

void Admin::Delete_flight()
{
	Flight temp;
	bool Check_FlightNum = false;
	bool Check_Capacity = false;
	bool Check_Year = false;
	bool Check_Month = false;
	bool Check_Day = false;
	bool Check_Hour = false;
	bool Check_Minute = false;
	cout << "\n ############################################################################# \n" << endl;
	cout << "\n\t ***** Plz enter flight Informations ***** ";
	cout << "\n\tFlightNumber: ";
	cin >> temp.FlightNumber;
	while (!Check_FlightNum)
	{
		if (strlen(temp.FlightNumber) != 4)
		{
			cout << "\n\t ***** Wrong ... Your FlightNumber must be four digit number Plz enter again  ***** ";
			cout << "\n\tFlightNumber: ";
			cin >> temp.FlightNumber;
		}
		else
		{
			for (int i = 0; i < strlen(temp.FlightNumber); i++)
			{
				if (!Is_number(temp.FlightNumber[i]))
				{
					cout << "\n\t ***** Wrong ... Your FlightNumber must be four digit number Plz enter again  ***** ";
					cout << "\n\tFlightNumber: ";
					cin >> temp.FlightNumber;
					break;
				}
			}
			Check_FlightNum = true;

		}
	}
	cout << "\n\tDestination: ";
	cin >> temp.Destination;
	
	temp.FlightDate = give_date();
	

	_FlightsTree.root = _FlightsTree.Delete_flight(temp.FlightNumber, temp.Destination,
		temp.FlightDate.year, temp.FlightDate.month, temp.FlightDate.day, temp.FlightDate.hour, temp.FlightDate.minute, _FlightsTree.root);
	number_of_flights --;
}

bool Admin::Insert_flight()
{
	Flight temp;
	bool Check_FlightNum = false;
	bool Check_Capacity = false;
	

	system("cls");

	cout << "\n ############################################################################# \n" << endl;
	cout << "\n\t ***** Plz enter new flight Informations ***** ";
	cout << "\n\tFlightNumber: ";
	cin >> temp.FlightNumber;
	while (!Check_FlightNum)
	{
		if (strlen(temp.FlightNumber)!=4)
		{
			cout << "\n\t ***** Wrong ... Your FlightNumber must be four digit number Plz enter again  ***** ";
			cout << "\n\tFlightNumber: ";
			cin >> temp.FlightNumber;
		}
		else 
		{
			for (int i = 0; i < strlen(temp.FlightNumber); i++)
			{
				if (!Is_number(temp.FlightNumber[i]))
				{
					cout << "\n\t ***** Wrong ... Your FlightNumber must be four digit number Plz enter again  ***** ";
					cout << "\n\tFlightNumber: ";
					cin >> temp.FlightNumber;
					break;
				}
					
			}
			Check_FlightNum = true;
			
		}
	}

	cout << "\n\tAirLine: ";
	cin >> temp.AirLine;
	char tmp_Capacity[20];
	cout << "\n\tCapacity: ";

	cin >> tmp_Capacity;
	while (!Check_Capacity)
	{
		if (strlen(tmp_Capacity) > 3)
		{
			cout << "\n\t ***** Wrong ... Your Capacity can be Maximum of three digits number Plz enter again  ***** ";
			cout << "\n\tCapacity: ";
			cin >> tmp_Capacity;
		}
		else
		{
			for (int i = 0; i < strlen(tmp_Capacity); i++)
			{
				if (!Is_number(tmp_Capacity[i]))
				{
					cout << "\n\t ***** Wrong ... Your Capacity can be Maximum of three digits number Plz enter again  ***** ";
					cout << "\n\tCapacity: ";
					cin >> tmp_Capacity;
					break;
				}

			}
			temp.Capacity = convert_char_to_int(tmp_Capacity);
			Check_Capacity = true;

		}
	}
	cout << "\n\tDestination: ";
	cin >> temp.Destination;
	
	temp.FlightDate = give_date();

	if (_FlightsTree.Is_the_same_flight(temp.FlightNumber, temp.AirLine, temp.Capacity, temp.Destination,
		temp.FlightDate.year, temp.FlightDate.month, temp.FlightDate.day, temp.FlightDate.hour, temp.FlightDate.minute,_FlightsTree.root) == true)
		return false;

	_FlightsTree.Insert2(temp.FlightNumber, temp.AirLine, temp.Capacity, temp.Destination,
		temp.FlightDate.year, temp.FlightDate.month, temp.FlightDate.day, temp.FlightDate.hour, temp.FlightDate.minute, _FlightsTree.root);
	number_of_flights = number_of_flights + 1;
	return true;
}

void Admin::Show_all_flights()
{
	system("cls");
	cout << "\n ############################################################################# \n" << endl;
	cout << "\t Flights Informations: " << endl;
	if (number_of_flights==0)
	{
		cout << "\n\t ***** Wrong ... there is no flight in the system ***** ";
		return;
	}
	_FlightsTree.Inorder(_FlightsTree.root);
}

void Admin::Show_All_Users()
{
	system("cls");
	cout << "\n ############################################################################# \n" << endl;
	cout << "\t Users Informations: " << endl;

	_UsersTree.Inorder(_UsersTree.root);
}

int Admin::Admin_panel()
{
	int func;
	system("cls");
	cout << "\n ############################################################################# \n" << endl;
	cout << "\t Admin panel: " << endl;
	cout << "\n\t (1) Insert flight" << endl;
	cout << "\t (2) Show all reservation for flight" << endl;
	cout << "\t (3) Check someone's flight to" << endl;
	cout << "\t (4) Show all flights" << endl;
	cout << "\t (5) Delete flight" << endl;
	cout << "\t (6) Find all flights to" << endl;
	cout << "\t (7) Log out & back to menu" << endl;
	cout << "\t (0) quit & Log out !" << endl;
	cout << "\n\t Plz enter your function: ";
	cin >> func;
	return func;
}


struct date give_date()
{
	bool Check_Year = false;
	bool Check_Month = false;
	bool Check_Day = false;
	bool Check_Hour = false;
	bool Check_Minute = false;
	date temp;
	cout << "\n\tDate: ";
	cout << "\n\t\tYear: ";
	cin >> temp.year;
	while (!Check_Year)
	{
		if (strlen(temp.year) > 2)
		{
			cout << "\n\t ***** Wrong ... Year can be Maximum of two digits number and bigger than \"95\"  Plz enter again  ***** ";
			cout << "\n\t\tYear: ";
			cin >> temp.year;
		}
		else if (convert_char_to_int(temp.year)>95)
		{
			Check_Year = true;
			for (int i = 0; i < strlen(temp.year); i++)
			{
				if (!Is_number(temp.year[i]))
				{
					cout << "\n\t ***** Wrong ... Year can be Maximum of two digits number and bigger than \"95\"  Plz enter again  ***** ";
					cout << "\n\t\tYear: ";
					cin >> temp.year;
					Check_Year = false;
					break;
				}
			}
		}

		else
		{
			cout << "\n\t ***** Wrong ... Year can be Maximum of two digits number and bigger than \"95\" Plz enter again  ***** ";
			cout << "\n\t\tYear: ";
			cin >> temp.year;
		}
	}

	cout << "\n\t\tMonth: ";
	cin >> temp.month;
	while (!Check_Month)
	{
		if (strlen(temp.month) > 2)
		{
			cout << "\n\t ***** Wrong ... Month can be between \"1 - 12\" (and we can use 01 or 1) Plz enter again  ***** ";
			cout << "\n\t\tMonth: ";
			cin >> temp.month;
		}
		else if (13>convert_char_to_int(temp.month)>0)
		{
			Check_Month = true;
			for (int i = 0; i < strlen(temp.month); i++)
			{
				if (!Is_number(temp.month[i]))
				{
					cout << "\n\t ***** Wrong ... Month can be between \"1 - 12\" (and we can use 01 or 1) Plz enter again  ***** ";
					cout << "\n\t\tMonth: ";
					cin >> temp.month;
					Check_Month = false;
					break;
				}
			}
		}

		else
		{
			cout << "\n\t ***** Wrong ... Month can be between \"1 - 12\" (and we can use 01 or 1) Plz enter again  ***** ";
			cout << "\n\t\tMonth: ";
			cin >> temp.month;
		}
	}
	cout << "\n\t\tDay: ";
	cin >> temp.day;
	while (!Check_Day)
	{
		if (strlen(temp.day) > 2)
		{
			cout << "\n\t ***** Wrong ... Day can be between \"1 - 31\" (and we can use 01 or 1) Plz enter again  ***** ";
			cout << "\n\t\tDay: ";
			cin >> temp.day;
		}
		else if (32>convert_char_to_int(temp.day)>0)
		{
			Check_Day = true;
			for (int i = 0; i < strlen(temp.day); i++)
			{
				if (!Is_number(temp.day[i]))
				{
					cout << "\n\t ***** Wrong ... Day can be between \"1 - 31\" (and we can use 01 or 1) Plz enter again  ***** ";
					cout << "\n\t\tDay: ";
					cin >> temp.day;
					Check_Day = false;
					break;
				}
			}
		}

		else
		{
			cout << "\n\t ***** Wrong ... Day can be between \"1 - 31\" (and we can use 01 or 1) Plz enter again  ***** ";
			cout << "\n\t\tDay: ";
			cin >> temp.day;
		}
	}
	cout << "\n\tTime: ";
	cout << "\n\t\tHour: ";
	cin >> temp.hour;
	while (!Check_Hour)
	{
		if (strlen(temp.hour) > 2)
		{
			cout << "\n\t ***** Wrong ... Hour can be between \"00 - 23\" (24 hours) Plz enter again  ***** ";
			cout << "\n\t\tHour: ";
			cin >> temp.hour;
		}
		else if (24>convert_char_to_int(temp.hour) && convert_char_to_int(temp.hour)>-1)
		{
			Check_Hour = true;
			for (int i = 0; i < strlen(temp.hour); i++)
			{
				if (!Is_number(temp.hour[i]))
				{
					cout << "\n\t ***** Wrong ... Hour can be between \"00 - 23\" (24 hours) Plz enter again  ***** ";
					cout << "\n\t\tHour: ";
					cin >> temp.hour;
					Check_Hour = false;
					break;
				}
			}
		}

		else
		{
			cout << "\n\t ***** Wrong ... Hour can be between \"00 - 23\" (24 hours) Plz enter again  ***** ";
			cout << "\n\t\tHour: ";
			cin >> temp.hour;
		}
	}
	cout << "\n\t\tMinute: ";
	cin >> temp.minute;
	while (!Check_Minute)
	{
		if (strlen(temp.minute) > 2)
		{
			cout << "\n\t ***** Wrong ... Minute can be between \"00 - 60\" (and we can use 01 or 1) Plz enter again  ***** ";
			cout << "\n\t\tMinute: ";
			cin >> temp.minute;
		}
		else if (60>convert_char_to_int(temp.minute) && convert_char_to_int(temp.minute)>-1)
		{

			Check_Minute = true;
			for (int i = 0; i < strlen(temp.minute); i++)
			{
				if (!Is_number(temp.minute[i]))
				{
					cout << "\n\t ***** Wrong ... Minute can be between \"00 - 60\" (and we can use 01 or 1) Plz enter again  ***** ";
					cout << "\n\t\tMinute: ";
					cin >> temp.minute;
					Check_Minute = false;
					break;
				}
			}
		}

		else
		{
			cout << "\n\t ***** Wrong ... Minute can be between \"00 - 60\" (and we can use 01 or 1) Plz enter again  ***** ";
			cout << "\n\t\tMinute: ";
			cin >> temp.minute;
		}
	}
	return temp;
}


int Start_menu()
{
	int func;
	system("cls");
	cout << "\n #################### WellCome to Iran_baam travel company #################### \n" << endl;
	cout << "\t (1) Sign in" << endl;
	cout << "\t (2) Sign up" << endl;
	cout << "\t (3) Show all flights" << endl;
	cout << "\t (0) quit !" << endl;
	cout << "\n\t Plz enter your function: ";
	cin >> func;
	return func;
}

int End_menu()
{
	system("cls");
	cout << "\n ############################################################################# \n" << endl;
	cout << "\n     ##################################################################### \n" << endl;
	cout << "\n         ############################################################# \n" << endl;
	cout << "\n             ##################### Good Bye ###################### \n" << endl;
	cout << "\n         ############################################################# \n" << endl;
	cout << "\n     ##################################################################### \n" << endl;
	cout << "\n ############################################################################# \n" << endl;
	Sleep(1 * 1000);
	return 0;
}

int convert_char_to_int(char* value)
{
	int res = 0;
	int length = strlen(value);
	int j = strlen(value);
	for (int i = 0; i < j; i++)
	{
		length--;
		res = res + ((int)((value[i]) - 48)*(int)(pow(10, length)));

	}
	return res;
}

bool Is_number(char point)
{
	if (point == '0' || point == '1' || point == '2' || point == '3'
		|| point == '4' || point == '5' || point == '6' || point == '7' || point == '8' || point == '9')
		return true;
	return false;
}

bool Is_admin(char* UserName, char* Pass)
{
	
	if (strcmp(UserName, AdminUserName) == 0 && strcmp(Pass, AdminPass) == 0)
		return true;
	else
		return false;
}

bool Check_NC(char* NC)
{
	if (strlen(NC) != 10)
		return false;

	for (int i = 0; i < strlen(NC); i++)
	{
		if (!Is_number(NC[i]))
			return false;
	}
	return true;
}


int main()
{
	Admin Admin_system;
	Client Client_system;
	int admin_func;
	int client_func;
	bool quit = false;
	bool quit1;
	
	
	int func = Start_menu();

	while (!quit)
	{
		switch (func)
		{
			char UserName[20];
			char Pass[20];
			char name[20];
			char family[20];
			char NC[11]; //National Code
		case -1:
			func = Start_menu();
			break;
		case 0:
			quit = true;
			break;
		case 1:
			if (population != 0)
			{
				system("cls");
				cout << "\n ############################################################################# \n" << endl;
				cout << "\t Sign in:" << endl;
				cout << "\n\t Plz enter your UserName: ";
				cin >> UserName;
				cout << "\n\t Plz enter your PassWord: ";
				cin >> Pass;
				if (Is_admin(UserName, Pass))
				{
					quit1 = false;
					while (!quit1)
					{
						admin_func = Admin_system.Admin_panel();
						switch (admin_func)
						{
						case 0:
							quit1 = true;
							quit = true;
							func = 0;
							break;
						case 1:
							if (Admin_system.Insert_flight()==true)
							{
								cout << "\n\t ***** congratulation ... your new flight inserted correctly ***** ";						
								cout << "\n\t *****  You will be returned to admin panel,Plz wait for seconds  ***** ";
								Admin_system.Save_datas();
								Sleep(5 * 1000);
								break;
							}
							cout << "\n\t ***** Wrong ... there is another flight in the system ***** ";
							cout << "\n\t *****  You will be returned to admin panel,Plz wait for seconds  ***** ";
							Admin_system.Save_datas();
							Sleep(5 * 1000);
							break;
						case 2:
							if (number_of_reserves != 0)
							{
								if (Admin_system.Show_all_reservations_for_flight() == true)
								{
									cout << "\n\t *****  You will be returned to admin panel,Plz press any key ***** ";
									Admin_system.Save_datas();
									_getch();
									break;
								}
								cout << "\n\t ***** Wrong ... this flight number has'nt any reserved ***** ";
								cout << "\n\t *****  You will be returned to admin panel,Plz wait for seconds***** ";
								Admin_system.Save_datas();
								Sleep(5 * 1000);
								break;

							}
							system("cls");
							cout << "\n ############################################################################# \n" << endl;
							cout << "\n\t ***** Wrong ... there is no resevation in the system ***** ";
							cout << "\n\t *****  You will be returned to admin panel,Plz wait for seconds  ***** ";
							Sleep(5 * 1000);
							break;

						case 3:
							if (number_of_flights != 0)
							{
								if (Admin_system.Check_someones_flight_to() == true)
								{
									cout << "\n\t ***** Yes ... this UserName has reserved for this flight ***** ";
									cout << "\n\t *****  You will be returned to admin panel,Plz wait for seconds  ***** ";
									Admin_system.Save_datas();
									_getch();
									break;
								}
								cout << "\n\t ***** Wrong ... this UserName hasnt reserved for this flight ***** ";
								cout << "\n\t *****  You will be returned to admin panel,Plz wait for seconds  ***** ";
								Admin_system.Save_datas();
								Sleep(5 * 1000);
								break;

							}
							system("cls");
							cout << "\n ############################################################################# \n" << endl;
							cout << "\n\t ***** Wrong ... there is no resevation in the system ***** ";
							cout << "\n\t *****  You will be returned to admin panel,Plz wait for seconds  ***** ";
							Sleep(5 * 1000);
							break;
						case 4:
							Admin_system.Show_all_flights();
							cout << "\n\t *****  Press any key for returning to admin panel ...  ***** ";
							_getch();
							break;
						case 5:
							if (number_of_flights != 0)
							{
								Admin_system.Show_all_flights();
								cout << "\n\t *****  which flight do you want to delete (Plz enter the flight informations) ***** ";
								Admin_system.Delete_flight();
								cout << "\n\t ***** congratulation ... your flight deleted correctly ***** ";
								cout << "\n\t *****  You will be returned to admin panel,Plz wait for seconds  ***** ";
								Admin_system.Save_datas();
								Sleep(5 * 1000);
								break;
							}
							system("cls");
							cout << "\n ############################################################################# \n" << endl;
							cout << "\n\t ***** Wrong ... there is no flight in the system ***** ";
							cout << "\n\t *****  You will be returned to admin panel,Plz wait for seconds  ***** ";
							Sleep(5 * 1000);
							break;

						case 6:
							if (number_of_flights != 0)
							{
								Admin_system.Find_all_flights_to();
								cout << "\n\t *****  Press any key for returning to admin panel ...  ***** ";
								_getch();
								break;
							}
							system("cls");
							cout << "\n ############################################################################# \n" << endl;
							cout << "\n\t ***** Wrong ... there is no flight in the system ***** ";
							cout << "\n\t *****  You will be returned to admin panel,Plz wait for seconds  ***** ";
							Sleep(5 * 1000);
							break;

						case 7:
							cout << "\n\t ***** Plz wait for seconds ***** ";
							Sleep(2 * 1000);
							func = Start_menu();
							quit1 = true;
							break;
						default:
							cout << "\n\t ***** Wrong ... Plz try again ***** ";
							Sleep(2 * 1000);
							admin_func = Admin_system.Admin_panel();
							break;
						}
					}
				}

				else if (Client_system.Is_user(UserName,Pass))
				{
					quit1 = false;
					while (!quit1)
					{
						client_func = Client_system.Client_panel();
						switch (client_func)
						{
						case 0:
							quit1 = true;
							quit = true;
							func = 0;
							break;
						case 1:
							Client_system.Unsubscribe();
							cout << "\n\t ***** your account Unsubscribed correctly ***** ";
							cout << "\n\t *****  You will be returned to menu,Plz wait for seconds  ***** ";
							Admin_system.Save_datas();
							Sleep(5 * 1000);
							quit1 = true;
							func = -1;
							break;

						case 2:
							Admin_system.Show_all_flights();
							cout << "\n\t *****  Press any key for returning to client panel ...  ***** ";
							_getch();
							break;

						case 3:
							if (number_of_reserves != 0)
							{
								if (Client_system.Show_your_reservations() == true)
								{
									Admin_system.Save_datas();
									cout << "\n\t *****  Press any key for returning to client panel ...  ***** ";
									_getch();
									break;
								}
								cout << "\n\t ***** Wrong ... you dont have any reservation for any flight ***** ";
								cout << "\n\t *****  You will be returned to client panel,Plz wait for seconds  ***** ";
								Admin_system.Save_datas();
								Sleep(5 * 1000);
								break;
							}
							system("cls");
							cout << "\n ############################################################################# \n" << endl;
							cout << "\n\t ***** Wrong ... there is no resevation in the system ***** ";
							cout << "\n\t *****  You will be returned to client panel,Plz wait for seconds  ***** ";
							Sleep(5 * 1000);
							break;
							
						case 4:
							if (number_of_flights != 0)
							{
								Admin_system.Find_all_flights_to();
								cout << "\n\t *****  Press any key for returning to client panel ...  ***** ";
								_getch();
								break;
							}
							system("cls");
							cout << "\n ############################################################################# \n" << endl;
							cout << "\n\t ***** Wrong ... there is no flight in the system ***** ";
							cout << "\n\t *****  You will be returned to client panel,Plz wait for seconds  ***** ";
							Sleep(5 * 1000);
							break;


						case 5:
							Admin_system.Show_all_flights();
							if (Client_system.Reserve_flight()==true)
							{
								cout << "\n\t ***** congratulation ... your flight reserved correctly ***** ";
								cout << "\n\t *****  You will be returned to client panel,Plz wait for seconds  ***** ";
								Admin_system.Save_datas();
								Sleep(5 * 1000);
								break;
							}
							cout << "\n\t ***** Wrong ... there isnt any flight with this information in the system ***** ";
							cout << "\n\t *****  You will be returned to client panel,Plz wait for seconds  ***** ";
							Admin_system.Save_datas();
							Sleep(5 * 1000);
							break;
							

						case 6:
							if (Client_system.Cancel_reservation() == true)
							{
								cout << "\n\t ***** congratulation ... your reservation correctly canceled ***** ";
								cout << "\n\t *****  You will be returned to client panel,Plz wait for seconds  ***** ";
								Admin_system.Save_datas();
								Sleep(5 * 1000);
								break;
							}
							cout << "\n\t ***** Wrong ... there isnt any reservation with this information in the system ***** ";
							cout << "\n\t *****  You will be returned to client panel,Plz wait for seconds  ***** ";
							Admin_system.Save_datas();
							Sleep(5 * 1000);
							break;

						case 7:
							cout << "\n\t ***** Plz wait for seconds ***** ";
							Sleep(2 * 1000);
							func = Start_menu();
							quit1 = true;
							break;
						default:
							cout << "\n\t ***** Wrong ... UserName or PassWord is incorrect Plz try again ***** ";
							Sleep(2 * 1000);
							client_func = Client_system.Client_panel();
							break;
						}
					}
				}
				else
				{
					cout << "\n\t ***** Wrong ... Plz try again ***** ";
					Sleep(2 * 1000);
				}
				break;

			}
			else
			{
				cout << "\n ############################################################################# \n" << endl;
				cout << "\n\t ***** Wrong ... there is no User in the system ***** ";
				cout << "\n\t *****  You will be returned to menu,Plz wait for seconds  ***** ";
				Sleep(5 * 1000);
				func = -1;
				break;
			}
			
		case 2:
			system("cls");
			cout << "\n ############################################################################# \n" << endl;
			cout << "\t Sign up:" << endl;
			cout << "\n\t Plz enter your UserName: ";
			cin >> UserName;
			while (Client_system.Is_user(UserName,Pass)==true)
			{
				cout << "\n\t ***** Wrong ... there is another account with this username or password, Plz try again after seconds ***** ";
				Sleep(3 * 1000);
				system("cls");
				cout << "\n ############################################################################# \n" << endl;
				cout << "\t Sign up:" << endl;
				cout << "\n\t Plz enter your UserName: ";
				cin >> UserName;
			} 
			cout << "\n\t Plz enter your PassWord: ";
			cin >> Pass;
			while (strlen(Pass) <= 4)
			{
				cout << "\n\t ***** Wrong ... Your password must be greater than four characters Plz enter again  ***** ";
				cout << "\n\t Plz enter your PassWord: ";
				cin >> Pass;
			}
			if (Is_admin(UserName, Pass))
			{
				bool temp_quit = false;
				int temp;
				while (!temp_quit)
				{
					cout << "\n\t ***** you are admin in system ***** ";
					cout << "\n\t ***** do you want to sign in as admin(1) or back to the menu(2) ? ***** ";
					cin >> temp;
					if (temp == 1)
					{
						cout << "\n\t ***** Ok ... Just enter your username and password after changing the window again ***** ";
						Sleep(4 * 1000);
						func = 1;
						break;
					}
					else if (temp == 2)
					{
						cout << "\n\t ***** Ok ... Just wait fo changing the window ***** ";
						Sleep(4 * 1000);
						func = Start_menu();
						break;
					}
					else
					{
						cout << "\n\t ***** Wrong ... Plz try again ***** ";
						Sleep(2 * 1000);
					}
				}	
			}
			else 
			{
				while (Client_system.Is_user(UserName,Pass)==true)
				{
					cout << "\n\t ***** Wrong ... there is another account with this username or password, Plz try again after seconds ***** ";
					Sleep(2 * 1000);
					system("cls");
					cout << "\n ############################################################################# \n" << endl;
					cout << "\t Sign up:" << endl;
					cout << "\n\t Plz enter your UserName: ";
					cin >> UserName;
					while (Client_system.Is_user(UserName, Pass)==true)
					{
						cout << "\n\t ***** Wrong ... there is another account with this username or password, Plz try again after seconds ***** ";
						Sleep(3 * 1000);
						system("cls");
						cout << "\n ############################################################################# \n" << endl;
						cout << "\t Sign up:" << endl;
						cout << "\n\t Plz enter your UserName: ";
						cin >> UserName;
					}
					cout << "\n\t Plz enter your PassWord: ";
					cin >> Pass;

				}
				cout << "\n\t Plz enter your Name: ";
				cin >> name;
				cout << "\n\t Plz enter your family: ";
				cin >> family;
				cout << "\n\t Plz enter your National Code: ";
				cin >> NC;
				while (!Check_NC(NC))
				{
					cout << "\n\t ***** Wrong ... Your national code must be a ten digit number Plz enter again  ***** ";
					cout << "\n\t Plz enter your National Code: ";
					cin >> NC;
				}
				Client_system.Sign_UP(name, family, Pass, UserName, NC);
				population++;
				Client_system.Save_datas();
				cout << "\n\t ***** congratulation ... now you are one of our clients ***** ";
				cout << "\n\t *****  You will be returned to menu for sign in to your account ,Plz wait for seconds  ***** ";
				Sleep(5 * 1000);
				func = -1;
			}
			break;

		case 3:
			Admin_system.Show_all_flights();
			cout << "\n ############################################################################# \n" << endl;
			cout << "\t (1) Sign in to reserve a flight" << endl;
			cout << "\t (2) Reserve a flight" << endl;
			cout << "\t (3) back to menu" << endl;
			cout << "\t (0) quit !" << endl;
			cout << "\n\t Plz enter your function: ";
			cin >> func;
			switch (func)
			{
			case 1:
				func = 1;
				break;
			case 2:
				break;
			case 3:
				func = -1;
				break;
			case 0:
				func = 0;
				break;
			}
			break;

		default:
			cout << "\n\t ***** Wrong ... Plz enter try again ***** ";
			Sleep(2 * 1000);
			func = Start_menu();
			break;
		}
	}
	return End_menu();
}
