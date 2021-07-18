<h1>Simple Pendulum simulation using opengl and C++<h1>

[Video Demo]()

A simple pendulum consists of a rod and a mass. The mass is connected to the rod which swings freely about its piviot.

![pendulum](http://www.acs.psu.edu/drussell/Demos/Pendulum/Pendulum.gif)

the equation of motion for a simple pendulum is:
ɑ = -(g/r)sin(θ)

where ɑ is the angular acceleration
g is the gravitational constant
L is the length
and θ is the angle measured from the resting position of the pendulum

https://gafferongames.com/post/fix_your_timestep/
https://gafferongames.com/post/integration_basics/


<h2>this simulation makes use of semi-implicit euler
Semi-implicit euler is a [Numerical Integration](https://en.wikipedia.org/wiki/Numerical_integration) method used to aproximate the solution of the pendulum's equation of motion.


Advantages
*Simple to implement compared to methods such as runga-kutta order 4
*More stable than explicit Euler since it does not add energy to the system
  *For example in a spring damper system explicit euler will add energy to the system causing the simulation to become unstable
  ![image of explicit euler](https://gafferongames.com/img/game-physics/integration_basics_damped_explicit_euler.png)
  *Meanwhile, semi-implicit Euler does not add energy to the system therefore producing an accurate simulation
  ![semi-implicit Euler](https://gafferongames.com/img/game-physics/integration_basics_damped_semi_implicit_euler.png)

Disadvantages
*Not as accurate as other methods such as implicit euler. It is first order accurate. (same as explicit euler)

**However** for our purposes, semi-implicit Euler is sufficently accurate.

<h2>the time step in the simulation is also not linked to frame rate
the time step used in physics calculations will affect the simulation's behavior and accuracy.
