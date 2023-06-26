#include <iostream>  
#include <string>  
#include <vector>  
#include <ranges>  

class Young_Player { //молодой игрок, игрок академии
private:
    std::string name;
    std::string position;
    int age;

public:
    Young_Player(const std::string& playerName, const std::string& playerPosition, int playerAge) //конструктор класса
        : name(playerName), position(playerPosition), age(playerAge) {}

    void train() {
        std::cout << name << " - " << position << ": Тренировка..." << std::endl; //тренировка
    }

    void play() {
        std::cout << name << " - " << position << ": Игра..." << std::endl; //игра
    }
};

class FootballAcademy { //футбольная академия
private:
    std::vector<Young_Player*> academyPlayers;

    Young_Player* createPlayer(const std::string& name, const std::string& position, int age) { //создание игрока
        Young_Player* player = new Young_Player(name, position, age);
        return player;
    }

public:
    ~FootballAcademy() {
        for (Young_Player* player : academyPlayers) {
            delete player;
        }
    }

    Young_Player* enrollPlayer(const std::string& name, const std::string& position, int age) { //зачисление в академию, внедрение в состав
        Young_Player* player = createPlayer(name, position, age);
        academyPlayers.push_back(player);
        return player;
    }

    void trainAllPlayers() { //тренировка всех игроков
        for (Young_Player* player : academyPlayers) {
            player->train();
        }
    }

    void playAllPlayers() { //игра всех игроков
        for (Young_Player* player : academyPlayers) {
            player->play();
        }
    }
};

class Player { //игрок взрослой команды
private:
    std::string name;
    std::string position;
    int age, height, salary, pace, passes, acceleration, stamina, strike, physique, hand_play, footwork, defense; //характеристики
    int rating;//рейтинг игрока

public:
    Player(const std::string& playerName, const std::string& playerPosition, int playerAge) //конструктор класса
        : name(playerName), position(playerPosition), age(playerAge),
        height(0), salary(0), pace(0), passes(0), acceleration(0), stamina(0),
        strike(0), physique(0), hand_play(0), footwork(0), defense(0), rating(0) {}

    void displayClub() {
        std::cout << "Текущий клуб: Манчестер сити" << std::endl;
    }

    // геттеры
    std::string getName() const {
        return name;
    }

    std::string getPosition() const {
        return position;
    }

    int getAge() const {
        return age;
    }

    // сеттеры
    void setName(const std::string& newName) {
        name = newName;
    }

    void setPosition(const std::string& newPosition) {
        position = newPosition;
    }

    void setAge(int newAge) {
        age = newAge;
    }

    int calculatePlayerRating() { //вычисление рейтинга
        if (position == "Нападающий") {
            rating = (strike + pace) / 2;
        }
        else if (position == "Полузащитник") {
            rating = (passes + stamina) / 2;
        }
        else if (position == "Защитник") {
            rating = (defense + stamina) / 2;
        }
        else if (position == "Вратарь") {
            rating = (hand_play + footwork) / 2;
        }

        return rating;
    }

    void TrainPlayer() { //тренировка
        rating += 1;
    }

    void changePlayerPosition(const std::string& newPosition) { //поменять позицию в коде
        position = newPosition;
    }
};

class FootballClub { //футбольный клуб
private:
    std::string name;
    std::string stadium;
    std::vector<Player> players;

public:
    void addPlayer(const std::string& name, const std::string& position, int age) {
        players.emplace_back(name, position, age);
    }

    void displayClubInfo() {
        std::cout << "Название клуба: " << name << std::endl;
        std::cout << "Стадион: " << stadium << std::endl;
    }

    template <typename Func> //концепт для ограничения возраста
    void checkPlayerAge(Func func) {
        for (const Player& player : players) {
            if (func(player.getAge())) {
                std::cout << player.getName() << " меньше 41 года." << std::endl;
            }
        }
    }

    template <typename Func> //ограничение возраста с ranges
    void checkPlayerAgeWithRanges(Func func) {
        std::vector<Player> ageCheckRange;
        std::copy_if(players.begin(), players.end(), std::back_inserter(ageCheckRange), [func](const Player& player) {
            return func(player.getAge());
            });

        for (const Player& player : ageCheckRange) {
            std::cout << player.getName() << " меньше 41 года. " << std::endl;
        }
    }

    void TrainPlayer(Player& player) { //тренировка игрока
        player.TrainPlayer();
    }

    void changePlayerPosition(const std::string& playerName, const std::string& newPosition) { //смена позиции
        for (Player& player : players) {
            if (player.getName() == playerName) {
                player.changePlayerPosition(newPosition);
                std::cout << playerName << " поменял позицию с " << player.getPosition() << " на " << newPosition << std::endl;
                return;
            }
        }

        std::cout << "Игрок не найден." << std::endl;
    }

    class ClubMemento { //мементо для отслеживания состояния клуба
    private:
        std::string name;
        std::string stadium;
        std::vector<Player> players;

    public:
        ClubMemento(const std::string& name, const std::string& stadium, const std::vector<Player>& players)
            : name(name), stadium(stadium), players(players) {}

        std::string getName() const {
            return name;
        }

        std::string getStadium() const {
            return stadium;
        }

        std::vector<Player> getPlayers() const {
            return players;
        }
    };

    ClubMemento createMemento() {
        return ClubMemento(name, stadium, players);
    }
};

class LegacyIterator { //итератор 
public:
    virtual void first() = 0; //первый элемент
    virtual void next() = 0; //следующий элемент
    virtual bool isDone() = 0; //проверка, дошел ли до конца
    virtual Player currentItem() = 0; //текущий элемент
};

class PlayerIterator : public LegacyIterator {
private:
    std::vector<Player>& players;
    int index;

public:
    PlayerIterator(std::vector<Player>& players) : players(players), index(0) {}

    void first() override {
        index = 0;
    }

    void next() override {
        ++index;
    }

    bool isDone() override {
        return index >= players.size();
    }

    Player currentItem() override {
        return players[index];
    }
};

template <typename T>
class Container { //контейнер
public:
    virtual LegacyIterator* createIterator() = 0;
};

class FootballClubContainer : public Container<Player> { //контейнер для футбольного клуба
private:
    std::vector<Player>& players;

public:
    FootballClubContainer(std::vector<Player>& players) : players(players) {}

    LegacyIterator* createIterator() override {
        return new PlayerIterator(players);
    }
};

    int main() {
        FootballClub manchesterCity;
        manchesterCity.addPlayer("Эрлинг Холланд", "Нападающий", 27);
        manchesterCity.addPlayer("Кевин Де Брюйне", "Полузащитник", 30);
        manchesterCity.addPlayer("Джон Стоунз", "Защитник", 27);
        manchesterCity.addPlayer("Эдерсон", "Вратарь", 28);

        manchesterCity.displayClubInfo();
        manchesterCity.TrainPlayer(manchesterCity.createMemento().getPlayers()[0]);
        manchesterCity.TrainPlayer(manchesterCity.createMemento().getPlayers()[1]);

        auto func = [](int age) { return age < 41; };

        manchesterCity.checkPlayerAge(func);
        manchesterCity.checkPlayerAgeWithRanges(func);

        std::vector<Player> players = manchesterCity.createMemento().getPlayers();
        FootballClubContainer clubContainer(players);
        LegacyIterator* iterator = clubContainer.createIterator();

        for (iterator->first(); !iterator->isDone(); iterator->next()) {
            Player player = iterator->currentItem();
            std::cout << "Имя: " << player.getName() << ", Позиция: " << player.getPosition() << std::endl;
        }

        delete iterator;

        return 0;
    }
