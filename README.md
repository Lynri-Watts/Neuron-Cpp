# A neuron-network based AI written in pure C++

## Part 1. Introduction
Nowadays, almost every AI-related code is written in Python, but I simply can't get used to the loose grammar of it. This code was written to help those who wish to use AI without python.

## Part 2. How to install
1. Download, extract and compile the code.
2. Run the application and input "r" for reset.

## Part 3. How to train the network
1. Create a directory named "train"
2. Create a file named "train.txt", storing the training data.
3. Run the application and input "t" for train.
4. Input how many times you want to train the network.

## Part 4. How to create your training data file
On the first line of the file, you need to write a single integer N, representing how many data groups there are.
Then, the file should be followed with exactly 2N lines. Each line should have a certain number of real numbers exactly equal to the width of the neural network, 25 by default. For each pair of line, the former represents the input and the latter represents the expected output. The expected output should all be between 0 and 1.

Here's an example.

```
3 
1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
```

The first number (must be an integer) tells us that there are 3 data groups in this case. Then the file is followed by exactly 6 lines. Each line has exactly 25 real numbers (not necessarily integers).

The first data group includes an input of 

`1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0`

and an expected output of 

`0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0`

Once you finished your training data, you can train the network according to Part 3.

I'm just a high school student in China. I have poor English skills and poor development skills. :(
