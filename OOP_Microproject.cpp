#include <iostream>
#include <fstream>
#include <conio.h>
#include <time.h>
using namespace std;

void heading();
void delay(int milliseconds);

class Attendance
{
    ifstream fin;
    ofstream fout;
    string sheetfile, sourcefile;
    int total;
    const string p = "P", a = "A";

public:
    void create_sheet()
    {
        heading();
        cout << "Enter file name of the attendance sheet -> ";
        cin >> sheetfile;
        cout << endl
             << "Enter file name (.csv) to import students roll no.s and names -> ";
        cin >> sourcefile;

        // Fetching total students into the source file
        total = fetch_total_students_from_file(sourcefile);

        // Fetching student details from source file...
        string rollno[total], name[total];
        fetch_student_details_from_file(sourcefile, total, rollno, name);

        // Fetching data into attendance sheet...
        fout.open(sheetfile + ".csv");
        fout << "Roll No.,Name of Student" << endl;
        for (int i = 0; i < total; i++)
        {
            fout << rollno[i] << "," << name[i] << endl;
        }
        fout.close();
        cout << endl
             << "Fetching data from file into the attendance sheet";
        for (int i = 0; i < 3; i++)
        {
            delay(700);
            cout << ".";
        }
        delay(500);
        heading();
        cout << "Successfully fetched the student details into " << sheetfile << ".csv file..." << endl;
        getch();
    }

    void fetch_student_details_from_file(string filename, int total, string *rollno, string *name)
    {
        fin.open(filename + ".csv");
        for (int i = 0, j = 0; fin.good(); i++)
        {
            string line;
            if (i % 2 == 0)
            {
                getline(fin, line, ',');
                rollno[j] = line;
            }
            else
            {
                getline(fin, line, '\n');
                name[j] = line;
                j++;
            }
        }
        fin.close();
    }

    int fetch_total_students_from_file(string filename)
    {
        int total = 0;
        fin.open(filename + ".csv");
        while (fin.good())
        {
            string line;
            getline(fin, line, '\n');
            total++;
        }
        fin.close();
        return total;
    }

    void add_attendance()
    {
        int total2, choice2;
        string date, presentrolls_filename;
        delay(500);
        heading();
        cout << "Enter file name of the attendance sheet -> ";
        cin >> sheetfile;
        cout << endl
             << "Enter date of attendance -> ";
        cin >> date;
        cout << endl
             << "Enter 1 -> To input present students roll no.s" << endl;
        cout << "Enter 2 -> To input absent students roll no.s" << endl;
        cout << endl
             << "Enter your choice -> ";
        cin >> choice2;
        if (choice2 == 1)
        {
            cout << endl
                 << "Enter file name which contains present students roll no.s -> ";
            cin >> presentrolls_filename;

            total = fetch_total_students_from_file(sheetfile);
            total2 = fetch_total_students_from_file(presentrolls_filename);

            // Fetching roll no.s and names from sheet
            string rollno[total], name[total];
            fetch_student_details_from_file(sheetfile, total, rollno, name);

            // Fetching data from present rollnos file
            string presentrolls[total2];
            fin.open(presentrolls_filename + ".csv");
            for (int i = 0; i < total2; i++)
            {
                getline(fin, presentrolls[i]);
            }
            fin.close();

            string filedata[total];
            fin.open(sheetfile + ".csv");
            for (int i = 0; i < total; i++)
            {
                getline(fin, filedata[i]);
            }
            fin.close();

            fout.open(sheetfile + ".csv");
            for (int i = 0; i < total; i++)
            {
                if (filedata[i].length() == 0)
                    break;
                else
                {
                    if (i == 0)
                        fout << filedata[i] << "," << date << endl;
                    else
                    {
                        int flag = -1;
                        for (int k = 0; k < total2; k++)
                        {
                            if (rollno[i].compare(presentrolls[k]) == 0)
                            {
                                flag = 1;
                                break;
                            }
                            else
                            {
                                flag = 0;
                            }
                        }
                        if (flag == 0)
                            fout << filedata[i] << "," << a << endl;
                        else if (flag == 1)
                            fout << filedata[i] << "," << p << endl;
                        else
                            fout << filedata[i] << endl;
                    }
                }
            }
            fout.close();
        }
        else if (choice2 == 2)
        {
            cout << endl
                 << "Enter file name which contains absent students roll no.s -> ";
            cin >> presentrolls_filename;

            total = fetch_total_students_from_file(sheetfile);
            total2 = fetch_total_students_from_file(presentrolls_filename);

            // Fetching roll no.s and names from sheet
            string rollno[total], name[total];
            fetch_student_details_from_file(sheetfile, total, rollno, name);

            // Fetching data from present rollnos file
            string presentrolls[total2];
            fin.open(presentrolls_filename + ".csv");
            for (int i = 0; i < total2; i++)
            {
                getline(fin, presentrolls[i]);
            }
            fin.close();

            string filedata[total];
            fin.open(sheetfile + ".csv");
            for (int i = 0; i < total; i++)
            {
                getline(fin, filedata[i]);
            }
            fin.close();

            fout.open(sheetfile + ".csv");
            for (int i = 0; i < total; i++)
            {
                if (filedata[i].length() == 0)
                    break;
                else
                {
                    if (i == 0)
                        fout << filedata[i] << "," << date << endl;
                    else
                    {
                        int flag = -1;
                        for (int k = 0; k < total2; k++)
                        {
                            if (rollno[i].compare(presentrolls[k]) == 0)
                            {
                                flag = 1;
                                break;
                            }
                            else
                            {
                                flag = 0;
                            }
                        }
                        if (flag == 0)
                            fout << filedata[i] << "," << p << endl;
                        else if (flag == 1)
                            fout << filedata[i] << "," << a << endl;
                        else
                            fout << filedata[i] << endl;
                    }
                }
            }
            fout.close();
        }
        else
        {
            cout << endl
                 << "Invalid choice..." << endl
                 << "Enter again..." << endl;
        }
        cout << endl
             << "Marking attendance";
        for (int i = 0; i < 3; i++)
        {
            delay(700);
            cout << ".";
        }
        delay(500);
        heading();
        cout << "Successfully marked attendance of " << date << " into " << sheetfile << ".csv file..." << endl;
        getch();
    }
};

int main()
{
    int choice;
    Attendance a;
    do
    {
        heading();
        cout << "1 -> Create new attendance sheet" << endl;
        cout << "2 -> Add attendance" << endl;
        cout << "3 -> Exit" << endl
             << endl;
        cout << "Enter your choice -> ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            a.create_sheet();
            break;
        case 2:
            a.add_attendance();
            break;
        case 3:
            cout << endl
                 << "Thank you..." << endl;
            getch();
            exit(0);
        default:
            cout << endl
                 << "Invalid choice..." << endl
                 << "Enter again..." << endl;
            getch();
        }
    } while (1);
    return 0;
}

void heading()
{
    system("cls");
    cout << "****** STUDENT ATTENDANCE MANAGEMENT SYSTEM ******" << endl;
    cout << "--------------------------------------------------" << endl
         << endl;
}

void delay(int milliseconds)
{
    clock_t start_time = clock();
    while (clock() < start_time + milliseconds)
        ;
}