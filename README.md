# onegin
Program for text sorting.

## Table of contents
* [Prerequisites](#prerequisites)
* [Installation and setup](#installation-and-setup)
* [Usage](@usage)
* [Additional info](#additional-info)

## Prerequisites
* `git`
* `make`
* `g++`

Program was built and tested on Manjaro Linux 21.3.6.

## Installation and setup
1. Download all source files into one folder:
```
$ git clone https://github.com/princess-oregano/onegin
```
2. Open the subfolder with source files and build with Make:
```
$ cd onegin/
$ make
```
This way the `onegin` programs will automatically run ans sort 
the testing file `Romeo_and_Juliet.txt`with default 
setting and verbose mode on.

3. You can run the `onegin` program again from the folder, where it was built:
```
$ ./onegin
```
4. To remove all object files type this:
```
$ make clean
```
5. To remove all files built by make type this:
```
$ make distclean
```

## Usage
All program's parameters are set through command-line arguments. 
The minimum required input are filenames of input and output:
```
$ ./onegin -i input.txt -o output.txt
```
But you can specify next parameters as well:
* `-s`, `--sort`: choose type of sorting from the list:
    * *`no-sort`* no sorting is executed, the source file is copied to 
destination file, but without empty lines or 
whitespace in the beginning of the lines
    * *`bubble`* sort strings using bubble sort
    * *`quicksort`* sort strings using quicksort
    * *`qsort`* sort strings using standart C `qsort()` function
* `-p`, `--punc`: compare lines including **all** punctuation charactes
(i.e. commas, dots, spaces, etc.), meaning it will not ignore 
those characters while comparing strings
* `-r`, `--reverse`: compare lines from the ends of them to the beginning
* `-v`, `--verbose`: set verbose mode on
* `-h`, `--help`: print help message
---
***Example of usage***
```
$ ./onegin -i Romeo_and_Juliet.txt -o sort.txt --reverse -s qsort
```
This way the program will sort `Romeo_and_Juliet.txt` file using `qsort()` and
comparing lines from their ends, and then print output to `sort.txt`.

## Additional info
* The default settings are:
  * Sorting function is `quicksort()`
  * Punctuation is ignored
  * Reverse mode is off
  * Verbose mode is on
* Order of entered args can be random, but filenames of input/output must be 
specified immediately after the corresponding flags
* `--help`(or `-h`) flag works only if it is the only flag

