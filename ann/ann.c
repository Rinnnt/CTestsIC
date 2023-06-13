#include "ann.h"

/* Creates and returns a new ann. */
ann_t *ann_create(int num_layers, int *layer_outputs)
{
  ann_t *ann = malloc(sizeof(ann_t));
  layer_t *prev = NULL;
  for (int i = 0; i < num_layers; i++) {
    layer_t *layer = layer_create();
    if (layer_init(layer, layer_outputs[i], prev)) {
      return NULL;
    }
    if (prev != NULL) {
      prev->next = layer;
    }
    
    if (i == 0) {
      ann->input_layer = layer;
    }
    if (i == num_layers - 1) {
      ann->output_layer = layer;
    }
    prev = layer;
  }
  return ann;
}

/* Frees the space allocated to ann. */
void ann_free(ann_t *ann)
{
  layer_t *layer = ann->input_layer;
  while (layer != NULL) {
    layer_t *next = layer->next;
    layer_free(layer);
    layer = next;
  }
  free(ann);
}

/* Forward run of given ann with inputs. */
void ann_predict(ann_t const *ann, double const *inputs)
{
  for (int i = 0; i < ann->input_layer->num_outputs; i++) {
    ann->input_layer->outputs[i] = inputs[i];
  }
  layer_t *layer = ann->input_layer->next;
  while (layer != NULL) {
    layer_compute_outputs(layer);
    layer = layer->next;
  }
}

/* Trains the ann with single backprop update. */
void ann_train(ann_t const *ann, double const *inputs, double const *targets, double l_rate)
{
  /* Sanity checks. */
  assert(ann != NULL);
  assert(inputs != NULL);
  assert(targets != NULL);
  assert(l_rate > 0);

  /* Run forward pass. */
  ann_predict(ann, inputs);

  layer_t *layer = ann->output_layer;
  for (int i = 0; i < layer->num_outputs; i++) {
    layer->deltas[i] = sigmoidprime(layer->outputs[i]) * (targets[i] - layer->outputs[i]);
  }
  layer = layer->prev;
  while (layer != ann->input_layer) {
    layer_compute_deltas(layer);
    layer = layer->prev;
  }

  layer = ann->output_layer;
  while (layer != ann->input_layer) {
    layer_update(layer, l_rate);
    layer = layer->prev;
  }
}
