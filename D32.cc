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
  vector<NodeContainer> nodeAdjacencyList(156);

nodeAdjacencyList[0]=NodeContainer(nodes.Get(0), nodes.Get(1)); 
nodeAdjacencyList[1]=NodeContainer(nodes.Get(0), nodes.Get(2)); 
nodeAdjacencyList[2]=NodeContainer(nodes.Get(0), nodes.Get(3)); 
nodeAdjacencyList[3]=NodeContainer(nodes.Get(1), nodes.Get(2)); 
nodeAdjacencyList[4]=NodeContainer(nodes.Get(1), nodes.Get(3)); 
nodeAdjacencyList[5]=NodeContainer(nodes.Get(2), nodes.Get(3)); 
nodeAdjacencyList[6]=NodeContainer(nodes.Get(4), nodes.Get(5)); 
nodeAdjacencyList[7]=NodeContainer(nodes.Get(4), nodes.Get(6)); 
nodeAdjacencyList[8]=NodeContainer(nodes.Get(4), nodes.Get(7)); 
nodeAdjacencyList[9]=NodeContainer(nodes.Get(5), nodes.Get(6)); 
nodeAdjacencyList[10]=NodeContainer(nodes.Get(5), nodes.Get(7)); 
nodeAdjacencyList[11]=NodeContainer(nodes.Get(6), nodes.Get(7)); 
nodeAdjacencyList[12]=NodeContainer(nodes.Get(8), nodes.Get(9)); 
nodeAdjacencyList[13]=NodeContainer(nodes.Get(8), nodes.Get(10)); 
nodeAdjacencyList[14]=NodeContainer(nodes.Get(8), nodes.Get(11)); 
nodeAdjacencyList[15]=NodeContainer(nodes.Get(9), nodes.Get(10)); 
nodeAdjacencyList[16]=NodeContainer(nodes.Get(9), nodes.Get(11)); 
nodeAdjacencyList[17]=NodeContainer(nodes.Get(10), nodes.Get(11)); 
nodeAdjacencyList[18]=NodeContainer(nodes.Get(12), nodes.Get(13)); 
nodeAdjacencyList[19]=NodeContainer(nodes.Get(12), nodes.Get(14)); 
nodeAdjacencyList[20]=NodeContainer(nodes.Get(12), nodes.Get(15)); 
nodeAdjacencyList[21]=NodeContainer(nodes.Get(13), nodes.Get(14)); 
nodeAdjacencyList[22]=NodeContainer(nodes.Get(13), nodes.Get(15)); 
nodeAdjacencyList[23]=NodeContainer(nodes.Get(14), nodes.Get(15)); 
nodeAdjacencyList[24]=NodeContainer(nodes.Get(16), nodes.Get(17)); 
nodeAdjacencyList[25]=NodeContainer(nodes.Get(16), nodes.Get(18)); 
nodeAdjacencyList[26]=NodeContainer(nodes.Get(16), nodes.Get(19)); 
nodeAdjacencyList[27]=NodeContainer(nodes.Get(17), nodes.Get(18)); 
nodeAdjacencyList[28]=NodeContainer(nodes.Get(17), nodes.Get(19)); 
nodeAdjacencyList[29]=NodeContainer(nodes.Get(18), nodes.Get(19)); 
nodeAdjacencyList[30]=NodeContainer(nodes.Get(20), nodes.Get(21)); 
nodeAdjacencyList[31]=NodeContainer(nodes.Get(20), nodes.Get(22)); 
nodeAdjacencyList[32]=NodeContainer(nodes.Get(20), nodes.Get(23)); 
nodeAdjacencyList[33]=NodeContainer(nodes.Get(21), nodes.Get(22)); 
nodeAdjacencyList[34]=NodeContainer(nodes.Get(21), nodes.Get(23)); 
nodeAdjacencyList[35]=NodeContainer(nodes.Get(22), nodes.Get(23)); 
nodeAdjacencyList[36]=NodeContainer(nodes.Get(24), nodes.Get(25)); 
nodeAdjacencyList[37]=NodeContainer(nodes.Get(24), nodes.Get(26)); 
nodeAdjacencyList[38]=NodeContainer(nodes.Get(24), nodes.Get(27)); 
nodeAdjacencyList[39]=NodeContainer(nodes.Get(25), nodes.Get(26)); 
nodeAdjacencyList[40]=NodeContainer(nodes.Get(25), nodes.Get(27)); 
nodeAdjacencyList[41]=NodeContainer(nodes.Get(26), nodes.Get(27)); 
nodeAdjacencyList[42]=NodeContainer(nodes.Get(28), nodes.Get(29)); 
nodeAdjacencyList[43]=NodeContainer(nodes.Get(28), nodes.Get(30)); 
nodeAdjacencyList[44]=NodeContainer(nodes.Get(28), nodes.Get(31)); 
nodeAdjacencyList[45]=NodeContainer(nodes.Get(29), nodes.Get(30)); 
nodeAdjacencyList[46]=NodeContainer(nodes.Get(29), nodes.Get(31)); 
nodeAdjacencyList[47]=NodeContainer(nodes.Get(30), nodes.Get(31)); 
nodeAdjacencyList[48]=NodeContainer(nodes.Get(32), nodes.Get(33)); 
nodeAdjacencyList[49]=NodeContainer(nodes.Get(32), nodes.Get(34)); 
nodeAdjacencyList[50]=NodeContainer(nodes.Get(32), nodes.Get(35)); 
nodeAdjacencyList[51]=NodeContainer(nodes.Get(33), nodes.Get(34)); 
nodeAdjacencyList[52]=NodeContainer(nodes.Get(33), nodes.Get(35)); 
nodeAdjacencyList[53]=NodeContainer(nodes.Get(34), nodes.Get(35)); 
nodeAdjacencyList[54]=NodeContainer(nodes.Get(36), nodes.Get(37)); 
nodeAdjacencyList[55]=NodeContainer(nodes.Get(36), nodes.Get(38)); 
nodeAdjacencyList[56]=NodeContainer(nodes.Get(36), nodes.Get(39)); 
nodeAdjacencyList[57]=NodeContainer(nodes.Get(37), nodes.Get(38)); 
nodeAdjacencyList[58]=NodeContainer(nodes.Get(37), nodes.Get(39)); 
nodeAdjacencyList[59]=NodeContainer(nodes.Get(38), nodes.Get(39)); 
nodeAdjacencyList[60]=NodeContainer(nodes.Get(40), nodes.Get(41)); 
nodeAdjacencyList[61]=NodeContainer(nodes.Get(40), nodes.Get(42)); 
nodeAdjacencyList[62]=NodeContainer(nodes.Get(40), nodes.Get(43)); 
nodeAdjacencyList[63]=NodeContainer(nodes.Get(41), nodes.Get(42)); 
nodeAdjacencyList[64]=NodeContainer(nodes.Get(41), nodes.Get(43)); 
nodeAdjacencyList[65]=NodeContainer(nodes.Get(42), nodes.Get(43)); 
nodeAdjacencyList[66]=NodeContainer(nodes.Get(44), nodes.Get(45)); 
nodeAdjacencyList[67]=NodeContainer(nodes.Get(44), nodes.Get(46)); 
nodeAdjacencyList[68]=NodeContainer(nodes.Get(44), nodes.Get(47)); 
nodeAdjacencyList[69]=NodeContainer(nodes.Get(45), nodes.Get(46)); 
nodeAdjacencyList[70]=NodeContainer(nodes.Get(45), nodes.Get(47)); 
nodeAdjacencyList[71]=NodeContainer(nodes.Get(46), nodes.Get(47)); 
nodeAdjacencyList[72]=NodeContainer(nodes.Get(48), nodes.Get(49)); 
nodeAdjacencyList[73]=NodeContainer(nodes.Get(48), nodes.Get(50)); 
nodeAdjacencyList[74]=NodeContainer(nodes.Get(48), nodes.Get(51)); 
nodeAdjacencyList[75]=NodeContainer(nodes.Get(49), nodes.Get(50)); 
nodeAdjacencyList[76]=NodeContainer(nodes.Get(49), nodes.Get(51)); 
nodeAdjacencyList[77]=NodeContainer(nodes.Get(50), nodes.Get(51)); 
nodeAdjacencyList[78]=NodeContainer(nodes.Get(0), nodes.Get(7)); 
nodeAdjacencyList[79]=NodeContainer(nodes.Get(0), nodes.Get(11)); 
nodeAdjacencyList[80]=NodeContainer(nodes.Get(0), nodes.Get(15)); 
nodeAdjacencyList[81]=NodeContainer(nodes.Get(1), nodes.Get(18)); 
nodeAdjacencyList[82]=NodeContainer(nodes.Get(1), nodes.Get(22)); 
nodeAdjacencyList[83]=NodeContainer(nodes.Get(1), nodes.Get(26)); 
nodeAdjacencyList[84]=NodeContainer(nodes.Get(2), nodes.Get(29)); 
nodeAdjacencyList[85]=NodeContainer(nodes.Get(2), nodes.Get(33)); 
nodeAdjacencyList[86]=NodeContainer(nodes.Get(2), nodes.Get(37)); 
nodeAdjacencyList[87]=NodeContainer(nodes.Get(3), nodes.Get(40)); 
nodeAdjacencyList[88]=NodeContainer(nodes.Get(3), nodes.Get(44)); 
nodeAdjacencyList[89]=NodeContainer(nodes.Get(3), nodes.Get(48)); 
nodeAdjacencyList[90]=NodeContainer(nodes.Get(4), nodes.Get(11)); 
nodeAdjacencyList[91]=NodeContainer(nodes.Get(4), nodes.Get(15)); 
nodeAdjacencyList[92]=NodeContainer(nodes.Get(4), nodes.Get(19)); 
nodeAdjacencyList[93]=NodeContainer(nodes.Get(5), nodes.Get(22)); 
nodeAdjacencyList[94]=NodeContainer(nodes.Get(5), nodes.Get(26)); 
nodeAdjacencyList[95]=NodeContainer(nodes.Get(5), nodes.Get(30)); 
nodeAdjacencyList[96]=NodeContainer(nodes.Get(6), nodes.Get(33)); 
nodeAdjacencyList[97]=NodeContainer(nodes.Get(6), nodes.Get(37)); 
nodeAdjacencyList[98]=NodeContainer(nodes.Get(6), nodes.Get(41)); 
nodeAdjacencyList[99]=NodeContainer(nodes.Get(7), nodes.Get(44)); 
nodeAdjacencyList[100]=NodeContainer(nodes.Get(7), nodes.Get(48)); 
nodeAdjacencyList[101]=NodeContainer(nodes.Get(8), nodes.Get(15)); 
nodeAdjacencyList[102]=NodeContainer(nodes.Get(8), nodes.Get(19)); 
nodeAdjacencyList[103]=NodeContainer(nodes.Get(8), nodes.Get(23)); 
nodeAdjacencyList[104]=NodeContainer(nodes.Get(9), nodes.Get(26)); 
nodeAdjacencyList[105]=NodeContainer(nodes.Get(9), nodes.Get(30)); 
nodeAdjacencyList[106]=NodeContainer(nodes.Get(9), nodes.Get(34)); 
nodeAdjacencyList[107]=NodeContainer(nodes.Get(10), nodes.Get(37)); 
nodeAdjacencyList[108]=NodeContainer(nodes.Get(10), nodes.Get(41)); 
nodeAdjacencyList[109]=NodeContainer(nodes.Get(10), nodes.Get(45)); 
nodeAdjacencyList[110]=NodeContainer(nodes.Get(11), nodes.Get(48)); 
nodeAdjacencyList[111]=NodeContainer(nodes.Get(12), nodes.Get(19)); 
nodeAdjacencyList[112]=NodeContainer(nodes.Get(12), nodes.Get(23)); 
nodeAdjacencyList[113]=NodeContainer(nodes.Get(12), nodes.Get(27)); 
nodeAdjacencyList[114]=NodeContainer(nodes.Get(13), nodes.Get(30)); 
nodeAdjacencyList[115]=NodeContainer(nodes.Get(13), nodes.Get(34)); 
nodeAdjacencyList[116]=NodeContainer(nodes.Get(13), nodes.Get(38)); 
nodeAdjacencyList[117]=NodeContainer(nodes.Get(14), nodes.Get(41)); 
nodeAdjacencyList[118]=NodeContainer(nodes.Get(14), nodes.Get(45)); 
nodeAdjacencyList[119]=NodeContainer(nodes.Get(14), nodes.Get(49)); 
nodeAdjacencyList[120]=NodeContainer(nodes.Get(16), nodes.Get(23)); 
nodeAdjacencyList[121]=NodeContainer(nodes.Get(16), nodes.Get(27)); 
nodeAdjacencyList[122]=NodeContainer(nodes.Get(16), nodes.Get(31)); 
nodeAdjacencyList[123]=NodeContainer(nodes.Get(17), nodes.Get(34)); 
nodeAdjacencyList[124]=NodeContainer(nodes.Get(17), nodes.Get(38)); 
nodeAdjacencyList[125]=NodeContainer(nodes.Get(17), nodes.Get(42)); 
nodeAdjacencyList[126]=NodeContainer(nodes.Get(18), nodes.Get(45)); 
nodeAdjacencyList[127]=NodeContainer(nodes.Get(18), nodes.Get(49)); 
nodeAdjacencyList[128]=NodeContainer(nodes.Get(20), nodes.Get(27)); 
nodeAdjacencyList[129]=NodeContainer(nodes.Get(20), nodes.Get(31)); 
nodeAdjacencyList[130]=NodeContainer(nodes.Get(20), nodes.Get(35)); 
nodeAdjacencyList[131]=NodeContainer(nodes.Get(21), nodes.Get(38)); 
nodeAdjacencyList[132]=NodeContainer(nodes.Get(21), nodes.Get(42)); 
nodeAdjacencyList[133]=NodeContainer(nodes.Get(21), nodes.Get(46)); 
nodeAdjacencyList[134]=NodeContainer(nodes.Get(22), nodes.Get(49)); 
nodeAdjacencyList[135]=NodeContainer(nodes.Get(24), nodes.Get(31)); 
nodeAdjacencyList[136]=NodeContainer(nodes.Get(24), nodes.Get(35)); 
nodeAdjacencyList[137]=NodeContainer(nodes.Get(24), nodes.Get(39)); 
nodeAdjacencyList[138]=NodeContainer(nodes.Get(25), nodes.Get(42)); 
nodeAdjacencyList[139]=NodeContainer(nodes.Get(25), nodes.Get(46)); 
nodeAdjacencyList[140]=NodeContainer(nodes.Get(25), nodes.Get(50)); 
nodeAdjacencyList[141]=NodeContainer(nodes.Get(28), nodes.Get(35)); 
nodeAdjacencyList[142]=NodeContainer(nodes.Get(28), nodes.Get(39)); 
nodeAdjacencyList[143]=NodeContainer(nodes.Get(28), nodes.Get(43)); 
nodeAdjacencyList[144]=NodeContainer(nodes.Get(29), nodes.Get(46)); 
nodeAdjacencyList[145]=NodeContainer(nodes.Get(29), nodes.Get(50)); 
nodeAdjacencyList[146]=NodeContainer(nodes.Get(32), nodes.Get(39)); 
nodeAdjacencyList[147]=NodeContainer(nodes.Get(32), nodes.Get(43)); 
nodeAdjacencyList[148]=NodeContainer(nodes.Get(32), nodes.Get(47)); 
nodeAdjacencyList[149]=NodeContainer(nodes.Get(33), nodes.Get(50)); 
nodeAdjacencyList[150]=NodeContainer(nodes.Get(36), nodes.Get(43)); 
nodeAdjacencyList[151]=NodeContainer(nodes.Get(36), nodes.Get(47)); 
nodeAdjacencyList[152]=NodeContainer(nodes.Get(36), nodes.Get(51)); 
nodeAdjacencyList[153]=NodeContainer(nodes.Get(40), nodes.Get(47)); 
nodeAdjacencyList[154]=NodeContainer(nodes.Get(40), nodes.Get(51)); 
nodeAdjacencyList[155]=NodeContainer(nodes.Get(44), nodes.Get(51)); 

