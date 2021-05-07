import matplotlib.pyplot as plt
import numpy as np

#教師データ

'''空のリストを用意して、後にx_listにxの値を詰め、y_listにsinxの値を詰めていく'''
x_list_teacher=[]
y_list_teacher=[]

'''sin.datをファイルをテキストモードで読み込む'''
f=open('kadai_data_mlp_app2.dat', 'rt')

'''fから一行ずつ取ってxとsinxの値をx_listとy_listに詰め込んでいる'''
for line in f:
    data=line[:-1].split(' ') 
#    print(data) '''dataがどういう形になるか気になる方は#を外して実行してみてください。'''
    x_list_teacher.append(float(data[0]))
    y_list_teacher.append(float(data[1]))

    plt.plot(x_list_teacher, y_list_teacher, '+', linestyle='None')


#結果のデータ

'''空のリストを用意して、後にx_listにxの値を詰め、y_listにsinxの値を詰めていく'''
x_list=[]
y_list=[]

'''sin.datをファイルをテキストモードで読み込む'''
f=open('prediction.dat', 'rt')

'''fから一行ずつ取ってxとsinxの値をx_listとy_listに詰め込んでいる'''
for line in f:
    data=line[:-1].split('	') 
#    print(data) '''dataがどういう形になるか気になる方は#を外して実行してみてください。'''
    x_list.append(float(data[0]))
    y_list.append(float(data[1]))





#plt.plot(x_list, y_list,color='BLUE',linewidth=3.0) '''線でつないだ絵を見たい場合'''


plt.plot(x_list, y_list, '+', linestyle='None', color='orange',label='prediction')

'''横軸と縦軸のラベル付け'''
plt.xlabel('x')
plt.ylabel('y')

plt.legend() # 凡例を表示
plt.title("ETA : 0.01 / ITERATION : 70000 / HIDDEN_DIM : 10")

'''グリッド線を引く'''
plt.grid(True)

'''表示'''
plt.show()