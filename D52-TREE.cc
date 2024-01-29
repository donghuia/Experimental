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
  nodes.Create(186);
  
  //各条边的节点组合
  vector<NodeContainer> nodeAdjacencyList(185);
  

nodeAdjacencyList[0]=NodeContainer(nodes.Get(0), nodes.Get(155)); 
nodeAdjacencyList[1]=NodeContainer(nodes.Get(0), nodes.Get(156)); 
nodeAdjacencyList[2]=NodeContainer(nodes.Get(0), nodes.Get(157)); 
nodeAdjacencyList[3]=NodeContainer(nodes.Get(0), nodes.Get(158)); 
nodeAdjacencyList[4]=NodeContainer(nodes.Get(0), nodes.Get(159)); 
nodeAdjacencyList[5]=NodeContainer(nodes.Get(0), nodes.Get(160)); 
nodeAdjacencyList[6]=NodeContainer(nodes.Get(0), nodes.Get(31)); 
nodeAdjacencyList[7]=NodeContainer(nodes.Get(0), nodes.Get(62)); 
nodeAdjacencyList[8]=NodeContainer(nodes.Get(155), nodes.Get(26)); 
nodeAdjacencyList[9]=NodeContainer(nodes.Get(155), nodes.Get(27)); 
nodeAdjacencyList[10]=NodeContainer(nodes.Get(155), nodes.Get(28)); 
nodeAdjacencyList[11]=NodeContainer(nodes.Get(155), nodes.Get(29)); 
nodeAdjacencyList[12]=NodeContainer(nodes.Get(155), nodes.Get(30)); 
nodeAdjacencyList[13]=NodeContainer(nodes.Get(155), nodes.Get(93)); 
nodeAdjacencyList[14]=NodeContainer(nodes.Get(155), nodes.Get(124)); 
nodeAdjacencyList[15]=NodeContainer(nodes.Get(156), nodes.Get(1)); 
nodeAdjacencyList[16]=NodeContainer(nodes.Get(156), nodes.Get(94)); 
nodeAdjacencyList[17]=NodeContainer(nodes.Get(156), nodes.Get(125)); 
nodeAdjacencyList[18]=NodeContainer(nodes.Get(1), nodes.Get(161)); 
nodeAdjacencyList[19]=NodeContainer(nodes.Get(1), nodes.Get(32)); 
nodeAdjacencyList[20]=NodeContainer(nodes.Get(1), nodes.Get(63)); 
nodeAdjacencyList[21]=NodeContainer(nodes.Get(157), nodes.Get(2)); 
nodeAdjacencyList[22]=NodeContainer(nodes.Get(157), nodes.Get(95)); 
nodeAdjacencyList[23]=NodeContainer(nodes.Get(157), nodes.Get(126)); 
nodeAdjacencyList[24]=NodeContainer(nodes.Get(2), nodes.Get(162)); 
nodeAdjacencyList[25]=NodeContainer(nodes.Get(2), nodes.Get(33)); 
nodeAdjacencyList[26]=NodeContainer(nodes.Get(2), nodes.Get(64)); 
nodeAdjacencyList[27]=NodeContainer(nodes.Get(158), nodes.Get(3)); 
nodeAdjacencyList[28]=NodeContainer(nodes.Get(158), nodes.Get(96)); 
nodeAdjacencyList[29]=NodeContainer(nodes.Get(158), nodes.Get(127)); 
nodeAdjacencyList[30]=NodeContainer(nodes.Get(3), nodes.Get(163)); 
nodeAdjacencyList[31]=NodeContainer(nodes.Get(3), nodes.Get(34)); 
nodeAdjacencyList[32]=NodeContainer(nodes.Get(3), nodes.Get(65)); 
nodeAdjacencyList[33]=NodeContainer(nodes.Get(159), nodes.Get(4)); 
nodeAdjacencyList[34]=NodeContainer(nodes.Get(159), nodes.Get(97)); 
nodeAdjacencyList[35]=NodeContainer(nodes.Get(159), nodes.Get(128)); 
nodeAdjacencyList[36]=NodeContainer(nodes.Get(4), nodes.Get(164)); 
nodeAdjacencyList[37]=NodeContainer(nodes.Get(4), nodes.Get(35)); 
nodeAdjacencyList[38]=NodeContainer(nodes.Get(4), nodes.Get(66)); 
nodeAdjacencyList[39]=NodeContainer(nodes.Get(160), nodes.Get(5)); 
nodeAdjacencyList[40]=NodeContainer(nodes.Get(160), nodes.Get(98)); 
nodeAdjacencyList[41]=NodeContainer(nodes.Get(160), nodes.Get(129)); 
nodeAdjacencyList[42]=NodeContainer(nodes.Get(5), nodes.Get(165)); 
nodeAdjacencyList[43]=NodeContainer(nodes.Get(5), nodes.Get(36)); 
nodeAdjacencyList[44]=NodeContainer(nodes.Get(5), nodes.Get(67)); 
nodeAdjacencyList[45]=NodeContainer(nodes.Get(26), nodes.Get(181)); 
nodeAdjacencyList[46]=NodeContainer(nodes.Get(26), nodes.Get(57)); 
nodeAdjacencyList[47]=NodeContainer(nodes.Get(26), nodes.Get(88)); 
nodeAdjacencyList[48]=NodeContainer(nodes.Get(181), nodes.Get(21)); 
nodeAdjacencyList[49]=NodeContainer(nodes.Get(181), nodes.Get(22)); 
nodeAdjacencyList[50]=NodeContainer(nodes.Get(181), nodes.Get(23)); 
nodeAdjacencyList[51]=NodeContainer(nodes.Get(181), nodes.Get(24)); 
nodeAdjacencyList[52]=NodeContainer(nodes.Get(181), nodes.Get(25)); 
nodeAdjacencyList[53]=NodeContainer(nodes.Get(181), nodes.Get(119)); 
nodeAdjacencyList[54]=NodeContainer(nodes.Get(181), nodes.Get(150)); 
nodeAdjacencyList[55]=NodeContainer(nodes.Get(27), nodes.Get(182)); 
nodeAdjacencyList[56]=NodeContainer(nodes.Get(27), nodes.Get(58)); 
nodeAdjacencyList[57]=NodeContainer(nodes.Get(27), nodes.Get(89)); 
nodeAdjacencyList[58]=NodeContainer(nodes.Get(182), nodes.Get(120)); 
nodeAdjacencyList[59]=NodeContainer(nodes.Get(182), nodes.Get(151)); 
nodeAdjacencyList[60]=NodeContainer(nodes.Get(28), nodes.Get(183)); 
nodeAdjacencyList[61]=NodeContainer(nodes.Get(28), nodes.Get(59)); 
nodeAdjacencyList[62]=NodeContainer(nodes.Get(28), nodes.Get(90)); 
nodeAdjacencyList[63]=NodeContainer(nodes.Get(183), nodes.Get(121)); 
nodeAdjacencyList[64]=NodeContainer(nodes.Get(183), nodes.Get(152)); 
nodeAdjacencyList[65]=NodeContainer(nodes.Get(29), nodes.Get(184)); 
nodeAdjacencyList[66]=NodeContainer(nodes.Get(29), nodes.Get(60)); 
nodeAdjacencyList[67]=NodeContainer(nodes.Get(29), nodes.Get(91)); 
nodeAdjacencyList[68]=NodeContainer(nodes.Get(184), nodes.Get(122)); 
nodeAdjacencyList[69]=NodeContainer(nodes.Get(184), nodes.Get(153)); 
nodeAdjacencyList[70]=NodeContainer(nodes.Get(30), nodes.Get(185)); 
nodeAdjacencyList[71]=NodeContainer(nodes.Get(30), nodes.Get(61)); 
nodeAdjacencyList[72]=NodeContainer(nodes.Get(30), nodes.Get(92)); 
nodeAdjacencyList[73]=NodeContainer(nodes.Get(185), nodes.Get(123)); 
nodeAdjacencyList[74]=NodeContainer(nodes.Get(185), nodes.Get(154)); 
nodeAdjacencyList[75]=NodeContainer(nodes.Get(161), nodes.Get(6)); 
nodeAdjacencyList[76]=NodeContainer(nodes.Get(161), nodes.Get(99)); 
nodeAdjacencyList[77]=NodeContainer(nodes.Get(161), nodes.Get(130)); 
nodeAdjacencyList[78]=NodeContainer(nodes.Get(6), nodes.Get(166)); 
nodeAdjacencyList[79]=NodeContainer(nodes.Get(6), nodes.Get(37)); 
nodeAdjacencyList[80]=NodeContainer(nodes.Get(6), nodes.Get(68)); 
nodeAdjacencyList[81]=NodeContainer(nodes.Get(162), nodes.Get(7)); 
nodeAdjacencyList[82]=NodeContainer(nodes.Get(162), nodes.Get(100)); 
nodeAdjacencyList[83]=NodeContainer(nodes.Get(162), nodes.Get(131)); 
nodeAdjacencyList[84]=NodeContainer(nodes.Get(7), nodes.Get(167)); 
nodeAdjacencyList[85]=NodeContainer(nodes.Get(7), nodes.Get(38)); 
nodeAdjacencyList[86]=NodeContainer(nodes.Get(7), nodes.Get(69)); 
nodeAdjacencyList[87]=NodeContainer(nodes.Get(163), nodes.Get(8)); 
nodeAdjacencyList[88]=NodeContainer(nodes.Get(163), nodes.Get(101)); 
nodeAdjacencyList[89]=NodeContainer(nodes.Get(163), nodes.Get(132)); 
nodeAdjacencyList[90]=NodeContainer(nodes.Get(8), nodes.Get(168)); 
nodeAdjacencyList[91]=NodeContainer(nodes.Get(8), nodes.Get(39)); 
nodeAdjacencyList[92]=NodeContainer(nodes.Get(8), nodes.Get(70)); 
nodeAdjacencyList[93]=NodeContainer(nodes.Get(164), nodes.Get(9)); 
nodeAdjacencyList[94]=NodeContainer(nodes.Get(164), nodes.Get(102)); 
nodeAdjacencyList[95]=NodeContainer(nodes.Get(164), nodes.Get(133)); 
nodeAdjacencyList[96]=NodeContainer(nodes.Get(9), nodes.Get(169)); 
nodeAdjacencyList[97]=NodeContainer(nodes.Get(9), nodes.Get(40)); 
nodeAdjacencyList[98]=NodeContainer(nodes.Get(9), nodes.Get(71)); 
nodeAdjacencyList[99]=NodeContainer(nodes.Get(165), nodes.Get(10)); 
nodeAdjacencyList[100]=NodeContainer(nodes.Get(165), nodes.Get(103)); 
nodeAdjacencyList[101]=NodeContainer(nodes.Get(165), nodes.Get(134)); 
nodeAdjacencyList[102]=NodeContainer(nodes.Get(10), nodes.Get(170)); 
nodeAdjacencyList[103]=NodeContainer(nodes.Get(10), nodes.Get(41)); 
nodeAdjacencyList[104]=NodeContainer(nodes.Get(10), nodes.Get(72)); 
nodeAdjacencyList[105]=NodeContainer(nodes.Get(21), nodes.Get(176)); 
nodeAdjacencyList[106]=NodeContainer(nodes.Get(21), nodes.Get(52)); 
nodeAdjacencyList[107]=NodeContainer(nodes.Get(21), nodes.Get(83)); 
nodeAdjacencyList[108]=NodeContainer(nodes.Get(176), nodes.Get(16)); 
nodeAdjacencyList[109]=NodeContainer(nodes.Get(176), nodes.Get(17)); 
nodeAdjacencyList[110]=NodeContainer(nodes.Get(176), nodes.Get(18)); 
nodeAdjacencyList[111]=NodeContainer(nodes.Get(176), nodes.Get(19)); 
nodeAdjacencyList[112]=NodeContainer(nodes.Get(176), nodes.Get(20)); 
nodeAdjacencyList[113]=NodeContainer(nodes.Get(176), nodes.Get(114)); 
nodeAdjacencyList[114]=NodeContainer(nodes.Get(176), nodes.Get(145)); 
nodeAdjacencyList[115]=NodeContainer(nodes.Get(22), nodes.Get(177)); 
nodeAdjacencyList[116]=NodeContainer(nodes.Get(22), nodes.Get(53)); 
nodeAdjacencyList[117]=NodeContainer(nodes.Get(22), nodes.Get(84)); 
nodeAdjacencyList[118]=NodeContainer(nodes.Get(177), nodes.Get(115)); 
nodeAdjacencyList[119]=NodeContainer(nodes.Get(177), nodes.Get(146)); 
nodeAdjacencyList[120]=NodeContainer(nodes.Get(23), nodes.Get(178)); 
nodeAdjacencyList[121]=NodeContainer(nodes.Get(23), nodes.Get(54)); 
nodeAdjacencyList[122]=NodeContainer(nodes.Get(23), nodes.Get(85)); 
nodeAdjacencyList[123]=NodeContainer(nodes.Get(178), nodes.Get(116)); 
nodeAdjacencyList[124]=NodeContainer(nodes.Get(178), nodes.Get(147)); 
nodeAdjacencyList[125]=NodeContainer(nodes.Get(24), nodes.Get(179)); 
nodeAdjacencyList[126]=NodeContainer(nodes.Get(24), nodes.Get(55)); 
nodeAdjacencyList[127]=NodeContainer(nodes.Get(24), nodes.Get(86)); 
nodeAdjacencyList[128]=NodeContainer(nodes.Get(179), nodes.Get(117)); 
nodeAdjacencyList[129]=NodeContainer(nodes.Get(179), nodes.Get(148)); 
nodeAdjacencyList[130]=NodeContainer(nodes.Get(25), nodes.Get(180)); 
nodeAdjacencyList[131]=NodeContainer(nodes.Get(25), nodes.Get(56)); 
nodeAdjacencyList[132]=NodeContainer(nodes.Get(25), nodes.Get(87)); 
nodeAdjacencyList[133]=NodeContainer(nodes.Get(180), nodes.Get(118)); 
nodeAdjacencyList[134]=NodeContainer(nodes.Get(180), nodes.Get(149)); 
nodeAdjacencyList[135]=NodeContainer(nodes.Get(166), nodes.Get(11)); 
nodeAdjacencyList[136]=NodeContainer(nodes.Get(166), nodes.Get(104)); 
nodeAdjacencyList[137]=NodeContainer(nodes.Get(166), nodes.Get(135)); 
nodeAdjacencyList[138]=NodeContainer(nodes.Get(11), nodes.Get(42)); 
nodeAdjacencyList[139]=NodeContainer(nodes.Get(11), nodes.Get(73)); 
nodeAdjacencyList[140]=NodeContainer(nodes.Get(167), nodes.Get(12)); 
nodeAdjacencyList[141]=NodeContainer(nodes.Get(167), nodes.Get(105)); 
nodeAdjacencyList[142]=NodeContainer(nodes.Get(167), nodes.Get(136)); 
nodeAdjacencyList[143]=NodeContainer(nodes.Get(12), nodes.Get(43)); 
nodeAdjacencyList[144]=NodeContainer(nodes.Get(12), nodes.Get(74)); 
nodeAdjacencyList[145]=NodeContainer(nodes.Get(168), nodes.Get(13)); 
nodeAdjacencyList[146]=NodeContainer(nodes.Get(168), nodes.Get(106)); 
nodeAdjacencyList[147]=NodeContainer(nodes.Get(168), nodes.Get(137)); 
nodeAdjacencyList[148]=NodeContainer(nodes.Get(13), nodes.Get(44)); 
nodeAdjacencyList[149]=NodeContainer(nodes.Get(13), nodes.Get(75)); 
nodeAdjacencyList[150]=NodeContainer(nodes.Get(169), nodes.Get(14)); 
nodeAdjacencyList[151]=NodeContainer(nodes.Get(169), nodes.Get(107)); 
nodeAdjacencyList[152]=NodeContainer(nodes.Get(169), nodes.Get(138)); 
nodeAdjacencyList[153]=NodeContainer(nodes.Get(14), nodes.Get(45)); 
nodeAdjacencyList[154]=NodeContainer(nodes.Get(14), nodes.Get(76)); 
nodeAdjacencyList[155]=NodeContainer(nodes.Get(170), nodes.Get(15)); 
nodeAdjacencyList[156]=NodeContainer(nodes.Get(170), nodes.Get(108)); 
nodeAdjacencyList[157]=NodeContainer(nodes.Get(170), nodes.Get(139)); 
nodeAdjacencyList[158]=NodeContainer(nodes.Get(15), nodes.Get(46)); 
nodeAdjacencyList[159]=NodeContainer(nodes.Get(15), nodes.Get(77)); 
nodeAdjacencyList[160]=NodeContainer(nodes.Get(16), nodes.Get(171)); 
nodeAdjacencyList[161]=NodeContainer(nodes.Get(16), nodes.Get(47)); 
nodeAdjacencyList[162]=NodeContainer(nodes.Get(16), nodes.Get(78)); 
nodeAdjacencyList[163]=NodeContainer(nodes.Get(171), nodes.Get(109)); 
nodeAdjacencyList[164]=NodeContainer(nodes.Get(171), nodes.Get(140)); 
nodeAdjacencyList[165]=NodeContainer(nodes.Get(17), nodes.Get(172)); 
nodeAdjacencyList[166]=NodeContainer(nodes.Get(17), nodes.Get(48)); 
nodeAdjacencyList[167]=NodeContainer(nodes.Get(17), nodes.Get(79)); 
nodeAdjacencyList[168]=NodeContainer(nodes.Get(172), nodes.Get(110)); 
nodeAdjacencyList[169]=NodeContainer(nodes.Get(172), nodes.Get(141)); 
nodeAdjacencyList[170]=NodeContainer(nodes.Get(18), nodes.Get(173)); 
nodeAdjacencyList[171]=NodeContainer(nodes.Get(18), nodes.Get(49)); 
nodeAdjacencyList[172]=NodeContainer(nodes.Get(18), nodes.Get(80)); 
nodeAdjacencyList[173]=NodeContainer(nodes.Get(173), nodes.Get(111)); 
nodeAdjacencyList[174]=NodeContainer(nodes.Get(173), nodes.Get(142)); 
nodeAdjacencyList[175]=NodeContainer(nodes.Get(19), nodes.Get(174)); 
nodeAdjacencyList[176]=NodeContainer(nodes.Get(19), nodes.Get(50)); 
nodeAdjacencyList[177]=NodeContainer(nodes.Get(19), nodes.Get(81)); 
nodeAdjacencyList[178]=NodeContainer(nodes.Get(174), nodes.Get(112)); 
nodeAdjacencyList[179]=NodeContainer(nodes.Get(174), nodes.Get(143)); 
nodeAdjacencyList[180]=NodeContainer(nodes.Get(20), nodes.Get(175)); 
nodeAdjacencyList[181]=NodeContainer(nodes.Get(20), nodes.Get(51)); 
nodeAdjacencyList[182]=NodeContainer(nodes.Get(20), nodes.Get(82)); 
nodeAdjacencyList[183]=NodeContainer(nodes.Get(175), nodes.Get(113)); 
nodeAdjacencyList[184]=NodeContainer(nodes.Get(175), nodes.Get(144)); 





  // 创建节点之间的连接，分别设置传输速率和传播延迟
  
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute("DataRate", StringValue("100Mbps"));
  p2p.SetChannelAttribute("Delay", StringValue("1ms"));

  //通过 Install 函数将设备配置应用到相应的节点上，形成了网络拓扑
  NetDeviceContainer 
