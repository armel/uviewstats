# Description

uViewStats is a system monitor: CPU, Memory, Disk and Network. It uses the MicroView to display information in real time.

# Quickstart

## Prerequisites
First, you need to install [**Python**] (https://www.python.org), if you haven't done so already. 

Second, install **pip**, a tool for installing and managing Python packages. It works on Unix/Linux, OS X, and Windows. To install or upgrade pip, securely download [get-pip.py] (https://bootstrap.pypa.io/get-pip.py). Then run the following (which may require administrator access, so you can use sudo):

~~~
$ sudo python get-pip.py
~~~

Third, install 2 Python packages: **psutil** and **pyserial**. For this, run the following:

~~~
$ sudo pip install psutil
$ sudo pip install pyserial
~~~

## Installation

First, start Arduino IDE, open `uviewstats.ino`, compile and upload it.

Second, start your favorite editor (personnaly, I'm using [SublimeText] (http://www.sublimetext.com/)), open `uviewstats.py` and set the `PORT` constant.

Third, open a `Terminal` and start the Python script:

~~~
$ python uviewstats.py
~~~

That’s all !

# License

~~~
The MIT License

Copyright (c) 2014 Armel FAUVEAU (@fauveauarmel), http://globalis-ms.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
~~~
