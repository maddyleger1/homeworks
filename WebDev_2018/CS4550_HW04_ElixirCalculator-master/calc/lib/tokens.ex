defmodule Tokens do
    defstruct [:type, :val]
    @token_types %{
        int: "int",
        op: "op",
        left: "(",
        right: ")",
        eof: "eof",
        illegal: "illegal",
        sp: "sp"
    }

    def match_token(type: type, val: val) do
        if Map.has_key?(@token_types, type) do
            %__MODULE__{type: type, val: val}
        else
            error()
        end
    end

    defp error() do
        raise "Token error"
    end
end