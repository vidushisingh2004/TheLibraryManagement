#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;

class Book{//Define class Book
    private://6 attributes
        string title, author, ISBN;
        int numberOfCopies, year;
        float rating;

    public:

        Book(string t, string a, int n, string i, float r, int y){//Constructor
            title = t;
            author = a;
            numberOfCopies = n;
            ISBN = i;
            rating = r;
            year = y;
        }

        string getTitle(){//return title
            return title;
        }

        string getISBN(){//return ISBN
                return ISBN;
        }

        string getAuthor(){//return author
                return author;
        }

        int getNumOfCopies(){//return No. of Copies
            return numberOfCopies;
        }

        float getRating(){//return rating
            return rating;
        }

        int getYear(){//return published year
            return year;
        }
        
        bool operator <(const Book& other) const{//compare the title
            string thisTitleLower = title;
            string otherTitleLower = other.title;
            transform(thisTitleLower.begin(), thisTitleLower.end(), thisTitleLower.begin(), ::tolower);
            transform(otherTitleLower.begin(), otherTitleLower.end(), otherTitleLower.begin(), ::tolower);
            return thisTitleLower < otherTitleLower;
        }

        void displayBook(){//print out the informatio of the book
            cout << "   Title: " << title << endl << "   Author: " << author << endl << "   ISBN: " << ISBN << endl << "   Number of Copies: " << numberOfCopies <<endl <<"   Rating: " << rating << endl << "   Published year: " << year << endl;
            return; 
        }
};

class Library{//binary search tree
    private:
        class Node{//class Node for the binary tree
            public:
                Book* data;
                Node* left = nullptr;
                Node* right = nullptr;
                Node(Book* a){
                    data = a;
                }
        };
        Node* root;

    public:

        Library(){//constructor
            root = nullptr;
        }


        Node* getRoot(){//return the pointer pointing to the root
            return root;
        }

        void setRoot(Node* a){//set root equal to a node
            root = a;
        }

        Node* addBook(Node* r, Book* a){//add the book according to the alphabetical order
            //Ava
            //creating a new node with the attributes wanted 
            Node* newNode = new Node(a);
            //figuring out if there are any books in the tree/library by seeing if the root of the tree has a value or not
            
            if (r== nullptr){
            //if the tree does not have a value the new node/book being added into the library becomes the root of the tree
            // Returning the root of the tree/ the new book
                return newNode;
            }  

            //Creating a temporary node with the attributes of the root to assist with the next function 
            Node* temp = r;
            
            //If the title of the root/temporary book is less than the new book (check by the operator <) the following lines of code add the book to the right side of the tree as we are organizing the library in alphabetical order  
            if(*(temp -> data) < *a){
                if (temp -> right == nullptr){
                    temp -> right = newNode;
                }
                //Using recursion so the new node a and the book go through the fuction again to find where the book will fit in the tree/library
                else addBook(temp -> right, a);
            } 

            else{
                //The following lines of code add the book to the the left side of the tree if their title allows 
                if(temp -> left == nullptr){
                    //adding a book to the right side
                    temp -> left= newNode;
                }
                else{
                    //Using recursion so the new node a and the book go through the fuction again to find where the book will fit in the tree/library
                    addBook(temp -> left, a);
                }
            }
            return r;//return the root
        }
        
        void search(string t) {
            Node* current = root; // Starting from the root node of the binary search tree
            while (current != nullptr) { // Keep iterating until we reach a leaf node
            if (current -> data -> getTitle() == t){ // If the current node's book title matches the given title
                current -> data -> displayBook(); // Display the book's details
                return; // End the function
            } else if (t < current -> data -> getTitle()){ // If the given title is smaller than the current node's book title
                current = current -> left; // Move to the left subtree
            } else { // Otherwise (i.e., if the given title is larger than the current node's book title)
                current = current -> right; // Move to the right subtree
            }
            }
            cout << "Book is not found." << endl; // If the function reaches this point, the book was not found in the tree
            return; // End the function
            }
        
