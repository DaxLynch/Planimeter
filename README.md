# Digital Planometer
A planometer is a device that calculates the area of an arbitrary shape on a flat surface. Invented in the early 1800s, they were a staple in engineers’ offices before the dawn of computers. They are always mentioned in multivariable calculus classes as they are a very physical example of Green’s Theorem, which relates the line integral around the surface to the area of the surface. I built one! All the design and code is mine except for the encoder interrupt handling, which is thanks to Nick Gammon and many others. 
![image](https://github.com/DaxLynch/Planimeter/assets/81718016/9c60bd2a-98b6-4b72-b960-3519bd61e8d0)
![image](https://github.com/DaxLynch/Planimeter/assets/81718016/34bf39c6-4287-45f2-9395-4deae8fb8f09)

# Description of the Planometer
For my final project for Digital Electronics 432, I created a digital Planometer. It is able to calculate the area of arbitrary shapes on a piece of paper with an error of 5%. By following around the edge of a shape with the “crosshair”, the area is calculated and recorded on the LCD.

I used 2 accurate rotary encoders, one recording the angle traversed on the shape while the other records the radius of the point that is tracked along the edge of the contour. An Arduino Nano continually records the position of the encoders and updates the area sum according to the formula. When a button is pressed, the sum is reset to zero. This is useful, because when you move the crosshair to the start of the shape, you will accumulate area on the sum.

# How it works
The area of a small sector of a circle is angle (in radians) * radius squared/2. If that angle is 2pi, then the area is pi* r^2. This machine performs that operation many times a second, calculating the positive or negative area to be added or subtracted from the current total. It is the same as the integral over the region of r^2*dr. It does not matter where the origin is, this integral is the same. If you would like more explanation feel free to email me at declanxlynch@gmail.com.


The largest problem was getting the encoders to work. They lack a datasheet, so it is difficult to know what to do. After about 5 hours or so, I was able to get them to work. Some of the complexities of these encoders include the fact that they need to be attached to interrupts pins, which I didn’t originally know were only pins digital  2 and 3. Furthermore, there was lots of disagreement on how the pull up resistors should work. Ultimately, I didn’t need any pull up resistors. Another issue with the encoders is reading the quadrature signal. It took me a while to understand.

        I also found a lot of difficulties in the mechanical pieces. I 3D printed 3 parts, shown below. These are the box, the rack, and the pinion. These underwent multiple rounds of revisions. Prior to this, I had only done minimal printing, so it was tough. A key issue is printing a long enough radial arm, so I glued two racks together, allowing for enough radial traversal. I think if I attached more, the planometer would still work.

The code had a few parts. The simplest was the LCD code, as the available library made it very simple.

 The integration was not too complex. It was essentially a while loop that added the radius^2 * the signed change in angle times a constant every loop. The constant however was difficult to determine. It required relating the change in position of the encoder to the linear change on the rack. This required some delicate measuring.  

A very scary issue I ran into was that I dropped and basically shattered my project before showing it to my teacher!

# Conclusion
This project came out exceptional. I am very proud of the results being within 5%. At the start I was very scared for this project, as it seemed like there was many possible pitfalls. It involved recording data from the encoder, powering the Arduino, 3D printing the mechanical portions, and handling and outputting the data. Not only did I have to do all these right, I had to still have time left over to do all my other classes 😊
