defmodule TasktrackerspaWeb.TokenController do
  use TasktrackerspaWeb, :controller
  alias Tasktrackerspa.Users.User

  action_fallback TasktrackerspaWeb.FallbackController

  def create(conn, %{"name" => name, "pass" => pass}) do
    with {:ok, %User{} = user} <- Tasktrackerspa.Users.get_and_auth_user(name, pass) do
      token = Phoenix.Token.sign(conn, "auth token", user.id)
      conn
      |> put_status(:created)
      |> render("token.json", user: user, token: token)
    end
  end
end
