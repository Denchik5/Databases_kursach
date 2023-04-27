#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<Windows.h>
#include <limits>



using namespace std;

//структура для даты
struct Date {
    int day;
    int month;
    int year;
};

//структура для информации о зачетах
struct Zach {
    int num; //количество сданных зачетов
    Date dates[10]; //даты сдачи зачетов
};

//структура для информации об экзаменах
struct Exam {
    int num; //количество сданных экзаменов
    int marks[5]; //оценки по экзаменам
    Date dates[10]; //даты сдачи экзаменов
};

//структура для информации о студентах
struct Students {
    string surname; //фамилия
    string name; //имя
    string patronymic; //отчество
    Date birthDate; //дата рождения
    Zach tests; //информация о зачетах
    Exam exams; //информация об экзаменах
};

//массив указателей на структуры о студентах
Students* students[20];

bool isDateValid(Date* date) {
    if (date->month > 12 or date->month <= 0) return false; //month
    if (date->day > 31 or date->day <= 0) return false; //day
    if (date->day == 31 and (date->month == 4 or date->month == 6 or date->month == 9 or date->month == 11)) return false; //30 days in Apr, Jun, Sen, Nov
    if ((date->month == 2) and (date->day > 29))  return false; //February
    return true;
}



//функция добавления нового студента
void addStudent() {
    //определяем пустую ячейку в массиве указателей на структуры о студентах
    for (int i = 0; i < 20; i++) {
        if (students[i] == nullptr) {
            students[i] = new Students;
            //вводим информацию о студенте
            cout << "Введите фамилию: ";
            cin >> students[i]->surname;
            cout << "Введите имя: ";
            cin >> students[i]->name;
            cout << "Введите отчество: ";
            cin >> students[i]->patronymic;
            cout << "Введите дату рождения (день месяц год (23)): ";
            cin >> students[i]->birthDate.day >> students[i]->birthDate.month >> students[i]->birthDate.year;
            while (cin.fail() or !isDateValid(&students[i]->birthDate))
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка в записи даты. Повторите попытку. Введите  корректную дату рождения (день месяц год (23)): ";
                cin >> students[i]->birthDate.day >> students[i]->birthDate.month >> students[i]->birthDate.year;
            }


            cout << "Введите количество сданных зачетов (максимум - 10): ";
            cin >> students[i]->tests.num; // количество зачетов
            while (cin.fail() or students[i]->tests.num > 10 or students[i]->tests.num < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка в количестве зачетов. Повторите попытку. Введите корректное число зачетов: ";
                cin >> students[i]->tests.num;
            }

            for (int j = 0; j < students[i]->tests.num; j++)
            {
                cout << "Введите дату зачета (день месяц год (23)): ";
                cin >> students[i]->tests.dates[j].day >> students[i]->tests.dates[j].month >> students[i]->tests.dates[j].year;
                while (cin.fail() or !isDateValid(&students[i]->tests.dates[j]))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ошибка в записи даты. Повторите попытку. Введите корректную дату зачета (день месяц год (23)): ";
                    cin >> students[i]->tests.dates[j].day >> students[i]->tests.dates[j].month >> students[i]->tests.dates[j].year;
                }

            }
            cout << "Введите количество сданных экзаменов (максимум - 5): ";
            cin >> students[i]->exams.num; // количество экзаменов
            
            while (cin.fail() or students[i]->exams.num > 5 or students[i]->exams.num < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Ошибка в количестве экзаменов. Повторите попытку. Введите корректное число экзаменов: ";
                cin >> students[i]->exams.num;
            }

            for (int j = 0; j < students[i]->exams.num; j++)
            {
                cout << "Введите дату экзамена (день месяц год (23)): ";
                cin >> students[i]->exams.dates[j].day >> students[i]->exams.dates[j].month >> students[i]->exams.dates[j].year;
                while (cin.fail() or !isDateValid(&students[i]->exams.dates[j]))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ошибка в записи даты. Повторите попытку. Введите  корректную дату экзамена (день месяц год (23)): ";
                    cin >> students[i]->exams.dates[j].day >> students[i]->exams.dates[j].month >> students[i]->exams.dates[j].year;
                }
                cout << "Введите оценку за этот экзамен (3-5): ";
                cin >> students[i]->exams.marks[j];
                while (cin.fail() or students[i]->exams.marks[j] > 5 or students[i]->exams.marks[j] < 3)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ошибка в записи оценки. Повторите попытку. Введите  корректную оценку (3-5)): ";
                    cin >> students[i]->exams.marks[j];
                }
            }
            cout << endl << "Студент успешно добавлен!" << endl << endl;
            return;
        }
    }
    cout << endl << "В группе нет свободных мест!" << endl << endl;
}

