import tensorflow as tf
from keras.models import load_model
from tkinter import *
import tkinter as tk
import win32gui
from PIL import ImageGrab, Image
import numpy as np
import struct
import time

model = load_model('seq_mnist.h5')

import codecs
import socket
import time
import binascii

server_ip = "192.168.3.18"  # "127.0.0.1"
server_udp_port = 4515
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.settimeout(5)


# sock.bind(('localhost', 4526))


def softmax(x):
    """Compute softmax values for each sets of scores in x."""
    e_x = np.exp(x - np.max(x))
    return e_x / e_x.sum()


def predict_digit(img):
    # изменение рзмера изобржений на 28x28
    img = img.convert('L')
    img = img.resize((28, 28))
    # конвертируем rgb в grayscale
    img = np.array(img)
    # изменение размерности для поддержки модели ввода и нормализации
    img = img.reshape(1, 784)
    sock.sendto(img, (server_ip, server_udp_port))
    res = []
    try:
        data, addr = sock.recvfrom(1024)
        data = struct.unpack('11f', data)
        print(data)
        res.append(data)
    except:
        print('Socket timeout off')

    ptime = time.time()  # start time
    img = img / 255.0
    img = abs(1 - img)
    # предсказание цифры
    res.append(model.predict([img])[0])
    # return np.argmax(res), max(res)
    ptime = round((time.time() - ptime) * 1000, 2)  # Время в милисекундах
    return res, ptime


class App(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)

        self.x = self.y = 0

        # Создание элементов
        self.canvas = tk.Canvas(self, width=300, height=300, bg="white", cursor="cross")
        self.label = tk.Label(self, text="Думаю..", font=("Helvetica", 48))
        self.classify_btn = tk.Button(self, text="Распознать", command=self.classify_handwriting)
        self.button_clear = tk.Button(self, text="Очистить", command=self.clear_all)

        # Сетка окна
        self.canvas.grid(row=0, column=0, pady=2, sticky=W, )
        self.label.grid(row=0, column=1, pady=2, padx=2)
        self.classify_btn.grid(row=1, column=1, pady=2, padx=2)
        self.button_clear.grid(row=1, column=0, pady=2)

        # self.canvas.bind("<Motion>", self.start_pos)
        self.canvas.bind("<B1-Motion>", self.draw_lines)

    def clear_all(self):
        self.canvas.delete("all")

    def classify_handwriting(self):
        HWND = self.canvas.winfo_id()
        rect = win32gui.GetWindowRect(HWND)  # получаем координату холста
        im = ImageGrab.grab(rect)

        result, ptime = predict_digit(im)
        digit, acc = np.argmax(result[1]), max(result[1])
        mcu_digit, mcu_acc, mcu_time = np.argmax(result[0][0:10]), max(result[0][0:10]), result[0][-1]
        self.label.configure(text='PC: ' + str(digit) + ', ' + str(int(acc * 100)) + '%, time: ' + str(ptime) + 'ms\n' +
                                  'MCU: ' + str(mcu_digit) + ', ' + str(int(mcu_acc * 100)) + '%, time: '
                                  + str(mcu_time) + "ms")

    def draw_lines(self, event):
        self.x = event.x
        self.y = event.y
        r = 8
        self.canvas.create_oval(self.x - r, self.y - r, self.x + r, self.y + r, fill='black')


app = App()
mainloop()
