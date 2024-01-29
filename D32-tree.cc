#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/flow-monitor-module.h"

using namespace ns3;
using namespace std;

NS_LOG_COMPONENT_DEFINE("StaticRoutingExample");

void CalculateMetrics(Ptr<FlowMonitor> flowMonitor, Ptr<OutputStreamWrapper> throughputStream,
                      Ptr<OutputStreamWrapper> lossStream, Ptr<OutputStreamWrapper> delayStream, Time stopTime) {
  if (Simulator::Now() < stopTime) {
    std::map<FlowId, FlowMonitor::FlowStats> stats = flowMonitor->GetFlowStats();
    double totalThroughput = 0.0;
    uint64_t totalPacketsSent = 0;
    uint64_t totalPacketsDropped = 0;
    double totalDelay = 0.0;

    for (std::map<FlowId, FlowMonitor::FlowStats>::const_iterator i = stats.begin(); i != stats.end(); ++i) {
      totalThroughput += i->second.rxBytes * 8.0 / i->second.timeLastRxPacket.GetSeconds();
      totalPacketsSent += i->second.txPackets;
      totalPacketsDropped += i->second.txPackets - i->second.rxPackets;
      totalDelay += i->second.delaySum.GetSeconds();
    }

    double throughput = totalThroughput / 1000000.0; // Convert to Mbps
    double lossRate = (totalPacketsDropped / static_cast<double>(totalPacketsSent)) * 100.0; // Convert to percentage
    double avgDelay = totalDelay / totalPacketsSent;

    *throughputStream->GetStream() << Simulator::Now().GetSeconds() << "\t" << throughput << std::endl;
    *lossStream->GetStream() << Simulator::Now().GetSeconds() << "\t" << lossRate << std::endl;
    *delayStream->GetStream() << Simulator::Now().GetSeconds() << "\t" << avgDelay << std::endl;

    Simulator::Schedule(Seconds(1.0), &CalculateMetrics, flowMonitor, throughputStream, lossStream, delayStream, stopTime);
  }
}


