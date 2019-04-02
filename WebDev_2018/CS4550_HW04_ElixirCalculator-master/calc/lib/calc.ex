defmodule Calc do
  @moduledoc """
  Documentation for Calc.
  """

  @doc """
  Hello world. This is my calculator!
  """

  def eval(expression) do
    Lex.lex(expression)
    |> Parse.parse()
    |> Evaluate.evaluate()
  end
  ## The method of lexing -> parsing -> evaluating came from this super helpful repo
  ## https://github.com/fabrik42/writing_an_interpreter_in_elixir/tree/master/lib/monkey

  def main do
    answer = IO.gets("Please enter an arithmetic expression: ") 
    |> Calc.eval()
    IO.puts("#{answer}")
    main()
  end
end
