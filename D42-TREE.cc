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
  nodes.Create(105);
  
  //各条边的节点组合
  vector<NodeContainer> nodeAdjacencyList(104);

  nodeAdjacencyList[0]=NodeContainer(nodes.Get(21), nodes.Get(63)); 
nodeAdjacencyList[1]=NodeContainer(nodes.Get(21), nodes.Get(68)); 
nodeAdjacencyList[2]=NodeContainer(nodes.Get(21), nodes.Get(69)); 
nodeAdjacencyList[3]=NodeContainer(nodes.Get(21), nodes.Get(70)); 
nodeAdjacencyList[4]=NodeContainer(nodes.Get(21), nodes.Get(71)); 
nodeAdjacencyList[5]=NodeContainer(nodes.Get(21), nodes.Get(42)); 
nodeAdjacencyList[6]=NodeContainer(nodes.Get(21), nodes.Get(0)); 
nodeAdjacencyList[7]=NodeContainer(nodes.Get(63), nodes.Get(34)); 
nodeAdjacencyList[8]=NodeContainer(nodes.Get(63), nodes.Get(35)); 
nodeAdjacencyList[9]=NodeContainer(nodes.Get(63), nodes.Get(36)); 
nodeAdjacencyList[10]=NodeContainer(nodes.Get(63), nodes.Get(37)); 
nodeAdjacencyList[11]=NodeContainer(nodes.Get(63), nodes.Get(84)); 
nodeAdjacencyList[12]=NodeContainer(nodes.Get(68), nodes.Get(26)); 
nodeAdjacencyList[13]=NodeContainer(nodes.Get(68), nodes.Get(39)); 
nodeAdjacencyList[14]=NodeContainer(nodes.Get(68), nodes.Get(40)); 
nodeAdjacencyList[15]=NodeContainer(nodes.Get(68), nodes.Get(41)); 
nodeAdjacencyList[16]=NodeContainer(nodes.Get(68), nodes.Get(89)); 
nodeAdjacencyList[17]=NodeContainer(nodes.Get(26), nodes.Get(73)); 
nodeAdjacencyList[18]=NodeContainer(nodes.Get(26), nodes.Get(74)); 
nodeAdjacencyList[19]=NodeContainer(nodes.Get(26), nodes.Get(75)); 
nodeAdjacencyList[20]=NodeContainer(nodes.Get(26), nodes.Get(47)); 
nodeAdjacencyList[21]=NodeContainer(nodes.Get(26), nodes.Get(5)); 
nodeAdjacencyList[22]=NodeContainer(nodes.Get(69), nodes.Get(27)); 
nodeAdjacencyList[23]=NodeContainer(nodes.Get(69), nodes.Get(22)); 
nodeAdjacencyList[24]=NodeContainer(nodes.Get(69), nodes.Get(90)); 
nodeAdjacencyList[25]=NodeContainer(nodes.Get(27), nodes.Get(48)); 
nodeAdjacencyList[26]=NodeContainer(nodes.Get(27), nodes.Get(6)); 
nodeAdjacencyList[27]=NodeContainer(nodes.Get(70), nodes.Get(28)); 
nodeAdjacencyList[28]=NodeContainer(nodes.Get(70), nodes.Get(23)); 
nodeAdjacencyList[29]=NodeContainer(nodes.Get(70), nodes.Get(91)); 
nodeAdjacencyList[30]=NodeContainer(nodes.Get(28), nodes.Get(49)); 
nodeAdjacencyList[31]=NodeContainer(nodes.Get(28), nodes.Get(7)); 
nodeAdjacencyList[32]=NodeContainer(nodes.Get(71), nodes.Get(29)); 
nodeAdjacencyList[33]=NodeContainer(nodes.Get(71), nodes.Get(24)); 
nodeAdjacencyList[34]=NodeContainer(nodes.Get(71), nodes.Get(92)); 
nodeAdjacencyList[35]=NodeContainer(nodes.Get(29), nodes.Get(50)); 
nodeAdjacencyList[36]=NodeContainer(nodes.Get(29), nodes.Get(8)); 
nodeAdjacencyList[37]=NodeContainer(nodes.Get(34), nodes.Get(76)); 
nodeAdjacencyList[38]=NodeContainer(nodes.Get(34), nodes.Get(55)); 
nodeAdjacencyList[39]=NodeContainer(nodes.Get(34), nodes.Get(13)); 
nodeAdjacencyList[40]=NodeContainer(nodes.Get(76), nodes.Get(97)); 
nodeAdjacencyList[41]=NodeContainer(nodes.Get(35), nodes.Get(77)); 
nodeAdjacencyList[42]=NodeContainer(nodes.Get(35), nodes.Get(56)); 
nodeAdjacencyList[43]=NodeContainer(nodes.Get(35), nodes.Get(14)); 
nodeAdjacencyList[44]=NodeContainer(nodes.Get(77), nodes.Get(30)); 
nodeAdjacencyList[45]=NodeContainer(nodes.Get(77), nodes.Get(98)); 
nodeAdjacencyList[46]=NodeContainer(nodes.Get(36), nodes.Get(78)); 
nodeAdjacencyList[47]=NodeContainer(nodes.Get(36), nodes.Get(57)); 
nodeAdjacencyList[48]=NodeContainer(nodes.Get(36), nodes.Get(15)); 
nodeAdjacencyList[49]=NodeContainer(nodes.Get(78), nodes.Get(99)); 
nodeAdjacencyList[50]=NodeContainer(nodes.Get(37), nodes.Get(79)); 
nodeAdjacencyList[51]=NodeContainer(nodes.Get(37), nodes.Get(58)); 
nodeAdjacencyList[52]=NodeContainer(nodes.Get(37), nodes.Get(16)); 
nodeAdjacencyList[53]=NodeContainer(nodes.Get(79), nodes.Get(100)); 
nodeAdjacencyList[54]=NodeContainer(nodes.Get(39), nodes.Get(81)); 
nodeAdjacencyList[55]=NodeContainer(nodes.Get(39), nodes.Get(67)); 
nodeAdjacencyList[56]=NodeContainer(nodes.Get(39), nodes.Get(60)); 
nodeAdjacencyList[57]=NodeContainer(nodes.Get(39), nodes.Get(18)); 
nodeAdjacencyList[58]=NodeContainer(nodes.Get(81), nodes.Get(102)); 
nodeAdjacencyList[59]=NodeContainer(nodes.Get(40), nodes.Get(82)); 
nodeAdjacencyList[60]=NodeContainer(nodes.Get(40), nodes.Get(61)); 
nodeAdjacencyList[61]=NodeContainer(nodes.Get(40), nodes.Get(19)); 
nodeAdjacencyList[62]=NodeContainer(nodes.Get(82), nodes.Get(103)); 
nodeAdjacencyList[63]=NodeContainer(nodes.Get(41), nodes.Get(83)); 
nodeAdjacencyList[64]=NodeContainer(nodes.Get(41), nodes.Get(62)); 
nodeAdjacencyList[65]=NodeContainer(nodes.Get(41), nodes.Get(20)); 
nodeAdjacencyList[66]=NodeContainer(nodes.Get(83), nodes.Get(104)); 
nodeAdjacencyList[67]=NodeContainer(nodes.Get(73), nodes.Get(31)); 
nodeAdjacencyList[68]=NodeContainer(nodes.Get(73), nodes.Get(94)); 
nodeAdjacencyList[69]=NodeContainer(nodes.Get(31), nodes.Get(80)); 
nodeAdjacencyList[70]=NodeContainer(nodes.Get(31), nodes.Get(52)); 
nodeAdjacencyList[71]=NodeContainer(nodes.Get(31), nodes.Get(10)); 
nodeAdjacencyList[72]=NodeContainer(nodes.Get(74), nodes.Get(32)); 
nodeAdjacencyList[73]=NodeContainer(nodes.Get(74), nodes.Get(95)); 
nodeAdjacencyList[74]=NodeContainer(nodes.Get(32), nodes.Get(53)); 
nodeAdjacencyList[75]=NodeContainer(nodes.Get(32), nodes.Get(11)); 
nodeAdjacencyList[76]=NodeContainer(nodes.Get(75), nodes.Get(33)); 
nodeAdjacencyList[77]=NodeContainer(nodes.Get(75), nodes.Get(96)); 
nodeAdjacencyList[78]=NodeContainer(nodes.Get(33), nodes.Get(54)); 
nodeAdjacencyList[79]=NodeContainer(nodes.Get(33), nodes.Get(12)); 
nodeAdjacencyList[80]=NodeContainer(nodes.Get(22), nodes.Get(64)); 
nodeAdjacencyList[81]=NodeContainer(nodes.Get(22), nodes.Get(43)); 
nodeAdjacencyList[82]=NodeContainer(nodes.Get(22), nodes.Get(1));
nodeAdjacencyList[83]=NodeContainer(nodes.Get(64), nodes.Get(85)); 
nodeAdjacencyList[84]=NodeContainer(nodes.Get(23), nodes.Get(65)); 
nodeAdjacencyList[85]=NodeContainer(nodes.Get(23), nodes.Get(44)); 
nodeAdjacencyList[86]=NodeContainer(nodes.Get(23), nodes.Get(2)); 
nodeAdjacencyList[87]=NodeContainer(nodes.Get(65), nodes.Get(86)); 
nodeAdjacencyList[88]=NodeContainer(nodes.Get(24), nodes.Get(66)); 
nodeAdjacencyList[89]=NodeContainer(nodes.Get(24), nodes.Get(45)); 
nodeAdjacencyList[90]=NodeContainer(nodes.Get(24), nodes.Get(3)); 
nodeAdjacencyList[91]=NodeContainer(nodes.Get(66), nodes.Get(87)); 
nodeAdjacencyList[92]=NodeContainer(nodes.Get(30), nodes.Get(72)); 
nodeAdjacencyList[93]=NodeContainer(nodes.Get(30), nodes.Get(51)); 
nodeAdjacencyList[94]=NodeContainer(nodes.Get(30), nodes.Get(9)); 
nodeAdjacencyList[95]=NodeContainer(nodes.Get(72), nodes.Get(93)); 
nodeAdjacencyList[96]=NodeContainer(nodes.Get(67), nodes.Get(25)); 
nodeAdjacencyList[97]=NodeContainer(nodes.Get(67), nodes.Get(88)); 
nodeAdjacencyList[98]=NodeContainer(nodes.Get(25), nodes.Get(46)); 
nodeAdjacencyList[99]=NodeContainer(nodes.Get(25), nodes.Get(4)); 
nodeAdjacencyList[100]=NodeContainer(nodes.Get(80), nodes.Get(38)); 
nodeAdjacencyList[101]=NodeContainer(nodes.Get(80), nodes.Get(101)); 
nodeAdjacencyList[102]=NodeContainer(nodes.Get(38), nodes.Get(59)); 
nodeAdjacencyList[103]=NodeContainer(nodes.Get(38), nodes.Get(17)); 




  // 创建节点之间的连接，分别设置传输速率和传播延迟
  
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute("DataRate", StringValue("100Mbps"));
  p2p.SetChannelAttribute("Delay", StringValue("1ms"));

  //通过 Install 函数将设备配置应用到相应的节点上，形成了网络拓扑
  NetDeviceContainer 
  devices21_63,
