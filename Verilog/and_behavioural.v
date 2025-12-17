module and_behavioural (
    a,
    b,
    z
);
  input a, b;
  output z;
  reg z;
  always @(a, b) begin
    // This part of code only runs when the sensitivity list i.e (a, b) changes
    z = a & b;
  end
endmodule
