# The impala-xpath-udf

This project is a simple but fast pather for xml documents for use with Apache Impala. It was built using Cloudera's distribution of Impala.

It is designed to process according to a subset of the xpath 1.0 standard.

To build the project execute

```
cmake .
make
```

Some basic tests are inluded with the UDF. The following command will execute the tests. 

```
build/xpath-test
```

To deploy the UDF to a Cloudera cluster add the library to a known location:  

```
hdfs dfs -put build/libxpath.so /user/cloudera/mylibs
```
```
create function xpath_query(string,string) returns string location '/user/cloudera/mylibs/libxpath.so' symbol=‘xpath_query';
```
```
[quickstart.cloudera:21000] > create external table xmldata (xml string) stored as parquet location '/user/cloudera/testxpath/xmldata';
```
```
insert into xmldata values ('<nodes><node>node1</node><node>node2</node></nodes>’);
```
```
[quickstart.cloudera:21000] > select xpath_query(xml,'/nodes/node[2]') from xmldata;
```
```
Query: select xpath_query(xml,'/nodes/node[2]') from xmldata

+--------------------------------------+
| testudf.xpath_query(xml, '/nodes/node[2]') |
+--------------------------------------+
| <node>node2</node>                   |
+--------------------------------------+
```
