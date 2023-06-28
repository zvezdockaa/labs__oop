#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ranges>

template <typename T>
class MyContainer {
    T* data;
    size_t container_size;
    size_t container_capacity;

    void ensure_capacity(size_t new_size) {
        if (new_size > container_capacity) {
            container_capacity = container_capacity + container_capacity / 2 + 1;
            T* new_data = new T[container_capacity];
            for (size_t i = 0; i < container_size; ++i) {
                new_data[i] = std::move(data[i]);
            }
            delete[] data;
            data = new_data;
        }
    }
    class Iterator {
        T* ptr;

    public:
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;

        Iterator() : ptr(nullptr) {}
        explicit Iterator(pointer p) : ptr(p) {}

        reference operator*() const { return *ptr; }
        pointer operator->() const { return ptr; }
        reference operator[](difference_type n) const { return *(ptr + n); }

        Iterator& operator++() { ++ptr; return *this; }
        Iterator& operator--() { --ptr; return *this; }
        Iterator operator++(int) { Iterator tmp(*this); ++ptr; return tmp; }
        Iterator operator--(int) { Iterator tmp(*this); --ptr; return tmp; }

        Iterator& operator+=(difference_type n) { ptr += n; return *this; }
        Iterator& operator-=(difference_type n) { ptr -= n; return *this; }

        friend Iterator operator+(const Iterator& it, difference_type n) { return Iterator(it.ptr + n); }
        friend Iterator operator+(difference_type n, const Iterator& it) { return it + n; }
        friend Iterator operator-(const Iterator& it, difference_type n) { return Iterator(it.ptr - n); }
        friend Iterator operator-(const Iterator& it1, const Iterator& it2) { return Iterator(it1.ptr - it2.ptr); }

        friend bool operator==(const Iterator& it1, const Iterator& it2) { return it1.ptr == it2.ptr; }
        friend bool operator!=(const Iterator& it1, const Iterator& it2) { return !(it1 == it2); }
        friend bool operator<(const Iterator& it1, const Iterator& it2) { return it1.ptr < it2.ptr; }
        friend bool operator>(const Iterator& it1, const Iterator& it2) { return it2 < it1; }
        friend bool operator<=(const Iterator& it1, const Iterator& it2) { return !(it2 < it1); }
        friend bool operator>=(const Iterator& it1, const Iterator& it2) { return !(it1 < it2); }
    };

public:
    MyContainer()
        : data(nullptr), container_size(0), container_capacity(0)
    {}
    Iterator begin() { return Iterator(data); }
    Iterator end() { return Iterator(data + container_size); }
    const Iterator begin() const { return Iterator(data); }
    const Iterator end() const { return Iterator(data + container_size); }

    //копирование конструктора
    MyContainer(const MyContainer<T>& other)
        : data(new T[other.container_size]),
        container_size(other.container_size),
        container_capacity(other.container_capacity)
    {
        std::copy(other.data, other.data + other.container_size, data);
    }

    //перемещение конструктора
    MyContainer(MyContainer<T>&& other)
        : data(other.data),
        container_size(other.container_size),
        container_capacity(other.container_capacity)
    {
        other.data = nullptr;
        other.container_size = 0;
        other.container_capacity = 0;
    }

    // Copy assignment operator
    MyContainer<T>& operator=(const MyContainer<T>& other) {
        if (this != &other) {
            MyContainer<T> tmp(other);
            std::swap(this->data, tmp.data);
            std::swap(this->container_size, tmp.container_size);
            std::swap(this->container_capacity, tmp.container_capacity);
        }
        return *this;
    }

    // оператор присваивания
    MyContainer<T>& operator=(MyContainer<T>&& other) {
        std::swap(this->data, other.data);
        std::swap(this->container_size, other.container_size);
        std::swap(this->container_capacity, other.container_capacity);
        return *this;
    }

    ~MyContainer() {
        delete[] data;
    }

    size_t size() const {
        return container_size;
    }

    bool empty() const {
        return container_size == 0;
    }

    void push_back(const T& value) {
        ensure_capacity(container_size + 1);
        data[container_size++] = value;
    }

    void push_back(T&& value) {
        ensure_capacity(container_size + 1);
        data[container_size++] = std::move(value);
    }

    void erase(size_t index) {
        if (index >= container_size) {
            throw std::out_of_range("Index is out of range");
        }
        for (size_t i = index + 1; i < container_size; ++i) {
            data[i - 1] = std::move(data[i]);
        }
        --container_size;
    }
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
            if (func(player)) {
                std::cout << player.getName() << "меньше 41 года" << std::endl;
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


