#pragma once 

#include <memory>
#include <boost/function.hpp>
#include "graph_generator.h"

double measure(boost::function<void (std::shared_ptr<graph_generator>)> f, const std::shared_ptr<graph_generator>& graph);
