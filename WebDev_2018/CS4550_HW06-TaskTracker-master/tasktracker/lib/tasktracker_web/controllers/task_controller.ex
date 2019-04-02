defmodule TasktrackerWeb.TaskController do
  use TasktrackerWeb, :controller
  use Rummage.Phoenix.Controller
  alias Tasktracker.Tracker
  alias Tasktracker.Tracker.Task
  alias Tasktracker.Accounts

  def index(conn, params) do
    {tasks, rummage} = Tracker.list_tasks(params["rummage"])
    IO.puts inspect(rummage)
    render(conn, "index.html", tasks: tasks, rummage: rummage)
  end

  def new(conn, _params) do
    changeset = Tracker.change_task(%Task{})
    users = Accounts.list_users()
    render(conn, "new.html", changeset: changeset, users: users)
  end

  def create(conn, %{"task" => task_params}) do
    users = Accounts.list_users()
    case Tracker.create_task(task_params) do
      {:ok, task} ->
        conn
        |> put_flash(:info, "Task created successfully.")
        |> redirect(to: page_path(conn, :feed))
      {:error, %Ecto.Changeset{} = changeset} ->
        render(conn, "new.html", changeset: changeset, users: users)
    end
  end

  def show(conn, %{"id" => id}) do
    task = Tracker.get_task!(id)
    render(conn, "show.html", task: task)
  end

  def edit(conn, %{"id" => id}) do
    task = Tracker.get_task!(id)
    changeset = Tracker.change_task(task)
    users = Accounts.list_users()
    render(conn, "edit.html", task: task, changeset: changeset, users: users)
  end

  def update(conn, %{"id" => id, "task" => task_params}) do
    task = Tracker.get_task!(id)

    case Tracker.update_task(task, task_params) do
      {:ok, task} ->
        conn
        |> put_flash(:info, "Task updated successfully.")
        |> redirect(to: page_path(conn, :feed))
      {:error, %Ecto.Changeset{} = changeset} ->
        render(conn, "edit.html", task: task, changeset: changeset)
    end
  end

  def delete(conn, %{"id" => id}) do
    task = Tracker.get_task!(id)
    {:ok, _task} = Tracker.delete_task(task)

    conn
    |> put_flash(:info, "Task deleted successfully.")
    |> redirect(to: page_path(conn, :feed))
  end
end
