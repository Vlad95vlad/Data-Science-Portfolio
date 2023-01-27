# MNIST on MCU

This project is my first attempt to create and implement on C code neural network model from Keras for MCU. The model is a two layers sequential neural network with 200 neurons on the first layers and 10 neurons on the second one.
The small number of neurons was due to the low size of MCU's flash. Nevertheless, the model was able to provide an accuracy of about 70% in real tests.

## Files:
- `STM32H753VIT6_app/`: contains all neccesary files for STM32H753VIT6 application.
- `STM32H753VIT6_app/neural_network.c`: model implementation on C code for target MCU.
- `model_test_and_C_implementation.c`: Windows application for test model implementation before deploying to STM32H753VIT6.
- `Sequential_NN.py`: model realisation on Keras.
- `gui_digit_recognizer.py`: main app which draws MNIST numbers, sends it to the MCU and returns the results. 
