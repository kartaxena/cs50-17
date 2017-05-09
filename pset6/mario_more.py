while True:
    h = int(input('Input height:'))
    if 0 < h < 24:
        break
for count in range(h):
    print((' ' * (h - count - 1)) + ('#' * count) + '#' + '  ' + ('#' * count) + '#')