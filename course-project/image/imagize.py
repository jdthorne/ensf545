#!/usr/bin/python

import png

r = png.Reader("background.png")
o = open("image.raw", 'wb')

for row in r.read()[2]:
   for data in row:
      o.write(chr(data))

o.close()
