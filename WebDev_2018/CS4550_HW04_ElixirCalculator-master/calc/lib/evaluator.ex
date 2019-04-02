defmodule Evaluate do
	
	def evaluate(parsed) do
		evaluate(parsed, [])
	end

	defp evaluate(_tokens=[token | rest], stack) do
		case token.type do
			:op -> eval_op(token, rest, stack)
			:int -> eval_int(token, rest, stack)
  	    end
	end

	defp evaluate(_tokens=[], stack) do
		[answer | _stack] = stack
		answer.val
	end

	defp eval_op(operator, tokens, stack) do
		[second_token | stack] = stack
        [first_token | stack] = stack
        first = 
            cond do
                is_integer(first_token.val) -> first_token.val
                !is_integer(first_token.val) -> String.to_integer(first_token.val)
            end
        second = 
            cond do
                is_integer(second_token.val) -> second_token.val
                !is_integer(second_token.val) -> String.to_integer(second_token.val)
            end
		answer = 
			case operator.val do
				"+" -> Tokens.match_token(type: :int, val: first + second)
				"-" -> Tokens.match_token(type: :int, val: first - second)
				"/" -> Tokens.match_token(type: :int, val: div(first, second))
				"*" -> Tokens.match_token(type: :int, val: first * second)
			end
		stack = [answer | stack]
		evaluate(tokens, stack)
	end

	defp eval_int(num, tokens, stack) do
		stack = [num | stack]
 		evaluate(tokens, stack)
	end

end