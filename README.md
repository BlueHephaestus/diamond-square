#This is a rather simple program to generate fractal terrain heightmaps using the diamond square algorithm, using C++ and Qt.

#Description
The [Wikipedia Page](https://en.wikipedia.org/wiki/Diamond-square_algorithm) has a pretty apt and accurate description of how it works, however there are several things that the programmer can set depending on the output they want.

1. I initialize all of the corner values to be 0.3, since when I initialized it as ~0(0.00001), it resulted in less mountains than I wanted. Changing this can drastically affect the mean elevation of your result.
2. I made the length equal to 513x513, since that is currently the largest number I could use with the algorithm and c++ arrays, since using the next(1025x1025) results in a Segmentation fault. Going to likely change this to vectors so that I can go bigger.
..* Note: You have to set the dimensions equal to 2^n + 1
3. On every iteration you reduce the magnitude of the range of the random offset. I started my random offset as a number between (-1, 1), and at first make the "magnitude" equal to 1, so that on the first iteration, we have:
..* Random offset set to some number between -1, and 1 (Let's say .4)
..* Random offset is then multiplied by the magnitude, which since this is the first iteration, is still 1. So .4*1 = .4
4. Once the iteration is complete, you decrease the magnitude by whatever you want the decrease rate to be. I wanted to half it every time, so I set my `rand_decrease_rate = .5` At this point, we go through the next iteration, and we have:
..* Random offset set to some number between -1, and 1 (This time it will be .8)
..* Random offset then get's multiplied by magnitude, which is 1*.5 = .5, so .8*.5 = .4, and this becomes our random offset.
5. I also draw each cell in the heightmap as one pixel, make the window and pixmap and matrix dimensions 513x513, and use my own color presets for display(although I believe I already mentioned the latter part). You can mess with the first two in the display_matrix function, and the latter with a find/replace or regex.

##Installation
Want to try it on your machine? Just do:

1. `git clone https://github.com/DarkElement75/diamond-square.git`
2. `cmake .`
3. `make`
4. `./dsquare <seed>`

##Usage
* All of the necessary values(except for the dimensions, you have to find/replace or regex that unfortunately) are at the top of the document, and have comments to describe their purpose. 
* Make sure to add a seed when running the program, such as ./dsquare "gargamel", or else it will not generate.
* I think that's it, happy generation!

##Notes
* Other than these default values, the wikipedia page actually gives quite a good description of it. I displayed the output using some manual color presets.
* I don't yet have implicit wrapping around the edges on the square step.
* Feel free to contact me if you have any questions regarding it, otherwise I hope this repository can help other programmers better understand it's implementation, be it for their games, or perhaps just for tinkering!