// 创建节点之间的连接，分别设置传输速率和传播延迟
  
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute("DataRate", StringValue("100Mbps"));
  p2p.SetChannelAttribute("Delay", StringValue("1ms"));

  //通过 Install 函数将设备配置应用到相应的节点上，形成了网络拓扑
    NetDeviceContainer 
devices0_1,
devices0_2,
devices0_3,
devices1_2,
devices1_3,
devices2_3,
devices4_5,
devices4_6,
devices4_7,
devices5_6,
devices5_7,
devices6_7,
devices8_9,
devices8_10,
devices8_11,
devices9_10,
devices9_11,
devices10_11,
devices12_13,
devices12_14,
devices12_15,
devices13_14,
devices13_15,
devices14_15,
devices16_17,
devices16_18,
devices16_19,
devices17_18,
devices17_19,
devices18_19,
devices20_21,
devices20_22,
devices20_23,
devices21_22,
devices21_23,
devices22_23,
devices24_25,
devices24_26,
devices24_27,
devices25_26,
devices25_27,
devices26_27,
devices28_29,
devices28_30,
devices28_31,
devices29_30,
devices29_31,
devices30_31,
devices32_33,
devices32_34,
devices32_35,
devices33_34,
devices33_35,
devices34_35,
devices36_37,
devices36_38,
devices36_39,
devices37_38,
devices37_39,
devices38_39,
devices40_41,
devices40_42,
devices40_43,
devices41_42,
devices41_43,
devices42_43,
devices44_45,
devices44_46,
devices44_47,
devices45_46,
devices45_47,
devices46_47,
devices48_49,
devices48_50,
devices48_51,
devices49_50,
devices49_51,
devices50_51,
devices0_7,
devices0_11,
devices0_15,
devices1_18,
devices1_22,
devices1_26,
devices2_29,
devices2_33,
devices2_37,
devices3_40,
devices3_44,
devices3_48,
devices4_11,
devices4_15,
devices4_19,
devices5_22,
devices5_26,
devices5_30,
devices6_33,
devices6_37,
devices6_41,
devices7_44,
devices7_48,
devices8_15,
devices8_19,
devices8_23,
devices9_26,
devices9_30,
devices9_34,
devices10_37,
devices10_41,
devices10_45,
devices11_48,
devices12_19,
devices12_23,
devices12_27,
devices13_30,
devices13_34,
devices13_38,
devices14_41,
devices14_45,
devices14_49,
devices16_23,
devices16_27,
devices16_31,
devices17_34,
devices17_38,
devices17_42,
devices18_45,
devices18_49,
devices20_27,
devices20_31,
devices20_35,
devices21_38,
devices21_42,
devices21_46,
devices22_49,
devices24_31,
devices24_35,
devices24_39,
devices25_42,
devices25_46,
devices25_50,
devices28_35,
devices28_39,
devices28_43,
devices29_46,
devices29_50,
devices32_39,
devices32_43,
devices32_47,
devices33_50,
devices36_43,
devices36_47,
devices36_51,
devices40_47,
devices40_51,
devices44_51;

