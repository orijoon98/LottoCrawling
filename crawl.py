import urllib.request
import ssl
from bs4 import BeautifulSoup

def newLotto():
    try:
        _create_unverified_https_context = ssl._create_unverified_context
    except AttributeError:
    # Legacy Python that doesn't verify HTTPS certificates by default
        pass
    else:
    # Handle target environment that doesn't support HTTPS verification
        ssl._create_default_https_context = _create_unverified_https_context

    url = 'https://dhlottery.co.kr/gameResult.do?method=byWin&wiselog=H_C_1_1'
    html = urllib.request.urlopen(url).read()
    soup = BeautifulSoup(html, 'html.parser')

    text = ""

    for meta in soup.head.find_all('meta'):
        text += str(meta.get('content'))
        text += '\n'
    # print(text)

    index = 0
    numbers = []
    flag = False

    for x in text:
        if x >= '0'and x <= '9':
            if flag == False:
                numbers.append("")
            numbers[index] += str(x)
            flag = True
        else:
            if flag == True: 
                index += 1
                flag = False

    print(numbers)
    # numbers index 별 정보
    # 0 : 회차
    # 1 ~ 6 : 당첨 번호
    # 7 : 보너스 번호
    # 9 : 1등 당첨 인원 수
    # 11 ~ end : 1등 1인당 당첨 금액

    f = open('/Users/orijoon98/Desktop/GitHub/LottoCrawling/lotto.txt', 'w')
    for num in numbers:
        f.write(num + ' ')
    f.close()



