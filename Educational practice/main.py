import requests
from bs4 import BeautifulSoup

def parse():
    URL = "https://coinmarketcap.com"
    HEADERS = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:97.0) Gecko/20100101 Firefox/97.0"
    }

    num = 10
    list = []

    r = requests.get(URL, headers = HEADERS)
    soup = BeautifulSoup(r.text, 'html.parser')
    body = soup.find('tbody')
    items = body.find_all('tr')

    for i,it in enumerate(items):
        if (i < num):
            list.append({
                'title' : it.find("p", class_ = "sc-1eb5slv-0 iworPT").text,
                'price' : it.find("div", class_="sc-131di3y-0 cLgOOr").text,
                'market cap': it.find("span", "sc-1ow4cwt-1 ieFnWP").text
            })
        else: break
    return (num, list)


def search(n, list_):
    print()
    name = input('Enter name cripto: ')
    i = 0
    print()
    while(i < n):
        if (name == str(list_[i]['title'])):
            print('Data about the found cryptocurrency:')
            print('%-16s %-13s %-20s' % ('Name' , 'Price', 'Market cap'))
            print('%-16s %-13s %-20s' % (list_[i]['title'], list_[i]['price'], list_[i]['market cap']))
            break
        i += 1
        if (i == (n-1)):
            print('Error: Element not found')
        

def output_all(n, list_):
    print()
    print('%-16s %-13s %-20s' % ('     Name', '     Price', '     Market cap'))
    for i,it in enumerate(list_):
        if (i < n):
            print('%2s %s %-16s %-13s %-20s' % (i+1 , ')', list_[i]['title'], list_[i]['price'], list_[i]['market cap']))
        else: break


#main
flag = True
n, list_ = parse()
while (flag == True):
    print('Enter "1" to output all the elements')
    print('Enter "2" to start the search')
    print('Enter "3" to exit')
    comand = input('Enter: ')
    if (comand == '1'):
        output_all(n, list_)
    elif(comand == '2'):
        search(n, list_)
    elif(comand == '3'):
        flag = False
    print()