devices21_68,
devices21_69,
devices21_70,
devices21_71,
devices21_42,
devices21_0,
devices63_34,
devices63_35,
devices63_36,
devices63_37,
devices63_84,
devices68_26,
devices68_39,
devices68_40,
devices68_41,
devices68_89,
devices26_73,
devices26_74,
devices26_75,
devices26_47,
devices26_5,
devices69_27,
devices69_22,
devices69_90,
devices27_48,
devices27_6,
devices70_28,
devices70_23,
devices70_91,
devices28_49,
devices28_7,
devices71_29,
devices71_24,
devices71_92,
devices29_50,
devices29_8,
devices34_76,
devices34_55,
devices34_13,
devices76_97,
devices35_77,
devices35_56,
devices35_14,
devices77_30,
devices77_98,
devices36_78,
devices36_57,
devices36_15,
devices78_99,
devices37_79,
devices37_58,
devices37_16,
devices79_100,
devices39_81,
devices39_67,
devices39_60,
devices39_18,
devices81_102,
devices40_82,
devices40_61,
devices40_19,
devices82_103,
devices41_83,
devices41_62,
devices41_20,
devices83_104,
devices73_31,
devices73_94,
devices31_80,
devices31_52,
devices31_10,
devices74_32,
devices74_95,
devices32_53,
devices32_11,
devices75_33,
devices75_96,
devices33_54,
devices33_12,
devices22_64,
devices22_43,
devices22_1,
devices64_85,
devices23_65,
devices23_44,
devices23_2,
devices65_86,
devices24_66,
devices24_45,
devices24_3,
devices66_87,
devices30_72,
devices30_51,
devices30_9,
devices72_93,
devices67_25,
devices67_88,
devices25_46,
devices25_4,
devices80_38,
devices80_101,
devices38_59,
devices38_17;



