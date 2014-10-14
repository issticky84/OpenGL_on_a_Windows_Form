OpenGL_on_a_Windows_Form
========================
Visualization of sensor data collecting from LG G watch
3 parts: Histogram Visualization(panel3,left) & RawData Visualization(panel1,right up) & Detail Visualization(panel2,right down)

mouse event
----
<For panel1 & panel3>
* left button : move
* wheel button : scale (zoom in or zoom out)
* right button : select
<For panel1>
* double click : show the original color bar on the panel3 by a flickering way

resize panel
----
When the mouse position touch the side of panel, it shows "NoMoveHoriz" cursor,
which indicates that you can move the panel left and right
* (1) panel3 vs panel1+panel2 (width)
* (2) panel1 (width)
* (3) panel2 (width)
