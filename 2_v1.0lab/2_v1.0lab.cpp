#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <algorithm>
using namespace std;

namespace Color {
    // ANSI escape codes для изменения цвета текста
    const string RESET = "\033[0m"; //сброс
    const string RED = "\033[1m\033[31m"; //красный 
    const string GREEN = "\033[1m\033[32m";//зеленый
    const string YELLOW = "\033[1m\033[33m"; //желтый
    const string BLUE = "\033[1m\033[34m";//синий
    const string MAGENTA = "\033[1m\033[35m";// пурпурный
    const string CYAN = "\033[1m\033[36m";// голубой
    const string BLACK = "\033[1m\033[30m";// черный
    const string WHITE = "\033[1m\033[37m"; // белый

    void Red(const string& text) {
        cout << RED << text << RESET << endl;
    }
    void Green(const string& text) {
        cout << GREEN << text << RESET << endl;
    }
    void Yellow(const string& text) {
        cout << YELLOW << text << RESET << endl;
    }
    void Blue(const string& text) {
        cout << BLUE << text << RESET << endl;
    }
    void Magenta(const string& text) {
        cout << MAGENTA << text << RESET << endl;
    }
    void Cian(const string& text) {
        cout << CYAN << text << RESET << endl;
    }
    void Black(const string& text) {
        cout << BLACK << text << RESET << endl;
    }
    void White(const string& text) {
        cout << WHITE << text << RESET << endl;
    }

}
using namespace Color;

struct Profile
{
    string firstName; // Фамилия Имя Отчество
    string secondName;// Фамилия Имя Отчество
    char sex;         // Пол: M/W
    int group;        // Номер группы
    int id;           // Номер студента в списке 
    int grades[8];    // Оценки за экзамены и диф. зачёты
    float srArifm;    // Средний балл
    char depart;      // Форма обучения
};


const int MAX_STUDENTS = 250; 
Profile masStudents[MAX_STUDENTS];
Profile sortedMasStudents[MAX_STUDENTS];
Profile sortedBySurnameStudents[MAX_STUDENTS];


//FUNCTIONS
//1 пункт
void createNewSt()
{

    Profile new_student;
    ofstream data_base;
    //Ввод того что будет добавлено в файл:

    string line;
    int lineCount = 0;
    ifstream file("students.txt");
    while (getline(file, line)) lineCount++;

    data_base.open("students.txt", ios::app);

    cin.clear();
    Green("Введите фамилию: ");
    cin.ignore();
    getline(cin, new_student.firstName);  // ФИО
    masStudents[lineCount].firstName = new_student.firstName;

    cin.clear();
    Green("Введите имя: ");
    getline(cin, new_student.secondName);  // ФИО
    masStudents[lineCount].secondName = new_student.secondName;

    Green("Введите Номер группы: ");
    cin >> new_student.group;     // Номер группы
    masStudents[lineCount].group = new_student.group;
    new_student.id = 1;        // Номер в списке группы
    masStudents[lineCount].id = new_student.id;
    Green("Введите Пол: ");
    cin >> new_student.sex;       // Пол
    masStudents[lineCount].sex = new_student.sex;
    Green("Введите форму обучения: [K/k] or [B/b]: ");
    cin >> new_student.depart;    // Форма обучения
    masStudents[lineCount].depart = new_student.depart;
    Green("Оценки: ");
    float sredniiBal = 0;
    for (int i = 0; i < 8; i++)   // Оценки
    {
        cin >> new_student.grades[i];
        sredniiBal += new_student.grades[i];
        masStudents[lineCount].grades[i] = new_student.grades[i];
    }
    //Средний балл
    masStudents[lineCount].srArifm = sredniiBal / 8.0f;

    int temp = 0;
    for (int i = 0; i < 8; i++)
    {
        if (new_student.grades[i] == 2)
            temp++;
    }
    if (temp == 0)
    {

        if (!data_base.is_open())
            cout << '\n' << "Сохранить не удалось";
        else
        {
            data_base << new_student.firstName << " ";
            data_base << new_student.secondName << " ";
            data_base << new_student.group << " " << new_student.id << " " << new_student.sex << " ";
            data_base << new_student.depart << " ";
            for (int i = 0; i < 8; i++)
                data_base << new_student.grades[i] << " ";
            data_base << masStudents[lineCount].srArifm << " ";
            data_base << endl;
            data_base.close();
            cout << '\n' << "Профиль сохранен в базу данных.\n"<<endl;
        }
    }
    else
        cout << '\n' << "Этот студент исключен. Профиль не будет сохранен в базе данных."<<endl;
}

