sum = float(input('How much change is owed? '))

while sum <= 0:
    sum = float(input('How much change is owed? '))

cent_sum = int(round(sum * 100))
coin = 0
quot = 25
dec = 10
fi = 5
one = 1
while cent_sum > 0:
    if cent_sum >= quot:
        zalysh = cent_sum % quot
        coin += (cent_sum - zalysh) / quot
        cent_sum = zalysh
    elif cent_sum >= dec:
        zalysh = cent_sum % dec
        coin += (cent_sum - zalysh) / dec
        cent_sum = zalysh
    elif cent_sum >= fi:
        zalysh = cent_sum % fi
        coin += (cent_sum - zalysh) / fi
        cent_sum = zalysh
    elif cent_sum >= one:
        zalysh = cent_sum % one
        coin += (cent_sum - zalysh) / one
        cent_sum = zalysh
print(int(coin))