//функция поиска студента по фамилии

void findStudent() {
    string surname_search;
    string name_search;
    string patronymic_search;
    cout << "Введите фамилию студента: ";
    cin >> surname_search;
    cout << "Введите имя студента: ";
    cin >> name_search;
    cout << "Введите отчество студента: ";
    cin >> patronymic_search;

    for (int i = 0; i < 20; i++) {
        if (students[i] != nullptr) { //проверяем, что ячейка в массиве не пустая
            if (students[i]->surname == surname_search and students[i]->name == name_search and students[i]->patronymic == patronymic_search) { //если совпадает, выводим информацию о студенте

                cout << "Фамилия: " << students[i]->surname << endl;
                cout << "Имя: " << students[i]->name << endl;
                cout << "Отчество: " << students[i]->patronymic << endl;
                cout << "Дата рождения: " << students[i]->birthDate.day << "." << students[i]->birthDate.month << "." << students[i]->birthDate.year << endl;
                cout << "Сданные зачеты: " << students[i]->tests.num << endl;
                for (int j = 0; j < students[i]->tests.num; j++) {
                    cout << "Дата сдачи зачета: " << j + 1 << ": " << students[i]->tests.dates[j].day << "." << students[i]->tests.dates[j].month << "." << students[i]->tests.dates[j].year << endl;
                }
                cout << "Сданные экзамены: " << students[i]->exams.num << endl;
                for (int j = 0; j < students[i]->exams.num; j++) {
                    cout << "Оценка по экзамену: " << j + 1 << ": " << students[i]->exams.marks[j] << endl;
                    cout << "Дата сдачи экзамена: " << j + 1 << ": " << students[i]->exams.dates[j].day << "." << students[i]->exams.dates[j].month << "." << students[i]->exams.dates[j].year << endl;
                }
                cout << endl;
                return;
            }
        }
    }
    cout << endl << "Студент с такой фамилией не найден!" << endl << endl;
}

//функция сохранения данных в файл
void saveData() {
    ofstream outFile(".\\Students.txt", ios::trunc);  //ios::app
    if (outFile.is_open()) {
        //перебираем все ячейки в массиве, пока не найдем первую пустую
        for (int i = 0; i < 20; i++) {
            if (students[i] != nullptr) {
                outFile << "Фамилия: " << students[i]->surname << endl;
                outFile << "Имя: " << students[i]->name << endl;
                outFile << "Отчество: " << students[i]->patronymic << endl;
                outFile << "Дата рождения: " << students[i]->birthDate.day << "." << students[i]->birthDate.month << "." << students[i]->birthDate.year << endl;

                outFile << endl;

                outFile << "Количество сданных зачетов (из 10): " << students[i]->tests.num << endl;
                for (int j = 0; j < students[i]->tests.num; j++) {
                    outFile << "Зачет #" << j + 1 << " " << "Дата сдачи зачета: "
                        << students[i]->tests.dates[j].day << "."
                        << students[i]->tests.dates[j].month << "."
                        << students[i]->tests.dates[j].year << endl;
                }

                outFile << "Количество сданных экзаменов (из 5): " << students[i]->exams.num << endl;
                for (int j = 0; j < students[i]->exams.num; j++) {
                    outFile << "Экзамен #" << j + 1 << " " << "Дата сдачи экзамена: "
                        << students[i]->exams.dates[j].day << "."
                        << students[i]->exams.dates[j].month << "."
                        << students[i]->exams.dates[j].year << " " << endl;

                    outFile << "Оценка за экзамен: "
                        << students[i]->exams.marks[j] << " " << endl;
                }
                outFile << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
                outFile << endl;
            }
        }
        outFile.close();
        cout << endl << "Данные успешно сохранены в файл!" << endl << endl;
    }
    else {
        cout << endl << "Ошибка открытия файла!" << endl << endl;
    }
}

//функция загрузки данных из файла
void loadData() {
    ifstream inFile(".\\Students.txt");
    if (inFile.is_open()) {

        cout << inFile.rdbuf();

        inFile.close();
        cout << endl << "Данные успешно загружены из файла!" << endl << endl;
    }
    else {
        cout << endl << "Ошибка открытия файла!" << endl << endl;
    }
}

