# An neuron-network based AI written entirely in C++ 

## Part 1. Introduction 

Python is now used for practically all AI-related programs, but I just can't get used to its sloppy grammar. To aid individuals who want to use AI without Python, this code was created. 



## Part 2. Installing the program 

1. Compile, extract, and download the code. 
2. Launch the program and type "r" to reset. 



## Part 3. Training the network 

1. A "train" directory should be created. 
2. Create a file called "train.txt" under "train" and put the training data in it. 
3. Launch the program and enter "t" to train. 
4. Provide the desired number of times to train the network. 



## Part 4. Making your training data file 

You must enter a single integer N, which represents the number of data groups, on the first line of the file. 

Following that, exactly 2N lines should be added to the file. The amount of real numbers on each line should be exactly equal to the width of the neural network, which is 25 by default. The first line in each pair of lines represents the input, while the second line indicates the desired result. Numbers in the output should range from 0 to 1. 

Here is one instance. 

```
3 
1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
```

There are three data groups in this instance, according to the first number, which must be an integer. The file then has exactly 6 lines after it. Every line contains precisely 25 real numbers (not necessarily integers). 

The input of the first data group is 

'1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0' 

and anticipated results of 

`0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0` 

Once your training data is complete, you can train the network in accordance with Part 3. 

I'm just a high school student in China. I have poor English skills and poor development skills. :(
