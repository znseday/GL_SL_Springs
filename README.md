# GL SL Springs

Author: Sergey Tsynikin

In this project, there is a modeling (in real time) a ball movement by stretching/compression forces of six springs.

The goal of the project is to study usage basics of using shaders in OpenGL. In the project, naive implementations are used intentionally, without additional optimizations. Also, the project represents different approaches to draw graphics (array pointers, buffer objects, different shader programs, etc.) .

![Screenshot](https://github.com/znseday/GL_SL_Springs/blob/master/Doc/Pic_01.png)

In the physic model, there are used Hooke law and Newton's second law. Differential equation of movement are being solved by trivial Eulerian approach. Also, there is a simplification: the springs don’t have constant fixers on the sphere surface, they can “slide” on the sphere surface in order to a line of force vector always passes through the center of the sphere.

Автор: Цыникин Сергей

В проекте моделируется (в реальном времени) движение объекта (шара) под действием силы растяжения/сжатия шести пружин.

Целью данного проекта является изучение основ использования шейдеров в OpenGL. В проекте осознанно используются наивные реализации без попыток достичь максимальной оптимизации, а также осознанно используются разные подходы к рисованию (указатели на массивы, буфферные объекты, разные шейдерные программы и т.п.). 

В физической модели используются закон Гука и 2й закон Ньютона, а дифференциальное уравнение движения решается тривиальным методом Эйлера. В качестве допущения, пружины не имеют фиксированного крепления к поверхности шарика, а могут как бы скользить по его поверхности так, чтобы линия, вдоль которой растягивается/сжимается пружина, всегда проходила через центр шара.

 

