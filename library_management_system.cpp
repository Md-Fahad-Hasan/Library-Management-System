#include <iostream>
#include <iomanip>
#include <string.h>
#include <fstream>
using namespace std;

class Library
{
    int BookId;
    char Title[20];
    char Author[20];
    char Category[20];
    int Pages;
    float Eddition;

public:
    int getID()
    {
        return BookId;
    }
    char *getTitle() { return Title; }
    char *getAuthor() { return Author; }
    char *getCategory() { return Category; }
    float getEddition() { return Eddition; }

    Library()
    {
        BookId = 0;
        strcpy(Title, "");
        strcpy(Author, "");
        strcpy(Category, "");
        Pages = 0;
        Eddition = 0.0;
    }

    void getBook();
    void listView();
    void showBook();
    void header();
};

void Library::getBook()
{
    cout << "\tEnter Book Id                 : ";
    cin >> BookId;
    cout << "\tEnter Book Title              : ";
    cin.get();
    cin.getline(Title, 20);
    cout << "\tEnter Book Author             : ";
    cin.getline(Author, 20);
    cout << "\tEnter Book Category           : ";
    cin.getline(Category, 20);
    cout << "\tEnter Number of Pages         : ";
    cin >> Pages;
    cout << "\tEnter date of Edition of Book :";
    cin >> Eddition;
    cout << endl;
}

void Library::showBook()
{
    cout << endl;
    cout << "Book ID         : " << BookId << endl;
    cout << "Book Title      : " << Title << endl;
    cout << "Author Name     : " << Author << endl;
    cout << "Category        : " << Category << endl;
    cout << "No. of Pages    : " << Pages << endl;
    cout << "Edition         : " << Eddition << endl;
}

void Library::header()
{
    cout.setf(ios::left);
    cout << setw(10) << "ID"
         << setw(20) << "Book Title"
         << setw(20) << "Book Author"
         << setw(15) << "Category"
         << setw(10) << "Pages"
         << setw(5) << "Edition" << endl;
    for (int i = 1; i <= 84; i++)
    {
        cout << "=";
    }
    cout << endl;
}

void Library::listView()
{
    cout.setf(ios::left);
    cout << setw(10) << BookId
         << setw(20) << Title
         << setw(20) << Author
         << setw(15) << Category
         << setw(10) << Pages
         << setw(5) << Eddition << endl;
}

void addBook();
void displayBooks();
void searchByID();
void searchByTitle();
void searchByCategory();
void searchByAuthor();
void dispose();
void modify();
void displayDisposed();
void drawline(char);
void heading();
void menu();
void searchMenu();

void drawline(char ch)
{
    for (int i = 1; i < 85; i++)
    {
        cout << ch;
    }
    cout << endl;
}

void heading()
{
    drawline('+');
    cout << "\t\tL I B R A R Y  M A N A G E M E N T  S Y S T E M\n";
    drawline('+');
}

void addBook()
{
    Library l;
    ofstream fout;
    fout.open("books.txt", ios::app);
    l.getBook();
    fout.write((char *)&l, sizeof(l));
    cout << "Book data saved in file...\n";
    fout.close();
}

void displayBooks()
{
    ifstream fin("books.txt");
    int rec = 0;
    Library l;
    while (fin.read((char *)&l, sizeof(l)))
    {
        if (rec < 1)
            l.header();
        l.listView();
        rec++;
    }
    fin.close();
    cout << "\nTotal " << rec << " Records in file...\n";
}

