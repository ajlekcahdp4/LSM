![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
# <p align = "center">Least Square Method Calculation</p>
## table of contents:

- [How to clone](#how-to-clone)
- [Dependencies](#dependencies)
- [How to use](#how-to-use)
    - [Use as an library](#use-as-an-library)
    - [Use as a program](#you-can-also-use-this-library-as-a-project-for-least-squares-method-using-my-main-file-in-this-case)

    - [Input files format](#input-files-format)


## How to clone
To clone this repository run:

```
git clone https://github.com/ajlekcahdp4/LSM.git
cd LSM
```

## Dependencies
### 1) [gnuplot](http://www.gnuplot.info):

You can install gnuplot by apt / apt-get:
```
sudo apt install gnuplot
```

Or by pacman (On Arch and Manjaro linux):
```
sudo pacman -S gnuplot
```
* If you face some problem with `libQt5Core.so.5` use this [reccomendations](https://stackoverflow.com/questions/63627955/cant-load-shared-library-libqt5core-so-5).
### 2) [make](https://www.gnu.org/software/make/)

You can install make by apt / apt-get:
```
sudo apt install make
```

Or by pacman (On Arch and Manjaro linux):
```
sudo pacman -S make
```

# How to use
----


## Use as an library


## You can also use this library as a project for least squares method using my `main` file. In this case:
To compile this program run:
```
make
```

And then to run it use:
```
./run
```
The program will ask you about type of aproximation (managed linear, exponential and any-degrees polinomial), input file name, output file name, abscissa axis label, ordinate axis label and degree of the polinom (in polinomial approximation case)

## Input files format
You have to write measured points in a file this way:
1) The decimal separator should be a dot, not a comma.
2) Write abscissa and ordinate values in columns like this



<figure class="sign">
    <p align = "center">
        <img src="https://github.com/ajlekcahdp4/LSM/blob/main/examples/input-file-format.png" alt="example of input file">
    </p>
   <figcaption>Points near y = x^3 line (for example)</figcaption>
</figure>


* In this example written this points:

Point number | X | Y 
-------------|---|----
1            |1.0|1.2
2            |2.0|9.0
3            |3.0|26.0
4            |4.0|67.0
5            |5.0|116.0



