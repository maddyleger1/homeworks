defmodule Lex do

  defp next(_chars = [current | rest], tokens) do
    token =
      case current do
        "(" -> Tokens.match_token(type: :left, val: current)
        ")" -> Tokens.match_token(type: :right, val: current)
        "+" -> Tokens.match_token(type: :op, val: current)
        "-" -> Tokens.match_token(type: :op, val: current)
        "*" -> Tokens.match_token(type: :op, val: current)
        "/" -> Tokens.match_token(type: :op, val: current)
        _ -> error()
      end
    lex(rest, [token | tokens])
  end
    
  def lex(expression) do
    String.replace(expression, ["\n"], "") 
    |> String.split("", trim: true)
    |> lex([])
  end
    
  def lex(_chars = [], tokens) do
    continue? = Enum.reduce_while(tokens, 0, fn(i, max) -> 
      if i.type != max, 
        do: {:cont, i.type}, 
        else: {:halt, false} end)

    if !continue? do
      error()
    end
    Enum.reverse([Tokens.match_token(type: :eof, val: "") | tokens])
  end
    
  def lex(chars = [current | rest], tokens) do
    cond do
      isInt?(current) -> num(chars, tokens)
      current == " " -> lex(rest, tokens)
      true -> next(chars, tokens)
    end
  end

  defp isInt?(token) do
    "0" <= token && token <= "9"
  end

  defp num(current, tokens) do
    {number, rest} = Enum.split_while(current, fn(token) -> isInt?(token) end)
    number = Enum.join(number)
    token = Tokens.match_token(type: :int, val: number)
    lex(rest, [token | tokens])
  end

  defp error() do
    raise "Lexer error"
  end

end