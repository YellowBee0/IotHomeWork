[TOC]
# HLS入门
**[参考网址](https://blog.csdn.net/m0_58807717/article/details/130953226)**
## 简介
### HLS
HLS（High-Level Synthesis）是一种硬件描述语言（HDL）的编程技术，它可以将高级语言代码（如C/C++）转换成硬件描述语言（如VHDL或Verilog）。
### HLS与VHDL/Verilog编程技术关系
HLS与VHDL/Verilog编程技术有很大的关系，因为它们都是用于编写硬件描述语言的工具。然而，HLS与传统的VHDL/Verilog编程技术不同之处在于，HLS更加高级，可以让开发人员使用更加直观和易于理解的语言来描述硬件功能，从而提高开发效率和代码质量。HLS的流程与传统的VHDL/Verilog编程技术也不同，它更加依赖于自动化工具来完成硬件代码的生成和优化。
## Vivado HLS LED 仿真
### 创建工程
打开Vivado HLS，点击Create New Project
![alt](https://img-blog.csdnimg.cn/direct/ec8c1d19586a4cd7b4e0251ea81d6218.png)
选择器件
![alt](https://img-blog.csdnimg.cn/direct/f33146bdf15649fcb91e451aabad4ff0.png)
### 添加文件
创建新文件led.h和led.cpp输入以下代码
led.h
```cpp
#ifndef _SHIFT_LED_H_
#define _SHIFT_LED_H_

#include "ap_int.h"
#define CNT_MAX 100000000
//#define CNT_MAX 100,100M时钟频率下计数一秒钟所需要的计数次数
#define FLASH_FLAG CNT_MAX-2
// typedef int led_t;
// typedef int cnt_t;
typedef ap_int<1> led_t;
typedef ap_int<32> cnt_t;
void flash_led(led_t *led_o , led_t led_i);

#endif
```
led.cpp

```cpp
#include "led.h"

void flash_led(led_t *led_o , led_t led_i){
#pragma HLS INTERFACE ap_vld port=led_i
#pragma HLS INTERFACE ap_ovld port=led_o
	cnt_t i;
	for(i=0;i<CNT_MAX;i++){
		if(i==FLASH_FLAG){
			*led_o = ~led_i;
		}
	}
}
```
仿真测试文件添加
右键Test Bench，选择New File
test_led.cpp
```cpp
#include "led.h"
#include <stdio.h>

int main(){

	led_t led_i=0x01;
	led_t led_o;
	const int SHIFT_TIME = 4;
	int i;
	for(i=0;i<SHIFT_TIME;i++){
		flash_led(&led_o , led_i);
		led_i = led_o;
		printf("shift_out is %d \n",(int)(led_o&0x01));
	}
}
```
### 仿真综合
![alt](https://img-blog.csdnimg.cn/direct/a9a1c97753d244bbb89f32600bed9b43.png)
![alt](https://img-blog.csdnimg.cn/direct/43ef2b5393764798b221c5aab6e8d153.png)
输出01交替，表示仿真结果正确
![alt](https://img-blog.csdnimg.cn/direct/6aea891068a14216800c82badd021250.png)
![alt](https://img-blog.csdnimg.cn/direct/75d383727ed24dd197297c9f33a17773.png)
### 创建Vivado工程
选择Greate Project
![alt](https://img-blog.csdnimg.cn/direct/4978f744a6af455c8e57e6b993757e33.png)
点Next
![alt](https://img-blog.csdnimg.cn/direct/12c674b1d87045958d4a3fde14f07e32.png)
![alt](https://img-blog.csdnimg.cn/direct/e7b18bdef7964e1e99bb2dfc9dc267b7.png)
直接Next，选择器件
![alt](https://img-blog.csdnimg.cn/direct/ef31d880595046dabfe6aa34a5f6c33c.png)
![alt](https://img-blog.csdnimg.cn/direct/ed6c975570a448e29406eae5cf3a01a5.png)
### 导入HLS生成的IP核
选择Solution->Export RTL
![alt](https://img-blog.csdnimg.cn/direct/4a88e52875df417fad9d4cdf097b1961.png)
![alt](https://img-blog.csdnimg.cn/direct/6b19363c7766497792b260faf9454b61.png)
导入
点击setting
![alt](https://img-blog.csdnimg.cn/direct/fefb7de4df714e35be6da1ec02b37a87.png)
![alt](https://img-blog.csdnimg.cn/direct/68d96c7967154601a7c0cb62bba93f71.png)
检验是否导入成功
![alt](https://img-blog.csdnimg.cn/direct/ba58354048684949b475beaa9305ba03.png)
![alt](https://img-blog.csdnimg.cn/direct/bc877888325d4d50a0a9ed51ca208115.png)
![alt](https://img-blog.csdnimg.cn/direct/79fdc0878c0a48d9ac7ac777b873f02f.png)
### 添加实验代码
![alt](https://img-blog.csdnimg.cn/direct/78678159de934ff387f7f89b428defa5.png)
![alt](https://img-blog.csdnimg.cn/direct/6057b06dc26245888feb291a367a7dfc.png)
输入以下代码
```cpp
`timescale 1ns / 1ps
module flash_led(
input wire clk ,
input wire rst_n ,
output wire led_o
);
 
wire rst ;//同步复位
wire ap_ready ;//当前可以接收下一次数据
reg ap_start ;//IP 开始工作
reg led_i_vld ;//输入数据有效
wire led_o_vld ;
reg led_i ;//输入的 led 信号
wire led_o_r ;
wire ap_done ;
wire ap_idle ;
reg [1:0] delay_cnt ;
assign rst = ~rst_n ;
assign led_o = led_o_r ;
 
//----------------delay_cnt------------------
always @(posedge clk) begin
if (rst==1'b1) begin
delay_cnt <= 'd0;
end
else if(delay_cnt[1]==1'b0) begin
delay_cnt <= delay_cnt + 1'b1;
end
end
 
//----------------ap_start------------------
always @(posedge clk) begin
if (rst==1'b1) begin
ap_start <= 1'b0;
end
else if(delay_cnt[1]==1'b1)begin
ap_start <= 1'b1;
end
end
 
//----------------led_i_vld------------------
always @(posedge clk) begin
if (rst==1'b1) begin
led_i_vld <= 1'b0;
end
else if(delay_cnt[1]==1'b1)begin
led_i_vld <= 1'b1;
end
end
 
//----------------ap_i------------------
always @(posedge clk) begin
if (rst==1'b1) begin
led_i <= 1'b0;
end
else if(led_o_vld==1'b1)begin
led_i <= led_o_r ;
end
end
 
 
flash_led_0 inst_flash_led (
.led_o_V_ap_vld(led_o_vld), // output wire led_o_V_ap_vld
.led_i_V_ap_vld(led_i_vld), // input wire led_i_V_ap_vld
.ap_clk(clk), // input wire ap_clk
.ap_rst(rst), // input wire ap_rst
.ap_start(ap_start), // input wire ap_start
.ap_done(ap_done), // output wire ap_done
.ap_idle(ap_idle), // output wire ap_idle
.ap_ready(ap_ready), // output wire ap_ready
.led_o_V(led_o_r), // output wire [0 : 0] led_o_V
.led_i_V(led_i) // input wire [0 : 0] led_i_V
); 
endmodule

```
创建约束文件
![在这里插入图片描述](https://img-blog.csdnimg.cn/direct/a26c0b03604a4c049558ea6188fe8351.png)
![alt](https://img-blog.csdnimg.cn/direct/d784c1a8593242259e49f9a932c18509.png)
输入以下代码
```cpp
##############LED define################## 
set_property PACKAGE_PIN P15 [get_ports {led_o}] 
set_property IOSTANDARD LVCMOS33 [get_ports {led_o}]

##############Reset define################## 
set_property PACKAGE_PIN P16 [get_ports {rst_n}] 
set_property IOSTANDARD LVCMOS33 [get_ports {rst_n}]

##############50M CLK define################## 
create_clock -period 20.000 -name clk -waveform {0.000 10.000} [get_ports clk]
set_property PACKAGE_PIN N18 [get_ports {clk}] 
set_property IOSTANDARD LVCMOS33 [get_ports {clk}]

```