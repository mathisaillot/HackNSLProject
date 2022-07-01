import json
import random

# Data
draw = {}
colors = ['pink','purple','blue','green']
cards = ['under_square','under_circle','under_pentagon','under_triangle','under_joker','over_square','over_circle','over_pentagon','over_triangle','over_joker','deviation']

# Run
random.shuffle(colors)
for color in colors:
    random.shuffle(cards)
    under,i = 0,0
    lst = []
    while under < 5:
        lst.append(cards[i])
        if cards[i].startswith('under_'):
            under+=1
        i+=1
    draw[color] = lst

with open('cards.json', 'w', encoding='utf-8') as f:
    json.dump(draw, f, indent=4)