devices0_1= p2p.Install(nodes.Get(0), nodes.Get(1)); 
devices0_2= p2p.Install(nodes.Get(0), nodes.Get(2)); 
devices0_3= p2p.Install(nodes.Get(0), nodes.Get(3)); 
devices1_2= p2p.Install(nodes.Get(1), nodes.Get(2)); 
devices1_3= p2p.Install(nodes.Get(1), nodes.Get(3)); 
devices2_3= p2p.Install(nodes.Get(2), nodes.Get(3)); 
devices4_5= p2p.Install(nodes.Get(4), nodes.Get(5)); 
devices4_6= p2p.Install(nodes.Get(4), nodes.Get(6)); 
devices4_7= p2p.Install(nodes.Get(4), nodes.Get(7)); 
devices5_6= p2p.Install(nodes.Get(5), nodes.Get(6)); 
devices5_7= p2p.Install(nodes.Get(5), nodes.Get(7)); 
devices6_7= p2p.Install(nodes.Get(6), nodes.Get(7)); 
devices8_9= p2p.Install(nodes.Get(8), nodes.Get(9)); 
devices8_10= p2p.Install(nodes.Get(8), nodes.Get(10)); 
devices8_11= p2p.Install(nodes.Get(8), nodes.Get(11)); 
devices9_10= p2p.Install(nodes.Get(9), nodes.Get(10)); 
devices9_11= p2p.Install(nodes.Get(9), nodes.Get(11)); 
devices10_11= p2p.Install(nodes.Get(10), nodes.Get(11)); 
devices12_13= p2p.Install(nodes.Get(12), nodes.Get(13)); 
devices12_14= p2p.Install(nodes.Get(12), nodes.Get(14)); 
devices12_15= p2p.Install(nodes.Get(12), nodes.Get(15)); 
devices13_14= p2p.Install(nodes.Get(13), nodes.Get(14)); 
devices13_15= p2p.Install(nodes.Get(13), nodes.Get(15)); 
devices14_15= p2p.Install(nodes.Get(14), nodes.Get(15)); 
devices16_17= p2p.Install(nodes.Get(16), nodes.Get(17)); 
devices16_18= p2p.Install(nodes.Get(16), nodes.Get(18)); 
devices16_19= p2p.Install(nodes.Get(16), nodes.Get(19)); 
devices17_18= p2p.Install(nodes.Get(17), nodes.Get(18)); 
devices17_19= p2p.Install(nodes.Get(17), nodes.Get(19)); 
devices18_19= p2p.Install(nodes.Get(18), nodes.Get(19)); 
devices20_21= p2p.Install(nodes.Get(20), nodes.Get(21)); 
devices20_22= p2p.Install(nodes.Get(20), nodes.Get(22)); 
devices20_23= p2p.Install(nodes.Get(20), nodes.Get(23)); 
devices21_22= p2p.Install(nodes.Get(21), nodes.Get(22)); 
devices21_23= p2p.Install(nodes.Get(21), nodes.Get(23)); 
devices22_23= p2p.Install(nodes.Get(22), nodes.Get(23)); 
devices24_25= p2p.Install(nodes.Get(24), nodes.Get(25)); 
devices24_26= p2p.Install(nodes.Get(24), nodes.Get(26)); 
devices24_27= p2p.Install(nodes.Get(24), nodes.Get(27)); 
devices25_26= p2p.Install(nodes.Get(25), nodes.Get(26)); 
devices25_27= p2p.Install(nodes.Get(25), nodes.Get(27)); 
devices26_27= p2p.Install(nodes.Get(26), nodes.Get(27)); 
devices28_29= p2p.Install(nodes.Get(28), nodes.Get(29)); 
devices28_30= p2p.Install(nodes.Get(28), nodes.Get(30)); 
devices28_31= p2p.Install(nodes.Get(28), nodes.Get(31)); 
devices29_30= p2p.Install(nodes.Get(29), nodes.Get(30)); 
devices29_31= p2p.Install(nodes.Get(29), nodes.Get(31)); 
devices30_31= p2p.Install(nodes.Get(30), nodes.Get(31)); 
devices32_33= p2p.Install(nodes.Get(32), nodes.Get(33)); 
devices32_34= p2p.Install(nodes.Get(32), nodes.Get(34)); 
devices32_35= p2p.Install(nodes.Get(32), nodes.Get(35)); 
devices33_34= p2p.Install(nodes.Get(33), nodes.Get(34)); 
devices33_35= p2p.Install(nodes.Get(33), nodes.Get(35)); 
devices34_35= p2p.Install(nodes.Get(34), nodes.Get(35)); 
devices36_37= p2p.Install(nodes.Get(36), nodes.Get(37)); 
devices36_38= p2p.Install(nodes.Get(36), nodes.Get(38)); 
devices36_39= p2p.Install(nodes.Get(36), nodes.Get(39)); 
devices37_38= p2p.Install(nodes.Get(37), nodes.Get(38)); 
devices37_39= p2p.Install(nodes.Get(37), nodes.Get(39)); 
devices38_39= p2p.Install(nodes.Get(38), nodes.Get(39)); 
devices40_41= p2p.Install(nodes.Get(40), nodes.Get(41)); 
devices40_42= p2p.Install(nodes.Get(40), nodes.Get(42)); 
devices40_43= p2p.Install(nodes.Get(40), nodes.Get(43)); 
devices41_42= p2p.Install(nodes.Get(41), nodes.Get(42)); 
devices41_43= p2p.Install(nodes.Get(41), nodes.Get(43)); 
devices42_43= p2p.Install(nodes.Get(42), nodes.Get(43)); 
devices44_45= p2p.Install(nodes.Get(44), nodes.Get(45)); 
devices44_46= p2p.Install(nodes.Get(44), nodes.Get(46)); 
devices44_47= p2p.Install(nodes.Get(44), nodes.Get(47)); 
devices45_46= p2p.Install(nodes.Get(45), nodes.Get(46)); 
devices45_47= p2p.Install(nodes.Get(45), nodes.Get(47)); 
devices46_47= p2p.Install(nodes.Get(46), nodes.Get(47)); 
devices48_49= p2p.Install(nodes.Get(48), nodes.Get(49)); 
devices48_50= p2p.Install(nodes.Get(48), nodes.Get(50)); 
devices48_51= p2p.Install(nodes.Get(48), nodes.Get(51)); 
devices49_50= p2p.Install(nodes.Get(49), nodes.Get(50)); 
devices49_51= p2p.Install(nodes.Get(49), nodes.Get(51)); 
devices50_51= p2p.Install(nodes.Get(50), nodes.Get(51)); 
devices0_7= p2p.Install(nodes.Get(0), nodes.Get(7)); 
devices0_11= p2p.Install(nodes.Get(0), nodes.Get(11)); 
devices0_15= p2p.Install(nodes.Get(0), nodes.Get(15)); 
devices1_18= p2p.Install(nodes.Get(1), nodes.Get(18)); 
devices1_22= p2p.Install(nodes.Get(1), nodes.Get(22)); 
devices1_26= p2p.Install(nodes.Get(1), nodes.Get(26)); 
devices2_29= p2p.Install(nodes.Get(2), nodes.Get(29)); 
devices2_33= p2p.Install(nodes.Get(2), nodes.Get(33)); 
devices2_37= p2p.Install(nodes.Get(2), nodes.Get(37)); 
devices3_40= p2p.Install(nodes.Get(3), nodes.Get(40)); 
devices3_44= p2p.Install(nodes.Get(3), nodes.Get(44)); 
devices3_48= p2p.Install(nodes.Get(3), nodes.Get(48)); 
devices4_11= p2p.Install(nodes.Get(4), nodes.Get(11)); 
devices4_15= p2p.Install(nodes.Get(4), nodes.Get(15)); 
devices4_19= p2p.Install(nodes.Get(4), nodes.Get(19)); 
devices5_22= p2p.Install(nodes.Get(5), nodes.Get(22)); 
devices5_26= p2p.Install(nodes.Get(5), nodes.Get(26)); 
devices5_30= p2p.Install(nodes.Get(5), nodes.Get(30)); 
devices6_33= p2p.Install(nodes.Get(6), nodes.Get(33)); 
devices6_37= p2p.Install(nodes.Get(6), nodes.Get(37)); 
devices6_41= p2p.Install(nodes.Get(6), nodes.Get(41)); 
devices7_44= p2p.Install(nodes.Get(7), nodes.Get(44)); 
devices7_48= p2p.Install(nodes.Get(7), nodes.Get(48)); 
devices8_15= p2p.Install(nodes.Get(8), nodes.Get(15)); 
devices8_19= p2p.Install(nodes.Get(8), nodes.Get(19)); 
devices8_23= p2p.Install(nodes.Get(8), nodes.Get(23)); 
devices9_26= p2p.Install(nodes.Get(9), nodes.Get(26)); 
devices9_30= p2p.Install(nodes.Get(9), nodes.Get(30)); 
devices9_34= p2p.Install(nodes.Get(9), nodes.Get(34)); 
devices10_37= p2p.Install(nodes.Get(10), nodes.Get(37)); 
devices10_41= p2p.Install(nodes.Get(10), nodes.Get(41)); 
devices10_45= p2p.Install(nodes.Get(10), nodes.Get(45)); 
devices11_48= p2p.Install(nodes.Get(11), nodes.Get(48)); 
devices12_19= p2p.Install(nodes.Get(12), nodes.Get(19)); 
devices12_23= p2p.Install(nodes.Get(12), nodes.Get(23)); 
devices12_27= p2p.Install(nodes.Get(12), nodes.Get(27)); 
devices13_30= p2p.Install(nodes.Get(13), nodes.Get(30)); 
devices13_34= p2p.Install(nodes.Get(13), nodes.Get(34)); 
devices13_38= p2p.Install(nodes.Get(13), nodes.Get(38)); 
devices14_41= p2p.Install(nodes.Get(14), nodes.Get(41)); 
devices14_45= p2p.Install(nodes.Get(14), nodes.Get(45)); 
devices14_49= p2p.Install(nodes.Get(14), nodes.Get(49)); 
devices16_23= p2p.Install(nodes.Get(16), nodes.Get(23)); 
devices16_27= p2p.Install(nodes.Get(16), nodes.Get(27)); 
devices16_31= p2p.Install(nodes.Get(16), nodes.Get(31)); 
devices17_34= p2p.Install(nodes.Get(17), nodes.Get(34)); 
devices17_38= p2p.Install(nodes.Get(17), nodes.Get(38)); 
devices17_42= p2p.Install(nodes.Get(17), nodes.Get(42)); 
devices18_45= p2p.Install(nodes.Get(18), nodes.Get(45)); 
devices18_49= p2p.Install(nodes.Get(18), nodes.Get(49)); 
devices20_27= p2p.Install(nodes.Get(20), nodes.Get(27)); 
devices20_31= p2p.Install(nodes.Get(20), nodes.Get(31)); 
devices20_35= p2p.Install(nodes.Get(20), nodes.Get(35)); 
devices21_38= p2p.Install(nodes.Get(21), nodes.Get(38)); 
devices21_42= p2p.Install(nodes.Get(21), nodes.Get(42)); 
devices21_46= p2p.Install(nodes.Get(21), nodes.Get(46)); 
devices22_49= p2p.Install(nodes.Get(22), nodes.Get(49)); 
devices24_31= p2p.Install(nodes.Get(24), nodes.Get(31)); 
devices24_35= p2p.Install(nodes.Get(24), nodes.Get(35)); 
devices24_39= p2p.Install(nodes.Get(24), nodes.Get(39)); 
devices25_42= p2p.Install(nodes.Get(25), nodes.Get(42)); 
devices25_46= p2p.Install(nodes.Get(25), nodes.Get(46)); 
devices25_50= p2p.Install(nodes.Get(25), nodes.Get(50)); 
devices28_35= p2p.Install(nodes.Get(28), nodes.Get(35)); 
devices28_39= p2p.Install(nodes.Get(28), nodes.Get(39)); 
devices28_43= p2p.Install(nodes.Get(28), nodes.Get(43)); 
devices29_46= p2p.Install(nodes.Get(29), nodes.Get(46)); 
devices29_50= p2p.Install(nodes.Get(29), nodes.Get(50)); 
devices32_39= p2p.Install(nodes.Get(32), nodes.Get(39)); 
devices32_43= p2p.Install(nodes.Get(32), nodes.Get(43)); 
devices32_47= p2p.Install(nodes.Get(32), nodes.Get(47)); 
devices33_50= p2p.Install(nodes.Get(33), nodes.Get(50)); 
devices36_43= p2p.Install(nodes.Get(36), nodes.Get(43)); 
devices36_47= p2p.Install(nodes.Get(36), nodes.Get(47)); 
devices36_51= p2p.Install(nodes.Get(36), nodes.Get(51)); 
devices40_47= p2p.Install(nodes.Get(40), nodes.Get(47)); 
devices40_51= p2p.Install(nodes.Get(40), nodes.Get(51)); 
devices44_51= p2p.Install(nodes.Get(44), nodes.Get(51)); 

 // 安装Internet协议栈
  InternetStackHelper internet;
  internet.Install(nodes);
  