void readStudents(Profile masStudents[], int count) {
    ifstream inputFile("students.txt");

    if (!inputFile) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    count = 0;

    while (inputFile) {
        Profile student;

        inputFile >> student.firstName >> student.secondName;
        if (!inputFile) break; 

        inputFile >> student.group >> student.id >> student.sex >> student.depart;

        for (int i = 0; i < 8; ++i) {
            inputFile >> student.grades[i];
        }
        
        inputFile >> student.srArifm;


        if (!inputFile) break; 

        masStudents[count++] = student;
    }

    inputFile.close();
}

void WriteMasToFile(Profile* students, int count) {
    ofstream outFile("students.txt");

    if (!outFile) {
        cout << "Не удалось открыть файл для записи." << endl;
    }

    for (int i = 0; i < count; ++i) 
    {
        outFile << students[i].firstName << " " << students[i].secondName << " " << students[i].group << " " << students[i].id<< " " << students[i].sex<< " " << students[i].depart<< " ";
        for (int j = 0; j < 8; j++) 
        {
            outFile << students[i].grades[j] << " ";
        }
        outFile<< students[i].srArifm << endl;
    }

    outFile.close();
}

//2 пункт
bool Del = false;
void changeSt()
{
    string line;
    int lineCount = 0;
    ifstream file("students.txt");
    while (getline(file, line)) lineCount++;
    while (true) 
    {
        Red("Выберите пункт (1-2) или 0 для выхода\n");
        cout << "1. Удалить запись.\n";
        cout << "2. Внесение изменений в уже имеющуюся запись.\n";
        cout << "0. Выход.\n";
        int vibor;
        cin >>  vibor;
        if (vibor == 0) break;
        if (vibor < 0 or vibor >2) 
        {
            Magenta("Вы ввели некорректное значение. Попробуйте еще раз");
            continue;
        }
        if (vibor == 1) 
        {
            Magenta("Введите фамилию студента, данные которого хотите УДАЛИТЬ: ");
            string surname;
            cin >> surname;

            int index = -1;
            for (int i = 0; i < lineCount; ++i)
            {
                if (masStudents[i].firstName == surname) 
                {
                    index = i;
                    break;
                }
            }
            for (int i = index; i < lineCount; i++)
            {
                masStudents[i] = masStudents[i + 1];
            }
            lineCount--;
            cout << "Студент с фамилией " << surname << " удален." << endl;
            Del = true;
            break;
        }

        else if (vibor == 2) 
        {
            Profile new_student;
            Green("Сейчас вы можете внести изменение в уже имеющуюся запись ");
            Magenta("Введите фамилию студента, данные которого хотите ИЗМЕНИТЬ: ");
            string surname;
            cin >> surname;
            for (int i = 0; i < lineCount; ++i)
            {
                if (masStudents[i].firstName == surname)
                {
                    Magenta("Введите что именно необходимо изменить: ");
                    int choice;
                    //Меню
                    Red("Выберите пункт (1-7) или 0 для выхода\n");
                    cout << "1. Фамилия.\n";
                    cout << "2. Имя. \n";
                    cout << "3. Группа.\n";
                    cout << "4. Номер студента в списке.\n";
                    cout << "5. Пол\n";
                    cout << "6. Оценки за экзамены.\n";
                    cout << "7. Форма обучения.\n";
                    cout << "0. Выход\n";
                    cin >> choice;
                    if (choice == 0) break;

                    if (choice < 0 || choice > 7) {
                        cout << "Некорректный выбор. Попробуйте снова." << endl;
                        continue; // Возврат в начало цикла для нового выбора
                    }

                    switch (choice)
                    {
                    case 1:
                    {
                        Magenta("Введите новую фамилию: ");
                        string familia;
                        cin.clear();
                        cin >> familia;
                        masStudents[i].firstName = familia;
                        break;
                    }
                    case 2:
                    {
                        Magenta("Введите новое имя: ");
                        string NAME;
                        cin.clear();
                        cin >> NAME;
                        masStudents[i].secondName = NAME;
                        break;
                    }
                    case 3:
                    {
                        Magenta("Введите новую группу: ");
                        int GROUP;
                        cin.clear();
                        cin >> GROUP;
                        masStudents[i].group = GROUP;
                        break;
                    }

                    case 4:
                    {
                        Magenta("Номер студента в списке зависит от Фамилии и Имени. Данный параметр изменить нельзя. ");
                    }
                    case 5:
                    {
                        Magenta("Введите пол: ");
                        char SEX;
                        cin.clear();
                        cin >> SEX;
                        masStudents[i].sex = SEX;
                        break;
                    }

                    case 6:
                    {
                        float sredniiBal = 0;
                        Magenta("Введите новые оценки за экзамен: ");
                        for (int j = 0; j < 8; j++)   // Оценки
                        {
                            cin >> masStudents[i].grades[j];
                            sredniiBal += masStudents[i].grades[j];
                            masStudents[lineCount].grades[i] = new_student.grades[i];
                        }
                        masStudents[i].srArifm = sredniiBal / 8.0f;
                        break;
                    }

                    case 7:
                    {
                        Magenta("Введите форму обучения: ");
                        char DEPART;
                        cin.clear();
                        cin >> DEPART;
                        masStudents[i].depart = DEPART;
                        break;
                    }
                    }
                    break;
                }
            }
        }
        break;
    }
}

