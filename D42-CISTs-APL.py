import networkx as nx
import math
import random

def constructCIST(n,k,I):
    f1=n*1+1
    f2=n*f1+1
    G = nx.Graph() #创建的图没有重复边
    #在图G中添加结点
    for x1 in range(0,f1):
        for x2 in range(0,f2):
            G.add_node(str(x2)+','+str(x1))
    for i in range(0,f2):
        for j in range(0,f1):
            for l in range(j+1,f1):
                G.add_edge(str(i)+','+str(j), str(i)+','+str(l), weight=1)
    for node in G.nodes:
        node = node.split(',')
        x2=int(node[0])
        x1=int(node[1])
        y1=f1-1-x1
        y2_list=[]
        for j in range(1,n+1):
            y2_list.append((n*x1+x2+j)%f2)
        for y2 in y2_list:
            G.add_edge(str(x2) + ',' + str(x1), str(y2) + ',' + str(y1))


    #构造树
    T = nx.Graph()
    nextGroup=[]
    T.add_edge(str(0)+','+str(I), str(0)+','+str(n-I))
    nextGroup.append(str(0)+','+str(I))
    nextGroup.append(str(0)+','+str(n-I))


    while nextGroup:
        next=nextGroup[0]
        #获取结点next的邻居结点集合
        neighbor=G[next] #得到的结果是一个set，需要将所有元素的key值取出
        R=[*neighbor]
        del R[0:n]
        for j in range(0,len(R)):
            node = R[j].split(',')
            x2 = int(node[0])
            x1 = int(node[1])
            R1 = str(x2)+','+str(n-x1)
            if R[j] not in T.nodes and R1 not in T.nodes:
                T.add_edge(str(next), str(R[j]))
                T.add_edge(str(R[j]), str(R1))
                #print(T.edges)
                nextGroup.append(R[j])
                nextGroup.append(R1)
        nextGroup.remove(next)
        if len(T.nodes)==2*f1*f2:
            break
    if I==0 and (n+1)%2!=0:
        for j in range(f2):
            T.add_edge(str(j)+','+str(0), str(j)+','+str(math.floor(n/2)))

    for j in range(0, f2):
        for l in range(0, n + 1):
            if (n + 1) % 2 != 0 and I == 0:
                if l != I and l != n - I and l < n / 2:
                    T.add_edge(str(j) + ',' + str(math.floor(n / 2)), str(j) + ',' + str(l))
                elif l != I and l != n - I and l > n / 2:
                    T.add_edge(str(j) + ',' + str(n - I), str(j) + ',' + str(l))
            elif (n + 1) % 2 != 0 and I != 0:
                if l != I and l != n - I and l <= n / 2:
                    T.add_edge(str(j) + ',' + str(I), str(j) + ',' + str(l))
                elif l != I and l != n - I and l > n / 2:
                    T.add_edge(str(j) + ',' + str(n - I), str(j) + ',' + str(l))
            else:
                if l != I and l != n - I and l < n / 2:
                    T.add_edge(str(j) + ',' + str(I), str(j) + ',' + str(l))
                elif l != I and l != n - I and l > n / 2:
                    T.add_edge(str(j) + ',' + str(n - I), str(j) + ',' + str(l))


    return T







n=4
k=2
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
    #用P集合表示所有无故障的路径集合
    P = []
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
    num1=0
    num2=0
    for i in FaultyNodes:
        if i in path1:
           num1=num1+1
        if i in path2:
           num2=num2+1
    if num1==0 and num2==0:
        P.append(len(path1)-1)
        P.append(len(path2)-1)
    elif num1!=0 and num2==0:
        P.append(len(path2)-1)
    elif num1==0 and num2!=0:
        P.append(len(path1)-1)
    return P


Path=[]
time=10000
#在这里修改故障结点的数量
f=10
num=0
for i in range(0,time):
    P=test(f)
    Path.append(sum(P))
    num=num+len(P)
print("num="+str(num))


print("APL="+str(sum(Path)/num))