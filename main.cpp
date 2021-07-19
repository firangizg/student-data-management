#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main() {
    char name[15];
    int no_of_students = 0, option = 0, count_data = 0;
    string empty = "00";
    string proctor = "";
    // open the file that stores all the data
    ifstream file("Data.txt");
    string line;

    // counts the total lines in Data.txt
    for (int i = 0; std::getline(file, line); i++) {
        count_data++;
    }

    // while the user does not want to exit, execute these 
    while (option != 6) {
        cout << "\nChoose one of the operations: \n1. Add new students\n";
        cout << "2. Student login\n3. Faculty login\n4. Proctor login\n5. Admin view\n6. Exit";
        cout << "\nEnter option: ";
        cin >> option;

        // add new students
        if (option == 1) {
            cout << "Enter the number of students: ";
            cin >> no_of_students;
        
            count_data += no_of_students;

            for (int i = 0; i < no_of_students; i++) {
                ofstream outfile;
                outfile.open("Data.txt", ios::app);
                cout << "Enter your registration number: ";
                cin >> name;
                outfile << name << "\t";

                cout << "Enter your name: ";
                cin >> name;
                int len = strlen(name);
                
                while (len < 15) {
                    name[len] = ' ';
                    len += 1;
                }
                outfile << name << "\t";

                outfile << empty << "\t";
                outfile << empty << "\t";

                cout << "Enter your proctor ID: ";
                cin >> proctor;

                outfile << proctor << endl;
            }
        }

        // Student Login
        else if (option == 2) {
            char registr_no[9];
            cout << "Enter your registration number: ";
            cin >> registr_no;
            ifstream infile;
            int check = 0;
            infile.open("Data.txt", ios::in);
            
            while (infile >> name) {
                if (strcmp(name, registr_no) == 0) {
                    cout << "\nRegistration number: " << name << endl;
                    infile >> name;
                    cout << "Name: " << name << endl;
                     
                    infile >> name;
                    cout << "EECS168 mark: " << name << endl;

                    infile >> name;
                    cout << "EECS140 mark: " << name << endl;

                    infile >> name;
                    cout << "Proctor ID: " << name << endl; 

                    infile.close();
                    check = 1;
                }
            }

            if (check == 0) {
                cout << "No such registration number found!" << endl;
            }
        }

        // Faculty Login
        else if (option == 3) {
            char subcode[7];
            cout << "Enter your class name: ";
            cin >> subcode;
            string code1 = "EECS168", code2 = "EECS140", mark = "";
            ifstream infile;
            int check = 0;

            cout <<"\nChoose an operation: \n1. Add data \n2. View data\nEnter your choice: ";
            cin >> option;

            if (option == 1) {
                cout << "Warning, you need to add marks for all the students!" << endl;
                
                for (int i = 0; i < count_data; i++) {
                    fstream file("Data.txt");
                    if (strcmp(subcode, code1.c_str()) == 0) {
                        file.seekp(26 + 37*i, std::ios_base::beg);
                        cout << "Enter the mark of student#" << (i+1) << " : ";
                        cin >> mark;
                        file.write(mark.c_str(), 2);
                    }

                    if (strcmp(subcode, code2.c_str()) == 0) {
                        file.seekp(29 + 37*i, std::ios_base::beg);
                        cout << "Enter the mark of student#" << (i+1) << " : ";
                        cin >> mark;
                        file.write(mark.c_str(),2);
                    }
                }
            }

            else if (option == 2) {
                infile.open("Data.txt", ios::in);
                if (strcmp(subcode, code1.c_str()) == 0) {
                    cout << "Registration number - Marks\n" << endl;
                    while (infile >> name) {
                        cout << name;
                        infile >> name;
                        infile >> name;
                        cout << " - " << name << endl;
                        infile >> name;
                        infile >> name; 
                        check = 1;
                    }
                }

                infile.close();
                infile.open("Data.txt", ios::in);

                if (strcmp(subcode, code2.c_str()) == 0) {
                    cout << "Registration number - Marks\n" << endl;
                    while (infile >> name) {
                        cout << name; 
                        infile >> name; 
                        infile >> name;
                        cout << " - " << name << endl;
                        infile >> name;
                        check = 1;
                    }
                }
            }

            infile.close();
            if (check == 0) {
                cout << "No such subject code was found." << endl;
            }
        }

        // Proctor Login
        
        else if (option == 4) {
            char proctor_id[7];
            cout << "Enter proctor ID: ";
            cin >> proctor_id;
            int check = 0;
            char temp1[100], temp2[100], temp3[100];
            char temp4[100], id[100];
            ifstream infile;
            infile.open("Data.txt", ios::in);

            while (infile >> temp1) {
                infile >> temp2;
                infile >> temp3;
                infile >> temp4;
                infile >> id;

                if (strcmp(id, proctor_id) == 0) {
                    cout <<"\nRegistration number: " << temp1 << endl;
                    cout <<"Name: " << temp2 << endl;
                    cout <<"EECS168 mark: " << temp3 << endl;
                    cout <<"EECS140 mark: " << temp4 << endl;
                    check = 1; 
                }
            }
            if (check == 0) {
                cout << "No such proctor ID found\n";
            }
        }

        // Admin View
        else if (option == 5) {
            char password[25];
            cout << "Enter admin password: ";
            cin >> password;
            string admin_pass = "admin";
            if (strcmp(password, admin_pass.c_str()) == 0) {
                // Print out the data 
                cout << "Regstr. No     "
                        "\tName\tEECS168\tEECS140\tProctor "
                        "ID"
                    << endl; 
                ifstream infile;
                infile.open("Data.txt", ios::in);
                char name[20];

                while (infile >> name) {
                    cout << name << "\t";
                    infile >> name;
                    cout << name << "\t";
                    infile >> name;
                    cout << name << "\t";
                    infile >> name;
                    cout << name << "\t";
                    infile >> name;
                    cout << name << endl;
                }
            }

        }
    }

}