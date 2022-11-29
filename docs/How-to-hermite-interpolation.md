# 埃尔米特插值
对于任意Hermite曲线片段，有左右控制点 $p_0(x_0, y_0)$ , $p_1(x_1, y_1)$ ，且左右控制点的右、左侧极限导数分别为 $d_0$ , $d_1$ .

## 求值
对于 $\forall x\in[x_0, x_1]$ , 有

$$\Delta x_0=x-x_0$$

$$\Delta x_1=x-x_1$$

$$\Delta x=x_1-x_0$$

$$T_0=\frac{\Delta x_0}{\Delta x}$$

$$T_1=\frac{\Delta x_1}{-\Delta x}$$

$$K_0=(1+2\cdot T_0)\cdot T_1^2$$

$$K_1=(1+2\cdot T_1)\cdot T_0^2$$

$$L_0=\Delta x_0\cdot T_1^2$$

$$L_1=\Delta x_1\cdot T_0^2$$

$$y(x)=K_0\cdot y_0+K_1\cdot y_1+L_0\cdot d_0+L_1\cdot d_1$$

## 求导
对于 $\forall x\in[x_0, x_1]$ , 由上述推导过程可知

$$y(x)=K_0\cdot y_0+K_1\cdot y_1+L_0\cdot d_0+L_1\cdot d_1$$

则

$$\frac{{\rm d}y(x)}{{\rm d}x}=\frac{{\rm d}K_0}{{\rm d}x}\cdot y_0+\frac{{\rm d}K_1}{{\rm d}x}\cdot y_1+\frac{{\rm d}L_0}{{\rm d}x}\cdot d_0+\frac{{\rm d}L_1}{{\rm d}x}\cdot d_1$$

又有

$$K_0=(1+2\cdot T_0)\cdot T_1^2$$

$$K_1=(1+2\cdot T_1)\cdot T_0^2$$

$$L_0=(x-x_0)\cdot T_1^2=\Delta x_0\cdot T_1^2$$

$$L_1=(x-x_1)\cdot T_0^2=\Delta x_1\cdot T_0^2$$

则

$$\frac{{\rm d}K_0}{{\rm d}x}=2\cdot\frac{{\rm d}T_0}{{\rm d}x}\cdot T_1^2+(1+2\cdot T_0)\cdot (2\cdot T_1\cdot\frac{{\rm d}T_1}{{\rm d}x})$$

$$\frac{{\rm d}K_1}{{\rm d}x}=2\cdot\frac{{\rm d}T_1}{{\rm d}x}\cdot T_0^2+(1+2\cdot T_1)\cdot (2\cdot T_0\cdot\frac{{\rm d}T_0}{{\rm d}x})$$

$$\frac{{\rm d}L_0}{{\rm d}x}=T_1^2+(x-x_0)\cdot (2\cdot T_1\cdot\frac{{\rm d}T_1}{{\rm d}x})=T_1^2+\Delta x_0\cdot (2\cdot T_1\cdot\frac{{\rm d}T_1}{{\rm d}x})$$

$$\frac{{\rm d}L_1}{{\rm d}x}=T_0^2+(x-x_1)\cdot (2\cdot T_0\cdot\frac{{\rm d}T_0}{{\rm d}x})=T_0^2+\Delta x_1\cdot (2\cdot T_0\cdot\frac{{\rm d}T_0}{{\rm d}x})$$

又有

$$T_0=\frac{\Delta x_0}{\Delta x}=\frac{x-x_0}{x_1-x_0}$$

$$T_1=\frac{\Delta x_1}{-\Delta x}=\frac{x-x_1}{-(x_1-x_0)}$$

则

$$\frac{{\rm d}T_0}{{\rm d}x}=\frac{1}{x_1-x_0}=\frac{1}{\Delta x}$$

$$\frac{{\rm d}T_1}{{\rm d}x}=\frac{1}{-(x_1-x_0)}=\frac{1}{-\Delta x}$$
