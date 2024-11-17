# authors:
# 1. Mardo Parlayan S5578566 m.parlayan@student.rug.nl
# 2. Elizabeth verbruggen S4540212 e.f.verbruggen@student.rug.nl
# 3. Julian Wierenga S5628237 j.d.p.l.wierenga@student.rug.nl

def read_input():
    a = int(input())
    b = int(input())
    text = ""
    while True:
        try:
            line = input()
            text += line
        except EOFError:
            break
    return a, b, text

def clean_text(text):
    cleaned_text = ""
    for letter in text:
        if letter.isalpha():
            cleaned_text += letter.lower()
    return cleaned_text

def find_frequencies(text):
    frequencies = [0] * 26
    for letter in text:
        frequencies[ord(letter) - 97] += 1
    return frequencies

def find_key(a, b, text):
    sd_sums = [""] * (b - a + 1)
    for possible_key_size in range(a, b + 1):
        vectors = ["" for _ in range(possible_key_size)]
        sd_sum = 0
        for j in range(len(text)):
            vectors[j % possible_key_size] += text[j]
        for vector in vectors:
            frequencies = find_frequencies(vector)
            sd = (sum([frequencies[i] ** 2 for i in range(26)]) / 26 - (sum([frequencies[i] for i in range(26)]) / 26) ** 2) ** 0.5
            sd_sum += sd
        sd_sums[possible_key_size - a] = sd_sum 
    for key_size in range(a, b + 1):
        print(f"The sum of {key_size} std. devs: {sd_sums[key_size - a]:.2f}")
    key_size = sd_sums.index(max(sd_sums)) + a
    key = [""] * key_size
    for i in range(key_size):
        letter_vector = ""
        for j in range(i, len(text), key_size):
            letter_vector += text[j]
        frequencies = find_frequencies(letter_vector)
        most_frequent_letter = frequencies.index(max(frequencies))
        shift = (most_frequent_letter - 4)
        new_letter = (shift % 26) + 97
        key[i] = chr(new_letter)
    print(f"\nKey guess:\n{''.join(key)}")

a, b, text = read_input()
text = clean_text(text)
find_key(a, b, text)