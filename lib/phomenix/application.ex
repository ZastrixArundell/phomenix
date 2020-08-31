defmodule Phomenix.Application do
  # See https://hexdocs.pm/elixir/Application.html
  # for more information on OTP Applications
  @moduledoc false

  use Application

  def start(_type, _args) do
    # List all child processes to be supervised
    children = [
      # Start the Ecto repository
      Phomenix.Repo,
      # Start the endpoint when the application starts
      PhomenixWeb.Endpoint,
      # Starts a worker by calling: Phomenix.Worker.start_link(arg)
      # {Phomenix.Worker, arg},
      {Phomenix.Controllers.Watcher, :controller}
    ]

    # See https://hexdocs.pm/elixir/Supervisor.html
    # for other strategies and supported options
    opts = [strategy: :one_for_one, name: Phomenix.Supervisor]
    Supervisor.start_link(children, opts)
  end

  # Tell Phoenix to update the endpoint configuration
  # whenever the application is updated.
  def config_change(changed, _new, removed) do
    PhomenixWeb.Endpoint.config_change(changed, removed)
    :ok
  end
end
