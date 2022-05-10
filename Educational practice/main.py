import requests
from bs4 import BeautifulSoup

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
            'reduction' : it.find("p", "sc-1eb5slv-0 gGIpIK coin-item-symbol").text,
            'price' : it.find("div", class_="sc-131di3y-0 cLgOOr").text,
            'market cap': it.find("span", "sc-1ow4cwt-1 ieFnWP").text
        })
    else: break
    print(list[i]['title'] + ' ', list[i]['reduction']+ '\t\t', list[i]['price']+ '\t\t', list[i]['market cap'])