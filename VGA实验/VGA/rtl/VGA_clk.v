module vga_colorbar_top(
       input    wire                sys_clk ,
       input    wire                sys_rst,
       
       output   wire                vga_hs,         // 输出到vga接口的行同步信号
       output   wire                vga_vs,         // 输出到vga接口的场同步信号
       output   wire    [15:0]  vga_rgb         // 输出到vga接口的像素数据
);
// 25MHZ时钟信号定义
wire clk_w ;
pll_clk pll_25MHz(
    .inclk0 (sys_clk), // （输入）50MHZ基准时钟
    .c3     (clk_w) // （输出）25MHZ分频时钟
 );
endmodule