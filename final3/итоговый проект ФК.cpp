#include <iostream>
#include "football.h"

int main() {
    FootballClub manchesterCity;
    manchesterCity.addPlayer("Kevin De Bruyne", "Полузащитник", 29);
    manchesterCity.addPlayer("Raheem Sterling", "Нападающий", 26);
    manchesterCity.addPlayer("Aymeric Laporte", "Защитник", 27);

    manchesterCity.displayClubInfo();

    // Создание экземпляра футбольной академии
    FootballAcademy academy;
    Young_Player* youngPlayer = academy.enrollPlayer("John Doe", "Защитник", 18);

    // Обучение и игра всех игроков
    academy.trainAllPlayers();
    academy.playAllPlayers();

    // Проверка возраста игроков в клубе
    manchesterCity.checkPlayerAge([](int age) { return age < 25; });

    // Изменение позиции игрока
    manchesterCity.changePlayerPosition("Kevin De Bruyne", "Атакующий полузащитник");

    // Сохранение состояния клуба
    FootballClub::ClubMemento memento = manchesterCity.createMemento();

    // Перебор игроков с использованием итератора


    return 0;
}