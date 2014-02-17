#ifndef MEASURABLE_H_
#define MEASURABLE_H_

#include <memory>
#include <boost/function.hpp>
#include "graph_generator.h"

typedef boost::function<void(std::shared_ptr<graph_generator>)> GraphFunction;

struct Measurement {
  double duration;
  unsigned long memory;
};

class Measurable {

  GraphFunction duration_fcn;
  GraphFunction memory_fcn;

protected:
  Measurable(GraphFunction duration_fcn, GraphFunction memory_fcn);

public:
  double measure_duration(std::shared_ptr<graph_generator> graph);
  unsigned long measure_memory(std::shared_ptr<graph_generator> graph);
};

class OriginalMeasurable: public Measurable {

public:
  OriginalMeasurable(GraphFunction duration_fcn);
};

class BoostSimpleMeasurable: public Measurable {

public:
  BoostSimpleMeasurable(GraphFunction duration_fcn);
};

class BoostWeightedGraphMeasurable: public Measurable {

public:
  BoostWeightedGraphMeasurable(GraphFunction duration_fcn);
};

class BoostJohnsonGraphMeasurable: public Measurable {

public:
  BoostJohnsonGraphMeasurable(GraphFunction duration_fcn);
};

#endif /* MEASURABLE_H */
