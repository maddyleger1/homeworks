defmodule Tasktracker.Tracker.Task do
  use Ecto.Schema
  import Ecto.Changeset
  alias Tasktracker.Tracker.Task

  schema "tasks" do
    field :complete, :boolean, default: false
    field :description, :string
    field :time_spent, :integer, default: 0
    field :title, :string
    belongs_to :user, Tasktracker.Accounts.User

    timestamps()
  end

  @doc false
  def changeset(%Task{} = task, attrs) do
    task
    |> cast(attrs, [:title, :description, :time_spent, :complete, :user_id])
    |> validate_required([:title, :description, :time_spent, :complete, :user_id])
  end
end
