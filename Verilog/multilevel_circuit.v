/*
module multilevel_circuit (
    a,
    b,
    c,
    e
);
  input a, b, c;
  output e;
  wire d;
  assign d = a & b;
  assign e = d | c;
endmodule
*/

module multilevel_circuit (
    a,
    b,
    c,
    e
);
  input a, b, c;
  output e;
  reg t1, e;
  always @(a, b, c) begin
      t1 = a & b;
      e = t1 & c;
  end
endmodule
