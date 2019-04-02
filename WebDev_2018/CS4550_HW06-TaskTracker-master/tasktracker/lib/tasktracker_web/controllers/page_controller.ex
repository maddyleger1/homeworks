defmodule TasktrackerWeb.PageController do
  use TasktrackerWeb, :controller

  def index(conn, _params) do
    render conn, "index.html"
  end

  def feed(conn, _params) do
    {tasks, rummage} = Tasktracker.Tracker.list_tasks()
    changeset = Tasktracker.Tracker.change_task(%Tasktracker.Tracker.Task{})
    users = Tasktracker.Accounts.list_users()
    render conn, "feed.html", rummage: rummage, tasks: tasks, changeset: changeset, users: users
  end
end
