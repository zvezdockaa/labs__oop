#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ranges>

template <typename T>
class ContainerIterator {
public:
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;

    // конструктор
    explicit ContainerIterator(pointer ptr) : ptr_(ptr) {}

    // oператор разыменования
    reference operator*() const {
        return *ptr_;
    }

    // пре инкремент
    ContainerIterator& operator++() {
        ++ptr_;
        return *this;
    }

    // пост-инкремент
    ContainerIterator operator++(int) {
        ContainerIterator iterator = *this;
        ++(*this);
        return iterator;
    }

    // проверка равенства
    bool operator==(const ContainerIterator& other) const {
        return ptr_ == other.ptr_;
    }

    // проверка неравенства
    bool operator!=(const ContainerIterator& other) const {
        return !(*this == other);
    }

private:
    pointer ptr_;
};

template <typename T>
class Container {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = ContainerIterator<T>;
    using const_iterator = ContainerIterator<const T>;
    using difference_type = std::ptrdiff_t;
    using size_type = std::size_t;

    // конструктор по умолчанию
    Container() = default;

    // конструктор копирования
    Container(const Container& other) : data_(other.data_) {}

    // консруктор перемещения
    Container(Container&& other) noexcept : data_(std::move(other.data_)) {}

    // Copy assignment operator
    Container& operator=(const Container& other) {
        if (this != &other) {
            data_ = other.data_;
        }
        return *this;
    }

    // перемещение оператора присваивания
    Container& operator=(Container&& other) noexcept {
        if (this != &other) {
            data_ = std::move(other.data_);
        }
        return *this;
    }

    // деструктор
    ~Container() = default;

    // начало
    iterator begin() {
        return iterator(data_.data());
    }

    // конец
    iterator end() {
        return iterator(data_.data() + data_.size());
    }

    // константный итератор
    const_iterator begin() const {
        return const_iterator(data_.data());
    }

    // 
    const_iterator end() const {
        return const_iterator(data_.data() + data_.size());
    }

    // оператор проверки равенства
    bool operator==(const Container& other) const {
        return data_ == other.data_;
    }

    // оператор проверки неравенства
    bool operator!=(const Container& other) const {
        return !(*this == other);
    }

    // обмен содержимого контейнера
    void swap(Container& other) {
        std::swap(data_, other.data_);
    }

    // кол-во элементов в контейнере
    size_type size() const {
        return data_.size();
    }

    // макс кол-во элементов в контейнере
    size_type max_size() const {
        return data_.max_size();
    }

    // проверка на пустоту
    bool empty() const {
        return data_.empty();
    }

private:
    std::vector<T> data_;
};


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
    Container<Player> players;

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
            if (func(player)) {
                std::cout << player.getName() << " меньше 41 года" << std::endl;
            }
        }
    }

    template <typename Func>
    void checkPlayerAgeWithRanges(Func func) {
        std::vector<Player> ageCheckRange;
        std::copy_if(players.begin(), players.end(), std::back_inserter(ageCheckRange), func);

        for (const Player& player : ageCheckRange) {
            std::cout << player.getName() << " меньше 41 года" << std::endl;
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