Ipv4AddressHelper 
address0_1,
address0_2,
address0_3,
address1_2,
address1_3,
address2_3,
address4_5,
address4_6,
address4_7,
address5_6,
address5_7,
address6_7,
address8_9,
address8_10,
address8_11,
address9_10,
address9_11,
address10_11,
address12_13,
address12_14,
address12_15,
address13_14,
address13_15,
address14_15,
address16_17,
address16_18,
address16_19,
address17_18,
address17_19,
address18_19,
address20_21,
address20_22,
address20_23,
address21_22,
address21_23,
address22_23,
address24_25,
address24_26,
address24_27,
address25_26,
address25_27,
address26_27,
address28_29,
address28_30,
address28_31,
address29_30,
address29_31,
address30_31,
address32_33,
address32_34,
address32_35,
address33_34,
address33_35,
address34_35,
address36_37,
address36_38,
address36_39,
address37_38,
address37_39,
address38_39,
address40_41,
address40_42,
address40_43,
address41_42,
address41_43,
address42_43,
address44_45,
address44_46,
address44_47,
address45_46,
address45_47,
address46_47,
address48_49,
address48_50,
address48_51,
address49_50,
address49_51,
address50_51,
address0_7,
address0_11,
address0_15,
address1_18,
address1_22,
address1_26,
address2_29,
address2_33,
address2_37,
address3_40,
address3_44,
address3_48,
address4_11,
address4_15,
address4_19,
address5_22,
address5_26,
address5_30,
address6_33,
address6_37,
address6_41,
address7_44,
address7_48,
address8_15,
address8_19,
address8_23,
address9_26,
address9_30,
address9_34,
address10_37,
address10_41,
address10_45,
address11_48,
address12_19,
address12_23,
address12_27,
address13_30,
address13_34,
address13_38,
address14_41,
address14_45,
address14_49,
address16_23,
address16_27,
address16_31,
address17_34,
address17_38,
address17_42,
address18_45,
address18_49,
address20_27,
address20_31,
address20_35,
address21_38,
address21_42,
address21_46,
address22_49,
address24_31,
address24_35,
address24_39,
address25_42,
address25_46,
address25_50,
address28_35,
address28_39,
address28_43,
address29_46,
address29_50,
address32_39,
address32_43,
address32_47,
address33_50,
address36_43,
address36_47,
address36_51,
address40_47,
address40_51,
address44_51;

