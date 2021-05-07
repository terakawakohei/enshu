import matplotlib.pyplot as plt
import numpy as np



'''空のリストを用意して、後にx_listにxの値を詰め、y_listにsinxの値を詰めていく'''
x_list=[]
y_list=[]

'''sin.datをファイルをテキストモードで読み込む'''
f=open('data_kadai3.dat', 'rt')

'''fから一行ずつ取ってxとsinxの値をx_listとy_listに詰め込んでいる'''
for line in f:
    data=line[:-1].split(' ') 
#    print(data) '''dataがどういう形になるか気になる方は#を外して実行してみてください。'''
    x_list.append(float(data[0]))
    y_list.append(float(data[1]))


#plt.plot(x_list, y_list,color='BLUE',linewidth=3.0) '''線でつないだ絵を見たい場合'''
x = np.arange(-2, 3, 0.1)
y = x**3*0.998958 + -2.308734*x**2 +-2.286289*x +4.007171


plt.plot(x, y)

plt.plot(x_list, y_list, 'o', linestyle='None')

'''横軸と縦軸のラベル付け'''
plt.xlabel('x')
plt.ylabel('y')

'''グリッド線を引く'''
plt.grid(True)

'''表示'''
plt.show()