import random


class Football_Club():
    name="Monako"
    coach= "Phil"
    staduim ="Lui 2"
    number_of_players= 36
    points= 90
    def Gde_Igraet(self):
        if(self.points > 89):
            print(self.name+" plays in Champions League")

class Player():
    name_of_player= "Sashka Golovin"
    pace= 90
    salary= 30000

class Midfielder(Player):
    acceleration= 80
    dribbling= 79
    long_range_strikes= 89
    passes= 90

def decorator(func):
    def inner():
        print(Player.name_of_player + ' plays in ' + Football_Club.name)
        func()
        print(Player.name_of_player + ' pace is ' + str(Midfielder.pace))

    return inner


def evolution():
    traits_names=['acceleration', 'dribbling', 'pace', 'long-range strikes']
    traits=[Midfielder.acceleration, Midfielder.dribbling, Midfielder.pace, Midfielder.long_range_strikes]
    for i in range(0, len(traits_names)):
        traits[0] += 4
        traits[1] += 3
        traits[2] += 5
        traits[3] += 0.5
        print('Player ' + str(traits_names[i]) +' will be ' + str(traits[i]))
    #print('Player acceleration will be ' + str(Midfielder.acceleration))
    #print('Player dribbling will be ' + str(Midfielder.dribbling))
    print('Player talent is ' + random.choice(Midfielder.talents))

d = decorator(evolution)
d()