        bool remove(string t) {
        //Morgan
            Node* parent = NULL; //parent set to null
            Node* current = root; // current set to root
            bool is_left_child = false; //bool variable is set as false
            while (current != NULL) { // loop to go through tree
                if (current->data->getTitle() == t) { //using the getTitle attribute to see if current node's title is the same as string t
                    break; //breaks out of loop if title is found
                } else if (t < current -> data -> getTitle()) { //move left or right depending on if t is smaller or greater than title
                    parent = current;
                    current = current->left;
                    is_left_child = true;
                } else {
                    parent = current;
                    current = current->right;
                    is_left_child = false;
                }
            }
            if (current == NULL) {
                cout << "The book " << t << " is not available in the library." << endl;
                return false;
            }
            // Case 1: Node has no children
            if (current->left == NULL && current->right == NULL) { //checks that node has no children
                if (current == root) { //checks if current node is the root
                    root = NULL;
                } else if (is_left_child) { //sets either left or right child to null which removes current node from tree
                    parent->left = NULL;  
                } else {
                    parent->right = NULL;
                }
                delete current; //deletes memory of child node using delete operator
                cout << "The book " << t << "is deleted from the library." << endl;
            }
            // Case 2: Node has one child
            else if (current->left == NULL) { // checks for no left child
                if (current == root) { //if theres no left child, checks if current is root
                    root = current->right;  // if yes, then it sets root to the right child of current node --> new root
                } else if (is_left_child) { //checks if left child
                    parent->left = current->right; //then sets left child of parent to right of current
                } else {
                    parent->right = current->right; 
                }
                delete current; // delete operator to get rid of node
            }
            else if (current->left == NULL) { // checks for no left child
                if (current == root) { //if theres no left child, checks if current is root
                    root = current->right;  // if yes, then it sets root to the right child of current node --> new root
                } else if (is_left_child) { //checks if left child
                    parent->left = current->right; //then sets left child of parent to right of current
                } else {
                    parent->right = current->right; 
                }
                delete current; // delete operator to get rid of node
            }
            // Case 3: If the node has two children, find nodes successor (node with smallest val) and replace it with successor
            else {
                Node* successor_parent = current; // initializes two pointers, one to current (node to be deleted) and its right child
                Node* successor = current->right;
                while (successor->left != NULL) { //travseres left children of the right child until it reaches smallest value
                    successor_parent = successor;
                    successor = successor->left;
             }
                if (successor != current->right) { // successor is not the node to be deleted right child
                    successor_parent->left = successor->right; //checks successors right subtree
                    successor->right = current->right;
                }
                if (current == root) { // checks if current is root
                    root = successor; // will replace node to be deleted with successor
                } else if (is_left_child) { //otherwise if root isnt successor, update nodes parent node to successor
                    parent->left = successor;
                } else {
                    parent->right = successor;
                    }
                successor->left = current->left; //updates successors left to current left so it is deleted
                delete current; //deletes node
            }
            cout << "The book " << t << " is deleted from the library." << endl;
            return true; //returns true if deletion was successful
        }

        void range(float a, float b, Node* root){
            //Additional function 1
            if (root == nullptr){//if there is no book in the library, return nothing
                return;
            }
            Node* curr = root;//create a new Node that points to the root
            range(a,b, curr -> left);//recusive function for the left side of the tree
            if (curr -> data -> getRating() >= a && curr -> data -> getRating() <= b){ // check if the current book has the rating in the range of rating
                cout << curr -> data -> getTitle() << " " << curr -> data -> getRating() << endl;//print out the title and the rating
            }
            range(a,b, curr -> right);//recursive function for the right side of the tree
        }

        void displayOrdered(Node* r){//Display the books in alphabetical order
            //Fay
            if (r == nullptr) return; //if the root is null, return nothing
            displayOrdered(r -> left);//recursive function on the left side of the root
            cout << endl;;
            Book a = *(r -> data);//get the book data from the current node
            cout << endl;
            a.displayBook();//print out the book
            displayOrdered(r -> right);//recurive function on the right side of the root
            //since we us inorder traversal, the title is printed out in the alphabetical order
            return;
        }

        void certain_year(Node* temp,int y){ //creating a temporary node and using the y value as the wanted year
            if (temp == nullptr) return; //checking to see if there are any books/nodes in the tree or not 
            //traversing through the tree recursively looking at the left side as long as the value is not null
                certain_year(temp->left,y);
            if(temp -> data -> getYear()==y){  //accessing the year by going through the data of the book and calling on the get year function and seeing if it is equal to the wanted year or not
                    temp->data->displayBook(); //if the year of the book is equal to the wanted year then this line prints the book and its attributes    
                    cout << endl;
            }
            //traversing through the tree recursively looking at the right side as long as the value is not null
                certain_year(temp->right,y);
        }

        void deleteBooks(Node* r) {
                    if (r == nullptr) {
                        return;
                    }

                    // Recursively delete books in the left and right subtrees
                    deleteBooks(r->left);
                    deleteBooks(r->right);

                    // Delete the Book object stored in the node
                    delete r -> data;


                    // Delete the node
                    delete r;
            }

};

