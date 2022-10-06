/*
 * neural_network.h
 *
 *  Created on: 19 ����. 2022 �.
 *      Author: tkachev
 */

#ifndef NEURAL_NETWORK_H_
#define NEURAL_NETWORK_H_

#define INPUT_MODEL_VECTOR_SIZE     784
#define INPUT_LAYER_SIZE            200
#define OUTPUT_MODEL_VECTOR_SIZE    10
#define OUTPUT_LAYER_SIZE           10


float * model_predict(const float *vector);
float ReLU(float scalar);
void softmax(float *vector);


#endif /* NEURAL_NETWORK_H_ */