void redactorStudent() {

    string surname_search;
    string name_search;
    string patronymic_search;

    cout << "Введите фамилию студента: ";   
    cin >> surname_search;
    cout << "Введите имя студента: ";
    cin >> name_search;
    cout << "Введите отчество студента: ";
    cin >> patronymic_search;

    for (int i = 0; i < 20; i++) {
        if (students[i] != nullptr) { //проверяем, что ячейка в массиве не пустая
            if (students[i]->surname == surname_search and students[i]->name == name_search and students[i]->patronymic == patronymic_search) { //если совпадает, выводим информацию о студенте

                cout << "Фамилия: " << students[i]->surname << endl;
                cout << "Имя: " << students[i]->name << endl;
                cout << "Отчество: " << students[i]->patronymic << endl;
                cout << "Дата рождения: " << students[i]->birthDate.day << "." << students[i]->birthDate.month << "." << students[i]->birthDate.year << endl;
                cout << "Сданные зачеты: " << students[i]->tests.num << endl;
                for (int j = 0; j < students[i]->tests.num; j++) {
                    cout << "Дата сдачи зачета: " << j + 1 << ": " << students[i]->tests.dates[j].day << "." << students[i]->tests.dates[j].month << "." << students[i]->tests.dates[j].year << endl;
                }
                cout << "Сданные экзамены: " << students[i]->exams.num << endl;
                for (int j = 0; j < students[i]->exams.num; j++) {
                    cout << "Оценка по экзамену: " << j + 1 << ": " << students[i]->exams.marks[j] << endl;
                    cout << "Дата сдачи экзамена: " << j + 1 << ": " << students[i]->exams.dates[j].day << "." << students[i]->exams.dates[j].month << "." << students[i]->exams.dates[j].year << endl;
                }

                cout << endl;

                cout << "Введите изменненую фамилию: "; cin >> students[i]->surname;
                cout << "Введите изменненое имя: "; cin >> students[i]->name;
                cout << "Введите изменненое отчество: "; cin >> students[i]->patronymic;
                cout << "Введите измененную дату рождения (день месяц год (23)): ";
                cin >> students[i]->birthDate.day >> students[i]->birthDate.month >> students[i]->birthDate.year;
 
                 while (cin.fail() or !isDateValid(&students[i]->birthDate))
                 {
                    cout << "Ошибка в записи даты. Повторите попытку. Введите  корректную дату рождения (день месяц год (23)): ";
                    cin >> students[i]->birthDate.day >> students[i]->birthDate.month >> students[i]->birthDate.year;
                 }

                cout << "Введите изменненое количество сданных зачетов (максимум - 10): ";
                cin >> students[i]->tests.num; // количество зачетов
                if (students[i]->tests.num > 10 or students[i]->tests.num < 0)
                {
                    while (students[i]->tests.num > 10 or students[i]->tests.num < 0)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Ошибка в количестве зачетов. Повторите попытку. Введите корректное число зачетов: ";
                        cin >> students[i]->tests.num;
                    }

                }
                for (int j = 0; j < students[i]->tests.num; j++)
                {
                    cout << "Введите измененную дату зачета (день месяц год (23)): ";
                    cin >> students[i]->tests.dates->day >> students[i]->tests.dates->month >> students[i]->tests.dates->year;
                    while (cin.fail() or !isDateValid(&students[i]->tests.dates[j]))
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Ошибка в записи даты. Повторите попытку. Введите корректную дату зачета (день месяц год (23)): ";
                        cin >> students[i]->tests.dates[j].day >> students[i]->tests.dates[j].month >> students[i]->tests.dates[j].year;
                    }

                }
                cout << "Введите измененное количество сданных экзаменов (максимум - 5): ";
                cin >> students[i]->exams.num; // количество экзаменов

                while (cin.fail() or students[i]->exams.num > 10 or students[i]->exams.num < 0)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Ошибка в количестве экзаменов. Повторите попытку. Введите корректное число экзаменов: ";
                    cin >> students[i]->exams.num;
                }
                for (int j = 0; j < students[i]->exams.num; j++)
                {
                    cout << "Введите измененную дату экзамена (день месяц год): ";
                    cin >> students[i]->exams.dates->day >> students[i]->exams.dates->month >> students[i]->exams.dates->year;
                    while (cin.fail() or !isDateValid(&students[i]->exams.dates[j]))
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Ошибка в записи даты. Повторите попытку. Введите  корректную дату экзамена (день месяц год (23)): ";
                        cin >> students[i]->exams.dates[j].day >> students[i]->exams.dates[j].month >> students[i]->exams.dates[j].year;
                    }
                    cout << "Введите измененную оценку за этот экзамен: ";
                    cin >> students[i]->exams.marks[i];
                    while (cin.fail() or students[i]->exams.marks[j] > 5 or students[i]->exams.marks[j] < 3)
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Ошибка в записи оценки. Повторите попытку. Введите  корректную оценку (3-5)): ";
                        cin >> students[i]->exams.marks[j];
                    }
                    return;
                }
            }
            else
            {
                cout << endl << "Студент с такой фамилией не найден!" << endl << endl;
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
    cout << "Введите фамилию удаляемого студента: ";
    cin >> surname_search;
    cout << "Введите имя удаляемого студента: ";
    cin >> name_search;
    cout << "Введите отчество удаляемого студента: ";
    cin >> patronymic_search;
    for (int i = 0; i < 20; i++) {
        if (students[i] != nullptr) { //проверяем, что ячейка в массиве не пустая
            if (students[i]->surname == surname_search and students[i]->name == name_search and students[i]->patronymic == patronymic_search) { //если совпадает, выводим информацию о студенте

                cout << "Фамилия: " << students[i]->surname << endl;
                cout << "Имя: " << students[i]->name << endl;
                cout << "Отчество: " << students[i]->patronymic << endl;

                cout << "Вы уверены?[Да/Нет]: ";
                cin >> answer;
              
                while (answer != "Да" && answer != "Нет")
                {
                    cout << "Ответ введен некорректно. Введите заново: " << endl;
                    cin >> answer;
                }
                if (answer == "Да")
                {
                    delete students[i];
                    students[i] = nullptr;
                    cout << "Удаление прошло успешно!" << endl; //УДАЛЯЮ
                    return;
                }
                if (answer == "Нет")
                {
                    cout << "Отмена удаления" << endl;
                    return;//НЕ УДАЛЯЮ
                }
            }
        }
    }
    cout << endl << "Студент с такой фамилией не найден!" << endl << endl;


}


