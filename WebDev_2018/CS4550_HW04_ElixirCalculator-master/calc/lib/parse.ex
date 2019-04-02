defmodule Parse do

    def parse(tokens) do
      parse(tokens, [], [])
    end
  
    defp parse(_tokens = [current | rest], operators, outputs) do
        case current.type do
            :int -> parse_int(current, rest, operators, outputs)
            :op -> parse_operator(current, rest, operators, outputs)
            :left -> parse_left(current, rest, operators, outputs)
            :right -> parse_right(current, rest, operators, outputs)
            :sp -> parse(rest, operators, outputs)
            :illegal -> error()
            :eof -> parse(rest, operators, outputs)
        end
    end
  
    defp parse(_tokens = [], operators, outputs) do
      Enum.reverse(outputs)++operators
    end
  
    defp parse_int(num, tokens, operators, outputs) do
      outputs = [num | outputs]
      parse(tokens, operators, outputs)
    end
  
    @orderofops %{
      "+"=> 2, 
      "-"=> 2, 
      "/"=> 3, 
      "*"=> 3
    }
  
    defp parse_operator(current, tokens, operators, outputs) do
      {args, operators} = Enum.split_while(operators, fn(prec) -> prec.val != "(" && @orderofops[prec.val] >= @orderofops[current.val] end)
      outputs = Enum.reverse(args)++outputs
      operators = [current | operators]
      parse(tokens, operators, outputs)
    end
  
    defp parse_left(current, tokens, operators, outputs) do
        operators = [current | operators]
        parse(tokens, operators, outputs)
    end
  
    defp parse_right(_right, tokens, operators, outputs) do
        {args, operators} = Enum.split_while(operators, fn(x) -> x.val != "(" end)
        outputs = Enum.reverse(args)++outputs
        [_paren | operators] = operators
        parse(tokens, operators, outputs)
    end

    def error() do
        raise "Error while parsing"
    end
  
  end