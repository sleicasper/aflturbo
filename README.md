# AFLTurbo

AFLTurbo is extended by three new techniques that make AFL more efficient (increase code coverage and find more bugs).


More detailes can be found in our paper accepted in The 31st International Symposium on Software Reliability Engineering (ISSRE 2020)

## Build
run `make` command inside this directory.

## Run

To use AFLTurbo, simplely run `afl-fuzz`.
We also provide three fuzzers (`afl-int` `afl-loc` `afl-hot`) equipped with only each of the techniques.