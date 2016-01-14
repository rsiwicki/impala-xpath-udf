#include <iostream>

#include <impala_udf/udf-test-harness.h>

#include "xpath.hpp"

using namespace impala;
using namespace impala_udf;
using namespace std;

int main(int argc, char** argv) {
  bool passed = true;

  passed &= UdfTestHarness::ValidateUdf<StringVal, StringVal, StringVal, StringVal>(
      xpath_query, StringVal("<value name=\"attribute\">node</value>"),StringVal("//value"),StringVal(","), StringVal("<value name=\"attribute\">node</value>"));

  passed &= UdfTestHarness::ValidateUdf<StringVal, StringVal, StringVal, StringVal>(
      xpath_query, StringVal("<container><value name='attribute'>node</value></container>"),StringVal("/container/value"), StringVal(","), StringVal("<value name=\"attribute\">node</value>"));

  passed &= UdfTestHarness::ValidateUdf<StringVal, StringVal, StringVal, StringVal>(
      xpath_query, StringVal("<container><value name='attribute'>node1</value><value name='attribute'>node2</value></container>"),StringVal("/container/value[1]/text()"),StringVal(","),StringVal("node1"));
 
  passed &= UdfTestHarness::ValidateUdf<StringVal, StringVal, StringVal, StringVal>(
      xpath_query, StringVal("<container><value name='attribute'>node1</value><value name='attribute'>node2</value></container>"),StringVal("/container//value/text()"),StringVal(","),StringVal("node1,node2"));


  passed &= UdfTestHarness::ValidateUdf<StringVal, StringVal, StringVal, StringVal>(
      xpath_query, StringVal("<container><value name='attribute'>node1</value><value name='attribute'>node2</value></container>"),StringVal("/container//value/text()"),StringVal("|"),StringVal("node1|node2"));
 
  
  cout << "Tests " << (passed ? "Passed." : "Failed.") << endl;
  return !passed;
}

