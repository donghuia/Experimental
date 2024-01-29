import random
import networkx as nx
import matplotlib.pyplot as plt

#定义第一个完全独立生成树
G1 = nx.Graph()
G1.add_edge('(0,0)', '(0,1)', weight=1)
G1.add_edge('(0,0)', '(0,3)', weight=1)
G1.add_edge('(0,0)', '(1,3)', weight=1)
G1.add_edge('(0,0)', '(2,3)', weight=1)
G1.add_edge('(0,0)', '(3,3)', weight=1)
G1.add_edge('(0,2)', '(0,3)', weight=1)
G1.add_edge('(0,3)', '(10,0)', weight=1)
G1.add_edge('(0,3)', '(11,0)', weight=1)
G1.add_edge('(0,3)', '(12,0)', weight=1)

G1.add_edge('(1,0)', '(1,1)', weight=1)
G1.add_edge('(1,0)', '(4,3)', weight=1)
G1.add_edge('(1,0)', '(1,3)', weight=1)
G1.add_edge('(1,2)', '(1,3)', weight=1)

G1.add_edge('(2,0)', '(2,1)', weight=1)
G1.add_edge('(2,0)', '(5,3)', weight=1)
G1.add_edge('(2,0)', '(2,3)', weight=1)
G1.add_edge('(2,2)', '(2,3)', weight=1)

G1.add_edge('(3,0)', '(3,1)', weight=1)
G1.add_edge('(3,0)', '(6,3)', weight=1)
G1.add_edge('(3,0)', '(3,3)', weight=1)
G1.add_edge('(3,2)', '(3,3)', weight=1)

G1.add_edge('(4,0)', '(4,1)', weight=1)
G1.add_edge('(4,0)', '(4,3)', weight=1)
G1.add_edge('(4,2)', '(4,3)', weight=1)

G1.add_edge('(5,0)', '(5,1)', weight=1)
G1.add_edge('(5,0)', '(5,3)', weight=1)
G1.add_edge('(5,2)', '(5,3)', weight=1)

G1.add_edge('(6,0)', '(6,1)', weight=1)
G1.add_edge('(6,0)', '(6,3)', weight=1)
G1.add_edge('(6,2)', '(6,3)', weight=1)

G1.add_edge('(7,0)', '(7,1)', weight=1)
G1.add_edge('(7,0)', '(10,3)', weight=1)
G1.add_edge('(7,0)', '(7,3)', weight=1)
G1.add_edge('(7,2)', '(7,3)', weight=1)

G1.add_edge('(8,0)', '(8,1)', weight=1)
G1.add_edge('(8,0)', '(10,3)', weight=1)
G1.add_edge('(8,0)', '(8,3)', weight=1)
G1.add_edge('(8,2)', '(8,3)', weight=1)

G1.add_edge('(9,0)', '(9,1)', weight=1)
G1.add_edge('(9,0)', '(10,3)', weight=1)
G1.add_edge('(9,0)', '(9,3)', weight=1)
G1.add_edge('(9,2)', '(9,3)', weight=1)

G1.add_edge('(10,0)', '(10,1)', weight=1)
G1.add_edge('(10,0)', '(10,3)', weight=1)
G1.add_edge('(10,2)', '(10,3)', weight=1)

G1.add_edge('(11,0)', '(11,1)', weight=1)
G1.add_edge('(11,0)', '(11,3)', weight=1)
G1.add_edge('(11,2)', '(11,3)', weight=1)

G1.add_edge('(12,0)', '(12,1)', weight=1)
G1.add_edge('(12,0)', '(12,3)', weight=1)
G1.add_edge('(12,2)', '(12,3)', weight=1)

#定义第二个完全独立生成树
G2 = nx.Graph()

G2.add_edge('(0,0)', '(0,1)', weight=1)
G2.add_edge('(0,1)', '(0,2)', weight=1)
G2.add_edge('(0,1)', '(4,2)', weight=1)
G2.add_edge('(0,1)', '(5,2)', weight=1)
G2.add_edge('(0,1)', '(6,2)', weight=1)
G2.add_edge('(0,2)', '(0,3)', weight=1)
G2.add_edge('(0,2)', '(7,1)', weight=1)
G2.add_edge('(0,2)', '(8,1)', weight=1)
G2.add_edge('(0,2)', '(9,1)', weight=1)

G2.add_edge('(1,0)', '(1,1)', weight=1)
G2.add_edge('(1,1)', '(1,2)', weight=1)
G2.add_edge('(1,1)', '(5,2)', weight=1)
G2.add_edge('(1,2)', '(1,3)', weight=1)

G2.add_edge('(2,0)', '(2,1)', weight=1)
G2.add_edge('(2,1)', '(2,2)', weight=1)
G2.add_edge('(2,1)', '(6,2)', weight=1)
G2.add_edge('(2,2)', '(2,3)', weight=1)

