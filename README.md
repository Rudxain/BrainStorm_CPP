# BSO_CPP
Brain Storm Optimazation (BSO) core in cpp.  
Based on the project 'Analysis of Risk Management for the Coal Mine Operations'.  
Translated from the matlab code of this paper.  
Also provide a demo of K_means algorithm.  

说明：

经过测试，使用评价函数 z = sum（ x(i)^2 + 10 - 10*cos(2*pi*x(i)))，fitness效果与matlab基本一致。
经过10次重复实验，（参数在源码中）
	CPP： fitness 最小值为 2.287，平均值 6.4
	matlab fitness 最小值1.988， 平均值5.78

代码逻辑已注释，方便阅读。
重写Function：：fun（）以使用新的评价函数
主函数为bsocore.cpp

存在问题：
	运行速度较慢，提高运行速度可能要改变现有架构。
	



