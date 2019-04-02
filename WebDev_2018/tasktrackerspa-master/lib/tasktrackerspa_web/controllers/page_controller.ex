defmodule TasktrackerspaWeb.PageController do
  use TasktrackerspaWeb, :controller

  def index(conn, _params) do
    render conn, "index.html"
  end
end