bool compareProfiles(const Profile& a, const Profile& b) {
    if (a.group != b.group)
        return a.group < b.group;

    if (a.firstName != b.firstName)
        return a.firstName < b.firstName;
    return a.secondName < b.secondName;
}

void sortAndNumerationByGroupSurnameName()
{
    string line;
    int lineCount = 0;
    ifstream file("students.txt");
    while (getline(file, line)) lineCount++;


    sort(masStudents, masStudents + lineCount, compareProfiles);
    int currentGroup = masStudents[0].group;
    int groupId = 1;  

    masStudents[0].id = groupId;

    for (int i = 1; i < lineCount; ++i) 
    {
        if (masStudents[i].group != currentGroup) {
            currentGroup = masStudents[i].group;
            groupId = 1; 
        }
        else {
            groupId++; 
        }

        masStudents[i].id = groupId;
    }
}

//3 пункт
void printStud(Profile mas[MAX_STUDENTS])
{
    string line;
    int lineCount = 0;
    ifstream file("students.txt");
    while (getline(file, line)) lineCount++;

    for (int i = 0; i < lineCount; ++i) 
    {
        cout << mas[i].firstName << " " << mas[i].secondName << " " << mas[i].group <<" "<< mas[i].id<< " "<< mas[i].sex<< " " << mas[i].depart<< " ";
        for (int j = 0; j < 8; ++j) 
        {
            cout << mas[i].grades[j] << (j < 7 ? ", " : " ");
        }
        cout<< mas[i].srArifm << endl;
    }
}

//4 пункт
void printGroup() 
{
    string line;
    int lineCount = 0;
    ifstream file("students.txt");
    while (getline(file, line)) lineCount++;
    
    Magenta("Введите группу, данные которой хотите вывести на экран: ");
    int GROUP;
    cin >> GROUP;

    for (int i = 0; i < lineCount; ++i) 
    {
        if (masStudents[i].group == GROUP)
        {
            cout << masStudents[i].firstName << " " << masStudents[i].secondName << " " << masStudents[i].group << " " << masStudents[i].id << " " << masStudents[i].sex << " " << masStudents[i].depart << " ";
            for (int j = 0; j < 8; ++j)
            {
                cout << masStudents[i].grades[j] << (j < 7 ? ", " : " ");
            }
            cout<< masStudents[i].srArifm << endl;
        }
    }
}
//5 пункт
bool parametr(const Profile& a, const Profile& b) {
    return a.srArifm > b.srArifm;
}
void sortBySrArifm() 
{
    string line;
    int lineCount = 0;
    ifstream file("students.txt");
    while (getline(file, line)) lineCount++;


    sort(sortedMasStudents, sortedMasStudents + MAX_STUDENTS, parametr);
    Magenta("Топ из скольки человек вы хотите увидеть? ");
    cout << "Количество (Максимум - "<<lineCount<<"): ";
    int num;
    cin >> num;
    cout << endl;
    if (num > lineCount) num = lineCount;

    for (int i = 0; i < num; ++i)
    {
        cout << sortedMasStudents[i].firstName << " " << sortedMasStudents[i].secondName << " " << sortedMasStudents[i].group << " " << sortedMasStudents[i].id << " " << sortedMasStudents[i].sex << " " << sortedMasStudents[i].depart << " ";
        for (int j = 0; j < 8; ++j)
        {
            cout << sortedMasStudents[i].grades[j] << (j < 7 ? ", " : " ");
        }
        cout << sortedMasStudents[i].srArifm << endl;
    }
    cout << endl;

}

