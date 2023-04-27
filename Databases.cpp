#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<Windows.h>
#include <limits>



using namespace std;

//��������� ��� ����
struct Date {
    int day;
    int month;
    int year;
};

//��������� ��� ���������� � �������
struct Zach {
    int num; //���������� ������� �������
    Date dates[10]; //���� ����� �������
};

//��������� ��� ���������� �� ���������
struct Exam {
    int num; //���������� ������� ���������
    int marks[5]; //������ �� ���������
    Date dates[10]; //���� ����� ���������
};

//��������� ��� ���������� � ���������
struct Students {
    string surname; //�������
    string name; //���
    string patronymic; //��������
    Date birthDate; //���� ��������
    Zach tests; //���������� � �������
    Exam exams; //���������� �� ���������
};

//������ ���������� �� ��������� � ���������
Students* students[20];

bool isDateValid(Date* date) {
    if (date->month > 12 or date->month <= 0) return false; //month
    if (date->day > 31 or date->day <= 0) return false; //day
    if (date->day == 31 and (date->month == 4 or date->month == 6 or date->month == 9 or date->month == 11)) return false; //30 days in Apr, Jun, Sen, Nov
    if ((date->month == 2) and (date->day > 29))  return false; //February
    return true;
}



//������� ���������� ������ ��������
void addStudent() {
    //���������� ������ ������ � ������� ���������� �� ��������� � ���������
    for (int i = 0; i < 20; i++) {
        if (students[i] == nullptr) {
            students[i] = new Students;
            //������ ���������� � ��������
            cout << "������� �������: ";
            cin >> students[i]->surname;
            cout << "������� ���: ";
            cin >> students[i]->name;
            cout << "������� ��������: ";
            cin >> students[i]->patronymic;
            cout << "������� ���� �������� (���� ����� ��� (23)): ";
            cin >> students[i]->birthDate.day >> students[i]->birthDate.month >> students[i]->birthDate.year;
            while (cin.fail() or !isDateValid(&students[i]->birthDate))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "������ � ������ ����. ��������� �������. �������  ���������� ���� �������� (���� ����� ��� (23)): ";
                cin >> students[i]->birthDate.day >> students[i]->birthDate.month >> students[i]->birthDate.year;
            }


            cout << "������� ���������� ������� ������� (�������� - 10): ";
            cin >> students[i]->tests.num; // ���������� �������
            while (cin.fail() or students[i]->tests.num > 10 or students[i]->tests.num < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "������ � ���������� �������. ��������� �������. ������� ���������� ����� �������: ";
                cin >> students[i]->tests.num;
            }

            for (int j = 0; j < students[i]->tests.num; j++)
            {
                cout << "������� ���� ������ (���� ����� ��� (23)): ";
                cin >> students[i]->tests.dates[j].day >> students[i]->tests.dates[j].month >> students[i]->tests.dates[j].year;
                while (cin.fail() or !isDateValid(&students[i]->tests.dates[j]))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "������ � ������ ����. ��������� �������. ������� ���������� ���� ������ (���� ����� ��� (23)): ";
                    cin >> students[i]->tests.dates[j].day >> students[i]->tests.dates[j].month >> students[i]->tests.dates[j].year;
                }

            }
            cout << "������� ���������� ������� ��������� (�������� - 5): ";
            cin >> students[i]->exams.num; // ���������� ���������
            
            while (cin.fail() or students[i]->exams.num > 5 or students[i]->exams.num < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "������ � ���������� ���������. ��������� �������. ������� ���������� ����� ���������: ";
                cin >> students[i]->exams.num;
            }

            for (int j = 0; j < students[i]->exams.num; j++)
            {
                cout << "������� ���� �������� (���� ����� ��� (23)): ";
                cin >> students[i]->exams.dates[j].day >> students[i]->exams.dates[j].month >> students[i]->exams.dates[j].year;
                while (cin.fail() or !isDateValid(&students[i]->exams.dates[j]))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "������ � ������ ����. ��������� �������. �������  ���������� ���� �������� (���� ����� ��� (23)): ";
                    cin >> students[i]->exams.dates[j].day >> students[i]->exams.dates[j].month >> students[i]->exams.dates[j].year;
                }
                cout << "������� ������ �� ���� ������� (3-5): ";
                cin >> students[i]->exams.marks[j];
                while (cin.fail() or students[i]->exams.marks[j] > 5 or students[i]->exams.marks[j] < 3)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "������ � ������ ������. ��������� �������. �������  ���������� ������ (3-5)): ";
                    cin >> students[i]->exams.marks[j];
                }
            }
            cout << endl << "������� ������� ��������!" << endl << endl;
            return;
        }
    }
    cout << endl << "� ������ ��� ��������� ����!" << endl << endl;
}

