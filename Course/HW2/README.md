# NTUDSA2018 HW2 - Cryptocurrency Querying
> This is a temporary version of the homework, Some weight of words will differ from the course webpage, but the meanings will all be the same.
## Problem definition
Cryptocurrency is in a big appreciation these year. So John Ceena, an oil tycoon wants to dive into the cryptocurrency market. However, the currencys, exchanges, and so many things make John really confused. As a result, he wants to hire you helping him to sort out the large data, and find out the best currency, exchange to put his enormous asset in.

Your job: Sort the data with multiple keys, and support each task list below.

### Data format will be:
```
Date, currency, exchange, low, high, daily caps
Each column will seperate with tabs ('\t'), 
each data will seperate with newline ('\n').
```
---
### Your program should support:
Get the testing data path from argv[1], get the commands from Stdin.
TAs will execute your program like: 
```
./a.out [data_path] <[test_case] >[output_file]
```
Each components in a command are separate with tab'\t', 
commands will separate with newline'\n'.

1. query
> Find the data corresponds to the input
```
            ____- >This is a tab
input: query    [date]    [currency]    [exchange]
output: [low] [high] [cap]
             _ ->This is a space
(low/high accurate to 4th decimal places)
```

2. daily maximum/minimum
> Find the maximum/minimum of the currency on the given day.
> Find the maximum based on high, minimum based on low of all the exchanges.
```
input:  price    [min/max]    [date]    [currency]
output: [min/max of the currency on that date]
(accurate to 4th decimal places)
```

3. cap
> Find the exchange's total capital of every currencys on the given date
```
input: cap    [date]    [exchange]
output: [total cap]
```

4. end of commanding
```
input: end
Exit the program
```
#### Note:
You can safely assume that the command format will always be correct. However, there might exist some date/currency/exchange that is not found in our database, which you should output **"none"** in these case.

---

## Data:
We provide some public data for you to test out your program, and maintain some private data on judge.

### Public Data
You can access the data on workstation's /tmp2
-> Path: /tmp2/DSA2018Spring/hw2
Or you can download them  directly from **[here](https://www.csie.ntu.edu.tw/~cyshih/dsa_hw2/)**
```
Dir Tree:
    Public_data.txt    ->Test_data
    
    1.in: Test case for "query"
    2.in: Test case for "price"
    3.in: Test case for "cap"
    4.in: Mixed
    
    *.out: outputs
```


---
## Sample case:
```
Input: query    20130114    Diamond    Tidex
Output: 2.944    4.6044    24
```

```
Input: price    low    20130114    Diamond
Output: 4.6257
```
```
Input: cap    20130114    Tidex
Output: 210671
```
```
Input: query    20120114    Roger    Jang
Output: none
```
#### Boundaries
```
Except that cap should store with long, all data will fit in integer/float.
```
---
## Suggestion
1. You may create more than one sorting table to support all the commands.
2. Binary search should be your weapon to deal with the time barrier.
3. The homework is focusing on multiple keys sorting and binary search. However, other methods with faster speed are welcome.
4. You can safely assume that the command format will always be correct. However, there might exist some date/currency/exchange that is not found in our database, which you should output "none" in these case.


## Requirements
Time limit: TBD
Memory limit: TBD
FYI, TA's program(fgets, std:sort, binary search) spend mostly 11s, max 12s on linux8. 10s on my PC, 15s on my laptop.