address0_1.SetBase("10.1.1.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_1 = address0_1.Assign(devices0_1);
address0_2.SetBase("10.1.2.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_2 = address0_2.Assign(devices0_2);
address0_3.SetBase("10.1.3.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_3 = address0_3.Assign(devices0_3);
address1_2.SetBase("10.1.4.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces1_2 = address1_2.Assign(devices1_2);
address1_3.SetBase("10.1.5.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces1_3 = address1_3.Assign(devices1_3);
address2_3.SetBase("10.1.6.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces2_3 = address2_3.Assign(devices2_3);
address4_5.SetBase("10.1.7.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces4_5 = address4_5.Assign(devices4_5);
address4_6.SetBase("10.1.8.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces4_6 = address4_6.Assign(devices4_6);
address4_7.SetBase("10.1.9.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces4_7 = address4_7.Assign(devices4_7);
address5_6.SetBase("10.1.10.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces5_6 = address5_6.Assign(devices5_6);
address5_7.SetBase("10.1.11.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces5_7 = address5_7.Assign(devices5_7);
address6_7.SetBase("10.1.12.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces6_7 = address6_7.Assign(devices6_7);
address8_9.SetBase("10.1.13.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces8_9 = address8_9.Assign(devices8_9);
address8_10.SetBase("10.1.14.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces8_10 = address8_10.Assign(devices8_10);
address8_11.SetBase("10.1.15.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces8_11 = address8_11.Assign(devices8_11);
address9_10.SetBase("10.1.16.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces9_10 = address9_10.Assign(devices9_10);
address9_11.SetBase("10.1.17.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces9_11 = address9_11.Assign(devices9_11);
address10_11.SetBase("10.1.18.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces10_11 = address10_11.Assign(devices10_11);
address12_13.SetBase("10.1.19.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces12_13 = address12_13.Assign(devices12_13);
address12_14.SetBase("10.1.20.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces12_14 = address12_14.Assign(devices12_14);
address12_15.SetBase("10.1.21.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces12_15 = address12_15.Assign(devices12_15);
address13_14.SetBase("10.1.22.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces13_14 = address13_14.Assign(devices13_14);
address13_15.SetBase("10.1.23.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces13_15 = address13_15.Assign(devices13_15);
address14_15.SetBase("10.1.24.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces14_15 = address14_15.Assign(devices14_15);
address16_17.SetBase("10.1.25.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces16_17 = address16_17.Assign(devices16_17);
address16_18.SetBase("10.1.26.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces16_18 = address16_18.Assign(devices16_18);
address16_19.SetBase("10.1.27.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces16_19 = address16_19.Assign(devices16_19);
address17_18.SetBase("10.1.28.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces17_18 = address17_18.Assign(devices17_18);
address17_19.SetBase("10.1.29.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces17_19 = address17_19.Assign(devices17_19);
address18_19.SetBase("10.1.30.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces18_19 = address18_19.Assign(devices18_19);
address20_21.SetBase("10.1.31.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces20_21 = address20_21.Assign(devices20_21);
address20_22.SetBase("10.1.32.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces20_22 = address20_22.Assign(devices20_22);
address20_23.SetBase("10.1.33.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces20_23 = address20_23.Assign(devices20_23);
address21_22.SetBase("10.1.34.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_22 = address21_22.Assign(devices21_22);
address21_23.SetBase("10.1.35.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_23 = address21_23.Assign(devices21_23);
address22_23.SetBase("10.1.36.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces22_23 = address22_23.Assign(devices22_23);
address24_25.SetBase("10.1.37.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces24_25 = address24_25.Assign(devices24_25);
address24_26.SetBase("10.1.38.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces24_26 = address24_26.Assign(devices24_26);
address24_27.SetBase("10.1.39.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces24_27 = address24_27.Assign(devices24_27);
address25_26.SetBase("10.1.40.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces25_26 = address25_26.Assign(devices25_26);
address25_27.SetBase("10.1.41.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces25_27 = address25_27.Assign(devices25_27);
address26_27.SetBase("10.1.42.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces26_27 = address26_27.Assign(devices26_27);
address28_29.SetBase("10.1.43.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces28_29 = address28_29.Assign(devices28_29);
address28_30.SetBase("10.1.44.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces28_30 = address28_30.Assign(devices28_30);
address28_31.SetBase("10.1.45.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces28_31 = address28_31.Assign(devices28_31);
address29_30.SetBase("10.1.46.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces29_30 = address29_30.Assign(devices29_30);
address29_31.SetBase("10.1.47.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces29_31 = address29_31.Assign(devices29_31);
address30_31.SetBase("10.1.48.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces30_31 = address30_31.Assign(devices30_31);
address32_33.SetBase("10.1.49.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces32_33 = address32_33.Assign(devices32_33);
address32_34.SetBase("10.1.50.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces32_34 = address32_34.Assign(devices32_34);
address32_35.SetBase("10.1.51.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces32_35 = address32_35.Assign(devices32_35);
address33_34.SetBase("10.1.52.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces33_34 = address33_34.Assign(devices33_34);
address33_35.SetBase("10.1.53.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces33_35 = address33_35.Assign(devices33_35);
address34_35.SetBase("10.1.54.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces34_35 = address34_35.Assign(devices34_35);
address36_37.SetBase("10.1.55.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces36_37 = address36_37.Assign(devices36_37);
address36_38.SetBase("10.1.56.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces36_38 = address36_38.Assign(devices36_38);
address36_39.SetBase("10.1.57.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces36_39 = address36_39.Assign(devices36_39);
address37_38.SetBase("10.1.58.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces37_38 = address37_38.Assign(devices37_38);
address37_39.SetBase("10.1.59.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces37_39 = address37_39.Assign(devices37_39);
address38_39.SetBase("10.1.60.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces38_39 = address38_39.Assign(devices38_39);
address40_41.SetBase("10.1.61.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces40_41 = address40_41.Assign(devices40_41);
address40_42.SetBase("10.1.62.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces40_42 = address40_42.Assign(devices40_42);
address40_43.SetBase("10.1.63.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces40_43 = address40_43.Assign(devices40_43);
address41_42.SetBase("10.1.64.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces41_42 = address41_42.Assign(devices41_42);
address41_43.SetBase("10.1.65.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces41_43 = address41_43.Assign(devices41_43);
address42_43.SetBase("10.1.66.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces42_43 = address42_43.Assign(devices42_43);
address44_45.SetBase("10.1.67.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces44_45 = address44_45.Assign(devices44_45);
address44_46.SetBase("10.1.68.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces44_46 = address44_46.Assign(devices44_46);
address44_47.SetBase("10.1.69.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces44_47 = address44_47.Assign(devices44_47);
address45_46.SetBase("10.1.70.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces45_46 = address45_46.Assign(devices45_46);
address45_47.SetBase("10.1.71.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces45_47 = address45_47.Assign(devices45_47);
address46_47.SetBase("10.1.72.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces46_47 = address46_47.Assign(devices46_47);
address48_49.SetBase("10.1.73.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces48_49 = address48_49.Assign(devices48_49);
address48_50.SetBase("10.1.74.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces48_50 = address48_50.Assign(devices48_50);
address48_51.SetBase("10.1.75.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces48_51 = address48_51.Assign(devices48_51);
address49_50.SetBase("10.1.76.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces49_50 = address49_50.Assign(devices49_50);
address49_51.SetBase("10.1.77.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces49_51 = address49_51.Assign(devices49_51);
address50_51.SetBase("10.1.78.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces50_51 = address50_51.Assign(devices50_51);
address0_7.SetBase("10.1.79.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_7 = address0_7.Assign(devices0_7);
address0_11.SetBase("10.1.80.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_11 = address0_11.Assign(devices0_11);
address0_15.SetBase("10.1.81.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_15 = address0_15.Assign(devices0_15);
address1_18.SetBase("10.1.82.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces1_18 = address1_18.Assign(devices1_18);
address1_22.SetBase("10.1.83.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces1_22 = address1_22.Assign(devices1_22);
address1_26.SetBase("10.1.84.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces1_26 = address1_26.Assign(devices1_26);
address2_29.SetBase("10.1.85.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces2_29 = address2_29.Assign(devices2_29);
address2_33.SetBase("10.1.86.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces2_33 = address2_33.Assign(devices2_33);
address2_37.SetBase("10.1.87.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces2_37 = address2_37.Assign(devices2_37);
address3_40.SetBase("10.1.88.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces3_40 = address3_40.Assign(devices3_40);
address3_44.SetBase("10.1.89.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces3_44 = address3_44.Assign(devices3_44);
address3_48.SetBase("10.1.90.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces3_48 = address3_48.Assign(devices3_48);
address4_11.SetBase("10.1.91.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces4_11 = address4_11.Assign(devices4_11);
address4_15.SetBase("10.1.92.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces4_15 = address4_15.Assign(devices4_15);
address4_19.SetBase("10.1.93.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces4_19 = address4_19.Assign(devices4_19);
address5_22.SetBase("10.1.94.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces5_22 = address5_22.Assign(devices5_22);
address5_26.SetBase("10.1.95.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces5_26 = address5_26.Assign(devices5_26);
address5_30.SetBase("10.1.96.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces5_30 = address5_30.Assign(devices5_30);
address6_33.SetBase("10.1.97.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces6_33 = address6_33.Assign(devices6_33);
address6_37.SetBase("10.1.98.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces6_37 = address6_37.Assign(devices6_37);
address6_41.SetBase("10.1.99.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces6_41 = address6_41.Assign(devices6_41);
address7_44.SetBase("10.1.100.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces7_44 = address7_44.Assign(devices7_44);
address7_48.SetBase("10.1.101.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces7_48 = address7_48.Assign(devices7_48);
address8_15.SetBase("10.1.102.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces8_15 = address8_15.Assign(devices8_15);
address8_19.SetBase("10.1.103.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces8_19 = address8_19.Assign(devices8_19);
address8_23.SetBase("10.1.104.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces8_23 = address8_23.Assign(devices8_23);
address9_26.SetBase("10.1.105.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces9_26 = address9_26.Assign(devices9_26);
address9_30.SetBase("10.1.106.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces9_30 = address9_30.Assign(devices9_30);
address9_34.SetBase("10.1.107.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces9_34 = address9_34.Assign(devices9_34);
address10_37.SetBase("10.1.108.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces10_37 = address10_37.Assign(devices10_37);
address10_41.SetBase("10.1.109.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces10_41 = address10_41.Assign(devices10_41);
address10_45.SetBase("10.1.110.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces10_45 = address10_45.Assign(devices10_45);
address11_48.SetBase("10.1.111.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces11_48 = address11_48.Assign(devices11_48);
address12_19.SetBase("10.1.112.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces12_19 = address12_19.Assign(devices12_19);
address12_23.SetBase("10.1.113.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces12_23 = address12_23.Assign(devices12_23);
address12_27.SetBase("10.1.114.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces12_27 = address12_27.Assign(devices12_27);
address13_30.SetBase("10.1.115.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces13_30 = address13_30.Assign(devices13_30);
address13_34.SetBase("10.1.116.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces13_34 = address13_34.Assign(devices13_34);
address13_38.SetBase("10.1.117.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces13_38 = address13_38.Assign(devices13_38);
address14_41.SetBase("10.1.118.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces14_41 = address14_41.Assign(devices14_41);
address14_45.SetBase("10.1.119.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces14_45 = address14_45.Assign(devices14_45);
address14_49.SetBase("10.1.120.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces14_49 = address14_49.Assign(devices14_49);
address16_23.SetBase("10.1.121.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces16_23 = address16_23.Assign(devices16_23);
address16_27.SetBase("10.1.122.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces16_27 = address16_27.Assign(devices16_27);
address16_31.SetBase("10.1.123.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces16_31 = address16_31.Assign(devices16_31);
address17_34.SetBase("10.1.124.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces17_34 = address17_34.Assign(devices17_34);
address17_38.SetBase("10.1.125.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces17_38 = address17_38.Assign(devices17_38);
address17_42.SetBase("10.1.126.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces17_42 = address17_42.Assign(devices17_42);
address18_45.SetBase("10.1.127.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces18_45 = address18_45.Assign(devices18_45);
address18_49.SetBase("10.1.128.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces18_49 = address18_49.Assign(devices18_49);
address20_27.SetBase("10.1.129.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces20_27 = address20_27.Assign(devices20_27);
address20_31.SetBase("10.1.130.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces20_31 = address20_31.Assign(devices20_31);
address20_35.SetBase("10.1.131.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces20_35 = address20_35.Assign(devices20_35);
address21_38.SetBase("10.1.132.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_38 = address21_38.Assign(devices21_38);
address21_42.SetBase("10.1.133.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_42 = address21_42.Assign(devices21_42);
address21_46.SetBase("10.1.134.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_46 = address21_46.Assign(devices21_46);
address22_49.SetBase("10.1.135.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces22_49 = address22_49.Assign(devices22_49);
address24_31.SetBase("10.1.136.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces24_31 = address24_31.Assign(devices24_31);
address24_35.SetBase("10.1.137.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces24_35 = address24_35.Assign(devices24_35);
address24_39.SetBase("10.1.138.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces24_39 = address24_39.Assign(devices24_39);
address25_42.SetBase("10.1.139.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces25_42 = address25_42.Assign(devices25_42);
address25_46.SetBase("10.1.140.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces25_46 = address25_46.Assign(devices25_46);
address25_50.SetBase("10.1.141.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces25_50 = address25_50.Assign(devices25_50);
address28_35.SetBase("10.1.142.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces28_35 = address28_35.Assign(devices28_35);
address28_39.SetBase("10.1.143.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces28_39 = address28_39.Assign(devices28_39);
address28_43.SetBase("10.1.144.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces28_43 = address28_43.Assign(devices28_43);
address29_46.SetBase("10.1.145.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces29_46 = address29_46.Assign(devices29_46);
address29_50.SetBase("10.1.146.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces29_50 = address29_50.Assign(devices29_50);
address32_39.SetBase("10.1.147.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces32_39 = address32_39.Assign(devices32_39);
address32_43.SetBase("10.1.148.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces32_43 = address32_43.Assign(devices32_43);
address32_47.SetBase("10.1.149.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces32_47 = address32_47.Assign(devices32_47);
address33_50.SetBase("10.1.150.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces33_50 = address33_50.Assign(devices33_50);
address36_43.SetBase("10.1.151.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces36_43 = address36_43.Assign(devices36_43);
address36_47.SetBase("10.1.152.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces36_47 = address36_47.Assign(devices36_47);
address36_51.SetBase("10.1.153.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces36_51 = address36_51.Assign(devices36_51);
address40_47.SetBase("10.1.154.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces40_47 = address40_47.Assign(devices40_47);
address40_51.SetBase("10.1.155.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces40_51 = address40_51.Assign(devices40_51);
address44_51.SetBase("10.1.156.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces44_51 = address44_51.Assign(devices44_51);


  // 启用流监测器，使用 FlowMonitorHelper 启用流监测器，并将其安装在所有的设备上
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll();
  
  // Create a packet sink on the star "hub" to receive these packets
    uint16_t port = 50000;//端口号50000
    ApplicationContainer sinkApp;//这一句是定义服务器的
    Address sinkLocalAddress (InetSocketAddress (Ipv4Address::GetAny (), port));
    PacketSinkHelper sinkHelper ("ns3::TcpSocketFactory", sinkLocalAddress);//接收和消耗生成到IP地址和端口的流量
    //sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[16].Get(0)));//9是服务器端
    //sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[85].Get(1)));//33是服务器端
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[24].Get(0)));//16是服务器端
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[30].Get(1)));//21是服务器端
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[67].Get(1)));//46是服务器端
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[36].Get(0)));//24是服务器端
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[77].Get(1)));//51是服务器端
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
    //clientApps.Add(clientHelper.Install(nodeAdjacencyList[6].Get(0)));
    //4负责发送数据，使用的应用层定义是上面的clientHelper
    
    //20->21
    AddressValue remoteAddress (InetSocketAddress (interfaces20_21.GetAddress (1), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[30].Get(0)));
    //20负责发送数据，使用的应用层定义是上面的clientHelper
    
    //20->46
    remoteAddress=AddressValue(InetSocketAddress (interfaces46_47.GetAddress (0), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[30].Get(0)));
    //20负责发送数据，使用的应用层定义是上面的clientHelper
    
    //12->24
    remoteAddress=AddressValue(InetSocketAddress (interfaces12_13.GetAddress (0), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[18].Get(0)));
    //12负责发送数据，使用的应用层定义是上面的clientHelper
    
    //50->51
    remoteAddress=AddressValue(InetSocketAddress (interfaces50_51.GetAddress (1), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[77].Get(0)));
    //50负责发送数据，使用的应用层定义是上面的clientHelper
    
    clientApps.Start(Seconds(1.0));
    clientApps.Stop (Seconds (61.0));
  
  // 启用 OSPF
  Ipv4GlobalRoutingHelper::PopulateRoutingTables();
  
  
  
  
  // 配置输出流
  AsciiTraceHelper throughputAscii, lossAscii, delayAscii;
  Ptr<OutputStreamWrapper> throughputStream = throughputAscii.CreateFileStream("D32_throughput.txt");
  Ptr<OutputStreamWrapper> lossStream = lossAscii.CreateFileStream("D32_loss.txt");
  Ptr<OutputStreamWrapper> delayStream = delayAscii.CreateFileStream("D32_delay.txt");
  
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

