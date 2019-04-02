defmodule CalcTest do
  use ExUnit.Case
  doctest Calc

  test "do multiplication" do
    assert Calc.eval("2*2") == 4
  end

  test "do divsion" do
    assert Calc.eval("4 / 2") == 2
  end

  test "do addition, subtraction, order of ops" do
    assert Calc.eval("4+ (3-1)*2") == 8 
  end
end