G2.add_edge('(3,0)', '(3,1)', weight=1)
G2.add_edge('(3,1)', '(3,2)', weight=1)
G2.add_edge('(3,1)', '(7,2)', weight=1)
G2.add_edge('(3,2)', '(3,3)', weight=1)

G2.add_edge('(4,0)', '(4,1)', weight=1)
G2.add_edge('(4,1)', '(4,2)', weight=1)
G2.add_edge('(4,1)', '(10,2)', weight=1)
G2.add_edge('(4,2)', '(4,3)', weight=1)
G2.add_edge('(4,2)', '(11,1)', weight=1)
G2.add_edge('(4,2)', '(12,1)', weight=1)


G2.add_edge('(5,0)', '(5,1)', weight=1)
G2.add_edge('(5,1)', '(5,2)', weight=1)
G2.add_edge('(5,2)', '(5,3)', weight=1)

G2.add_edge('(6,0)', '(6,1)', weight=1)
G2.add_edge('(6,1)', '(6,2)', weight=1)
G2.add_edge('(6,2)', '(6,3)', weight=1)

G2.add_edge('(7,0)', '(7,1)', weight=1)
G2.add_edge('(7,1)', '(7,2)', weight=1)
G2.add_edge('(7,2)', '(7,3)', weight=1)

G2.add_edge('(8,0)', '(8,1)', weight=1)
G2.add_edge('(8,1)', '(8,2)', weight=1)
G2.add_edge('(8,2)', '(8,3)', weight=1)

G2.add_edge('(9,0)', '(9,1)', weight=1)
G2.add_edge('(9,1)', '(9,2)', weight=1)
G2.add_edge('(9,2)', '(9,3)', weight=1)

G2.add_edge('(10,0)', '(10,1)', weight=1)
G2.add_edge('(10,1)', '(10,2)', weight=1)
G2.add_edge('(10,2)', '(10,3)', weight=1)

G2.add_edge('(11,0)', '(11,1)', weight=1)
G2.add_edge('(11,1)', '(11,2)', weight=1)
G2.add_edge('(11,2)', '(11,3)', weight=1)

G2.add_edge('(12,0)', '(12,1)', weight=1)
G2.add_edge('(12,1)', '(12,2)', weight=1)
G2.add_edge('(12,2)', '(12,3)', weight=1)


def test(f):
    # 用N集合表示G1的结点集合
    N = []
    for i in G1.nodes:
        N.append(i)
    #定义故障结点数量
    FaultyNodesNumber = f
    print("起始结点和终端结点为：")
    ST=random.sample(N,2)
    print(ST)
    print("故障结点为：")
    #故障结点不能是起始结点或终端结点
    nodes_F=[x for x in N if x not in ST]
    FaultyNodes=random.sample(nodes_F,FaultyNodesNumber)
    print(FaultyNodes)


    # dijkstra_path计算两点间的最短路
    print('dijkstra方法寻找最短路径：')
    path1 = nx.dijkstra_path(G1, source=str(ST[0]), target=str(ST[1]))
    path2 = nx.dijkstra_path(G2, source=str(ST[0]), target=str(ST[1]))
    print('结点'+str(ST[0])+'到'+str(ST[1])+'的路径：', path1)
    print('结点' + str(ST[0]) + '到' + str(ST[1]) + '的路径：', path2)
    print('dijkstra方法寻找最短距离：')
    distance = nx.dijkstra_path_length(G1, source=str(ST[0]), target=str(ST[1]))
    print('结点'+str(ST[0])+'到'+str(ST[1])+'的距离为：', distance)
    num1=0
    num2=0
    for i in FaultyNodes:
        if i in path1:
           num1=num1+1
        if i in path2:
           num2 = num2 + 1
    if num1==0 and num2==0:
        return 0
    elif num1!=0 and num2==0:
        return 1
    elif num1==0 and num2!=0:
        return 2
    elif num1!=0 and num2!=0:
        return 3
    #nx.draw_networkx(G, pos, node_size=400)
    #plt.savefig("wuxiangtu.png")
    #plt.show()

sum = []
time=10000
#在这里修改故障结点的数量
f=10
for num in range(0,time):
    n=test(f)
    sum.append(n)

sum_0=0
sum_1=0
sum_2=0
sum_3=0
for i in sum:
    if i==0:
       sum_0=sum_0+1
    elif i==1:
       sum_1 = sum_1 + 1
    elif i == 2:
       sum_2 = sum_2 + 1
    elif i==3:
       sum_3 = sum_3 + 1

print("路径P1和P2都无故障的次数为："+str(sum_0))
print("路径P1故障，P2无故障的次数为："+str(sum_1))
print("路径P1无故障，P2故障的次数为："+str(sum_2))
print("路径P1和P2都故障的次数为："+str(sum_3))
print("TFR="+str(sum_3/time))
print("TFR1="+str((sum_1+sum_3)/time))
print("TFR2="+str((sum_2+sum_3)/time))