void searchByID()
{
    int n, flag = 0;
    Library l;
    ifstream fin("books.txt");
    cout << "Enter Book ID : ";
    cin >> n;
    while (fin.read((char *)&l, sizeof(l)))
    {
        if (n == l.getID())
        {
            l.showBook();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
    {
        cout << "Book Number with ID : " << n << " not available...\n";
    }
}

void searchByTitle()
{
    int flag = 0;
    char title[20];
    Library l;
    ifstream fin("books.txt");
    cout << "Enter Book Title : ";
    cin.ignore();
    cin.getline(title, 20);
    while (fin.read((char *)&l, sizeof(l)))
    {
        if (strcmpi(title, l.getTitle()) == 0)
        {
            l.showBook();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with Title : " << title << " not available...\n";
}

void searchByCategory()
{
    int flag = 0;
    char cat[20];
    Library l;
    ifstream fin("books.txt");
    cout << "Enter Book Category : ";
    cin.ignore();
    cin.getline(cat, 20);
    while (fin.read((char *)&l, sizeof(l)))
    {
        if (strcmpi(cat, l.getCategory()) == 0)
        {
            l.showBook();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with Category : " << cat << " not available...\n";
}

void searchByAuthor()
{
    int flag = 0;
    char aut[20];
    Library l;
    ifstream fin("books.txt");
    cout << "Enter Book Author : ";
    cin.ignore();
    cin.getline(aut, 20);
    while (fin.read((char *)&l, sizeof(l)))
    {
        if (strcmpi(aut, l.getAuthor()) == 0)
        {
            l.showBook();
            flag++;
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with Author name : " << aut << " not available...\n";
}

void dispose()
{
    int n, flag = 0;
    Library l;
    ifstream fin("books.txt");
    ofstream fout("dispose.txt", ios::out);
    cout << "Enter Book ID to dispose: ";
    cin >> n;
    while (fin.read((char *)&l, sizeof(l)))
    {
        if (n == l.getID())
        {
            l.showBook();
            flag++;
        }
        else
        {
            fout.write((char *)&l, sizeof(l));
        }
    }
    fin.close();
    fout.close();
    if (flag == 0)
        cout << "Book with ID : " << n << " not available...\n";
}

void modify()
{
    int n, flag = 0, pos;
    Library l;
    fstream fin("books.txt", ios::in | ios::out);
    cout << "Enter Book ID to modify: ";
    cin >> n;
    while (fin.read((char *)&l, sizeof(l)))
    {
        if (n == l.getID())
        {
            pos = fin.tellg();
            cout << "Following data will be edited...\n";
            l.showBook();
            flag++;
            fin.seekg(pos - sizeof(l));
            l.getBook();
            fin.write((char *)&l, sizeof(l));
            cout << "\nData Modified successfully...\n";
        }
    }
    fin.close();
    if (flag == 0)
        cout << "Book with ID : " << n << " not available...\n";
}

void displayDisposed()
{
    ifstream fin("dispose.txt");
    int rec = 0;
    Library l;
    while (fin.read((char *)&l, sizeof(l)))
    {
        if (rec < 1)
            l.header();
        l.listView();
        rec++;
    }
    fin.close();
    cout << "\nTotal " << rec << " Records in disposed off file...\n";
}

void menu()
{
    int ch;
    do
    {
        system("cls");
        heading();
        cout << "0. EXIT.\n";
        cout << "1. Add New Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Books\n";
        cout << "4. Dispose a Book\n";
        cout << "5. Modify Book Details\n";
        cout << "6. List of Disposed Books\n";
        cout << "Enter Your Choice : ";
        cin >> ch;
        system("cls");
        heading();
        switch (ch)
        {
        case 1:
            addBook();
            break;
        case 2:
            displayBooks();
            break;
        case 3:
            searchMenu();
            break;
        case 4:
            dispose();
            break;
        case 5:
            modify();
            break;
        case 6:
            displayDisposed();
            break;
        }
        system("pause");
    } while (ch != 0);
}

void searchMenu()
{
    int ch;
    do
    {
        system("cls");
        heading();
        cout << "BOOK SEARCH OPTIONS\n";
        cout << "0. Back\n";
        cout << "1. By ID\n";
        cout << "2. By Title\n";
        cout << "3. By Category\n";
        cout << "4. By Author\n";
        cout << "Enter Your Choice : ";
        cin >> ch;
        system("cls");
        heading();
        switch (ch)
        {
        case 1:
            searchByID();
            break;
        case 2:
            searchByTitle();
            break;
        case 3:
            searchByCategory();
            break;
        case 4:
            searchByAuthor();
            break;
        default:
            cout << "\a";
        }
        system("pause");
    } while (ch != 0);
}

int main()
{
    menu();
    return 0;
}
