#include <iostream>
#include <string>
#include <ranges>

class Young_Player {
public:
    std::string name;
    std::string position;
    int age;

    void train() {
        std::cout << name << " - " << position << ": Тренировка..." << std::endl;
    }

    void play() {
        std::cout << name << " - " << position << ": Игра..." << std::endl;
    }
};

class FootballAcademy {

public:
    Young_Player** academyPlayers;
    int playerCount;

    // Фабричный метод для создания игрока
    Young_Player* createPlayer(const std::string& name, const std::string& position, int age) {
        Young_Player* player = new Young_Player();
        player->name = name;
        player->position = position;
        player->age = age;
        return player;
    }

    FootballAcademy() : academyPlayers(nullptr), playerCount(0) {}

    Young_Player* enrollPlayer(const std::string& name, const std::string& position, int age) {
        Young_Player* player = createPlayer(name, position, age);

        // Создание нового динамического массива с увеличенной емкостью
        Young_Player** newArray = new Young_Player * [playerCount + 1];

        // Копирование существующих игроков в новый массив
        for (int i = 0; i < playerCount; ++i) {
            newArray[i] = academyPlayers[i];
        }

        // Добавление нового игрока в массив
        newArray[playerCount] = player;

        // Удаление старого массива
        delete[] academyPlayers;

        // Установка указателя academyPlayers на новый массив
        academyPlayers = newArray;

        // Увеличение счетчика игроков
        ++playerCount;

        return player;
    }

    void trainAllPlayers() { //тренировка всех игроков
        for (int i = 0; i < playerCount; ++i) {
            academyPlayers[i]->train();
        }
    }

    void playAllPlayers() { //игра всех игроков
        for (int i = 0; i < playerCount; ++i) {
            academyPlayers[i]->play();
        }
    }

    ~FootballAcademy() { //деструктор
        for (int i = 0; i < playerCount; ++i) {
            delete academyPlayers[i];
        }
        delete[] academyPlayers;
    }
};

class Player { //класс для игрока взрослой команды
public:
    std::string name; // имя
    std::string position; // позиция
    int age, height, salary, pace, passes, acceleration, stamina, strike, physique, hand_play, footwork, defense; //различные характеристики
    int rating;

    void displayClub() {
        std::cout << "Текущий клуб: Манчестер сити" << std::endl;
    }
};

class FootballClub { //класс для футбольного клуба
public:
    std::string name; // название
    std::string stadium; // стадион
    Player* players; // игроки
    int playerCount; //количество игроков

    FootballClub(const std::string& name, const std::string& stadium) : name(name), stadium(stadium), players(nullptr), playerCount(0) {}

    void addPlayer(const std::string& name, const std::string& position, int age) {
        Player* newPlayer = new Player();
        newPlayer->name = name;
        newPlayer->position = position;
        newPlayer->age = age;

        Player* newArray = new Player[playerCount + 1];

        for (int i = 0; i < playerCount; ++i) {
            newArray[i] = players[i];
        }

        newArray[playerCount] = *newPlayer;

        delete[] players;

        players = newArray;
        ++playerCount;
    }

    void displayClubInfo() {
        std::cout << "Название клуба: " << name << std::endl;
        std::cout << "Стадион: " << stadium << std::endl;
    }

    class Iterator {
    public:
        Player* current;

        Iterator(Player* current) : current(current) {}

        Player& operator*() {
            return *current;
        }

