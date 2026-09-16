import requests
def probability(content):
    dic = dict()
    
    for char in content:
        if char not in ['?', ',']:
            if char in dic:
                dic[char] += 1
            else:
                dic[char] = 0

    # sorting OMGGGGGGGG

    length = len(content)
    for char, freq in dic.items():
        print(char, freq, freq / length)

    dic = {k: dic[k] for k in sorted(dic)}
    for char, freq in reversed(dic.items()):
        print(char, freq, freq / length)
        

if __name__ == '__main__':
    url = input()

    content = requests.get(url)
    content = content.text
    probability(content)
    