devices0_155,
devices0_156,
devices0_157,
devices0_158,
devices0_159,
devices0_160,
devices0_31,
devices0_62,
devices155_26,
devices155_27,
devices155_28,
devices155_29,
devices155_30,
devices155_93,
devices155_124,
devices156_1,
devices156_94,
devices156_125,
devices1_161,
devices1_32,
devices1_63,
devices157_2,
devices157_95,
devices157_126,
devices2_162,
devices2_33,
devices2_64,
devices158_3,
devices158_96,
devices158_127,
devices3_163,
devices3_34,
devices3_65,
devices159_4,
devices159_97,
devices159_128,
devices4_164,
devices4_35,
devices4_66,
devices160_5,
devices160_98,
devices160_129,
devices5_165,
devices5_36,
devices5_67,
devices26_181,
devices26_57,
devices26_88,
devices181_21,
devices181_22,
devices181_23,
devices181_24,
devices181_25,
devices181_119,
devices181_150,
devices27_182,
devices27_58,
devices27_89,
devices182_120,
devices182_151,
devices28_183,
devices28_59,
devices28_90,
devices183_121,
devices183_152,
devices29_184,
devices29_60,
devices29_91,
devices184_122,
devices184_153,
devices30_185,
devices30_61,
devices30_92,
devices185_123,
devices185_154,
devices161_6,
devices161_99,
devices161_130,
devices6_166,
devices6_37,
devices6_68,
devices162_7,
devices162_100,
devices162_131,
devices7_167,
devices7_38,
devices7_69,
devices163_8,
devices163_101,
devices163_132,
devices8_168,
devices8_39,
devices8_70,
devices164_9,
devices164_102,
devices164_133,
devices9_169,
devices9_40,
devices9_71,
devices165_10,
devices165_103,
devices165_134,
devices10_170,
devices10_41,
devices10_72,
devices21_176,
devices21_52,
devices21_83,
devices176_16,
devices176_17,
devices176_18,
devices176_19,
devices176_20,
devices176_114,
devices176_145,
devices22_177,
devices22_53,
devices22_84,
devices177_115,
devices177_146,
devices23_178,
devices23_54,
devices23_85,
devices178_116,
devices178_147,
devices24_179,
devices24_55,
devices24_86,
devices179_117,
devices179_148,
devices25_180,
devices25_56,
devices25_87,
devices180_118,
devices180_149,
devices166_11,
devices166_104,
devices166_135,
devices11_42,
devices11_73,
devices167_12,
devices167_105,
devices167_136,
devices12_43,
devices12_74,
devices168_13,
devices168_106,
devices168_137,
devices13_44,
devices13_75,
devices169_14,
devices169_107,
devices169_138,
devices14_45,
devices14_76,
devices170_15,
devices170_108,
devices170_139,
devices15_46,
devices15_77,
devices16_171,
devices16_47,
devices16_78,
devices171_109,
devices171_140,
devices17_172,
devices17_48,
devices17_79,
devices172_110,
devices172_141,
devices18_173,
devices18_49,
devices18_80,
devices173_111,
devices173_142,
devices19_174,
devices19_50,
devices19_81,
devices174_112,
devices174_143,
devices20_175,
devices20_51,
devices20_82,
devices175_113,
devices175_144;

 
devices0_155= p2p.Install(nodes.Get(0), nodes.Get(155)); 
devices0_156= p2p.Install(nodes.Get(0), nodes.Get(156)); 
devices0_157= p2p.Install(nodes.Get(0), nodes.Get(157)); 
devices0_158= p2p.Install(nodes.Get(0), nodes.Get(158)); 
devices0_159= p2p.Install(nodes.Get(0), nodes.Get(159)); 
devices0_160= p2p.Install(nodes.Get(0), nodes.Get(160)); 
devices0_31= p2p.Install(nodes.Get(0), nodes.Get(31)); 
devices0_62= p2p.Install(nodes.Get(0), nodes.Get(62)); 
devices155_26= p2p.Install(nodes.Get(155), nodes.Get(26)); 
devices155_27= p2p.Install(nodes.Get(155), nodes.Get(27)); 
devices155_28= p2p.Install(nodes.Get(155), nodes.Get(28)); 
devices155_29= p2p.Install(nodes.Get(155), nodes.Get(29)); 
devices155_30= p2p.Install(nodes.Get(155), nodes.Get(30)); 
devices155_93= p2p.Install(nodes.Get(155), nodes.Get(93)); 
devices155_124= p2p.Install(nodes.Get(155), nodes.Get(124)); 
devices156_1= p2p.Install(nodes.Get(156), nodes.Get(1)); 
devices156_94= p2p.Install(nodes.Get(156), nodes.Get(94)); 
devices156_125= p2p.Install(nodes.Get(156), nodes.Get(125)); 
devices1_161= p2p.Install(nodes.Get(1), nodes.Get(161)); 
devices1_32= p2p.Install(nodes.Get(1), nodes.Get(32)); 
devices1_63= p2p.Install(nodes.Get(1), nodes.Get(63)); 
devices157_2= p2p.Install(nodes.Get(157), nodes.Get(2)); 
devices157_95= p2p.Install(nodes.Get(157), nodes.Get(95)); 
devices157_126= p2p.Install(nodes.Get(157), nodes.Get(126)); 
devices2_162= p2p.Install(nodes.Get(2), nodes.Get(162)); 
devices2_33= p2p.Install(nodes.Get(2), nodes.Get(33)); 
devices2_64= p2p.Install(nodes.Get(2), nodes.Get(64)); 
devices158_3= p2p.Install(nodes.Get(158), nodes.Get(3)); 
devices158_96= p2p.Install(nodes.Get(158), nodes.Get(96)); 
devices158_127= p2p.Install(nodes.Get(158), nodes.Get(127)); 
devices3_163= p2p.Install(nodes.Get(3), nodes.Get(163)); 
devices3_34= p2p.Install(nodes.Get(3), nodes.Get(34)); 
devices3_65= p2p.Install(nodes.Get(3), nodes.Get(65)); 
devices159_4= p2p.Install(nodes.Get(159), nodes.Get(4)); 
devices159_97= p2p.Install(nodes.Get(159), nodes.Get(97)); 
devices159_128= p2p.Install(nodes.Get(159), nodes.Get(128)); 
devices4_164= p2p.Install(nodes.Get(4), nodes.Get(164)); 
devices4_35= p2p.Install(nodes.Get(4), nodes.Get(35)); 
devices4_66= p2p.Install(nodes.Get(4), nodes.Get(66)); 
devices160_5= p2p.Install(nodes.Get(160), nodes.Get(5)); 
devices160_98= p2p.Install(nodes.Get(160), nodes.Get(98)); 
devices160_129= p2p.Install(nodes.Get(160), nodes.Get(129)); 
devices5_165= p2p.Install(nodes.Get(5), nodes.Get(165)); 
devices5_36= p2p.Install(nodes.Get(5), nodes.Get(36)); 
devices5_67= p2p.Install(nodes.Get(5), nodes.Get(67)); 
devices26_181= p2p.Install(nodes.Get(26), nodes.Get(181)); 
devices26_57= p2p.Install(nodes.Get(26), nodes.Get(57)); 
devices26_88= p2p.Install(nodes.Get(26), nodes.Get(88)); 
devices181_21= p2p.Install(nodes.Get(181), nodes.Get(21)); 
devices181_22= p2p.Install(nodes.Get(181), nodes.Get(22)); 
devices181_23= p2p.Install(nodes.Get(181), nodes.Get(23)); 
devices181_24= p2p.Install(nodes.Get(181), nodes.Get(24)); 
devices181_25= p2p.Install(nodes.Get(181), nodes.Get(25)); 
devices181_119= p2p.Install(nodes.Get(181), nodes.Get(119)); 
devices181_150= p2p.Install(nodes.Get(181), nodes.Get(150)); 
devices27_182= p2p.Install(nodes.Get(27), nodes.Get(182)); 
devices27_58= p2p.Install(nodes.Get(27), nodes.Get(58)); 
devices27_89= p2p.Install(nodes.Get(27), nodes.Get(89)); 
devices182_120= p2p.Install(nodes.Get(182), nodes.Get(120)); 
devices182_151= p2p.Install(nodes.Get(182), nodes.Get(151)); 
devices28_183= p2p.Install(nodes.Get(28), nodes.Get(183)); 
devices28_59= p2p.Install(nodes.Get(28), nodes.Get(59)); 
devices28_90= p2p.Install(nodes.Get(28), nodes.Get(90)); 
devices183_121= p2p.Install(nodes.Get(183), nodes.Get(121)); 
devices183_152= p2p.Install(nodes.Get(183), nodes.Get(152)); 
devices29_184= p2p.Install(nodes.Get(29), nodes.Get(184)); 
devices29_60= p2p.Install(nodes.Get(29), nodes.Get(60)); 
devices29_91= p2p.Install(nodes.Get(29), nodes.Get(91)); 
devices184_122= p2p.Install(nodes.Get(184), nodes.Get(122)); 
devices184_153= p2p.Install(nodes.Get(184), nodes.Get(153)); 
devices30_185= p2p.Install(nodes.Get(30), nodes.Get(185)); 
devices30_61= p2p.Install(nodes.Get(30), nodes.Get(61)); 
devices30_92= p2p.Install(nodes.Get(30), nodes.Get(92)); 
devices185_123= p2p.Install(nodes.Get(185), nodes.Get(123)); 
devices185_154= p2p.Install(nodes.Get(185), nodes.Get(154)); 
devices161_6= p2p.Install(nodes.Get(161), nodes.Get(6)); 
devices161_99= p2p.Install(nodes.Get(161), nodes.Get(99)); 
devices161_130= p2p.Install(nodes.Get(161), nodes.Get(130)); 
devices6_166= p2p.Install(nodes.Get(6), nodes.Get(166)); 
devices6_37= p2p.Install(nodes.Get(6), nodes.Get(37)); 
devices6_68= p2p.Install(nodes.Get(6), nodes.Get(68)); 
devices162_7= p2p.Install(nodes.Get(162), nodes.Get(7)); 
devices162_100= p2p.Install(nodes.Get(162), nodes.Get(100)); 
devices162_131= p2p.Install(nodes.Get(162), nodes.Get(131)); 
devices7_167= p2p.Install(nodes.Get(7), nodes.Get(167)); 
devices7_38= p2p.Install(nodes.Get(7), nodes.Get(38)); 
devices7_69= p2p.Install(nodes.Get(7), nodes.Get(69)); 
devices163_8= p2p.Install(nodes.Get(163), nodes.Get(8)); 
devices163_101= p2p.Install(nodes.Get(163), nodes.Get(101)); 
devices163_132= p2p.Install(nodes.Get(163), nodes.Get(132)); 
devices8_168= p2p.Install(nodes.Get(8), nodes.Get(168)); 
devices8_39= p2p.Install(nodes.Get(8), nodes.Get(39)); 
devices8_70= p2p.Install(nodes.Get(8), nodes.Get(70)); 
devices164_9= p2p.Install(nodes.Get(164), nodes.Get(9)); 
devices164_102= p2p.Install(nodes.Get(164), nodes.Get(102)); 
devices164_133= p2p.Install(nodes.Get(164), nodes.Get(133)); 
devices9_169= p2p.Install(nodes.Get(9), nodes.Get(169)); 
devices9_40= p2p.Install(nodes.Get(9), nodes.Get(40)); 
devices9_71= p2p.Install(nodes.Get(9), nodes.Get(71)); 
devices165_10= p2p.Install(nodes.Get(165), nodes.Get(10)); 
devices165_103= p2p.Install(nodes.Get(165), nodes.Get(103)); 
devices165_134= p2p.Install(nodes.Get(165), nodes.Get(134)); 
devices10_170= p2p.Install(nodes.Get(10), nodes.Get(170)); 
devices10_41= p2p.Install(nodes.Get(10), nodes.Get(41)); 
devices10_72= p2p.Install(nodes.Get(10), nodes.Get(72)); 
devices21_176= p2p.Install(nodes.Get(21), nodes.Get(176)); 
devices21_52= p2p.Install(nodes.Get(21), nodes.Get(52)); 
devices21_83= p2p.Install(nodes.Get(21), nodes.Get(83)); 
devices176_16= p2p.Install(nodes.Get(176), nodes.Get(16)); 
devices176_17= p2p.Install(nodes.Get(176), nodes.Get(17)); 
devices176_18= p2p.Install(nodes.Get(176), nodes.Get(18)); 
devices176_19= p2p.Install(nodes.Get(176), nodes.Get(19)); 
devices176_20= p2p.Install(nodes.Get(176), nodes.Get(20)); 
devices176_114= p2p.Install(nodes.Get(176), nodes.Get(114)); 
devices176_145= p2p.Install(nodes.Get(176), nodes.Get(145)); 
devices22_177= p2p.Install(nodes.Get(22), nodes.Get(177)); 
devices22_53= p2p.Install(nodes.Get(22), nodes.Get(53)); 
devices22_84= p2p.Install(nodes.Get(22), nodes.Get(84)); 
devices177_115= p2p.Install(nodes.Get(177), nodes.Get(115)); 
devices177_146= p2p.Install(nodes.Get(177), nodes.Get(146)); 
devices23_178= p2p.Install(nodes.Get(23), nodes.Get(178)); 
devices23_54= p2p.Install(nodes.Get(23), nodes.Get(54)); 
devices23_85= p2p.Install(nodes.Get(23), nodes.Get(85)); 
devices178_116= p2p.Install(nodes.Get(178), nodes.Get(116)); 
devices178_147= p2p.Install(nodes.Get(178), nodes.Get(147)); 
devices24_179= p2p.Install(nodes.Get(24), nodes.Get(179)); 
devices24_55= p2p.Install(nodes.Get(24), nodes.Get(55)); 
devices24_86= p2p.Install(nodes.Get(24), nodes.Get(86)); 
devices179_117= p2p.Install(nodes.Get(179), nodes.Get(117)); 
devices179_148= p2p.Install(nodes.Get(179), nodes.Get(148)); 
devices25_180= p2p.Install(nodes.Get(25), nodes.Get(180)); 
devices25_56= p2p.Install(nodes.Get(25), nodes.Get(56)); 
devices25_87= p2p.Install(nodes.Get(25), nodes.Get(87)); 
devices180_118= p2p.Install(nodes.Get(180), nodes.Get(118)); 
devices180_149= p2p.Install(nodes.Get(180), nodes.Get(149)); 
devices166_11= p2p.Install(nodes.Get(166), nodes.Get(11)); 
devices166_104= p2p.Install(nodes.Get(166), nodes.Get(104)); 
devices166_135= p2p.Install(nodes.Get(166), nodes.Get(135)); 
devices11_42= p2p.Install(nodes.Get(11), nodes.Get(42)); 
devices11_73= p2p.Install(nodes.Get(11), nodes.Get(73)); 
devices167_12= p2p.Install(nodes.Get(167), nodes.Get(12)); 
devices167_105= p2p.Install(nodes.Get(167), nodes.Get(105)); 
devices167_136= p2p.Install(nodes.Get(167), nodes.Get(136)); 
devices12_43= p2p.Install(nodes.Get(12), nodes.Get(43)); 
devices12_74= p2p.Install(nodes.Get(12), nodes.Get(74)); 
devices168_13= p2p.Install(nodes.Get(168), nodes.Get(13)); 
devices168_106= p2p.Install(nodes.Get(168), nodes.Get(106)); 
devices168_137= p2p.Install(nodes.Get(168), nodes.Get(137)); 
devices13_44= p2p.Install(nodes.Get(13), nodes.Get(44)); 
devices13_75= p2p.Install(nodes.Get(13), nodes.Get(75)); 
devices169_14= p2p.Install(nodes.Get(169), nodes.Get(14)); 
devices169_107= p2p.Install(nodes.Get(169), nodes.Get(107)); 
devices169_138= p2p.Install(nodes.Get(169), nodes.Get(138)); 
devices14_45= p2p.Install(nodes.Get(14), nodes.Get(45)); 
devices14_76= p2p.Install(nodes.Get(14), nodes.Get(76)); 
devices170_15= p2p.Install(nodes.Get(170), nodes.Get(15)); 
devices170_108= p2p.Install(nodes.Get(170), nodes.Get(108)); 
devices170_139= p2p.Install(nodes.Get(170), nodes.Get(139)); 
devices15_46= p2p.Install(nodes.Get(15), nodes.Get(46)); 
devices15_77= p2p.Install(nodes.Get(15), nodes.Get(77)); 
devices16_171= p2p.Install(nodes.Get(16), nodes.Get(171)); 
devices16_47= p2p.Install(nodes.Get(16), nodes.Get(47)); 
devices16_78= p2p.Install(nodes.Get(16), nodes.Get(78)); 
devices171_109= p2p.Install(nodes.Get(171), nodes.Get(109)); 
devices171_140= p2p.Install(nodes.Get(171), nodes.Get(140)); 
devices17_172= p2p.Install(nodes.Get(17), nodes.Get(172)); 
devices17_48= p2p.Install(nodes.Get(17), nodes.Get(48)); 
devices17_79= p2p.Install(nodes.Get(17), nodes.Get(79)); 
devices172_110= p2p.Install(nodes.Get(172), nodes.Get(110)); 
devices172_141= p2p.Install(nodes.Get(172), nodes.Get(141)); 
devices18_173= p2p.Install(nodes.Get(18), nodes.Get(173)); 
devices18_49= p2p.Install(nodes.Get(18), nodes.Get(49)); 
devices18_80= p2p.Install(nodes.Get(18), nodes.Get(80)); 
devices173_111= p2p.Install(nodes.Get(173), nodes.Get(111)); 
devices173_142= p2p.Install(nodes.Get(173), nodes.Get(142)); 
devices19_174= p2p.Install(nodes.Get(19), nodes.Get(174)); 
devices19_50= p2p.Install(nodes.Get(19), nodes.Get(50)); 
devices19_81= p2p.Install(nodes.Get(19), nodes.Get(81)); 
devices174_112= p2p.Install(nodes.Get(174), nodes.Get(112)); 
devices174_143= p2p.Install(nodes.Get(174), nodes.Get(143)); 
devices20_175= p2p.Install(nodes.Get(20), nodes.Get(175)); 
devices20_51= p2p.Install(nodes.Get(20), nodes.Get(51)); 
devices20_82= p2p.Install(nodes.Get(20), nodes.Get(82)); 
devices175_113= p2p.Install(nodes.Get(175), nodes.Get(113)); 
devices175_144= p2p.Install(nodes.Get(175), nodes.Get(144)); 


  // 安装Internet协议栈
  InternetStackHelper internet;
  internet.Install(nodes);
  

  Ipv4AddressHelper 