devices21_63= p2p.Install(nodes.Get(21), nodes.Get(63)); 
devices21_68= p2p.Install(nodes.Get(21), nodes.Get(68)); 
devices21_69= p2p.Install(nodes.Get(21), nodes.Get(69)); 
devices21_70= p2p.Install(nodes.Get(21), nodes.Get(70)); 
devices21_71= p2p.Install(nodes.Get(21), nodes.Get(71)); 
devices21_42= p2p.Install(nodes.Get(21), nodes.Get(42)); 
devices21_0= p2p.Install(nodes.Get(21), nodes.Get(0)); 
devices63_34= p2p.Install(nodes.Get(63), nodes.Get(34)); 
devices63_35= p2p.Install(nodes.Get(63), nodes.Get(35)); 
devices63_36= p2p.Install(nodes.Get(63), nodes.Get(36)); 
devices63_37= p2p.Install(nodes.Get(63), nodes.Get(37)); 
devices63_84= p2p.Install(nodes.Get(63), nodes.Get(84)); 
devices68_26= p2p.Install(nodes.Get(68), nodes.Get(26)); 
devices68_39= p2p.Install(nodes.Get(68), nodes.Get(39)); 
devices68_40= p2p.Install(nodes.Get(68), nodes.Get(40)); 
devices68_41= p2p.Install(nodes.Get(68), nodes.Get(41)); 
devices68_89= p2p.Install(nodes.Get(68), nodes.Get(89)); 
devices26_73= p2p.Install(nodes.Get(26), nodes.Get(73)); 
devices26_74= p2p.Install(nodes.Get(26), nodes.Get(74)); 
devices26_75= p2p.Install(nodes.Get(26), nodes.Get(75)); 
devices26_47= p2p.Install(nodes.Get(26), nodes.Get(47)); 
devices26_5= p2p.Install(nodes.Get(26), nodes.Get(5)); 
devices69_27= p2p.Install(nodes.Get(69), nodes.Get(27)); 
devices69_22= p2p.Install(nodes.Get(69), nodes.Get(22)); 
devices69_90= p2p.Install(nodes.Get(69), nodes.Get(90)); 
devices27_48= p2p.Install(nodes.Get(27), nodes.Get(48)); 
devices27_6= p2p.Install(nodes.Get(27), nodes.Get(6)); 
devices70_28= p2p.Install(nodes.Get(70), nodes.Get(28)); 
devices70_23= p2p.Install(nodes.Get(70), nodes.Get(23)); 
devices70_91= p2p.Install(nodes.Get(70), nodes.Get(91)); 
devices28_49= p2p.Install(nodes.Get(28), nodes.Get(49)); 
devices28_7= p2p.Install(nodes.Get(28), nodes.Get(7)); 
devices71_29= p2p.Install(nodes.Get(71), nodes.Get(29)); 
devices71_24= p2p.Install(nodes.Get(71), nodes.Get(24)); 
devices71_92= p2p.Install(nodes.Get(71), nodes.Get(92)); 
devices29_50= p2p.Install(nodes.Get(29), nodes.Get(50)); 
devices29_8= p2p.Install(nodes.Get(29), nodes.Get(8)); 
devices34_76= p2p.Install(nodes.Get(34), nodes.Get(76)); 
devices34_55= p2p.Install(nodes.Get(34), nodes.Get(55)); 
devices34_13= p2p.Install(nodes.Get(34), nodes.Get(13)); 
devices76_97= p2p.Install(nodes.Get(76), nodes.Get(97)); 
devices35_77= p2p.Install(nodes.Get(35), nodes.Get(77)); 
devices35_56= p2p.Install(nodes.Get(35), nodes.Get(56)); 
devices35_14= p2p.Install(nodes.Get(35), nodes.Get(14)); 
devices77_30= p2p.Install(nodes.Get(77), nodes.Get(30)); 
devices77_98= p2p.Install(nodes.Get(77), nodes.Get(98)); 
devices36_78= p2p.Install(nodes.Get(36), nodes.Get(78)); 
devices36_57= p2p.Install(nodes.Get(36), nodes.Get(57)); 
devices36_15= p2p.Install(nodes.Get(36), nodes.Get(15)); 
devices78_99= p2p.Install(nodes.Get(78), nodes.Get(99)); 
devices37_79= p2p.Install(nodes.Get(37), nodes.Get(79)); 
devices37_58= p2p.Install(nodes.Get(37), nodes.Get(58)); 
devices37_16= p2p.Install(nodes.Get(37), nodes.Get(16)); 
devices79_100= p2p.Install(nodes.Get(79), nodes.Get(100)); 
devices39_81= p2p.Install(nodes.Get(39), nodes.Get(81)); 
devices39_67= p2p.Install(nodes.Get(39), nodes.Get(67)); 
devices39_60= p2p.Install(nodes.Get(39), nodes.Get(60)); 
devices39_18= p2p.Install(nodes.Get(39), nodes.Get(18)); 
devices81_102= p2p.Install(nodes.Get(81), nodes.Get(102)); 
devices40_82= p2p.Install(nodes.Get(40), nodes.Get(82)); 
devices40_61= p2p.Install(nodes.Get(40), nodes.Get(61)); 
devices40_19= p2p.Install(nodes.Get(40), nodes.Get(19)); 
devices82_103= p2p.Install(nodes.Get(82), nodes.Get(103)); 
devices41_83= p2p.Install(nodes.Get(41), nodes.Get(83)); 
devices41_62= p2p.Install(nodes.Get(41), nodes.Get(62)); 
devices41_20= p2p.Install(nodes.Get(41), nodes.Get(20)); 
devices83_104= p2p.Install(nodes.Get(83), nodes.Get(104)); 
devices73_31= p2p.Install(nodes.Get(73), nodes.Get(31)); 
devices73_94= p2p.Install(nodes.Get(73), nodes.Get(94)); 
devices31_80= p2p.Install(nodes.Get(31), nodes.Get(80)); 
devices31_52= p2p.Install(nodes.Get(31), nodes.Get(52)); 
devices31_10= p2p.Install(nodes.Get(31), nodes.Get(10)); 
devices74_32= p2p.Install(nodes.Get(74), nodes.Get(32)); 
devices74_95= p2p.Install(nodes.Get(74), nodes.Get(95)); 
devices32_53= p2p.Install(nodes.Get(32), nodes.Get(53)); 
devices32_11= p2p.Install(nodes.Get(32), nodes.Get(11)); 
devices75_33= p2p.Install(nodes.Get(75), nodes.Get(33)); 
devices75_96= p2p.Install(nodes.Get(75), nodes.Get(96)); 
devices33_54= p2p.Install(nodes.Get(33), nodes.Get(54)); 
devices33_12= p2p.Install(nodes.Get(33), nodes.Get(12)); 
devices22_64= p2p.Install(nodes.Get(22), nodes.Get(64)); 
devices22_43= p2p.Install(nodes.Get(22), nodes.Get(43)); 
devices22_1= p2p.Install(nodes.Get(22), nodes.Get(1)); 
devices64_85= p2p.Install(nodes.Get(64), nodes.Get(85)); 
devices23_65= p2p.Install(nodes.Get(23), nodes.Get(65)); 
devices23_44= p2p.Install(nodes.Get(23), nodes.Get(44)); 
devices23_2= p2p.Install(nodes.Get(23), nodes.Get(2)); 
devices65_86= p2p.Install(nodes.Get(65), nodes.Get(86)); 
devices24_66= p2p.Install(nodes.Get(24), nodes.Get(66)); 
devices24_45= p2p.Install(nodes.Get(24), nodes.Get(45)); 
devices24_3= p2p.Install(nodes.Get(24), nodes.Get(3)); 
devices66_87= p2p.Install(nodes.Get(66), nodes.Get(87)); 
devices30_72= p2p.Install(nodes.Get(30), nodes.Get(72)); 
devices30_51= p2p.Install(nodes.Get(30), nodes.Get(51)); 
devices30_9= p2p.Install(nodes.Get(30), nodes.Get(9)); 
devices72_93= p2p.Install(nodes.Get(72), nodes.Get(93)); 
devices67_25= p2p.Install(nodes.Get(67), nodes.Get(25)); 
devices67_88= p2p.Install(nodes.Get(67), nodes.Get(88)); 
devices25_46= p2p.Install(nodes.Get(25), nodes.Get(46)); 
devices25_4= p2p.Install(nodes.Get(25), nodes.Get(4)); 
devices80_38= p2p.Install(nodes.Get(80), nodes.Get(38)); 
devices80_101= p2p.Install(nodes.Get(80), nodes.Get(101)); 
devices38_59= p2p.Install(nodes.Get(38), nodes.Get(59)); 
devices38_17= p2p.Install(nodes.Get(38), nodes.Get(17)); 


  // 安装Internet协议栈
  InternetStackHelper internet;
  internet.Install(nodes);
  

  Ipv4AddressHelper 
  address21_63,