//������� ������ �������� �� �������

void findStudent() {
    string surname_search;
    string name_search;
    string patronymic_search;
    cout << "������� ������� ��������: ";
    cin >> surname_search;
    cout << "������� ��� ��������: ";
    cin >> name_search;
    cout << "������� �������� ��������: ";
    cin >> patronymic_search;

    for (int i = 0; i < 20; i++) {
        if (students[i] != nullptr) { //���������, ��� ������ � ������� �� ������
            if (students[i]->surname == surname_search and students[i]->name == name_search and students[i]->patronymic == patronymic_search) { //���� ���������, ������� ���������� � ��������

                cout << "�������: " << students[i]->surname << endl;
                cout << "���: " << students[i]->name << endl;
                cout << "��������: " << students[i]->patronymic << endl;
                cout << "���� ��������: " << students[i]->birthDate.day << "." << students[i]->birthDate.month << "." << students[i]->birthDate.year << endl;
                cout << "������� ������: " << students[i]->tests.num << endl;
                for (int j = 0; j < students[i]->tests.num; j++) {
                    cout << "���� ����� ������: " << j + 1 << ": " << students[i]->tests.dates[j].day << "." << students[i]->tests.dates[j].month << "." << students[i]->tests.dates[j].year << endl;
                }
                cout << "������� ��������: " << students[i]->exams.num << endl;
                for (int j = 0; j < students[i]->exams.num; j++) {
                    cout << "������ �� ��������: " << j + 1 << ": " << students[i]->exams.marks[j] << endl;
                    cout << "���� ����� ��������: " << j + 1 << ": " << students[i]->exams.dates[j].day << "." << students[i]->exams.dates[j].month << "." << students[i]->exams.dates[j].year << endl;
                }
                cout << endl;
                return;
            }
        }
    }
    cout << endl << "������� � ����� �������� �� ������!" << endl << endl;
}

//������� ���������� ������ � ����
void saveData() {
    ofstream outFile(".\\Students.txt", ios::trunc);  //ios::app
    if (outFile.is_open()) {
        //���������� ��� ������ � �������, ���� �� ������ ������ ������
        for (int i = 0; i < 20; i++) {
            if (students[i] != nullptr) {
                outFile << "�������: " << students[i]->surname << endl;
                outFile << "���: " << students[i]->name << endl;
                outFile << "��������: " << students[i]->patronymic << endl;
                outFile << "���� ��������: " << students[i]->birthDate.day << "." << students[i]->birthDate.month << "." << students[i]->birthDate.year << endl;

                outFile << endl;

                outFile << "���������� ������� ������� (�� 10): " << students[i]->tests.num << endl;
                for (int j = 0; j < students[i]->tests.num; j++) {
                    outFile << "����� #" << j + 1 << " " << "���� ����� ������: "
                        << students[i]->tests.dates[j].day << "."
                        << students[i]->tests.dates[j].month << "."
                        << students[i]->tests.dates[j].year << endl;
                }

                outFile << "���������� ������� ��������� (�� 5): " << students[i]->exams.num << endl;
                for (int j = 0; j < students[i]->exams.num; j++) {
                    outFile << "������� #" << j + 1 << " " << "���� ����� ��������: "
                        << students[i]->exams.dates[j].day << "."
                        << students[i]->exams.dates[j].month << "."
                        << students[i]->exams.dates[j].year << " " << endl;

                    outFile << "������ �� �������: "
                        << students[i]->exams.marks[j] << " " << endl;
                }
                outFile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                outFile << endl;
            }
        }
        outFile.close();
        cout << endl << "������ ������� ��������� � ����!" << endl << endl;
    }
    else {
        cout << endl << "������ �������� �����!" << endl << endl;
    }
}

//������� �������� ������ �� �����
void loadData() {
    ifstream inFile(".\\Students.txt");
    if (inFile.is_open()) {

        cout << inFile.rdbuf();

        inFile.close();
        cout << endl << "������ ������� ��������� �� �����!" << endl << endl;
    }
    else {
        cout << endl << "������ �������� �����!" << endl << endl;
    }
}

