#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include<iomanip>
#include<conio.h>

using namespace std;

//Function to create/append a file
void file(string name){
	fstream File;
	int MAX=300;
	char str[MAX];
	File.open(name);
	if(!File){
		cout<<"\nFile doesnt exist , wait for the registrations or feedback\n";
		exit(1);
	}
	while(!File.eof()){
		File.getline(str,MAX);
		cout << str << endl;
	}
	File.close();
}

class Admin{
private:	
	const string username="dsaa", password="dsaa.project";
	
public:
	void login(){
		string user, pw;
		cout << "\n\n\tLOG IN" << endl;
		cout << "\nEnter username: ";
		cin >> user;
		cout << "Enter password: ";
		cin >> pw; 
		if (username!=user || password!=pw)	{
			cout << "Wrong info, please try again!" << endl;
			login();
		}
		else {
			cout << "\nYou're logged in!" << endl;
		}		
	}
	
	void view_feedback(){
		cout<<"\n\tREVIEWS"<<endl;
		file("RiderFeedback.txt");	
	}
	
	void view_driver_records(){
		cout<<"\n\tDRIVER RECORDS"<<endl;
		file("DriverDetails.txt");
	}
	
	void view_rider_records(){
		cout<<"\n\tREGISTERED RIDERS"<<endl;
		file("Registeredriders.txt");
	}
	
	void admin_menu(){
		int option;
		cout << "\n\n\n\t     ADMIN MENU  " << endl;
		cout << "\n\n\t 1. View Driver Records" << endl;
		cout << "\t 2. View Riders Records " << endl;
		cout << "\t 3. View Feedback " << endl;
		cout << "\t 4. Main Menu / Exit " << endl;
		cout << "\n\t Choose an option: " ;
		cin >> option;
		switch (option)
		{
			case 1:
				view_driver_records();
				cout << "\n\t\t\tPress any key to continue" << endl;
				getch();
				admin_menu();
				break;
			
			case 2:
				view_rider_records();
				cout << "\n\t\t\tPress any key to continue" << endl;
				getch();
				admin_menu();
				break;
			
			case 3:
				view_feedback();
				cout << "\n\t\t\tPress any key to continue" << endl;
				getch();
				admin_menu();
				break;
			case 4:
				break;
			
			default:
				cout << "\n\t\t\tIncorrect option! Please try again." << endl;
				admin_menu();
				break;
		}
	}
};

// Function to check if the character is an alphabet or not
bool isChar(char c){
	    return ((c >= 'a' && c <= 'z')
	            || (c >= 'A' && c <= 'Z'));
	}
	
bool isName(string name){
	 int s=name.size();
	 for(int i=0;i<s;i++){
	 	if (!isChar(name[i])){
	 		return false;
		 }
	 }
	 return true;
	}

// Function to check if the email ID is valid or not
bool is_valid(string email){
	    if (!isChar(email[0])) {
	        return 0;
	    }
	    int At = -1, Dot = -1;
	    for (int i = 0; i < email.length(); i++) {
	        if (email[i] == '@') {
	            At = i;
	        }
	        else if (email[i] == '.') {
	            Dot = i;
	        }
	    }
	    if (At == -1 || Dot == -1)
	        return 0;
	    if (At > Dot)
	        return 0;
	    return !(Dot >= (email.length() - 1));
	}

class Driver{
	private:
			string name, phone_number, email, NIC;
			int age;
	public:
		bool driver_register(){
			cout<<"\nRegister yourself as a driver!"<<endl;
			cout<<"\nEnter your name: ";
			cin>>name;
			while (!isName(name)) {
		            cout << "invalid name!  name must only be alphabetic"<<endl;
		            cout << "Enter  Name: "; cin >> name;
		        } 
			cin.sync();
			cout << "Enter Phone Number: " ;
			cin >> phone_number;
			while (phone_number.length() != 11) {
		            cout << "Wrong number! Length must be 11 digits"<<endl;
		            cout << "Enter Phone Numbe: "; cin >> phone_number;
		        } 
			cout << "Enter Email: " ;
			cin >> email;
			while(!is_valid(email)){
				cout<<"Wrong email provided!"<<endl;
				cout<<"Enter correct Email: ";
				cin>>email;
			}
			cout << "Enter Age: " ;
			cin >> age;
			if (age >= 18) {
				cout << "Enter NIC: " ;
				cin >> NIC;
				while (NIC.length() != 13) {
		            cout << "Wrong NIC! Length must be 13 digits"<<endl;
		            cout << "Enter NIC: "; cin >> NIC;
		        } 
			cout<<"\nYou have been registered!";
			
			//Storing driver details in a file
			fstream File;
			File.open("DriverDetails.txt", ios::app);
			File << "\nName: " << name << endl;
			File << "Phone Number: " << phone_number << endl;
			File << "Email: " << email << endl;
			File << "NIC: " << NIC << endl;
			File << "Age: " << age << endl;
			File.close();
			
			//Storing driver names in a file
			fstream File2;
			File2.open("Availabledrivers.txt", ios::app);
			File2 << name<<endl;
			File2.close();
			return true;
		}
		else{
			cout<<"Not old enough to register"<<endl;
			return false;
		}
	}
};

