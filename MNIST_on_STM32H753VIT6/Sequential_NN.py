from tensorflow.keras import Sequential
from tensorflow.keras.layers import Dense, ReLU, Softmax, Dropout, Flatten
from tensorflow.keras.callbacks import EarlyStopping

from keras.datasets import mnist
from keras.utils import np_utils

# скачиваем данные и разделяем на надор для обучения и тесовый
(x_train, y_train), (x_test, y_test) = mnist.load_data()

num_classes = 10
#x_train = x_train.reshape(x_train.shape[0], 28, 28)
#x_test = x_test.reshape(x_test.shape[0], 28, 28)
x_train = x_train.reshape(60000, 784)
x_test = x_test.reshape(10000, 784)

# преобразование векторных классов в бинарные матрицы
y_train = np_utils.to_categorical(y_train, num_classes)
y_test = np_utils.to_categorical(y_test, num_classes)

x_train = x_train.astype('float32')
x_test = x_test.astype('float32')
x_train /= 255
x_test /= 255
print('Размерность x_train:', x_train.shape)
print(x_train.shape[0], 'Размер train')
print(x_test.shape[0], 'Размер test')

model = Sequential()
#model.add(Flatten(input_shape=(28, 28)))
#model.add(Dense(512, activation='relu'))
#model.add(Dropout(0.5))
#model.add(Dense(512, activation='relu'))
#model.add(Dropout(0.5))
#model.add(Dense(10, activation='sigmoid'))
model.add(Dense(200, input_dim=784, activation="relu"))
model.add(Dense(10, activation="softmax"))

model.compile(loss='categorical_crossentropy',
              optimizer='adam',
              metrics=['accuracy'])

early_stopping_callback = EarlyStopping(monitor='val_accuracy',
                                        patience=2)

hist = model.fit(x_train, y_train, batch_size=200,
                 epochs=25, verbose=2, validation_split=0.2,
                 callbacks=[early_stopping_callback])

print("Модель успешно обучена")

model.save('seq_mnist.h5')
print("Модель сохранена как seq_mnist.h5")
score = model.evaluate(x_test, y_test, verbose=0)
print('Потери на тесте:', score[0])
print('Точность на тесте:', score[1])




