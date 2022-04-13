![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

![license](https://img.shields.io/github/license/ajlekcahdp4/LSM.svg)
![GH stars](https://img.shields.io/github/stars/ajlekcahdp4/LSM.svg)
![GH pull-requests](https://img.shields.io/github/issues-pr/ajlekcahdp4/LSM.svg)
![GH issues](https://img.shields.io/github/issues/ajlekcahdp4/LSM.svg)
# <p align = "center">Least Square Method Calculation</p>
## table of contents:

- [How to clone](#how-to-clone)
- [Dependencies](#dependencies)
- [How to use](#how-to-use)
    - [Use as an library](#use-as-a-library)
    - [Use as a program](#you-can-also-use-this-library-as-a-complete-program-for-least-squares-method-calculation-and-graph-plotting)
    - [Input files format](#input-files-format)
    - [Output format](#output-format)
- [Feedback](#feedback)


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


## Use as a library

----------------------
## You can also use this library as a complete program for least squares method calculation and graph plotting
### Using my `main` file. In this case:
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
        <img src="https://github.com/ajlekcahdp4/LSM/blob/main/examples/input-file-format.png" alt="example of the input file">
    </p>
   <figcaption>Points near y = x^3 line (for example)</figcaption>
</figure>


* In this example was used this points:

Point number | X | Y 
-------------|---|----
1            |1.0|1.2
2            |2.0|9.0
3            |3.0|26.0
4            |4.0|67.0
5            |5.0|116.0


## output format
After the program is completed, information about the calculation performed using the least squares method will be written to the file that you specified as output. 
* If the file did not exist, it will be created

The output file will look like this:

* example of the output file for polinomial approximation:
<figure class="sign">
    <p align = "center">
        <img src="https://github.com/ajlekcahdp4/LSM/blob/main/examples/example-output-file-polinomial.png" alt="example of the output file">
    </p>
</figure>

* example of the output file for linear approximation:
<figure class="sign">
    <p align = "center">
        <img src="https://github.com/ajlekcahdp4/LSM/blob/main/examples/example-output-file-linear.png" alt="example of the output file">
    </p>
</figure>

* example of the output file for exponential approximation:
<figure class="sign">
    <p align = "center">
        <img src="https://github.com/ajlekcahdp4/LSM/blob/main/examples/example-output-file-exponential.png" alt="example of the output file">
    </p>
</figure>

And also you will get the graph of your approximation:

* example of the polinomial graph:
<figure class="sign">
    <p align = "center">
        <img src="https://github.com/ajlekcahdp4/LSM/blob/main/examples/example-graph-polinomial.png" alt="example of the polinomial graph">
    </p>
</figure>

* example of the exponential graph:
<figure class="sign">
    <p align = "center">
        <img src="https://github.com/ajlekcahdp4/LSM/blob/main/examples/example-graph-exponential.png" alt="example of the exponential graph">
    </p>
</figure>

* example of the linear graph:
<figure class="sign">
    <p align = "center">
        <img src="https://github.com/ajlekcahdp4/LSM/blob/main/examples/example-graph-linear.png" alt="example of the linear graph">
    </p>
</figure>


# Feedback
* If you faced some bugs with this program - please, create a bug report in the [issues](https://github.com/ajlekcahdp4/LSM/issues) and I'll try to help you.

*  If you have an idea how to improve this project - please, write it in [issue](https://github.com/ajlekcahdp4/LSM/issues) or fork this repository, write code and create pull request.

### If you found my program interesting or usefull please Give me a star 🌟

