import crawl
import schedule
import time

# schedule.every(3).seconds.do(crawl.newLotto)
schedule.every().saturday.at("21:30").do(crawl.newLotto)

while True:
    schedule.run_pending()
    time.sleep(1)