address21_68,
address21_69,
address21_70,
address21_71,
address21_42,
address21_0,
address63_34,
address63_35,
address63_36,
address63_37,
address63_84,
address68_26,
address68_39,
address68_40,
address68_41,
address68_89,
address26_73,
address26_74,
address26_75,
address26_47,
address26_5,
address69_27,
address69_22,
address69_90,
address27_48,
address27_6,
address70_28,
address70_23,
address70_91,
address28_49,
address28_7,
address71_29,
address71_24,
address71_92,
address29_50,
address29_8,
address34_76,
address34_55,
address34_13,
address76_97,
address35_77,
address35_56,
address35_14,
address77_30,
address77_98,
address36_78,
address36_57,
address36_15,
address78_99,
address37_79,
address37_58,
address37_16,
address79_100,
address39_81,
address39_67,
address39_60,
address39_18,
address81_102,
address40_82,
address40_61,
address40_19,
address82_103,
address41_83,
address41_62,
address41_20,
address83_104,
address73_31,
address73_94,
address31_80,
address31_52,
address31_10,
address74_32,
address74_95,
address32_53,
address32_11,
address75_33,
address75_96,
address33_54,
address33_12,
address22_64,
address22_43,
address22_1,
address64_85,
address23_65,
address23_44,
address23_2,
address65_86,
address24_66,
address24_45,
address24_3,
address66_87,
address30_72,
address30_51,
address30_9,
address72_93,
address67_25,
address67_88,
address25_46,
address25_4,
address80_38,
address80_101,
address38_59,
address38_17;


  
address21_63.SetBase("10.1.1.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_63 = address21_63.Assign(devices21_63);
address21_68.SetBase("10.1.2.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_68 = address21_68.Assign(devices21_68);
address21_69.SetBase("10.1.3.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_69 = address21_69.Assign(devices21_69);
address21_70.SetBase("10.1.4.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_70 = address21_70.Assign(devices21_70);
address21_71.SetBase("10.1.5.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_71 = address21_71.Assign(devices21_71);
address21_42.SetBase("10.1.6.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_42 = address21_42.Assign(devices21_42);
address21_0.SetBase("10.1.7.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_0 = address21_0.Assign(devices21_0);
address63_34.SetBase("10.1.8.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces63_34 = address63_34.Assign(devices63_34);
address63_35.SetBase("10.1.9.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces63_35 = address63_35.Assign(devices63_35);
address63_36.SetBase("10.1.10.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces63_36 = address63_36.Assign(devices63_36);
address63_37.SetBase("10.1.11.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces63_37 = address63_37.Assign(devices63_37);
address63_84.SetBase("10.1.12.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces63_84 = address63_84.Assign(devices63_84);
address68_26.SetBase("10.1.13.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces68_26 = address68_26.Assign(devices68_26);
address68_39.SetBase("10.1.14.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces68_39 = address68_39.Assign(devices68_39);
address68_40.SetBase("10.1.15.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces68_40 = address68_40.Assign(devices68_40);
address68_41.SetBase("10.1.16.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces68_41 = address68_41.Assign(devices68_41);
address68_89.SetBase("10.1.17.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces68_89 = address68_89.Assign(devices68_89);
address26_73.SetBase("10.1.18.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces26_73 = address26_73.Assign(devices26_73);
address26_74.SetBase("10.1.19.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces26_74 = address26_74.Assign(devices26_74);
address26_75.SetBase("10.1.20.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces26_75 = address26_75.Assign(devices26_75);
address26_47.SetBase("10.1.21.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces26_47 = address26_47.Assign(devices26_47);
address26_5.SetBase("10.1.22.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces26_5 = address26_5.Assign(devices26_5);
address69_27.SetBase("10.1.23.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces69_27 = address69_27.Assign(devices69_27);
address69_22.SetBase("10.1.24.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces69_22 = address69_22.Assign(devices69_22);
address69_90.SetBase("10.1.25.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces69_90 = address69_90.Assign(devices69_90);
address27_48.SetBase("10.1.26.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces27_48 = address27_48.Assign(devices27_48);
address27_6.SetBase("10.1.27.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces27_6 = address27_6.Assign(devices27_6);
address70_28.SetBase("10.1.28.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces70_28 = address70_28.Assign(devices70_28);
address70_23.SetBase("10.1.29.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces70_23 = address70_23.Assign(devices70_23);
address70_91.SetBase("10.1.30.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces70_91 = address70_91.Assign(devices70_91);
address28_49.SetBase("10.1.31.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces28_49 = address28_49.Assign(devices28_49);
address28_7.SetBase("10.1.32.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces28_7 = address28_7.Assign(devices28_7);
address71_29.SetBase("10.1.33.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces71_29 = address71_29.Assign(devices71_29);
address71_24.SetBase("10.1.34.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces71_24 = address71_24.Assign(devices71_24);
address71_92.SetBase("10.1.35.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces71_92 = address71_92.Assign(devices71_92);
address29_50.SetBase("10.1.36.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces29_50 = address29_50.Assign(devices29_50);
address29_8.SetBase("10.1.37.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces29_8 = address29_8.Assign(devices29_8);
address34_76.SetBase("10.1.38.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces34_76 = address34_76.Assign(devices34_76);
address34_55.SetBase("10.1.39.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces34_55 = address34_55.Assign(devices34_55);
address34_13.SetBase("10.1.40.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces34_13 = address34_13.Assign(devices34_13);
address76_97.SetBase("10.1.41.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces76_97 = address76_97.Assign(devices76_97);
address35_77.SetBase("10.1.42.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces35_77 = address35_77.Assign(devices35_77);
address35_56.SetBase("10.1.43.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces35_56 = address35_56.Assign(devices35_56);
address35_14.SetBase("10.1.44.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces35_14 = address35_14.Assign(devices35_14);
address77_30.SetBase("10.1.45.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces77_30 = address77_30.Assign(devices77_30);
address77_98.SetBase("10.1.46.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces77_98 = address77_98.Assign(devices77_98);
address36_78.SetBase("10.1.47.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces36_78 = address36_78.Assign(devices36_78);
address36_57.SetBase("10.1.48.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces36_57 = address36_57.Assign(devices36_57);
address36_15.SetBase("10.1.49.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces36_15 = address36_15.Assign(devices36_15);
address78_99.SetBase("10.1.50.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces78_99 = address78_99.Assign(devices78_99);
address37_79.SetBase("10.1.51.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces37_79 = address37_79.Assign(devices37_79);
address37_58.SetBase("10.1.52.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces37_58 = address37_58.Assign(devices37_58);
address37_16.SetBase("10.1.53.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces37_16 = address37_16.Assign(devices37_16);
address79_100.SetBase("10.1.54.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces79_100 = address79_100.Assign(devices79_100);
address39_81.SetBase("10.1.55.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces39_81 = address39_81.Assign(devices39_81);
address39_67.SetBase("10.1.56.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces39_67 = address39_67.Assign(devices39_67);
address39_60.SetBase("10.1.57.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces39_60 = address39_60.Assign(devices39_60);
address39_18.SetBase("10.1.58.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces39_18 = address39_18.Assign(devices39_18);
address81_102.SetBase("10.1.59.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces81_102 = address81_102.Assign(devices81_102);
address40_82.SetBase("10.1.60.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces40_82 = address40_82.Assign(devices40_82);
address40_61.SetBase("10.1.61.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces40_61 = address40_61.Assign(devices40_61);
address40_19.SetBase("10.1.62.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces40_19 = address40_19.Assign(devices40_19);
address82_103.SetBase("10.1.63.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces82_103 = address82_103.Assign(devices82_103);
address41_83.SetBase("10.1.64.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces41_83 = address41_83.Assign(devices41_83);
address41_62.SetBase("10.1.65.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces41_62 = address41_62.Assign(devices41_62);
address41_20.SetBase("10.1.66.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces41_20 = address41_20.Assign(devices41_20);
address83_104.SetBase("10.1.67.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces83_104 = address83_104.Assign(devices83_104);
address73_31.SetBase("10.1.68.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces73_31 = address73_31.Assign(devices73_31);
address73_94.SetBase("10.1.69.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces73_94 = address73_94.Assign(devices73_94);
address31_80.SetBase("10.1.70.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces31_80 = address31_80.Assign(devices31_80);
address31_52.SetBase("10.1.71.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces31_52 = address31_52.Assign(devices31_52);
address31_10.SetBase("10.1.72.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces31_10 = address31_10.Assign(devices31_10);
address74_32.SetBase("10.1.73.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces74_32 = address74_32.Assign(devices74_32);
address74_95.SetBase("10.1.74.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces74_95 = address74_95.Assign(devices74_95);
address32_53.SetBase("10.1.75.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces32_53 = address32_53.Assign(devices32_53);
address32_11.SetBase("10.1.76.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces32_11 = address32_11.Assign(devices32_11);
address75_33.SetBase("10.1.77.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces75_33 = address75_33.Assign(devices75_33);
address75_96.SetBase("10.1.78.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces75_96 = address75_96.Assign(devices75_96);
address33_54.SetBase("10.1.79.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces33_54 = address33_54.Assign(devices33_54);
address33_12.SetBase("10.1.80.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces33_12 = address33_12.Assign(devices33_12);
address22_64.SetBase("10.1.81.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces22_64 = address22_64.Assign(devices22_64);
address22_43.SetBase("10.1.82.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces22_43 = address22_43.Assign(devices22_43);
address22_1.SetBase("10.1.83.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces22_1 = address22_1.Assign(devices22_1);
address64_85.SetBase("10.1.84.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces64_85 = address64_85.Assign(devices64_85);
address23_65.SetBase("10.1.85.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces23_65 = address23_65.Assign(devices23_65);
address23_44.SetBase("10.1.86.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces23_44 = address23_44.Assign(devices23_44);
address23_2.SetBase("10.1.87.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces23_2 = address23_2.Assign(devices23_2);
address65_86.SetBase("10.1.88.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces65_86 = address65_86.Assign(devices65_86);
address24_66.SetBase("10.1.89.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces24_66 = address24_66.Assign(devices24_66);
address24_45.SetBase("10.1.90.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces24_45 = address24_45.Assign(devices24_45);
address24_3.SetBase("10.1.91.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces24_3 = address24_3.Assign(devices24_3);
address66_87.SetBase("10.1.92.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces66_87 = address66_87.Assign(devices66_87);
address30_72.SetBase("10.1.93.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces30_72 = address30_72.Assign(devices30_72);
address30_51.SetBase("10.1.94.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces30_51 = address30_51.Assign(devices30_51);
address30_9.SetBase("10.1.95.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces30_9 = address30_9.Assign(devices30_9);
address72_93.SetBase("10.1.96.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces72_93 = address72_93.Assign(devices72_93);
address67_25.SetBase("10.1.97.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces67_25 = address67_25.Assign(devices67_25);
address67_88.SetBase("10.1.98.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces67_88 = address67_88.Assign(devices67_88);
address25_46.SetBase("10.1.99.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces25_46 = address25_46.Assign(devices25_46);
address25_4.SetBase("10.1.100.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces25_4 = address25_4.Assign(devices25_4);
address80_38.SetBase("10.1.101.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces80_38 = address80_38.Assign(devices80_38);
address80_101.SetBase("10.1.102.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces80_101 = address80_101.Assign(devices80_101);
address38_59.SetBase("10.1.103.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces38_59 = address38_59.Assign(devices38_59);
address38_17.SetBase("10.1.104.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces38_17 = address38_17.Assign(devices38_17);




  

  // 启用流监测器，使用 FlowMonitorHelper 启用流监测器，并将其安装在所有的设备上
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll();
  
  // Create a packet sink on the star "hub" to receive these packets
    uint16_t port = 50000;//端口号50000
    ApplicationContainer sinkApp;//这一句是定义服务器的
    Address sinkLocalAddress (InetSocketAddress (Ipv4Address::GetAny (), port));
    PacketSinkHelper sinkHelper ("ns3::TcpSocketFactory", sinkLocalAddress);//接收和消耗生成到IP地址和端口的流量
    //sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[6].Get(1)));//0为服务器结点
    //sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[61].Get(1)));//19为服务器结点
    //sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[28].Get(1)));//23为服务器结点
    //sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[71].Get(1)));//10为服务器结点
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[0].Get(0)));//21为服务器结点
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[8].Get(1)));//35为服务器结点
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[99].Get(1)));//4为服务器结点
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[21].Get(0)));//26为服务器结点
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[39].Get(1)));//13为服务器结点
    //sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[96].Get(1)));//25为服务器结点
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
    //69----0
    //AddressValue remoteAddress (InetSocketAddress (interfaces21_0.GetAddress(1), port));
    //clientHelper.SetAttribute("Remote",remoteAddress);    
    //clientApps.Add(clientHelper.Install(nodeAdjacencyList[24].Get(0)));
    
    //82----19
    //remoteAddress=AddressValue(InetSocketAddress (interfaces40_19.GetAddress (1), port));
    //clientHelper.SetAttribute("Remote",remoteAddress);    
    //clientApps.Add(clientHelper.Install(nodeAdjacencyList[59].Get(1)));
    
    
    //82----23
    //remoteAddress=AddressValue(InetSocketAddress (interfaces23_65.GetAddress (0), port));
    //clientHelper.SetAttribute("Remote",remoteAddress);    
    //clientApps.Add(clientHelper.Install(nodeAdjacencyList[59].Get(1)));
    
    //40----10
    //remoteAddress=AddressValue(InetSocketAddress (interfaces31_10.GetAddress (1), port));
    //clientHelper.SetAttribute("Remote",remoteAddress);    
    //clientApps.Add(clientHelper.Install(nodeAdjacencyList[14].Get(1)));
    
    //0----21
    AddressValue remoteAddress (InetSocketAddress (interfaces21_0.GetAddress (0), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[6].Get(1)));
    
    //85----21
    remoteAddress=AddressValue(InetSocketAddress (interfaces21_0.GetAddress (0), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[83].Get(1)));
    
    //30----35
    remoteAddress=AddressValue(InetSocketAddress (interfaces63_35.GetAddress (1), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[44].Get(1)));
    
    //46----4
    //remoteAddress=AddressValue(InetSocketAddress (interfaces25_4.GetAddress (1), port));
    //clientHelper.SetAttribute("Remote",remoteAddress);    
    //clientApps.Add(clientHelper.Install(nodeAdjacencyList[98].Get(1)));
    
    //95----26
    remoteAddress=AddressValue(InetSocketAddress (interfaces26_5.GetAddress (0), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[73].Get(1)));
    
    //63----13
    remoteAddress=AddressValue(InetSocketAddress (interfaces34_13.GetAddress (1), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[0].Get(1)));
    
    //39----25
    //remoteAddress=AddressValue(InetSocketAddress (interfaces67_25.GetAddress (1), port));
    //clientHelper.SetAttribute("Remote",remoteAddress);    
    //clientApps.Add(clientHelper.Install(nodeAdjacencyList[13].Get(1)));
    

    
    clientApps.Start(Seconds(1.0));
    clientApps.Stop (Seconds (61.0));
  
  // 启用 OSPF
  Ipv4GlobalRoutingHelper::PopulateRoutingTables();
  
  
  
  
  // 配置输出流
  AsciiTraceHelper throughputAscii, lossAscii, delayAscii;
  Ptr<OutputStreamWrapper> throughputStream = throughputAscii.CreateFileStream("throughput-D42-TREE.txt");
  Ptr<OutputStreamWrapper> lossStream = lossAscii.CreateFileStream("loss-D42-TREE.txt");
  Ptr<OutputStreamWrapper> delayStream = delayAscii.CreateFileStream("delay-D42-TREE.txt");
  
  // 输出文件的表头
  *throughputStream->GetStream() << "Time (s)\tThroughput (Mbps)\n";
  *lossStream->GetStream() << "Time (s)\tLoss Rate (%)\n";
  *delayStream->GetStream() << "Time (s)\tAverage Delay (s)\n";
  
  // 在仿真运行期间定期计算性能指标
  Simulator::Schedule(Seconds(1), &CalculateMetrics, monitor, throughputStream, lossStream, delayStream, Seconds(600.0));
  
  // 运行仿真
  Simulator::Run();
  Simulator::Destroy();

  return 0;
}
