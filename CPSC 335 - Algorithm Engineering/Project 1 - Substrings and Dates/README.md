Project 1: Empirical Analysis
Hypothesis
This project will test the following hypothesis:

For large values of n, the mathematically-derived efficiency class of an algorithm accurately predicts the observed running time of an implementation of that algorithm.

To test this hypothesis, you will implement three algorithms; analyze each mathematically; analyze each empirically; and determine whether the empirical and mathematical analyses are in agreement.

You will produce two deliverables: 1) C++ code implementing the algorithms, and 2) a project report. There are two separate GradeScope assignments for submitting your deliverables.

The Problems and Algorithms
All three problems involve string processing

Run-Length Encode
The run-length encode (Links to an external site.) problem involves compressing a string so that it takes less space. A "run" is a substring of repeated characters, for example "aaaa". Run-length encoding means replacing a run with a single copy of the character and count of how many times it appears. For example, "aaaa" is replaced with "4a", because there are 4 copies of the letter 'a'. In our run-length encoding problem, all runs are encoded, and the input string is limited to lower-case letter and space characters.

run-length encode problem problem
input: a string  of  characters, where each character is a lower-case letter or space
output: a string  where each run of  repetitions of the character  is replaced with the string ""

Example inputs and outputs:

"aaa" becomes "3a"
"heloooooooo there" becomes "hel8o there"
"footloose and fancy free" becomes "f2otl2ose and fancy fr2e"
The following algorithm solves the run-length encode problem.

run_length_encode(S):
    C = ""
    if S is empty:
        return C
    run_char = S[0]
    run_length = 1
    for each character c in S after the first:
           if c == run_char:
               run_length++
           else:
               append_run(C, run_char, run_length)
               run_char = c
               run_length = 1
    append_run(C, run_char, run_length)
    return C

append_run(C, run_char, run_length):
    if run_length > 1:
        C.append(convert_to_string(run_length))
    C.append(run_char)
Longest Frequent Substring
In the longest frequent substring problem, we search for a long substring, where every character in the substring appears at least  times in the original string.

longest frequent substring problem
input: a string  of  characters, and integer 
output: the longest string  such that  is a substring of  and every character in  appears at least  times in 

When  the "appears at least  times" requirement is not a limitation at all, so the output is the entire string  Note that the empty string "" counts as a substring of any  so if  is too large, no characters appear at least  times, and the output is "". Example inputs and outputs:

"abc",  output is "abc"
"abc",  output is ""
"aaabb",  output is "aaa"
"aa_bb_baba_aaa",  output is "baba"
See the unit tests in algorithms_test.cpp for more examples.

The following algorithm solves the longest frequent substring problem.

longest_frequent_substring(S, k):
    freq = new dictionary that maps a char to an int
    for c in S:
        if c not in freq:
            freq[c] = 1
        else:
            freq[c]++
    best = ""
    for b from 0 through n-1:
        for e from b+1 through n:
            cand = S[b:e]
            if every character c in cand has freq[c] >= k:
                if cand.size() > best.size():
                    best = cand
    return best
Reformat Date
The third problem involves data cleansing (Links to an external site.) a string that may contain a date in various formats, and reformatting the date in string YYYY-MM-DD format.

reformate date problem
input: a string   that may fit in pattern 1, 2, 3, 4 
output: a string  that contains the same date in YYYY-MM-DD format; or throws an exception if  is invalid

There are four valid patterns for an input string:

"Y-M-D", where Y, M, and D are positive integers (this resembles the output format)
"M/D/Y", where Y, M, and D are positive integers
"MONTH D, Y" where D and Y are positive integers, and MONTH is the full name of a month ("january", "february", ..., "december")
"MON D, Y" where D and Y are positive integers, and MON is the first three letters of a month name ("jan", "feb", ..., "dec") 
Any number of leading spaces and trailing spaces are ignored.

The input is invalid, and your function should throw an exception, if any of the following are true:

 does not fit pattern 1, 2, 3, or 4
MONTH is not a valid month name
MON is not a valid month abbreviation
Y is not in the range 
M is not in the range 
DAY is not in the range 
(Some months actually have fewer than 31 days, but we are ignoring this to keep things simple.)

To compile the test and timing programs:
$ make

To test your algorithm implementations for correctness:
$ make test

To grade your submission:
$ make grade
