module input_array(a, b);
  input [3:0] a; // [MSB : LSB]
  output b;
  assign b = a[3] & a[2] & a[1] & a[0];
endmodule
