from flask import Flask
import serial  # 导入串口包
import requests

app = Flask(__name__)

ser = serial.Serial("COM5", 9600, timeout=5)  # 开启com5口，波特率9600，超时5
ser.flushInput()  # 清空缓冲区


@app.route("/buzz")
def buzz():
    ser.write('a'.encode())
    print("蜂鸣器响")
    return "succeed"


@app.route("/read")
def read():
    count = ser.inWaiting()  # 获取串口缓冲区数据
    if count != 0:
        recv = ser.read(ser.in_waiting).decode("gbk")  # 读出串口数据，数据采用gbk编码
        index = recv.find('Temperature', 0, len(recv))
        if index != -1:
            temstr = recv[index + 18: index + 20]
            print(temstr)
            data = '{"device":"arduino","readings":[{"name":"temperature","value":"' + str(temstr) + '"}]}'
            headers = {'Content-Type': 'application/json'}
            rep = requests.post(url='http://127.0.0.1:48080/api/v1/event', data=data, headers=headers)
            print(rep)
    return temstr


if __name__ == '__main__':
    app.run(host="172.19.183.136", port=5000)
