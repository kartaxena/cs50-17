import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""
        self.positives = []
        self.negatives = []
        with open('positive-words.txt') as pos:
            for wp in pos:
                if wp.startswith(';'):
                    pass
                else:
                    self.positives.append(wp.strip())
                
        with open('negative-words.txt') as neg:
            for wn in neg:
                if wn.startswith(';'):
                    pass
                else:
                    self.negatives.append(wn.strip())

    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        score = 0
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)
        for word in tokens:
            if word.lower() in self.positives:
                score += 1
            elif word.lower() in self.negatives:
                score -= 1
            else:
                score += 0
                
                
        return score
