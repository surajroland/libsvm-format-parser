Libsvm calculations
============

## Task

Estimated time to complete the task 45-60 minutes. An implementation in C/C++ is preferred over any other programming language. 
You will get an additional 60 minutes of time if you choose to solve this task in C/C++.

As we want to test your algorithmic skills, we would prefer a code with minimal use of libraries.

** In your own interest read and understand this whole file before you start to think about a solution! **

The task consists of three steps:
 * Read the sparse libsvm file *example_file*
 * Calculate the expectation and variance of every dimension that appears at least once separately for each label
 * Output the result as a libsvm file.


### Read a libsvm file of the following format: 

```
label1 key1:value1 key2:value2 key3:value3 ... key_n:value_n\n 
label2 key1:value1 key2:value2 key3:value3 ... key_m:value_m\n 
...
```

Notes: 
 * keys type integer
 * values type double precision floating point
 * every sample has at least one key with one corresponding value
 * keys start at >=1 and are ascending
 * values are normalized in the range (0., 1.]
 * data is sparse. Only keys with values > 0. appear in the data
 * in this task there are only two labels -1 and 1
 * as a simplification all data with label -1 is at the top of the file and all data with label 1 is at the bottom of the file
 * the example data has > 1500 dimensions but only about ~20% have values != 0

_Examples of valid libsvm files_

Example 1:
```
-1 1:0.25 2:1. 3:0.1
-1 1:0.4  2:0.5 3:0.3
1 1:0.1 2:0.2 3:0.1
1 1:0.4 2:0.53 3:0.01
1 1:0.2 2:0.34 3:0.31
1 1:0.3 2:0.36 3:0.21
1 1:0.14 2:0.43 3:0.41
```

Example 2:
```
-1 3:0.1 12:0.2 15:0.3
-1 4:0.4  8:0.5 16:0.3
1 1000:0.1
1 11111:0.4
```

Example 3:
```
-1 1:0.1
-1 2:0.25
1 3:0.13
1 4:0.75
```

### Calculate the expectation and variance

Only the expectation and variance of dimensions that appear at least once shall be calculated.

Input data:
```
-1 1:0.1
-1 3:0.25
1 3:0.13
1 3:0.75
```

What needs to be calculated:

```
for label -1: expectation and variance for key 1 and 3
for label 1: expectation and variance for key 3
```

**Important: Don´t mix the values between labels**

Notes:
 * even if key1 only appears once in all samples of a specific label, the expectation of key1 wont be value1 since the expectation will have to be computed from all appearing samples. For all samples where key1 does not appear, the value of 0.0 has to be used as input value. Same for the calculation of the variance. **If this is not clear, have a look at the corresponding output in the section below**

### Print the result (stdout)

The result shall be printed as libsvm data in the same format as above.
The result shall only consist of the following four lines:

```
-1 key1:expectation_key1 key2:expectation_key2 .. keyn:expectation_keyn
-1 key1:variance_key1 key2:variance_key2 .. keyn:variance_keyn
1 key1:expectation_key1 key2:expectation_key2 .. keym:expectation_keym
1 key1:variance_key1 key2:variance_key2 .. keym:variance_keym
```

Notes:
 * The expectation and variance values shall be printed as .18f
 * Only the dimensions that were set in the input shall appear in the output!

Example input data:
```
-1 1:a 5:b
-1 3:c 5:d
-1 1:e 3:f
1 4:g 1332:h
1 5:i 1333:j
1 6:k 1334:l
```

Corresponding output:
```
-1 1:expectation(0, a, e) 3:expectation(0, c, f) 5:expectation(0, b, d)
-1 1:variance(0, a, e) 3:variance(0, c, f) 5:variance(0, b, d)
1 4:expectation(0, 0, g) 5:expectation(0, 0, i) 6:expectation(0, 0, k) 1332:expectation(0, 0, h) 1333:expectation(0, 0, j) 1334:expectation(0, 0, l)
1 4:variance(0, 0, g) 5:variance(0, 0, i) 6:variance(0, 0, k) 1332:variance(0, 0, h) 1333:variance(0, 0, j) 1334:variance(0, 0, l)
```


