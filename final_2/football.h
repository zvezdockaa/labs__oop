#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ranges>

class Young_Player {
private:
    std::string name;
    std::string position;
    int age;

public:
    Young_Player(const std::string& playerName, const std::string& playerPosition, int playerAge)
        : name(playerName), position(playerPosition), age(playerAge) {}

    void train() {
        std::cout << name << " - " << position << ": Тренировка..." << std::endl;
    }

    void play() {
        std::cout << name << " - " << position << ": Игра..." << std::endl;
    }
};

class FootballAcademy {
private:
    std::vector<Young_Player*> academyPlayers;

    Young_Player* createPlayer(const std::string& name, const std::string& position, int age) {
        Young_Player* player = new Young_Player(name, position, age);
        return player;
    }

public:
    ~FootballAcademy() {
        for (Young_Player* player : academyPlayers) {
            delete player;
        }
    }

    Young_Player* enrollPlayer(const std::string& name, const std::string& position, int age) {
        Young_Player* player = createPlayer(name, position, age);
        academyPlayers.push_back(player);
        return player;
    }

    void trainAllPlayers() {
        for (Young_Player* player : academyPlayers) {
            player->train();
        }
    }

    void playAllPlayers() {
        for (Young_Player* player : academyPlayers) {
            player->play();
        }
    }
};

class Player {
private:
    std::string name;
    std::string position;
    int age, height, salary, pace, passes, acceleration, stamina, strike, physique, hand_play, footwork, defense;
    int rating;

public:
    Player(const std::string& playerName, const std::string& playerPosition, int playerAge)
        : name(playerName), position(playerPosition), age(playerAge),
        height(0), salary(0), pace(0), passes(0), acceleration(0), stamina(0),
        strike(0), physique(0), hand_play(0), footwork(0), defense(0), rating(0) {}

    void displayClub() {
        std::cout << "Текущий клуб: Манчестер сити" << std::endl;
    }

    std::string getName() const {
        return name;
    }

    std::string getPosition() const {
        return position;
    }

    int getAge() const {
        return age;
    }

    void setName(const std::string& newName) {
        name = newName;
    }

    void setPosition(const std::string& newPosition) {
        position = newPosition;
    }

    void setAge(int newAge) {
        age = newAge;
    }

    int calculatePlayerRating() {
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

    void TrainPlayer() {
        rating += 1;
    }

    void changePlayerPosition(const std::string& newPosition) {
        position = newPosition;
    }
};

class FootballClub {
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

    template <typename Func>
    void checkPlayerAge(Func func) {
        for (const Player& player : players) {
            if (func(player.getAge())) {
                std::cout << player.getName() << " меньше 41 года." << std::endl;
            }
        }
    }

    template <typename Func>
    void checkPlayerAgeWithRanges(Func func) {
        std::vector<Player> ageCheckRange;
        std::copy_if(players.begin(), players.end(), std::back_inserter(ageCheckRange), func);

        for (const Player& player : ageCheckRange) {
            std::cout << player.getName() << " меньше 41 года. " << std::endl;
        }
    }

    void TrainPlayer(Player& player) {
        player.TrainPlayer();
    }

    void changePlayerPosition(const std::string& playerName, const std::string& newPosition) {
        for (Player& player : players) {
            if (player.getName() == playerName) {
                player.changePlayerPosition(newPosition);
                std::cout << playerName << " поменял позицию с " << player.getPosition() << " на " << newPosition << std::endl;
                return;
            }
        }

        std::cout << "Игрок не найден." << std::endl;
    }

    class ClubMemento {
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

class LegacyIterator {
public:
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() = 0;
    virtual Player currentItem() = 0;
};

class PlayerIterator : public LegacyIterator {
private:
    const std::vector<Player>& players;
    int index;

public:
    PlayerIterator(const std::vector<Player>& players) : players(players), index(0) {}

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
class Container {
public:
    virtual LegacyIterator* createIterator() = 0;
};

class FootballClubContainer : public Container<Player> {
private:
    const std::vector<Player>& players;

public:
    FootballClubContainer(const std::vector<Player>& players) : players(players) {}

    LegacyIterator* createIterator() override {
        return new PlayerIterator(players);
    }
};
