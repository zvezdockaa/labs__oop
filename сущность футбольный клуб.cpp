// сущность футбольный клуб.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
class Football_Club { //футбольный клуб
public:
    std::string name_of_club; //название клуба
    int number_of_players; //количество игроков
    std::string stadium;// стадион
    std::string coach; // тренер
    int points; // очки
private:
    int money; // бюджет клуба
    std::string owner; // владелец
    bool mood; // настрой игроков
};

class Player {
public:
    std::string name_of_player{}; //имя игрока
    int age; //возраст игрока
    int height; //рост игрока
    int number_of_player; //номер игрока
    int salary; //зарплата
    friend Player_Type1;
    void Gde_Igraet(Football_Club& obj);
    
};
bool operator < (Player c1, Player c2)
{
    return c1.salary < c2.salary;
}

void Player::Gde_Igraet(Football_Club& obj) {
    obj.name_of_club;
}
class Player_Type1 {
public:
    std::string surname;//фамилия игрока
    int reiting; //рейтинг игрока
    std::string citizenship;//гражданство игрока
    int agee; //возраст игрока
};
class Midfielder : public Player { //игрок полузащитник, его показатели
public:
    float pace; //скорость игрока
    int acceleration; //ускорение
    int dribbling; //дриблинг, обводки
    float long_range_strikes; //дальние удары
    int passes; //пасы
};
class Defender : public Player_Type1 { //игрок защитник
public:
    float stamina; //выносливость игрока
    int defence; //общий показатель игры в защите
    int speed; //скорость игрока
};
class Forward : public Midfielder { //нападающий
public:
    float finishing; //завершение ударов
    int agility; //ловкость
    int balance; //баланс
    int head_play; //игра головой
};
class GoalKeeper : public Defender { //вратарь
public:
    int reflexes; //рефлексы
    int diving; //нырки
    int handling; //игра руками
    int kicking; //игра ногами
};

int main()
{
    std::cout << "Hello World!\n";
    
   /* Player player1{ .name_of_player{"Ivanov"},
        .age = 17, .height = 190, .number_of_player = 5, .salary = 19000 };*/

    
    





}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