// Class to represent a weighted edge in the graph
class Edge {
public:
    int to;
    int weight;

    Edge(int to, int weight) {
        this->to = to;
        this->weight = weight;
    }
};

// Class to represent a weighted graph
class Graph {
public:
    int V;
    vector<vector<Edge>> adj;
    unordered_map<int, string> vertex_names;

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Function to add an edge to the graph
    void addEdge(int from, int to, int weight) {
        adj[from].push_back(Edge(to, weight));
    }

    // Function to add a vertex name to the graph
    void addVertexName(int vertex, string name) {
        vertex_names[vertex] = name;
    }
};

// Function to implement Dijkstra's algorithm
vector<int> dijkstra(Graph g, int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> dist(g.V, INT_MAX);
    pq.push({ 0, start });
    dist[start] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto e : g.adj[u]) {
            int v = e.to;
            int weight = e.weight;
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({ dist[v], v });
            }
        }
    }
    return dist;
}

class Bill{
	public:	
	Bill(int m,int n){
		Graph g(1200);
		
	    // Add the names of vertices to the graph
	    g.addVertexName(1, "University road");
	    g.addVertexName(2, "Karsaz");
	    g.addVertexName(3, "Bahadurabad");
	    g.addVertexName(4, "Gulshan");
	    g.addVertexName(5, "North Nazimabad");
	    g.addVertexName(6, "Baloch Colony");
	    g.addVertexName(7, "Defense");
	    g.addVertexName(8, "Clifton");
	    g.addVertexName(9, "Metropole");
	    g.addVertexName(10, "Kemari");
	    g.addVertexName(11, "Saddar");
	    g.addVertexName(12, "Gulberg");
	    g.addVertexName(13, "Lyari Expressway");
	
	    // Add edges to the graph
	    g.addEdge(1, 2, 300);    g.addEdge(2, 1, 300);
	    g.addEdge(1, 3, 400);	 g.addEdge(3, 1, 400);
	    g.addEdge(1, 4, 300);    g.addEdge(4, 1, 300);
	    g.addEdge(1, 5, 400);    g.addEdge(5, 1, 400);
	    g.addEdge(2, 3, 200);    g.addEdge(3, 2, 200);
	    g.addEdge(3, 6, 900);    g.addEdge(6, 3, 900);
	    g.addEdge(3, 9, 700);    g.addEdge(9, 3, 700);
	    g.addEdge(4, 5, 300);    g.addEdge(5, 4, 300);
	    g.addEdge(4, 13, 1200);  g.addEdge(13, 4, 1200);
	    g.addEdge(6, 7, 800);    g.addEdge(7, 6, 800);
	    g.addEdge(7, 8, 700);    g.addEdge(8, 7, 700);
	    g.addEdge(8, 9, 500);    g.addEdge(9, 8, 500);
	    g.addEdge(8, 10, 300);   g.addEdge(10, 8, 300);
	    g.addEdge(9, 10, 400);   g.addEdge(10, 9, 400);
	    g.addEdge(9, 11, 300);   g.addEdge(11, 9, 300);
	    g.addEdge(10, 11, 600);  g.addEdge(11, 10, 600);
	    g.addEdge(11, 12, 300);  g.addEdge(12, 11, 300);
	    g.addEdge(12, 13, 500);  g.addEdge(13, 12, 500);
	
	    vector<int> cash = dijkstra(g, m);
	    //Get total fare
        cout <<"The total fare from "<< g.vertex_names[m]<<" to "<< g.vertex_names[n] << " is " << cash[n] << "Rs"<< endl;
	}
};

class Car{ 
public: 
	string model; 
	string colour; 
	int capacity_of_passengers; 
	Car* next; 
}; 

class CarList{ 
private: 
	Car* head; 
	
public: 
	CarList(){ 
		head = NULL; 
	} 
	
	void addCar(string m, string c, int cp) { 
		if (head==NULL) { 
			head = new Car(); 
			head->model = m; 
			head->colour = c; 
			head->capacity_of_passengers = cp; 
			head->next = NULL; 
		} 
		else { 
			Car* temp = new Car(); 
			temp->model = m; 
			temp->colour = c; 
			temp->capacity_of_passengers = cp; 
			temp->next = head; 
			head = temp; 
		} 
	} 
	