//6 пункт
void countMandW() 
{
    string line;
    int lineCount = 0;
    ifstream file("students.txt");
    while (getline(file, line)) lineCount++;
    int countM = 0;
    int countW = 0;
    for (int i = 0; i < lineCount; ++i)
    {
        if (masStudents[i].sex == 'M' or masStudents[i].sex == 'm') countM++;
        else countW++;
    }
    cout << "Количество парней: " << countM<<endl;
    cout << "Количество девушек: " << countW<<endl<<endl;
}

//7 пункт
void whoLearning_1_2_3_Variations()
{
    string line;
    int lineCount = 0;
    ifstream file("students.txt");
    while (getline(file, line)) lineCount++;

    //Меню
    Red("Выберите пункт (1-3) или 0 для выхода\n");
    cout << "1. Вывод данных о студентах, которые не получают стипендию.\n";
    cout << "2. Учатся только на «хорошо» и «отлично». \n";
    cout << "3. Учатся только на «отлично».\n";
    cout << "0. Выход\n";
    int Var;
    cin >> Var;
    
    if (Var == 1) 
    {
        for (int i = 0; i < lineCount; ++i)
        {
            bool YorN = false;
            for (int j = 0; j < 8; ++j)
            {
                if (masStudents[i].grades[j] == 3) YorN = true;
            }
            if (YorN or masStudents[i].depart == 'K' or masStudents[i].depart == 'k')
            {
                cout << masStudents[i].firstName << " " << masStudents[i].secondName << " " << masStudents[i].group << " " << masStudents[i].id << " " << masStudents[i].sex << " " << masStudents[i].depart << " ";
                for (int j = 0; j < 8; ++j)
                {
                    cout << masStudents[i].grades[j] << (j < 7 ? ", " : " ");
                }
                cout << masStudents[i].srArifm << endl;
            }
        }
    }
    if (Var == 2) 
    {
        for (int i = 0; i < lineCount; ++i)
        {
            bool Y5 = false;
            bool Y4 = false;
            bool Y3 = false;
            for (int j = 0; j < 8; ++j)
            {
                if (masStudents[i].grades[j] == 3) Y3 = true;
                if (masStudents[i].grades[j] == 4) Y4 = true;
                if (masStudents[i].grades[j] == 5) Y5 = true;

            }
            if (Y4 && Y5 && (!Y3))
            {
                cout << masStudents[i].firstName << " " << masStudents[i].secondName << " " << masStudents[i].group << " " << masStudents[i].id << " " << masStudents[i].sex << " " << masStudents[i].depart << " ";
                for (int j = 0; j < 8; ++j)
                {
                    cout << masStudents[i].grades[j] << (j < 7 ? ", " : " ");
                }
                cout << masStudents[i].srArifm << endl;
            }
        }
    }
    if (Var == 3)
    {
        for (int i = 0; i < lineCount; ++i)
        {
            bool Y5 = false;
            bool Y4 = false;
            bool Y3 = false;
            for (int j = 0; j < 8; ++j)
            {
                if (masStudents[i].grades[j] == 3) Y3 = true;
                if (masStudents[i].grades[j] == 4) Y4 = true;
                if (masStudents[i].grades[j] == 5) Y5 = true;

            }
            if (!Y4 && Y5 && (!Y3))
            {
                cout << masStudents[i].firstName << " " << masStudents[i].secondName << " " << masStudents[i].group << " " << masStudents[i].id << " " << masStudents[i].sex << " " << masStudents[i].depart << " ";
                for (int j = 0; j < 8; ++j)
                {
                    cout << masStudents[i].grades[j] << (j < 7 ? ", " : " ");
                }
                cout << masStudents[i].srArifm << endl;
            }
        }
    }
}

