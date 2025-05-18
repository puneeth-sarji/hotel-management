#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstdlib>
using namespace std;

class hotel {
    int room_no;
    char name[30];
    char address[50];
    char phone[10];

public:
    void main_menu();
    void add();
    void display();
    void rooms();
    void edit();
    int check(int);
    void modify(int);
    void delete_rec(int);
    void bill(int);
};

// MAIN MENU
void hotel::main_menu() {
    int choice = 0;
    while (choice != 5) {
        system("cls");
        cout << "\n\t\t\t\t**************************";
        cout << "\n\t\t\t\t SIMPLE HOTEL MANAGEMENT ";
        cout << "\n\t\t\t\t * MAIN MENU *";
        cout << "\n\t\t\t\t**************************";
        cout << "\n\n\n\t\t\t1. Book A Room";
        cout << "\n\t\t\t2. Customer Records";
        cout << "\n\t\t\t3. Rooms Allotted";
        cout << "\n\t\t\t4. Edit Record";
        cout << "\n\t\t\t5. Exit";
        cout << "\n\n\t\t\tEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: add(); break;
            case 2: display(); break;
            case 3: rooms(); break;
            case 4: edit(); break;
            case 5: break;
            default:
                cout << "\n\n\t\t\tWrong choice.....!!!";
                cout << "\n\t\t\tPress any key to continue....!!";
                getch();
        }
    }
}

// BOOK A ROOM
void hotel::add() {
    system("cls");
    int r, flag;
    ofstream fout("Record.dat", ios::app);
    cout << "\n Enter Customer Details";
    cout << "\n -----------------------";
    cout << "\n\n Room no: ";
    cout << "\n Total no. of Rooms - 50";
    cout << "\n Ordinary Rooms from 1 - 30";
    cout << "\n Luxury Rooms from 31 - 45";
    cout << "\n Royal Rooms from 46 - 50";
    cout << "\n Enter The Room no. you want to stay in: ";
    cin >> r;

    flag = check(r);
    if (flag)
        cout << "\n Sorry..!!! Room is already booked";
    else {
        room_no = r;
        cout << " Name: ";
        cin >> name;
        cout << " Address: ";
        cin >> address;
        cout << " Phone No: ";
        cin >> phone;
        fout.write((char*)this, sizeof(hotel));
        cout << "\n Room is booked...!!!";
    }

    cout << "\n Press any key to continue.....!!";
    getch();
    fout.close();
}

// DISPLAY CUSTOMER RECORD
void hotel::display() {
    system("cls");
    ifstream fin("Record.dat", ios::in);
    int r, flag = 0;
    cout << "\n Enter room No. for customer details: ";
    cin >> r;

    while (fin.read((char*)this, sizeof(hotel))) {
        if (room_no == r) {
            system("cls");
            cout << "\n Customer Details";
            cout << "\n -----------------";
            cout << "\n Room no: " << room_no;
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone no: " << phone;
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        cout << "\n Sorry, Room no. not found or vacant....!!";

    cout << "\n\n Press any key to continue....!!";
    getch();
    fin.close();
}

// DISPLAY ALL ROOMS
void hotel::rooms() {
    system("cls");
    ifstream fin("Record.dat", ios::in);
    cout << "\n\t\t\t List Of Rooms Allotted";
    cout << "\n\t\t\t -----------------------";
    cout << "\n\n Room No.\tName\t\tAddress\t\t\t\tPhone No.\n";

    while (fin.read((char*)this, sizeof(hotel))) {
        cout << "\n " << room_no << "\t\t" << name << "\t\t" << address << "\t\t" << phone;
    }

    cout << "\n\n\n\t\t\tPress any key to continue.....!!";
    getch();
    fin.close();
}

// EDIT MENU
void hotel::edit() {
    system("cls");
    int choice, r;
    cout << "\n EDIT MENU";
    cout << "\n ----------";
    cout << "\n 1. Modify Customer Record";
    cout << "\n 2. Delete Customer Record";
    cout << "\n 3. Bill Of Customer";
    cout << "\n Enter your choice: ";
    cin >> choice;
    cout << "\n Enter room no: ";
    cin >> r;

    switch (choice) {
        case 1: modify(r); break;
        case 2: delete_rec(r); break;
        case 3: bill(r); break;
        default: cout << "\n Wrong Choice.....!!";
    }

    cout << "\n Press any key to continue....!!!";
    getch();
}

// CHECK ROOM STATUS
int hotel::check(int r) {
    int flag = 0;
    ifstream fin("Record.dat", ios::in);
    while (fin.read((char*)this, sizeof(hotel))) {
        if (room_no == r) {
            flag = 1;
            break;
        }
    }
    fin.close();
    return flag;
}

// MODIFY RECORD
void hotel::modify(int r) {
    long pos;
    int flag = 0;
    fstream file("Record.dat", ios::in | ios::out | ios::binary);
    while (file.read((char*)this, sizeof(hotel))) {
        pos = file.tellg();
        if (room_no == r) {
            cout << "\n Enter New Details";
            cout << "\n ------------------";
            cout << " Name: ";
            cin >> name;
            cout << " Address: ";
            cin >> address;
            cout << " Phone no: ";
            cin >> phone;
            file.seekg(pos - sizeof(hotel));
            file.write((char*)this, sizeof(hotel));
            cout << "\n Record is modified....!!";
            flag = 1;
            break;
        }
    }

    if (flag == 0)
        cout << "\n Sorry Room No. not found or vacant...!!";

    file.close();
}

// DELETE RECORD
void hotel::delete_rec(int r) {
    int flag = 0;
    char ch;
    ifstream fin("Record.dat", ios::in);
    ofstream fout("temp.dat", ios::out);

    while (fin.read((char*)this, sizeof(hotel))) {
        if (room_no == r) {
            cout << "\n Name: " << name;
            cout << "\n Address: " << address;
            cout << "\n Phone No: " << phone;
            cout << "\n\n Do you want to delete this record (y/n): ";
            cin >> ch;
            if (ch == 'n' || ch == 'N')
                fout.write((char*)this, sizeof(hotel));
            flag = 1;
        } else {
            fout.write((char*)this, sizeof(hotel));
        }
    }

    fin.close();
    fout.close();

    if (flag == 0)
        cout << "\n Sorry room No. not found or vacant...!!";
    else {
        remove("Record.dat");
        rename("temp.dat", "Record.dat");
    }
}

// BILLING
void hotel::bill(int r) {
    hotel h1;
    ifstream f1("Record.dat", ios::in | ios::binary);

    if (!f1)
        cout << "Cannot open file";
    else {
        int found = 0;
        while (f1.read((char*)&h1, sizeof(hotel))) {
            if (h1.room_no == r) {
                found = 1;
                if (r >= 1 && r <= 30)
                    cout << "Your bill = ₹2000";
                else if (r >= 31 && r <= 45)
                    cout << "Your bill = ₹5000";
                else if (r >= 46 && r <= 50)
                    cout << "Your bill = ₹7000";
                break;
            }
        }

        if (!found)
            cout << "Room no. not found";
    }

    f1.close();
    getch();
}

// MAIN FUNCTION
int main() {
    hotel h;
    system("cls");
    cout << "\n\t\t\t*****************************";
    cout << "\n\t\t\t* HOTEL MANAGEMENT PROJECT *";
    cout << "\n\t\t\t*****************************";
    cout << "\n\n\n\n\n\n\n\t\t\t\t\tPress any key to continue....!!";
    getch();
    h.main_menu();
    return 0;
}