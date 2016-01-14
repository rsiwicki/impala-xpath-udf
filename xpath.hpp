#ifndef XPATH_H
#define XPATH_H

#include <impala_udf/udf.h>
#include "pugixml.hpp"


using namespace impala_udf;

StringVal xpath_query(FunctionContext* ctx, const StringVal& in, const StringVal& qry, const StringVal& delim);

#endif