address0_155,
address0_156,
address0_157,
address0_158,
address0_159,
address0_160,
address0_31,
address0_62,
address155_26,
address155_27,
address155_28,
address155_29,
address155_30,
address155_93,
address155_124,
address156_1,
address156_94,
address156_125,
address1_161,
address1_32,
address1_63,
address157_2,
address157_95,
address157_126,
address2_162,
address2_33,
address2_64,
address158_3,
address158_96,
address158_127,
address3_163,
address3_34,
address3_65,
address159_4,
address159_97,
address159_128,
address4_164,
address4_35,
address4_66,
address160_5,
address160_98,
address160_129,
address5_165,
address5_36,
address5_67,
address26_181,
address26_57,
address26_88,
address181_21,
address181_22,
address181_23,
address181_24,
address181_25,
address181_119,
address181_150,
address27_182,
address27_58,
address27_89,
address182_120,
address182_151,
address28_183,
address28_59,
address28_90,
address183_121,
address183_152,
address29_184,
address29_60,
address29_91,
address184_122,
address184_153,
address30_185,
address30_61,
address30_92,
address185_123,
address185_154,
address161_6,
address161_99,
address161_130,
address6_166,
address6_37,
address6_68,
address162_7,
address162_100,
address162_131,
address7_167,
address7_38,
address7_69,
address163_8,
address163_101,
address163_132,
address8_168,
address8_39,
address8_70,
address164_9,
address164_102,
address164_133,
address9_169,
address9_40,
address9_71,
address165_10,
address165_103,
address165_134,
address10_170,
address10_41,
address10_72,
address21_176,
address21_52,
address21_83,
address176_16,
address176_17,
address176_18,
address176_19,
address176_20,
address176_114,
address176_145,
address22_177,
address22_53,
address22_84,
address177_115,
address177_146,
address23_178,
address23_54,
address23_85,
address178_116,
address178_147,
address24_179,
address24_55,
address24_86,
address179_117,
address179_148,
address25_180,
address25_56,
address25_87,
address180_118,
address180_149,
address166_11,
address166_104,
address166_135,
address11_42,
address11_73,
address167_12,
address167_105,
address167_136,
address12_43,
address12_74,
address168_13,
address168_106,
address168_137,
address13_44,
address13_75,
address169_14,
address169_107,
address169_138,
address14_45,
address14_76,
address170_15,
address170_108,
address170_139,
address15_46,
address15_77,
address16_171,
address16_47,
address16_78,
address171_109,
address171_140,
address17_172,
address17_48,
address17_79,
address172_110,
address172_141,
address18_173,
address18_49,
address18_80,
address173_111,
address173_142,
address19_174,
address19_50,
address19_81,
address174_112,
address174_143,
address20_175,
address20_51,
address20_82,
address175_113,
address175_144;