	//Assign a car based on the entered number of passengers
	bool assignCar(int n) { 
		Car* temp = new Car(); 
		temp = head; 
		while (temp != NULL) { 
			if (temp->capacity_of_passengers >= n) { 
				cout << "\nA "<<temp->colour<<" coloured "<<temp->model<<" will be waiting right at your location!\n"<<endl; 
				return true; 
			} 
			temp = temp->next; 
		} 
		cout << "No car available for given number of passengers!" << endl; 
		return false;
	} 
}; 

class Ride{
public:
	int data;
    Ride *next;
    Ride(int d){
	    data=d;
	    next=NULL;
		}
};

class RideLinkedList{
private:
	Ride *head;
	
public: 
	RideLinkedList(){
		head=NULL;
	} 

	void Add_ride(int d){
		if(head==NULL){
			Ride *newNode=new Ride(d);
			newNode->next=head;
			head=newNode;
		}
		else{
			Ride *current=head;
			while(current->next!=NULL){
				current=current->next;}
			Ride *newNode=new Ride(d);
			current->next=newNode; 
		} 
	}
		
	void Display_ride(){
		if(head==NULL){
			cout<<"\nNo Ride IDs"<<endl;	
		}
		else{
			cout<<"\nDisplaying all Ride IDs"<<endl;
			Ride *current=head;
			while(current!=NULL){
				cout<<current->data<<endl;
				current=current->next;
			}
	    }
	} 
	
	void delete_ride(int d){
		Ride *current=head;
		if(head!=NULL){
			if (head->data==d){
				head=head->next;
				delete current;
				cout<<"Deleted"; }
			else{
				Ride *previous=NULL;
				while(current!=NULL && current->data!=d){
					previous=current;
					current=current->next;}
				if(current!=NULL){
					previous->next=current->next;
					delete current;
					cout<<"Deleted"<<endl;
				}
				else{
					cout<<"Ride ID not found"<<endl;
				}
			}
		}
		else{
			cout<<"Ride ID not found"<<endl;
		}
	}
}; 

class Rider {
private:
	string name, phone_number, email, NIC;
	int age,ID;
	
public:	
	CarList cl;
	RideLinkedList list;
	
	bool Register(){
		cout << "\nEnter Name: " ;
		cin >> name;
		while (!isName(name)) {
		            cout << "invalid name!  name must only be alphabetic"<<endl;
		            cout << "Enter  Name: "; cin >> name;
		        } 
		cin.sync();
		cout << "Enter Phone Number: " ;
		cin >> phone_number;
		while (phone_number.length() != 11) {
	        cout << "Wrong number! Length must be 11 digits"<<endl;
	        cout << "Enter Phone Number: "; cin >> phone_number;
	    } 
		cout << "Enter Email: " ;
		cin >> email;
		while(!is_valid(email)){
			cout<<"Wrong email provided!"<<endl;
			cout<<"Enter correct Email: ";
			cin>>email;
		}
		cout << "Enter Age: " ;
		cin >> age;
		if (age >= 18) {
			cout << "Enter NIC: " ;
			cin >> NIC;
			while (NIC.length() != 13) {
	            cout << "Wrong NIC! Length must be 13 digits"<<endl;
	            cout << "Enter NIC: "; cin >> NIC;
	        } 
	        cout <<"\nYou are Registered!\n";
	        
	        //Storing rider details in a file
	        fstream File;
			File.open("Registeredriders.txt", ios::app);
			File << "\nName: " << name << endl;
			File << "Phone Number: " << phone_number << endl;
			File << "Email: " << email << endl;
			File << "NIC: " << NIC << endl;
			File << "Age: " << age << endl;
			File.close();
			return true;
        }
		else{
			cout << "Not old enough to register!"<<endl;
			return false;
		} 
	}
	
	void rider_register(){
		cout<<"\nPlease register yourself first"<<endl;
		bool res=Register();
		if(res){
			get_ride();
			rider_menu();
		}
	}
	
	void give_feedback(){
		int rating;
		string review;
		cout << "\nEnter your name: ";
		cin >> name;
		cin.sync();
		cout << "Enter your rating out of 5: ";
		cin >> rating;
		if (rating<1 || rating>5){
			cout << "Invalid, please try again!" << endl;
			give_feedback();
		}
		else{
			cout << "Enter review: ";
			cin >> review;
			cin.sync();
			cout << "\nThank you for your feedback!" << endl;
			
			//Storing rider feedback in a file
			fstream file;
			file.open("RiderFeedback.txt", ios::app);
			file << "\nName: "<< name << endl;
			file << "Rating: " << rating << "/5 stars" << endl;
			file << "Review: " << review << endl;
			file.close();
		}
	}