void redactorStudent() {

    string surname_search;
    string name_search;
    string patronymic_search;

    cout << "������� ������� ��������: ";   
    cin >> surname_search;
    cout << "������� ��� ��������: ";
    cin >> name_search;
    cout << "������� �������� ��������: ";
    cin >> patronymic_search;

    for (int i = 0; i < 20; i++) {
        if (students[i] != nullptr) { //���������, ��� ������ � ������� �� ������
            if (students[i]->surname == surname_search and students[i]->name == name_search and students[i]->patronymic == patronymic_search) { //���� ���������, ������� ���������� � ��������

                cout << "�������: " << students[i]->surname << endl;
                cout << "���: " << students[i]->name << endl;
                cout << "��������: " << students[i]->patronymic << endl;
                cout << "���� ��������: " << students[i]->birthDate.day << "." << students[i]->birthDate.month << "." << students[i]->birthDate.year << endl;
                cout << "������� ������: " << students[i]->tests.num << endl;
                for (int j = 0; j < students[i]->tests.num; j++) {
                    cout << "���� ����� ������: " << j + 1 << ": " << students[i]->tests.dates[j].day << "." << students[i]->tests.dates[j].month << "." << students[i]->tests.dates[j].year << endl;
                }
                cout << "������� ��������: " << students[i]->exams.num << endl;
                for (int j = 0; j < students[i]->exams.num; j++) {
                    cout << "������ �� ��������: " << j + 1 << ": " << students[i]->exams.marks[j] << endl;
                    cout << "���� ����� ��������: " << j + 1 << ": " << students[i]->exams.dates[j].day << "." << students[i]->exams.dates[j].month << "." << students[i]->exams.dates[j].year << endl;
                }

                cout << endl;

                cout << "������� ���������� �������: "; cin >> students[i]->surname;
                cout << "������� ���������� ���: "; cin >> students[i]->name;
                cout << "������� ���������� ��������: "; cin >> students[i]->patronymic;
                cout << "������� ���������� ���� �������� (���� ����� ��� (23)): ";
                cin >> students[i]->birthDate.day >> students[i]->birthDate.month >> students[i]->birthDate.year;
 
                 while (cin.fail() or !isDateValid(&students[i]->birthDate))
                 {
                    cout << "������ � ������ ����. ��������� �������. �������  ���������� ���� �������� (���� ����� ��� (23)): ";
                    cin >> students[i]->birthDate.day >> students[i]->birthDate.month >> students[i]->birthDate.year;
                 }

                cout << "������� ���������� ���������� ������� ������� (�������� - 10): ";
                cin >> students[i]->tests.num; // ���������� �������
                if (students[i]->tests.num > 10 or students[i]->tests.num < 0)
                {
                    while (students[i]->tests.num > 10 or students[i]->tests.num < 0)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "������ � ���������� �������. ��������� �������. ������� ���������� ����� �������: ";
                        cin >> students[i]->tests.num;
                    }

                }
                for (int j = 0; j < students[i]->tests.num; j++)
                {
                    cout << "������� ���������� ���� ������ (���� ����� ��� (23)): ";
                    cin >> students[i]->tests.dates->day >> students[i]->tests.dates->month >> students[i]->tests.dates->year;
                    while (cin.fail() or !isDateValid(&students[i]->tests.dates[j]))
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "������ � ������ ����. ��������� �������. ������� ���������� ���� ������ (���� ����� ��� (23)): ";
                        cin >> students[i]->tests.dates[j].day >> students[i]->tests.dates[j].month >> students[i]->tests.dates[j].year;
                    }

                }
                cout << "������� ���������� ���������� ������� ��������� (�������� - 5): ";
                cin >> students[i]->exams.num; // ���������� ���������

                while (cin.fail() or students[i]->exams.num > 10 or students[i]->exams.num < 0)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "������ � ���������� ���������. ��������� �������. ������� ���������� ����� ���������: ";
                    cin >> students[i]->exams.num;
                }
                for (int j = 0; j < students[i]->exams.num; j++)
                {
                    cout << "������� ���������� ���� �������� (���� ����� ���): ";
                    cin >> students[i]->exams.dates->day >> students[i]->exams.dates->month >> students[i]->exams.dates->year;
                    while (cin.fail() or !isDateValid(&students[i]->exams.dates[j]))
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "������ � ������ ����. ��������� �������. �������  ���������� ���� �������� (���� ����� ��� (23)): ";
                        cin >> students[i]->exams.dates[j].day >> students[i]->exams.dates[j].month >> students[i]->exams.dates[j].year;
                    }
                    cout << "������� ���������� ������ �� ���� �������: ";
                    cin >> students[i]->exams.marks[i];
                    while (cin.fail() or students[i]->exams.marks[j] > 5 or students[i]->exams.marks[j] < 3)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "������ � ������ ������. ��������� �������. �������  ���������� ������ (3-5)): ";
                        cin >> students[i]->exams.marks[j];
                    }
                    return;
                }
            }
            else
            {
                cout << endl << "������� � ����� �������� �� ������!" << endl << endl;
                return;
            }
        }
        
    }
}

