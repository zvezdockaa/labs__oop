class FootballClub:
    def __init__(self):
        self.players = []

    def add_player(self, player):
        self.players.append(player)

    def __iter__(self):  #возвращает сам объект, который является итератором
        self.index = 0
        return self

    def __next__(self): #возвращает следующего игрока в списке, и при достижении конца списка вызывает исключение
        if self.index >= len(self.players):
            raise StopIteration
        player = self.players[self.index]
        self.index += 1
        return player


club = FootballClub()
club.add_player("Lionel Messi")
club.add_player("Cristiano Ronaldo")
club.add_player("Neymar")
for player in club:
    print(player)