void searchAboutSsesia() {
    for (int i = 0; i < 20; i++) {
        if (students[i] != nullptr) { //проверяем, что ячейка в массиве не пустая
            if (students[i]->exams.num == 5) { //если совпадает, выводим информацию о студенте

                cout << "Фамилия: " << students[i]->surname << endl;
                cout << "Имя: " << students[i]->name << endl;
                cout << "Отчество: " << students[i]->patronymic << endl;
                cout << "Дата рождения: " << students[i]->birthDate.day << "." << students[i]->birthDate.month << "." << students[i]->birthDate.year << endl;
                cout << "Сданные зачеты: " << students[i]->exams.num << endl;
                for (int j = 0; j < students[i]->tests.num; j++) {
                    cout << "Дата сдачи зачета: " << j + 1 << ": " << students[i]->tests.dates[j].day << "." << students[i]->tests.dates[j].month << "." << students[i]->tests.dates[j].year << endl;
                }
                cout << "Сданные экзамены: " << students[i]->exams.num << endl;
                for (int j = 0; j < students[i]->exams.num; j++) {
                    cout << "Оценка по экзамену: " << j + 1 << ": " << students[i]->exams.marks[j] << endl;
                    cout << "Дата сдачи экзамена: " << j + 1 << ": " << students[i]->exams.dates[j].day << "." << students[i]->exams.dates[j].month << "." << students[i]->exams.dates[j].year << endl;
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
    while (true) { //бесконечный цикл, до тех пор пока пользователь не введет команду выхода
        cout << "Выберите действие:" << endl;
        cout << "1 - Добавление студента" << endl;
        cout << "2 - Найти студента" << endl;
        cout << "3 - Сохранить данные в файл" << endl;
        cout << "4 - Загрузить данные из файла" << endl;
        cout << "5 - Редактирование студента" << endl;
        cout << "6 - Удаление студента" << endl;
        cout << "7 - Поиск, сдавших ссесию" << endl;
        cout << "8 - Выход" << endl;

        while (true)
        {
            cout << "Ваш выбор: ";
            cin >> command;  cout << "\n";
            if (!cin)
            {
                cout << "Неверно введено число! Попробуйте заново: \n";
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
            //очищаем память перед выходом
            for (int i = 0; i < 20; i++) {
                if (students[i] != nullptr) {
                    delete students[i];
                    students[i] = nullptr;
                }
            }
            return 0;
        default:
            cout << endl << "Неверная команда!" << endl << endl;
        }
    }
}