        Iterator& operator++() {
            ++current;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() {
        return Iterator(players);
    }

    Iterator end() {
        return Iterator(players + playerCount);
    }

    template <typename Func>
    void checkPlayerAge(Func func) {
        for (int i = 0; i < playerCount; ++i) {
            if (func(players[i].age)) {
                std::cout << players[i].name << " меньше 41 года. " << std::endl;
            }
        }
    }
    template <typename Func> //сначала фильтрует, потом перебирает
    void checkPlayerAgeWithRanges(Func func) {
        auto playersRange = std::ranges::subrange(players, players + playerCount);
        auto ageCheckRange = playersRange | std::ranges::views::filter([func](const Player& player) {
            return func(player.age);
            });

        for (const Player& player : ageCheckRange) {
            std::cout << player.name << " меньше 41 года. " << std::endl;
        }
    }


    int calculatePlayerRating(const std::string& name, const std::string& position) { //высчитывает рейтинг игрока
        Player player;
        if (position == "Нападающий") {
            // Увеличивает удары и скорость для нападающего
            player.strike += 2;
            player.pace += 1;
        }
        else if (position == "Полузащитник") {
            // Увеличивает пасы и выносливость для полузащитников
            player.passes += 5;
            player.stamina += 7;
        }
        else if (position == "Защитник") {
            // Увеличивает защиту и выносливость для защитников
            player.defense += 8;
            player.stamina += 6;
        }
        else if (position == "Вратарь") {
            // Увеличивает игру руками и ногами для вратарей
            player.hand_play += 7;
            player.footwork += 4;
        }

        // Расчет рейтинга исходя из характеристик игроков
        int rating = 0;
        int totalCharacteristics = 0;

        if (position == "Нападающий") {
            rating += player.strike;
            rating += player.pace;
            totalCharacteristics += 2;
        }
        else if (position == "Полузащитник") {
            rating += player.passes;
            rating += player.stamina;
            totalCharacteristics += 2;
        }
        else if (position == "Защитник") {
            rating += player.defense;
            rating += player.stamina;
            totalCharacteristics += 2;
        }
        else if (position == "Вратарь") {
            rating += player.hand_play;
            rating += player.footwork;
            totalCharacteristics += 2;
        }

        if (totalCharacteristics > 0) {
            int averageRating = rating / totalCharacteristics;
            return averageRating;
        }

        // Если позиция не нападающий или защитник или полузащитник или вратарь
        return 0;
    }

    void TrainPlayer(Player* player) { //тренировка игрока, просто увеличивает рейтинг
        player->rating += 1;
    }

    void changePlayerPosition(const std::string& playerName, const std::string& currentPosition, const std::string& newPosition) { //смена позиции игроков
        // поиск игрока
        for (int i = 0; i < playerCount; ++i) {
            if (players[i].name == playerName) {
                // смена позиции
                players[i].position = newPosition;
                std::cout << playerName << " поменял позицию с  " << currentPosition << " на " << newPosition << std::endl;
                return;
            }
        }

        // игрок не найден
        std::cout << "Игрок не найден." << std::endl;
    }

    // Реализация мементо для состояния клуба
    class ClubMemento {
    public:
        std::string name;
        std::string stadium;
        Player* players;
        int playerCount;

        ClubMemento(const std::string& name, const std::string& stadium, Player* players, int playerCount)
            : name(name), stadium(stadium), players(players), playerCount(playerCount) {}
    };

    ClubMemento createMemento() {
        Player* playerArray = new Player[playerCount];
        std::copy(players, players + playerCount, playerArray);
        return ClubMemento(name, stadium, playerArray, playerCount);
    }

    void restoreMemento(const ClubMemento& memento) {
        name = memento.name;
        stadium = memento.stadium;
        players = memento.players;
        playerCount = memento.playerCount;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    FootballClub club("Манчестер Сити", "Стадион Этихад");

    Player player1;
    player1.name = "Эдерсон";
    player1.position = "Вратарь";
    player1.age = 28;
    player1.height = 188;
    player1.salary = 150000;
    club.addPlayer(player1.name, player1.position, player1.age);

    Player player2;
    player2.name = "Кайл Уокер";
    player2.position = "Защитник";
    player2.age = 31;
    player2.height = 183;
    player2.salary = 125000;
    club.addPlayer(player2.name, player2.position, player2.age);

    Player player3;
    player3.name = "Эрлинг Холланд";
    player3.position = "Нападающий";
    player3.age = 22;
    player3.height = 194;
    player3.salary = 200000;
    club.addPlayer(player3.name, player3.position, player3.age);

    Player player4;
    player4.name = "Кевин Де Брейне";
    player4.position = "Полузащитник";
    player4.age = 22;
    player4.height = 194;
    player4.salary = 200000;
    club.addPlayer(player4.name, player4.position, player4.age);

    club.displayClubInfo();
    club.TrainPlayer(&club.players[0]);
    club.TrainPlayer(&club.players[1]);
    club.TrainPlayer(&club.players[2]);
    club.changePlayerPosition("Эрлинг Холланд", "Нападающий", "Полузащитник");
    club.checkPlayerAge([](int age) { return age < 41; });
    club.checkPlayerAgeWithRanges([](int age) { return age < 41; });

    FootballAcademy academy;

    Young_Player* uplayer1 = academy.createPlayer("Борхес Борк", "Нападающий", 18);
    Young_Player* uplayer2 = academy.createPlayer("Джеймс МакКейти", "Полузащитник", 17);
    Young_Player* uplayer3 = academy.createPlayer("Рико Льюис", "Защитник", 16);
    Young_Player* uplayer4 = academy.createPlayer("Джон Траффорд", "Вратарь", 19);

    academy.trainAllPlayers();

    return 0;
}