void deleteStudent() {
    string surname_search;
    string name_search;
    string patronymic_search;
    string answer;
    cout << "������� ������� ���������� ��������: ";
    cin >> surname_search;
    cout << "������� ��� ���������� ��������: ";
    cin >> name_search;
    cout << "������� �������� ���������� ��������: ";
    cin >> patronymic_search;
    for (int i = 0; i < 20; i++) {
        if (students[i] != nullptr) { //���������, ��� ������ � ������� �� ������
            if (students[i]->surname == surname_search and students[i]->name == name_search and students[i]->patronymic == patronymic_search) { //���� ���������, ������� ���������� � ��������

                cout << "�������: " << students[i]->surname << endl;
                cout << "���: " << students[i]->name << endl;
                cout << "��������: " << students[i]->patronymic << endl;

                cout << "�� �������?[��/���]: ";
                cin >> answer;
              
                while (answer != "��" && answer != "���")
                {
                    cout << "����� ������ �����������. ������� ������: " << endl;
                    cin >> answer;
                }
                if (answer == "��")
                {
                    delete students[i];
                    students[i] = nullptr;
                    cout << "�������� ������ �������!" << endl; //������
                    return;
                }
                if (answer == "���")
                {
                    cout << "������ ��������" << endl;
                    return;//�� ������
                }
            }
        }
    }
    cout << endl << "������� � ����� �������� �� ������!" << endl << endl;


}


void searchAboutSsesia() {
    for (int i = 0; i < 20; i++) {
        if (students[i] != nullptr) { //���������, ��� ������ � ������� �� ������
            if (students[i]->exams.num == 5) { //���� ���������, ������� ���������� � ��������

                cout << "�������: " << students[i]->surname << endl;
                cout << "���: " << students[i]->name << endl;
                cout << "��������: " << students[i]->patronymic << endl;
                cout << "���� ��������: " << students[i]->birthDate.day << "." << students[i]->birthDate.month << "." << students[i]->birthDate.year << endl;
                cout << "������� ������: " << students[i]->exams.num << endl;
                for (int j = 0; j < students[i]->tests.num; j++) {
                    cout << "���� ����� ������: " << j + 1 << ": " << students[i]->tests.dates[j].day << "." << students[i]->tests.dates[j].month << "." << students[i]->tests.dates[j].year << endl;
                }
                cout << "������� ��������: " << students[i]->exams.num << endl;
                for (int j = 0; j < students[i]->exams.num; j++) {
                    cout << "������ �� ��������: " << j + 1 << ": " << students[i]->exams.marks[j] << endl;
                    cout << "���� ����� ��������: " << j + 1 << ": " << students[i]->exams.dates[j].day << "." << students[i]->exams.dates[j].month << "." << students[i]->exams.dates[j].year << endl;
                }
                cout << endl;
            }
        }
    }

}
    
//int printbaza() {
//
//    //system(".\\Students.txt");
//    string file = "\\Students.txt";
//    HINSTANCE result = ShellExecute(nullptr, "print", file.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
//    if (reinterpret_cast<uintptr_t>(result) <= 32) {
//        std::cout << "Failed to print file\n";
//    }
//    else {
//        std::cout << "File sent to printer\n";
//    }
//    return 0;
//}



int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russia");
    int command;
    while (true) { //����������� ����, �� ��� ��� ���� ������������ �� ������ ������� ������
        cout << "�������� ��������:" << endl;
        cout << "1 - ���������� ��������" << endl;
        cout << "2 - ����� ��������" << endl;
        cout << "3 - ��������� ������ � ����" << endl;
        cout << "4 - ��������� ������ �� �����" << endl;
        cout << "5 - �������������� ��������" << endl;
        cout << "6 - �������� ��������" << endl;
        cout << "7 - �����, ������� ������" << endl;
        cout << "8 - �����" << endl;

        while (true)
        {
            cout << "��� �����: ";
            cin >> command;  cout << "\n";
            if (!cin)
            {
                cout << "������� ������� �����! ���������� ������: \n";
                cin.clear();
                while (cin.get() != '\n');
            }
            else break;

        }


        switch (command) {
        case 1:
            addStudent();
            break;
        case 2:
            findStudent();
            break;
        case 3:
            saveData();
            break;
        case 4:
            loadData();
            break;
        case 5:
            redactorStudent();
            break;
        case 6:
            deleteStudent();
            break;
        case 7:
            searchAboutSsesia();
            break;
        case 8:
            //������� ������ ����� �������
            for (int i = 0; i < 20; i++) {
                if (students[i] != nullptr) {
                    delete students[i];
                    students[i] = nullptr;
                }
            }
            return 0;
        default:
            cout << endl << "�������� �������!" << endl << endl;
        }
    }
}