//8 пункт
void haveNumberK() 
{
    string line;
    int lineCount = 0;
    ifstream file("students.txt");
    while (getline(file, line)) lineCount++;

    //Меню
    Red("Введите номер K: \n");
    int K;
    cin >> K;

    for (int i = 0; i < lineCount; ++i)
    {
        if (masStudents[i].id == K)
        {
            cout << masStudents[i].firstName << " " << masStudents[i].secondName << " " << masStudents[i].group << " " << masStudents[i].id << " " << masStudents[i].sex << " " << masStudents[i].depart << " ";
            for (int j = 0; j < 8; ++j)
            {
                cout << masStudents[i].grades[j] << (j < 7 ? ", " : " ");
            }
            cout << masStudents[i].srArifm << endl;
        }
    }
}


//ИДЗ
struct Dish 
{
    string nameDish;
    int weight;
    int price;
    int masGrades[250];
    float srArr;
};

Dish masDish[250];
const int countDishes = 8;

void createDish() 
{
    string names[] = {"Рассольник", "Борщ", "Пельмени", "Омлет", "Салат", "Стейк", "Картофель - фри", "Чай"};
    int weights[] = {300,300, 250, 200, 150, 400, 200, 250};
    int prices[] = {170,150, 200, 100, 120, 350, 180, 100};
    int grades[][5] = {
        {5, 5, 5, 5, 5},
        {5, 4, 5, 3, 5},
        {4, 4, 3, 5, 5},
        {3, 4, 4, 4, 5},
        {5, 5, 5, 4, 4},
        {5, 4, 5, 5, 5},
        {3, 3, 5, 5, 5},
        {3, 5, 5, 5, 5}
    };

    for (int i = 0; i < countDishes; i++) {
        masDish[i].nameDish = names[i];
        masDish[i].weight = weights[i];
        masDish[i].price = prices[i];

        int sum = 0;
        for (int j = 0; j < 5; j++) { // Заполняем оценки и считаем среднее
            masDish[i].masGrades[j] = grades[i][j];
            sum += grades[i][j];
        }
        masDish[i].srArr = sum / 5.0f;
    }

}

bool parametrDish(const Dish& a, const Dish& b) 
{
    return a.srArr > b.srArr;
}
void sortBySrArr()
{
    sort(masDish, masDish + countDishes, parametrDish);
    Magenta("Топ из скольки блюд вы хотите увидеть? ");
    cout << "Количество (Максимум - " << 5 << "): ";
    int num;
    cin >> num;
    cout << endl;
    if (num > countDishes) num = countDishes;

    for (int i = 0; i < num; i++)
    {
        cout << "Блюдо: " << masDish[i].nameDish << ", Вес: " << masDish[i].weight << "г, Цена: " << masDish[i].price << " руб." << endl;
        cout << "Средняя оценка: " << masDish[i].srArr << endl;
    }
    cout << endl;

}

void printDish() 
{
    for (int i = 0; i < countDishes; i++)
    {
        cout << "Блюдо: " << masDish[i].nameDish << ", Вес: " << masDish[i].weight << "г, Цена: " << masDish[i].price << " руб." << endl;
        cout << "Средняя оценка: " << masDish[i].srArr << endl;
    }
}

