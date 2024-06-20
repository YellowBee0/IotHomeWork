# 实验四基于System-Verilog的FPGA设计与仿真
[TOC]
## 简介
### 什么是system Verilog：
SystemVerilog是IEEE官方语言标准的较新名称，它取代了原来的Verilog名称。Verilog HDL语言最初是于1 9 8 3年由Gateway Design Automation 公司为其模拟器产品开发的硬件建模语言。那时它只是一种专用语言。专有的Verilog HDL于1989年逐渐向公众开放，并于1995年由IEEE标准化为国际标准，即IEEE Std 1364-1995TM（通常称为"Verilog-95"）。IEEE于2001年将Verilog标准更新为1364-2001 TM标准，称为"Verilog-2001"。Verilog名称下的最后一个官方版本是IEEE Std 1364-2005TM。同年，IEEE发布了一系列对Verilog HDL的增强功能。这些增强功能最初以不同的标准编号和名称记录，即IEEE Std 1800-2005TM SystemVerilog标准。2009年，IEEE终止了IEEE-1364标准，并将Verilog-2005合并到SystemVerilog标准中，标准编号为IEEE Std 1800-2009TM标准。2012年增加了其他设计和验证增强功能，如IEEE标准1800-2012TM标准，称为SystemVerilog-2012。在撰写本书时，IEEE已接近完成拟定的IEEE标准1800-2017TM或SystemVerilog-2017。本版本仅修正了2012版标准中的勘误表，并增加了对语言语法和语义规则的澄清。
## System-Verilog改写Verilog代码
### 流水灯
流水灯Verilog代码
```v
    module led_chaser(
        input wire clk,
        input wire rst,
        output reg [7:0] leds
    );
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            leds <= 8'b00000001;
        end else begin
            leds <= {leds[6:0], leds[7]};
        end
    end

    endmodule
```
System Verilog改写：
```v
    module led_chaser(
        input logic clk,
        input logic rst,
        output logic [7:0] leds
    );

    always_ff @(posedge clk or posedge rst) begin
        if (rst) begin
            leds <= 8'b00000001;
        end else begin
            leds <= {leds[6:0], leds[7]};
        end
    end

    endmodule
```
Testbench
```v
module tb_led_chaser;
    logic clk;
    logic rst;
    logic [7:0] leds;

    led_chaser uut (
        .clk(clk),
        .rst(rst),
        .leds(leds)
    );

    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end

    initial begin
        rst = 1;
        #10;
        rst = 0;
        #100;
        $stop;
    end
endmodule
```
### VGA
VGA显示Verilog代码：
```v
    module vga_controller (
        input wire clk,
        input wire rst,
        output wire hsync,
        output wire vsync,
        output wire [3:0] r,
        output wire [3:0] g,
        output wire [3:0] b
    );

    // Implementation of VGA controller here

    endmodule
```
System Verilog代码改写：
```v
    module vga_controller (
        input logic clk,
        input logic rst,
        output logic hsync,
        output logic vsync,
        output logic [3:0] r,
        output logic [3:0] g,
        output logic [3:0] b
    );

    // Implementation of VGA controller here

    endmodule
```
Testbench
```v
    module tb_vga_controller;
        logic clk;
        logic rst;
        logic hsync, vsync;
        logic [3:0] r, g, b;

        vga_controller uut (
            .clk(clk),
            .rst(rst),
            .hsync(hsync),
            .vsync(vsync),
            .r(r),
            .g(g),
            .b(b)
        );

        initial begin
            clk = 0;
            forever #5 clk = ~clk;
        end

        initial begin
            rst = 1;
            #10;
            rst = 0;
            #1000;
            $stop;
        end
    endmodule
```
### 超声波测距
超声波测距Verilog代码：
```v
    module ultrasonic_distance (
        input wire clk,
        input wire rst,
        input wire echo,
        output wire trig,
        output wire [15:0] distance
    );

    // Implementation of ultrasonic distance measurement here

    endmodule
```
System Verilog代码改写：
```v
    module ultrasonic_distance (
        input logic clk,
        input logic rst,
        input logic echo,
        output logic trig,
        output logic [15:0] distance
    );

    // Implementation of ultrasonic distance measurement here

    endmodule
```
Testbench：
```v
    module tb_ultrasonic_distance;
        logic clk;
        logic rst;
        logic echo;
        logic trig;
        logic [15:0] distance;

        ultrasonic_distance uut (
            .clk(clk),
            .rst(rst),
            .echo(echo),
            .trig(trig),
            .distance(distance)
        );

        initial begin
            clk = 0;
            forever #5 clk = ~clk;
        end

        initial begin
            rst = 1;
            #10;
            rst = 0;
            #2000;
            $stop;
        end
    endmodule
```
## 实验总结：
SystemVerilog是Verilog的扩展，它提供了更多的功能和特性，比如更强大的数据类型、对象编程、接口和多线程等。改用SystemVerilog可以提高代码的可维护性、可扩展性和可重用性，同时还能够更好地满足复杂设计的需求。