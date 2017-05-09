import sys

if len(sys.argv) != 2 or int(sys.argv[1]) <= 0:
    print('false')
    exit(1)
    
key = int(sys.argv[1])
text = input('plaintext: ')

if text:
    print('ciphertext: ', end='')
    for i in range(len(text)):
        if text[i].isalpha() and text[i].isupper():
            code_text = ((ord(text[i]) - ord('A') + key) % 26) + ord('A')
            print(chr(code_text), end='')
        elif text[i].isalpha() and text[i].islower():
            code_text = ((ord(text[i]) - ord('a') + key) % 26) + ord('a')
            print(chr(code_text), end='')
        else:
            print(text[i], end='')
    print()
            