	//Assign a driver from the the file containg driver names
	string get_driver(){
		ifstream in ( "Availabledrivers.txt" );
		vector<string> words;
		string word;
		if ( !in )
		  return "Huma";
		while ( in>> word )
		  words.push_back ( word );
		return words[rand() % words.size()];
	}

	void  get_ride(){
		int r3andom,n,pickup,destination;
		cout << "\nLets book a ride for you!" << endl;
		srand(time(0));
		int random;
		random=rand(); 
		cl.addCar("Honda City", "Red", 15); 
		cl.addCar("Jeep Compass", "Black", 12); 
		cl.addCar("Toyota Innova", "White", 10); 
		cl.addCar("Tata Nano", "Blue", 9); 
		cl.addCar("BMW", "Black", 7); 
		cl.addCar("Audi", "White", 5); 
		cl.addCar("Hyundai", "Silver", 4); 
		cl.addCar("Maruti", "White", 3); 
		cl.addCar("Mercedes", "White", 2);
		cl.addCar("Heavy Bike", "Red", 1);

		cout<<"\nEnter the number of passengers: ";
		cin >> n;
		
		bool assign = cl.assignCar(n);
		if(assign){
			cout<<"1)University Road\n2)Karsaz\n3)Bahadurabad\n4)Gulshan\n5)North Nazimabad\n";
			cout<<"6)Baloch Colony\n7)Defense\n8)Clifton\n9)Metropole\n10)Kemari\n11)Saddar\n12)Gulberg\n13)Lyari Expressway\n\n";
			pickup=pick_up();
			destination=des_loc();
			cout <<"\n\tYour car is booked!\n"<<endl;
			cout<<"\nYour Drivers name: "<<get_driver();
			cout<<"\nRide ID: "<<random<<endl;
			list.Add_ride(random);
			Bill m1(pickup,destination);
		}		
	}

	int pick_up(){
		int pickup;
		cout<<"Enter a number for Pickup location(1-13): ";
		cin>>pickup;
		if(pickup>13 || pickup<1){
			cout<<"Incorrect location"<<endl;
			return pick_up();
		}
		return pickup;
	}
	
	int des_loc(){
		int d;
		cout<<"Enter a number for Destination(1-13): ";
		cin>>d;
		if(d>13 || d<1){
			cout<<"Incorrect location"<<endl;
			return des_loc();
		}
		return d;
	}
	
	void cancel_ride(){
		cout<<"Enter the ride ID you want to cancel: ";
		cin>>ID;
		list.delete_ride(ID);
	}
	
	void rider_menu(){
		int option;
		cout << "\n\n\n\t     RIDER MENU  " << endl;
		cout << "\n\t 1. Search for another ride " << endl;
		cout << "\t 2. See all accepted rides "<< endl;
		cout << "\t 3. Cancel a ride " << endl;
		cout << "\t 4. Main Menu / Exit " << endl;
		cout << "\n\t Choose an option: " ;
		cin >> option;
			switch (option){
				case 1:
					get_ride();
					cout << "\n\t\t\tPress any key to continue" << endl;
					getch();
					rider_menu();
					break;
				
				case 2:
					list.Display_ride();
					cout << "\n\t\t\tPress any key to continue" << endl;
					getch();
					rider_menu();
					break;
				
				case 3:
					cancel_ride();
					cout << "\n\t\t\tPress any key to continue" << endl;
					getch();
					rider_menu();
					break;
				
				case 4:
					break;
				
				default:
					cout << "\n\t\t\tIncorrect option! Please try again." << endl;
					rider_menu();
					break;
		}
	}
};

class App{
private:
	string App_name = "Elite Ride"; 
public:
	Admin a1;
	Driver d1;
	Rider r1;
	
	void main_menu(){
		cout << "\n\t\t  Welcome to " << App_name << "!" << endl;
		cout << "\t\tThank you for choosing us"<<endl;
		int option;
		cout << "\n\n\n\t     MAIN MENU " << endl;
		cout << "\n\t 1. Rider" << endl;
		cout << "\t 2. Driver " << endl;
		cout << "\t 3. Admin " << endl;
		cout << "\n\t Choose an option: " ;
		cin >> option;
		switch (option)
		{
			case 1:
				r1.rider_register();
				break;
			
			case 2:
					d1.driver_register();
					break;
			
			case 3:
				a1.login();
				a1.admin_menu();
				break;
			
			default:
				cout << "\n\t\t\t\t\t\t Incorrect option. " ;
				main_menu();
				break;
		}	
	}
};

int main(){
	string choice;
	App app;
	app.main_menu();
	cout<<"\n\n\t1. Main menu \n\t0. Exit\n"; 
	cout<<"\n\tChoose an option: "; cin>>choice;
	if(choice=="1"){
		main(); }	
	return 0;
}