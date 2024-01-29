import networkx as nx
import math
import random

def constructCIST(n,k,I):
    f1=n*1+1
    f2=n*f1+1
    f3=n*f2*f1+1
    G = nx.Graph() #创建的图没有重复边
    for x1 in range(0,f1):
        for x2 in range(0,f2):
            for x3 in range(0,f3):
                G.add_node(str(x3)+','+str(x2)+','+str(x1))
    for m in range(0,f3):
        for i in range(0, f2):
            for j in range(0, f1):
                for l in range(j + 1, f1):
                    G.add_edge(str(m) + ',' +str(i) + ',' + str(j), str(m) + ',' + str(i) + ',' + str(l))

    for node in G.nodes:
        node = node.split(',')
        x3 = int(node[0])
        x2=int(node[1])
        x1=int(node[2])

        y1=f1-1-x1
        y2_list=[]
        for j in range(1,n+1):
            y2_list.append((n*x1+x2+j)%f2)
        for y2 in y2_list:
            G.add_edge(str(x3) + ',' +str(x2) + ',' + str(x1), str(x3) + ',' +str(y2) + ',' + str(y1))

    for node in G.nodes:
        node = node.split(',')
        x3 = int(node[0])
        x2 = int(node[1])
        x1 = int(node[2])

        y1 = f1 - 1 - x1
        y2= f2-1-x2
        y3_list = []
        for j in range(1, n + 1):
            y3_list.append((n * x1 + x2*(f2-1) + j) % f3)
        for y3 in y3_list:
            G.add_edge(str(x3) + ',' + str(x2) + ',' + str(x1), str(y3) + ',' + str(y2) + ',' + str(y1))


    # 构造树
    T = nx.Graph()
    nextGroup = []
    T.add_edge(str(0) + ',' +str(0) + ',' + str(I), str(0) + ',' +str(0) + ',' + str(n - I))
    nextGroup.append(str(0) + ',' +str(0) + ',' + str(I))
    nextGroup.append(str(0) + ',' +str(0) + ',' + str(n - I))

    while nextGroup:
        next=nextGroup[0]
        #获取结点next的邻居结点集合
        neighbor=G[next] #得到的结果是一个set，需要将所有元素的key值取出
        R=[*neighbor]
        del R[0:n]
        for j in range(0,len(R)):
            node = R[j].split(',')
            x3 = int(node[0])
            x2 = int(node[1])
            x1 = int(node[2])
            R1 = str(x3)+','+str(x2)+','+str(n-x1)
            if R[j] not in T.nodes and R1 not in T.nodes:
                T.add_edge(str(next), str(R[j]))
                T.add_edge(str(R[j]), str(R1))
                #print(T.edges)
                nextGroup.append(R[j])
                nextGroup.append(R1)
        nextGroup.remove(next)
        if len(T.nodes)==2*f1*f2*f3:
            break
    if I == 0 and (n + 1) % 2 != 0:
        for i in range(f3):
            for j in range(f2):
                T.add_edge(str(i) + ',' + str(j) + ',' + str(0), str(i) + ',' + str(j) + ',' + str(math.floor(n / 2)))

    for m in range(0, f3):
        for j in range(0, f2):
            for l in range(0, n + 1):
                if (n + 1) % 2 != 0 and I == 0:
                    if l != I and l != n - I and l < n / 2:
                        T.add_edge(str(m) + ',' + str(j) + ',' + str(math.floor(n / 2)),
                                   str(m) + ',' + str(j) + ',' + str(l))
                    elif l != i and l != n - i and l > n / 2:
                        T.add_edge(str(m) + ',' + str(j) + ',' + str(n - I), str(m) + ',' + str(j) + ',' + str(l))
                elif (n + 1) % 2 != 0 and I != 0:
                    if l != I and l != n - I and l <= n / 2:
                        T.add_edge(str(m) + ',' + str(j) + ',' + str(I), str(m) + ',' + str(j) + ',' + str(l))
                    elif l != I and l != n - I and l > n / 2:
                        T.add_edge(str(m) + ',' + str(j) + ',' + str(n - I), str(m) + ',' + str(j) + ',' + str(l))
                else:
                    if l != I and l != n - I and l < n / 2:
                        T.add_edge(str(m) + ',' + str(j) + ',' + str(I), str(m) + ',' + str(j) + ',' + str(l))
                    elif l != I and l != n - I and l > n / 2:
                        T.add_edge(str(m) + ',' + str(j) + ',' + str(n - I), str(m) + ',' + str(j) + ',' + str(l))
    return T

n=4
k=3
G1=nx.Graph()
G1=constructCIST(n,k,0)
G2=nx.Graph()
G2=constructCIST(n,k,1)

print("第1棵树的边集合为：")
print(G1.edges)

print("第2棵树的边集合为：")
print(G2.edges)


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
f=500
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
print("故障结点为："+str(f))