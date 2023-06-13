#include "layer.h"

/* The sigmoid function and derivative. */
double sigmoid(double x)
{
  return 1 / (1 + exp(-x));
}

double sigmoidprime(double x)
{
  return x*(1 - x);
}

/* Creates a single layer. */
layer_t *layer_create()
{
  layer_t *layer = malloc(sizeof(layer_t));
  if (layer == NULL) {
    return NULL;
  }
  layer->num_inputs = 0;
  layer->num_outputs = 0;
  layer->outputs = NULL;
  layer->prev = NULL;
  layer->next = NULL;
  layer->weights = NULL;
  layer->biases = NULL;
  layer->deltas = NULL;
  return layer;
}

/* Initialises the given layer. */
bool layer_init(layer_t *layer, int num_outputs, layer_t *prev)
{
  layer->num_outputs = num_outputs;
  layer->outputs = malloc(num_outputs * sizeof(double));
  if (layer->outputs == NULL) {
    return true;
  }
  for (int i = 0; i < num_outputs; i++) {
    layer->outputs[i] = 0.0;
  }

  layer->prev = prev;
  if (prev != NULL) {
    layer->num_inputs = prev->num_outputs;
    layer->weights = malloc(layer->num_inputs * sizeof(double *));
    if (layer->weights == NULL) {
      return true;
    }
    double *weights = malloc(num_outputs * layer->num_inputs * sizeof(double));
    if (weights == NULL) {
      return true;
    }
    for (int i = 0; i < layer->num_inputs; i++) {
      layer->weights[i] = weights + i * layer->num_outputs;
    }
    for (int i = 0; i < layer->num_inputs; i++) {
      for (int j = 0; j < num_outputs; j++) {
	layer->weights[i][j] = ANN_RANDOM();
      }
    }

    layer->biases = malloc(num_outputs * sizeof(double));
    if (layer->biases == NULL) {
      return true;
    }
    for (double *b = layer->biases; b - layer->biases < num_outputs; b++) {
      *b = 0.0;
    }

    layer->deltas = malloc(num_outputs * sizeof(double));
    if (layer->deltas == NULL) {
      return true;
    }
    for (double *d = layer->deltas; d - layer->deltas < num_outputs; d++) {
      *d = 0.0;
    }
  }
  return false;
}

/* Frees a given layer. */
void layer_free(layer_t *layer)
{
  free(layer->outputs);
  if (layer->weights != NULL) {
    free(layer->weights[0]);
    free(layer->weights);
  }
  free(layer->biases);
  free(layer->deltas);
  free(layer);
}

/* Computes the outputs of the current layer. */
void layer_compute_outputs(layer_t const *layer)
{
  for (int j = 0; j < layer->num_outputs; j++) {
    double output = 0;
    for (int i = 0; i < layer->num_inputs; i++) {
      output += layer->weights[i][j] * layer->prev->outputs[i];
    }
    output = sigmoid(output + layer->biases[j]);
    layer->outputs[j] = output;
  }
}

/* Computes the delta errors for this layer. */
void layer_compute_deltas(layer_t const *layer)
{
  for (int i = 0; i < layer->num_outputs; i++) {
    double delta = 0;
    for (int j = 0; j < layer->next->num_outputs; j++) {
      delta += layer->next->weights[i][j] * layer->next->deltas[j];
    }
    delta *= sigmoidprime(layer->outputs[i]);
    layer->deltas[i] = delta;
  }
}

/* Updates weights and biases according to the delta errors given learning rate. */
void layer_update(layer_t const *layer, double l_rate)
{
  for (int i = 0; i < layer->num_inputs; i++) {
    for (int j = 0; j < layer->num_outputs; j++) {
      layer->weights[i][j] += l_rate * layer->prev->outputs[i] * layer->deltas[j];
    }
  }
  for (int j = 0; j < layer->num_outputs; j++) {
    layer->biases[j] += l_rate * layer->deltas[j];
  }
}