int main(){
    int T = 0;//number of the selection of the menu
    string title, author, ISBN;
    float rating;
    int noOfCopies, year;
    Library l;

    while (1){
        cout << "___ LIBRARY MANAGEMENT SYSTEM MENU ___\n1.Add a book\n2.Add a database of book (use .csv file)\n3.Delete a book\n4.Search for a book\n5.Dislay book in sorted order\n6.Rating range:\n7.Print out the book(s) published in a specific year\n8.Exit the library system\nChoose an option: ";
        string input;
        getline(cin,input);
        try{
            T = stoi(input);
            switch(T){
                case 1:{
                    cout << "Input the title: ";//get title
                    getline(cin, title);
                    cout << "Input the author: ";//get author
                    getline(cin, author);
                    cout << "Input the ISBN: ";//get isbn
                    getline(cin, ISBN);
                    cout << "Input the number of copies: ";//get no. of copies
                    cin >> noOfCopies;
                    cout << "Input the rating: ";//get rating
                    cin >> rating;
                    cout << "Input the published year ";//get published year
                    cin >> year;
                    cin.ignore();
                    Book* newBook = new Book(title, author, noOfCopies, ISBN, rating, year);//creating a new book with the attributes from above
                    l.setRoot(l.addBook(l.getRoot(), newBook));
                    cout << "The book is added into the library." << endl; //print statement wehn addition of book into library is succesful
                    break;
                }
                
                case 2:{
                    ifstream f;//create an ifstream obj to read the file
                    string file;
                    cout << "Input the file name: ";
                    getline(cin, file);
                    f.open(file);//read the file books.csv
                    if (f.is_open()) {
                        string line;
                        getline(f, line); // Skip the first line

                        while (getline(f, line)) {
                            char* strToSplit = strdup(line.c_str()); // Convert string to C-style string

                            char* items = strtok(strToSplit, ",");
                            int count = 0;

                            while (items != nullptr) {
                                if (count == 0) {
                                    title = items;
                                } else if (count == 1) {
                                    author = items;
                                } else if (count == 6) {
                                    ISBN = items;
                                } else if (count == 5) {
                                    noOfCopies = atoi(items); // Convert C-style string to int
                                }
                                else if (count == 3){
                                    rating = atof(items);
                                }
                                else if (count == 2){
                                    year = atoi(items);
                                }
                                items = strtok(nullptr, ",");                         
                                count++;
                            }

                            // Create a new Book object and add it to the library
                            Book* newBook = new Book(title, author, noOfCopies, ISBN,rating, year);
                            l.setRoot(l.addBook(l.getRoot(), newBook));

                            free(strToSplit); // Free the dynamically allocated memory
                    }

                    f.close(); // Close the file
                    } 
                    else {
                        cout << "Failed to open the file." << endl;
                    }
                    cout << endl;
                    break;
                }

                case 3:{
                    string t;
                    cout << "Input the title:";//input the title you want to remove
                    getline(cin,t);
                    cout << endl;
                    l.remove(t);
                    cout << endl;
                    break;
                }

                case 4:{
                    string t;
                    cout << "Input the title:";//input the title you want to search
                    getline(cin,t);
                    cout << endl;
                    l.search(t);
                    break;
                }
                
                case 5:{
                    cout << "Books displayed in alphabetical order:\n";
                    l.displayOrdered(l.getRoot());//display everybook in alphabetical order
                    cout << endl << endl;
                    break;
                }

                case 6:{
                    float low, high;
                    cout << "Input the lowest rating you want:" << endl;//input the lowerbound of the range
                    cin >> low;
                    cin.ignore(); // Clear the newline character from the input buffer
                    cout << "Input the highest rating you want:" << endl;//input the upperbound of the range
                    cin >> high;
                    cin.ignore(); // Clear the newline character from the input buffer
                    cout << endl << "The books that are in the rating range from " << low << " to " << high << ": " << endl;
                    cout << endl;
                    l.range(low,high,l.getRoot());//print out every book that has the rating in the range in alphabetical order
                    cout << endl << endl;
                    break;
                }

                case 7:{
                  int year; //creating a variable to hold the year wanted from the user
                    cout <<"input wanted year to see books from:" <<endl; //asking for the input for the wanted year from the user
                    cin>>year; //putting the wanted value for year into the variable for year
                    cin.ignore();
                    cout << endl;
                    l.certain_year(l.getRoot(),year); //calling the function for certain year with the root of the tree and the wanted year value 
                    break;
                }

                case 8:{
                    cout << "Thank you for using our system! Hope you have a great day!" << endl;
                    l.deleteBooks(l.getRoot());//delete every book
                    exit(10);
                    break; 

                }

                default:{
                    continue;
                    break;
                }
                    
            }
        }catch (const std::invalid_argument& e) {
            cerr << "\nError: Invalid input. Please enter a valid option." << endl;
            // Handle the error condition (e.g., display an error message, ask for input again)
        } catch (const std::out_of_range& e) {
            cerr << "\nError: Input out of range. Please enter a valid option." << endl;
            // Handle the error condition (e.g., display an error message, ask for input again)
        }
    }
    return 0;

}



