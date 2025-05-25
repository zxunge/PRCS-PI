# PRCS-PI
Demonstrate how to compute the value of π in Plane Rectangular Coordinate System.

## Introduction
This program uses a simple but special method to compute the value of π. To achieve high precisions, it uses [mp++](https://github.com/bluescarni/mppp) (wrapper for GNU MPFR Library).
We notice that the result isn't very accurate. <br />
This is the result computed under a 'precision' of 1(default):
````
3.21799354990720181227976120874663508754653746090348532423780930726215312027493188071806905849145571130739396797038824618862015169967781062558444669728979886
````
Under 100:
````
3.34494604258553080392913345589115642916926580020813673238584998980609166948683339540858413489496519638336788606183757010627873221864293995310374928145924224
````

## Build Instructions
It's very simple. Make sure you've installed gmp, mpfr libraries on your machine. Then run
````
git clone --recursive https://github.com/zxunge/PRCS-PI.git
cd PRCS-PI/ && mkdir build && cd $_
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .

./prcspi
````
Use `./prcspi -h` for help.