int main(int argc, char *argv[]) {
  LogComponentEnable("StaticRoutingExample", LOG_LEVEL_INFO);

  // 创建节点
  NodeContainer nodes;
  nodes.Create(52);
  
  //各条边的节点组合
  vector<NodeContainer> nodeAdjacencyList(51);

nodeAdjacencyList[0]=NodeContainer(nodes.Get(0), nodes.Get(1)); 
nodeAdjacencyList[1]=NodeContainer(nodes.Get(0), nodes.Get(3)); 
nodeAdjacencyList[2]=NodeContainer(nodes.Get(0), nodes.Get(7)); 
nodeAdjacencyList[3]=NodeContainer(nodes.Get(0), nodes.Get(11)); 
nodeAdjacencyList[4]=NodeContainer(nodes.Get(0), nodes.Get(15)); 
nodeAdjacencyList[5]=NodeContainer(nodes.Get(2), nodes.Get(3)); 
nodeAdjacencyList[6]=NodeContainer(nodes.Get(3), nodes.Get(40)); 
nodeAdjacencyList[7]=NodeContainer(nodes.Get(3), nodes.Get(44)); 
nodeAdjacencyList[8]=NodeContainer(nodes.Get(3), nodes.Get(48)); 
nodeAdjacencyList[9]=NodeContainer(nodes.Get(4), nodes.Get(5)); 
nodeAdjacencyList[10]=NodeContainer(nodes.Get(4), nodes.Get(7)); 
nodeAdjacencyList[11]=NodeContainer(nodes.Get(4), nodes.Get(19)); 
nodeAdjacencyList[12]=NodeContainer(nodes.Get(6), nodes.Get(7)); 
nodeAdjacencyList[13]=NodeContainer(nodes.Get(8), nodes.Get(9)); 
nodeAdjacencyList[14]=NodeContainer(nodes.Get(8), nodes.Get(11)); 
nodeAdjacencyList[15]=NodeContainer(nodes.Get(8), nodes.Get(23)); 
nodeAdjacencyList[16]=NodeContainer(nodes.Get(10), nodes.Get(11)); 
nodeAdjacencyList[17]=NodeContainer(nodes.Get(12), nodes.Get(13)); 
nodeAdjacencyList[18]=NodeContainer(nodes.Get(12), nodes.Get(15)); 
nodeAdjacencyList[19]=NodeContainer(nodes.Get(12), nodes.Get(27)); 
nodeAdjacencyList[20]=NodeContainer(nodes.Get(14), nodes.Get(15)); 
nodeAdjacencyList[21]=NodeContainer(nodes.Get(16), nodes.Get(17)); 
nodeAdjacencyList[22]=NodeContainer(nodes.Get(16), nodes.Get(19)); 
nodeAdjacencyList[23]=NodeContainer(nodes.Get(18), nodes.Get(19)); 
nodeAdjacencyList[24]=NodeContainer(nodes.Get(20), nodes.Get(21)); 
nodeAdjacencyList[25]=NodeContainer(nodes.Get(20), nodes.Get(23)); 
nodeAdjacencyList[26]=NodeContainer(nodes.Get(22), nodes.Get(23)); 
nodeAdjacencyList[27]=NodeContainer(nodes.Get(24), nodes.Get(25)); 
nodeAdjacencyList[28]=NodeContainer(nodes.Get(24), nodes.Get(27)); 
nodeAdjacencyList[29]=NodeContainer(nodes.Get(26), nodes.Get(27)); 
nodeAdjacencyList[30]=NodeContainer(nodes.Get(28), nodes.Get(29)); 
nodeAdjacencyList[31]=NodeContainer(nodes.Get(28), nodes.Get(31)); 
nodeAdjacencyList[32]=NodeContainer(nodes.Get(28), nodes.Get(43)); 
nodeAdjacencyList[33]=NodeContainer(nodes.Get(30), nodes.Get(31)); 
nodeAdjacencyList[34]=NodeContainer(nodes.Get(32), nodes.Get(33)); 
nodeAdjacencyList[35]=NodeContainer(nodes.Get(32), nodes.Get(35)); 
nodeAdjacencyList[36]=NodeContainer(nodes.Get(32), nodes.Get(43)); 
nodeAdjacencyList[37]=NodeContainer(nodes.Get(34), nodes.Get(35)); 
nodeAdjacencyList[38]=NodeContainer(nodes.Get(36), nodes.Get(37)); 
nodeAdjacencyList[39]=NodeContainer(nodes.Get(36), nodes.Get(39)); 
nodeAdjacencyList[40]=NodeContainer(nodes.Get(36), nodes.Get(43)); 
nodeAdjacencyList[41]=NodeContainer(nodes.Get(38), nodes.Get(39)); 
nodeAdjacencyList[42]=NodeContainer(nodes.Get(40), nodes.Get(41)); 
nodeAdjacencyList[43]=NodeContainer(nodes.Get(40), nodes.Get(43)); 
nodeAdjacencyList[44]=NodeContainer(nodes.Get(42), nodes.Get(43)); 
nodeAdjacencyList[45]=NodeContainer(nodes.Get(44), nodes.Get(45)); 
nodeAdjacencyList[46]=NodeContainer(nodes.Get(44), nodes.Get(47)); 
nodeAdjacencyList[47]=NodeContainer(nodes.Get(46), nodes.Get(47)); 
nodeAdjacencyList[48]=NodeContainer(nodes.Get(48), nodes.Get(49)); 
nodeAdjacencyList[49]=NodeContainer(nodes.Get(48), nodes.Get(51)); 
nodeAdjacencyList[50]=NodeContainer(nodes.Get(50), nodes.Get(51)); 

// 创建节点之间的连接，分别设置传输速率和传播延迟
  
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute("DataRate", StringValue("100Mbps"));
  p2p.SetChannelAttribute("Delay", StringValue("1ms"));

  //通过 Install 函数将设备配置应用到相应的节点上，形成了网络拓扑
    NetDeviceContainer 
devices0_1,
devices0_3,
devices0_7,
devices0_11,
devices0_15,
devices2_3,
devices3_40,
devices3_44,
devices3_48,
devices4_5,
devices4_7,
devices4_19,
devices6_7,
devices8_9,
devices8_11,
devices8_23,
devices10_11,
devices12_13,
devices12_15,
devices12_27,
devices14_15,
devices16_17,
devices16_19,
devices18_19,
devices20_21,
devices20_23,
devices22_23,
devices24_25,
devices24_27,
devices26_27,
devices28_29,
devices28_31,
devices28_43,
devices30_31,
devices32_33,
devices32_35,
devices32_43,
devices34_35,
devices36_37,
devices36_39,
devices36_43,
devices38_39,
devices40_41,
devices40_43,
devices42_43,
devices44_45,
devices44_47,
devices46_47,
devices48_49,
devices48_51,
devices50_51;

devices0_1= p2p.Install(nodes.Get(0), nodes.Get(1)); 
devices0_3= p2p.Install(nodes.Get(0), nodes.Get(3)); 
devices0_7= p2p.Install(nodes.Get(0), nodes.Get(7)); 
devices0_11= p2p.Install(nodes.Get(0), nodes.Get(11)); 
devices0_15= p2p.Install(nodes.Get(0), nodes.Get(15)); 
devices2_3= p2p.Install(nodes.Get(2), nodes.Get(3)); 
devices3_40= p2p.Install(nodes.Get(3), nodes.Get(40)); 
devices3_44= p2p.Install(nodes.Get(3), nodes.Get(44)); 
devices3_48= p2p.Install(nodes.Get(3), nodes.Get(48)); 
devices4_5= p2p.Install(nodes.Get(4), nodes.Get(5)); 
devices4_7= p2p.Install(nodes.Get(4), nodes.Get(7)); 
devices4_19= p2p.Install(nodes.Get(4), nodes.Get(19)); 
devices6_7= p2p.Install(nodes.Get(6), nodes.Get(7)); 
devices8_9= p2p.Install(nodes.Get(8), nodes.Get(9)); 
devices8_11= p2p.Install(nodes.Get(8), nodes.Get(11)); 
devices8_23= p2p.Install(nodes.Get(8), nodes.Get(23)); 
devices10_11= p2p.Install(nodes.Get(10), nodes.Get(11)); 
devices12_13= p2p.Install(nodes.Get(12), nodes.Get(13)); 
devices12_15= p2p.Install(nodes.Get(12), nodes.Get(15)); 
devices12_27= p2p.Install(nodes.Get(12), nodes.Get(27)); 
devices14_15= p2p.Install(nodes.Get(14), nodes.Get(15)); 
devices16_17= p2p.Install(nodes.Get(16), nodes.Get(17)); 
devices16_19= p2p.Install(nodes.Get(16), nodes.Get(19)); 
devices18_19= p2p.Install(nodes.Get(18), nodes.Get(19)); 
devices20_21= p2p.Install(nodes.Get(20), nodes.Get(21)); 
devices20_23= p2p.Install(nodes.Get(20), nodes.Get(23)); 
devices22_23= p2p.Install(nodes.Get(22), nodes.Get(23)); 
devices24_25= p2p.Install(nodes.Get(24), nodes.Get(25)); 
devices24_27= p2p.Install(nodes.Get(24), nodes.Get(27)); 
devices26_27= p2p.Install(nodes.Get(26), nodes.Get(27)); 
devices28_29= p2p.Install(nodes.Get(28), nodes.Get(29)); 
devices28_31= p2p.Install(nodes.Get(28), nodes.Get(31)); 
devices28_43= p2p.Install(nodes.Get(28), nodes.Get(43)); 
devices30_31= p2p.Install(nodes.Get(30), nodes.Get(31)); 
devices32_33= p2p.Install(nodes.Get(32), nodes.Get(33)); 
devices32_35= p2p.Install(nodes.Get(32), nodes.Get(35)); 
devices32_43= p2p.Install(nodes.Get(32), nodes.Get(43)); 
devices34_35= p2p.Install(nodes.Get(34), nodes.Get(35)); 
devices36_37= p2p.Install(nodes.Get(36), nodes.Get(37)); 
devices36_39= p2p.Install(nodes.Get(36), nodes.Get(39)); 
devices36_43= p2p.Install(nodes.Get(36), nodes.Get(43)); 
devices38_39= p2p.Install(nodes.Get(38), nodes.Get(39)); 
devices40_41= p2p.Install(nodes.Get(40), nodes.Get(41)); 
devices40_43= p2p.Install(nodes.Get(40), nodes.Get(43)); 
devices42_43= p2p.Install(nodes.Get(42), nodes.Get(43)); 
devices44_45= p2p.Install(nodes.Get(44), nodes.Get(45)); 
devices44_47= p2p.Install(nodes.Get(44), nodes.Get(47)); 
devices46_47= p2p.Install(nodes.Get(46), nodes.Get(47)); 
devices48_49= p2p.Install(nodes.Get(48), nodes.Get(49)); 
devices48_51= p2p.Install(nodes.Get(48), nodes.Get(51)); 
devices50_51= p2p.Install(nodes.Get(50), nodes.Get(51)); 

// 安装Internet协议栈
  InternetStackHelper internet;
  internet.Install(nodes);
  
Ipv4AddressHelper  
address0_1,
address0_3,
address0_7,
address0_11,
address0_15,
address2_3,
address3_40,
address3_44,
address3_48,
address4_5,
address4_7,
address4_19,
address6_7,
address8_9,
address8_11,
address8_23,
address10_11,
address12_13,
address12_15,
address12_27,
address14_15,
address16_17,
address16_19,
address18_19,
address20_21,
address20_23,
address22_23,
address24_25,
address24_27,
address26_27,
address28_29,
address28_31,
address28_43,
address30_31,
address32_33,
address32_35,
address32_43,
address34_35,
address36_37,
address36_39,
address36_43,
address38_39,
address40_41,
address40_43,
address42_43,
address44_45,
address44_47,
address46_47,
address48_49,
address48_51,
address50_51;

address0_1.SetBase("10.1.1.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_1 = address0_1.Assign(devices0_1);
address0_3.SetBase("10.1.2.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_3 = address0_3.Assign(devices0_3);
address0_7.SetBase("10.1.3.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_7 = address0_7.Assign(devices0_7);
address0_11.SetBase("10.1.4.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_11 = address0_11.Assign(devices0_11);
address0_15.SetBase("10.1.5.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_15 = address0_15.Assign(devices0_15);
address2_3.SetBase("10.1.6.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces2_3 = address2_3.Assign(devices2_3);
address3_40.SetBase("10.1.7.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces3_40 = address3_40.Assign(devices3_40);
address3_44.SetBase("10.1.8.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces3_44 = address3_44.Assign(devices3_44);
address3_48.SetBase("10.1.9.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces3_48 = address3_48.Assign(devices3_48);
address4_5.SetBase("10.1.10.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces4_5 = address4_5.Assign(devices4_5);
address4_7.SetBase("10.1.11.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces4_7 = address4_7.Assign(devices4_7);
address4_19.SetBase("10.1.12.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces4_19 = address4_19.Assign(devices4_19);
address6_7.SetBase("10.1.13.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces6_7 = address6_7.Assign(devices6_7);
address8_9.SetBase("10.1.14.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces8_9 = address8_9.Assign(devices8_9);
address8_11.SetBase("10.1.15.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces8_11 = address8_11.Assign(devices8_11);
address8_23.SetBase("10.1.16.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces8_23 = address8_23.Assign(devices8_23);
address10_11.SetBase("10.1.17.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces10_11 = address10_11.Assign(devices10_11);
address12_13.SetBase("10.1.18.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces12_13 = address12_13.Assign(devices12_13);
address12_15.SetBase("10.1.19.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces12_15 = address12_15.Assign(devices12_15);
address12_27.SetBase("10.1.20.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces12_27 = address12_27.Assign(devices12_27);
address14_15.SetBase("10.1.21.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces14_15 = address14_15.Assign(devices14_15);
address16_17.SetBase("10.1.22.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces16_17 = address16_17.Assign(devices16_17);
address16_19.SetBase("10.1.23.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces16_19 = address16_19.Assign(devices16_19);
address18_19.SetBase("10.1.24.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces18_19 = address18_19.Assign(devices18_19);
address20_21.SetBase("10.1.25.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces20_21 = address20_21.Assign(devices20_21);
address20_23.SetBase("10.1.26.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces20_23 = address20_23.Assign(devices20_23);
address22_23.SetBase("10.1.27.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces22_23 = address22_23.Assign(devices22_23);
address24_25.SetBase("10.1.28.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces24_25 = address24_25.Assign(devices24_25);
address24_27.SetBase("10.1.29.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces24_27 = address24_27.Assign(devices24_27);
address26_27.SetBase("10.1.30.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces26_27 = address26_27.Assign(devices26_27);
address28_29.SetBase("10.1.31.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces28_29 = address28_29.Assign(devices28_29);
address28_31.SetBase("10.1.32.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces28_31 = address28_31.Assign(devices28_31);
address28_43.SetBase("10.1.33.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces28_43 = address28_43.Assign(devices28_43);
address30_31.SetBase("10.1.34.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces30_31 = address30_31.Assign(devices30_31);
address32_33.SetBase("10.1.35.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces32_33 = address32_33.Assign(devices32_33);
address32_35.SetBase("10.1.36.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces32_35 = address32_35.Assign(devices32_35);
address32_43.SetBase("10.1.37.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces32_43 = address32_43.Assign(devices32_43);
address34_35.SetBase("10.1.38.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces34_35 = address34_35.Assign(devices34_35);
address36_37.SetBase("10.1.39.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces36_37 = address36_37.Assign(devices36_37);
address36_39.SetBase("10.1.40.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces36_39 = address36_39.Assign(devices36_39);
address36_43.SetBase("10.1.41.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces36_43 = address36_43.Assign(devices36_43);
address38_39.SetBase("10.1.42.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces38_39 = address38_39.Assign(devices38_39);
address40_41.SetBase("10.1.43.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces40_41 = address40_41.Assign(devices40_41);
address40_43.SetBase("10.1.44.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces40_43 = address40_43.Assign(devices40_43);
address42_43.SetBase("10.1.45.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces42_43 = address42_43.Assign(devices42_43);
address44_45.SetBase("10.1.46.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces44_45 = address44_45.Assign(devices44_45);
address44_47.SetBase("10.1.47.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces44_47 = address44_47.Assign(devices44_47);
address46_47.SetBase("10.1.48.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces46_47 = address46_47.Assign(devices46_47);
address48_49.SetBase("10.1.49.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces48_49 = address48_49.Assign(devices48_49);
address48_51.SetBase("10.1.50.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces48_51 = address48_51.Assign(devices48_51);
address50_51.SetBase("10.1.51.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces50_51 = address50_51.Assign(devices50_51);



  // 启用流监测器，使用 FlowMonitorHelper 启用流监测器，并将其安装在所有的设备上
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll();
  
  // Create a packet sink on the star "hub" to receive these packets
    uint16_t port = 50000;//端口号50000
    ApplicationContainer sinkApp;//这一句是定义服务器的
    Address sinkLocalAddress (InetSocketAddress (Ipv4Address::GetAny (), port));
    PacketSinkHelper sinkHelper ("ns3::TcpSocketFactory", sinkLocalAddress);//接收和消耗生成到IP地址和端口的流量
    //sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[13].Get(1)));//9是服务器端   已经改了是tree的
    //sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[34].Get(1)));//33是服务器端  已经改了是tree的
    //sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[21].Get(0)));//16是服务器端  已经改了是tree的
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[24].Get(1)));//21是服务器端
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[47].Get(0)));//46是服务器端
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[27].Get(0)));//24是服务器端
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[50].Get(1)));//51是服务器端
    sinkApp.Start (Seconds (0.0));
    sinkApp.Stop (Seconds (60.0));
    //服务端在0s的时候开始服务，30s的时候停止

    OnOffHelper clientHelper ("ns3::TcpSocketFactory", Address ());//这句话是在定义客户端，设置了IP地址和tcp端口号
    clientHelper.SetAttribute("DataRate", StringValue("100Mbps"));
  clientHelper.SetAttribute("PacketSize", UintegerValue(100));
    clientHelper.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
    clientHelper.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
    
    //这三句设置客户端应用层
    //ConstantRandomVariable是随机数，意思应该是客户端建立连接和断开连接时间是随机的。就是不是一直在收发数据。

    ApplicationContainer clientApps;
    //0->9
    //AddressValue remoteAddress (InetSocketAddress (interfaces8_9.GetAddress (1), port));
    //clientHelper.SetAttribute("Remote",remoteAddress);    
    //clientApps.Add(clientHelper.Install(nodeAdjacencyList[0].Get(0)));
    //0负责发送数据，使用的应用层定义是上面的clientHelper

    //0->33
    //remoteAddress=AddressValue(InetSocketAddress (interfaces32_33.GetAddress (1), port));
    //clientHelper.SetAttribute("Remote",remoteAddress);
    //clientApps.Add(clientHelper.Install(nodeAdjacencyList[0].Get(0)));
    //0负责发送数据，使用的应用层定义是上面的clientHelper
    
    //0->40
    //remoteAddress=AddressValue(InetSocketAddress (interfaces40_41.GetAddress (0), port));
    //clientHelper.SetAttribute("Remote",remoteAddress);
    //clientApps.Add(clientHelper.Install(nodeAdjacencyList[0].Get(0)));
    //0负责发送数据，使用的应用层定义是上面的clientHelper
    
    //4->16
    //remoteAddress=AddressValue(InetSocketAddress (interfaces16_17.GetAddress (0), port));
    //clientHelper.SetAttribute("Remote",remoteAddress);
    //clientApps.Add(clientHelper.Install(nodeAdjacencyList[9].Get(0)));
    //4负责发送数据，使用的应用层定义是上面的clientHelper
    
    //20->21
    AddressValue remoteAddress (InetSocketAddress (interfaces20_21.GetAddress (1), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[24].Get(0)));
    //20负责发送数据，使用的应用层定义是上面的clientHelper
    
    //20->46
    remoteAddress=AddressValue(InetSocketAddress (interfaces46_47.GetAddress (0), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[24].Get(0)));
    //20负责发送数据，使用的应用层定义是上面的clientHelper
    
    //12->24
    remoteAddress=AddressValue(InetSocketAddress (interfaces12_13.GetAddress (0), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[17].Get(0)));
    //12负责发送数据，使用的应用层定义是上面的clientHelper
    
    //50->51
    remoteAddress=AddressValue(InetSocketAddress (interfaces50_51.GetAddress (1), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[50].Get(0)));
    //50负责发送数据，使用的应用层定义是上面的clientHelper
    
    clientApps.Start(Seconds(1.0));
    clientApps.Stop (Seconds (61.0));
  
  // 启用 OSPF
  Ipv4GlobalRoutingHelper::PopulateRoutingTables();
  
  
  
  
  // 配置输出流
  AsciiTraceHelper throughputAscii, lossAscii, delayAscii;
  Ptr<OutputStreamWrapper> throughputStream = throughputAscii.CreateFileStream("D32tree_throughput.txt");
  Ptr<OutputStreamWrapper> lossStream = lossAscii.CreateFileStream("D32tree_loss.txt");
  Ptr<OutputStreamWrapper> delayStream = delayAscii.CreateFileStream("D32tree_delay.txt");
  
  // 输出文件的表头
  *throughputStream->GetStream() << "Time (s)\tThroughput (Mbps)\n";
  *lossStream->GetStream() << "Time (s)\tLoss Rate (%)\n";
  *delayStream->GetStream() << "Time (s)\tAverage Delay (s)\n";
  
  // 在仿真运行期间定期计算性能指标
  Simulator::Schedule(Seconds(1.0), &CalculateMetrics, monitor, throughputStream, lossStream, delayStream, Seconds(60.0));
  
  // 运行仿真
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}
