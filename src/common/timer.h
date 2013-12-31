#ifndef TIMER_H_
#define TIMER_H_

#include <memory>
#include <boost/function.hpp>
#include "graph_generator.h"

double measure(boost::function<void (std::shared_ptr<graph_generator>)> f, const std::shared_ptr<graph_generator>& graph);

#endif /* TIMER_H_ */