void CreateOrder()
{
    const int countDishes = 8;
    string menu[countDishes] = 
    {
        "Рассольник", "Борщ", "Пельмени", "Омлет",
        "Салат", "Стейк", "Картофель - фри", "Чай"
    };

    bool ordered[countDishes] = {false};  
    string korzina[countDishes];  
    int cartSize = 0;

    while (true)
    {
        int choice;
        Magenta("Добро пожаловать в столовую «Анастасия»! ");
        Red("Выберите пункт (1-8) или 0 для выхода\n");
        Yellow("Меню: ");
        for (int i = 0; i < countDishes; i++) 
        {
            cout << i + 1 << ". " << menu[i] << endl;
        }

        cin >> choice;
        cout << endl;

        if (choice == 0) break;

        if (choice >= 1 && choice <= countDishes)
        {
            int index = choice - 1;
            if (!ordered[index])
            {
                ordered[index] = true;  
                korzina[cartSize++] = menu[index];
            }

            Cian("Корзина: ");
            for (int i = 0; i < cartSize; i++)
            {
                cout << korzina[i] << (i < cartSize - 1 ? ", " : "\n");
            }
        }

        Magenta("Желаете оплатить заказ?");
        cout << "1. Да, ПОСКОРЕЕ БЫ ПОЕСТЬ!!\n";
        cout << "2. Нет, я добавлю еще еды\n";
        int vibor;
        cin >> vibor;
        if (vibor == 1) break;
    }

    int sum = 0;
    for (int i = 0; i < countDishes; i++) 
    {
        if (ordered[i]) sum += masDish[i].price;
    }

    Magenta("Итак");
    cout << "Сумма вашего заказа = " << sum << endl;
    Red("1 - оплатить\n");
    int oplata;
    cin >> oplata;

    Green("Спасибо за заказ! Приятного аппетита!\n");

    for (int i = 0; i < countDishes; i++) 
    {
        if (ordered[i])
        {
            int grade;
            cout << "Оцените блюдо \"" << masDish[i].nameDish << "\" (от 1 до 5): ";
            cin >> grade;

            // Добавление оценки в массив оценок
            if (grade >= 1 && grade <= 5) 
            {
                for (int j = 0; j < 250; j++) 
                {
                    if (masDish[i].masGrades[j] == 0)
                    {
                        masDish[i].masGrades[j] = grade;
                        break;
                    }
                }
            }
            else {
                cout << "Некорректная оценка! Оценка не добавлена." << endl;
            }
        }
    }
}
int main()
{
    string line;
    int lineCount = 0;
    ifstream file("students.txt");
    while (getline(file, line)) lineCount++;

    setlocale(LC_ALL, "ru");
    while (true)
    {
        int choice;
        //Меню
        Red("Выберите пункт (1-8) или 0 для выхода\n");
        cout << "1. Создание новой записи о студенте.\n";
        cout << "2. Внесение изменений в уже имеющуюся запись. \n";
        cout << "3. Вывод всех данных о студентах.\n";
        cout << "4. Вывод информации обо всех студентах группы N. N – инициализируется пользователем.\n";
        cout << "5. Вывод топа самых успешных студентов с наивысшим по рейтингу средним баллом за прошедшую сессию.\n";
        cout << "6. Вывод количества студентов мужского и женского пола.\n";
        cout << "7. Вывод данных о студентах, которые не получают стипендию; учатся только на «хорошо» и «отлично»; учатся только на «отлично»;\n";
        cout << "8. Вывод данных о студентах, имеющих номер в списке – k.\n";
        cout << "9. ИДЗ  - структура блюд из столовой.\n";
        cout << "0. Выход\n";
        cin >> choice;
        cout << endl;
        if (choice == 0) break;
        switch (choice)
        {
        case 1:
        {
            readStudents(masStudents, lineCount);
            createNewSt();
            sortAndNumerationByGroupSurnameName();
            break;
        }
        case 2:
        {
            readStudents(masStudents, lineCount);
            sortAndNumerationByGroupSurnameName();
            changeSt();
            WriteMasToFile(masStudents, lineCount);
            if (Del) 
            {
                WriteMasToFile(masStudents, lineCount - 1);
            }
            break;
        }

        case 3:
        {
            readStudents(masStudents, lineCount);
            //WriteMasToFile(masStudents, lineCount);
            //copy(masStudents, masStudents + MAX_STUDENTS, sortedBySurnameStudents);
            sortAndNumerationByGroupSurnameName();
            WriteMasToFile(masStudents, lineCount);
            printStud(masStudents);
            break;
        }
        case 4:
        {
            readStudents(masStudents, lineCount);
            sortAndNumerationByGroupSurnameName();
            WriteMasToFile(masStudents, lineCount);
            printGroup();
            break;
        }

        case 5:
        {
            readStudents(masStudents, lineCount);
            WriteMasToFile(masStudents, lineCount);
            copy(begin(masStudents), end(masStudents), begin(sortedMasStudents));
            sortBySrArifm();
            /*printStud(sortedMasStudents);*/
            break;
        }

        case 6:
        {
            readStudents(masStudents, lineCount);
            sortAndNumerationByGroupSurnameName();
            WriteMasToFile(masStudents, lineCount);
            countMandW();
            break;

        }

        case 7:
        {
            readStudents(masStudents, lineCount);
            sortAndNumerationByGroupSurnameName();
            WriteMasToFile(masStudents, lineCount);
            whoLearning_1_2_3_Variations();
            break;

        }

        case 8:
        {
            readStudents(masStudents, lineCount);
            sortAndNumerationByGroupSurnameName();
            WriteMasToFile(masStudents, lineCount);
            haveNumberK();
            break;

        }
        case 9:
        {
            createDish();
            printDish();
            CreateOrder();
        }

        }
    }
}

