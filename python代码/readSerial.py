import time  # 导入时间包
import requests


def getTemperature():
    while True:
        requests.get("http://172.19.183.136:5000/read")
        time.sleep(3)  # 间隔


if __name__ == '__main__':
    getTemperature()
