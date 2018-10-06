# Assignment 1 Structs and Array

## Introduction ##
This is a simple C program doing string matching. Input a csv file or enter your data through command line, and using the data to construct the mainstring. After data implemantation, enter a pattern for searching in the mainstring. First output the failure function of the pattern. If match then delete the pattern from the mainstring and output the remain main string.

## How to use this program ##

You will got 4 options to choose in the beginning.

1. Read data from a file
    The data should be a csv file and you need to give the program the complete path of your file. EX: `/Users/joycechin/Desktop/data.csv`. Your file should be the format `name(string),index(int)` in each line.
 2. Write your own data
   You will be implementing your data from the command line. There will be instruction which guide you to input your data. `enter the name: `, you will be expect to enter a string. And also each time you enter your string lenght should not be over 200, but the total length can. `enter the index: `, you will enter the starting index of the next string insertion. If you want to stop input any data just enter *0* when seeing `enter the name`.

After all your input you will see your mainstring construction on the screen

3. Pop the data
   After choosing this option, you will be ask to enter the pattern you will be searching from the mainstring. The first line of output is your failure function of your pattern and the second line of output is the remaining mainstring after deleting the pattern from the original mainstring. But if you haven't input any data before you will be reminded to first enter your data.
 4. Exit
   This option is for exitting the program.

Note: After choosing 1 or 2 you can only choose 3 or 4. If you choose 1 after 2 or 2 after 1 you will be reminded to first process the datasets before pushig new datasets. If you want to end this data just enter 4 to exit from it, then you can enter new datasets. After the first exit from the prvious data, if you want to exit the program just choose 4 again. 