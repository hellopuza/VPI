module my_module1 (
    input x,
    output y);
endmodule

module my_module2;

wire x;
wire y;

my_module1 m1_a(x, y);
my_module1 m1_b(x, y);

endmodule

module my_module3(
    output y);
endmodule

module top;

wire x;
wire y;

my_module1 m1_a(x, y);
my_module1 m1_b(y, x);

my_module2 m2_a();
my_module2 m2_b();
my_module2 m2_c();

initial
begin
    $display("hello");
    $finish;
end

endmodule
