from keras.utils.vis_utils import plot_model
from keras.models import load_model
import sys
import numpy

numpy.set_printoptions(threshold=sys.maxsize)
model = load_model('seq_mnist.h5')

plot_model(model, "model_with_shape_info.png", show_shapes=True)
#print(model.get_config())
print(model.summary())
weight = model.get_weights()

print(len(weight[0]))
print(len(weight[1]))
print(len(weight[2]))
print(len(weight[3]))
with open("model_weights.txt", 'w') as file:
    print(f"Input layer weights (size:{len(weight[0])}): ", file=file)
    print(weight[0], file=file)
    print(f"Input layer bias (size:{len(weight[1])}): ", file=file)
    print(weight[1], file=file)
    print(f"Input output layer weights (size:{len(weight[2])}): ", file=file)
    print(weight[2], file=file)
    print(f"Output layer weights (size:{len(weight[3])}): ", file=file)
    print(weight[3], file=file)
