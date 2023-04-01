class FootballClub:
    def __init__(self, name=None, stadium=None, manager=None, formation=None):
        self.name = name #название
        self.stadium = stadium #стадион
        self.manager = manager #тренер
        self.formation = formation #схема игры

class FootballClubBuilder:
    def __init__(self):
        self.club = FootballClub()

    def set_name(self, name):
        self.club.name = name
        return self

    def set_stadium(self, stadium):
        self.club.stadium = stadium
        return self

    def set_manager(self, manager):
        self.club.manager = manager
        return self

    def set_formation(self, formation):
        self.club.formation = formation
        return self

    def build(self):
        return self.club

# Пример использования паттерна Builder
builder = FootballClubBuilder()
builder.set_name("AC Milan")
builder.set_stadium("San Siro")
builder.set_manager("Stefano Pioli")
builder.set_formation("4-2-3-1")
club = builder.build()
print(club.name)
print(club.stadium)
print(club.manager)
print(club.formation)