address0_155.SetBase("10.1.2.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_155 = address0_155.Assign(devices0_155);
address0_156.SetBase("10.1.3.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_156 = address0_156.Assign(devices0_156);
address0_157.SetBase("10.1.4.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_157 = address0_157.Assign(devices0_157);
address0_158.SetBase("10.1.5.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_158 = address0_158.Assign(devices0_158);
address0_159.SetBase("10.1.6.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_159 = address0_159.Assign(devices0_159);
address0_160.SetBase("10.1.7.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_160 = address0_160.Assign(devices0_160);
address0_31.SetBase("10.1.8.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_31 = address0_31.Assign(devices0_31);
address0_62.SetBase("10.1.9.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces0_62 = address0_62.Assign(devices0_62);
address155_26.SetBase("10.1.10.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces155_26 = address155_26.Assign(devices155_26);
address155_27.SetBase("10.1.11.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces155_27 = address155_27.Assign(devices155_27);
address155_28.SetBase("10.1.12.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces155_28 = address155_28.Assign(devices155_28);
address155_29.SetBase("10.1.13.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces155_29 = address155_29.Assign(devices155_29);
address155_30.SetBase("10.1.14.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces155_30 = address155_30.Assign(devices155_30);
address155_93.SetBase("10.1.15.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces155_93 = address155_93.Assign(devices155_93);
address155_124.SetBase("10.1.16.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces155_124 = address155_124.Assign(devices155_124);
address156_1.SetBase("10.1.17.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces156_1 = address156_1.Assign(devices156_1);
address156_94.SetBase("10.1.18.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces156_94 = address156_94.Assign(devices156_94);
address156_125.SetBase("10.1.19.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces156_125 = address156_125.Assign(devices156_125);
address1_161.SetBase("10.1.20.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces1_161 = address1_161.Assign(devices1_161);
address1_32.SetBase("10.1.21.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces1_32 = address1_32.Assign(devices1_32);
address1_63.SetBase("10.1.22.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces1_63 = address1_63.Assign(devices1_63);
address157_2.SetBase("10.1.23.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces157_2 = address157_2.Assign(devices157_2);
address157_95.SetBase("10.1.24.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces157_95 = address157_95.Assign(devices157_95);
address157_126.SetBase("10.1.25.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces157_126 = address157_126.Assign(devices157_126);
address2_162.SetBase("10.1.26.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces2_162 = address2_162.Assign(devices2_162);
address2_33.SetBase("10.1.27.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces2_33 = address2_33.Assign(devices2_33);
address2_64.SetBase("10.1.28.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces2_64 = address2_64.Assign(devices2_64);
address158_3.SetBase("10.1.29.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces158_3 = address158_3.Assign(devices158_3);
address158_96.SetBase("10.1.30.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces158_96 = address158_96.Assign(devices158_96);
address158_127.SetBase("10.1.31.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces158_127 = address158_127.Assign(devices158_127);
address3_163.SetBase("10.1.32.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces3_163 = address3_163.Assign(devices3_163);
address3_34.SetBase("10.1.33.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces3_34 = address3_34.Assign(devices3_34);
address3_65.SetBase("10.1.34.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces3_65 = address3_65.Assign(devices3_65);
address159_4.SetBase("10.1.35.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces159_4 = address159_4.Assign(devices159_4);
address159_97.SetBase("10.1.36.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces159_97 = address159_97.Assign(devices159_97);
address159_128.SetBase("10.1.37.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces159_128 = address159_128.Assign(devices159_128);
address4_164.SetBase("10.1.38.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces4_164 = address4_164.Assign(devices4_164);
address4_35.SetBase("10.1.39.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces4_35 = address4_35.Assign(devices4_35);
address4_66.SetBase("10.1.40.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces4_66 = address4_66.Assign(devices4_66);
address160_5.SetBase("10.1.41.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces160_5 = address160_5.Assign(devices160_5);
address160_98.SetBase("10.1.42.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces160_98 = address160_98.Assign(devices160_98);
address160_129.SetBase("10.1.43.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces160_129 = address160_129.Assign(devices160_129);
address5_165.SetBase("10.1.44.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces5_165 = address5_165.Assign(devices5_165);
address5_36.SetBase("10.1.45.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces5_36 = address5_36.Assign(devices5_36);
address5_67.SetBase("10.1.46.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces5_67 = address5_67.Assign(devices5_67);
address26_181.SetBase("10.1.47.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces26_181 = address26_181.Assign(devices26_181);
address26_57.SetBase("10.1.48.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces26_57 = address26_57.Assign(devices26_57);
address26_88.SetBase("10.1.49.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces26_88 = address26_88.Assign(devices26_88);
address181_21.SetBase("10.1.50.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces181_21 = address181_21.Assign(devices181_21);
address181_22.SetBase("10.1.51.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces181_22 = address181_22.Assign(devices181_22);
address181_23.SetBase("10.1.52.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces181_23 = address181_23.Assign(devices181_23);
address181_24.SetBase("10.1.53.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces181_24 = address181_24.Assign(devices181_24);
address181_25.SetBase("10.1.54.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces181_25 = address181_25.Assign(devices181_25);
address181_119.SetBase("10.1.55.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces181_119 = address181_119.Assign(devices181_119);
address181_150.SetBase("10.1.56.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces181_150 = address181_150.Assign(devices181_150);
address27_182.SetBase("10.1.57.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces27_182 = address27_182.Assign(devices27_182);
address27_58.SetBase("10.1.58.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces27_58 = address27_58.Assign(devices27_58);
address27_89.SetBase("10.1.59.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces27_89 = address27_89.Assign(devices27_89);
address182_120.SetBase("10.1.60.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces182_120 = address182_120.Assign(devices182_120);
address182_151.SetBase("10.1.61.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces182_151 = address182_151.Assign(devices182_151);
address28_183.SetBase("10.1.62.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces28_183 = address28_183.Assign(devices28_183);
address28_59.SetBase("10.1.63.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces28_59 = address28_59.Assign(devices28_59);
address28_90.SetBase("10.1.64.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces28_90 = address28_90.Assign(devices28_90);
address183_121.SetBase("10.1.65.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces183_121 = address183_121.Assign(devices183_121);
address183_152.SetBase("10.1.66.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces183_152 = address183_152.Assign(devices183_152);
address29_184.SetBase("10.1.67.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces29_184 = address29_184.Assign(devices29_184);
address29_60.SetBase("10.1.68.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces29_60 = address29_60.Assign(devices29_60);
address29_91.SetBase("10.1.69.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces29_91 = address29_91.Assign(devices29_91);
address184_122.SetBase("10.1.70.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces184_122 = address184_122.Assign(devices184_122);
address184_153.SetBase("10.1.71.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces184_153 = address184_153.Assign(devices184_153);
address30_185.SetBase("10.1.72.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces30_185 = address30_185.Assign(devices30_185);
address30_61.SetBase("10.1.73.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces30_61 = address30_61.Assign(devices30_61);
address30_92.SetBase("10.1.74.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces30_92 = address30_92.Assign(devices30_92);
address185_123.SetBase("10.1.75.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces185_123 = address185_123.Assign(devices185_123);
address185_154.SetBase("10.1.76.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces185_154 = address185_154.Assign(devices185_154);
address161_6.SetBase("10.1.77.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces161_6 = address161_6.Assign(devices161_6);
address161_99.SetBase("10.1.78.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces161_99 = address161_99.Assign(devices161_99);
address161_130.SetBase("10.1.79.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces161_130 = address161_130.Assign(devices161_130);
address6_166.SetBase("10.1.80.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces6_166 = address6_166.Assign(devices6_166);
address6_37.SetBase("10.1.81.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces6_37 = address6_37.Assign(devices6_37);
address6_68.SetBase("10.1.82.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces6_68 = address6_68.Assign(devices6_68);
address162_7.SetBase("10.1.83.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces162_7 = address162_7.Assign(devices162_7);
address162_100.SetBase("10.1.84.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces162_100 = address162_100.Assign(devices162_100);
address162_131.SetBase("10.1.85.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces162_131 = address162_131.Assign(devices162_131);
address7_167.SetBase("10.1.86.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces7_167 = address7_167.Assign(devices7_167);
address7_38.SetBase("10.1.87.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces7_38 = address7_38.Assign(devices7_38);
address7_69.SetBase("10.1.88.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces7_69 = address7_69.Assign(devices7_69);
address163_8.SetBase("10.1.89.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces163_8 = address163_8.Assign(devices163_8);
address163_101.SetBase("10.1.90.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces163_101 = address163_101.Assign(devices163_101);
address163_132.SetBase("10.1.91.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces163_132 = address163_132.Assign(devices163_132);
address8_168.SetBase("10.1.92.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces8_168 = address8_168.Assign(devices8_168);
address8_39.SetBase("10.1.93.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces8_39 = address8_39.Assign(devices8_39);
address8_70.SetBase("10.1.94.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces8_70 = address8_70.Assign(devices8_70);
address164_9.SetBase("10.1.95.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces164_9 = address164_9.Assign(devices164_9);
address164_102.SetBase("10.1.96.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces164_102 = address164_102.Assign(devices164_102);
address164_133.SetBase("10.1.97.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces164_133 = address164_133.Assign(devices164_133);
address9_169.SetBase("10.1.98.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces9_169 = address9_169.Assign(devices9_169);
address9_40.SetBase("10.1.99.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces9_40 = address9_40.Assign(devices9_40);
address9_71.SetBase("10.1.100.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces9_71 = address9_71.Assign(devices9_71);
address165_10.SetBase("10.1.101.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces165_10 = address165_10.Assign(devices165_10);
address165_103.SetBase("10.1.102.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces165_103 = address165_103.Assign(devices165_103);
address165_134.SetBase("10.1.103.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces165_134 = address165_134.Assign(devices165_134);
address10_170.SetBase("10.1.104.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces10_170 = address10_170.Assign(devices10_170);
address10_41.SetBase("10.1.105.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces10_41 = address10_41.Assign(devices10_41);
address10_72.SetBase("10.1.106.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces10_72 = address10_72.Assign(devices10_72);
address21_176.SetBase("10.1.107.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_176 = address21_176.Assign(devices21_176);
address21_52.SetBase("10.1.108.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_52 = address21_52.Assign(devices21_52);
address21_83.SetBase("10.1.109.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces21_83 = address21_83.Assign(devices21_83);
address176_16.SetBase("10.1.110.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces176_16 = address176_16.Assign(devices176_16);
address176_17.SetBase("10.1.111.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces176_17 = address176_17.Assign(devices176_17);
address176_18.SetBase("10.1.112.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces176_18 = address176_18.Assign(devices176_18);
address176_19.SetBase("10.1.113.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces176_19 = address176_19.Assign(devices176_19);
address176_20.SetBase("10.1.114.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces176_20 = address176_20.Assign(devices176_20);
address176_114.SetBase("10.1.115.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces176_114 = address176_114.Assign(devices176_114);
address176_145.SetBase("10.1.116.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces176_145 = address176_145.Assign(devices176_145);
address22_177.SetBase("10.1.117.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces22_177 = address22_177.Assign(devices22_177);
address22_53.SetBase("10.1.118.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces22_53 = address22_53.Assign(devices22_53);
address22_84.SetBase("10.1.119.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces22_84 = address22_84.Assign(devices22_84);
address177_115.SetBase("10.1.120.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces177_115 = address177_115.Assign(devices177_115);
address177_146.SetBase("10.1.121.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces177_146 = address177_146.Assign(devices177_146);
address23_178.SetBase("10.1.122.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces23_178 = address23_178.Assign(devices23_178);
address23_54.SetBase("10.1.123.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces23_54 = address23_54.Assign(devices23_54);
address23_85.SetBase("10.1.124.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces23_85 = address23_85.Assign(devices23_85);
address178_116.SetBase("10.1.125.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces178_116 = address178_116.Assign(devices178_116);
address178_147.SetBase("10.1.126.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces178_147 = address178_147.Assign(devices178_147);
address24_179.SetBase("10.1.127.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces24_179 = address24_179.Assign(devices24_179);
address24_55.SetBase("10.1.128.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces24_55 = address24_55.Assign(devices24_55);
address24_86.SetBase("10.1.129.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces24_86 = address24_86.Assign(devices24_86);
address179_117.SetBase("10.1.130.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces179_117 = address179_117.Assign(devices179_117);
address179_148.SetBase("10.1.131.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces179_148 = address179_148.Assign(devices179_148);
address25_180.SetBase("10.1.132.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces25_180 = address25_180.Assign(devices25_180);
address25_56.SetBase("10.1.133.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces25_56 = address25_56.Assign(devices25_56);
address25_87.SetBase("10.1.134.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces25_87 = address25_87.Assign(devices25_87);
address180_118.SetBase("10.1.135.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces180_118 = address180_118.Assign(devices180_118);
address180_149.SetBase("10.1.136.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces180_149 = address180_149.Assign(devices180_149);
address166_11.SetBase("10.1.137.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces166_11 = address166_11.Assign(devices166_11);
address166_104.SetBase("10.1.138.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces166_104 = address166_104.Assign(devices166_104);
address166_135.SetBase("10.1.139.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces166_135 = address166_135.Assign(devices166_135);
address11_42.SetBase("10.1.140.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces11_42 = address11_42.Assign(devices11_42);
address11_73.SetBase("10.1.141.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces11_73 = address11_73.Assign(devices11_73);
address167_12.SetBase("10.1.142.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces167_12 = address167_12.Assign(devices167_12);
address167_105.SetBase("10.1.143.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces167_105 = address167_105.Assign(devices167_105);
address167_136.SetBase("10.1.144.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces167_136 = address167_136.Assign(devices167_136);
address12_43.SetBase("10.1.145.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces12_43 = address12_43.Assign(devices12_43);
address12_74.SetBase("10.1.146.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces12_74 = address12_74.Assign(devices12_74);
address168_13.SetBase("10.1.147.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces168_13 = address168_13.Assign(devices168_13);
address168_106.SetBase("10.1.148.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces168_106 = address168_106.Assign(devices168_106);
address168_137.SetBase("10.1.149.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces168_137 = address168_137.Assign(devices168_137);
address13_44.SetBase("10.1.150.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces13_44 = address13_44.Assign(devices13_44);
address13_75.SetBase("10.1.151.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces13_75 = address13_75.Assign(devices13_75);
address169_14.SetBase("10.1.152.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces169_14 = address169_14.Assign(devices169_14);
address169_107.SetBase("10.1.153.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces169_107 = address169_107.Assign(devices169_107);
address169_138.SetBase("10.1.154.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces169_138 = address169_138.Assign(devices169_138);
address14_45.SetBase("10.1.155.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces14_45 = address14_45.Assign(devices14_45);
address14_76.SetBase("10.1.156.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces14_76 = address14_76.Assign(devices14_76);
address170_15.SetBase("10.1.157.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces170_15 = address170_15.Assign(devices170_15);
address170_108.SetBase("10.1.158.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces170_108 = address170_108.Assign(devices170_108);
address170_139.SetBase("10.1.159.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces170_139 = address170_139.Assign(devices170_139);
address15_46.SetBase("10.1.160.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces15_46 = address15_46.Assign(devices15_46);
address15_77.SetBase("10.1.161.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces15_77 = address15_77.Assign(devices15_77);
address16_171.SetBase("10.1.162.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces16_171 = address16_171.Assign(devices16_171);
address16_47.SetBase("10.1.163.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces16_47 = address16_47.Assign(devices16_47);
address16_78.SetBase("10.1.164.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces16_78 = address16_78.Assign(devices16_78);
address171_109.SetBase("10.1.165.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces171_109 = address171_109.Assign(devices171_109);
address171_140.SetBase("10.1.166.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces171_140 = address171_140.Assign(devices171_140);
address17_172.SetBase("10.1.167.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces17_172 = address17_172.Assign(devices17_172);
address17_48.SetBase("10.1.168.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces17_48 = address17_48.Assign(devices17_48);
address17_79.SetBase("10.1.169.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces17_79 = address17_79.Assign(devices17_79);
address172_110.SetBase("10.1.170.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces172_110 = address172_110.Assign(devices172_110);
address172_141.SetBase("10.1.171.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces172_141 = address172_141.Assign(devices172_141);
address18_173.SetBase("10.1.172.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces18_173 = address18_173.Assign(devices18_173);
address18_49.SetBase("10.1.173.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces18_49 = address18_49.Assign(devices18_49);
address18_80.SetBase("10.1.174.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces18_80 = address18_80.Assign(devices18_80);
address173_111.SetBase("10.1.175.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces173_111 = address173_111.Assign(devices173_111);
address173_142.SetBase("10.1.176.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces173_142 = address173_142.Assign(devices173_142);
address19_174.SetBase("10.1.177.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces19_174 = address19_174.Assign(devices19_174);
address19_50.SetBase("10.1.178.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces19_50 = address19_50.Assign(devices19_50);
address19_81.SetBase("10.1.179.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces19_81 = address19_81.Assign(devices19_81);
address174_112.SetBase("10.1.180.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces174_112 = address174_112.Assign(devices174_112);
address174_143.SetBase("10.1.181.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces174_143 = address174_143.Assign(devices174_143);
address20_175.SetBase("10.1.182.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces20_175 = address20_175.Assign(devices20_175);
address20_51.SetBase("10.1.183.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces20_51 = address20_51.Assign(devices20_51);
address20_82.SetBase("10.1.184.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces20_82 = address20_82.Assign(devices20_82);
address175_113.SetBase("10.1.185.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces175_113 = address175_113.Assign(devices175_113);
address175_144.SetBase("10.1.186.0", "255.255.255.0"); Ipv4InterfaceContainer interfaces175_144 = address175_144.Assign(devices175_144);



  // 启用流监测器，使用 FlowMonitorHelper 启用流监测器，并将其安装在所有的设备上
  FlowMonitorHelper flowmon;
  Ptr<FlowMonitor> monitor = flowmon.InstallAll();
  
  // Create a packet sink on the star "hub" to receive these packets
    uint16_t port = 50000;//端口号50000
    ApplicationContainer sinkApp;//这一句是定义服务器的
    Address sinkLocalAddress (InetSocketAddress (Ipv4Address::GetAny (), port));
    PacketSinkHelper sinkHelper ("ns3::TcpSocketFactory", sinkLocalAddress);//接收和消耗生成到IP地址和端口的流量
    //sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[0].Get(0)));//0为服务器结点
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[56].Get(1)));//58为服务器结点
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[77].Get(1)));//130为服务器结点
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[5].Get(1)));//160为服务器结点
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[49].Get(1)));//22为服务器结点
    sinkApp.Add(sinkHelper.Install(nodeAdjacencyList[155].Get(1)));//15为服务器结点
    

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
    //2----0
    //AddressValue remoteAddress (InetSocketAddress (interfaces0_155.GetAddress(0), port));
    //clientHelper.SetAttribute("Remote",remoteAddress);    
    //clientApps.Add(clientHelper.Install(nodeAdjacencyList[24].Get(0)));
    
    //0----58
    AddressValue remoteAddress (InetSocketAddress (interfaces27_58.GetAddress(1), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[0].Get(0)));
    
    //0----130
    remoteAddress=AddressValue(InetSocketAddress (interfaces161_130.GetAddress (1), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[0].Get(0)));
    
    //36----160
    remoteAddress=AddressValue(InetSocketAddress (interfaces0_160.GetAddress (1), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[43].Get(1)));
    
    //26----22
    remoteAddress=AddressValue(InetSocketAddress (interfaces181_22.GetAddress (1), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[8].Get(1)));
    
    //41----15
    remoteAddress=AddressValue(InetSocketAddress (interfaces170_15.GetAddress (1), port));
    clientHelper.SetAttribute("Remote",remoteAddress);    
    clientApps.Add(clientHelper.Install(nodeAdjacencyList[103].Get(1)));
    
    

    
    clientApps.Start(Seconds(1.0));
    clientApps.Stop (Seconds (61.0));
 
  // 启用 OSPF
  Ipv4GlobalRoutingHelper::PopulateRoutingTables();
  
  
  
  
  // 配置输出流
  AsciiTraceHelper throughputAscii, lossAscii, delayAscii;
  Ptr<OutputStreamWrapper> throughputStream = throughputAscii.CreateFileStream("throughput-D52-TREE.txt");
  Ptr<OutputStreamWrapper> lossStream = lossAscii.CreateFileStream("loss-D52-TREE.txt");
  Ptr<OutputStreamWrapper> delayStream = delayAscii.CreateFileStream("delay-D52-TREE.txt");
  
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
