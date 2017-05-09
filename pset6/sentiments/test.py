import nltk

negatives = []
positives = []
with open('negative-words.txt') as neg:
    for wn in neg:
        #print(len(neg))
        if wn.startswith(';'):
           pass
        else:
           negatives.append(wn.strip())
with open('positive-words.txt') as pos:
    for wp in pos:
        #print(len(neg))
        if wp.startswith(';'):
           pass
        else:
           positives.append(wp.strip())

text = '''
At eight o'clock on Thursday morning
... Arthur didn't feel very good.
'''
tokenizer = nltk.tokenize.TweetTokenizer(text)
c = tokenizer.tokenize(text)
for w in c:
    if w.lower() in positives:
        print(w, 1)
    elif w.lower() in negatives:
        print(w, -1)
    else:
        print(w, 0)